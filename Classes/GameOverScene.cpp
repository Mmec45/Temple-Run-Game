//
// Created by shree on 11-04-2021.
//

#include "GameOverScene.h"
#include "ui/CocosGUI.h"
#include "GameScene.h"
#include "MenuScene.h"

USING_NS_CC;


Scene *GameOverScene ::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameOverScene::init() {
    if (!Layer::init()) {
        return false;
    }

    this->initNodes();
    this->initControllers();

    scheduleUpdate();

    return true;

}

void GameOverScene::initNodes()
{

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::createWithSpriteFrameName("background.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);

    auto ground = Sprite::createWithSpriteFrameName("ground.png");
    ground->setPosition(Point(visibleSize.width/2 + origin.x, origin.y));
    this->addChild(ground, -1);

    auto gameover = Sprite::createWithSpriteFrameName("gameover.png");
    gameover->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.7 + origin.y));
    this->addChild(gameover, -1);

    auto boyfallen = Sprite::createWithSpriteFrameName("boyfallen.png");
    boyfallen->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.25 + origin.y));
    this->addChild(boyfallen, -1);
}

void GameOverScene::initControllers() {

    Size screenSize = Director::getInstance()->getWinSize();
    ui::Button* restartBtn = ui::Button::create("restartBtn.png","restartBtnDn.png","restartBtnDn.png",ui::AbstractCheckButton::TextureResType::PLIST);
    restartBtn->setPosition(Point(screenSize.width * 0.2f, screenSize.height * 0.5f));
    restartBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->clickRestartButton(sender);
                break;
            default:
                break;
        }
    });


    ui::Button* exitBtn = ui::Button::create("exitBtn.png","exitBtnDn.png","exitBtnDn.png",ui::AbstractCheckButton::TextureResType::PLIST);
    exitBtn->setPosition(Point(screenSize.width * 0.8f, screenSize.height * 0.5f));
    exitBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->clickExitButton(sender);
                break;
            default:
                break;
        }
    });

    this->addChild(restartBtn,-1);
    this->addChild(exitBtn,-1);

}

void GameOverScene::clickRestartButton(Ref* sender){

    Scene* newScene = TransitionMoveInR::create(0.2f, GameScene::createScene());
    Director::getInstance()->replaceScene(newScene);
}
void GameOverScene::clickExitButton(Ref *ptr) {

    Scene* newScene = TransitionMoveInR::create(0.2f, MenuScene::createScene());
    Director::getInstance()->replaceScene(newScene);
}

void GameOverScene::update(float dt) {

}