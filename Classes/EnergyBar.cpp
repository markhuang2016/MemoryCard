//
// Created by mark on 2020/2/8.
//

#include "EnergyBar.h"

EnergyBar::EnergyBar() : progress(0) {

}

EnergyBar::~EnergyBar() {

}

bool EnergyBar::init() {

    if (Node::init() == false) {
        return false;
    }


    emptyBar = Sprite::create("emptyBar.jpg");
    energyBar = ProgressTimer::create(Sprite::create("energyBar.tga"));
    energyBar->setType(cocos2d::ProgressTimer::Type::BAR);
    energyBar->setMidpoint(Vec2(0, 0));
    energyBar->setBarChangeRate(Vec2(1, 0));


    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto barSize = emptyBar->getContentSize();
    float scale = visibleSize.width / (barSize.width + 100);

    emptyBar->setAnchorPoint(Vec2(0, 0));
    energyBar->setAnchorPoint(Vec2(0, 0));
    emptyBar->setPosition(Vec2(0, 0));
    energyBar->setPosition(Vec2(0, 0));
    emptyBar->setScaleX(scale);
    energyBar->setScaleX(scale);
    this->setContentSize(Size(visibleSize.width - 100, barSize.height));

    addChild(emptyBar);
    addChild(energyBar);

    updateView(100);

    return true;
}

void EnergyBar::updateView(int value) {
    progress = value/100;
    energyBar->setPercentage(progress);
}