#include "Actor.h"
#include "Definitions.h"
#include "stealthSpriteFrameCache.h"

USING_NS_CC;

Actor::Actor()
{
    this->numFrames = 1;
    this->baseName = (char *)malloc(sizeof("nest_0"));
    
    initialSpeed = currentSpeed = 1;
    
    strcpy(this->baseName, "nest_0");
    baseInit();
}

void Actor::baseInit()
{
    // check first if the pipe is a sprite or single image
    char file[100] = {0};
    sprintf(file, "%s%d.png", this->baseName, 1);
    
    initWithSpriteFrameName(file);
    
    if (this->numFrames > 1)
        this->runAction(animateActor());
    
    score = 0; //
}

RepeatForever* Actor::animateActor()
{
    auto frames = new Vector<SpriteFrame *>();
    
    //3 frames for now .. add 2 more for better effect
    char file[100] = {0};
    for (int i = 0; i < this->numFrames; i++)
    {
        sprintf(file, "%s%d.png", this->baseName, i+1);
        SpriteFrame* frame = stealthSpriteFrameCache::getInstance()->getSpriteFrameByName(file);
        frames->pushBack(frame);
    }
    
    //create animation
    Animation* animation = Animation::createWithSpriteFrames(*frames, ANIMATION_TIME*4 / currentSpeed);
    Animate* animate = Animate::create(animation);
    
    RepeatForever* repeat = RepeatForever::create(animate);
    return repeat;
}

