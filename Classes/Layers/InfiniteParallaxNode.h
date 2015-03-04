#ifndef __parallax_node_H__
#define __parallax_node_H__

#include "cocos2d.h"

USING_NS_CC;
class GameScene;
class Actor;

class InfiniteParallaxNode : public ParallaxNode
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(InfiniteParallaxNode);
    
    void update(float dt);
    void setSize(Size size);
    void setSpeed(float speed);
    bool isCollision(Sprite *a, Sprite *b); //collision or not
    void addHero(Actor *hero);
    void setGameScene(GameScene *s);

private:
    void onEnter();
    void actionMoveTo(float dt);
    void endGame();
    
    const float d = 20.0; //might have to fine tune this delta for precision contact
    Actor* hero;
    GameScene *gameScene;

protected:
    float w,h;
    float initialSpeed, currentSpeed;
    void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags);
    
};


#endif // __parallax_node_H__
