//
// Created by mark on 2020/2/4.
//

#ifndef MEMORYCARD_CARD_H
#define MEMORYCARD_CARD_H


#include "ICard.h"
#include <cocos2d.h>
USING_NS_CC;
class Card : public ICard, public Node {
    Card();

    virtual ~Card();
    
protected:
    CardState cardState;
    CardData cardData;
    CC_PROPERTY(Node*,backImage,BackImage);
    CC_PROPERTY(Node*,frontImage,FrontImage);

    void flipTo(Node *from, Node *to, const std::function<void()> &callback = nullptr);

public:
    CREATE_FUNC(Card);
    
    virtual void flipToBack(const std::function<void()> &callback= nullptr) ;

    virtual void flipToFront(const std::function<void()> &callback = nullptr) ;

    virtual CardState getCardState() const ;

    virtual void setCardState(CardState cardState) ;

    virtual CardData* getCardData();

    virtual CardData* setCardData(CardData cardData);

};


#endif //MEMORYCARD_CARD_H
