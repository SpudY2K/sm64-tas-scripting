#include <sm64/Camera.hpp>
#include <sm64/Math.hpp>
#include <sm64/Sm64.hpp>
#include <sm64/Surface.hpp>
#include <sm64/SurfaceTerrains.hpp>
#include <sm64/Trig.hpp>
#include <sm64/Types.hpp>

#define CBUTTON_MASK (U_CBUTTONS | D_CBUTTONS | L_CBUTTONS | R_CBUTTONS)

/**
 * @file camera.c
 * Implements the camera system, including C-button input, camera modes, camera triggers, and cutscenes.
 *
 * When working with the camera, you should be familiar with sm64's coordinate system.
 * Relative to the camera, the coordinate system follows the right hand rule:
 *          +X points right.
 *          +Y points up.
 *          +Z points out of the screen.
 *
 * You should also be familiar with Euler angles: 'pitch', 'yaw', and 'roll'.
 *      pitch: rotation about the X-axis, measured from +Y.
 *          Unlike yaw and roll, pitch is bounded in +-0x4000 (90 degrees).
 *          Pitch is 0 when the camera points parallel to the xz-plane (+Y points straight up).
 *
 *      yaw: rotation about the Y-axis, measured from (absolute) +Z.
 *          Positive yaw rotates clockwise, towards +X.
 *
 *      roll: rotation about the Z-axis, measured from the camera's right direction.
 *          Unfortunately, it's weird: For some reason, roll is flipped. Positive roll makes the camera
 *          rotate counterclockwise, which means the WORLD rotates clockwise. Luckily roll is rarely
 *          used.
 *
 *      Remember the right hand rule: make a thumbs-up with your right hand, stick your thumb in the
 *      +direction (except for roll), and the angle follows the rotation of your curled fingers.
 *
 * Illustrations:
 * Following the right hand rule, each hidden axis's positive direction points out of the screen.
 *
 *       YZ-Plane (pitch)        XZ-Plane (yaw)          XY-Plane (roll -- Note flipped)
 *          +Y                      -Z                      +Y
 *           ^                       ^ (into the             ^
 *         --|--                     |   screen)             |<-
 * +pitch /  |  \ -pitch             |                       |  \ -roll
 *       v   |   v                   |                       |   |
 * +Z <------O------> -Z   -X <------O------> +X   -X <------O------> +X
 *           |                   ^   |   ^                   |   |
 *           |                    \  |  /                    |  / +roll
 *           |               -yaw  --|--  +yaw               |<-
 *           v                       v                       v
 *          -Y                      +Z                      -Y
 *
 */

u8 sZoomOutAreaMasks[] = {
    ZOOMOUT_AREA_MASK(0,0,0,0, 0,0,0,0), // Unused         | Unused
    ZOOMOUT_AREA_MASK(0,0,0,0, 0,0,0,0), // Unused         | Unused
    ZOOMOUT_AREA_MASK(0,0,0,0, 1,0,0,0), // BBH            | CCM
    ZOOMOUT_AREA_MASK(0,0,0,0, 0,0,0,0), // CASTLE_INSIDE  | HMC
    ZOOMOUT_AREA_MASK(1,0,0,0, 1,0,0,0), // SSL            | BOB
    ZOOMOUT_AREA_MASK(1,0,0,0, 1,0,0,0), // SL             | WDW
    ZOOMOUT_AREA_MASK(0,0,0,0, 1,1,0,0), // JRB            | THI
    ZOOMOUT_AREA_MASK(0,0,0,0, 1,0,0,0), // TTC            | RR
    ZOOMOUT_AREA_MASK(1,0,0,0, 1,0,0,0), // CASTLE_GROUNDS | BITDW
    ZOOMOUT_AREA_MASK(0,0,0,0, 1,0,0,0), // VCUTM          | BITFS
    ZOOMOUT_AREA_MASK(0,0,0,0, 1,0,0,0), // SA             | BITS
    ZOOMOUT_AREA_MASK(1,0,0,0, 0,0,0,0), // LLL            | DDD
    ZOOMOUT_AREA_MASK(1,0,0,0, 0,0,0,0), // WF             | ENDING
    ZOOMOUT_AREA_MASK(0,0,0,0, 0,0,0,0), // COURTYARD      | PSS
    ZOOMOUT_AREA_MASK(0,0,0,0, 1,0,0,0), // COTMC          | TOTWC
    ZOOMOUT_AREA_MASK(1,0,0,0, 1,0,0,0), // BOWSER_1       | WMOTR
    ZOOMOUT_AREA_MASK(0,0,0,0, 1,0,0,0), // Unused         | BOWSER_2
    ZOOMOUT_AREA_MASK(1,0,0,0, 0,0,0,0), // BOWSER_3       | Unused
    ZOOMOUT_AREA_MASK(1,0,0,0, 0,0,0,0), // TTM            | Unused
    ZOOMOUT_AREA_MASK(0,0,0,0, 0,0,0,0), // Unused         | Unused
};

s32 update_mario_camera(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, Vec3f, Vec3f);
s32 update_c_up(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, Vec3f, Vec3f);
s32 update_8_directions_camera(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, Vec3f, Vec3f);

typedef s32(*CameraTransition)(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, Vec3f, Vec3f);
CameraTransition sModeTransitions[] = {
    NULL,
    NULL,
    NULL,
    NULL,
    update_mario_camera,
    NULL,
    update_c_up,
    update_mario_camera,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    update_8_directions_camera,
    NULL,
    update_mario_camera,
    NULL
};


/**
 * Calculates Mario's distance to the floor, or the water level if it is above the floor. Then:
 * `posOff` is set to the distance multiplied by posMul and bounded to [-posBound, posBound]
 * `focOff` is set to the distance multiplied by focMul and bounded to [-focBound, focBound]
 *
 * Notes:
 *      posMul is always 1.0f, focMul is always 0.9f
 *      both ranges are always 200.f
 *          Since focMul is 0.9, `focOff` is closer to the floor than `posOff`
 *      posOff and focOff are sometimes the same address, which just ignores the pos calculation
 *! Doesn't return anything, but required to match on -O2
 */
void calc_y_to_curr_floor(struct CameraData* cameraData, f32* posOff, f32 posMul, f32 posBound, f32* focOff, f32 focMul, f32 focBound) {
    f32 floorHeight = cameraData->sMarioGeometry.currFloorHeight;
    f32 waterHeight;

    *posOff = (floorHeight - cameraData->sMarioCamState->pos[1]) * posMul;

    if (*posOff > posBound) {
        *posOff = posBound;
    }

    if (*posOff < -posBound) {
        *posOff = -posBound;
    }

    *focOff = (floorHeight - cameraData->sMarioCamState->pos[1]) * focMul;

    if (*focOff > focBound) {
        *focOff = focBound;
    }

    if (*focOff < -focBound) {
        *focOff = -focBound;
    }
}

void focus_on_mario(struct CameraData* cameraData, Vec3f focus, Vec3f pos, f32 posYOff, f32 focYOff, f32 dist, s16 pitch, s16 yaw) {
    Vec3f marioPos;

    marioPos[0] = cameraData->sMarioCamState->pos[0];
    marioPos[1] = cameraData->sMarioCamState->pos[1] + posYOff;
    marioPos[2] = cameraData->sMarioCamState->pos[2];

    vec3f_set_dist_and_angle(marioPos, pos, dist, pitch + cameraData->sLakituPitch, yaw);

    focus[0] = cameraData->sMarioCamState->pos[0];
    focus[1] = cameraData->sMarioCamState->pos[1] + focYOff;
    focus[2] = cameraData->sMarioCamState->pos[2];
}

/**
 * Set the camera's y coordinate to goalHeight, respecting floors and ceilings in the way
 */
void set_camera_height(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, f32 goalHeight) {
    struct Surface* surface;
    f32 marioFloorHeight;
    f32 marioCeilHeight;
    f32 camFloorHeight;
    f32 baseOff = 125.f;
    f32 camCeilHeight = find_ceil(surfaceLists, c->pos[0], cameraData->gLakituState.goalPos[1] - 50.f, c->pos[2], &surface);

    camFloorHeight = find_floor(surfaceLists, c->pos[0], c->pos[1] + 100.f, c->pos[2], &surface) + baseOff;
    marioFloorHeight = baseOff + cameraData->sMarioGeometry.currFloorHeight;

    if (camFloorHeight < marioFloorHeight) {
        camFloorHeight = marioFloorHeight;
    }
    if (goalHeight < camFloorHeight) {
        goalHeight = camFloorHeight;
        c->pos[1] = goalHeight;
    }

    approach_camera_height(c, cameraData, goalHeight, 20.f);
    if (camCeilHeight != CELL_HEIGHT_LIMIT) {
        camCeilHeight -= baseOff;
        if ((c->pos[1] > camCeilHeight && cameraData->sMarioGeometry.currFloorHeight + baseOff < camCeilHeight)
            || (cameraData->sMarioGeometry.currCeilHeight != CELL_HEIGHT_LIMIT
                && cameraData->sMarioGeometry.currCeilHeight > camCeilHeight && c->pos[1] > camCeilHeight)) {
            c->pos[1] = camCeilHeight;
        }
    }
}

/**
 * Pitch the camera down when the camera is facing down a slope
 */
s16 look_down_slopes(struct CameraData* cameraData, s16 camYaw, struct Surfaces* surfaceLists) {
    struct Surface* floor;
    f32 floorDY;
    // Default pitch
    s16 pitch = 0x05B0;
    // x and z offsets towards the camera
    f32 xOff = cameraData->sMarioCamState->pos[0] + sins(camYaw) * 40.f;
    f32 zOff = cameraData->sMarioCamState->pos[2] + coss(camYaw) * 40.f;

    floorDY = find_floor(surfaceLists, xOff, cameraData->sMarioCamState->pos[1], zOff, &floor) - cameraData->sMarioCamState->pos[1];

    if (floor != NULL) {
        if (floor->type != SURFACE_WALL_MISC && floorDY > 0) {
            if (floor->normal.z == 0.f && floorDY < 100.f) {
                pitch = 0x05B0;
            }
            else {
                // Add the slope's angle of declination to the pitch
                pitch += atan2s(40.f, floorDY);
            }
        }
    }

    return pitch;
}

/**
 * Look ahead to the left or right in the direction the player is facing
 * The calculation for pan[0] could be simplified to:
 *      yaw = -yaw;
 *      pan[0] = sins(sMarioCamState->faceAngle[1] + yaw) * sins(0xC00) * dist;
 * Perhaps, early in development, the pan used to be calculated for both the x and z directions
 *
 * Since this function only affects the camera's focus, Mario's movement direction isn't affected.
 */
void pan_ahead_of_player(struct Camera* c, struct CameraData* cameraData) {
    f32 dist;
    s16 pitch;
    s16 yaw;
    Vec3f pan = { 0, 0, 0 };

    // Get distance and angle from camera to Mario.
    vec3f_get_dist_and_angle(c->pos, cameraData->sMarioCamState->pos, &dist, &pitch, &yaw);

    // The camera will pan ahead up to about 30% of the camera's distance to Mario.
    pan[2] = sins(0xC00) * dist;

    rotate_in_xz(pan, pan, cameraData->sMarioCamState->faceAngle[1]);
    // rotate in the opposite direction
    yaw = -yaw;
    rotate_in_xz(pan, pan, yaw);
    // Only pan left or right
    pan[2] = 0.f;

    // Slowly make the actual pan, sPanDistance, approach the calculated pan
    // If Mario is sleeping, then don't pan
    if (cameraData->sStatusFlags & CAM_FLAG_SLEEPING) {
        approach_f32_asymptotic_bool(&(cameraData->sPanDistance), 0.f, 0.025f);
    }
    else {
        approach_f32_asymptotic_bool(&(cameraData->sPanDistance), pan[0], 0.025f);
    }

    // Now apply the pan. It's a dir vector to the left or right, rotated by the camera's yaw to Mario
    pan[0] = cameraData->sPanDistance;
    yaw = -yaw;
    rotate_in_xz(pan, pan, yaw);
    vec3f_add(c->focus, pan);
}

