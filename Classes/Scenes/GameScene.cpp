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
    
//    s = Director::getInstance()->getWinSize();
    this->visibleSize    = Director::getInstance()->getVisibleSize();
    this->origin         = Director::getInstance()->getVisibleOrigin();
    
    resetGame();

    auto contactListener = EventListenerPhysicsContact::create( );
    contactListener->onContactBegin = CC_CALLBACK_1( GameScene::onContactBegin, this );
    Director::getInstance( )->getEventDispatcher( )->addEventListenerWithSceneGraphPriority( contactListener, this );
    
    return true;
}

void GameScene::resetGame()
{
    this->removeAllChildrenWithCleanup(true);
    unscheduleUpdate();
    
    isFirstTouchComplete = false;
    gameSpeed = 1;
    score = 0;
    
    addBackground();
    addEdges();
    addHero();
    addParallaxLayer();
    updateScoreUI();
}

void GameScene::startGame() {
    scheduleUpdate();
}

void GameScene::endGame()
{
    stopAllActions();
    unscheduleUpdate();
}

void GameScene::addBackground()
{
    Sprite* bg = Sprite::createWithSpriteFrameName("background.png");
    bg->Node::setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(bg);
}

void GameScene::addEdges()
{    
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    edgeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
    edgeBody->setContactTestBitmask( OBSTACLE_COLLISION_BITMASK );
    edgeBody->setCategoryBitmask(LAND_COLLISION_BITMASK);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
    
    edgeNode->setPhysicsBody( edgeBody );
    
    this->addChild( edgeNode );
}

void GameScene::addHero()
{
    nest = new Nest();
    nest->setZOrder(1000); //front most
    nest->Node::setPosition(visibleSize.width/2, visibleSize.height/3); // position on screen
    
    this->addChild(nest);
}

void GameScene::addParallaxLayer()
{
    parallaxLayer = InfiniteParallaxNode::create();
    parallaxLayer->setSize(visibleSize);
    parallaxLayer->addHero(nest);
    parallaxLayer->setGameScene(this);
    this->addChild(parallaxLayer);
}

void GameScene::addOpponent()
{
    
    FallingBird* opponent = nullptr;
    if (this->score == 5 || (this->score > 0 && (this->score) % 22 == 0)) {
        opponent = new FallingBird(true, gameSpeed);
    }
    else {
        opponent = new FallingBird(false, gameSpeed);
    }
    opponent->addCollider(nest);

    int r = rand() % (int)(visibleSize.width/opponent->boundingBox().size.width*2);

    float dx = r * opponent->boundingBox().size.width/2 + opponent->boundingBox().size.width/2;
    if ( dx > visibleSize.width) dx = visibleSize.width - opponent->boundingBox().size.width/2;
    
    Point pos = Vec2(dx, visibleSize.height + opponent->boundingBox().size.height/2);
    //
//    opponent->setPosition(parallaxLayer->convertToNodeSpace(pos));
    //
    opponent->setZOrder(2);
    
    Point bgSpeed = Vec2(0.0, 1.0);
    parallaxLayer->addChild(opponent, 0, bgSpeed, parallaxLayer->convertToNodeSpace(pos));
    
}

void GameScene::levelUp()
{
    gameSpeed += 0.01;
    log("level up - new speed %f", gameSpeed);
}

void GameScene::update(float delta)
{
    nextOpponentInterval += delta;
    if (nextOpponentInterval >= TIME_TO_ADD_NEXT_OPPONENT/gameSpeed)
    {
        nextOpponentInterval = 0;
        this->addOpponent();
    }
}

void GameScene::updateScore()
{
    score++;
    log("score %d", score);
    if (score > 22)
        levelUp();
}

void GameScene::updateScoreUI()
{

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
        if ((loc.x + nest->boundingBox().size.width/2) > visibleSize.width)
            loc.x = visibleSize.width - nest->boundingBox().size.width/2;

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
        if ((loc.x + nest->boundingBox().size.width/2) > visibleSize.width)
            loc.x = visibleSize.width - nest->boundingBox().size.width/2;
    
    loc.y = nest->getPosition().y;
    nest->setPosition(loc);
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA( )->getBody();
    PhysicsBody *b = contact.getShapeB( )->getBody();
    log("bang");
    
    if ( ( ACTOR_COLLISION_BITMASK == a->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( ACTOR_COLLISION_BITMASK == b->getCollisionBitmask( ) && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() ) )
    {
//        auto scene = GameOverScene::createScene( );
//        
//        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    }
    
    return true;
}

