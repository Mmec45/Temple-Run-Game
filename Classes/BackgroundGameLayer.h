//
// Created by shree on 11-04-2021.
//

#ifndef PROJ_ANDROID_BACKGROUNDGAMELAYER_H
#define PROJ_ANDROID_BACKGROUNDGAMELAYER_H

#include "cocos2d.h"

USING_NS_CC;


class BackgroundGameLayer : public Layer{

public:
    // Destructor
    ~BackgroundGameLayer();
    // Create a layer
    static BackgroundGameLayer* create();
    // Creates the scene of the component
    static Scene* scene();

    void setSpeed(int speed);

private:
    // Initialize all resources from the layer
    virtual bool init();
    // standard Cocos2d layer method
    virtual void update(float dt);

    Sprite* ground1;
    Sprite* ground2;

    int speed=400;
};


#endif //PROJ_ANDROID_BACKGROUNDGAMELAYER_H
