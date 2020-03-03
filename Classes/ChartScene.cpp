//
// Created by mark on 2020/2/9.
//

#include <cocos/ui/UIButton.h>
#include <cocos/ui/UITextAtlas.h>
#include "ChartScene.h"
#include "SceneManager.h"
#include "UserConst.h"

ChartScene::ChartScene() : backGround(nullptr), returnBtn(nullptr), newScore(nullptr), newScoreTitle(nullptr),
                           chartTitle(nullptr) {

}

ChartScene::~ChartScene() {

}

bool ChartScene::init() {
    if (Layer::init() == false) {
        return false;
    }

    backGround = BackGround::create();
    returnBtn = ui::Button::create("return.png");
    newScoreTitle = Sprite::create("nowScore.png");
    newScore = ui::TextAtlas::create("0", "number.png", 22, 32, "0");
    chartTitle = Sprite::create("chart.png");

    auto visibleSize = Director::getInstance()->getVisibleSize();

    returnBtn->setAnchorPoint(Vec2(0, 1));
    returnBtn->setScale(0.5);
    returnBtn->setPosition(Vec2(-40, visibleSize.height - 10));
    returnBtn->addClickEventListener([](Ref *ref) {
        SceneManager::getInstance()->toStartScene();
    });

    newScoreTitle->setAnchorPoint(Vec2(0, 0.5));
    newScoreTitle->setScale(0.5);
    newScoreTitle->setPosition(Vec2(10, visibleSize.height / 2 + 250));

    newScore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
    auto score = UserDefault::getInstance()->getIntegerForKey(NewScore, 100);
    newScore->setString(StringUtils::format("%d", score));

    chartTitle->setAnchorPoint(Vec2(0, 0.5));
    chartTitle->setScale(0.5);
    chartTitle->setPosition(Vec2(10, visibleSize.height / 2 + 100));

    addChild(backGround);
    addChild(returnBtn);
    addChild(newScore);
    addChild(newScoreTitle);
    addChild(chartTitle);




    for (int i = 0; i < 5; ++i) {
        int score = UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d", RankScore, i).c_str(), 0);

        auto row = createChart(i, score);
        row->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50 - 75 * i));
        this->addChild(row);
    }

    return true;
}

Node* ChartScene::createChart(int rank, int score) {

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto row = Node::create();
    auto r = ui::TextAtlas::create("0", "number.png", 22, 32, "0");
    auto s = ui::TextAtlas::create("0", "number.png", 22, 32, "0");

    r->setString(StringUtils::format("%d", rank + 1));
    s->setString(StringUtils::format("%d", score));

    r->setAnchorPoint(Vec2(0, 0.5));
    s->setAnchorPoint(Vec2(1, 0.5));

    r->setPosition(Vec2(30, 0));
    s->setPosition(Vec2(visibleSize.width - 30, 0));

    row->addChild(r);
    row->addChild(s);

    row->setAnchorPoint(Vec2(0.5, 0.5));
    row->setContentSize(Size(visibleSize.width, 75));
    return row;
}

Scene* ChartScene::createScene() {

    auto scene = Scene::create();

    auto layer = ChartScene::create();
    scene->addChild(layer);

    return scene;
}