/**
 * Update the camera during 8 directional mode
 */
s32 update_8_directions_camera(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, Vec3f focus, Vec3f pos) {
    s16 camYaw = cameraData->s8DirModeBaseYaw + cameraData->s8DirModeYawOffset;
    s16 pitch = look_down_slopes(cameraData, camYaw, surfaceLists);
    f32 posY;
    f32 focusY;
    f32 yOff = 125.f;
    f32 baseDist = 1000.f;

    cameraData->sAreaYaw = camYaw;
    calc_y_to_curr_floor(cameraData, &posY, 1.f, 200.f, &focusY, 0.9f, 200.f);
    focus_on_mario(cameraData, focus, pos, posY + yOff, focusY + yOff, cameraData->sLakituDist + baseDist, pitch, camYaw);
    pan_ahead_of_player(c, cameraData);

    return camYaw;
}

/**
 * Moves Lakitu from zoomed in to zoomed out and vice versa.
 * When C-Down mode is not active, sLakituDist and sLakituPitch decrease to 0.
 */
void lakitu_zoom(struct CameraData* cameraData, f32 rangeDist, s16 rangePitch) {
    if (cameraData->sLakituDist < 0) {
        if ((cameraData->sLakituDist += 30) > 0) {
            cameraData->sLakituDist = 0;
        }
    }
    else if (rangeDist < cameraData->sLakituDist) {
        if ((cameraData->sLakituDist -= 30) < rangeDist) {
            cameraData->sLakituDist = rangeDist;
        }
    }
    else if (cameraData->gCameraMovementFlags & CAM_MOVE_ZOOMED_OUT) {
        if ((cameraData->sLakituDist += 30) > rangeDist) {
            cameraData->sLakituDist = rangeDist;
        }
    }
    else {
        if ((cameraData->sLakituDist -= 30) < 0) {
            cameraData->sLakituDist = 0;
        }
    }

    if (cameraData->gCameraMovementFlags & CAM_MOVE_ZOOMED_OUT) {
        if ((cameraData->sLakituPitch += rangePitch / 13) > rangePitch) {
            cameraData->sLakituPitch = rangePitch;
        }
    }
    else {
        if ((cameraData->sLakituPitch -= rangePitch / 13) < 0) {
            cameraData->sLakituPitch = 0;
        }
    }
}

/**
 * A mode that only has 8 camera angles, 45 degrees apart
 */
void mode_8_directions_camera(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, struct Controller* gPlayer1Controller) {
    Vec3f pos;
    s16 oldAreaYaw = cameraData->sAreaYaw;

    radial_camera_input(c, cameraData, gPlayer1Controller, 0.f);

    if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
        cameraData->s8DirModeYawOffset += DEGREES(45);
    }
    if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
        cameraData->s8DirModeYawOffset -= DEGREES(45);
    }

    lakitu_zoom(cameraData, 400.f, 0x900);
    c->nextYaw = update_8_directions_camera(c, cameraData, surfaceLists, c->focus, pos);
    c->pos[0] = pos[0];
    c->pos[2] = pos[2];
    cameraData->sAreaYawChange = cameraData->sAreaYaw - oldAreaYaw;
    set_camera_height(c, cameraData, surfaceLists, pos[1]);
}

/**
 * Used in sModeTransitions for CLOSE and FREE_ROAM mode
 */
s32 update_mario_camera(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, Vec3f focus, Vec3f pos) {
    s16 yaw = cameraData->sMarioCamState->faceAngle[1] + cameraData->sModeOffsetYaw + DEGREES(180);
    focus_on_mario(cameraData, focus, pos, 125.f, 125.f, cameraData->gCameraZoomDist, 0x05B0, yaw);

    return cameraData->sMarioCamState->faceAngle[1];
}

/**
 * Update the camera in default, close, and free roam mode
 *
 * The camera moves behind Mario, and can rotate all the way around
 */
s16 update_default_camera(struct Camera* c, struct CameraData* cameraData, struct MarioState* m, struct Surfaces* surfaceLists, struct Controller* gPlayer1Controller) {
    Vec3f tempPos;
    Vec3f cPos;
    struct Surface* marioFloor;
    struct Surface* cFloor;
    struct Surface* tempFloor;
    struct Surface* ceil;
    f32 camFloorHeight;
    f32 tempFloorHeight;
    f32 marioFloorHeight;
    f32 dist;
    f32 zoomDist;
    f32 waterHeight;
    f32 gasHeight;
    s16 avoidYaw;
    s16 pitch;
    s16 yaw;
    s16 yawGoal = cameraData->sMarioCamState->faceAngle[1] + DEGREES(180);
    f32 posHeight;
    f32 focHeight;
    f32 distFromWater;
    s16 tempPitch;
    s16 tempYaw;
    f32 xzDist;
    s16 nextYawVel;
    s16 yawVel = 0;
    f32 scale;
    s32 avoidStatus = 0;
    s32 closeToMario = 0;
    f32 ceilHeight = find_ceil(surfaceLists, cameraData->gLakituState.goalPos[0],
        cameraData->gLakituState.goalPos[1],
        cameraData->gLakituState.goalPos[2], &ceil);
    s16 yawDir;

    handle_c_button_movement(c, cameraData, gPlayer1Controller);
    vec3f_get_dist_and_angle(cameraData->sMarioCamState->pos, c->pos, &dist, &pitch, &yaw);

    // If C-Down is active, determine what distance the camera should be from Mario
    if (cameraData->gCameraMovementFlags & CAM_MOVE_ZOOMED_OUT) {
        //! In Mario mode, the camera is zoomed out further than in Lakitu mode (1400 vs 1200)
        if (set_cam_angle(cameraData, 0) == CAM_ANGLE_MARIO) {
            zoomDist = cameraData->gCameraZoomDist + 1050;
        }
        else {
            zoomDist = cameraData->gCameraZoomDist + 400;
        }
    }
    else {
        zoomDist = cameraData->gCameraZoomDist;
    }

    // If not zooming out, only allow dist to decrease
    if (cameraData->sZoomAmount == 0.f) {
        if (dist > zoomDist) {
            if ((dist -= 50.f) < zoomDist) {
                dist = zoomDist;
            }
        }
    }
    else {
        if ((cameraData->sZoomAmount -= 30.f) < 0.f) {
            cameraData->sZoomAmount = 0.f;
        }
        if (dist > zoomDist) {
            if ((dist -= 30.f) < zoomDist) {
                dist = zoomDist;
            }
        }
        if (dist < zoomDist) {
            if ((dist += 30.f) > zoomDist) {
                dist = zoomDist;
            }
        }
    }

    // Determine how fast to rotate the camera
    if (cameraData->sCSideButtonYaw == 0) {
        if (c->mode == CAMERA_MODE_FREE_ROAM) {
            nextYawVel = 0xC0;
        }
        else {
            nextYawVel = 0x100;
        }
        if ((gPlayer1Controller->stickX != 0.f || gPlayer1Controller->stickY != 0.f) != 0) {
            nextYawVel = 0x20;
        }
    }
    else {
        if (cameraData->sCSideButtonYaw < 0) {
            yaw += 0x200;
        }
        if (cameraData->sCSideButtonYaw > 0) {
            yaw -= 0x200;
        }
        camera_approach_s16_symmetric_bool(&(cameraData->sCSideButtonYaw), 0, 0x100);
        nextYawVel = 0;
    }
    cameraData->sYawSpeed = 0x400;
    xzDist = calc_hor_dist(cameraData->sMarioCamState->pos, c->pos);

    if (xzDist < 250) {
        // Turn rapidly if very close to Mario
        c->pos[0] += (250 - xzDist) * sins(yaw);
        c->pos[2] += (250 - xzDist) * coss(yaw);
        if (cameraData->sCSideButtonYaw == 0) {
            nextYawVel = 0x1000;
            cameraData->sYawSpeed = 0;
            vec3f_get_dist_and_angle(cameraData->sMarioCamState->pos, c->pos, &dist, &pitch, &yaw);
        }
        closeToMario |= 1;
    }

    if (-16 < gPlayer1Controller->stickY) {
        c->yaw = yaw;
    }

    calc_y_to_curr_floor(cameraData, &posHeight, 1, 200, &focHeight, 0.9f, 200);
    vec3f_copy(cPos, c->pos);
    avoidStatus = rotate_camera_around_walls(c, cameraData, surfaceLists, cPos, &avoidYaw, 0x600);
    // If a wall is blocking the view of Mario, then rotate in the calculated direction
    if (avoidStatus == 3) {
        cameraData->sAvoidYawVel = yaw;
        cameraData->sStatusFlags |= CAM_FLAG_COLLIDED_WITH_WALL;
        //! Does nothing
        vec3f_get_dist_and_angle(cameraData->sMarioCamState->pos, cPos, &xzDist, &tempPitch, &tempYaw);
        // Rotate to avoid the wall
        approach_s16_asymptotic_bool(&yaw, avoidYaw, 10);
        //! Does nothing
        vec3f_set_dist_and_angle(cameraData->sMarioCamState->pos, cPos, xzDist, tempPitch, tempYaw);
        cameraData->sAvoidYawVel = (cameraData->sAvoidYawVel - yaw) / 0x100;
    }
    else {
        if (m->forwardVel == 0.f) {
            if (cameraData->sStatusFlags & CAM_FLAG_COLLIDED_WITH_WALL) {
                if ((yawGoal - yaw) / 0x100 >= 0) {
                    yawDir = -1;
                }
                else {
                    yawDir = 1;
                }
                if ((cameraData->sAvoidYawVel > 0 && yawDir > 0) || (cameraData->sAvoidYawVel < 0 && yawDir < 0)) {
                    yawVel = nextYawVel;
                }
            }
            else {
                yawVel = nextYawVel;
            }
        }
        else {
            if (nextYawVel == 0x1000) {
                yawVel = nextYawVel;
            }
            cameraData->sStatusFlags &= ~CAM_FLAG_COLLIDED_WITH_WALL;
        }

        // If a wall is near the camera, turn twice as fast
        if (avoidStatus != 0) {
            yawVel += yawVel;
        }
        // ...Unless the camera already rotated from being close to Mario
        if ((closeToMario & 1) && avoidStatus != 0) {
            yawVel = 0;
        }
        if (yawVel != 0) {
            camera_approach_s16_symmetric_bool(&yaw, yawGoal, yawVel);
        }
    }

    // Only zoom out if not obstructed by walls and Lakitu hasn't collided with any
    if (avoidStatus == 0 && !(cameraData->sStatusFlags & CAM_FLAG_COLLIDED_WITH_WALL)) {
        approach_f32_asymptotic_bool(&dist, zoomDist - 100.f, 0.05f);
    }
    vec3f_set_dist_and_angle(cameraData->sMarioCamState->pos, cPos, dist, pitch, yaw);
    cPos[1] += posHeight + 125.f;

    // Move the camera away from walls and set the collision flag
    if (collide_with_walls(surfaceLists, cPos, 10.f, 80.f) != 0) {
        cameraData->sStatusFlags |= CAM_FLAG_COLLIDED_WITH_WALL;
    }

    c->focus[0] = cameraData->sMarioCamState->pos[0];
    c->focus[1] = cameraData->sMarioCamState->pos[1] + 125.f + focHeight;
    c->focus[2] = cameraData->sMarioCamState->pos[2];

    marioFloorHeight = 125.f + cameraData->sMarioGeometry.currFloorHeight;
    marioFloor = cameraData->sMarioGeometry.currFloor;
    camFloorHeight = find_floor(surfaceLists, cPos[0], cPos[1] + 50.f, cPos[2], &cFloor) + 125.f;
    for (scale = 0.1f; scale < 1.f; scale += 0.2f) {
        scale_along_line(tempPos, cPos, cameraData->sMarioCamState->pos, scale);
        tempFloorHeight = find_floor(surfaceLists, tempPos[0], tempPos[1], tempPos[2], &tempFloor) + 125.f;
        if (tempFloor != NULL && tempFloorHeight > marioFloorHeight) {
            marioFloorHeight = tempFloorHeight;
            marioFloor = tempFloor;
        }
    }

    // Lower the camera in Mario mode
    if (cameraData->sSelectionFlags & CAM_MODE_MARIO_ACTIVE) {
        marioFloorHeight -= 35.f;
        camFloorHeight -= 35.f;
        c->focus[1] -= 25.f;
    }

    cameraData->gCameraMovementFlags &= ~CAM_MOVE_METAL_BELOW_WATER;

    cPos[1] = camFloorHeight;
    vec3f_copy(tempPos, cPos);
    tempPos[1] -= 125.f;
    if (marioFloor != NULL && camFloorHeight <= marioFloorHeight) {
        avoidStatus = is_range_behind_surface(c->focus, tempPos, marioFloor, 0, -1);
        if (avoidStatus != 1 && ceilHeight > marioFloorHeight) {
            camFloorHeight = marioFloorHeight;
        }
    }

    posHeight = 0.f;
    if ((cameraData->gCameraMovementFlags & CAM_MOVE_ZOOMED_OUT) && (cameraData->sSelectionFlags & CAM_MODE_MARIO_ACTIVE)) {
        posHeight = 610.f;
    }

    if (camFloorHeight != FLOOR_LOWER_LIMIT) {
        camFloorHeight += posHeight;
        approach_camera_height(c, cameraData, camFloorHeight, 20.f);
    }

    c->pos[0] = cPos[0];
    c->pos[2] = cPos[2];
    cPos[0] = cameraData->gLakituState.goalPos[0];
    cPos[1] = c->pos[1];
    cPos[2] = cameraData->gLakituState.goalPos[2];
    vec3f_get_dist_and_angle(cPos, c->pos, &dist, &tempPitch, &tempYaw);
    // Prevent the camera from lagging behind too much
    if (dist > 50.f) {
        dist = 50.f;
        vec3f_set_dist_and_angle(cPos, c->pos, dist, tempPitch, tempYaw);
    }

    vec3f_get_dist_and_angle(c->focus, c->pos, &dist, &tempPitch, &tempYaw);
    if (dist > zoomDist) {
        dist = zoomDist;
        vec3f_set_dist_and_angle(c->focus, c->pos, dist, tempPitch, tempYaw);
    }

    if (ceilHeight != CELL_HEIGHT_LIMIT) {
        if (c->pos[1] > (ceilHeight -= 150.f)
            && (avoidStatus = is_range_behind_surface(c->pos, cameraData->sMarioCamState->pos, ceil, 0, -1)) == 1) {
            c->pos[1] = ceilHeight;
        }
    }
    return yaw;
}

