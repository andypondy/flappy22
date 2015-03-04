#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#define DISPLAY_SPLASHSCENE_TIME 0.5
#define TRANSITION_TIME 0.5

#define ACTOR_COLLISION_BITMASK 0x000001
#define OBSTACLE_COLLISION_BITMASK 0x000002
#define LAND_COLLISION_BITMASK 0x000003
#define ANTIHERO_COLLISION_BITMASK 0x000004

#define COLLISION_BITMASK (ACTOR_COLLISION_BITMASK | OBSTACLE_COLLISION_BITMASK | LAND_COLLISION_BITMASK | ANTIHERO_COLLISION_BITMASK)

#define LAND_HEIGHT 140
#define AD_HEIGHT 50

#define SoundTap "sfx_wing.mp3"
#define SoundHit "sfx_hit.mp3"
#define SoundPoint "sfx_point.mp3"


#define kLandParts 15 // land is 15 part sprite, move 1/15 every update
#define kMoveDownDura 0.3   //move land to left duration

#define ANIMATION_TIME 0.05 //bird flap speed


#define TIME_TO_ADD_NEXT_OPPONENT 0.7 // time distance between each pipe

#define point(p) \
{ \
    log("[%f, %f]", p.x, p.y); \
}

#endif // __DEFINITIONS_H__
