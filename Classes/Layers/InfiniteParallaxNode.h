#ifndef __parallax_node_H__
#define __parallax_node_H__

#include "cocos2d.h"

USING_NS_CC;

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

private:
    void onEnter();
    void actionMove();
    void actionMoveTo(float dt);
    
protected:
    float w,h;
    float initialSpeed, currentSpeed;

};


#endif // __parallax_node_H__