/**
 * The default camera mode
 * Used by close and free roam modes
 */
void mode_default_camera(struct Camera* c, struct CameraData* cameraData, struct MarioState* m, struct Surfaces* surfaceLists, struct Controller* gPlayer1Controller) {
    c->nextYaw = update_default_camera(c, cameraData, m, surfaceLists, gPlayer1Controller);
    pan_ahead_of_player(c, cameraData);
}

/**
 * When no other mode is active and the current R button mode is Mario
 */
void mode_mario_camera(struct Camera* c, struct CameraData* cameraData, struct MarioState* m, struct Surfaces* surfaceLists, struct Controller* gPlayer1Controller) {
    cameraData->gCameraZoomDist = 350.f;
    mode_default_camera(c, cameraData, m, surfaceLists, gPlayer1Controller);
}

void store_lakitu_cam_info_for_c_up(struct Camera* c, struct CameraData* cameraData) {
    vec3f_copy(cameraData->sCameraStoreCUp.pos, c->pos);
    vec3f_sub(cameraData->sCameraStoreCUp.pos, cameraData->sMarioCamState->pos);
    // Only store the y value, and as an offset from Mario, for some reason
    vec3f_set(cameraData->sCameraStoreCUp.focus, 0.f, c->focus[1] - cameraData->sMarioCamState->pos[1], 0.f);
}

/**
 * Start C-Up mode. The actual mode change is handled in update_mario_inputs() in mario.c
 *
 * @see update_mario_inputs
 */
s32 set_mode_c_up(struct Camera* c, struct CameraData* cameraData) {
    if (!(cameraData->gCameraMovementFlags & CAM_MOVE_C_UP_MODE)) {
        cameraData->gCameraMovementFlags |= CAM_MOVE_C_UP_MODE;
        store_lakitu_cam_info_for_c_up(c, cameraData);
        return 1;
    }
    return 0;
}

/**
 * Zoom the camera out of C-Up mode, avoiding moving into a wall, if possible, by searching for an open
 * direction.
 */
s32 exit_c_up(struct Camera* c, struct CameraData* cameraData) {
    struct Surface* surface;
    Vec3f checkFoc;
    Vec3f curPos;
    // Variables for searching for an open direction
    s32 searching = 0;
    /// The current sector of the circle that we are checking
    s32 sector;
    f32 ceilHeight;
    f32 floorHeight;
    f32 curDist;
    f32 d;
    s16 curPitch;
    s16 curYaw;
    s16 checkYaw = 0;
    Vec3f storePos; // unused
    Vec3f storeFoc; // unused

    if ((cameraData->gCameraMovementFlags & CAM_MOVE_C_UP_MODE) && !(cameraData->gCameraMovementFlags & CAM_MOVE_STARTED_EXITING_C_UP)) {
        // Copy the stored pos and focus. This is unused.
        vec3f_copy(storePos, cameraData->sCameraStoreCUp.pos);
        vec3f_add(storePos, cameraData->sMarioCamState->pos);
        vec3f_copy(storeFoc, cameraData->sCameraStoreCUp.focus);
        vec3f_add(storeFoc, cameraData->sMarioCamState->pos);

        vec3f_copy(checkFoc, c->focus);
        checkFoc[0] = cameraData->sMarioCamState->pos[0];
        checkFoc[2] = cameraData->sMarioCamState->pos[2];
        vec3f_get_dist_and_angle(checkFoc, c->pos, &curDist, &curPitch, &curYaw);
        vec3f_copy(curPos, c->pos);
        curDist = 80.f;


        // Let the next camera mode handle it
        cameraData->gCameraMovementFlags &= ~(CAM_MOVE_STARTED_EXITING_C_UP | CAM_MOVE_C_UP_MODE);
        vec3f_set_dist_and_angle(checkFoc, c->pos, curDist, curPitch, curYaw + checkYaw);
    }
    return 0;
}

/**
 * The mode used when C-Up is pressed.
 */
s32 update_c_up(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, Vec3f focus, Vec3f pos) {
    s16 pitch = cameraData->sCUpCameraPitch;
    s16 yaw = cameraData->sMarioCamState->faceAngle[1] + cameraData->sModeOffsetYaw + DEGREES(180);

    focus_on_mario(cameraData, focus, pos, 125.f, 125.f, 250.f, pitch, yaw);
    return cameraData->sMarioCamState->faceAngle[1];
}

/**
 * Make Mario's head move in C-Up mode.
 */
void move_mario_head_c_up(UNUSED struct Camera* c, struct CameraData* cameraData, struct Controller* gPlayer1Controller) {
    cameraData->sCUpCameraPitch += (s16)(gPlayer1Controller->stickY * 10.f);
    cameraData->sModeOffsetYaw -= (s16)(gPlayer1Controller->stickX * 10.f);

    // Bound looking up to nearly 80 degrees.
    if (cameraData->sCUpCameraPitch > 0x38E3) {
        cameraData->sCUpCameraPitch = 0x38E3;
    }
    // Bound looking down to -45 degrees
    if (cameraData->sCUpCameraPitch < -0x2000) {
        cameraData->sCUpCameraPitch = -0x2000;
    }

    // Bound the camera yaw to +-120 degrees
    if (cameraData->sModeOffsetYaw > 0x5555) {
        cameraData->sModeOffsetYaw = 0x5555;
    }
    if (cameraData->sModeOffsetYaw < -0x5555) {
        cameraData->sModeOffsetYaw = -0x5555;
    }

    // Give Mario's neck natural-looking constraints
    cameraData->sMarioCamState->headRotation[0] = cameraData->sCUpCameraPitch * 3 / 4;
    cameraData->sMarioCamState->headRotation[1] = cameraData->sModeOffsetYaw * 3 / 4;
}

/**
 * Zooms the camera in for C-Up mode
 */
void move_into_c_up(struct Camera* c, struct CameraData* cameraData) {
    struct LinearTransitionPoint* start = &(cameraData->sModeInfo.transitionStart);
    struct LinearTransitionPoint* end = &(cameraData->sModeInfo.transitionEnd);

    f32 dist = end->dist - start->dist;
    s16 pitch = end->pitch - start->pitch;
    s16 yaw = end->yaw - start->yaw;

    // Linearly interpolate from start to end position's polar coordinates
    dist = start->dist + dist * cameraData->sModeInfo.frame / cameraData->sModeInfo.max;
    pitch = start->pitch + pitch * cameraData->sModeInfo.frame / cameraData->sModeInfo.max;
    yaw = start->yaw + yaw * cameraData->sModeInfo.frame / cameraData->sModeInfo.max;

    // Linearly interpolate the focus from start to end
    c->focus[0] = start->focus[0] + (end->focus[0] - start->focus[0]) * cameraData->sModeInfo.frame / cameraData->sModeInfo.max;
    c->focus[1] = start->focus[1] + (end->focus[1] - start->focus[1]) * cameraData->sModeInfo.frame / cameraData->sModeInfo.max;
    c->focus[2] = start->focus[2] + (end->focus[2] - start->focus[2]) * cameraData->sModeInfo.frame / cameraData->sModeInfo.max;

    vec3f_add(c->focus, cameraData->sMarioCamState->pos);
    vec3f_set_dist_and_angle(c->focus, c->pos, dist, pitch, yaw);

    cameraData->sMarioCamState->headRotation[0] = 0;
    cameraData->sMarioCamState->headRotation[1] = 0;

    // Finished zooming in
    if (++cameraData->sModeInfo.frame == cameraData->sModeInfo.max) {
        cameraData->gCameraMovementFlags &= ~CAM_MOVING_INTO_MODE;
    }
}

/**
 * The main update function for C-Up mode
 */
