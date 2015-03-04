#include "FallingBird.h"
#include "Definitions.h"
#include "stealthSpriteFrameCache.h"
#include "Nest.h"

USING_NS_CC;

FallingBird::FallingBird(bool antiHero, float speed)
{
    this->numFrames = 2;
    if (antiHero) {
        this->baseName = (char *)malloc(sizeof("crow_0"));
        strcpy(this->baseName, "crow_0");
    }
    else {
        this->baseName = (char *)malloc(sizeof("flappy_0"));
        strcpy(this->baseName, "flappy_0");
    }
    
    this->antihero = antiHero;
    this->currentSpeed = speed;
    
    Actor::baseInit();
    setScale(0.75, 0.75);
    
    auto flappyBody = PhysicsBody::createCircle( this->getContentSize().width / 2 );
    
    flappyBody->setCollisionBitmask( ACTOR_COLLISION_BITMASK );
    flappyBody->setContactTestBitmask( ACTOR_COLLISION_BITMASK );
    if (antiHero) {
        flappyBody->setCategoryBitmask( ANTIHERO_COLLISION_BITMASK);
    }
    else {
        flappyBody->setCategoryBitmask( OBSTACLE_COLLISION_BITMASK);
    }
    flappyBody->setGravityEnable(false);
    
    this->setPhysicsBody( flappyBody );
    
    this->scheduleUpdate();
}

void FallingBird::addCollider(Actor *hero) {
    this->nest = hero;
}

void FallingBird::update(float delta)
{
    Point pself     = getWorldPosition();
    Vec2 size       = Director::getInstance()->getVisibleSize();
    float yPos      = (size.y - pself.y) / 150;
    if (pself.y < size.y*1/3) {
        yPos = (size.y*2/3) / 175;
    }
    float exp       = exp2f(yPos);
    
    this->setPositionY(this->getPositionY()-exp);
}

bool FallingBird::isCollision(Sprite *a)
{
    Size sself = this->boundingBox().size;
    Point pself = getWorldPosition();
    
    Size snest = a->boundingBox().size;
    Point pnest = a->getPosition();
        
    float maxx1 = pself.x + sself.width/2 - d;
    float minx1 = pself.x - sself.width/2 + d;
    float maxy1 = pself.y + sself.height/2 - d;
    float miny1 = pself.y - sself.height/2 + d;
    
    float maxx2 = pnest.x + snest.width/2 - d;
    float minx2 = pnest.x - snest.width/2 + d;
    float maxy2 = pnest.y + snest.height/2 - d;
    float miny2 = pnest.y - snest.height/2 + d;
    
    return !(maxx1 < minx2 ||
             maxx2 < minx1 ||
             maxy1 < miny2 ||
             maxy2 < miny1);
    
}

Point FallingBird::getWorldPosition()
{
    return ((ParallaxNode*)getParent())->convertToWorldSpace(getPosition());
}

void FallingBird::splat()
{
    // if anti hero then explode nest too
    if (this->antihero) {
        ((Nest*)this->nest)->explode();
    }
    else {
    }
}

