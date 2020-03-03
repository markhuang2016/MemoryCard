//
// Created by mark on 2020/2/5.
//

#include <cocos/ui/UITextAtlas.h>
#include "CardFactory.h"
#include "cocos2d.h"
USING_NS_CC;

ICard* CardFactory::createCard(int cardNumber, int number) {
    const int cardWidth = 240;
    const int cardHeight = 360;

    if (cardNumber < 0 || cardNumber > 4) {
        cardNumber = 0;
    }

    int x = cardNumber % 2 * cardWidth;
    int y = cardNumber / 2 * cardHeight;

    auto backImage = Sprite::create("back.jpg", Rect(x, y, cardWidth, cardHeight));
    auto frontImage = Node::create();
    frontImage->setContentSize(Size(cardWidth, cardHeight));
    frontImage->addChild(Sprite::create("front.jpeg", Rect(0, 0, cardWidth, cardHeight)));

    auto numberText = ui::TextAtlas::create(StringUtils::format("%d", number), "number.jpeg", 200, 332, "0");
    frontImage->addChild(numberText);

    CardData cardData = {};
    cardData.number = number;

    auto card = Card::create();
    card->setFrontImage(frontImage);
    card->setBackImage(backImage);
    card->setCardData(cardData);

    card->setContentSize(backImage->getContentSize());

    return card;
}