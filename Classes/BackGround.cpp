//
// Created by mark on 2020/2/7.
//

#include "BackGround.h"

BackGround::BackGround() {

}

BackGround::~BackGround() {
    unscheduleUpdate();
}

bool BackGround::init() {

    if (Node::init() == false) {
        return false;
    }

    sprite = Sprite::create("background.jpeg");
    sprite->setAnchorPoint(Vec2(0, 0));

    Texture2D::TexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    sprite->getTexture()->setTexParameters(tp);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    sprite->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));

    this->addChild(sprite);

    scheduleUpdate();

    return true;
}

void BackGround::update(float t) {
    Node::update(t);

    auto rect = sprite->getTextureRect();
    rect.origin.x += 100 * t;
    rect.origin.y += 100 * t;

    sprite->setTextureRect(rect);
}