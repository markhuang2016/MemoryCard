//
// Created by mark on 2020/2/5.
//

#ifndef MEMORYCARD_CARDFACTORY_H
#define MEMORYCARD_CARDFACTORY_H

#include "Card.h"

class CardFactory {
public:
    ICard* createCard(int cardNumber, int number);
};


#endif //MEMORYCARD_CARDFACTORY_H
