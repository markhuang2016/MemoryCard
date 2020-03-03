//
// Created by mark on 2020/2/8.
//

#include "ScoreText.h"

ScoreText::ScoreText() : score(0) {

}

ScoreText::~ScoreText() {

}

bool ScoreText::init() {
    if (Node::init() == false) {
        return false;
    }

    text = ui::TextAtlas::create("0", "number.png", 22, 32, "0");

    text->setAnchorPoint(Vec2(1, 1));

    addChild(text);

    return true;
}

void ScoreText::updateView(int value) {

    if (score == value) {
        return;
    }

    score = value;
    text->setString(StringUtils::format("%d", value));

    auto effect = text->clone();
    effect->runAction(Sequence::create(Spawn::create(
            ScaleTo::create(0.5, 2),
            FadeOut::create(0.5)
            ,NULL
    ), CallFunc::create([effect](){
        effect->removeFromParent();
    }),
            NULL));

    addChild(effect);
}