s32 mode_c_up_camera(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, struct Controller* gPlayer1Controller) {
    // Zoom in first
    if (cameraData->gCameraMovementFlags & CAM_MOVING_INTO_MODE) {
        cameraData->gCameraMovementFlags |= CAM_MOVE_C_UP_MODE;
        move_into_c_up(c, cameraData);
        return 1;
    }

    if (!(cameraData->gCameraMovementFlags & CAM_MOVE_STARTED_EXITING_C_UP)) {
        // Normal update
        move_mario_head_c_up(c, cameraData, gPlayer1Controller);
        update_c_up(c, cameraData, surfaceLists, c->focus, c->pos);
    }
    else {
        // Exiting C-Up
        if (cameraData->sStatusFlags & CAM_FLAG_TRANSITION_OUT_OF_C_UP) {
            // Retrieve the previous position and focus
            vec3f_copy(c->pos, cameraData->sCameraStoreCUp.pos);
            vec3f_add(c->pos, cameraData->sMarioCamState->pos);
            vec3f_copy(c->focus, cameraData->sCameraStoreCUp.focus);
            vec3f_add(c->focus, cameraData->sMarioCamState->pos);
            // Make Mario look forward
            camera_approach_s16_symmetric_bool(&(cameraData->sMarioCamState->headRotation[0]), 0, 1024);
            camera_approach_s16_symmetric_bool(&(cameraData->sMarioCamState->headRotation[1]), 0, 1024);
        }
        else {
            // Finished exiting C-Up
            cameraData->gCameraMovementFlags &= ~(CAM_MOVE_STARTED_EXITING_C_UP | CAM_MOVE_C_UP_MODE);
        }
    }
    cameraData->sPanDistance = 0.f;

    // Exit C-Up mode
    if (gPlayer1Controller->buttonPressed & (A_BUTTON | B_BUTTON | D_CBUTTONS | L_CBUTTONS | R_CBUTTONS)) {
        exit_c_up(c, cameraData);
    }
    return 0;
}

void set_camera_mode(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, s16 mode, s16 frames) {
    struct LinearTransitionPoint* start = &(cameraData->sModeInfo.transitionStart);
    struct LinearTransitionPoint* end = &(cameraData->sModeInfo.transitionEnd);

    // Clear movement flags that would affect the transition
    cameraData->gCameraMovementFlags &= (u16)~(CAM_MOVE_RESTRICT | CAM_MOVE_ROTATE);
    cameraData->gCameraMovementFlags |= CAM_MOVING_INTO_MODE;
    if (mode == CAMERA_MODE_NONE) {
        mode = CAMERA_MODE_CLOSE;
    }
    cameraData->sCUpCameraPitch = 0;
    cameraData->sModeOffsetYaw = 0;
    cameraData->sLakituDist = 0;
    cameraData->sLakituPitch = 0;
    cameraData->sAreaYawChange = 0;

    cameraData->sModeInfo.newMode = (mode != -1) ? mode : cameraData->sModeInfo.lastMode;
    cameraData->sModeInfo.lastMode = c->mode;
    cameraData->sModeInfo.max = frames;
    cameraData->sModeInfo.frame = 1;

    c->mode = cameraData->sModeInfo.newMode;
    cameraData->gLakituState.mode = c->mode;

    vec3f_copy(end->focus, c->focus);
    vec3f_sub(end->focus, cameraData->sMarioCamState->pos);

    vec3f_copy(end->pos, c->pos);
    vec3f_sub(end->pos, cameraData->sMarioCamState->pos);

    cameraData->sAreaYaw = sModeTransitions[cameraData->sModeInfo.newMode](c, cameraData, surfaceLists, end->focus, end->pos);

    // End was updated by sModeTransitions
    vec3f_sub(end->focus, cameraData->sMarioCamState->pos);
    vec3f_sub(end->pos, cameraData->sMarioCamState->pos);

    vec3f_copy(start->focus, cameraData->gLakituState.curFocus);
    vec3f_sub(start->focus, cameraData->sMarioCamState->pos);

    vec3f_copy(start->pos, cameraData->gLakituState.curPos);
    vec3f_sub(start->pos, cameraData->sMarioCamState->pos);

    vec3f_get_dist_and_angle(start->focus, start->pos, &start->dist, &start->pitch, &start->yaw);
    vec3f_get_dist_and_angle(end->focus, end->pos, &end->dist, &end->pitch, &end->yaw);
}

/**
 * Updates Lakitu's position/focus and applies camera shakes.
 */
void update_lakitu(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    struct Surface* floor = NULL;
    Vec3f newPos;
    Vec3f newFoc;
    f32 distToFloor;
    s16 newYaw;

    if (cameraData->gCameraMovementFlags & CAM_MOVE_PAUSE_SCREEN) {
    }
    else {
        if (TRUE) {
            newYaw = next_lakitu_state(cameraData, surfaceLists, newPos, newFoc, c->pos, c->focus, cameraData->sOldPosition, cameraData->sOldFocus,
                c->nextYaw);
            set_or_approach_s16_symmetric(cameraData, &c->yaw, newYaw, cameraData->sYawSpeed);
            cameraData->sStatusFlags &= ~CAM_FLAG_UNUSED_CUTSCENE_ACTIVE;
        }
        else {
            //! dead code, moved to next_lakitu_state()
            vec3f_copy(newPos, c->pos);
            vec3f_copy(newFoc, c->focus);
        }

        // Update old state
        vec3f_copy(cameraData->sOldPosition, newPos);
        vec3f_copy(cameraData->sOldFocus, newFoc);

        cameraData->gLakituState.yaw = c->yaw;
        cameraData->gLakituState.nextYaw = c->nextYaw;
        vec3f_copy(cameraData->gLakituState.goalPos, c->pos);
        vec3f_copy(cameraData->gLakituState.goalFocus, c->focus);

        // Simulate Lakitu flying to the new position and turning towards the new focus
        set_or_approach_vec3f_asymptotic(cameraData, cameraData->gLakituState.curPos, newPos,
            cameraData->gLakituState.posHSpeed, cameraData->gLakituState.posVSpeed,
            cameraData->gLakituState.posHSpeed);
        set_or_approach_vec3f_asymptotic(cameraData, cameraData->gLakituState.curFocus, newFoc,
            cameraData->gLakituState.focHSpeed, cameraData->gLakituState.focVSpeed,
            cameraData->gLakituState.focHSpeed);
        // Adjust Lakitu's speed back to normal
        set_or_approach_f32_asymptotic(cameraData, &(cameraData->gLakituState.focHSpeed), 0.8f, 0.05f);
        set_or_approach_f32_asymptotic(cameraData, &(cameraData->gLakituState.focVSpeed), 0.3f, 0.05f);
        set_or_approach_f32_asymptotic(cameraData, &(cameraData->gLakituState.posHSpeed), 0.3f, 0.05f);
        set_or_approach_f32_asymptotic(cameraData, &(cameraData->gLakituState.posVSpeed), 0.3f, 0.05f);

        // Turn on smooth movement when it hasn't been blocked for 2 frames
        if (cameraData->sStatusFlags & CAM_FLAG_BLOCK_SMOOTH_MOVEMENT) {
            cameraData->sStatusFlags &= ~CAM_FLAG_BLOCK_SMOOTH_MOVEMENT;
        }
        else {
            cameraData->sStatusFlags |= CAM_FLAG_SMOOTH_MOVEMENT;
        }

        vec3f_copy(cameraData->gLakituState.pos, cameraData->gLakituState.curPos);
        vec3f_copy(cameraData->gLakituState.focus, cameraData->gLakituState.curFocus);

        vec3f_get_dist_and_angle(cameraData->gLakituState.pos, cameraData->gLakituState.focus, &(cameraData->gLakituState.focusDistance),
            &(cameraData->gLakituState.oldPitch), &(cameraData->gLakituState.oldYaw));

        cameraData->gLakituState.roll = 0;

        if (cameraData->sMarioCamState->action == ACT_DIVE && cameraData->gLakituState.lastFrameAction != ACT_DIVE) {
            cameraData->gLakituState.focHSpeed = 0.07;
            cameraData->gLakituState.posHSpeed = 0.07;
        }


        if (c->mode != CAMERA_MODE_C_UP && c->cutscene == 0) {
            distToFloor = find_floor(surfaceLists, cameraData->gLakituState.pos[0],
                cameraData->gLakituState.pos[1] + 20.0f,
                cameraData->gLakituState.pos[2], &floor);
            if (distToFloor != FLOOR_LOWER_LIMIT) {
                if (cameraData->gLakituState.pos[1] < (distToFloor += 100.0f)) {
                    cameraData->gLakituState.pos[1] = distToFloor;
                }
            }
        }

        vec3f_copy(cameraData->sModeTransition.marioPos, cameraData->sMarioCamState->pos);
    }
    clamp_pitch(cameraData->gLakituState.pos, cameraData->gLakituState.focus, 0x3E00, -0x3E00);
    cameraData->gLakituState.mode = c->mode;
    cameraData->gLakituState.defMode = c->defMode;
}


/**
 * The main camera update function.
 * Gets controller input, checks for cutscenes, handles mode changes, and moves the camera
 */
void update_camera(struct Camera* c, struct CameraData* cameraData, struct MarioState* m, struct AreaData* areaData, struct Surfaces* surfaceLists, struct Controller* gPlayer1Controller) {
    cameraData->gCamera = c;

    if (c->cutscene == 0) {
        // Only process R_TRIG if 'fixed' is not selected in the menu
        if (cam_select_alt_mode(cameraData, 0) == CAM_SELECTION_MARIO) {
            if (gPlayer1Controller->buttonPressed & R_TRIG) {
                if (set_cam_angle(cameraData, 0) == CAM_ANGLE_LAKITU) {
                    set_cam_angle(cameraData, CAM_ANGLE_MARIO);
                }
                else {
                    set_cam_angle(cameraData, CAM_ANGLE_LAKITU);
                }
            }
        }
    }

    // Initialize the camera
    cameraData->sStatusFlags &= ~CAM_FLAG_FRAME_AFTER_CAM_INIT;
    if (cameraData->gCameraMovementFlags & CAM_MOVE_INIT_CAMERA) {
        init_camera(c, cameraData, areaData, surfaceLists);
        cameraData->gCameraMovementFlags &= ~CAM_MOVE_INIT_CAMERA;
        cameraData->sStatusFlags |= CAM_FLAG_FRAME_AFTER_CAM_INIT;
    }

    // Store previous geometry information
    cameraData->sMarioGeometry.prevFloorHeight = cameraData->sMarioGeometry.currFloorHeight;
    cameraData->sMarioGeometry.prevCeilHeight = cameraData->sMarioGeometry.currCeilHeight;
    cameraData->sMarioGeometry.prevFloor = cameraData->sMarioGeometry.currFloor;
    cameraData->sMarioGeometry.prevCeil = cameraData->sMarioGeometry.currCeil;
    cameraData->sMarioGeometry.prevFloorType = cameraData->sMarioGeometry.currFloorType;
    cameraData->sMarioGeometry.prevCeilType = cameraData->sMarioGeometry.currCeilType;

    find_mario_floor_and_ceil(&(cameraData->sMarioGeometry), cameraData, surfaceLists);
    vec3f_copy(c->pos, cameraData->gLakituState.goalPos);
    vec3f_copy(c->focus, cameraData->gLakituState.goalFocus);

    c->yaw = cameraData->gLakituState.yaw;
    c->nextYaw = cameraData->gLakituState.nextYaw;
    c->mode = cameraData->gLakituState.mode;
    c->defMode = cameraData->gLakituState.defMode;

    camera_course_processing(c, cameraData, areaData);
    cameraData->sCButtonsPressed = find_c_buttons_pressed(cameraData->sCButtonsPressed, gPlayer1Controller->buttonPressed,
    gPlayer1Controller->buttonDown);

    cameraData->sYawSpeed = 0x400;

    if (cameraData->sSelectionFlags & CAM_MODE_MARIO_ACTIVE) {
        switch (c->mode) {
        case CAMERA_MODE_C_UP:
            mode_c_up_camera(c, cameraData, surfaceLists, gPlayer1Controller);
            break;

        default:
            mode_mario_camera(c, cameraData, m, surfaceLists, gPlayer1Controller);
        }
    }
    else {
        switch (c->mode) {
        case CAMERA_MODE_C_UP:
            mode_c_up_camera(c, cameraData, surfaceLists, gPlayer1Controller);
            break;

        case CAMERA_MODE_8_DIRECTIONS:
            mode_8_directions_camera(c, cameraData, surfaceLists, gPlayer1Controller);
            break;
        }
    }

    // If fixed camera is selected as the alternate mode, then fix the camera as long as the right
    // trigger is held
    if (((gPlayer1Controller->buttonDown & R_TRIG) && cam_select_alt_mode(cameraData, 0) == CAM_SELECTION_FIXED)
        || (cameraData->gCameraMovementFlags & CAM_MOVE_FIX_IN_PLACE)) {

        // Fixed mode only prevents Lakitu from moving. The camera pos still updates, so
        // Lakitu will fly to his next position as normal whenever R_TRIG is released.
        cameraData->gLakituState.posHSpeed = 0.f;
        cameraData->gLakituState.posVSpeed = 0.f;

        c->nextYaw = calculate_yaw(cameraData->gLakituState.focus, cameraData->gLakituState.pos);
        c->yaw = c->nextYaw;
        cameraData->gCameraMovementFlags &= ~CAM_MOVE_FIX_IN_PLACE;
    }

    update_lakitu(c, cameraData, surfaceLists);

    cameraData->gLakituState.lastFrameAction = cameraData->sMarioCamState->action;
}

