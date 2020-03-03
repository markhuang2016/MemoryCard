//
// Created by mark on 2020/2/7.
//

#ifndef MEMORYCARD_STATISTICSTRATEGY_H
#define MEMORYCARD_STATISTICSTRATEGY_H


#include "StatisticStrategyBase.h"

class StatisticStrategy: public StatisticStrategyBase {
    int continuous;
public:
    StatisticStrategy();

    void execute(ScoreData& scoreData, CardData *cardA, CardData *cardB);

};


#endif //MEMORYCARD_STATISTICSTRATEGY_H
