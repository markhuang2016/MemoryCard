//
// Created by mark on 2020/2/9.
//

#ifndef MEMORYCARD_PAUSEBOX_H
#define MEMORYCARD_PAUSEBOX_H

#include <cocos2d.h>
USING_NS_CC;

class PauseBox :public Layer {
protected:
    std::function<void()> continueCallback;
    std::function<void()> exitCallback;

public:
    PauseBox();

    virtual ~PauseBox();

    CREATE_FUNC(PauseBox);

    virtual bool init();

    virtual void registerCallback(std::function<void()> continueCallback, std::function<void()> exitCallback);

};


#endif //MEMORYCARD_PAUSEBOX_H
