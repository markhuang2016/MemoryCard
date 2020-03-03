//
// Created by mark on 2020/2/7.
//

#ifndef MEMORYCARD_STATISTICSTRATEGYBASE_H
#define MEMORYCARD_STATISTICSTRATEGYBASE_H

#include "ScoreData.h"
#include "CardData.h"

class StatisticStrategyBase {
public:
    virtual void execute(ScoreData& scoreData, CardData *cardA, CardData *cardB) = 0;
};
#endif //MEMORYCARD_STATISTICSTRATEGYBASE_H
