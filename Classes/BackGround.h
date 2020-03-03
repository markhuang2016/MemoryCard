//
// Created by mark on 2020/2/7.
//

#ifndef MEMORYCARD_BACKGROUND_H
#define MEMORYCARD_BACKGROUND_H

#include <cocos2d.h>
USING_NS_CC;

class BackGround :public Node{

    Sprite *sprite;

public:
    BackGround();

    virtual ~BackGround();

    CREATE_FUNC(BackGround);

    virtual bool init();

    void update(float t);

};


#endif //MEMORYCARD_BACKGROUND_H
