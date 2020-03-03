//
// Created by mark on 2020/2/9.
//

#include "StartScene.h"
#include "SceneManager.h"

StartScene::StartScene() : startBtn(nullptr), exitBtn(nullptr), chartBtn(nullptr), logo(nullptr), backGround(nullptr) {

}

StartScene::~StartScene() {
    this->removeAllChildren();
}

bool StartScene::init() {

    if (Layer::init() == false) {
        return false;
    }

    backGround = BackGround::create();
    startBtn = ui::Button::create("startButton.png");
    exitBtn = ui::Button::create("exitBut.png");
    chartBtn = ui::Button::create("sorted.png");
    logo = Sprite::create("memory.png");

    logo->setAnchorPoint(Vec2(0.5, 0.5));
    exitBtn->setAnchorPoint(Vec2(0.5, 0.5));
    startBtn->setAnchorPoint(Vec2(0.5, 0.5));
    chartBtn->setAnchorPoint(Vec2(0.5, 0.5));

    auto visibleSize = Director::getInstance()->getVisibleSize();
    logo->setPosition(visibleSize.width / 2, visibleSize.height/2 + 250);
    startBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/2 + 75));
    chartBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/2 - 75));
    exitBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/2 + -220));

    startBtn->addClickEventListener([](Ref *ref) {
        SceneManager::getInstance()->toGameScene();
    });

    chartBtn->addClickEventListener([](Ref *ref) {
        SceneManager::getInstance()->toChartScene();
    });

    exitBtn->addClickEventListener([](Ref *ref) {
        Director::getInstance()->end();
    });
    addChild(backGround);
    addChild(startBtn);
    addChild(exitBtn);
    addChild(chartBtn);
    addChild(logo);

    return true;
}

Scene* StartScene::createScene() {
    auto layer = StartScene::create();
    auto scene = Scene::create();
    scene->addChild(layer);
    return scene;
}