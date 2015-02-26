#include "InfiniteParallaxNode.h"
#include "Definitions.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool InfiniteParallaxNode::init()
{
    if ( !ParallaxNode::init() )
    {
        return false;
    }

    return true;
}

void InfiniteParallaxNode::onEnter()
{
    ParallaxNode::onEnter();
//    actionMove();
    scheduleUpdate();
}

void InfiniteParallaxNode::update(float dt)
{
    Point p = this->getPosition();
    actionMoveTo(dt);
//    point(p);
    
    // remove offscreen children
    Vector<Node*>& children = ((ParallaxNode*)this)->getChildren();
    if (children.size() == 0) return;
    for(auto child : this->getChildren())
    {
        Point cpos = this->convertToWorldSpace(child->getPosition());
        if (cpos.x < -child->boundingBox().size.width)
        {
            log("remove child from parent");
            child->removeFromParentAndCleanup(true);
        }
    }
}

void InfiniteParallaxNode::actionMove()
{
    MoveBy* move = MoveBy::create(kMoveDownDura, Vec2(0, -currentSpeed));
    this->runAction(CCRepeatForever::create(move));
}

void InfiniteParallaxNode::actionMoveTo(float dt)
{
    Vec2 moveToPosition = Vec2(this->getPosition().x, this->getPosition().y - this->h * currentSpeed * dt*5);
    MoveTo* move = MoveTo::create(kMoveDownDura, moveToPosition);
    this->runAction(move);
}

void InfiniteParallaxNode::setSize(Size size)
{
    Size winSize = Director::getInstance()->getWinSize();
    
    if(winSize.width == 1024) {
        this->w = size.width / (kLandParts*2);
        this->h = size.height / (kLandParts*2);
    }
    else if(winSize.width > 1024) {
        this->w = size.width / (kLandParts*4);
        this->h = size.height / (kLandParts*4);
    }
    else {
        this->w = size.width / kLandParts;
        this->h = size.height / kLandParts;
    }
    
    initialSpeed = currentSpeed = 1;
}

void InfiniteParallaxNode::setSpeed(float speed) {
    currentSpeed = speed;
}