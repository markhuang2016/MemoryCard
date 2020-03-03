//
// Created by mark on 2020/2/7.
//

#include "StatisticStrategy.h"

StatisticStrategy::StatisticStrategy() : continuous(0) {

}

void StatisticStrategy::execute(ScoreData& scoreData, CardData *cardA, CardData *cardB) {

    if (cardA->number == cardB->number) {
        //配对成功，增加连击数，增加能量，增加分数
        continuous++;
        if (continuous > scoreData.maxContinuous) {
            scoreData.maxContinuous = continuous;
        }

        scoreData.energy += 100;

        scoreData.score += 100 * continuous;
    } else {
        //配对失败，清空连击数
        continuous = 0;
        if (cardA->flipCount != 0 || cardB->flipCount != 0) {
            scoreData.energy -= 100;
        }
    }

    cardA->flipCount += 1;
    cardB->flipCount+=1;
}