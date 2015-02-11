#include "stealthSpriteFrameCache.h"
#include "2d/CCSpriteFrame.h"
#include "2d/CCSprite.h"

USING_NS_CC;

bool stealthSpriteFrameCache::objectForKey(const char *pszSpriteFrameName)
{
    Map<std::string, SpriteFrame*>::iterator frame = _spriteFrames.find(pszSpriteFrameName);
    if (frame == _spriteFrames.end()) {
        return false;
    }

    return true;
}