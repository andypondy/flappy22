#ifndef __FlappyBird__stealthSpriteFrameCache__
#define __FlappyBird__stealthSpriteFrameCache__

USING_NS_CC;

#include <iostream>
#include "cocos2d.h"
#include "2d/CCSpriteFrameCache.h"

class stealthSpriteFrameCache : public cocos2d::SpriteFrameCache
{
    public:
    bool objectForKey(const char *pszSpriteFrameName);
};
#endif /* defined(__FlappyBird__stealthSpriteFrameCache__) */
