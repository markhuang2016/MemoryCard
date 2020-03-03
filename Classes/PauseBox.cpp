//
// Created by mark on 2020/2/9.
//

#include <cocos/ui/UIButton.h>
#include <cocos/ui/UIScale9Sprite.h>
#include "PauseBox.h"

PauseBox::PauseBox() : continueCallback(nullptr), exitCallback(nullptr) {

}

PauseBox::~PauseBox() {
    this->removeAllChildren();
}

bool PauseBox::init() {
    if (Layer::init() == false) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto backColor = LayerColor::create(Color4B(0, 0, 0, 200));
    auto box = ui::Scale9Sprite::create("box.png");
    auto continueBtn = ui::Button::create("continue.png");
    auto exitBtn = ui::Button::create("exit.png");

    box->setContentSize(Size(450, 300));
    box->setPosition(visibleSize / 2);

    continueBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 75));
    exitBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 75));

    continueBtn->addClickEventListener([this](Ref *ref) {
        if (continueCallback) {
            continueCallback();
        }
    });

    exitBtn->addClickEventListener([this](Ref *ref) {
        if (exitCallback) {
            exitCallback();
        }
    });

    addChild(backColor);
    addChild(box);
    addChild(continueBtn);
    addChild(exitBtn);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch,Event* event){ return true; };
    listener->setSwallowTouches(true);

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, backColor);

    return true;
}

void PauseBox::registerCallback(std::function<void()> continueCallback, std::function<void()> exitCallback) {
    this->continueCallback = continueCallback;
    this->exitCallback = exitCallback;
}