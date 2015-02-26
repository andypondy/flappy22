#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Nest.h"
#include "InfiniteParallaxNode.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    void updateScore();
    void gameOver();
    
    void playSound(std::string name);
    
private:
    virtual void onEnter();
    virtual void onExit();
    void update(float delta);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    
    Size visibleSize;
    Vec2 origin;
    
    Nest *nest;
    InfiniteParallaxNode *parallaxLayer;
    bool isFirstTouchComplete;
    float nextOpponentInterval;
    float gameSpeed = 1;

    void resetGame();
    void startGame();
    void addBackground();
    void addEdges();
    void addHero();
    void addParallaxLayer();
    void addOpponent();
    void levelUp();

    int score;
protected:
    
};

#endif // __GAME_SCENE_H__
