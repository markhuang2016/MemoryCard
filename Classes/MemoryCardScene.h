//
// Created by mark on 2020/2/7.
//

#ifndef MEMORYCARD_MEMORYCARDSCENE_H
#define MEMORYCARD_MEMORYCARDSCENE_H


#include "ScoreData.h"
#include <memory>
#include "StatisticStrategyBase.h"
#include "MemoryCardLevel.h"
#include "BackGround.h"
#include "EnergyBar.h">
#include "ScoreText.h"
#include <cocos2d.h>
USING_NS_CC;

class MemoryCardScene :public Layer{
protected:
    int nowLevel;

    int allLevel;

    std::vector<LevelData> levelDatas;

    LevelData nowLevelData;

    ScoreData scoreData;

    std::shared_ptr<StatisticStrategyBase> statisticStrategy;

    MemoryCardLevel* memoryCardLevel;

    BackGround *background;

    EnergyBar *energyBar;

    ScoreText *scoreText;

    ui::Button *pauseBut;

public:
    MemoryCardScene();

    virtual ~MemoryCardScene();

    static Scene *createScene(std::shared_ptr<StatisticStrategyBase> statisticStrategy);

    static MemoryCardScene *create(std::shared_ptr<StatisticStrategyBase> statisticStrategy);

    bool initWithScoreStrategy(std::shared_ptr<StatisticStrategyBase> statisticStrategy);

    virtual void initLevelDatas();

    virtual void initUI();

    virtual void newGame();

    virtual void nextLevel();

    virtual void update(float t);

};


#endif //MEMORYCARD_MEMORYCARDSCENE_H
