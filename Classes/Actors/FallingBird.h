#ifndef __ACTOR_FALLINGBIRD__
#define __ACTOR_FALLINGBIRD__

#include "cocos2d.h"
#include "Actor.h"

using namespace cocos2d;

class FallingBird : public Actor
{
public:
    FallingBird(bool antiHero, float speed);

    void addCollider(Actor *hero);
    void splat();
    
private:
    bool antihero;
    virtual void update(float delta); //collision checking and scoring
    bool isCollision(Sprite *a); //collision or not
    Point getWorldPosition();
    
    Actor* nest;

    const float d = 20.0; //might have to fine tune this delta for precision contact
    
};


#endif /* defined(__ACTOR_FALLINGBIRD__) */
