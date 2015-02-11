#include "FallingBird.h"
#include "Definitions.h"
#include "stealthSpriteFrameCache.h"

USING_NS_CC;

FallingBird::FallingBird(bool antiHero, float speed)
{
    this->numFrames = 2;
    this->baseName = (char *)malloc(sizeof("flappy_0"));
    strcpy(this->baseName, "flappy_0");
    
    this->isReverse = antiHero;
    this->currentSpeed = speed;
    
    Actor::baseInit();
    setScale(0.8, 0.8);
}
/*
void FallingBird::update(float delta)
{
    if (bird->status == isDead) return;
    
    if (getScore)
    {
        if (getWorldPosition().x <= bird->getPosition().x)
        {
            getScore = false; // count once for every time you pass the pipes
            //            bird->updateScore();
        }
    }
    
    if (isCollision())
    {
        bird->hitMe();
        parent->removeFromParentAndCleanup(true);
    }

}

bool FallingBird::isCollision()
{
    CCSize spipe = parent->boundingBox().size;
    CCPoint ppipe = getWorldPosition();
    
    CCSize sbird = bird->boundingBox().size;
    CCPoint pbird = bird->getPosition();
    
    float d = 7.0; //might have to fine tune this delta for precision contact
    
    float maxx1 = ppipe.x + spipe.width/2 - d;
    float minx1 = ppipe.x - spipe.width/2 + d;
    float maxy1 = ppipe.y + spipe.height/2 - d;
    float miny1 = ppipe.y - spipe.height/2 + d;
    
    float maxx2 = pbird.x + sbird.width/2 - d;
    float minx2 = pbird.x - sbird.width/2 + d;
    float maxy2 = pbird.y + sbird.height/2 - d;
    float miny2 = pbird.y - sbird.height/2 + d;
    
    return !(maxx1 < minx2 ||
             maxx2 < minx1 ||
             maxy1 < miny2 ||
             maxy2 < miny1);
    
}

CCPoint FallingBird::getWorldPosition()
{
    return ((CCParallaxNode*)parent->getParent())->convertToWorldSpace(parent->getPosition());
}
*/