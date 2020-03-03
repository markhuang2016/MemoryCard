//
// Created by mark on 2020/2/6.
//

#ifndef MEMORYCARD_MEMORYCARDLEVEL_H
#define MEMORYCARD_MEMORYCARDLEVEL_H

#include "cocos2d.h"
#include "LevelData.h"
#include "Card.h"
USING_NS_CC;

class MemoryCardLevel :public Layer{

    LevelData levelData;

    std::vector<std::vector<Card*>> cardTable;

    int unfinnishedCard;

    Card* selectedCard;

    std::function<void(CardData *a, CardData *b)> pairCallBack;

    std::function<void()> completeCallBack;

public:

    MemoryCardLevel();

    virtual ~MemoryCardLevel();

    static MemoryCardLevel *create(LevelData levelData);

    virtual bool initWithLevelData(LevelData levelData);

    void registerCallback(std::function<void(CardData *a, CardData *b)> pairCallBack, std::function<void()> completeCallBack);

protected:
    virtual void initCardLayout();

    virtual void initTouchEvent();

};


#endif //MEMORYCARD_MEMORYCARDLEVEL_H
