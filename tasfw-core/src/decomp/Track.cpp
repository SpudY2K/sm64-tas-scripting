#include <sm64/ObjectFields.hpp>
#include <sm64/Types.hpp>
#include <sm64/UltraTypes.hpp>
#include <sm64/Trig.hpp>
#include <sm64/Track.hpp>
#include <cmath>

/**
 * Behavior for bhvPlatformOnTrack and bhvTrackBall.
 * The platform spawns up to 5 track balls at a time, which then despawn
 * themselves as the platform moves past them.
 */

/**
 * Paths for the different instances of these platforms.
 */
const Trajectory bitfs_seg7_trajectory_070159AC[] = {
    TRAJECTORY_POS(0, /*pos*/ -5744, -3072,     0),
    TRAJECTORY_POS(1, /*pos*/ -5444, -3072,     0),
    TRAJECTORY_POS(2, /*pos*/ -5144, -3072,     0),
    TRAJECTORY_POS(3, /*pos*/ -4954, -3122,     0),
    TRAJECTORY_POS(4, /*pos*/ -4754, -3172,     0),
    TRAJECTORY_POS(5, /*pos*/ -4300, -3172,     0),
    TRAJECTORY_POS(6, /*pos*/ -3850, -3172,     0),
    TRAJECTORY_POS(7, /*pos*/ -3650, -3122,     0),
    TRAJECTORY_POS(8, /*pos*/ -3460, -3072,     0),
    TRAJECTORY_POS(9, /*pos*/ -3160, -3072,     0),
    TRAJECTORY_POS(10, /*pos*/ -3000, -3150,     0),
    TRAJECTORY_POS(11, /*pos*/ -2800, -3300,     0),
    TRAJECTORY_POS(12, /*pos*/ -2600, -3450,     0),
    TRAJECTORY_POS(13, /*pos*/ -2400, -3500,     0),
    TRAJECTORY_POS(14, /*pos*/ -2200, -3450,     0),
    TRAJECTORY_POS(15, /*pos*/ -2000, -3300,     0),
    TRAJECTORY_POS(16, /*pos*/ -1800, -3150,     0),
    TRAJECTORY_POS(17, /*pos*/ -1600, -3072,     0),
    TRAJECTORY_POS(18, /*pos*/ -1300, -3072,     0),
    TRAJECTORY_POS(19, /*pos*/ -1000, -3072,     0),
    TRAJECTORY_POS(20, /*pos*/  -608, -3072,     0),
    TRAJECTORY_POS(21, /*pos*/ -1000, -3072,     0),
    TRAJECTORY_POS(22, /*pos*/ -1300, -3072,     0),
    TRAJECTORY_POS(23, /*pos*/ -1600, -3072,     0),
    TRAJECTORY_POS(24, /*pos*/ -1800, -3150,     0),
    TRAJECTORY_POS(25, /*pos*/ -2000, -3300,     0),
    TRAJECTORY_POS(26, /*pos*/ -2200, -3450,     0),
    TRAJECTORY_POS(27, /*pos*/ -2400, -3500,     0),
    TRAJECTORY_POS(28, /*pos*/ -2600, -3450,     0),
    TRAJECTORY_POS(29, /*pos*/ -2800, -3300,     0),
    TRAJECTORY_POS(30, /*pos*/ -3000, -3150,     0),
    TRAJECTORY_POS(31, /*pos*/ -3160, -3072,     0),
    TRAJECTORY_POS(32, /*pos*/ -3460, -3072,     0),
    TRAJECTORY_POS(33, /*pos*/ -3650, -3122,     0),
    TRAJECTORY_POS(34, /*pos*/ -3850, -3172,     0),
    TRAJECTORY_POS(35, /*pos*/ -4300, -3172,     0),
    TRAJECTORY_POS(36, /*pos*/ -4754, -3172,     0),
    TRAJECTORY_POS(37, /*pos*/ -4954, -3122,     0),
    TRAJECTORY_POS(38, /*pos*/ -5144, -3072,     0),
    TRAJECTORY_POS(39, /*pos*/ -5444, -3072,     0),
    TRAJECTORY_END(),
};
/**
 * Despawn all track balls and enter the init action.
 */
static void platform_on_track_reset(struct Object* o) {
    o->oAction = PLATFORM_ON_TRACK_ACT_INIT;
    // This will cause the track balls to all despawn
    o->oPlatformOnTrackBaseBallIndex += 99;
}

/**
 * Init function for bhvPlatformOnTrack.
 */
