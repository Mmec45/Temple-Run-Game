//
// Created by shree on 08-04-2021.
//

#include "MenuScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;


Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    this->initNodes();
    this->initControllers();


    auto userdefaults = cocos2d::UserDefault::getInstance();
    auto id= userdefaults->getIntegerForKey("audio");
    if(AudioEngine::getState(id) != AudioEngine::AudioState::PLAYING)
    {
        id= AudioEngine::play2d("music/music_ingame.mp3",true,0.5f);
        AudioEngine::resume(id);
    }
    userdefaults->setIntegerForKey("audio", id);

    scheduleUpdate();

    return true;
}

void MenuScene::initNodes()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    // Load background textures
    auto bg = Sprite::createWithSpriteFrameName("background.png");
    bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, -1);

    auto ground = Sprite::createWithSpriteFrameName("ground.png");
    ground->setPosition(Point(visibleSize.width/2 + origin.x, origin.y));
    this->addChild(ground, -1);

    auto logo = Sprite::createWithSpriteFrameName("logo.png");
    logo->setPosition(Point(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.7 + origin.y));
    this->addChild(logo, -1);


    //Adding backbutton to main menu
    auto touchListener = EventListenerKeyboard::create();
    touchListener->onKeyReleased = [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            Director::getInstance()->end();
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MenuScene::initControllers()
{
    Size screenSize = Director::getInstance()->getWinSize();

    ui::Button* startBtn = ui::Button::create("startButton.png","startButtonDn.png","startButtonDn.png",ui::AbstractCheckButton::TextureResType::PLIST);
    startBtn->setPosition(Point(screenSize.width * 0.5f, screenSize.height * 0.3f));
    startBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                this->clickPlayButton(sender);
                break;
            default:
                break;
        }
    });


    ui::Button* settingsBtn = ui::Button::create("muteBtn.png","muteBtnDn.png","muteBtnDn.png",ui::AbstractCheckButton::TextureResType::PLIST);
    settingsBtn->setPosition(Point(screenSize.width /10, screenSize.height /10));
    settingsBtn->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                AudioEngine::stopAll();
                break;
            default:
                break;
        }
    });


    ui::Button* offerBtn = ui::Button::create("offerwallBtn.png","offerwallBtnDn.png","offerwallBtnDn.png",ui::AbstractCheckButton::TextureResType::PLIST);
    offerBtn->setPosition(Point(screenSize.width *9/10, screenSize.height /10));

    this->addChild(startBtn, 1);
    this->addChild(settingsBtn, 1);
    this->addChild(offerBtn, 1);



}

void MenuScene::clickPlayButton(Ref* sender)
{
    Scene* newScene = TransitionMoveInR::create(0.2f, GameScene::createScene());
    Director::getInstance()->replaceScene(newScene);
}

void MenuScene::clickSettingsButton(Ref* sender)
{

}

void MenuScene::clickOfferwallButton(Ref* sender)
{

}

void MenuScene::update(float dt)
{

}