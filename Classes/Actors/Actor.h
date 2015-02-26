#ifndef __ACTOR_ACTOR__
#define __ACTOR_ACTOR__

#include "cocos2d.h"
//#include "GameScene.h"

using namespace cocos2d;

class Actor : public Sprite
{
public:
    Actor();
    
//    void setGameScene(GameScene *s);

    
private:
    RepeatForever* animateActor();
    
protected:
    void baseInit();

//    GameScene *gameScene;
    
    int score;
    int numFrames;
    char *baseName;
    
    float initialSpeed=1, currentSpeed=1;
};


#endif /* defined(__ACTOR_ACTOR__) */
