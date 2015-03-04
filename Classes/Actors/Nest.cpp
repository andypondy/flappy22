#include "Nest.h"
#include "Definitions.h"
#include "stealthSpriteFrameCache.h"

USING_NS_CC;

Nest::Nest()
{
    this->numFrames = 1;
    this->baseName = (char *)malloc(sizeof("nest_0"));
    strcpy(this->baseName, "nest_0");
    Actor::baseInit();
    
    auto flappyBody = PhysicsBody::createCircle( this->getContentSize( ).width / 2 );
    flappyBody->setCategoryBitmask(ACTOR_COLLISION_BITMASK);
    flappyBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK | ANTIHERO_COLLISION_BITMASK);
    flappyBody->setContactTestBitmask( OBSTACLE_COLLISION_BITMASK | ANTIHERO_COLLISION_BITMASK);
    flappyBody->setGravityEnable(false);
    
    this->setPhysicsBody( flappyBody );
}

void Nest::explode()
{
    
}