//
// Created by mark on 2020/2/9.
//

#ifndef MEMORYCARD_STARTSCENE_H
#define MEMORYCARD_STARTSCENE_H

#include <cocos2d.h>
#include <cocos/ui/UIButton.h>
#include "BackGround.h"

USING_NS_CC;

class StartScene :public Layer {
protected:
    ui::Button *startBtn;
    ui::Button *exitBtn;
    ui::Button *chartBtn;
    Sprite *logo;
    BackGround * backGround;

public:
    StartScene();

    virtual ~StartScene();

    CREATE_FUNC(StartScene);

    virtual bool init();

    static Scene *createScene();

};


#endif //MEMORYCARD_STARTSCENE_H
