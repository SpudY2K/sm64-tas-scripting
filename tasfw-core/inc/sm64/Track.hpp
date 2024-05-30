#pragma once

#ifndef TRACK_H
#define TRACK_H
/* oAction */
#define PLATFORM_ON_TRACK_ACT_INIT             0
#define PLATFORM_ON_TRACK_ACT_WAIT_FOR_MARIO   1
#define PLATFORM_ON_TRACK_ACT_MOVE_ALONG_TRACK 2
#define PLATFORM_ON_TRACK_ACT_PAUSE_BRIEFLY    3
#define PLATFORM_ON_TRACK_ACT_FALL             4

/* oBehParams >> 16 */
#define PLATFORM_ON_TRACK_BP_MASK_PATH       0x000F
#define PLATFORM_ON_TRACK_BP_MASK_TYPE       0x0070
#define PLATFORM_ON_TRACK_BP_RETURN_TO_START (1 <<  8)
#define PLATFORM_ON_TRACK_BP_DONT_DISAPPEAR  (1 <<  9)
#define PLATFORM_ON_TRACK_BP_DONT_TURN_YAW   (1 << 10)
#define PLATFORM_ON_TRACK_BP_DONT_TURN_ROLL  (1 << 11)

#define PLATFORM_ON_TRACK_TYPE_CARPET    0
#define PLATFORM_ON_TRACK_TYPE_SKI_LIFT  1
#define PLATFORM_ON_TRACK_TYPE_CHECKERED 2
#define PLATFORM_ON_TRACK_TYPE_GRATE     3

#define WAYPOINT_FLAGS_END -1
#define WAYPOINT_FLAGS_INITIALIZED 0x8000
#define WAYPOINT_MASK_00FF 0x00FF
#define WAYPOINT_FLAGS_PLATFORM_ON_TRACK_PAUSE 3

#define TRAJECTORY_POS(trajId, x, y, z) \
    trajId, x, y, z

#define TRAJECTORY_END() \
    -1
#endif

void bhv_platform_on_track_update(struct Object* o, struct MarioState* m);