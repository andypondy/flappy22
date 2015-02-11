#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#define DISPLAY_SPLASHSCENE_TIME 2
#define TRANSITION_TIME 0.5

#define SoundTap "sfx_wing.mp3"
#define SoundHit "sfx_hit.mp3"
#define SoundPoint "sfx_point.mp3"


#define kLandParts 15 // land is 15 part sprite, move 1/15 every update
#define kMoveDownDura 0.3   //move land to left duration

#define ANIMATION_TIME 0.05 //bird flap speed

#define kJumpHeight 50 // duh
#define kJumpDura 0.4 // these two const define the speed and height of each jump

#define kLandHeight 110 //


#define ktimeToAddOpponent 1 // time distance between each pipe
#define kHoleBetweenPipe 80

#define point(p) \
{ \
    log("[%f, %f]", p.x, p.y); \
}

#endif // __DEFINITIONS_H__
