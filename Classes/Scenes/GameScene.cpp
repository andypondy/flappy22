#include "GameScene.h"
#include "Actor.h"
#include "FallingBird.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    s = Director::getInstance()->getWinSize();
    
    resetGame();

    return true;
}

void GameScene::resetGame()
{
    this->removeAllChildrenWithCleanup(true);
    unscheduleUpdate();
    
    GameOver = false;
    isFirstTouchComplete = false;
    gameSpeed = 1;
    
    addBackground();
    addHero();
    addParallaxLayer();
    
}

void GameScene::startGame() {
    scheduleUpdate();
}

void GameScene::addBackground()
{
    Sprite* bg = Sprite::createWithSpriteFrameName("background.png");
    bg->Node::setPosition(s.width/2, s.height/2);
    this->addChild(bg);
}

void GameScene::addHero()
{
    nest = new Nest();
    nest->setZOrder(1000); //front most
    nest->CCNode::setPosition(s.width/2, s.height/3); // position on screen
    
    this->addChild(nest);
}

void GameScene::addParallaxLayer()
{
    parallaxLayer = InfiniteParallaxNode::create();
    parallaxLayer->setSize(s);
    this->addChild(parallaxLayer);
}

void GameScene::addOpponent()
{
    
    FallingBird* opponent = new FallingBird(false, gameSpeed);

    int r = rand() % (int)(s.width/opponent->boundingBox().size.width*2);

    float dx = r * opponent->boundingBox().size.width/2 + opponent->boundingBox().size.width/2;
    if ( dx > s.width) dx = s.width - opponent->boundingBox().size.width/2;
    
    Point pos = Vec2(dx, s.height + opponent->boundingBox().size.height/2);
    //
//    opponent->setPosition(parallaxLayer->convertToNodeSpace(pos));
    //
    opponent->setZOrder(2);
    
//    opponent->addComponent(new Collision(bird, true)); //score for only when 1 of the pipe is crossed
    Point bgSpeed = Vec2(0.0, 1.0);
    parallaxLayer->addChild(opponent, 0, bgSpeed, parallaxLayer->convertToNodeSpace(pos));

//    log("--------- after adding to parallax");
//    point(parallaxLayer->getPosition());
//    point(opponent->getPosition());
    
}

void GameScene::levelUp()
{
    gameSpeed += 0.01;
}

void GameScene::update(float delta)
{
    nextOpponentInterval += delta;
    if (nextOpponentInterval >= ktimeToAddOpponent/gameSpeed && !GameOver)
    {
        nextOpponentInterval = 0;
        this->addOpponent();
        levelUp();
    }
}

//-----------------------------
void GameScene::onEnter()
{
    Layer::onEnter();
    
    // Register Touch Event
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void GameScene::onExit()
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    
    dispatcher->removeEventListener(listener);
    
    Layer::onExit();
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (!isFirstTouchComplete) {
        startGame();
    }

    Point loc = touch->getLocation();
    
    if ((loc.x - nest->boundingBox().size.width/2) < 0)
        loc.x = nest->boundingBox().size.width/2;
    else
        if ((loc.x + nest->boundingBox().size.width/2) > s.width)
            loc.x = s.width - nest->boundingBox().size.width/2;

    loc.y = nest->getPosition().y;
    
    auto moveTo = MoveTo::create(0.2, loc);
    
    nest->runAction(moveTo);
    
    return true;
}
void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
//    log("anand - onTouchesMoved ");
    Point loc = touch->getLocation();
    
    if ((loc.x - nest->boundingBox().size.width/2) < 0)
        loc.x = nest->boundingBox().size.width/2;
    else
        if ((loc.x + nest->boundingBox().size.width/2) > s.width)
            loc.x = s.width - nest->boundingBox().size.width/2;
    
    loc.y = nest->getPosition().y;
    nest->setPosition(loc);
}

