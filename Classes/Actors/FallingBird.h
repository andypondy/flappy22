#ifndef __ACTOR_FALLINGBIRD__
#define __ACTOR_FALLINGBIRD__

#include <cocos2d.h>
#include "Actor.h"

using namespace cocos2d;

class FallingBird : public Actor
{
public:
    FallingBird(bool antiHero, float speed);

private:
    bool isReverse;
//    virtual void update(float delta); //collision checking and scoring
//    bool isCollision(); //collision or not
//    Point getWorldPosition();
//    
//    Nest* nest;

};


#endif /* defined(__ACTOR_FALLINGBIRD__) */
