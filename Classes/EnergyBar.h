//
// Created by mark on 2020/2/8.
//

#ifndef MEMORYCARD_ENERGYBAR_H
#define MEMORYCARD_ENERGYBAR_H

#include <cocos2d.h>
USING_NS_CC;

class EnergyBar :public Node{
    Sprite *emptyBar;
    ProgressTimer *energyBar;
    int progress;

public:
    EnergyBar();

    virtual ~EnergyBar();

    CREATE_FUNC(EnergyBar);

    bool init();

    void updateView(int value);

};


#endif //MEMORYCARD_ENERGYBAR_H
