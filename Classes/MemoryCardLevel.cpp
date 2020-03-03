//
// Created by mark on 2020/2/6.
//

#include "MemoryCardLevel.h"
#include "CardFactory.h"
#include <SimpleAudioEngine.h>

MemoryCardLevel::MemoryCardLevel() : selectedCard(nullptr), unfinnishedCard(0) {
    this->setCascadeOpacityEnabled(true);
}

MemoryCardLevel::~MemoryCardLevel() {
    this->removeAllChildren();
//    this->getEventDispatcher()->removeAllEventListeners();
}

MemoryCardLevel* MemoryCardLevel::create(LevelData levelData) {
    MemoryCardLevel *cardLevel = new MemoryCardLevel();
    if (cardLevel && cardLevel->initWithLevelData(levelData)) {
        cardLevel->autorelease();
        return cardLevel;
    }

    CC_SAFE_DELETE(cardLevel);
    return nullptr;
}

bool MemoryCardLevel::initWithLevelData(LevelData levelData) {
    if (Layer::init() == false) {
        return false;
    }
    if ((levelData.rows * levelData.columns) % 2 != 0) {
        return false;
    }

    this->levelData = levelData;

    initCardLayout();

    initTouchEvent();

    return true;
}

void MemoryCardLevel::initCardLayout() {

    int backId = CCRANDOM_0_1() * 4;

    for (int i = 0; i < levelData.rows; ++i) {
        std::vector<Card *> card(levelData.columns);
        cardTable.push_back(card);
    }

    CardFactory cardFactory;
    int number = 0;
    Size cardSize;
    int space = 20;

    Vector<Card*> cards;
    for (int x = 0; x < levelData.rows * levelData.columns; ++x) {
        Card *card = dynamic_cast<Card *>(cardFactory.createCard(backId, number / 2));
        cards.pushBack(card);
        number++;
    }
    unfinnishedCard = cards.size();

    for (int j = 0; j < levelData.rows; ++j) {
        for (int i = 0; i < levelData.columns; ++i) {
            int number = CCRANDOM_0_1() * cards.size();
            Card *card = cards.at(number);
            cards.eraseObject(card);
            card->getCardData()->row = j;
            card->getCardData()->column = i;


            cardSize = card->getContentSize();
            card->setPosition(Vec2((cardSize.width + space) * i + cardSize.width / 2, (cardSize.height + space) * j +
                              cardSize.height / 2));
            cardTable[j][i] = card;

            this->addChild(card);
        };
    }
    this->setContentSize(Size((cardSize.width + space) * (levelData.columns - 1) + cardSize.width,
                              (cardSize.height + space) * (levelData.rows - 1) + cardSize.height));


}

void MemoryCardLevel::registerCallback(std::function<void(CardData *a, CardData *b)> pairCallBack,
                                       std::function<void()> completeCallBack) {
    this->pairCallBack = pairCallBack;
    this->completeCallBack = completeCallBack;
}

void MemoryCardLevel::initTouchEvent() {

    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan=[&](Touch* touch ,Event* event){
        Point point = convertToNodeSpace(touch->getLocation());
        Size size = getContentSize();
        Rect rect(0, 0, size.width, size.height);
        if (rect.containsPoint(point)) {
            return true;
        }
        return false;
    };

    listener->onTouchEnded=[&](Touch* touch ,Event* event){
        Point point = convertToNodeSpace(touch->getLocation());
        Card *selCard = nullptr;
        for (int row = 0; row < levelData.rows; ++row) {
            auto cards = cardTable[row];
            for (int column = 0; column < levelData.columns; ++column) {
                auto card = cards[column];

                if (card == nullptr) {
                    continue;
                }

                auto size = card->getContentSize();
                auto pos = card->getPosition();
                auto rect = Rect(pos.x - size.width / 2, pos.y - size.height / 2, size.width, size.height);
                if (rect.containsPoint(point)) {
                    selCard = card;
                    break;
                }
            }
            if (selCard != nullptr) {
                break;
            }
        }

        if (selCard == nullptr || selCard == this->selectedCard) {
            return;
        }

        if (selectedCard == nullptr) {
            selectedCard = selCard;
            selCard->flipToFront();
        } else {
            //第二次选中

            if (pairCallBack != nullptr) {
                pairCallBack(selectedCard->getCardData(), selCard->getCardData());
            }

            if (selectedCard->getCardData()->number == selCard->getCardData()->number) {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("cardRemove.mp3");

                auto cardA = selectedCard;
                auto cardB = selCard;
                //配对成功，消除
                selCard->flipToFront([&, cardA, cardB]() {
                    cardA->runAction(
                            Sequence::create(Spawn::create(FadeOut::create(0.25f), ScaleTo::create(0.25, 0.25), NULL),
                                             CallFunc::create([&, cardA]() {
                                                 cardA->removeFromParent();
                                             }),
                                             NULL));

                    cardB->runAction(
                            Sequence::create(Spawn::create(FadeOut::create(0.25f), ScaleTo::create(0.25, 0.25), NULL),
                                             CallFunc::create([&, cardB]() {
                                                 cardB->removeFromParent();
                                             }),
                                             NULL));

                });

                cardTable[cardA->getCardData()->row][cardA->getCardData()->column] = nullptr;
                cardTable[cardB->getCardData()->row][cardB->getCardData()->column] = nullptr;

                selectedCard = nullptr;

                unfinnishedCard -= 2;

                if (unfinnishedCard == 0 && completeCallBack != nullptr) {
                    completeCallBack();
                }
            } else {
                //配对失败，翻回去
                auto cardA = selectedCard;
                auto cardB = selCard;
                selCard->flipToFront([&,cardA,cardB](){
                    cardA->flipToBack();
                    cardB->flipToBack();
                });
                selectedCard = nullptr;
            }

        }

    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}