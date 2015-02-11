#include "Nest.h"
#include "Definitions.h"
#include "stealthSpriteFrameCache.h"

USING_NS_CC;

Nest::Nest()
{
    this->numFrames = 1;
    this->baseName = (char *)malloc(sizeof("nest_0"));
    strcpy(this->baseName, "nest_0");
    Actor::baseInit();
}