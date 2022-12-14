//
// Created by shree on 11-04-2021.
//

#ifndef PROJ_ANDROID_COINSLAYER_H
#define PROJ_ANDROID_COINSLAYER_H
#include "cocos2d.h"
USING_NS_CC;

class CoinsLayer : public Layer{

public:
    // Destructor
    ~CoinsLayer();
    // Create a layer
    static CoinsLayer* create();
    // Creates the scene of the component
    static Scene* scene();

    bool checkCollection(Sprite *pSprite);

private:
    // Initialize all resources from the layer
    virtual bool init();
    // standard Cocos2d layer method
    virtual void update(float dt);

    int speed=400;
    int random;

    Sprite* coins[];

};


#endif //PROJ_ANDROID_COINSLAYER_H
