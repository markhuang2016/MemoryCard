//
// Created by mark on 2020/2/7.
//

#include "MemoryCardScene.h"
#include "PauseBox.h"
#include "SceneManager.h"
#include "UserConst.h"
#include <SimpleAudioEngine.h>

MemoryCardScene::MemoryCardScene() : scoreData({}), nowLevel(0), allLevel(0) {
    scoreData.energy = 10000;
}

MemoryCardScene::~MemoryCardScene() {
    unscheduleUpdate();
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

Scene* MemoryCardScene::createScene(std::shared_ptr<StatisticStrategyBase> statisticStrategy) {
    auto scene = Scene::create();
    auto layer = MemoryCardScene::create(statisticStrategy);
    scene->addChild(layer);
    return scene;
}

MemoryCardScene* MemoryCardScene::create(std::shared_ptr<StatisticStrategyBase> statisticStrategy) {
    MemoryCardScene *memoryCardScene = new MemoryCardScene();
    if (memoryCardScene && memoryCardScene->initWithScoreStrategy(statisticStrategy)) {
        memoryCardScene->autorelease();
        return memoryCardScene;
    }
    return nullptr;
}

bool MemoryCardScene::initWithScoreStrategy(std::shared_ptr<StatisticStrategyBase> statisticStrategy) {
    if (Layer::init() == false) {
        return false;
    }
    this->statisticStrategy = statisticStrategy;

    initLevelDatas();

    initUI();

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("countDown_10.mp3", true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);

    newGame();

    return true;
}

void MemoryCardScene::initLevelDatas() {

    auto levelstr = FileUtils::getInstance()->getStringFromFile("level.csv");

    std::vector<std::string> rows;
    auto row = strtok((char *) levelstr.c_str(), "\n");

    while (row) {
        rows.emplace_back(row);
        row = strtok(nullptr, "\n");
    }



    for (int i = 1; i < rows.size(); ++i) {
        auto str = rows.at(i);
        auto row = strtok((char *) str.c_str(), ",");
        auto column = strtok(nullptr, ",");
        auto loss = strtok(nullptr, ",");

        if (row == nullptr || column == nullptr || loss == nullptr) {
            continue;
        }

        LevelData levelData;

        levelData.rows = atoi(row);
        levelData.columns = atoi(column);
        levelData.loss = atoi(loss);

        if (levelData.rows * levelData.columns >0 || levelData.rows * levelData.columns % 2 == 0) {
            levelDatas.push_back(levelData);
        }
    }

    allLevel = levelDatas.size();
}

void MemoryCardScene::initUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    background = BackGround::create();
    addChild(background);

    energyBar = EnergyBar::create();
    energyBar->setAnchorPoint(Vec2(0.5, 1));
    energyBar->setPosition(visibleSize.width / 2 + 10, visibleSize.height - 10);
    addChild(energyBar);

    scoreText = ScoreText::create();
    scoreText->setAnchorPoint(Vec2(1, 1));
    scoreText->setPosition(visibleSize.width - 20, visibleSize.height - 10);
    addChild(scoreText);

    pauseBut = ui::Button::create("pauseBut.png");
    pauseBut->setAnchorPoint(Vec2(0, 1));
    pauseBut->setPosition(Vec2(0, visibleSize.height));
    pauseBut->addClickEventListener([this](Ref *ref) {
        auto pauseBox = PauseBox::create();
        pauseBox->registerCallback([this, pauseBox]() {
                                       pauseBox->removeFromParent();
                                       scheduleUpdate();
                                   },
                                   [this]() {
                                       //退出游戏
                                       SceneManager::getInstance()->toStartScene();

                                       UserDefault::getInstance()->setIntegerForKey(NewScore, scoreData.score);

                                       std::vector<int> scoreList;

                                       scoreList.push_back(scoreData.score);

                                       for (int i = 0; i < 5; ++i) {
                                           auto score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RankScore, i).c_str(), 0);
                                           scoreList.push_back(score);
                                       }

                                       std::sort(scoreList.begin(), scoreList.end(), [](int &a,int &b) {
                                           return a > b;
                                       });

                                       for (int i = 0; i < 5; ++i) {
                                           UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", RankScore, i).c_str(),
                                                                                        scoreList.at(i));
                                       }

                                   });
        addChild(pauseBox);
        unscheduleUpdate();
    });
    addChild(pauseBut);
}

void MemoryCardScene::newGame() {

    scheduleUpdate();
    nextLevel();

}

void MemoryCardScene::nextLevel() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (nowLevel >= allLevel) {
        nowLevel = 0;
    }
    nowLevelData = levelDatas.at(nowLevel);
    nowLevel++;
    auto level = MemoryCardLevel::create(nowLevelData);
    this->memoryCardLevel = level;

    level->setAnchorPoint(Vec2(0.5, 0.5));
    level->ignoreAnchorPointForPosition(false);

    level->setPosition(visibleSize.width/2,visibleSize.height/2-40);
    auto scale = visibleSize.height / (level->getContentSize().height + 100);
    level->setScale(2);
    level->setOpacity(0);

    level->runAction(Spawn::create(
            FadeIn::create(0.25),
            ScaleTo::create(0.25, scale),
            NULL
    ));

    this->addChild(level);
    level->registerCallback([this](CardData *cardDataA, CardData *cardDataB) {
        statisticStrategy->execute(scoreData, cardDataA, cardDataB);
        CCLOG("energy:%d,maxContinuous:%d,score:%d",scoreData.energy,scoreData.maxContinuous,scoreData.score );
    }, [this]() {
        CCLOG("complete");
        this->memoryCardLevel->removeFromParent();
        memoryCardLevel = nullptr;
        nextLevel();
    });


}

void MemoryCardScene::update(float t) {
    Layer::update(t);

    scoreData.energy -= nowLevelData.loss * t;

    if (scoreData.energy < 0) {
        scoreData.energy = 0;
    }

    energyBar->updateView(scoreData.energy);

    if (scoreData.energy / 10000.0f < 0.5) {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1-scoreData.energy / 10000.0f);
    } else{
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
    }

    if (scoreData.energy <= 0) {
        UserDefault::getInstance()->setIntegerForKey(NewScore, scoreData.score);

        std::vector<int> scoreList;

        scoreList.push_back(scoreData.score);

        for (int i = 0; i < 5; ++i) {
            auto score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RankScore, i).c_str(), 0);
            scoreList.push_back(score);
        }

        std::sort(scoreList.begin(), scoreList.end(), [](int &a,int &b) {
            return a > b;
        });

        for (int i = 0; i < 5; ++i) {
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d", RankScore, i).c_str(),
                                                         scoreList.at(i));
        }
        SceneManager::getInstance()->toChartScene();
    }

    scoreText->updateView(scoreData.score);
}