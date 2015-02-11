#include "GameOver.h"
#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

void GameOver::gotoMainMenuScene(cocos2d::Ref *sender) {
    auto scene = GameScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}
void GameOver::gotoGameScene(cocos2d::Ref *sender) {
    auto scene = GameScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}