/**
 * Reset all the camera variables to their arcane defaults
 */
void reset_camera(struct Camera* c, struct CameraData* cameraData) {
    cameraData->gCamera = c;
    cameraData->gCameraMovementFlags = 0;
    cameraData->sStatusFlags = 0;
    cameraData->sCButtonsPressed = 0;
    vec3f_copy(cameraData->sModeTransition.marioPos, cameraData->sMarioCamState->pos);
    cameraData->sModeTransition.framesLeft = 0;
    cameraData->gCameraMovementFlags = 0;
    cameraData->gCameraMovementFlags |= CAM_MOVE_INIT_CAMERA;
    cameraData->sStatusFlags = 0;
    cameraData->sCUpCameraPitch = 0;
    cameraData->sModeOffsetYaw = 0;
    cameraData->sLakituDist = 0;
    cameraData->sLakituPitch = 0;
    cameraData->sAreaYaw = 0;
    cameraData->sPanDistance = 0.f;
    cameraData->sZoomAmount = 0.f;
    cameraData->sCSideButtonYaw = 0;
    cameraData->s8DirModeBaseYaw = 0;
    cameraData->s8DirModeYawOffset = 0;
    cameraData->sMarioCamState->headRotation[0] = 0;
    cameraData->sMarioCamState->headRotation[1] = 0;
    cameraData->sLuigiCamState->headRotation[0] = 0;
    cameraData->sLuigiCamState->headRotation[1] = 0;
    cameraData->sMarioCamState->cameraEvent = 0;
    cameraData->sMarioCamState->usedObj = NULL;
    cameraData->gLakituState.shakeMagnitude[0] = 0;
    cameraData->gLakituState.shakeMagnitude[1] = 0;
    cameraData->gLakituState.shakeMagnitude[2] = 0;
    cameraData->gLakituState.lastFrameAction = 0;
}

void init_camera(struct Camera* c, struct CameraData* cameraData, struct AreaData* areaData, struct Surfaces* surfaceLists) {
    struct Surface* floor = 0;
    Vec3f marioOffset;
    s32 i;

    areaData->gPrevLevel = areaData->gCurrLevelArea / 16;
    areaData->gCurrLevelArea = areaData->gCurrLevelNum * 16 + areaData->gCurrentArea->index;
    cameraData->sSelectionFlags &= CAM_MODE_MARIO_SELECTED;
    cameraData->gLakituState.mode = c->mode;
    cameraData->gLakituState.defMode = c->defMode;
    cameraData->gLakituState.posHSpeed = 0.3f;
    cameraData->gLakituState.posVSpeed = 0.3f;
    cameraData->gLakituState.focHSpeed = 0.8f;
    cameraData->gLakituState.focHSpeed = 0.3f; // @bug set focHSpeed back-to-back
    cameraData->gLakituState.roll = 0;
    cameraData->gLakituState.keyDanceRoll = 0;
    cameraData->gLakituState.unused = 0;
    cameraData->sStatusFlags &= ~CAM_FLAG_SMOOTH_MOVEMENT;
    find_mario_floor_and_ceil(&(cameraData->sMarioGeometry), cameraData, surfaceLists);
    cameraData->sMarioGeometry.prevFloorHeight = cameraData->sMarioGeometry.currFloorHeight;
    cameraData->sMarioGeometry.prevCeilHeight = cameraData->sMarioGeometry.currCeilHeight;
    cameraData->sMarioGeometry.prevFloor = cameraData->sMarioGeometry.currFloor;
    cameraData->sMarioGeometry.prevCeil = cameraData->sMarioGeometry.currCeil;
    cameraData->sMarioGeometry.prevFloorType = cameraData->sMarioGeometry.currFloorType;
    cameraData->sMarioGeometry.prevCeilType = cameraData->sMarioGeometry.currCeilType;
    marioOffset[0] = 0.f;
    marioOffset[1] = 125.f;
    marioOffset[2] = 400.f;

    if (c->mode == CAMERA_MODE_8_DIRECTIONS) {
        cameraData->gCameraMovementFlags |= CAM_MOVE_ZOOMED_OUT;
    }

    // Set the camera pos to marioOffset (relative to Mario), added to Mario's position
    offset_rotated(c->pos, cameraData->sMarioCamState->pos, marioOffset, cameraData->sMarioCamState->faceAngle);
    if (c->mode != CAMERA_MODE_BEHIND_MARIO) {
        c->pos[1] = find_floor(surfaceLists, cameraData->sMarioCamState->pos[0], cameraData->sMarioCamState->pos[1] + 100.f,
            cameraData->sMarioCamState->pos[2], &floor) + 125.f;
    }
    vec3f_copy(c->focus, cameraData->sMarioCamState->pos);
    vec3f_copy(cameraData->gLakituState.curPos, c->pos);
    vec3f_copy(cameraData->gLakituState.curFocus, c->focus);
    vec3f_copy(cameraData->gLakituState.goalPos, c->pos);
    vec3f_copy(cameraData->gLakituState.goalFocus, c->focus);
    vec3f_copy(cameraData->gLakituState.pos, c->pos);
    vec3f_copy(cameraData->gLakituState.focus, c->focus);
    store_lakitu_cam_info_for_c_up(c, cameraData);
    cameraData->gLakituState.yaw = calculate_yaw(c->focus, c->pos);
    cameraData->gLakituState.nextYaw = cameraData->gLakituState.yaw;
    c->yaw = cameraData->gLakituState.yaw;
    c->nextYaw = cameraData->gLakituState.yaw;
}

void vec3f_sub(Vec3f dst, Vec3f src) {
    dst[0] -= src[0];
    dst[1] -= src[1];
    dst[2] -= src[2];
}

/**
 * If `selection` is 0, just get the current selection
 * If `selection` is 1, select 'Mario' as the alt mode.
 * If `selection` is 2, select 'fixed' as the alt mode.
 *
 * @return the current selection
 */
s32 cam_select_alt_mode(struct CameraData* cameraData, s32 selection) {
    s32 mode = CAM_SELECTION_FIXED;

    if (selection == CAM_SELECTION_MARIO) {
        if (!(cameraData->sSelectionFlags & CAM_MODE_MARIO_SELECTED)) {
            cameraData->sSelectionFlags |= CAM_MODE_MARIO_SELECTED;
        }
    }

    // The alternate mode is up-close, but the player just selected fixed in the pause menu
    if (selection == CAM_SELECTION_FIXED && (cameraData->sSelectionFlags & CAM_MODE_MARIO_SELECTED)) {
        // So change to normal mode in case the user paused in up-close mode
        set_cam_angle(cameraData, CAM_ANGLE_LAKITU);
        cameraData->sSelectionFlags &= ~CAM_MODE_MARIO_SELECTED;
    }

    if (cameraData->sSelectionFlags & CAM_MODE_MARIO_SELECTED) {
        mode = CAM_SELECTION_MARIO;
    }
    return mode;
}

/**
 * Sets the camera angle to either Lakitu or Mario mode. Returns the current mode.
 *
 * If `mode` is 0, just returns the current mode.
 * If `mode` is 1, start Mario mode
 * If `mode` is 2, start Lakitu mode
 */
s32 set_cam_angle(struct CameraData* cameraData, s32 mode) {
    s32 curMode = CAM_ANGLE_LAKITU;

    // Switch to Mario mode
    if (mode == CAM_ANGLE_MARIO && !(cameraData->sSelectionFlags & CAM_MODE_MARIO_ACTIVE)) {
        cameraData->sSelectionFlags |= CAM_MODE_MARIO_ACTIVE;
        if (cameraData->gCameraMovementFlags & CAM_MOVE_ZOOMED_OUT) {
            cameraData->sSelectionFlags |= CAM_MODE_LAKITU_WAS_ZOOMED_OUT;
            cameraData->gCameraMovementFlags &= ~CAM_MOVE_ZOOMED_OUT;
        }
    }

    // Switch back to normal mode
    if (mode == CAM_ANGLE_LAKITU && (cameraData->sSelectionFlags & CAM_MODE_MARIO_ACTIVE)) {
        cameraData->sSelectionFlags &= ~CAM_MODE_MARIO_ACTIVE;
        if (cameraData->sSelectionFlags & CAM_MODE_LAKITU_WAS_ZOOMED_OUT) {
            cameraData->sSelectionFlags &= ~CAM_MODE_LAKITU_WAS_ZOOMED_OUT;
            cameraData->gCameraMovementFlags |= CAM_MOVE_ZOOMED_OUT;
        }
        else {
            cameraData->gCameraMovementFlags &= ~CAM_MOVE_ZOOMED_OUT;
        }
    }
    if (cameraData->sSelectionFlags & CAM_MODE_MARIO_ACTIVE) {
        curMode = CAM_ANGLE_MARIO;
    }
    return curMode;
}

/**
 * Updates C Button input state and stores it in `currentState`
 */
