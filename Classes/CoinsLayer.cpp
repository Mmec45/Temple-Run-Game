//
// Created by shree on 11-04-2021.
//

#include "CoinsLayer.h"

#define CCRANDOM_0_1() ((float)rand()/RAND_MAX)

CoinsLayer::~CoinsLayer()
{

}

CoinsLayer* CoinsLayer::create()
{
    CoinsLayer* layer = new CoinsLayer();
    layer->init();
    return layer;
}

bool CoinsLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    random = rand() % 10;


    for(int i=1;i<random;i++){
        auto coin = Sprite::createWithSpriteFrameName("coin.png");

        coin->setPosition(Point(visibleSize.width+coin->getContentSize().width*i, visibleSize.height * 0.3f));
        this->addChild(coin);
        coins[i]=coin;
    }

    scheduleUpdate();


    return true;
}

void CoinsLayer::update(float dt)
{

    Size visibleSize = Director::getInstance()->getVisibleSize();
    for(int i=1;i<random;i++){
        coins[i]->setPositionX(coins[i]->getPositionX()-speed*dt);

        if(!coins[i]->isVisible() || coins[i]->getPositionX()<0){

            coins[i]->setPosition(Point(visibleSize.width+coins[i]->getContentSize().width*i, visibleSize.height * 0.3f));
            coins[i]->setVisible(true);

        }


    }

}

bool CoinsLayer::checkCollection(Sprite *pSprite) {

    bool coinhit=false;

    for(int i=1;i<random;i++){
        if(coins[i]->getBoundingBox().intersectsRect(pSprite->getBoundingBox()) && coins[i]->isVisible()){
            coins[i]->setVisible(false);
            coinhit=true;
            break;
        }

    }

    return coinhit;
}