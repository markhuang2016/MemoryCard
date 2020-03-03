//
// Created by mark on 2020/2/9.
//

#include "SceneManager.h"
#include "StartScene.h"
#include "ChartScene.h"
#include "MemoryCardScene.h"
#include "StatisticStrategy.h"

SceneManager *SceneManager::sceneManager = nullptr;
SceneManager* SceneManager::getInstance() {
    if (sceneManager == nullptr) {
        sceneManager = new SceneManager();
    }
    return sceneManager;
}
void SceneManager::toStartScene() {

    auto scene = StartScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
void SceneManager::toGameScene() {
    std::shared_ptr<StatisticStrategy> statisticStrategy(new StatisticStrategy());
    auto scene = MemoryCardScene::createScene(statisticStrategy);
    Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(0.25, scene));

}
void SceneManager::toChartScene() {

    auto scene = ChartScene::createScene();
    Director::getInstance()->replaceScene(scene);
}