void bhv_platform_on_track_init(struct Object* o) {
    s16 pathIndex = (u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_MASK_PATH;
    o->oPlatformOnTrackType = ((u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_MASK_TYPE) >> 4;

    o->oPlatformOnTrackIsNotSkiLift = o->oPlatformOnTrackType - PLATFORM_ON_TRACK_TYPE_SKI_LIFT;

    o->oPlatformOnTrackStartWaypoint = (Waypoint*)(&bitfs_seg7_trajectory_070159AC);

    o->oPlatformOnTrackIsNotHMC = pathIndex - 4;

    o->oBehParams2ndByte = o->oMoveAngleYaw; // TODO: Weird?

    if (o->oPlatformOnTrackType == PLATFORM_ON_TRACK_TYPE_CHECKERED) {
        o->header.gfx.scale[1] = 2.0f;
    }
}

/**
 * Move to the start waypoint, spawn the first track balls, and enter the
 * wait for mario action.
 */
static void platform_on_track_act_init(struct Object* o) {
    s32 i;

    o->oPlatformOnTrackPrevWaypoint = o->oPlatformOnTrackStartWaypoint;
    o->oPlatformOnTrackPrevWaypointFlags = 0;
    o->oPlatformOnTrackBaseBallIndex = 0;

    o->oPosX = o->oHomeX = o->oPlatformOnTrackStartWaypoint->pos[0];
    o->oPosY = o->oHomeY = o->oPlatformOnTrackStartWaypoint->pos[1];
    o->oPosZ = o->oHomeZ = o->oPlatformOnTrackStartWaypoint->pos[2];

    o->oFaceAngleYaw = o->oBehParams2ndByte;
    o->oForwardVel = o->oVelX = o->oVelY = o->oVelZ = o->oPlatformOnTrackDistMovedSinceLastBall = 0.0f;

    o->oPlatformOnTrackWasStoodOn = FALSE;

    o->oFaceAngleRoll = 0;

    o->oAction = PLATFORM_ON_TRACK_ACT_WAIT_FOR_MARIO;
}

/**
 * Wait for mario to stand on the platform for 20 frames, then begin moving.
 */
static void platform_on_track_act_wait_for_mario(struct Object* o, struct MarioState* m) {
    if (m->marioObj->platform == o) {
        if (o->oTimer > 20) {
            o->oAction = PLATFORM_ON_TRACK_ACT_MOVE_ALONG_TRACK;
        }
    }
    else {
        o->oTimer = 0;
    }
}

static s32 approach_f32_ptr(f32* px, f32 target, f32 delta) {
    if (*px > target) {
        delta = -delta;
    }

    *px += delta;

    if ((*px - target) * delta >= 0) {
        *px = target;
        return TRUE;
    }
    return FALSE;
}

static void platform_on_track_update_pos_or_spawn_ball(struct Object* o, s32 ballIndex, f32 x, f32 y, f32 z) {
    struct Object* trackBall;
    struct Waypoint* initialPrevWaypoint;
    struct Waypoint* nextWaypoint;
    struct Waypoint* prevWaypoint;
    f32 amountToMove;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 sObjSavedPosX;
    f32 sObjSavedPosY;
    f32 sObjSavedPosZ;
    f32 distToNextWaypoint;

    initialPrevWaypoint = o->oPlatformOnTrackPrevWaypoint;
    nextWaypoint = initialPrevWaypoint;

    sObjSavedPosX = o->oPosX;
    sObjSavedPosY = o->oPosY;
    sObjSavedPosZ = o->oPosZ;
    o->oPlatformOnTrackPrevWaypointFlags = 0;
    amountToMove = o->oForwardVel;

    do {
        prevWaypoint = nextWaypoint;

        nextWaypoint++;
        if (nextWaypoint->flags == WAYPOINT_FLAGS_END) {
            if (ballIndex == 0) {
                o->oPlatformOnTrackPrevWaypointFlags = WAYPOINT_FLAGS_END;
            }

            nextWaypoint = o->oPlatformOnTrackStartWaypoint;
        }

        dx = nextWaypoint->pos[0] - x;
        dy = nextWaypoint->pos[1] - y;
        dz = nextWaypoint->pos[2] - z;

        distToNextWaypoint = sqrtf(dx * dx + dy * dy + dz * dz);

        // Move directly to the next waypoint, even if it's farther away
        // than amountToMove
        amountToMove -= distToNextWaypoint;
        x += dx;
        y += dy;
        z += dz;
    } while (amountToMove > 0.0f);

    // If we moved farther than amountToMove, move in the opposite direction
    // No risk of near-zero division: If distToNextWaypoint is close to
    // zero, then that means we didn't cross a waypoint this frame (since
    // otherwise distToNextWaypoint would equal the distance between two
    // waypoints, which should never be that small). But this implies that
    // amountToMove - distToNextWaypoint <= 0, and amountToMove is at least
    // 0.1 (from platform on track behavior).
    distToNextWaypoint = amountToMove / distToNextWaypoint;
    x += dx * distToNextWaypoint;
    y += dy * distToNextWaypoint;
    z += dz * distToNextWaypoint;

    if (prevWaypoint != initialPrevWaypoint) {
        if (o->oPlatformOnTrackPrevWaypointFlags == 0) {
            o->oPlatformOnTrackPrevWaypointFlags = initialPrevWaypoint->flags;
        }
        o->oPlatformOnTrackPrevWaypoint = prevWaypoint;
    }

    o->oPosX = x;
    o->oPosY = y;
    o->oPosZ = z;

    o->oVelX = o->oPosX - sObjSavedPosX;
    o->oVelY = o->oPosY - sObjSavedPosY;
    o->oVelZ = o->oPosZ - sObjSavedPosZ;

    o->oPlatformOnTrackPitch =
        atan2s(sqrtf(o->oVelX * o->oVelX + o->oVelZ * o->oVelZ), -o->oVelY);
    o->oPlatformOnTrackYaw = atan2s(o->oVelZ, o->oVelX);
}

s16 approach_s16_symmetric(s16 value, s16 target, s16 increment) {
    s16 dist = target - value;

    if (dist >= 0) {
        if (dist > increment) {
            value += increment;
        }
        else {
            value = target;
        }
    }
    else {
        if (dist < -increment) {
            value -= increment;
        }
        else {
            value = target;
        }
    }

    return value;
}

s16 abs_angle_diff(s16 x0, s16 x1) {
    s16 diff = x1 - x0;

    if (diff == -0x8000) {
        diff = -0x7FFF;
    }

    if (diff < 0) {
        diff = -diff;
    }

    return diff;
}

static s32 clamp_s16(s16* value, s16 minimum, s16 maximum) {
    if (*value <= minimum) {
        *value = minimum;
    }
    else if (*value >= maximum) {
        *value = maximum;
    }
    else {
        return FALSE;
    }

    return TRUE;
}

static s32 obj_face_yaw_approach(struct Object* o, s16 targetYaw, s16 deltaYaw) {
    o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, targetYaw, deltaYaw);

    if ((s16)o->oFaceAngleYaw == targetYaw) {
        return TRUE;
    }

    return FALSE;
}

/**
 * Move along the track. After reaching the end, either start falling,
 * return to the init action, or continue moving back to the start waypoint.
 */
static void platform_on_track_act_move_along_track(struct Object* o, struct MarioState* m) {
    s16 initialAngle;

    // Fall after reaching the last waypoint if desired
    o->oForwardVel = 10.0f;

    // Spawn a new track ball if necessary
    if (approach_f32_ptr(&o->oPlatformOnTrackDistMovedSinceLastBall, 300.0f, o->oForwardVel)) {
        o->oPlatformOnTrackDistMovedSinceLastBall -= 300.0f;

        o->oHomeX = o->oPosX;
        o->oHomeY = o->oPosY;
        o->oHomeZ = o->oPosZ;
        o->oPlatformOnTrackBaseBallIndex = (u16)(o->oPlatformOnTrackBaseBallIndex + 1);
    }

    platform_on_track_update_pos_or_spawn_ball(o, 0, o->oPosX, o->oPosY, o->oPosZ);

    o->oMoveAnglePitch = o->oPlatformOnTrackPitch;
    o->oMoveAngleYaw = o->oPlatformOnTrackYaw;

    //! Both oAngleVelYaw and oAngleVelRoll aren't reset until the platform
    //  starts moving again, resulting in unexpected platform displacement
    //  after reappearing

    // Turn face yaw and compute yaw vel
    if (!((u16)(o->oBehParams >> 16) & PLATFORM_ON_TRACK_BP_DONT_TURN_YAW)) {
        s16 targetFaceYaw = o->oMoveAngleYaw + 0x4000;
        s16 yawSpeed = abs_angle_diff(targetFaceYaw, o->oFaceAngleYaw) / 20;

        initialAngle = o->oFaceAngleYaw;
        clamp_s16(&yawSpeed, 100, 500);
        obj_face_yaw_approach(o, targetFaceYaw, yawSpeed);
        o->oAngleVelYaw = (s16)o->oFaceAngleYaw - initialAngle;
    }

    if (m->marioObj->platform != o) {
    }
    else {
        o->oTimer = 0;
    }
}

/**
 * Wait 20 frames then continue moving.
 */
static void platform_on_track_act_pause_briefly(struct Object* o) {
    if (o->oTimer > 20) {
        o->oAction = PLATFORM_ON_TRACK_ACT_MOVE_ALONG_TRACK;
    }
}

/**
 * Update function for bhvPlatformOnTrack.
 */
void bhv_platform_on_track_update(struct Object* o, struct MarioState* m) {
    switch (o->oAction) {
    case PLATFORM_ON_TRACK_ACT_INIT:
        platform_on_track_act_init(o);
        break;
    case PLATFORM_ON_TRACK_ACT_WAIT_FOR_MARIO:
        platform_on_track_act_wait_for_mario(o, m);
        break;
    case PLATFORM_ON_TRACK_ACT_MOVE_ALONG_TRACK:
        platform_on_track_act_move_along_track(o, m);
        break;
    case PLATFORM_ON_TRACK_ACT_PAUSE_BRIEFLY:
        platform_on_track_act_pause_briefly(o);
        break;
    }
}