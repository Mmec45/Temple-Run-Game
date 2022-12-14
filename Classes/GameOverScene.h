//
// Created by shree on 11-04-2021.
//

#ifndef PROJ_ANDROID_GAMEOVERSCENE_H
#define PROJ_ANDROID_GAMEOVERSCENE_H

#include "cocos2d.h"

USING_NS_CC;

class GameOverScene: public Layer {
public:
// implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

// there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene *createScene();

// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

private:

    void initNodes();

    void initControllers();
    // standard Cocos2d layer method
    virtual void update(float dt);

    void clickRestartButton(Ref *ptr);

    void clickExitButton(Ref *ptr);

};


#endif //PROJ_ANDROID_GAMEOVERSCENE_H
