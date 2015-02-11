#include "MainMenu.h"
#include "Definitions.h"
#include "GameScene.h"
#include "stealthSpriteFrameCache.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //load resource
    stealthSpriteFrameCache::getInstance()->addSpriteFramesWithFile("falldown.plist");
    
    //load file sound
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SoundTap);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SoundHit);
    //    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(SoundPoint);
    

    
    auto backgroundSprite = Sprite::create("Background.png");
    // position the sprite on the center of the screen
    backgroundSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(backgroundSprite, 0);
    
    auto playButton = MenuItemImage::create("play.png", "playClicked.png", CC_CALLBACK_1(MainMenu::gotoGameScene, this));
    playButton->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    auto menu = Menu::create(playButton, NULL);
    menu->setPosition(Point::ZERO);
    
    this->addChild(menu, 0);

    return true;
}

void MainMenu::gotoGameScene(cocos2d::Ref *sender) {
    auto scene = GameScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}