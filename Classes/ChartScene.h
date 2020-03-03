//
// Created by mark on 2020/2/9.
//

#ifndef MEMORYCARD_CHARTSCENE_H
#define MEMORYCARD_CHARTSCENE_H

#include <cocos2d.h>
#include "BackGround.h"
#include <ui/CocosGUI.h>
#include <vector>

USING_NS_CC;

class ChartScene :public Layer {
protected:
    BackGround *backGround;
    ui::Button *returnBtn;

    Sprite *newScoreTitle;
    ui::TextAtlas *newScore;

    Sprite *chartTitle;
    std::vector<Node *> scores;

    Node *createChart(int rank, int score);
public:
    ChartScene();

    virtual ~ChartScene();

    CREATE_FUNC(ChartScene);

    virtual bool init();

    static Scene *createScene();
};


#endif //MEMORYCARD_CHARTSCENE_H
