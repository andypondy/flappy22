#include "SplashScene.h"
#include "Definitions.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(schedule_selector(SplashScene::gotoMainMenuScene), DISPLAY_SPLASHSCENE_TIME);
    
    auto backgroundSprite = Sprite::create("Default.png");
    // position the sprite on the center of the screen
    backgroundSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(backgroundSprite, 0);
    
    return true;
}

void SplashScene::gotoMainMenuScene(float dt) {
    auto scene = MainMenu::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}