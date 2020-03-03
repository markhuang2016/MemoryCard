//
// Created by mark on 2020/2/4.
//

#ifndef MEMORYCARD_ICARD_H
#define MEMORYCARD_ICARD_H

#include <functional>
#include "CardState.h"
#include "CardData.h"

class ICard{
public:
    virtual void flipToBack(const std::function<void()> &callback= nullptr) = 0;

    virtual void flipToFront(const std::function<void()> &callback = nullptr) = 0;

    virtual CardState getCardState() const = 0;

    virtual void setCardState(CardState cardState) = 0;

    virtual CardData* getCardData()=0;

};
#endif //MEMORYCARD_ICARD_H