s32 find_c_buttons_pressed(u16 currentState, u16 buttonsPressed, u16 buttonsDown) {
    buttonsPressed &= CBUTTON_MASK;
    buttonsDown &= CBUTTON_MASK;

    if (buttonsPressed & L_CBUTTONS) {
        currentState |= L_CBUTTONS;
        currentState &= ~R_CBUTTONS;
    }
    if (!(buttonsDown & L_CBUTTONS)) {
        currentState &= ~L_CBUTTONS;
    }

    if (buttonsPressed & R_CBUTTONS) {
        currentState |= R_CBUTTONS;
        currentState &= ~L_CBUTTONS;
    }
    if (!(buttonsDown & R_CBUTTONS)) {
        currentState &= ~R_CBUTTONS;
    }

    if (buttonsPressed & U_CBUTTONS) {
        currentState |= U_CBUTTONS;
        currentState &= ~D_CBUTTONS;
    }
    if (!(buttonsDown & U_CBUTTONS)) {
        currentState &= ~U_CBUTTONS;
    }

    if (buttonsPressed & D_CBUTTONS) {
        currentState |= D_CBUTTONS;
        currentState &= ~U_CBUTTONS;
    }
    if (!(buttonsDown & D_CBUTTONS)) {
        currentState &= ~D_CBUTTONS;
    }

    return currentState;
}

/**
 * Check `pos` for collisions within `radius`, and update `pos`
 *
 * @return the number of collisions found
 */
s32 collide_with_walls(struct Surfaces* surfaceLists, Vec3f pos, f32 offsetY, f32 radius) {
    struct WallCollisionData collisionData;
    struct Surface* wall = NULL;
    f32 normX;
    f32 normY;
    f32 normZ;
    f32 originOffset;
    f32 offset;
    f32 offsetAbsolute;
    Vec3f newPos[4];
    s32 i;
    s32 numCollisions = 0;

    collisionData.x = pos[0];
    collisionData.y = pos[1];
    collisionData.z = pos[2];
    collisionData.radius = radius;
    collisionData.offsetY = offsetY;
    numCollisions = find_wall_collisions(surfaceLists, &collisionData);
    if (numCollisions != 0) {
        for (i = 0; i < collisionData.numWalls; i++) {
            wall = collisionData.walls[collisionData.numWalls - 1];
            vec3f_copy(newPos[i], pos);
            normX = wall->normal.x;
            normY = wall->normal.y;
            normZ = wall->normal.z;
            originOffset = wall->originOffset;
            offset = normX * newPos[i][0] + normY * newPos[i][1] + normZ * newPos[i][2] + originOffset;
            offsetAbsolute = ABS2(offset);
            if (offsetAbsolute < radius) {
                newPos[i][0] += normX * (radius - offset);
                newPos[i][2] += normZ * (radius - offset);
                vec3f_copy(pos, newPos[i]);
            }
        }
    }
    return numCollisions;
}

s32 clamp_pitch(Vec3f from, Vec3f to, s16 maxPitch, s16 minPitch) {
    s32 outOfRange = 0;
    s16 pitch;
    s16 yaw;
    f32 dist;

    vec3f_get_dist_and_angle(from, to, &dist, &pitch, &yaw);
    if (pitch > maxPitch) {
        pitch = maxPitch;
        outOfRange++;
    }
    if (pitch < minPitch) {
        pitch = minPitch;
        outOfRange++;
    }
    vec3f_set_dist_and_angle(from, to, dist, pitch, yaw);
    return outOfRange;
}

