//
// Created by shree on 09-04-2021.
//

#include "GameScene.h"
#include "MenuScene.h"
#include "ui/CocosGUI.h"
#include "CoinsLayer.h"
#include "GameOverScene.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;


Scene* GameScene::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

BackgroundGameLayer* GameScene::setupBackgroundLayer()
{
    this->setScrollSpeed(400);
    this->backgroundGameLayer = BackgroundGameLayer::create();
    return this->backgroundGameLayer;
}

CoinsLayer* GameScene::setupCoinsLayer() {

     this->coinsLayer = CoinsLayer::create();
    return this->coinsLayer;
}


void GameScene::setScrollSpeed(int speed){
    auto userdefaults = cocos2d::UserDefault::getInstance();
    userdefaults->setIntegerForKey("speed", speed);

}


bool GameScene::init() {
    if (!Layer::init())
    {
        return false;
    }

    gameOverFlag=false;
    auto userdefaults = cocos2d::UserDefault::getInstance();

    if(userdefaults->getIntegerForKey("life")<=0){
        this->setScores(3,500);
    }


    this->initNodes();
    this->initHuds();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    scheduleUpdate();


    //Adding backbutton to main menu
    auto touchListener = EventListenerKeyboard::create();
    touchListener->onKeyReleased = [](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            Scene* newScene = TransitionMoveInR::create(0.2f, MenuScene::createScene());
            Director::getInstance()->replaceScene(newScene);
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


    return true;
}

void GameScene::initNodes() {

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    heroRun= getRunAnimation();

    //Hero Run Action



    playerSprite = Sprite::create();
    playerSprite->setPosition(Point(visibleSize.width * 0.2f, visibleSize.height * 0.22f));
    playerSprite->runAction(heroRun);

    obstacleSprite= Sprite::createWithSpriteFrameName("obstacle.png");
    obstacleSprite->setPosition(Point(visibleSize.width, visibleSize.height * 0.1f));


    this->addChild(this->setupBackgroundLayer(), -1);
    this->addChild(this->setupCoinsLayer(), -1);
     this->addChild(playerSprite,-1);
    this->addChild(obstacleSprite,-1);

}

Action* GameScene::getRunAnimation() {
    auto heroAnimation = Animation::create();
    for(int index = 1; index < 7; index++ )
    {
        char name[100] = {0};
        sprintf(name, "boyrun_0%i.png", index);
        auto heroSpriteFrame =SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        heroAnimation->addSpriteFrame(heroSpriteFrame);
    }
    heroAnimation->setDelayPerUnit(0.3f / 3.0f);
    heroAnimation->setRestoreOriginalFrame(true);
    auto heroAnimate = Animate::create(heroAnimation);
    heroRun = RepeatForever::create(heroAnimate);
    return heroRun;
}


Action *GameScene::getJumpAnimation() {
    auto heroAnimation2 = Animation::create();
    for(int index = 1; index < 4; index++ )
    {
        char name[100] = {0};
        sprintf(name, "jump_0%i.png", index);
        auto heroSpriteFrame2 =SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        heroAnimation2->addSpriteFrame(heroSpriteFrame2);
    }
    heroAnimation2->setDelayPerUnit(0.8f / 3.0f);
    heroAnimation2->setRestoreOriginalFrame(true);
    auto heroAnimate2 = Animate::create(heroAnimation2);
    heroJump =  RepeatForever::create(heroAnimate2);

    return heroJump;
}


void GameScene::update(float dt) {
    //this->setScrollSpeed(400*dt);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if(obstacleSprite->getPositionX()<=0){
        obstacleSprite->setPositionX( visibleSize.width +obstacleSprite->getContentSize().width);
    } else {
        obstacleSprite->setPositionX(obstacleSprite->getPositionX()-400*dt);
    }

    auto rect = obstacleSprite->getBoundingBox();

    if(rect.intersectsRect(playerSprite->getBoundingBox()) && !gameOverFlag){
        this->decreaseLife();
        gameOverFlag=true;
        Scene* newScene = TransitionMoveInR::create(0.2f, GameOverScene::createScene());
        Director::getInstance()->replaceScene(newScene);
    }

    if(coinsLayer->checkCollection(playerSprite)){
        this->increaseCoins();

        AudioEngine::play2d("music/pickup.mp3",false,1.0f);
    //Play Audio
    // Increase the coins in score Window.
    }

}


bool GameScene::onTouchBegan(Touch *touch, Event *event)
{

    auto calb = CallFunc::create( [this] () {
        playerSprite->stopAllActions();
        playerSprite->runAction(getRunAnimation());
        jumping=false;
    });

    if(!jumping){
        playerSprite->stopAllActions();

        playerSprite->runAction(getJumpAnimation());

        jumping=true;
        auto action = JumpBy::create(1, Point(0, 0), 250, 1);
        auto seq = Sequence::create(action, calb, nullptr);
        playerSprite->runAction(seq);
    }


    return true;
}


void GameScene::initHuds() {

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    auto coinScorer = Sprite::createWithSpriteFrameName("coinScorer.png");
    coinScorer->setPosition(Point(visibleSize.width*0.9f + origin.x, visibleSize.height*0.9f + origin.y));
    this->addChild(coinScorer, -1);

    auto lifeScorer = Sprite::createWithSpriteFrameName("lifescorer.png");
    lifeScorer->setPosition(Point(visibleSize.width*0.1f + origin.x, visibleSize.height*0.9f + origin.y));
    this->addChild(lifeScorer, -1);


    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/MilkyNice.ttf";
    labelConfig.fontSize = 32;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.outlineSize = 0;
    labelConfig.customGlyphs = nullptr;
    labelConfig.distanceFieldEnabled = false;


    coins = Label::createWithTTF(labelConfig, ""+this->getCoins());
    coins->setPosition(Point(visibleSize.width*0.9f + origin.x+20, visibleSize.height*0.9f + origin.y));
    lifes = Label::createWithTTF(labelConfig, ""+this->getLifes());
    lifes->setPosition(Point(visibleSize.width*0.1f + origin.x+20, visibleSize.height*0.9f + origin.y));

    this->addChild(coins,-1);
    this->addChild(lifes,-1);

}

void GameScene::setScores(int life,int coins) {

    auto userdefaults = cocos2d::UserDefault::getInstance();
    userdefaults->setIntegerForKey("life", life);
    userdefaults->setIntegerForKey("coins", coins);
}

void GameScene::increaseCoins() {

    auto userdefaults = cocos2d::UserDefault::getInstance();
    auto coinscount=userdefaults->getIntegerForKey("coins");
    userdefaults->setIntegerForKey("coins", coinscount+1);

    coins->setString(this->getCoins());


}


void GameScene::decreaseLife() {

    auto userdefaults = cocos2d::UserDefault::getInstance();
    auto lifecount=userdefaults->getIntegerForKey("life");
    userdefaults->setIntegerForKey("life", lifecount-1);

    lifes->setString(this->getLifes());
}



std::basic_string<char, std::char_traits<char>, std::allocator<char>> GameScene::getCoins() {

    auto userdefaults = cocos2d::UserDefault::getInstance();

    return  Value(userdefaults->getIntegerForKey("coins")).asString();
}

std::basic_string<char, std::char_traits<char>, std::allocator<char>> GameScene::getLifes() {

    auto userdefaults = cocos2d::UserDefault::getInstance();
    return  Value(userdefaults->getIntegerForKey("life")).asString();
}