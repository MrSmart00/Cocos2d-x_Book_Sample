#include "HelloWorldScene.h"
#include <random>

#define CARD_NUM 13
#define CARD_TYPE_NUM 4

#define CARD_1_POS_X 200
#define CARD_1_POS_Y 320
#define CARD_DISTANCE_X 140
#define CARD_DISTANCE_Y 200

#define ZORDER_SHOW_CARD 1

USING_NS_CC;

bool CardSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    return true;
}

void CardSprite::onEnter()
{
    Sprite::onEnter();
    
    setTexture(getFileName(_card.type));
    showNumber();
    float x = CARD_1_POS_X + CARD_DISTANCE_X * _posIndex.x;
    float y = CARD_1_POS_Y + CARD_DISTANCE_Y * _posIndex.y;
    setPosition(x, y);
    setTag(_posIndex.x + _posIndex.y * 5 + 1);
}

std::string CardSprite::getFileName(CardType type)
{
    std::string filename;
    switch (type) {
        case Clubs:
            filename = "card_clubs.png";
            break;
        case Diamonds:
            filename = "card_diamonds.png";
            break;
        case Hearts:
            filename = "card_hearts.png";
            break;
        default:
            filename = "card_spades.png";
            break;
    }
    return filename;
}

void CardSprite::showNumber()
{
    std::string numberString;
    switch (_card.number) {
        case 1:
            numberString = "A";
            break;
        case 11:
            numberString = "J";
            break;
        case 12:
            numberString = "Q";
            break;
        case 13:
            numberString = "K";
            break;
        default:
            numberString = StringUtils::format("%d", _card.number);
            break;
    }
    
    Color4B textColor;
    switch (_card.type) {
        case Clubs:
        case Spades:
            textColor = Color4B::BLACK;
            break;
        default:
            textColor = Color4B::RED;
            break;
    }
    auto number = Label::createWithSystemFont(numberString, "Arial", 96);
    number->setPosition(Point(getContentSize() / 2));
    number->setTextColor(textColor);
    addChild(number);
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    initGame();
    
    return true;
}

void HelloWorld::initCards()
{
    _cards.clear();
    for (int type = 0; type < CARD_TYPE_NUM; type++) {
        for (int number = 1; number <= CARD_NUM; number++) {
            Card card;
            card.number = number;
            card.type = (CardType)type;
            
            _cards.push_back(card);
        }
    }
}

Card HelloWorld::getCard()
{
    std::random_device rd;
    std::mt19937 rand = std::mt19937(rd());
    
    int index = std::uniform_int_distribution<int>(0, (int)_cards.size() - 1)(rand);
    
    auto card = _cards[index];
    _cards.erase(_cards.begin() + index);
    return card;
}

void HelloWorld::createCard(PosIndex posIndex)
{
//    auto card = Sprite::create("card_spades.png");
//    card->setPosition(CARD_1_POS_X + CARD_DISTANCE_X * posIndex.x,
//                      CARD_1_POS_Y + CARD_DISTANCE_Y * posIndex.y);
//    addChild(card, ZORDER_SHOW_CARD);
    auto card = CardSprite::create();
    card->setCard(getCard());
    card->setPosIndex(posIndex);
    addChild(card, ZORDER_SHOW_CARD);
}

void HelloWorld::showInitCards()
{
    for (int tag = 1; tag <= 10; tag++) {
        auto card = getChildByTag(tag);
        if (card) {
            card->removeFromParent();
        }
    }
    
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 2; y++) {
            PosIndex posIndex;
            posIndex.x = x;
            posIndex.y = y;
            
            createCard(posIndex);
        }
    }
}

void HelloWorld::initGame()
{
    initCards();
    showInitCards();
}