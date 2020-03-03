//
// Created by mark on 2020/2/9.
//

#ifndef MEMORYCARD_SCENEMANAGER_H
#define MEMORYCARD_SCENEMANAGER_H

#include <cocos2d.h>
USING_NS_CC;

class SceneManager {

protected:
    static SceneManager *sceneManager;

public:
    static SceneManager *getInstance();

    void toStartScene();

    void toChartScene();

    void toGameScene();
};


#endif //MEMORYCARD_SCENEMANAGER_H
