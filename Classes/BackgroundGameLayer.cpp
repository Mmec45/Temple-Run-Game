//
// Created by shree on 11-04-2021.
//

#include "BackgroundGameLayer.h"

BackgroundGameLayer::~BackgroundGameLayer()
{

}

BackgroundGameLayer* BackgroundGameLayer::create()
{
    BackgroundGameLayer* layer = new BackgroundGameLayer();
    layer->init();
    return layer;
}

bool BackgroundGameLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::createWithSpriteFrameName("background.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(bg, -1);

    ground1 = Sprite::createWithSpriteFrameName("ground.png");
    ground1->setName("ground1");

    ground2 = Sprite::createWithSpriteFrameName("ground.png");
    ground2->setName("ground2");

    ground1->setPosition(Point(visibleSize.width/2 + origin.x,  origin.y));
    this->addChild(ground1, -1);

    ground2->setPosition(Point(visibleSize.width*3/2 + origin.x,  origin.y));
    this->addChild(ground2, -1);


    scheduleUpdate();

    return true;


}

void BackgroundGameLayer::update(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();


    if(ground1->getPositionX()  <= -visibleSize.width*0.4 ) {
        ground1->setPositionX(visibleSize.width*3/2-origin.x);

    } else {
        ground1->setPositionX(ground1->getPositionX()-speed*dt);
    }

    if(ground2->getPositionX() <= -visibleSize.width*0.4 ) {
        ground2->setPositionX(visibleSize.width*3/2-origin.x);
    }else {
        ground2->setPositionX(ground2->getPositionX()-speed*dt);
    }

}