s32 set_or_approach_f32_asymptotic(struct CameraData* cameraData, f32* dst, f32 goal, f32 scale) {
    if (cameraData->sStatusFlags & CAM_FLAG_SMOOTH_MOVEMENT) {
        approach_f32_asymptotic_bool(dst, goal, scale);
    }
    else {
        *dst = goal;
    }
    if (*dst == goal) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

/**
 * Approaches an f32 value by taking the difference between the target and current value
 * and adding a fraction of that to the current value.
 * Edits the current value directly, returns TRUE if the target has been reached, FALSE otherwise.
 */
s32 approach_f32_asymptotic_bool(f32* current, f32 target, f32 multiplier) {
    if (multiplier > 1.f) {
        multiplier = 1.f;
    }
    *current = *current + (target - *current) * multiplier;
    if (*current == target) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

/**
 * Approaches an s16 value in the same fashion as approach_f32_asymptotic_bool, returns TRUE if target
 * is reached. Note: Since this function takes integers as parameters, the last argument is the
 * reciprocal of what it would be in the previous two functions.
 */
s32 approach_s16_asymptotic_bool(s16* current, s16 target, s16 divisor) {
    s16 temp = *current;

    if (divisor == 0) {
        *current = target;
    }
    else {
        temp -= target;
        temp -= temp / divisor;
        temp += target;
        *current = temp;
    }
    if (*current == target) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

/**
 * Applies the set_or_approach_f32_asymptotic_bool function to each of the X, Y, & Z components of the
 * given vector.
 */
void set_or_approach_vec3f_asymptotic(struct CameraData* cameraData, Vec3f dst, Vec3f goal, f32 xMul, f32 yMul, f32 zMul) {
    set_or_approach_f32_asymptotic(cameraData, &dst[0], goal[0], xMul);
    set_or_approach_f32_asymptotic(cameraData, &dst[1], goal[1], yMul);
    set_or_approach_f32_asymptotic(cameraData, &dst[2], goal[2], zMul);
}

s32 camera_approach_s16_symmetric_bool(s16* current, s16 target, s16 increment) {
    s16 dist = target - *current;

    if (increment < 0) {
        increment = -1 * increment;
    }
    if (dist > 0) {
        dist -= increment;
        if (dist >= 0) {
            *current = target - dist;
        }
        else {
            *current = target;
        }
    }
    else {
        dist += increment;
        if (dist <= 0) {
            *current = target - dist;
        }
        else {
            *current = target;
        }
    }
    if (*current == target) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

s32 set_or_approach_s16_symmetric(struct CameraData* cameraData, s16* current, s16 target, s16 increment) {
    if (cameraData->sStatusFlags & CAM_FLAG_SMOOTH_MOVEMENT) {
        camera_approach_s16_symmetric_bool(current, target, increment);
    }
    else {
        *current = target;
    }
    if (*current == target) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

/**
 * Approaches a value by a given increment, returns FALSE if the target is reached.
 * Appears to be a strange way of implementing approach_f32_symmetric from object_helpers.c.
 * It could possibly be an older version of the function
 */
s32 camera_approach_f32_symmetric_bool(f32* current, f32 target, f32 increment) {
    f32 dist = target - *current;

    if (increment < 0) {
        increment = -1 * increment;
    }
    if (dist > 0) {
        dist -= increment;
        if (dist > 0) {
            *current = target - dist;
        }
        else {
            *current = target;
        }
    }
    else {
        dist += increment;
        if (dist < 0) {
            *current = target - dist;
        }
        else {
            *current = target;
        }
    }
    if (*current == target) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

/**
 * The yaw passed here is the yaw of the direction FROM Mario TO Lakitu.
 *
 * wallYaw always has 90 degrees added to it before this is called -- it's parallel to the wall.
 *
 * @return the new yaw from Mario to rotate towards.
 *
 * @warning this is jank. It actually returns the yaw that will rotate further INTO the wall. So, the
 *          developers just add 180 degrees to the result.
 */
s32 calc_avoid_yaw(s16 yawFromMario, s16 wallYaw) {
    s16 yawDiff;

    yawDiff = wallYaw - yawFromMario + DEGREES(90);

    if (yawDiff < 0) {
        // Deflect to the right
        yawFromMario = wallYaw;
    }
    else {
        // Note: this favors the left side if the wall is exactly perpendicular to the camera.
        // Deflect to the left
        yawFromMario = wallYaw + DEGREES(180);
    }
    return yawFromMario;
}

/**
 * Checks if `surf` is within the rect prism defined by xMax, yMax, and zMax
 *
 * @param surf surface to check
 * @param xMax absolute-value max size in x, set to -1 to ignore
 * @param yMax absolute-value max size in y, set to -1 to ignore
 * @param zMax absolute-value max size in z, set to -1 to ignore
 */
s32 is_surf_within_bounding_box(struct Surface* surf, f32 xMax, f32 yMax, f32 zMax) {
    // Surface vertex coordinates
    Vec3s sx;
    Vec3s sy;
    Vec3s sz;
    // Max delta between x, y, and z
    s16 dxMax = 0;
    s16 dyMax = 0;
    s16 dzMax = 0;
    // Current deltas between x, y, and z
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;
    s32 j;
    // result
    s32 smaller = FALSE;

    sx[0] = surf->vertex1[0];
    sx[1] = surf->vertex2[0];
    sx[2] = surf->vertex3[0];
    sy[0] = surf->vertex1[1];
    sy[1] = surf->vertex2[1];
    sy[2] = surf->vertex3[1];
    sz[0] = surf->vertex1[2];
    sz[1] = surf->vertex2[2];
    sz[2] = surf->vertex3[2];

    for (i = 0; i < 3; i++) {
        j = i + 1;
        if (j >= 3) {
            j = 0;
        }
        dx = ABS(sx[i] - sx[j]);
        if (dx > dxMax) {
            dxMax = dx;
        }
        dy = ABS(sy[i] - sy[j]);
        if (dy > dyMax) {
            dyMax = dy;
        }
        dz = ABS(sz[i] - sz[j]);
        if (dz > dzMax) {
            dzMax = dz;
        }
    }
    if (yMax != -1.f) {
        if (dyMax < yMax) {
            smaller = TRUE;
        }
    }
    if (xMax != -1.f && zMax != -1.f) {
        if (dxMax < xMax && dzMax < zMax) {
            smaller = TRUE;
        }
    }
    return smaller;
}

/**
 * Checks if `pos` is behind the surface, using the dot product.
 *
 * Because the function only uses `surf`s first vertex, some surfaces can shadow others.
 */
s32 is_behind_surface(Vec3f pos, struct Surface* surf) {
    s32 behindSurface = 0;
    // Surface normal
    f32 normX = (surf->vertex2[1] - surf->vertex1[1]) * (surf->vertex3[2] - surf->vertex2[2]) -
        (surf->vertex3[1] - surf->vertex2[1]) * (surf->vertex2[2] - surf->vertex1[2]);
    f32 normY = (surf->vertex2[2] - surf->vertex1[2]) * (surf->vertex3[0] - surf->vertex2[0]) -
        (surf->vertex3[2] - surf->vertex2[2]) * (surf->vertex2[0] - surf->vertex1[0]);
    f32 normZ = (surf->vertex2[0] - surf->vertex1[0]) * (surf->vertex3[1] - surf->vertex2[1]) -
        (surf->vertex3[0] - surf->vertex2[0]) * (surf->vertex2[1] - surf->vertex1[1]);
    f32 dirX = surf->vertex1[0] - pos[0];
    f32 dirY = surf->vertex1[1] - pos[1];
    f32 dirZ = surf->vertex1[2] - pos[2];

    if (dirX * normX + dirY * normY + dirZ * normZ < 0) {
        behindSurface = 1;
    }
    return behindSurface;
}

/**
 * Checks if the whole circular sector is behind the surface.
 */
s32 is_range_behind_surface(Vec3f from, Vec3f to, struct Surface* surf, s16 range, s16 surfType) {
    s32 behindSurface = TRUE;
    s32 leftBehind = 0;
    s32 rightBehind = 0;
    f32 checkDist;
    s16 checkPitch;
    s16 checkYaw;
    Vec3f checkPos;

    if (surf != NULL) {
        if (surfType == -1 || surf->type != surfType) {
            if (range == 0) {
                behindSurface = is_behind_surface(to, surf);
            }
            else {
                vec3f_get_dist_and_angle(from, to, &checkDist, &checkPitch, &checkYaw);
                vec3f_set_dist_and_angle(from, checkPos, checkDist, checkPitch, checkYaw + range);
                leftBehind = is_behind_surface(checkPos, surf);
                vec3f_set_dist_and_angle(from, checkPos, checkDist, checkPitch, checkYaw - range);
                rightBehind = is_behind_surface(checkPos, surf);
                behindSurface = leftBehind * rightBehind;
            }
        }
    }
    return behindSurface;
}

s32 is_mario_behind_surface(UNUSED struct Camera* c, struct CameraData* cameraData, struct Surface* surf) {
    s32 behindSurface = is_behind_surface(cameraData->sMarioCamState->pos, surf);

    return behindSurface;
}

/**
 * Calculates the distance between two points and sets a vector to a point
 * scaled along a line between them. Typically, somewhere in the middle.
 */
void scale_along_line(Vec3f dst, Vec3f from, Vec3f to, f32 scale) {
    Vec3f tempVec;

    tempVec[0] = (to[0] - from[0]) * scale + from[0];
    tempVec[1] = (to[1] - from[1]) * scale + from[1];
    tempVec[2] = (to[2] - from[2]) * scale + from[2];
    vec3f_copy(dst, tempVec);
}

s16 calculate_yaw(Vec3f from, Vec3f to) {
    f32 dx = to[0] - from[0];
    UNUSED f32 dy = to[1] - from[1];
    f32 dz = to[2] - from[2];
    s16 yaw = atan2s(dz, dx);

    return yaw;
}

/**
 * Finds the horizontal distance between two vectors.
 */
f32 calc_hor_dist(Vec3f a, Vec3f b) {
    f32 distX = b[0] - a[0];
    f32 distZ = b[2] - a[2];
    f32 distHor = sqrtf(distX * distX + distZ * distZ);

    return distHor;
}

/**
 * Rotates a vector in the horizontal plane and copies it to a new vector.
 */
void rotate_in_xz(Vec3f dst, Vec3f src, s16 yaw) {
    Vec3f tempVec;

    vec3f_copy(tempVec, src);
    dst[0] = tempVec[2] * sins(yaw) + tempVec[0] * coss(yaw);
    dst[1] = tempVec[1];
    dst[2] = tempVec[2] * coss(yaw) - tempVec[0] * sins(yaw);
}

/**
 * Handles input for radial, outwards radial, parallel tracking, and 8 direction mode.
 */
s32 radial_camera_input(struct Camera* c, struct CameraData* cameraData, struct Controller* gPlayer1Controller, UNUSED f32 unused) {
    s16 dummy = 0;

    if ((cameraData->gCameraMovementFlags & CAM_MOVE_ENTERED_ROTATE_SURFACE) || !(cameraData->gCameraMovementFlags & CAM_MOVE_ROTATE)) {

        // If C-L or C-R are pressed, the camera is rotating
        if (gPlayer1Controller->buttonPressed & (L_CBUTTONS | R_CBUTTONS)) {
            cameraData->gCameraMovementFlags &= ~CAM_MOVE_ENTERED_ROTATE_SURFACE;
            //  @bug this does not clear the rotation flags set by the surface. It's possible to set
            //       both ROTATE_LEFT and ROTATE_RIGHT, locking the camera.
            //       Ex: If a surface set CAM_MOVE_ROTATE_RIGHT and the user presses C-R, it locks the
            //       camera until a different mode is activated
        }

        // Rotate Right and left
        if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
            if (cameraData->sModeOffsetYaw > -0x800) {
                // The camera is now rotating right
                if (!(cameraData->gCameraMovementFlags & CAM_MOVE_ROTATE_RIGHT)) {
                    cameraData->gCameraMovementFlags |= CAM_MOVE_ROTATE_RIGHT;
                }
            }
            else {
                cameraData->gCameraMovementFlags |= CAM_MOVE_RETURN_TO_MIDDLE;
            }
        }
        if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
            if (cameraData->sModeOffsetYaw < 0x800) {
                if (!(cameraData->gCameraMovementFlags & CAM_MOVE_ROTATE_LEFT)) {
                    cameraData->gCameraMovementFlags |= CAM_MOVE_ROTATE_LEFT;
                }
            }
            else {
                cameraData->gCameraMovementFlags |= CAM_MOVE_RETURN_TO_MIDDLE;
            }
        }
    }

    // Zoom in / enter C-Up
    if (gPlayer1Controller->buttonPressed & U_CBUTTONS) {
        if (cameraData->gCameraMovementFlags & CAM_MOVE_ZOOMED_OUT) {
            cameraData->gCameraMovementFlags &= ~CAM_MOVE_ZOOMED_OUT;
        }
        else {
            set_mode_c_up(c, cameraData);
        }
    }

    // Zoom out
    if (gPlayer1Controller->buttonPressed & D_CBUTTONS) {
        if (cameraData->gCameraMovementFlags & CAM_MOVE_ZOOMED_OUT) {
            cameraData->gCameraMovementFlags |= CAM_MOVE_ALREADY_ZOOMED_OUT;
        }
        else {
            cameraData->gCameraMovementFlags |= CAM_MOVE_ZOOMED_OUT;
        }
    }

    //! returning uninitialized variable
    return dummy;
}


/**
 * Updates the camera based on which C buttons are pressed this frame
 */
void handle_c_button_movement(struct Camera* c, struct CameraData* cameraData, struct Controller* gPlayer1Controller) {
    s16 cSideYaw;

    // Zoom in
    if (gPlayer1Controller->buttonPressed & U_CBUTTONS) {
        if (c->mode != CAMERA_MODE_FIXED && (cameraData->gCameraMovementFlags & CAM_MOVE_ZOOMED_OUT)) {
            cameraData->gCameraMovementFlags &= ~CAM_MOVE_ZOOMED_OUT;
        }
        else {
            set_mode_c_up(c, cameraData);
            cameraData->sZoomAmount = cameraData->gCameraZoomDist;
        }
    }
    if (c->mode != CAMERA_MODE_FIXED) {
        // Zoom out
        if (gPlayer1Controller->buttonPressed & D_CBUTTONS) {
            if (cameraData->gCameraMovementFlags & CAM_MOVE_ZOOMED_OUT) {
                cameraData->gCameraMovementFlags |= CAM_MOVE_ALREADY_ZOOMED_OUT;
                cameraData->sZoomAmount = cameraData->gCameraZoomDist + 400.f;
            }
            else {
                cameraData->gCameraMovementFlags |= CAM_MOVE_ZOOMED_OUT;
                cameraData->sZoomAmount = cameraData->gCameraZoomDist + 400.f;
            }
        }

        // Rotate left or right
        cSideYaw = 0x1000;
        if (gPlayer1Controller->buttonPressed & R_CBUTTONS) {
            if (cameraData->gCameraMovementFlags & CAM_MOVE_ROTATE_LEFT) {
                cameraData->gCameraMovementFlags &= ~CAM_MOVE_ROTATE_LEFT;
            }
            else {
                cameraData->gCameraMovementFlags |= CAM_MOVE_ROTATE_RIGHT;
                cameraData->sCSideButtonYaw = -cSideYaw;
            }
        }
        if (gPlayer1Controller->buttonPressed & L_CBUTTONS) {
            if (cameraData->gCameraMovementFlags & CAM_MOVE_ROTATE_RIGHT) {
                cameraData->gCameraMovementFlags &= ~CAM_MOVE_ROTATE_RIGHT;
            }
            else {
                cameraData->gCameraMovementFlags |= CAM_MOVE_ROTATE_LEFT;
                cameraData->sCSideButtonYaw = cSideYaw;
            }
        }
    }
}

/**
 * Make the camera's y coordinate approach `goal`,
 * unless smooth movement is off, in which case the y coordinate is simply set to `goal`
 */
void approach_camera_height(struct Camera* c, struct CameraData* cameraData, f32 goal, f32 inc) {
    if (cameraData->sStatusFlags & CAM_FLAG_SMOOTH_MOVEMENT) {
        if (c->pos[1] < goal) {
            if ((c->pos[1] += inc) > goal) {
                c->pos[1] = goal;
            }
        }
        else {
            if ((c->pos[1] -= inc) < goal) {
                c->pos[1] = goal;
            }
        }
    }
    else {
        c->pos[1] = goal;
    }
}

/**
 * Rotates the offset `to` according to the pitch and yaw values in `rotation`.
 * Adds `from` to the rotated offset, and stores the result in `dst`.
 *
 * @warning Flips the Z axis, so that relative to `rotation`, -Z moves forwards and +Z moves backwards.
 */
void offset_rotated(Vec3f dst, Vec3f from, Vec3f to, Vec3s rotation) {
    Vec3f unusedCopy;
    Vec3f pitchRotated;

    vec3f_copy(unusedCopy, from);

    // First rotate the direction by rotation's pitch
    //! The Z axis is flipped here.
    pitchRotated[2] = -(to[2] * coss(rotation[0]) - to[1] * sins(rotation[0]));
    pitchRotated[1] = to[2] * sins(rotation[0]) + to[1] * coss(rotation[0]);
    pitchRotated[0] = to[0];

    // Rotate again by rotation's yaw
    dst[0] = from[0] + pitchRotated[2] * sins(rotation[1]) + pitchRotated[0] * coss(rotation[1]);
    dst[1] = from[1] + pitchRotated[1];
    dst[2] = from[2] + pitchRotated[2] * coss(rotation[1]) - pitchRotated[0] * sins(rotation[1]);
}

/**
 * Calculate Lakitu's next position and focus, according to gCamera's state,
 * and store them in `newPos` and `newFoc`.
 *
 * @param newPos where Lakitu should fly towards this frame
 * @param newFoc where Lakitu should look towards this frame
 *
 * @param curPos gCamera's pos this frame
 * @param curFoc gCamera's foc this frame
 *
 * @param oldPos gCamera's pos last frame
 * @param oldFoc gCamera's foc last frame
 *
 * @return Lakitu's next yaw, which is the same as the yaw passed in if no transition happened
 */
s16 next_lakitu_state(struct CameraData* cameraData, struct Surfaces* surfaceLists, Vec3f newPos, Vec3f newFoc, Vec3f curPos, Vec3f curFoc,
    Vec3f oldPos, Vec3f oldFoc, s16 yaw) {
    s16 yawVelocity;
    s16 pitchVelocity;
    f32 distVelocity;
    f32 goalDist;
    s16 goalPitch;
    s16 goalYaw;
    f32 distTimer = cameraData->sModeTransition.framesLeft;
    s16 angleTimer = cameraData->sModeTransition.framesLeft;
    Vec3f nextPos;
    Vec3f nextFoc;
    Vec3f startPos;
    Vec3f startFoc;
    s32 i;
    f32 floorHeight;
    struct Surface* floor;

    // If not transitioning, just use gCamera's current pos and foc
    vec3f_copy(newPos, curPos);
    vec3f_copy(newFoc, curFoc);

    if (cameraData->sStatusFlags & CAM_FLAG_START_TRANSITION) {
        for (i = 0; i < 3; i++) {
            // Add Mario's displacement from this frame to the last frame's pos and focus
            // Makes the transition start from where the camera would have moved
            startPos[i] = oldPos[i] + cameraData->sMarioCamState->pos[i] - cameraData->sModeTransition.marioPos[i];
            startFoc[i] = oldFoc[i] + cameraData->sMarioCamState->pos[i] - cameraData->sModeTransition.marioPos[i];
        }


        vec3f_get_dist_and_angle(curFoc, startFoc, &(cameraData->sModeTransition.focDist), &(cameraData->sModeTransition.focPitch),
            &(cameraData->sModeTransition.focYaw));
        vec3f_get_dist_and_angle(curFoc, startPos, &(cameraData->sModeTransition.posDist), &(cameraData->sModeTransition.posPitch),
            &(cameraData->sModeTransition.posYaw));
        cameraData->sStatusFlags &= ~CAM_FLAG_START_TRANSITION;
    }

    // Transition from the last mode to the current one
    if (cameraData->sModeTransition.framesLeft > 0) {
        vec3f_get_dist_and_angle(curFoc, curPos, &goalDist, &goalPitch, &goalYaw);
        distVelocity = ABS(goalDist - cameraData->sModeTransition.posDist) / distTimer;
        pitchVelocity = ABS(goalPitch - cameraData->sModeTransition.posPitch) / angleTimer;
        yawVelocity = ABS(goalYaw - cameraData->sModeTransition.posYaw) / angleTimer;

        camera_approach_f32_symmetric_bool(&(cameraData->sModeTransition.posDist), goalDist, distVelocity);
        camera_approach_s16_symmetric_bool(&(cameraData->sModeTransition.posYaw), goalYaw, yawVelocity);
        camera_approach_s16_symmetric_bool(&(cameraData->sModeTransition.posPitch), goalPitch, pitchVelocity);
        vec3f_set_dist_and_angle(curFoc, nextPos, cameraData->sModeTransition.posDist, cameraData->sModeTransition.posPitch,
            cameraData->sModeTransition.posYaw);

        vec3f_get_dist_and_angle(curPos, curFoc, &goalDist, &goalPitch, &goalYaw);
        pitchVelocity = cameraData->sModeTransition.focPitch / (s16)cameraData->sModeTransition.framesLeft;
        yawVelocity = cameraData->sModeTransition.focYaw / (s16)cameraData->sModeTransition.framesLeft;
        distVelocity = cameraData->sModeTransition.focDist / cameraData->sModeTransition.framesLeft;

        camera_approach_s16_symmetric_bool(&(cameraData->sModeTransition.focPitch), goalPitch, pitchVelocity);
        camera_approach_s16_symmetric_bool(&(cameraData->sModeTransition.focYaw), goalYaw, yawVelocity);
        camera_approach_f32_symmetric_bool(&(cameraData->sModeTransition.focDist), 0, distVelocity);
        vec3f_set_dist_and_angle(curFoc, nextFoc, cameraData->sModeTransition.focDist, cameraData->sModeTransition.focPitch,
            cameraData->sModeTransition.focYaw);

        vec3f_copy(newFoc, nextFoc);
        vec3f_copy(newPos, nextPos);

        if (cameraData->gCamera->cutscene != 0 || !(cameraData->gCameraMovementFlags & CAM_MOVE_C_UP_MODE)) {
            floorHeight = find_floor(surfaceLists, newPos[0], newPos[1], newPos[2], &floor);
            if (floorHeight != FLOOR_LOWER_LIMIT) {
                if ((floorHeight += 125.f) > newPos[1]) {
                    newPos[1] = floorHeight;
                }
            }
            f32_find_wall_collision(surfaceLists, &newPos[0], &newPos[1], &newPos[2], 0.f, 100.f);
        }
        cameraData->sModeTransition.framesLeft--;
        yaw = calculate_yaw(newFoc, newPos);
    }
    else {
        cameraData->sModeTransition.posDist = 0.f;
        cameraData->sModeTransition.posPitch = 0;
        cameraData->sModeTransition.posYaw = 0;
        cameraData->sStatusFlags &= ~CAM_FLAG_TRANSITION_OUT_OF_C_UP;
    }
    vec3f_copy(cameraData->sModeTransition.marioPos, cameraData->sMarioCamState->pos);
    return yaw;
}

/**
 * Activates any CameraTriggers that Mario is inside.
 * Then, applies area-specific processing to the camera, such as setting the default mode, or changing
 * the mode based on the terrain type Mario is standing on.
 *
 * @return the camera's mode after processing, although this is unused in the code
 */
s16 camera_course_processing(struct Camera* c, struct CameraData* cameraData, struct AreaData* areaData) {
    s16 level = areaData->gCurrLevelNum;
    s16 mode;
    s8 area = areaData->gCurrentArea->index;
    // Bounds iterator
    u32 b;
    // Camera trigger's bounding box
    Vec3f center, bounds;
    u32 insideBounds = FALSE;
    u8 oldMode = c->mode;

    if (c->mode == CAMERA_MODE_C_UP) {
        c->mode = cameraData->sModeInfo.lastMode;
    }

    if (level > LEVEL_COUNT + 1) {
        level = LEVEL_COUNT + 1;
    }

    cameraData->sStatusFlags &= ~CAM_FLAG_BLOCK_AREA_PROCESSING;
    if (oldMode == CAMERA_MODE_C_UP) {
        cameraData->sModeInfo.lastMode = c->mode;
        c->mode = oldMode;
    }
    mode = c->mode;
    return mode;
}

/**
 * Checks for any walls obstructing Mario from view, and calculates a new yaw that the camera should
 * rotate towards.
 *
 * @param[out] avoidYaw the angle (from Mario) that the camera should rotate towards to avoid the wall.
 *                      The camera then approaches avoidYaw until Mario is no longer obstructed.
 *                      avoidYaw is always parallel to the wall.
 * @param yawRange      how wide of an arc to check for walls obscuring Mario.
 *
 * @return 3 if a wall is covering Mario, 1 if a wall is only near the camera.
 */
s32 rotate_camera_around_walls(struct Camera* c, struct CameraData* cameraData, struct Surfaces* surfaceLists, Vec3f cPos, s16* avoidYaw, s16 yawRange) {
    struct WallCollisionData colData;
    struct Surface* wall;
    f32 dummyDist, checkDist;
    f32 coarseRadius;
    f32 fineRadius;
    s16 wallYaw, horWallNorm;
    s16 dummyPitch;
    // The yaw of the vector from Mario to the camera.
    s16 yawFromMario;
    s32 status = 0;
    /// The current iteration. The algorithm takes 8 equal steps from Mario back to the camera.
    s32 step = 0;

    vec3f_get_dist_and_angle(cameraData->sMarioCamState->pos, cPos, &dummyDist, &dummyPitch, &yawFromMario);
    cameraData->sStatusFlags &= ~CAM_FLAG_CAM_NEAR_WALL;
    colData.offsetY = 100.0f;
    // The distance from Mario to Lakitu
    checkDist = 0.0f;
    /// The radius used to find potential walls to avoid.
    /// @bug Increases to 250.f, but the max collision radius is 200.f
    coarseRadius = 150.0f;
    /// This only increases when there is a wall collision found in the coarse pass
    fineRadius = 100.0f;

    for (step = 0; step < 8; step++) {
        // Start at Mario, move backwards to Lakitu's position
        colData.x = cameraData->sMarioCamState->pos[0] + ((cPos[0] - cameraData->sMarioCamState->pos[0]) * checkDist);
        colData.y = cameraData->sMarioCamState->pos[1] + ((cPos[1] - cameraData->sMarioCamState->pos[1]) * checkDist);
        colData.z = cameraData->sMarioCamState->pos[2] + ((cPos[2] - cameraData->sMarioCamState->pos[2]) * checkDist);
        colData.radius = coarseRadius;
        // Increase the coarse check radius
        camera_approach_f32_symmetric_bool(&coarseRadius, 250.f, 30.f);

        if (find_wall_collisions(surfaceLists, &colData) != 0) {
            wall = colData.walls[colData.numWalls - 1];

            // If we're over halfway from Mario to Lakitu, then there's a wall near the camera, but
            // not necessarily obstructing Mario
            if (step >= 5) {
                cameraData->sStatusFlags |= CAM_FLAG_CAM_NEAR_WALL;
                if (status <= 0) {
                    status = 1;
                    wall = colData.walls[colData.numWalls - 1];
                    // wallYaw is parallel to the wall, not perpendicular
                    wallYaw = atan2s(wall->normal.z, wall->normal.x) + DEGREES(90);
                    // Calculate the avoid direction. The function returns the opposite direction so add 180
                    // degrees.
                    *avoidYaw = calc_avoid_yaw(yawFromMario, wallYaw) + DEGREES(180);
                }
            }

            colData.x = cameraData->sMarioCamState->pos[0] + ((cPos[0] - cameraData->sMarioCamState->pos[0]) * checkDist);
            colData.y = cameraData->sMarioCamState->pos[1] + ((cPos[1] - cameraData->sMarioCamState->pos[1]) * checkDist);
            colData.z = cameraData->sMarioCamState->pos[2] + ((cPos[2] - cameraData->sMarioCamState->pos[2]) * checkDist);
            colData.radius = fineRadius;
            // Increase the fine check radius
            camera_approach_f32_symmetric_bool(&fineRadius, 200.f, 20.f);

            if (find_wall_collisions(surfaceLists, &colData) != 0) {
                wall = colData.walls[colData.numWalls - 1];
                horWallNorm = atan2s(wall->normal.z, wall->normal.x);
                wallYaw = horWallNorm + DEGREES(90);
                // If Mario would be blocked by the surface, then avoid it
                if ((is_range_behind_surface(cameraData->sMarioCamState->pos, cPos, wall, yawRange, SURFACE_WALL_MISC) == 0)
                    && (is_mario_behind_surface(c, cameraData, wall) == TRUE)
                    // Also check if the wall is tall enough to cover Mario
                    && (is_surf_within_bounding_box(wall, -1.f, 150.f, -1.f) == FALSE)) {
                    // Calculate the avoid direction. The function returns the opposite direction so add 180
                    // degrees.
                    *avoidYaw = calc_avoid_yaw(yawFromMario, wallYaw) + DEGREES(180);
                    camera_approach_s16_symmetric_bool(avoidYaw, horWallNorm, yawRange);
                    status = 3;
                    step = 8;
                }
            }
        }
        checkDist += 0.125f;
    }

    return status;
}

/**
 * Stores type and height of the nearest floor and ceiling to Mario in `pg`
 *
 * Note: Also finds the water level, but waterHeight is unused
 */
void find_mario_floor_and_ceil(struct PlayerGeometry* pg, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    struct Surface* surf;

    if (find_floor(surfaceLists, cameraData->sMarioCamState->pos[0], cameraData->sMarioCamState->pos[1] + 10.f,
        cameraData->sMarioCamState->pos[2], &surf) != FLOOR_LOWER_LIMIT) {
        pg->currFloorType = surf->type;
    }
    else {
        pg->currFloorType = 0;
    }

    if (find_ceil(surfaceLists, cameraData->sMarioCamState->pos[0], cameraData->sMarioCamState->pos[1] - 10.f,
        cameraData->sMarioCamState->pos[2], &surf) != CELL_HEIGHT_LIMIT) {
        pg->currCeilType = surf->type;
    }
    else {
        pg->currCeilType = 0;
    }

    pg->currFloorHeight = find_floor(surfaceLists, cameraData->sMarioCamState->pos[0],
        cameraData->sMarioCamState->pos[1] + 10.f,
        cameraData->sMarioCamState->pos[2], &pg->currFloor);
    pg->currCeilHeight = find_ceil(surfaceLists, cameraData->sMarioCamState->pos[0],
        cameraData->sMarioCamState->pos[1] - 10.f,
        cameraData->sMarioCamState->pos[2], &pg->currCeil);
    pg->waterHeight = find_water_level(cameraData->sMarioCamState->pos[0], cameraData->sMarioCamState->pos[2]);
}