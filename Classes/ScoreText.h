//
// Created by mark on 2020/2/8.
//

#ifndef MEMORYCARD_SCORETEXT_H
#define MEMORYCARD_SCORETEXT_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
USING_NS_CC;

class ScoreText: public Node {
    ui::TextAtlas *text;
    int score;

public:
    ScoreText();

    virtual ~ScoreText();

    CREATE_FUNC(ScoreText);

    virtual bool init();

    virtual void updateView(int value);
};


#endif //MEMORYCARD_SCORETEXT_H
