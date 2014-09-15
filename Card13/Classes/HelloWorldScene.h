#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

enum CardType
{
    Clubs,
    Diamonds,
    Hearts,
    Spades,
};

struct Card
{
    int number;
    CardType type;
};

struct PosIndex
{
    int x;
    int y;
};

class CardSprite : public cocos2d::Sprite
{
protected:
    std::string getFileName(CardType type);
    void showNumber();
    
public:
    virtual bool init();
    void onEnter() override;
    CREATE_FUNC(CardSprite);
    
    CC_SYNTHESIZE(Card, _card, Card);
    CC_SYNTHESIZE(PosIndex, _posIndex, PosIndex);
};

class HelloWorld : public cocos2d::Layer
{
protected:
    std::vector<Card> _cards;
    
    void initCards();
    Card getCard();
    void createCard(PosIndex posIndex);
    void showInitCards();
    void initGame();
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
