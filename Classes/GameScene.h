//
// Created by shree on 09-04-2021.
//

#ifndef PROJ_ANDROID_GAMESCENE_H
#define PROJ_ANDROID_GAMESCENE_H
#include "cocos2d.h"
#include "BackgroundGameLayer.h"
#include "CoinsLayer.h"

USING_NS_CC;


class GameScene : public Layer{
public:
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    CC_SYNTHESIZE(bool, gameOverFlag, GameOverFlag);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

private:
    // initialize sprites and other nodes for the layer
    void initNodes();

    void initHuds();


    // standard Cocos2d layer method
    virtual void update(float dt);
    // standard Cocos2d layer method
    virtual bool onTouchBegan(Touch *touch, Event *event);


    BackgroundGameLayer* setupBackgroundLayer();

    CoinsLayer* setupCoinsLayer();

    Sprite* playerSprite;
    Sprite* obstacleSprite;


    BackgroundGameLayer* backgroundGameLayer;

    CoinsLayer* coinsLayer;

    Action* heroRun;
    Action* heroJump;

    Action* getRunAnimation();

    Action* getJumpAnimation();

    bool  jumping;

    void setScrollSpeed(int speed);

    std::basic_string<char, std::char_traits<char>, std::allocator<char>> getLifes();

    std::basic_string<char, std::char_traits<char>, std::allocator<char>> getCoins();

    void increaseCoins();

    void decreaseLife();

    void setScores(int life,int coins);

    Label* coins;

    Label* lifes;


};


#endif //PROJ_ANDROID_GAMESCENE_H
