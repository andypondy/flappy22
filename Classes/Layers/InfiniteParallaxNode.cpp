#include "InfiniteParallaxNode.h"
#include "Definitions.h"
#include "GameScene.h"
#include "FallingBird.h"

USING_NS_CC;

class PointObject : public Ref
{
public:
    static PointObject * create(Vec2 ratio, Vec2 offset)
    {
        PointObject *ret = new (std::nothrow) PointObject();
        ret->initWithPoint(ratio, offset);
        ret->autorelease();
        return ret;
    }
    
    bool initWithPoint(Vec2 ratio, Vec2 offset)
    {
        _ratio = ratio;
        _offset = offset;
        _child = nullptr;
        return true;
    }
    
    inline const Vec2& getRatio() const { return _ratio; };
    inline void setRatio(const Vec2& ratio) { _ratio = ratio; };
    
    inline const Vec2& getOffset() const { return _offset; };
    inline void setOffset(const Vec2& offset) { _offset = offset; };
    
    inline Node* getChild() const { return _child; };
    inline void setChild(Node* child) { _child = child; };
    
private:
    Vec2 _ratio;
    Vec2 _offset;
    Node *_child; // weak ref
};

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
    actionMoveTo(dt);
    
    // remove offscreen children
    Vector<Node*>& children = this->getChildren();
    if (children.size() == 0) return;
    for(auto child : this->getChildren())
    {
        Point cpos = this->convertToWorldSpace(child->getPosition());
        if (cpos.y < AD_HEIGHT)
        {
            log("remove child from parent");
            child->removeFromParentAndCleanup(true);
        }
        else {
            // check for collision
            if (this->isCollision((Sprite*)this->hero, (Sprite*)child)) {
                // check if anti hero
                if (child->getPhysicsBody()->getCategoryBitmask() == ANTIHERO_COLLISION_BITMASK) {
                    // game over
                    this->endGame();
                }
                else {
                    // update score
                    child->removeFromParentAndCleanup(true);
                    this->gameScene->updateScore();
                }
            }
            // check if colliding ground
            else if(cpos.y < LAND_HEIGHT) {
                if (child->getPhysicsBody()->getCategoryBitmask() == OBSTACLE_COLLISION_BITMASK) {
                    // splat the bird
                    // game over
                    this->endGame();
                }
            }
        }
    }
}

void InfiniteParallaxNode::endGame()
{
    stopAllActions();
    unscheduleUpdate();
    for(auto child : this->getChildren()) {
        child->unscheduleUpdate();
    }
    this->gameScene->endGame();
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

bool InfiniteParallaxNode::isCollision(Sprite *a, Sprite *b)
{
    Size sself = b->boundingBox().size;
    Point pself = this->convertToWorldSpace(b->getPosition());;
    
    Size snest = a->boundingBox().size;
    Point pnest = a->getPosition();
    
    float maxx1 = pself.x + sself.width/2 - d;
    float minx1 = pself.x - sself.width/2 + d;
    float maxy1 = pself.y + sself.height/2 - d;
    float miny1 = pself.y - sself.height/2 + d;
    
    float maxx2 = pnest.x + snest.width/2 - d;
    float minx2 = pnest.x - snest.width/2 + d;
    float maxy2 = pnest.y + snest.height/2 - d;
    float miny2 = pnest.y - snest.height/2 + d;
    
    return !(maxx1 < minx2 ||
             maxx2 < minx1 ||
             maxy1 < miny2 ||
             maxy2 < miny1);
    
}

void InfiniteParallaxNode::addHero(Actor *hero)
{
    this->hero = hero;
}

void InfiniteParallaxNode::setGameScene(GameScene *s)
{
    this->gameScene = s;
}

/*
 The positions are updated at visit because:
 - using a timer is not guaranteed that it will called after all the positions were updated
 - overriding "draw" will only precise if the children have a z > 0
 */
void InfiniteParallaxNode::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    //    Vec2 pos = position_;
    //    Vec2    pos = [self convertToWorldSpace:Vec2::ZERO];
//    Vec2 pos = this->absolutePosition();
//    if( ! pos.equals(_lastPosition) )
//    {
//        for( int i=0; i < _parallaxArray->num; i++ )
//        {
//            PointObject *point = (PointObject*)_parallaxArray->arr[i];
//            float x = -pos.x + pos.x * point->getRatio().x + point->getOffset().x;
//            float y = -pos.y + pos.y * point->getRatio().y + point->getOffset().y;
//            point->getChild()->setPosition(x,y);
//        }
//        _lastPosition = pos;
//    }
    Node::visit(renderer, parentTransform, parentFlags);
}
