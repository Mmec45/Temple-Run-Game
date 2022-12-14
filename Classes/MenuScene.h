//
// Created by shree on 08-04-2021.
//

#ifndef PROJ_ANDROID_MENUSCENE_H
#define PROJ_ANDROID_MENUSCENE_H


#include "cocos2d.h"

USING_NS_CC;

class MenuScene : public Layer {
public:
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

private:
    // initialize sprites and other nodes for the layer
    void initNodes();
    // initialize controllers for the layer
    void initControllers();
    // Click play button callback
    void clickPlayButton(Ref* sender);
    // Click settings button callback
    void clickSettingsButton(Ref* sender);
    // Click Offerwall button callback
    void clickOfferwallButton(Ref* sender);

    // standard Cocos2d layer method
    virtual void update(float dt);

};


#endif //PROJ_ANDROID_MENUSCENE_H
