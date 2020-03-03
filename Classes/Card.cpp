//
// Created by mark on 2020/2/4.
//

#include "Card.h"
#include <SimpleAudioEngine.h>

Card::Card() : backImage(nullptr), frontImage(nullptr), cardState(CardState::Back) {
    this->setCascadeOpacityEnabled(true);
}

Card::~Card() {
    this->removeAllChildren();
}

Node* Card::getFrontImage() const {
    return frontImage;
}

Node* Card::getBackImage() const {
    return backImage;
}

void Card::setFrontImage(Node *var) {
    if (nullptr == var) {
        return;
    }

    if (nullptr != frontImage) {
        frontImage->removeFromParent();
    }
    frontImage = var;
    frontImage->setCascadeColorEnabled(true);
    frontImage->setVisible(false);
    addChild(frontImage);
}

void Card::setBackImage(Node *var) {
    if (nullptr == var) {
        return;
    }

    if (nullptr != backImage) {
        backImage->removeFromParent();
    }
    backImage = var;
    backImage->setCascadeColorEnabled(true);
//    backImage->setVisible(false);
    addChild(backImage);
}

void Card::flipTo(Node *from, Node *to, const std::function<void()> &callback) {
    if (from == nullptr || to == nullptr) {
        return;
    }

    from->stopAllActions();
    to->stopAllActions();

    from->setVisible(true);
    from->setScale(1);

    to->setVisible(false);
    to->setScale(0);

    auto flipTo = [from, to, callback]() {
        from->setVisible(false);
        to->setVisible(true);
        CallFunc *func = callback == nullptr ? nullptr : CallFunc::create(callback);
        to->runAction(Sequence::create(ScaleTo::create(0.25f, 1.0f, 1.0f), func, NULL));
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("cardFlip.mp3");
    };

    from->runAction(Sequence::create(ScaleTo::create(0.25f, 0, 1.0f), CallFunc::create(flipTo), NULL));
}

void Card::flipToBack(const std::function<void()> &callback) {
    if (cardState == CardState::Back) {
        return;
    }
    flipTo(frontImage, backImage, callback);
    cardState = CardState::Back;
}

void Card::flipToFront(const std::function<void()> &callback) {
    if (cardState == CardState::Front) {
        return;
    }
    flipTo( backImage,frontImage, callback);
    cardState = CardState::Front;
}

CardState Card::getCardState() const {
    return cardState;
}

void Card::setCardState(CardState cardState) {
    this->cardState = cardState;
}

CardData* Card::getCardData() {
    return &cardData;
}

CardData* Card::setCardData(CardData cardData) {
    this->cardData = cardData;
}