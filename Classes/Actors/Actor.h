#ifndef __ACTOR_ACTOR__
#define __ACTOR_ACTOR__

#include <cocos2d.h>

using namespace cocos2d;

class Actor : public Sprite
{
public:
    Actor();
    
//
//    virtual void tapMe(); //
//    virtual void hitMe(); //
//    virtual void updateScore(); //
    
private:
    RepeatForever* animateActor();
    
protected:
    void baseInit();

    int score;
    int numFrames;
    char *baseName;
    
    float initialSpeed=1, currentSpeed=1;
};


#endif /* defined(__ACTOR_ACTOR__) */
