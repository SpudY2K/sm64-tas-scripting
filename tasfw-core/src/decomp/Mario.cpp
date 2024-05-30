#include <Sm64/UltraTypes.hpp>
#include <sm64/Camera.hpp>
#include <Sm64/Mario.hpp>
#include <Sm64/Math.hpp>
#include <Sm64/ObjectFields.hpp>
#include <Sm64/Sm64.hpp>
#include <Sm64/Surface.hpp>
#include <Sm64/SurfaceTerrains.hpp>
#include <Sm64/Trig.hpp>
#include <Sm64/Types.hpp>

struct Animation animList[209] = { 
    {1, 189, 0, 0, 34, 20, NULL, NULL, 2896},
    {1, 189, 0, 0, 80, 20, NULL, NULL, 6908},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 6868},
    {1, 189, 0, 0, 64, 20, NULL, NULL, 4664},
    {1, 189, 0, 0, 33, 20, NULL, NULL, 2556},
    {0, 189, 0, 0, 90, 20, NULL, NULL, 6088},
    {1, 189, 0, 0, 12, 20, NULL, NULL, 1184},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 1800},
    {1, 189, 1, 0, 20, 20, NULL, NULL, 1760},
    {16, 189, 0, 0, 52, 20, NULL, NULL, 3344},
    {1, 189, 0, 0, 36, 20, NULL, NULL, 2836},
    {17, 189, 0, 0, 17, 20, NULL, NULL, 1680},
    {19, 189, 16, 0, 17, 20, NULL, NULL, 1640},
    {0, 189, 0, 0, 112, 20, NULL, NULL, 1062},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 372},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 1834},
    {1, 189, 1, 0, 18, 20, NULL, NULL, 1794},
    {1, 189, 0, 0, 16, 20, NULL, NULL, 1466},
    {1, 189, 0, 0, 18, 20, NULL, NULL, 1610},
    {1, 189, 0, 0, 23, 20, NULL, NULL, 1970},
    {1, 189, 0, 0, 15, 20, NULL, NULL, 1394},
    {0, 189, 0, 0, 15, 20, NULL, NULL, 1222},
    {0, 189, 0, 0, 100, 20, NULL, NULL, 4744},
    {0, 189, 0, 0, 76, 20, NULL, NULL, 3234},
    {0, 189, 42, 0, 100, 20, NULL, NULL, 4744},
    {1, 189, 0, 0, 86, 20, NULL, NULL, 5646},
    {1, 189, 0, 0, 17, 20, NULL, NULL, 1438},
    {0, 189, 0, 0, 64, 20, NULL, NULL, 3150},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 1072},
    {0, 189, 0, 0, 35, 20, NULL, NULL, 1672},
    {0, 189, 0, 0, 30, 20, NULL, NULL, 1822},
    {1, 189, 0, 0, 21, 20, NULL, NULL, 1138},
    {1, 189, 0, 0, 96, 20, NULL, NULL, 7416},
    {1, 189, 0, 0, 35, 20, NULL, NULL, 2902},
    {1, 189, 0, 0, 27, 20, NULL, NULL, 2042},
    {1, 189, 0, 0, 100, 20, NULL, NULL, 8508},
    {1, 189, 0, 0, 120, 20, NULL, NULL, 9668},
    {65, 189, 0, 0, 100, 20, NULL, NULL, 8310},
    {65, 189, 0, 0, 94, 20, NULL, NULL, 7644},
    {1, 189, 0, 0, 112, 20, NULL, NULL, 9272},
    {1, 189, 0, 0, 15, 20, NULL, NULL, 1302},
    {0, 189, 0, 0, 10, 20, NULL, NULL, 874},
    {0, 189, 0, 0, 40, 20, NULL, NULL, 1544},
    {0, 189, 0, 0, 40, 20, NULL, NULL, 1874},
    {1, 189, 0, 0, 80, 20, NULL, NULL, 5952},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 5912},
    {1, 189, 0, 0, 47, 20, NULL, NULL, 3320},
    {1, 189, 0, 0, 100, 20, NULL, NULL, 7712},
    {0, 189, 0, 0, 90, 20, NULL, NULL, 5720},
    {1, 189, 0, 0, 140, 20, NULL, NULL, 10952},
    {1, 189, 0, 0, 96, 20, NULL, NULL, 8182},
    {0, 189, 0, 0, 50, 20, NULL, NULL, 3132},
    {1, 189, 0, 0, 16, 20, NULL, NULL, 1592},
    {1, 189, 0, 0, 54, 20, NULL, NULL, 3996},
    {1, 189, 10, 0, 46, 20, NULL, NULL, 3992},
    {1, 189, 0, 0, 100, 20, NULL, NULL, 7120},
    {1, 189, 0, 0, 12, 20, NULL, NULL, 1136},
    {1, 189, 0, 0, 155, 20, NULL, NULL, 12710},
    {1, 189, 0, 0, 6, 20, NULL, NULL, 666},
    {1, 189, 0, 0, 16, 20, NULL, NULL, 1496},
    {1, 189, 0, 0, 11, 20, NULL, NULL, 1106},
    {1, 189, 10, 0, 11, 20, NULL, NULL, 1066},
    {1, 189, 0, 0, 155, 20, NULL, NULL, 11782},
    {0, 189, 0, 0, 61, 20, NULL, NULL, 3386},
    {1, 189, 0, 0, 19, 20, NULL, NULL, 1386},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 828},
    {1, 189, 2, 0, 16, 20, NULL, NULL, 1248},
    {1, 189, 0, 0, 2, 20, NULL, NULL, 376},
    {1, 189, 0, 0, 15, 20, NULL, NULL, 942},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 1522},
    {1, 189, 1, 0, 14, 20, NULL, NULL, 1482},
    {1, 189, 0, 0, 11, 20, NULL, NULL, 1130},
    {0, 189, 0, 0, 77, 20, NULL, NULL, 5390},
    {1, 189, 0, 0, 16, 20, NULL, NULL, 1590},
    {1, 189, 0, 0, 8, 20, NULL, NULL, 908},
    {1, 189, 0, 0, 18, 20, NULL, NULL, 1678},
    {1, 189, 0, 0, 9, 20, NULL, NULL, 962},
    {1, 189, 0, 0, 12, 20, NULL, NULL, 2788},
    {1, 189, 22, 0, 38, 20, NULL, NULL, 2748},
    {1, 189, 0, 0, 21, 20, NULL, NULL, 1870},
    {1, 189, 0, 0, 6, 20, NULL, NULL, 712},
    {1, 189, 0, 0, 14, 20, NULL, NULL, 1294},
    {1, 189, 0, 0, 11, 20, NULL, NULL, 1170},
    {1, 189, 0, 0, 25, 20, NULL, NULL, 2262},
    {1, 189, 0, 0, 30, 20, NULL, NULL, 1606},
    {1, 189, 0, 0, 152, 20, NULL, NULL, 11560},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 1892},
    {1, 189, 9, 0, 24, 20, NULL, NULL, 1852},
    {0, 189, 0, 0, 20, 20, NULL, NULL, 1374},
    {1, 189, 0, 0, 37, 20, NULL, NULL, 3344},
    {1, 189, 0, 0, 38, 20, NULL, NULL, 3570},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 1012},
    {1, 189, 0, 0, 20, 20, NULL, NULL, 1550},
    {1, 189, 0, 0, 19, 20, NULL, NULL, 1434},
    {1, 189, 0, 0, 155, 20, NULL, NULL, 12402},
    {9, 189, 0, 0, 60, 20, NULL, NULL, 5350},
    {9, 189, 0, 0, 50, 20, NULL, NULL, 4312},
    {9, 189, 0, 0, 147, 20, NULL, NULL, 12952},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 1034},
    {0, 189, 0, 0, 33, 20, NULL, NULL, 1918},
    {0, 189, 0, 0, 18, 20, NULL, NULL, 1538},
    {1, 189, 0, 0, 21, 20, NULL, NULL, 1992},
    {1, 189, 0, 0, 26, 20, NULL, NULL, 2240},
    {1, 189, 0, 0, 5, 20, NULL, NULL, 678},
    {1, 189, 0, 0, 4, 20, NULL, NULL, 632},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 1056},
    {1, 189, 0, 0, 13, 20, NULL, NULL, 1352},
    {1, 189, 0, 0, 11, 20, NULL, NULL, 1232},
    {0, 189, 0, 0, 27, 20, NULL, NULL, 1576},
    {1, 189, 0, 0, 18, 20, NULL, NULL, 1578},
    {1, 189, 0, 0, 16, 20, NULL, NULL, 1428},
    {0, 189, 0, 0, 10, 20, NULL, NULL, 430},
    {2, 189, 0, 0, 10, 20, NULL, NULL, 390},
    {1, 189, 0, 0, 24, 20, NULL, NULL, 2370},
    {0, 189, 0, 0, 72, 20, NULL, NULL, 4674},
    {0, 189, 0, 0, 72, 20, NULL, NULL, 4634},
    {1, 189, 0, 0, 24, 20, NULL, NULL, 2136},
    {1, 189, 0, 0, 24, 20, NULL, NULL, 2184},
    {1, 189, 0, 0, 100, 20, NULL, NULL, 4940},
    {0, 189, 0, 0, 100, 20, NULL, NULL, 2756},
    {0, 189, 0, 0, 149, 20, NULL, NULL, 10746},
    {1, 189, 0, 0, 53, 20, NULL, NULL, 3926},
    {0, 189, 0, 0, 6, 20, NULL, NULL, 694},
    {1, 189, 0, 0, 30, 20, NULL, NULL, 2652},
    {1, 189, 0, 0, 30, 20, NULL, NULL, 2592},
    {0, 189, 0, 0, 40, 20, NULL, NULL, 1406},
    {0, 189, 0, 0, 90, 20, NULL, NULL, 4830},
    {0, 189, 0, 0, 64, 20, NULL, NULL, 3914},
    {0, 189, 0, 0, 64, 20, NULL, NULL, 4540},
    {1, 189, 0, 0, 50, 20, NULL, NULL, 4600},
    {1, 189, 0, 0, 67, 20, NULL, NULL, 6062},
    {1, 189, 0, 0, 59, 20, NULL, NULL, 5026},
    {1, 189, 0, 0, 64, 20, NULL, NULL, 5048},
    {0, 189, 0, 0, 40, 20, NULL, NULL, 616},
    {1, 189, 0, 0, 40, 20, NULL, NULL, 3194},
    {0, 189, 0, 0, 50, 20, NULL, NULL, 1856},
    {1, 189, 0, 0, 20, 20, NULL, NULL, 1592},
    {1, 189, 20, 0, 20, 20, NULL, NULL, 1552},
    {1, 189, 0, 0, 40, 20, NULL, NULL, 3272},
    {1, 189, 0, 0, 37, 20, NULL, NULL, 3262},
    {1, 189, 0, 0, 8, 20, NULL, NULL, 938},
    {1, 189, 0, 0, 14, 20, NULL, NULL, 1378},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 1950},
    {1, 189, 1, 0, 20, 20, NULL, NULL, 1910},
    {1, 189, 0, 0, 15, 20, NULL, NULL, 1304},
    {0, 189, 0, 0, 8, 20, NULL, NULL, 558},
    {0, 189, 27, 0, 116, 20, NULL, NULL, 5892},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 894},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 372},
    {1, 189, 0, 0, 5, 20, NULL, NULL, 572},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 972},
    {1, 189, 0, 0, 6, 20, NULL, NULL, 708},
    {0, 189, 0, 0, 90, 20, NULL, NULL, 3050},
    {0, 189, 0, 0, 92, 20, NULL, NULL, 7306},
    {1, 189, 0, 0, 8, 20, NULL, NULL, 936},
    {1, 189, 0, 0, 8, 20, NULL, NULL, 922},
    {9, 189, 0, 0, 64, 20, NULL, NULL, 5176},
    {9, 189, 0, 0, 26, 20, NULL, NULL, 2236},
    {1, 189, 0, 0, 50, 20, NULL, NULL, 4300},
    {1, 189, 0, 0, 16, 20, NULL, NULL, 1066},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 682},
    {0, 189, 0, 0, 24, 20, NULL, NULL, 1212},
    {1, 189, 0, 0, 23, 20, NULL, NULL, 1740},
    {1, 189, 0, 0, 30, 20, NULL, NULL, 2882},
    {0, 189, 0, 0, 30, 20, NULL, NULL, 1942},
    {1, 189, 0, 0, 80, 20, NULL, NULL, 5440},
    {1, 189, 0, 0, 70, 20, NULL, NULL, 4938},
    {1, 189, 0, 0, 40, 20, NULL, NULL, 3352},
    {1, 189, 0, 0, 50, 20, NULL, NULL, 4202},
    {1, 189, 0, 0, 20, 20, NULL, NULL, 2020},
    {1, 189, 0, 0, 13, 20, NULL, NULL, 1264},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 1042},
    {0, 189, 8, 0, 24, 20, NULL, NULL, 1998},
    {1, 189, 0, 0, 25, 20, NULL, NULL, 2152},
    {1, 189, 0, 0, 11, 20, NULL, NULL, 1248},
    {1, 189, 0, 0, 25, 20, NULL, NULL, 2452},
    {1, 189, 0, 0, 5, 20, NULL, NULL, 732},
    {1, 189, 0, 0, 28, 20, NULL, NULL, 2710},
    {0, 189, 0, 0, 30, 20, NULL, NULL, 2116},
    {1, 189, 0, 0, 83, 20, NULL, NULL, 6786},
    {1, 189, 0, 0, 24, 20, NULL, NULL, 2138},
    {1, 189, 0, 0, 20, 20, NULL, NULL, 1714},
    {1, 189, 19, 0, 20, 20, NULL, NULL, 1674},
    {1, 189, 0, 0, 40, 20, NULL, NULL, 3272},
    {0, 189, 0, 0, 50, 20, NULL, NULL, 1068},
    {1, 189, 0, 0, 25, 20, NULL, NULL, 2360},
    {0, 189, 0, 0, 20, 20, NULL, NULL, 1278},
    {0, 189, 0, 0, 97, 20, NULL, NULL, 4424},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 1860},
    {1, 189, 1, 0, 18, 20, NULL, NULL, 1820},
    {1, 189, 0, 0, 10, 20, NULL, NULL, 1052},
    {1, 189, 0, 0, 24, 20, NULL, NULL, 2228},
    {1, 189, 0, 0, 32, 20, NULL, NULL, 2744},
    {1, 189, 0, 0, 36, 20, NULL, NULL, 2760},
    {0, 189, 0, 0, 90, 20, NULL, NULL, 5714},
    {1, 189, 0, 0, 30, 20, NULL, NULL, 2234},
    {1, 189, 0, 0, 30, 20, NULL, NULL, 2234},
    {1, 189, 0, 0, 30, 20, NULL, NULL, 2234},
    {0, 189, 0, 0, 50, 20, NULL, NULL, 1958},
    {0, 189, 0, 0, 50, 20, NULL, NULL, 3136},
    {1, 189, 6, 0, 20, 20, NULL, NULL, 1940},
    {1, 189, 0, 0, 21, 20, NULL, NULL, 2232},
    {0, 189, 25, 0, 30, 20, NULL, NULL, 2290},
    {1, 189, 0, 0, 17, 20, NULL, NULL, 1714},
    {1, 189, 0, 0, 1, 20, NULL, NULL, 1674},
    {1, 189, 0, 0, 63, 20, NULL, NULL, 5476},
    {1, 189, 0, 0, 18, 20, NULL, NULL, 1752},
    {1, 189, 0, 0, 42, 20, NULL, NULL, 3000},
    {1, 189, 0, 0, 14, 20, NULL, NULL, 1022}
};

/**************************************************
 *                    ANIMATIONS                  *
 **************************************************/

 /**
  * Checks if Mario's animation has reached its end point.
  */
s32 is_anim_at_end(struct MarioState* m) {
    struct Object* o = m->marioObj;

    return (o->header.gfx.animInfo.animFrame + 1) == o->header.gfx.animInfo.curAnim->loopEnd;
}

/**
 * Checks if Mario's animation has surpassed 2 frames before its end point.
 */
s32 is_anim_past_end(struct MarioState* m) {
    struct Object* o = m->marioObj;

    return o->header.gfx.animInfo.animFrame >= (o->header.gfx.animInfo.curAnim->loopEnd - 2);
}

/**
 * Sets Mario's animation without any acceleration, running at its default rate.
 */
s16 set_mario_animation(struct MarioState* m, s32 targetAnimID) {
    struct Object* o = m->marioObj;
    m->animation->targetAnim = &(animList[targetAnimID]);
    struct Animation* targetAnim = m->animation->targetAnim;

    if (o->header.gfx.animInfo.animID != targetAnimID) {
        o->header.gfx.animInfo.animID = targetAnimID;
        o->header.gfx.animInfo.curAnim = targetAnim;
        o->header.gfx.animInfo.animAccel = 0;
        o->header.gfx.animInfo.animYTrans = m->unkB0;

        if (targetAnim->flags & ANIM_FLAG_2) {
            o->header.gfx.animInfo.animFrame = targetAnim->startFrame;
        }
        else {
            if (targetAnim->flags & ANIM_FLAG_BACKWARD) {
                o->header.gfx.animInfo.animFrame = targetAnim->startFrame + 1;
            }
            else {
                o->header.gfx.animInfo.animFrame = targetAnim->startFrame - 1;
            }
        }
    }

    return o->header.gfx.animInfo.animFrame;
}

/**
 * Sets Mario's animation where the animation is sped up or
 * slowed down via acceleration.
 */
s16 set_mario_anim_with_accel(struct MarioState* m, s32 targetAnimID, s32 accel) {
    struct Object* o = m->marioObj;
    m->animation->targetAnim = &(animList[targetAnimID]);
    struct Animation* targetAnim = m->animation->targetAnim;

    if (o->header.gfx.animInfo.animID != targetAnimID) {
        o->header.gfx.animInfo.animID = targetAnimID;
        o->header.gfx.animInfo.curAnim = targetAnim;
        o->header.gfx.animInfo.animYTrans = m->unkB0;

        if (targetAnim->flags & ANIM_FLAG_2) {
            o->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10);
        }
        else {
            if (targetAnim->flags & ANIM_FLAG_BACKWARD) {
                o->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) + accel;
            }
            else {
                o->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) - accel;
            }
        }

        o->header.gfx.animInfo.animFrame = (o->header.gfx.animInfo.animFrameAccelAssist >> 0x10);
    }

    o->header.gfx.animInfo.animAccel = accel;

    return o->header.gfx.animInfo.animFrame;
}

/**
 * Sets the animation to a specific "next" frame from the frame given.
 */
void set_anim_to_frame(struct MarioState* m, s16 animFrame) {
    struct AnimInfo* animInfo = &m->marioObj->header.gfx.animInfo;
    struct Animation* curAnim = animInfo->curAnim;

    if (animInfo->animAccel != 0) {
        if (curAnim->flags & ANIM_FLAG_BACKWARD) {
            animInfo->animFrameAccelAssist = (animFrame << 0x10) + animInfo->animAccel;
        }
        else {
            animInfo->animFrameAccelAssist = (animFrame << 0x10) - animInfo->animAccel;
        }
    }
    else {
        if (curAnim->flags & ANIM_FLAG_BACKWARD) {
            animInfo->animFrame = animFrame + 1;
        }
        else {
            animInfo->animFrame = animFrame - 1;
        }
    }
}

s32 is_anim_past_frame(struct MarioState* m, s16 animFrame) {
    s32 isPastFrame;
    s32 acceleratedFrame = animFrame << 0x10;
    struct AnimInfo* animInfo = &m->marioObj->header.gfx.animInfo;
    struct Animation* curAnim = animInfo->curAnim;

    if (animInfo->animAccel != 0) {
        if (curAnim->flags & ANIM_FLAG_BACKWARD) {
            isPastFrame =
                (animInfo->animFrameAccelAssist > acceleratedFrame)
                && (acceleratedFrame >= (animInfo->animFrameAccelAssist - animInfo->animAccel));
        }
        else {
            isPastFrame =
                (animInfo->animFrameAccelAssist < acceleratedFrame)
                && (acceleratedFrame <= (animInfo->animFrameAccelAssist + animInfo->animAccel));
        }
    }
    else {
        if (curAnim->flags & ANIM_FLAG_BACKWARD) {
            isPastFrame = (animInfo->animFrame == (animFrame + 1));
        }
        else {
            isPastFrame = ((animInfo->animFrame + 1) == animFrame);
        }
    }

    return isPastFrame;
}

/**
 * Update the animation frame of an object. The animation flags determine
 * whether it plays forwards or backwards, and whether it stops or loops at
 * the end etc.
 */
s16 geo_update_animation_frame(struct AnimInfo* obj, s32* accelAssist, u16 gAreaUpdateCounter) {
    s32 result;
    struct Animation* anim = obj->curAnim;

    if (obj->animTimer == gAreaUpdateCounter || anim->flags & ANIM_FLAG_2) {
        if (accelAssist != NULL) {
            accelAssist[0] = obj->animFrameAccelAssist;
        }

        return obj->animFrame;
    }

    if (anim->flags & ANIM_FLAG_BACKWARD) {
        if (obj->animAccel != 0) {
            result = obj->animFrameAccelAssist - obj->animAccel;
        }
        else {
            result = (obj->animFrame - 1) << 16;
        }

        if (GET_HIGH_S16_OF_32(result) < anim->loopStart) {
            if (anim->flags & ANIM_FLAG_NOLOOP) {
                SET_HIGH_S16_OF_32(result, anim->loopStart);
            }
            else {
                SET_HIGH_S16_OF_32(result, anim->loopEnd - 1);
            }
        }
    }
    else {
        if (obj->animAccel != 0) {
            result = obj->animFrameAccelAssist + obj->animAccel;
        }
        else {
            result = (obj->animFrame + 1) << 16;
        }

        if (GET_HIGH_S16_OF_32(result) >= anim->loopEnd) {
            if (anim->flags & ANIM_FLAG_NOLOOP) {
                SET_HIGH_S16_OF_32(result, anim->loopEnd - 1);
            }
            else {
                SET_HIGH_S16_OF_32(result, anim->loopStart);
            }
        }
    }

    if (accelAssist != 0) {
        accelAssist[0] = result;
    }

    return GET_HIGH_S16_OF_32(result);
}

/**
 * Initialize the animation-related global variables for the currently drawn
 * object's animation.
 */
void geo_set_animation_globals(struct AnimInfo* node, s32 hasAnimation, u16 gAreaUpdateCounter) {
    if (hasAnimation) {
        node->animFrame = geo_update_animation_frame(node, &node->animFrameAccelAssist, gAreaUpdateCounter);
    }
    node->animTimer = gAreaUpdateCounter;
}


/**************************************************
 *                     ACTIONS                    *
 **************************************************/

 /**
  * Sets Mario's other velocities from his forward speed.
  */
void mario_set_forward_vel(struct MarioState* m, f32 forwardVel) {
    m->forwardVel = forwardVel;

    m->slideVelX = sins(m->faceAngle[1]) * m->forwardVel;
    m->slideVelZ = coss(m->faceAngle[1]) * m->forwardVel;

    m->vel[0] = (f32)m->slideVelX;
    m->vel[2] = (f32)m->slideVelZ;
}

/**
 * Returns the slipperiness class of Mario's floor.
 */
s32 mario_get_floor_class(struct MarioState* m) {
    s32 floorClass;

    // The slide terrain type defaults to slide slipperiness.
    // This doesn't matter too much since normally the slide terrain
    // is checked for anyways.
    if ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE) {
        floorClass = SURFACE_CLASS_VERY_SLIPPERY;
    }
    else {
        floorClass = SURFACE_CLASS_DEFAULT;
    }

    if (m->floor != NULL) {
        switch (m->floor->type) {
        case SURFACE_NOT_SLIPPERY:
        case SURFACE_HARD_NOT_SLIPPERY:
        case SURFACE_SWITCH:
            floorClass = SURFACE_CLASS_NOT_SLIPPERY;
            break;

        case SURFACE_SLIPPERY:
        case SURFACE_NOISE_SLIPPERY:
        case SURFACE_HARD_SLIPPERY:
        case SURFACE_NO_CAM_COL_SLIPPERY:
            floorClass = SURFACE_CLASS_SLIPPERY;
            break;

        case SURFACE_VERY_SLIPPERY:
        case SURFACE_ICE:
        case SURFACE_HARD_VERY_SLIPPERY:
        case SURFACE_NOISE_VERY_SLIPPERY_73:
        case SURFACE_NOISE_VERY_SLIPPERY_74:
        case SURFACE_NOISE_VERY_SLIPPERY:
        case SURFACE_NO_CAM_COL_VERY_SLIPPERY:
            floorClass = SURFACE_CLASS_VERY_SLIPPERY;
            break;
        }
    }

    // Crawling allows Mario to not slide on certain steeper surfaces.
    if (m->action == ACT_CRAWLING && m->floor->normal.y > 0.5f && floorClass == SURFACE_CLASS_DEFAULT) {
        floorClass = SURFACE_CLASS_NOT_SLIPPERY;
    }

    return floorClass;
}

/**
 * Collides with walls and returns the most recent wall.
 */
struct Surface* resolve_and_return_wall_collisions(struct Surfaces* surfaceLists, Vec3f pos, f32 offset, f32 radius) {
    struct WallCollisionData collisionData;
    struct Surface* wall = NULL;

    collisionData.x = pos[0];
    collisionData.y = pos[1];
    collisionData.z = pos[2];
    collisionData.radius = radius;
    collisionData.offsetY = offset;

    if (find_wall_collisions(surfaceLists, &collisionData)) {
        wall = collisionData.walls[collisionData.numWalls - 1];
    }

    pos[0] = collisionData.x;
    pos[1] = collisionData.y;
    pos[2] = collisionData.z;

    // This only returns the most recent wall and can also return NULL
    // there are no wall collisions.
    return wall;
}

/**
 * Finds the ceiling from a vec3f horizontally and a height (with 80 vertical buffer).
 */
f32 vec3f_find_ceil(struct Surfaces* surfaceLists, Vec3f pos, f32 height, struct Surface** ceil) {
    return find_ceil(surfaceLists, pos[0], height + 80.0f, pos[2], ceil);
}

/**
 * Determines if Mario is facing "downhill."
 */
s32 mario_facing_downhill(struct MarioState* m, s32 turnYaw) {
    s16 faceAngleYaw = m->faceAngle[1];

    // This is never used in practice, as turnYaw is
    // always passed as zero.
    if (turnYaw && m->forwardVel < 0.0f) {
        faceAngleYaw += 0x8000;
    }

    faceAngleYaw = m->floorAngle - faceAngleYaw;

    return (-0x4000 < faceAngleYaw) && (faceAngleYaw < 0x4000);
}

/**
 * Determines if a surface is slippery based on the surface class.
 */
u32 mario_floor_is_slippery(struct MarioState* m) {
    f32 normY;

    if ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE
        && m->floor->normal.y < 0.9998477f //~cos(1 deg)
        ) {
        return TRUE;
    }

    switch (mario_get_floor_class(m)) {
    case SURFACE_VERY_SLIPPERY:
        normY = 0.9848077f; //~cos(10 deg)
        break;

    case SURFACE_SLIPPERY:
        normY = 0.9396926f; //~cos(20 deg)
        break;

    default:
        normY = 0.7880108f; //~cos(38 deg)
        break;

    case SURFACE_NOT_SLIPPERY:
        normY = 0.0f;
        break;
    }

    return m->floor->normal.y <= normY;
}

/**
 * Determines if a surface is a slope based on the surface class.
 */
s32 mario_floor_is_slope(struct MarioState* m) {
    f32 normY;

    if ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE
        && m->floor->normal.y < 0.9998477f) { // ~cos(1 deg)
        return TRUE;
    }

    switch (mario_get_floor_class(m)) {
    case SURFACE_VERY_SLIPPERY:
        normY = 0.9961947f; // ~cos(5 deg)
        break;

    case SURFACE_SLIPPERY:
        normY = 0.9848077f; // ~cos(10 deg)
        break;

    default:
        normY = 0.9659258f; // ~cos(15 deg)
        break;

    case SURFACE_NOT_SLIPPERY:
        normY = 0.9396926f; // ~cos(20 deg)
        break;
    }

    return m->floor->normal.y <= normY;
}

/**
 * Determines if a surface is steep based on the surface class.
 */
s32 mario_floor_is_steep(struct MarioState* m) {
    f32 normY;
    s32 result = FALSE;

    // Interestingly, this function does not check for the
    // slide terrain type. This means that steep behavior persists for
    // non-slippery and slippery surfaces.
    // This does not matter in vanilla game practice.
    if (!mario_facing_downhill(m, FALSE)) {
        switch (mario_get_floor_class(m)) {
        case SURFACE_VERY_SLIPPERY:
            normY = 0.9659258f; // ~cos(15 deg)
            break;

        case SURFACE_SLIPPERY:
            normY = 0.9396926f; // ~cos(20 deg)
            break;

        default:
            normY = 0.8660254f; // ~cos(30 deg)
            break;

        case SURFACE_NOT_SLIPPERY:
            normY = 0.8660254f; // ~cos(30 deg)
            break;
        }

        result = m->floor->normal.y <= normY;
    }

    return result;
}

/**
 * Finds the floor height relative from Mario given polar displacement.
 */
f32 find_floor_height_relative_polar(struct MarioState* m, struct Surfaces* surfaceLists, s16 angleFromMario, f32 distFromMario) {
    struct Surface* floor;
    f32 floorY;

    f32 y = sins(m->faceAngle[1] + angleFromMario) * distFromMario;
    f32 x = coss(m->faceAngle[1] + angleFromMario) * distFromMario;

    floorY = find_floor(surfaceLists, m->pos[0] + y, m->pos[1] + 100.0f, m->pos[2] + x, &floor);

    return floorY;
}

/**
 * Returns the slope of the floor based off points around Mario.
 */
s16 find_floor_slope(struct MarioState* m, struct Surfaces* surfaceLists, s16 yawOffset) {
    struct Surface* floor;
    f32 forwardFloorY, backwardFloorY;
    f32 forwardYDelta, backwardYDelta;
    s16 result;

    f32 x = sins(m->faceAngle[1] + yawOffset) * 5.0f;
    f32 z = coss(m->faceAngle[1] + yawOffset) * 5.0f;

    forwardFloorY = find_floor(surfaceLists, m->pos[0] + x, m->pos[1] + 100.0f, m->pos[2] + z, &floor);
    backwardFloorY = find_floor(surfaceLists, m->pos[0] - x, m->pos[1] + 100.0f, m->pos[2] - z, &floor);

    //! If Mario is near OOB, these floorY's can sometimes be -11000.
    //  This will cause these to be off and give improper slopes.
    forwardYDelta = forwardFloorY - m->pos[1];
    backwardYDelta = m->pos[1] - backwardFloorY;

    if (forwardYDelta * forwardYDelta < backwardYDelta * backwardYDelta) {
        result = atan2s(5.0f, forwardYDelta);
    }
    else {
        result = atan2s(5.0f, backwardYDelta);
    }

    return result;
}

/**
 * Adjusts Mario's camera and sound based on his action status.
 */
void update_mario_sound_and_camera(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    u32 action = m->action;
    s32 camPreset = m->area->camera->mode;

    if (action == ACT_FIRST_PERSON) {
        cameraData->gCameraMovementFlags &= ~CAM_MOVE_C_UP_MODE;
        // Go back to the last camera mode
        set_camera_mode(m->area->camera, cameraData, surfaceLists, -1, 1);
    }
}

/**
 * Transitions for a variety of airborne actions.
 */
static u32 set_mario_action_airborne(struct MarioState* m, u32 action, u32 actionArg) {
    f32 forwardVel;

    switch (action) {
    case ACT_LAVA_BOOST:
        m->vel[1] = 84.0f;
        if (actionArg == 0) {
            m->forwardVel = 0.0f;
        }
        break;

    case ACT_DIVE:
        if ((forwardVel = m->forwardVel + 15.0f) > 48.0f) {
            forwardVel = 48.0f;
        }
        mario_set_forward_vel(m, forwardVel);
        break;
    case ACT_SLIDE_KICK:
        m->vel[1] = 12.0f;
        if (m->forwardVel < 32.0f) {
            m->forwardVel = 32.0f;
        }
        break;
    }

    m->peakHeight = m->pos[1];
    m->flags |= MARIO_UNKNOWN_08;

    return action;
}

/**
 * Transitions for a variety of moving actions.
 */
static u32 set_mario_action_moving(struct MarioState* m, u32 action, UNUSED u32 actionArg) {
    s16 floorClass = mario_get_floor_class(m);
    f32 forwardVel = m->forwardVel;
    f32 mag = min(m->intendedMag, 8.0f);

    switch (action) {
    case ACT_WALKING:
        if (floorClass != SURFACE_CLASS_VERY_SLIPPERY) {
            if (0.0f <= forwardVel && forwardVel < mag) {
                m->forwardVel = mag;
            }
        }

        m->marioObj->oMarioWalkingPitch = 0;
        break;

    case ACT_HOLD_WALKING:
        if (0.0f <= forwardVel && forwardVel < mag / 2.0f) {
            m->forwardVel = mag / 2.0f;
        }
        break;

    case ACT_BEGIN_SLIDING:
        if (mario_facing_downhill(m, FALSE)) {
            action = ACT_BUTT_SLIDE;
        }
        else {
            action = ACT_STOMACH_SLIDE;
        }
        break;

    case ACT_HOLD_BEGIN_SLIDING:
        if (mario_facing_downhill(m, FALSE)) {
            action = ACT_HOLD_BUTT_SLIDE;
        }
        else {
            action = ACT_HOLD_STOMACH_SLIDE;
        }
        break;
    }

    return action;
}

/**
 * Transitions for a variety of cutscene actions.
 */
static u32 set_mario_action_cutscene(struct MarioState* m, u32 action, UNUSED u32 actionArg) {
    switch (action) {
    case ACT_EMERGE_FROM_PIPE:
        m->vel[1] = 52.0f;
        break;

    case ACT_FALL_AFTER_STAR_GRAB:
        mario_set_forward_vel(m, 0.0f);
        break;

    case ACT_SPAWN_SPIN_AIRBORNE:
        mario_set_forward_vel(m, 2.0f);
        break;

    case ACT_SPECIAL_EXIT_AIRBORNE:
    case ACT_SPECIAL_DEATH_EXIT:
        m->vel[1] = 64.0f;
        break;
    }

    return action;
}

/**
 * Puts Mario into a given action, putting Mario through the appropriate
 * specific function if needed.
 */
u32 set_mario_action(struct MarioState* m, u32 action, u32 actionArg) {
    switch (action & ACT_GROUP_MASK) {
    case ACT_GROUP_MOVING:
        action = set_mario_action_moving(m, action, actionArg);
        break;

    case ACT_GROUP_AIRBORNE:
        action = set_mario_action_airborne(m, action, actionArg);
        break;

    case ACT_GROUP_CUTSCENE:
        action = set_mario_action_cutscene(m, action, actionArg);
        break;
    }

    if (!(m->action & ACT_FLAG_AIR)) {
        m->flags &= ~MARIO_UNKNOWN_18;
    }

    // Initialize the action information.
    m->prevAction = m->action;
    m->action = action;
    m->actionArg = actionArg;
    m->actionState = 0;
    m->actionTimer = 0;

    return TRUE;
}

/**
 * Drop anything Mario is holding and set a new action.
 */
s32 drop_and_set_mario_action(struct MarioState* m, u32 action, u32 actionArg) {
    return set_mario_action(m, action, actionArg);
}

/**
 * Increment Mario's hurt counter and set a new action.
 */
s32 hurt_and_set_mario_action(struct MarioState* m, u32 action, u32 actionArg, s16 hurtCounter) {
    m->hurtCounter = hurtCounter;

    return set_mario_action(m, action, actionArg);
}

/**
 * Checks a variety of inputs for common transitions between many different
 * actions. A common variant of the below function.
 */
s32 check_common_action_exits(struct MarioState* m) {
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }
    if (m->input & INPUT_NONZERO_ANALOG) {
        return set_mario_action(m, ACT_WALKING, 0);
    }
    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    return FALSE;
}

/**
 * Checks a variety of inputs for common transitions between many different
 * object holding actions. A holding variant of the above function.
 */
s32 check_common_hold_action_exits(struct MarioState* m) {
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_HOLD_FREEFALL, 0);
    }
    if (m->input & INPUT_NONZERO_ANALOG) {
        return set_mario_action(m, ACT_HOLD_WALKING, 0);
    }
    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_HOLD_BEGIN_SLIDING, 0);
    }

    return FALSE;
}

/**
 * Transitions Mario from a submerged action to a walking action.
 */
s32 transition_submerged_to_walking(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    set_camera_mode(m->area->camera, cameraData, surfaceLists, m->area->camera->defMode, 1);

    vec3s_set(m->angleVel, 0, 0, 0);

    if (m->heldObj == NULL) {
        return set_mario_action(m, ACT_WALKING, 0);
    }
    else {
        return set_mario_action(m, ACT_HOLD_WALKING, 0);
    }
}

/**
 * These are the scaling values for the x and z axis for Mario
 * when he is close to unsquishing.
 */
u8 sSquishScaleOverTime[16] = { 0x46, 0x32, 0x32, 0x3C, 0x46, 0x50, 0x50, 0x3C,
                                0x28, 0x14, 0x14, 0x1E, 0x32, 0x3C, 0x3C, 0x28 };

/**
 * Applies the squish to Mario's model via scaling.
 */
void squish_mario_model(struct MarioState* m) {
    if (m->squishTimer != 0xFF) {
        // If no longer squished, scale back to default.
        if (m->squishTimer == 0) {
            vec3f_set(m->marioObj->header.gfx.scale, 1.0f, 1.0f, 1.0f);
        }
        // If timer is less than 16, rubber-band Mario's size scale up and down.
        else if (m->squishTimer <= 16) {
            m->squishTimer -= 1;

            m->marioObj->header.gfx.scale[1] =
                1.0f - ((sSquishScaleOverTime[15 - m->squishTimer] * 0.6f) / 100.0f);
            m->marioObj->header.gfx.scale[0] =
                ((sSquishScaleOverTime[15 - m->squishTimer] * 0.4f) / 100.0f) + 1.0f;

            m->marioObj->header.gfx.scale[2] = m->marioObj->header.gfx.scale[0];
        }
        else {
            m->squishTimer -= 1;

            vec3f_set(m->marioObj->header.gfx.scale, 1.4f, 0.4f, 1.4f);
        }
    }
}

/**
 * Update the button inputs for Mario.
 */
void update_mario_button_inputs(struct MarioState* m) {
    // Don't update for these buttons if squished.
    if (m->squishTimer == 0) {
        if (m->controller->buttonPressed & B_BUTTON) {
            m->input |= INPUT_B_PRESSED;
        }

        if (m->controller->buttonDown & Z_TRIG) {
            m->input |= INPUT_Z_DOWN;
        }

        if (m->controller->buttonPressed & Z_TRIG) {
            m->input |= INPUT_Z_PRESSED;
        }
    }

    if (m->input & INPUT_A_PRESSED) {
        m->framesSinceA = 0;
    }
    else if (m->framesSinceA < 0xFF) {
        m->framesSinceA++;
    }

    if (m->input & INPUT_B_PRESSED) {
        m->framesSinceB = 0;
    }
    else if (m->framesSinceB < 0xFF) {
        m->framesSinceB++;
    }
}

/**
 * Updates the joystick intended magnitude.
 */
void update_mario_joystick_inputs(struct MarioState* m) {
    struct Controller* controller = m->controller;
    f32 mag = ((controller->stickMag / 64.0f) * (controller->stickMag / 64.0f)) * 64.0f;

    if (m->squishTimer == 0) {
        m->intendedMag = mag / 2.0f;
    }
    else {
        m->intendedMag = mag / 8.0f;
    }

    if (m->intendedMag > 0.0f) {
        m->intendedYaw = atan2s(-controller->stickY, controller->stickX) + m->area->camera->yaw;
        m->input |= INPUT_NONZERO_ANALOG;
    }
    else {
        m->intendedYaw = m->faceAngle[1];
    }
}

/**
 * Resolves wall collisions, and updates a variety of inputs.
 */
void update_mario_geometry_inputs(struct MarioState* m, struct Surfaces* surfaceLists) {
    f32 gasLevel;
    f32 ceilToFloorDist;

    f32_find_wall_collision(surfaceLists, &m->pos[0], &m->pos[1], &m->pos[2], 60.0f, 50.0f);
    f32_find_wall_collision(surfaceLists, &m->pos[0], &m->pos[1], &m->pos[2], 30.0f, 24.0f);

    m->floorHeight = find_floor(surfaceLists, m->pos[0], m->pos[1], m->pos[2], &m->floor);

    // If Mario is OOB, move his position to his graphical position (which was not updated)
    // and check for the floor there.
    // This can cause errant behavior when combined with astral projection,
    // since the graphical position was not Mario's previous location.
    if (m->floor == NULL) {
        vec3f_copy(m->pos, m->marioObj->header.gfx.pos);
        m->floorHeight = find_floor(surfaceLists, m->pos[0], m->pos[1], m->pos[2], &m->floor);
    }

    m->ceilHeight = vec3f_find_ceil(surfaceLists, m->pos, m->floorHeight, &m->ceil);
    gasLevel = find_poison_gas_level(m->pos[0], m->pos[2]);
    m->waterLevel = find_water_level(m->pos[0], m->pos[2]);

    if (m->floor != NULL) {
        m->floorAngle = atan2s(m->floor->normal.z, m->floor->normal.x);

        if ((m->pos[1] > m->waterLevel - 40) && mario_floor_is_slippery(m)) {
            m->input |= INPUT_ABOVE_SLIDE;
        }

        if ((m->floor->flags & SURFACE_FLAG_DYNAMIC)
            || (m->ceil && m->ceil->flags & SURFACE_FLAG_DYNAMIC)) {
            ceilToFloorDist = m->ceilHeight - m->floorHeight;

            if ((0.0f <= ceilToFloorDist) && (ceilToFloorDist <= 150.0f)) {
                m->input |= INPUT_SQUISHED;
            }
        }

        if (m->pos[1] > m->floorHeight + 100.0f) {
            m->input |= INPUT_OFF_FLOOR;
        }

    }
    else {
        // This should never happen in this sim.
    }
}

/**
 * Handles Mario's input flags as well as a couple timers.
 */
void update_mario_inputs(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    m->particleFlags = 0;
    m->input = 0;
    m->collidedObjInteractTypes = m->marioObj->collidedObjInteractTypes;
    m->flags &= 0xFFFFFF;

    update_mario_button_inputs(m);
    update_mario_joystick_inputs(m);
    update_mario_geometry_inputs(m, surfaceLists);

    if (cameraData->gCameraMovementFlags & CAM_MOVE_C_UP_MODE) {
        if (m->action & ACT_FLAG_ALLOW_FIRST_PERSON) {
            m->input |= INPUT_FIRST_PERSON;
        }
        else {
            cameraData->gCameraMovementFlags &= ~CAM_MOVE_C_UP_MODE;
        }
    }

    if (!(m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED))) {
        m->input |= INPUT_UNKNOWN_5;
    }

    if (m->wallKickTimer > 0) {
        m->wallKickTimer--;
    }

    if (m->doubleJumpTimer > 0) {
        m->doubleJumpTimer--;
    }
}

/**
 * Both increments and decrements Mario's HP.
 */
void update_mario_health(struct MarioState* m) {
    s32 terrainIsSnow;

    if (m->health >= 0x100) {
        if (m->healCounter > 0) {
            m->health += 0x40;
            m->healCounter--;
        }
        if (m->hurtCounter > 0) {
            m->health -= 0x40;
            m->hurtCounter--;
        }

        if (m->health > 0x880) {
            m->health = 0x880;
        }
        if (m->health < 0x100) {
            m->health = 0xFF;
        }
    }
}

/**
 * Updates some basic info for camera usage.
 */
void update_mario_info_for_cam(struct MarioState* m) {
    m->statusForCamera->action = m->action;

    vec3s_copy(m->statusForCamera->faceAngle, m->faceAngle);

    if (!(m->flags & MARIO_UNKNOWN_25)) {
        vec3f_copy(m->statusForCamera->pos, m->pos);
    }
}

/**
 * Is a binary representation of the frames to flicker Mario's cap when the timer
 * is running out.
 *
 * Equals [1000]^5 . [100]^8 . [10]^9 . [1] in binary, which is
 * 100010001000100010001001001001001001001001001010101010101010101.
 */
u64 sCapFlickerFrames = 0x4444449249255555;

/**
 * Updates the Mario's cap, rendering, and hitbox.
 */
void mario_update_hitbox_and_cap_model(struct MarioState* m) {
    // Short hitbox for crouching/crawling/etc.
    if (m->action & ACT_FLAG_SHORT_HITBOX) {
        m->marioObj->hitboxHeight = 100.0f;
    }
    else {
        m->marioObj->hitboxHeight = 160.0f;
    }
}

void check_lava_boost(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    if (!(m->action & ACT_FLAG_RIDING_SHELL) && m->pos[1] < m->floorHeight + 10.0f) {
        if (!(m->flags & MARIO_METAL_CAP)) {
            m->hurtCounter += (m->flags & MARIO_CAP_ON_HEAD) ? 12 : 18;
        }

        update_mario_sound_and_camera(m, cameraData, surfaceLists);
        drop_and_set_mario_action(m, ACT_LAVA_BOOST, 0);
    }
}

void mario_handle_special_floors(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_CUTSCENE) {
        return;
    }

    if (m->floor != NULL) {
        s32 floorType = m->floor->type;
        
        if (!(m->action & ACT_FLAG_AIR) && !(m->action & ACT_FLAG_SWIMMING)) {
            switch (floorType) {
            case SURFACE_BURNING:
                check_lava_boost(m, cameraData, surfaceLists);
                break;
            }
        }
    }
}

/**
 * Main function for executing Mario's behavior.
 */
s32 execute_mario_action(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    s32 inLoop = TRUE;

    if (m->action) {
        update_mario_inputs(m, cameraData, surfaceLists);
        mario_handle_special_floors(m, cameraData, surfaceLists);

        // If Mario is OOB, stop executing actions.
        if (m->floor == NULL) {
            return 0;
        }

        // The function can loop through many action shifts in one frame,
        // which can lead to unexpected sub-frame behavior. Could potentially hang
        // if a loop of actions were found, but there has not been a situation found.
        while (inLoop) {
            switch (m->action & ACT_GROUP_MASK) {
            case ACT_GROUP_STATIONARY:
                inLoop = mario_execute_stationary_action(m, cameraData, surfaceLists);
                break;

            case ACT_GROUP_MOVING:
                inLoop = mario_execute_moving_action(m, surfaceLists);
                break;

            case ACT_GROUP_AIRBORNE:
                inLoop = mario_execute_airborne_action(m, surfaceLists);
                break;

            case ACT_GROUP_CUTSCENE:
                inLoop = mario_execute_cutscene_action(m, surfaceLists);
                break;

            case ACT_GROUP_AUTOMATIC:
                inLoop = mario_execute_automatic_action(m, surfaceLists);
                break;

            case ACT_GROUP_OBJECT:
                inLoop = mario_execute_object_action(m, surfaceLists);
                break;
            }
        }

        squish_mario_model(m);
        update_mario_health(m);
        update_mario_info_for_cam(m);
        mario_update_hitbox_and_cap_model(m);

        m->marioObj->oInteractStatus = 0;

        return m->particleFlags;
    }

    return 0;
}

void transfer_bully_speed(struct BullyCollisionData* obj1, struct BullyCollisionData* obj2) {
    f32 rx = obj2->posX - obj1->posX;
    f32 rz = obj2->posZ - obj1->posZ;

    //! Bully NaN crash
    f32 projectedV1 = (rx * obj1->velX + rz * obj1->velZ) / (rx * rx + rz * rz);
    f32 projectedV2 = (-rx * obj2->velX - rz * obj2->velZ) / (rx * rx + rz * rz);

    // Kill speed along r. Convert one object's speed along r and transfer it to
    // the other object.
    obj2->velX += obj2->conversionRatio * projectedV1 * rx - projectedV2 * -rx;
    obj2->velZ += obj2->conversionRatio * projectedV1 * rz - projectedV2 * -rz;

    obj1->velX += -projectedV1 * rx + obj1->conversionRatio * projectedV2 * -rx;
    obj1->velZ += -projectedV1 * rz + obj1->conversionRatio * projectedV2 * -rz;

    //! Bully battery
}

void init_bully_collision_data(struct BullyCollisionData* data, f32 posX, f32 posZ,
    f32 forwardVel, s16 yaw, f32 conversionRatio, f32 radius) {
    if (forwardVel < 0.0f) {
        forwardVel *= -1.0f;
        yaw += 0x8000;
    }

    data->radius = radius;
    data->conversionRatio = conversionRatio;
    data->posX = posX;
    data->posZ = posZ;
    data->velX = forwardVel * sins(yaw);
    data->velZ = forwardVel * coss(yaw);
}

void mario_bonk_reflection(struct MarioState* m, u32 negateSpeed) {
    if (m->wall != NULL) {
        s16 wallAngle = atan2s(m->wall->normal.z, m->wall->normal.x);
        m->faceAngle[1] = wallAngle - (s16)(m->faceAngle[1] - wallAngle);
    }

    if (negateSpeed) {
        mario_set_forward_vel(m, -m->forwardVel);
    }
    else {
        m->faceAngle[1] += 0x8000;
    }
}

u32 mario_push_off_steep_floor(struct MarioState* m, u32 action, u32 actionArg) {
    s16 floorDYaw = m->floorAngle - m->faceAngle[1];

    if (floorDYaw > -0x4000 && floorDYaw < 0x4000) {
        m->forwardVel = 16.0f;
        m->faceAngle[1] = m->floorAngle;
    }
    else {
        m->forwardVel = -16.0f;
        m->faceAngle[1] = m->floorAngle + 0x8000;
    }

    return set_mario_action(m, action, actionArg);
}

void stop_and_set_height_to_floor(struct MarioState* m) {
    struct Object* marioObj = m->marioObj;

    mario_set_forward_vel(m, 0.0f);
    m->vel[1] = 0.0f;

    //! This is responsible for some downwarps.
    m->pos[1] = m->floorHeight;

    vec3f_copy(marioObj->header.gfx.pos, m->pos);
    vec3s_set(marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);
}

s32 stationary_ground_step(struct MarioState* m, struct Surfaces* surfaceLists) {
    u32 takeStep;
    struct Object* marioObj = m->marioObj;
    u32 stepResult = GROUND_STEP_NONE;

    mario_set_forward_vel(m, 0.0f);

    //! This is responsible for several stationary downwarps.
    m->pos[1] = m->floorHeight;

    vec3f_copy(marioObj->header.gfx.pos, m->pos);
    vec3s_set(marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);

    return stepResult;
}

static s32 perform_ground_quarter_step(struct MarioState* m, struct Surfaces* surfaceLists, Vec3f nextPos) {
    UNUSED struct Surface* lowerWall;
    struct Surface* upperWall;
    struct Surface* ceil;
    struct Surface* floor;
    f32 ceilHeight;
    f32 floorHeight;
    f32 waterLevel;

    lowerWall = resolve_and_return_wall_collisions(surfaceLists, nextPos, 30.0f, 24.0f);
    upperWall = resolve_and_return_wall_collisions(surfaceLists, nextPos, 60.0f, 50.0f);

    floorHeight = find_floor(surfaceLists, nextPos[0], nextPos[1], nextPos[2], &floor);
    ceilHeight = vec3f_find_ceil(surfaceLists, nextPos, floorHeight, &ceil);

    waterLevel = find_water_level(nextPos[0], nextPos[2]);

    m->wall = upperWall;

    if (floor == NULL) {
        return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
    }

    if (nextPos[1] > floorHeight + 100.0f) {
        if (nextPos[1] + 160.0f >= ceilHeight) {
            return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
        }

        vec3f_copy(m->pos, nextPos);
        m->floor = floor;
        m->floorHeight = floorHeight;
        return GROUND_STEP_LEFT_GROUND;
    }

    if (floorHeight + 160.0f >= ceilHeight) {
        return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
    }

    vec3f_set(m->pos, nextPos[0], floorHeight, nextPos[2]);
    m->floor = floor;
    m->floorHeight = floorHeight;

    if (upperWall != NULL) {
        s16 wallDYaw = atan2s(upperWall->normal.z, upperWall->normal.x) - m->faceAngle[1];

        if (wallDYaw >= 0x2AAA && wallDYaw <= 0x5555) {
            return GROUND_STEP_NONE;
        }
        if (wallDYaw <= -0x2AAA && wallDYaw >= -0x5555) {
            return GROUND_STEP_NONE;
        }

        return GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS;
    }

    return GROUND_STEP_NONE;
}

s32 perform_ground_step(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 i;
    u32 stepResult;
    Vec3f intendedPos;

    for (i = 0; i < 4; i++) {
        intendedPos[0] = m->pos[0] + m->floor->normal.y * (m->vel[0] / 4.0f);
        intendedPos[2] = m->pos[2] + m->floor->normal.y * (m->vel[2] / 4.0f);
        intendedPos[1] = m->pos[1];

        stepResult = perform_ground_quarter_step(m, surfaceLists, intendedPos);
        if (stepResult == GROUND_STEP_LEFT_GROUND || stepResult == GROUND_STEP_HIT_WALL_STOP_QSTEPS) {
            break;
        }
    }

    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);

    if (stepResult == GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS) {
        stepResult = GROUND_STEP_HIT_WALL;
    }
    return stepResult;
}

u32 check_ledge_grab(struct MarioState* m, struct Surfaces* surfaceLists, struct Surface* wall, Vec3f intendedPos, Vec3f nextPos) {
    struct Surface* ledgeFloor;
    Vec3f ledgePos;
    f32 displacementX;
    f32 displacementZ;

    if (m->vel[1] > 0) {
        return FALSE;
    }

    displacementX = nextPos[0] - intendedPos[0];
    displacementZ = nextPos[2] - intendedPos[2];

    // Only ledge grab if the wall displaced Mario in the opposite direction of
    // his velocity.
    if (displacementX * m->vel[0] + displacementZ * m->vel[2] > 0.0f) {
        return FALSE;
    }

    //! Since the search for floors starts at y + 160, we will sometimes grab
    // a higher ledge than expected (glitchy ledge grab)
    ledgePos[0] = nextPos[0] - wall->normal.x * 60.0f;
    ledgePos[2] = nextPos[2] - wall->normal.z * 60.0f;
    ledgePos[1] = find_floor(surfaceLists, ledgePos[0], nextPos[1] + 160.0f, ledgePos[2], &ledgeFloor);

    if (ledgePos[1] - nextPos[1] <= 100.0f) {
        return FALSE;
    }

    vec3f_copy(m->pos, ledgePos);
    m->floor = ledgeFloor;
    m->floorHeight = ledgePos[1];

    m->floorAngle = atan2s(ledgeFloor->normal.z, ledgeFloor->normal.x);

    m->faceAngle[0] = 0;
    m->faceAngle[1] = atan2s(wall->normal.z, wall->normal.x) + 0x8000;
    return TRUE;
}

s32 perform_air_quarter_step(struct MarioState* m, struct Surfaces* surfaceLists, Vec3f intendedPos, u32 stepArg) {
    s16 wallDYaw;
    Vec3f nextPos;
    struct Surface* upperWall;
    struct Surface* lowerWall;
    struct Surface* ceil;
    struct Surface* floor;
    f32 ceilHeight;
    f32 floorHeight;
    f32 waterLevel;

    vec3f_copy(nextPos, intendedPos);

    upperWall = resolve_and_return_wall_collisions(surfaceLists, nextPos, 150.0f, 50.0f);
    lowerWall = resolve_and_return_wall_collisions(surfaceLists, nextPos, 30.0f, 50.0f);

    floorHeight = find_floor(surfaceLists, nextPos[0], nextPos[1], nextPos[2], &floor);
    ceilHeight = vec3f_find_ceil(surfaceLists, nextPos, floorHeight, &ceil);

    waterLevel = find_water_level(nextPos[0], nextPos[2]);

    m->wall = NULL;

    //! The water pseudo floor is not referenced when your intended qstep is
    // out of bounds, so it won't detect you as landing.

    if (floor == NULL) {
        if (nextPos[1] <= m->floorHeight) {
            m->pos[1] = m->floorHeight;
            return AIR_STEP_LANDED;
        }

        m->pos[1] = nextPos[1];
        return AIR_STEP_HIT_WALL;
    }

    //! This check uses f32, but findFloor uses short (overflow jumps)
    if (nextPos[1] <= floorHeight) {
        if (ceilHeight - floorHeight > 160.0f) {
            m->pos[0] = nextPos[0];
            m->pos[2] = nextPos[2];
            m->floor = floor;
            m->floorHeight = floorHeight;
        }

        //! When ceilHeight - floorHeight <= 160, the step result says that
        // Mario landed, but his movement is cancelled and his referenced floor
        // isn't updated (pedro spots)
        m->pos[1] = floorHeight;
        return AIR_STEP_LANDED;
    }

    if (nextPos[1] + 160.0f > ceilHeight) {
        if (m->vel[1] >= 0.0f) {
            m->vel[1] = 0.0f;

            //! Uses referenced ceiling instead of ceil (ceiling hang upwarp)
            if ((stepArg & AIR_STEP_CHECK_HANG) && m->ceil != NULL
                && m->ceil->type == SURFACE_HANGABLE) {
                return AIR_STEP_GRABBED_CEILING;
            }

            return AIR_STEP_NONE;
        }

        //! Potential subframe downwarp->upwarp?
        if (nextPos[1] <= m->floorHeight) {
            m->pos[1] = m->floorHeight;
            return AIR_STEP_LANDED;
        }

        m->pos[1] = nextPos[1];
        return AIR_STEP_HIT_WALL;
    }

    //! When the wall is not completely vertical or there is a slight wall
    // misalignment, you can activate these conditions in unexpected situations
    if ((stepArg & AIR_STEP_CHECK_LEDGE_GRAB) && upperWall == NULL && lowerWall != NULL) {
        if (check_ledge_grab(m, surfaceLists, lowerWall, intendedPos, nextPos)) {
            return AIR_STEP_GRABBED_LEDGE;
        }

        vec3f_copy(m->pos, nextPos);
        m->floor = floor;
        m->floorHeight = floorHeight;
        return AIR_STEP_NONE;
    }

    vec3f_copy(m->pos, nextPos);
    m->floor = floor;
    m->floorHeight = floorHeight;

    if (upperWall != NULL || lowerWall != NULL) {
        m->wall = upperWall != NULL ? upperWall : lowerWall;
        wallDYaw = atan2s(m->wall->normal.z, m->wall->normal.x) - m->faceAngle[1];

        if (wallDYaw < -0x6000 || wallDYaw > 0x6000) {
            m->flags |= MARIO_UNKNOWN_30;
            return AIR_STEP_HIT_WALL;
        }
    }

    return AIR_STEP_NONE;
}

u32 should_strengthen_gravity_for_jump_ascent(struct MarioState* m) {
    if (!(m->flags & MARIO_UNKNOWN_08)) {
        return FALSE;
    }

    if (m->action & (ACT_FLAG_INTANGIBLE | ACT_FLAG_INVULNERABLE)) {
        return FALSE;
    }

    if (!(m->input & INPUT_A_DOWN) && m->vel[1] > 20.0f) {
        return (m->action & ACT_FLAG_CONTROL_JUMP_HEIGHT) != 0;
    }

    return FALSE;
}

void apply_gravity(struct MarioState* m) {
    if (m->action == ACT_LONG_JUMP || m->action == ACT_SLIDE_KICK
        || m->action == ACT_BBH_ENTER_SPIN) {
        m->vel[1] -= 2.0f;
        if (m->vel[1] < -75.0f) {
            m->vel[1] = -75.0f;
        }
    }
    else if (m->action == ACT_LAVA_BOOST || m->action == ACT_FALL_AFTER_STAR_GRAB) {
        m->vel[1] -= 3.2f;
        if (m->vel[1] < -65.0f) {
            m->vel[1] = -65.0f;
        }
    }
    else if (should_strengthen_gravity_for_jump_ascent(m)) {
        m->vel[1] /= 4.0f;
    }
    else {
        m->vel[1] -= 4.0f;
        if (m->vel[1] < -75.0f) {
            m->vel[1] = -75.0f;
        }
    }
}

s32 perform_air_step(struct MarioState* m, struct Surfaces* surfaceLists, u32 stepArg) {
    Vec3f intendedPos;
    s32 i;
    s32 quarterStepResult;
    s32 stepResult = AIR_STEP_NONE;

    m->wall = NULL;

    for (i = 0; i < 4; i++) {
        intendedPos[0] = m->pos[0] + m->vel[0] / 4.0f;
        intendedPos[1] = m->pos[1] + m->vel[1] / 4.0f;
        intendedPos[2] = m->pos[2] + m->vel[2] / 4.0f;

        quarterStepResult = perform_air_quarter_step(m, surfaceLists, intendedPos, stepArg);

        //! On one qf, hit OOB/ceil/wall to store the 2 return value, and continue
        // getting 0s until your last qf. Graze a wall on your last qf, and it will
        // return the stored 2 with a sharply angled reference wall. (some gwks)

        if (quarterStepResult != AIR_STEP_NONE) {
            stepResult = quarterStepResult;
        }

        if (quarterStepResult == AIR_STEP_LANDED || quarterStepResult == AIR_STEP_GRABBED_LEDGE
            || quarterStepResult == AIR_STEP_GRABBED_CEILING
            || quarterStepResult == AIR_STEP_HIT_LAVA_WALL) {
            break;
        }
    }

    if (m->vel[1] >= 0.0f) {
        m->peakHeight = m->pos[1];
    }

    if (m->action != ACT_FLYING) {
        apply_gravity(m);
    }

    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set(m->marioObj->header.gfx.angle, 0, m->faceAngle[1], 0);

    return stepResult;
}

// They had these functions the whole time and never used them? Lol

void set_vel_from_pitch_and_yaw(struct MarioState* m) {
    m->vel[0] = m->forwardVel * coss(m->faceAngle[0]) * sins(m->faceAngle[1]);
    m->vel[1] = m->forwardVel * sins(m->faceAngle[0]);
    m->vel[2] = m->forwardVel * coss(m->faceAngle[0]) * coss(m->faceAngle[1]);
}

void set_vel_from_yaw(struct MarioState* m) {
    m->vel[0] = m->slideVelX = m->forwardVel * sins(m->faceAngle[1]);
    m->vel[1] = 0.0f;
    m->vel[2] = m->slideVelZ = m->forwardVel * coss(m->faceAngle[1]);
}

void update_air_with_turn(struct MarioState* m) {
    f32 dragThreshold;
    s16 intendedDYaw;
    f32 intendedMag;

    dragThreshold = m->action == ACT_LONG_JUMP ? 48.0f : 32.0f;
    m->forwardVel = approach_f32(m->forwardVel, 0.0f, 0.35f, 0.35f);

    if (m->input & INPUT_NONZERO_ANALOG) {
        intendedDYaw = m->intendedYaw - m->faceAngle[1];
        intendedMag = m->intendedMag / 32.0f;

        m->forwardVel += 1.5f * coss(intendedDYaw) * intendedMag;
        m->faceAngle[1] += 512.0f * sins(intendedDYaw) * intendedMag;
    }

    //! Uncapped air speed. Net positive when moving forward.
    if (m->forwardVel > dragThreshold) {
        m->forwardVel -= 1.0f;
    }
    if (m->forwardVel < -16.0f) {
        m->forwardVel += 2.0f;
    }

    m->vel[0] = m->slideVelX = m->forwardVel * sins(m->faceAngle[1]);
    m->vel[2] = m->slideVelZ = m->forwardVel * coss(m->faceAngle[1]);
}

void update_air_without_turn(struct MarioState* m) {
    f32 sidewaysSpeed = 0.0f;
    f32 dragThreshold;
    s16 intendedDYaw;
    f32 intendedMag;

    dragThreshold = m->action == ACT_LONG_JUMP ? 48.0f : 32.0f;
    m->forwardVel = approach_f32(m->forwardVel, 0.0f, 0.35f, 0.35f);

    if (m->input & INPUT_NONZERO_ANALOG) {
        intendedDYaw = m->intendedYaw - m->faceAngle[1];
        intendedMag = m->intendedMag / 32.0f;

        m->forwardVel += intendedMag * coss(intendedDYaw) * 1.5f;
        sidewaysSpeed = intendedMag * sins(intendedDYaw) * 10.0f;
    }

    //! Uncapped air speed. Net positive when moving forward.
    if (m->forwardVel > dragThreshold) {
        m->forwardVel -= 1.0f;
    }
    if (m->forwardVel < -16.0f) {
        m->forwardVel += 2.0f;
    }

    m->slideVelX = m->forwardVel * sins(m->faceAngle[1]);
    m->slideVelZ = m->forwardVel * coss(m->faceAngle[1]);

    m->slideVelX += sidewaysSpeed * sins(m->faceAngle[1] + 0x4000);
    m->slideVelZ += sidewaysSpeed * coss(m->faceAngle[1] + 0x4000);

    m->vel[0] = m->slideVelX;
    m->vel[2] = m->slideVelZ;
}

void update_lava_boost_or_twirling(struct MarioState* m) {
    s16 intendedDYaw;
    f32 intendedMag;

    if (m->input & INPUT_NONZERO_ANALOG) {
        intendedDYaw = m->intendedYaw - m->faceAngle[1];
        intendedMag = m->intendedMag / 32.0f;

        m->forwardVel += coss(intendedDYaw) * intendedMag;
        m->faceAngle[1] += sins(intendedDYaw) * intendedMag * 1024.0f;

        if (m->forwardVel < 0.0f) {
            m->faceAngle[1] += 0x8000;
            m->forwardVel *= -1.0f;
        }

        if (m->forwardVel > 32.0f) {
            m->forwardVel -= 2.0f;
        }
    }

    m->vel[0] = m->slideVelX = m->forwardVel * sins(m->faceAngle[1]);
    m->vel[2] = m->slideVelZ = m->forwardVel * coss(m->faceAngle[1]);
}

u32 common_air_action_step(struct MarioState* m, struct Surfaces* surfaceLists, u32 landAction, s32 animation, u32 stepArg) {
    u32 stepResult;

    update_air_without_turn(m);

    stepResult = perform_air_step(m, surfaceLists, stepArg);
    switch (stepResult) {
    case AIR_STEP_NONE:
        set_mario_animation(m, animation);
        break;

    case AIR_STEP_LANDED:
        set_mario_action(m, landAction, 0);
        break;

    case AIR_STEP_HIT_WALL:
        set_mario_animation(m, animation);

        if (m->forwardVel > 16.0f) {
            mario_bonk_reflection(m, FALSE);
            m->faceAngle[1] += 0x8000;

            if (m->wall != NULL) {
                set_mario_action(m, ACT_AIR_HIT_WALL, 0);
            }
            else {
                if (m->vel[1] > 0.0f) {
                    m->vel[1] = 0.0f;
                }

                //! Hands-free holding. Bonking while no wall is referenced
                // sets Mario's action to a non-holding action without
                // dropping the object, causing the hands-free holding
                // glitch. This can be achieved using an exposed ceiling,
                // out of bounds, grazing the bottom of a wall while
                // falling such that the final quarter step does not find a
                // wall collision, or by rising into the top of a wall such
                // that the final quarter step detects a ledge, but you are
                // not able to ledge grab it.
                if (m->forwardVel >= 38.0f) {
                    set_mario_action(m, ACT_BACKWARD_AIR_KB, 0);
                }
                else {
                    if (m->forwardVel > 8.0f) {
                        mario_set_forward_vel(m, -8.0f);
                    }
                    return set_mario_action(m, ACT_SOFT_BONK, 0);
                }
            }
        }
        else {
            mario_set_forward_vel(m, 0.0f);
        }
        break;

    case AIR_STEP_GRABBED_LEDGE:
        set_mario_animation(m, MARIO_ANIM_IDLE_ON_LEDGE);
        drop_and_set_mario_action(m, ACT_LEDGE_GRAB, 0);
        break;

    case AIR_STEP_GRABBED_CEILING:
        set_mario_action(m, ACT_START_HANGING, 0);
        break;
    }

    return stepResult;
}

s32 act_freefall(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 animation;

    if (m->input & INPUT_B_PRESSED) {
        return set_mario_action(m, ACT_DIVE, 0);
    }

    if (m->input & INPUT_Z_PRESSED) {
        return set_mario_action(m, ACT_GROUND_POUND, 0);
    }

    switch (m->actionArg) {
    case 0:
        animation = MARIO_ANIM_GENERAL_FALL;
        break;
    case 1:
        animation = MARIO_ANIM_FALL_FROM_SLIDE;
        break;
    case 2:
        animation = MARIO_ANIM_FALL_FROM_SLIDE_KICK;
        break;
    }

    common_air_action_step(m, surfaceLists, ACT_FREEFALL_LAND, animation, AIR_STEP_CHECK_LEDGE_GRAB);
    return FALSE;
}

s32 act_dive(struct MarioState* m, struct Surfaces* surfaceLists) {
    set_mario_animation(m, MARIO_ANIM_DIVE);

    update_air_without_turn(m);

    switch (perform_air_step(m, surfaceLists, 0)) {
    case AIR_STEP_NONE:
        if (m->vel[1] < 0.0f && m->faceAngle[0] > -0x2AAA) {
            m->faceAngle[0] -= 0x200;
            if (m->faceAngle[0] < -0x2AAA) {
                m->faceAngle[0] = -0x2AAA;
            }
        }
        m->marioObj->header.gfx.angle[0] = -m->faceAngle[0];
        break;

    case AIR_STEP_LANDED:
        set_mario_action(m, ACT_DIVE_SLIDE, 0);
        m->faceAngle[0] = 0;
        break;

    case AIR_STEP_HIT_WALL:
        mario_bonk_reflection(m, TRUE);
        m->faceAngle[0] = 0;

        if (m->vel[1] > 0.0f) {
            m->vel[1] = 0.0f;
        }

        drop_and_set_mario_action(m, ACT_BACKWARD_AIR_KB, 0);
        break;
    }

    return FALSE;
}

u32 common_air_knockback_step(struct MarioState* m, struct Surfaces* surfaceLists, u32 landAction, u32 hardFallAction, s32 animation,
    f32 speed) {
    u32 stepResult;

    mario_set_forward_vel(m, speed);

    stepResult = perform_air_step(m, surfaceLists, 0);
    switch (stepResult) {
    case AIR_STEP_NONE:
        set_mario_animation(m, animation);
        break;

    case AIR_STEP_LANDED:
        set_mario_action(m, landAction, m->actionArg);
        break;

    case AIR_STEP_HIT_WALL:
        set_mario_animation(m, MARIO_ANIM_BACKWARD_AIR_KB);
        mario_bonk_reflection(m, FALSE);

        if (m->vel[1] > 0.0f) {
            m->vel[1] = 0.0f;
        }

        mario_set_forward_vel(m, -speed);
        break;
    }

    return stepResult;
}

s32 act_backward_air_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    common_air_knockback_step(m, surfaceLists, ACT_BACKWARD_GROUND_KB, ACT_HARD_BACKWARD_GROUND_KB, 0x0002, -16.0f);
    return FALSE;
}

s32 act_forward_air_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    common_air_knockback_step(m, surfaceLists, ACT_FORWARD_GROUND_KB, ACT_HARD_FORWARD_GROUND_KB, 0x002D, 16.0f);
    return FALSE;
}

s32 act_hard_backward_air_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    common_air_knockback_step(m, surfaceLists, ACT_HARD_BACKWARD_GROUND_KB, ACT_HARD_BACKWARD_GROUND_KB, 0x0002,
        -16.0f);
    return FALSE;
}

s32 act_hard_forward_air_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    common_air_knockback_step(m, surfaceLists, ACT_HARD_FORWARD_GROUND_KB, ACT_HARD_FORWARD_GROUND_KB, 0x002D, 16.0f);
    return FALSE;
}

s32 act_soft_bonk(struct MarioState* m, struct Surfaces* surfaceLists) {
    common_air_knockback_step(m, surfaceLists, ACT_FREEFALL_LAND, ACT_HARD_BACKWARD_GROUND_KB, 0x0056, m->forwardVel);
    return FALSE;
}

s32 act_air_hit_wall(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (++(m->actionTimer) <= 2) {
    }
    else if (m->forwardVel >= 38.0f) {
        m->wallKickTimer = 5;
        if (m->vel[1] > 0.0f) {
            m->vel[1] = 0.0f;
        }

        return set_mario_action(m, ACT_BACKWARD_AIR_KB, 0);
    }
    else {
        m->wallKickTimer = 5;
        if (m->vel[1] > 0.0f) {
            m->vel[1] = 0.0f;
        }

        if (m->forwardVel > 8.0f) {
            mario_set_forward_vel(m, -8.0f);
        }
        return set_mario_action(m, ACT_SOFT_BONK, 0);
    }

    return set_mario_animation(m, MARIO_ANIM_START_WALLKICK);
}

s32 act_forward_rollout(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->actionState == 0) {
        m->vel[1] = 30.0f;
        m->actionState = 1;
    }

    update_air_without_turn(m);

    switch (perform_air_step(m, surfaceLists, 0)) {
    case AIR_STEP_NONE:
        if (m->actionState == 1) {
            if (set_mario_animation(m, MARIO_ANIM_FORWARD_SPINNING) == 4) {
            }
        }
        else {
            set_mario_animation(m, MARIO_ANIM_GENERAL_FALL);
        }
        break;

    case AIR_STEP_LANDED:
        set_mario_action(m, ACT_FREEFALL_LAND_STOP, 0);
        break;

    case AIR_STEP_HIT_WALL:
        mario_set_forward_vel(m, 0.0f);
        break;
    }

    if (m->actionState == 1 && is_anim_past_end(m)) {
        m->actionState = 2;
    }
    return FALSE;
}

s32 act_backward_rollout(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->actionState == 0) {
        m->vel[1] = 30.0f;
        m->actionState = 1;
    }

    update_air_without_turn(m);

    switch (perform_air_step(m, surfaceLists, 0)) {
    case AIR_STEP_NONE:
        if (m->actionState == 1) {
            if (set_mario_animation(m, MARIO_ANIM_BACKWARD_SPINNING) == 4) {
            }
        }
        else {
            set_mario_animation(m, MARIO_ANIM_GENERAL_FALL);
        }
        break;

    case AIR_STEP_LANDED:
        set_mario_action(m, ACT_FREEFALL_LAND_STOP, 0);
        break;

    case AIR_STEP_HIT_WALL:
        mario_set_forward_vel(m, 0.0f);
        break;
    }

    if (m->actionState == 1 && m->marioObj->header.gfx.animInfo.animFrame == 2) {
        m->actionState = 2;
    }
    return FALSE;
}

s32 act_butt_slide_air(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (++(m->actionTimer) > 30 && m->pos[1] - m->floorHeight > 500.0f) {
        return set_mario_action(m, ACT_FREEFALL, 1);
    }

    update_air_with_turn(m);

    switch (perform_air_step(m, surfaceLists, 0)) {
    case AIR_STEP_LANDED:
        if (m->actionState == 0 && m->vel[1] < 0.0f && m->floor->normal.y >= 0.9848077f) {
            m->vel[1] = -m->vel[1] / 2.0f;
            m->actionState = 1;
        }
        else {
            set_mario_action(m, ACT_BUTT_SLIDE, 0);
        }
        break;

    case AIR_STEP_HIT_WALL:
        if (m->vel[1] > 0.0f) {
            m->vel[1] = 0.0f;
        }
        set_mario_action(m, ACT_BACKWARD_AIR_KB, 0);
        break;
    }

    set_mario_animation(m, MARIO_ANIM_SLIDE);
    return FALSE;
}

s32 act_lava_boost(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (!(m->input & INPUT_NONZERO_ANALOG)) {
        m->forwardVel = approach_f32(m->forwardVel, 0.0f, 0.35f, 0.35f);
    }

    update_lava_boost_or_twirling(m);

    switch (perform_air_step(m, surfaceLists, 0)) {
    case AIR_STEP_LANDED:
        if (m->floor->type == SURFACE_BURNING) {
            m->actionState = 0;
            if (!(m->flags & MARIO_METAL_CAP)) {
                m->hurtCounter += (m->flags & MARIO_CAP_ON_HEAD) ? 12 : 18;
            }
            m->vel[1] = 84.0f;
        }
        else {
            if (m->actionState < 2 && m->vel[1] < 0.0f) {
                m->vel[1] = -m->vel[1] * 0.4f;
                mario_set_forward_vel(m, m->forwardVel * 0.5f);
                m->actionState++;
            }
            else {
                set_mario_action(m, ACT_LAVA_BOOST_LAND, 0);
            }
        }
        break;

    case AIR_STEP_HIT_WALL:
        mario_bonk_reflection(m, FALSE);
        break;
    }

    set_mario_animation(m, MARIO_ANIM_FIRE_LAVA_BURN);

    return FALSE;
}

s32 act_slide_kick(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->actionState == 0 && m->actionTimer == 0) {
        set_mario_animation(m, MARIO_ANIM_SLIDE_KICK);
    }

    if (++(m->actionTimer) > 30 && m->pos[1] - m->floorHeight > 500.0f) {
        return set_mario_action(m, ACT_FREEFALL, 2);
    }

    update_air_without_turn(m);

    switch (perform_air_step(m, surfaceLists, 0)) {
    case AIR_STEP_NONE:
        if (m->actionState == 0) {
            m->marioObj->header.gfx.angle[0] = atan2s(m->forwardVel, -m->vel[1]);
            if (m->marioObj->header.gfx.angle[0] > 0x1800) {
                m->marioObj->header.gfx.angle[0] = 0x1800;
            }
        }
        break;

    case AIR_STEP_LANDED:
        if (m->actionState == 0 && m->vel[1] < 0.0f) {
            m->vel[1] = -m->vel[1] / 2.0f;
            m->actionState = 1;
            m->actionTimer = 0;
        }
        else {
            set_mario_action(m, ACT_SLIDE_KICK_SLIDE, 0);
        }
        break;

    case AIR_STEP_HIT_WALL:
        if (m->vel[1] > 0.0f) {
            m->vel[1] = 0.0f;
        }

        set_mario_action(m, ACT_BACKWARD_AIR_KB, 0);
        break;
    }

    return FALSE;
}

s32 check_common_airborne_cancels(struct MarioState* m) {
    if (m->input & INPUT_SQUISHED) {
        return drop_and_set_mario_action(m, ACT_SQUISHED, 0);
    }

    m->quicksandDepth = 0.0f;
    return FALSE;
}

s32 mario_execute_airborne_action(struct MarioState* m, struct Surfaces* surfaceLists) {
    u32 cancel;

    if (check_common_airborne_cancels(m)) {
        return TRUE;
    }

    /* clang-format off */
    switch (m->action) {
    case ACT_FREEFALL:             cancel = act_freefall(m, surfaceLists);             break;
    case ACT_DIVE:                 cancel = act_dive(m, surfaceLists);                 break;
    case ACT_BACKWARD_AIR_KB:      cancel = act_backward_air_kb(m, surfaceLists);      break;
    case ACT_FORWARD_AIR_KB:       cancel = act_forward_air_kb(m, surfaceLists);       break;
    case ACT_HARD_FORWARD_AIR_KB:  cancel = act_hard_forward_air_kb(m, surfaceLists);  break;
    case ACT_HARD_BACKWARD_AIR_KB: cancel = act_hard_backward_air_kb(m, surfaceLists); break;
    case ACT_SOFT_BONK:            cancel = act_soft_bonk(m, surfaceLists);            break;
    case ACT_AIR_HIT_WALL:         cancel = act_air_hit_wall(m, surfaceLists);         break;
    case ACT_FORWARD_ROLLOUT:      cancel = act_forward_rollout(m, surfaceLists);      break;
    case ACT_BUTT_SLIDE_AIR:       cancel = act_butt_slide_air(m, surfaceLists);       break;
    case ACT_LAVA_BOOST:           cancel = act_lava_boost(m, surfaceLists);           break;
    case ACT_BACKWARD_ROLLOUT:     cancel = act_backward_rollout(m, surfaceLists);     break;
    case ACT_SLIDE_KICK:           cancel = act_slide_kick(m, surfaceLists);           break;
    }
    /* clang-format on */

    return cancel;
}

s32 let_go_of_ledge(struct MarioState* m, struct Surfaces* surfaceLists) {
    f32 floorHeight;
    struct Surface* floor;

    m->vel[1] = 0.0f;
    m->forwardVel = -8.0f;
    m->pos[0] -= 60.0f * sins(m->faceAngle[1]);
    m->pos[2] -= 60.0f * coss(m->faceAngle[1]);

    floorHeight = find_floor(surfaceLists, m->pos[0], m->pos[1], m->pos[2], &floor);
    if (floorHeight < m->pos[1] - 100.0f) {
        m->pos[1] -= 100.0f;
    }
    else {
        m->pos[1] = floorHeight;
    }

    return set_mario_action(m, ACT_SOFT_BONK, 0);
}

void climb_up_ledge(struct MarioState* m) {
    set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_LEFT);
    m->pos[0] += 14.0f * sins(m->faceAngle[1]);
    m->pos[2] += 14.0f * coss(m->faceAngle[1]);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
}

void update_ledge_climb_camera(struct MarioState* m) {
    f32 sp4;

    if (m->actionTimer < 14) {
        sp4 = m->actionTimer;
    }
    else {
        sp4 = 14.0f;
    }
    m->statusForCamera->pos[0] = m->pos[0] + sp4 * sins(m->faceAngle[1]);
    m->statusForCamera->pos[2] = m->pos[2] + sp4 * coss(m->faceAngle[1]);
    m->statusForCamera->pos[1] = m->pos[1];
    m->actionTimer++;
    m->flags |= MARIO_UNKNOWN_25;
}

void update_ledge_climb(struct MarioState* m, s32 animation, u32 endAction) {
    stop_and_set_height_to_floor(m);

    set_mario_animation(m, animation);
    if (is_anim_at_end(m)) {
        set_mario_action(m, endAction, 0);
        if (endAction == ACT_IDLE) {
            climb_up_ledge(m);
        }
    }
}

s32 act_ledge_grab(struct MarioState* m, struct Surfaces* surfaceLists) {
    f32 heightAboveFloor;
    s16 intendedDYaw = m->intendedYaw - m->faceAngle[1];
    s32 hasSpaceForMario = (m->ceilHeight - m->floorHeight >= 160.0f);

    if (m->actionTimer < 10) {
        m->actionTimer++;
    }

    if (m->floor->normal.y < 0.9063078f) {
        return let_go_of_ledge(m, surfaceLists);
    }

    if (m->input & (INPUT_Z_PRESSED | INPUT_OFF_FLOOR)) {
        return let_go_of_ledge(m, surfaceLists);
    }

    if (m->actionTimer == 10 && (m->input & INPUT_NONZERO_ANALOG)) {
        if (intendedDYaw >= -0x4000 && intendedDYaw <= 0x4000) {
            if (hasSpaceForMario) {
                return set_mario_action(m, ACT_LEDGE_CLIMB_SLOW_1, 0);
            }
        }
        else {
            return let_go_of_ledge(m, surfaceLists);
        }
    }

    heightAboveFloor = m->pos[1] - find_floor_height_relative_polar(m, surfaceLists, -0x8000, 30.0f);
    if (hasSpaceForMario && heightAboveFloor < 100.0f) {
        return set_mario_action(m, ACT_LEDGE_CLIMB_FAST, 0);
    }

    stop_and_set_height_to_floor(m);
    set_mario_animation(m, MARIO_ANIM_IDLE_ON_LEDGE);

    return FALSE;
}

s32 act_ledge_climb_slow(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return let_go_of_ledge(m, surfaceLists);
    }

    if (m->actionTimer >= 28
        && (m->input
            & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE))) {
        climb_up_ledge(m);
        return check_common_action_exits(m);
    }

    update_ledge_climb(m, MARIO_ANIM_SLOW_LEDGE_GRAB, ACT_IDLE);

    update_ledge_climb_camera(m);
    if (m->marioObj->header.gfx.animInfo.animFrame == 17) {
        m->action = ACT_LEDGE_CLIMB_SLOW_2;
    }

    return FALSE;
}

s32 act_ledge_climb_down(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return let_go_of_ledge(m, surfaceLists);
    }

    update_ledge_climb(m, MARIO_ANIM_CLIMB_DOWN_LEDGE, ACT_LEDGE_GRAB);
    m->actionArg = 1;

    return FALSE;
}

s32 act_ledge_climb_fast(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return let_go_of_ledge(m, surfaceLists);
    }

    update_ledge_climb(m, MARIO_ANIM_FAST_LEDGE_GRAB, ACT_IDLE);

    update_ledge_climb_camera(m);

    return FALSE;
}

s32 mario_execute_automatic_action(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 cancel;

    m->quicksandDepth = 0.0f;

    /* clang-format off */
    switch (m->action) {
    case ACT_LEDGE_GRAB:             cancel = act_ledge_grab(m, surfaceLists);             break;
    case ACT_LEDGE_CLIMB_SLOW_1:     cancel = act_ledge_climb_slow(m, surfaceLists);       break;
    case ACT_LEDGE_CLIMB_SLOW_2:     cancel = act_ledge_climb_slow(m, surfaceLists);       break;
    case ACT_LEDGE_CLIMB_DOWN:       cancel = act_ledge_climb_down(m, surfaceLists);       break;
    case ACT_LEDGE_CLIMB_FAST:       cancel = act_ledge_climb_fast(m, surfaceLists);       break;
    }
    /* clang-format on */

    return cancel;
}

s32 act_squished(struct MarioState* m, struct Surfaces* surfaceLists) {
    f32 squishAmount;
    f32 spaceUnderCeil;
    s16 surfAngle;
    s32 underSteepSurf = FALSE; // seems to be responsible for setting velocity?

    if ((spaceUnderCeil = m->ceilHeight - m->floorHeight) < 0) {
        spaceUnderCeil = 0;
    }

    switch (m->actionState) {
    case 0:
        if (spaceUnderCeil > 160.0f) {
            m->squishTimer = 0;
            return set_mario_action(m, ACT_IDLE, 0);
        }

        m->squishTimer = 0xFF;

        if (spaceUnderCeil >= 10.1f) {
            // Mario becomes a pancake
            squishAmount = spaceUnderCeil / 160.0f;
            vec3f_set(m->marioObj->header.gfx.scale, 2.0f - squishAmount, squishAmount,
                2.0f - squishAmount);
        }
        else {
            if (!(m->flags & MARIO_METAL_CAP) && m->invincTimer == 0) {
                // cap on: 3 units; cap off: 4.5 units
                m->hurtCounter += m->flags & MARIO_CAP_ON_HEAD ? 12 : 18;
            }

            // Both of the 1.8's are really floats, but one of them has to
            // be written as a double for this to match on -O2.
            vec3f_set(m->marioObj->header.gfx.scale, 1.8, 0.05f, 1.8f);

            m->actionState = 1;
        }
        break;
    case 1:
        if (spaceUnderCeil >= 30.0f) {
            m->actionState = 2;
        }
        break;
    case 2:
        m->actionTimer++;
        if (m->actionTimer >= 15) {
            // 1 unit of health
            if (m->health < 0x0100) {
            }
            else if (m->hurtCounter == 0) {
                // un-squish animation
                m->squishTimer = 30;
                set_mario_action(m, ACT_IDLE, 0);
            }
        }
        break;
    }

    // steep floor
    if (m->floor != NULL && m->floor->normal.y < 0.5f) {
        surfAngle = atan2s(m->floor->normal.z, m->floor->normal.x);
        underSteepSurf = TRUE;
    }
    // steep ceiling
    if (m->ceil != NULL && -0.5f < m->ceil->normal.y) {
        surfAngle = atan2s(m->ceil->normal.z, m->ceil->normal.x);
        underSteepSurf = TRUE;
    }

    if (underSteepSurf) {
        m->vel[0] = sins(surfAngle) * 10.0f;
        m->vel[2] = coss(surfAngle) * 10.0f;
        m->vel[1] = 0;

        // check if there's no floor 10 units away from the surface
        if (perform_ground_step(m, surfaceLists) == GROUND_STEP_LEFT_GROUND) {
            // instant un-squish
            m->squishTimer = 0;
            set_mario_action(m, ACT_IDLE, 0);
            return FALSE;
        }
    }

    // squished for more than 10 seconds, so kill Mario
    if (m->actionArg++ > 300) {
        // 0 units of health
        m->health = 0x00FF;
        m->hurtCounter = 0;
    }
    stop_and_set_height_to_floor(m);
    set_mario_animation(m, MARIO_ANIM_A_POSE);
    return FALSE;
}

s32 mario_execute_cutscene_action(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 cancel;

    /* clang-format off */
    switch (m->action) {
    case ACT_SQUISHED:                   cancel = act_squished(m, surfaceLists);                   break;
    }
    /* clang-format on */

    return cancel;
}

struct LandingAction {
    s16 numFrames;
    s16 unk02;
    u32 verySteepAction;
    u32 endAction;
    u32 aPressedAction;
    u32 offFloorAction;
    u32 slideAction;
};


struct LandingAction sFreefallLandAction = {
    4, 5, ACT_FREEFALL, ACT_FREEFALL_LAND_STOP, ACT_DOUBLE_JUMP, ACT_FREEFALL, ACT_BEGIN_SLIDING,
};

Mat4 sFloorAlignMatrix[2];

s16 tilt_body_running(struct MarioState* m, struct Surfaces* surfaceLists) {
    s16 pitch = find_floor_slope(m, surfaceLists, 0);
    pitch = pitch * m->forwardVel / 40.0f;
    return -pitch;
}

void align_with_floor(struct MarioState* m, struct Surfaces* surfaceLists) {
    m->pos[1] = m->floorHeight;
    mtxf_align_terrain_triangle(surfaceLists, sFloorAlignMatrix[m->unk00], m->pos, m->faceAngle[1], 40.0f);
    m->marioObj->header.gfx.throwMatrix = &sFloorAlignMatrix[m->unk00];
}

s32 begin_walking_action(struct MarioState* m, f32 forwardVel, u32 action, u32 actionArg) {
    m->faceAngle[1] = m->intendedYaw;
    mario_set_forward_vel(m, forwardVel);
    return set_mario_action(m, action, actionArg);
}

void check_ledge_climb_down(struct MarioState* m, struct Surfaces* surfaceLists) {
    struct WallCollisionData wallCols;
    struct Surface* floor;
    f32 floorHeight;
    struct Surface* wall;
    s16 wallAngle;
    s16 wallDYaw;

    if (m->forwardVel < 10.0f) {
        wallCols.x = m->pos[0];
        wallCols.y = m->pos[1];
        wallCols.z = m->pos[2];
        wallCols.radius = 10.0f;
        wallCols.offsetY = -10.0f;

        if (find_wall_collisions(surfaceLists, &wallCols) != 0) {
            floorHeight = find_floor(surfaceLists, wallCols.x, wallCols.y, wallCols.z, &floor);
            if (floor != NULL && (wallCols.y - floorHeight > 160.0f)) {
                wall = wallCols.walls[wallCols.numWalls - 1];
                wallAngle = atan2s(wall->normal.z, wall->normal.x);
                wallDYaw = wallAngle - m->faceAngle[1];

                if (wallDYaw > -0x4000 && wallDYaw < 0x4000) {
                    m->pos[0] = wallCols.x - 20.0f * wall->normal.x;
                    m->pos[2] = wallCols.z - 20.0f * wall->normal.z;

                    m->faceAngle[0] = 0;
                    m->faceAngle[1] = wallAngle + 0x8000;

                    set_mario_action(m, ACT_LEDGE_CLIMB_DOWN, 0);
                    set_mario_animation(m, MARIO_ANIM_CLIMB_DOWN_LEDGE);
                }
            }
        }
    }
}

void slide_bonk(struct MarioState* m, u32 fastAction, u32 slowAction) {
    if (m->forwardVel > 16.0f) {
        mario_bonk_reflection(m, TRUE);
        drop_and_set_mario_action(m, fastAction, 0);
    }
    else {
        mario_set_forward_vel(m, 0.0f);
        set_mario_action(m, slowAction, 0);
    }
}

void update_sliding_angle(struct MarioState* m, f32 accel, f32 lossFactor) {
    s32 newFacingDYaw;
    s16 facingDYaw;

    struct Surface* floor = m->floor;
    s16 slopeAngle = atan2s(floor->normal.z, floor->normal.x);
    f32 steepness = sqrtf(floor->normal.x * floor->normal.x + floor->normal.z * floor->normal.z);
    UNUSED f32 normalY = floor->normal.y;

    m->slideVelX += accel * steepness * sins(slopeAngle);
    m->slideVelZ += accel * steepness * coss(slopeAngle);

    m->slideVelX *= lossFactor;
    m->slideVelZ *= lossFactor;

    m->slideYaw = atan2s(m->slideVelZ, m->slideVelX);

    facingDYaw = m->faceAngle[1] - m->slideYaw;
    newFacingDYaw = facingDYaw;

    //! -0x4000 not handled - can slide down a slope while facing perpendicular to it
    if (newFacingDYaw > 0 && newFacingDYaw <= 0x4000) {
        if ((newFacingDYaw -= 0x200) < 0) {
            newFacingDYaw = 0;
        }
    }
    else if (newFacingDYaw > -0x4000 && newFacingDYaw < 0) {
        if ((newFacingDYaw += 0x200) > 0) {
            newFacingDYaw = 0;
        }
    }
    else if (newFacingDYaw > 0x4000 && newFacingDYaw < 0x8000) {
        if ((newFacingDYaw += 0x200) > 0x8000) {
            newFacingDYaw = 0x8000;
        }
    }
    else if (newFacingDYaw > -0x8000 && newFacingDYaw < -0x4000) {
        if ((newFacingDYaw -= 0x200) < -0x8000) {
            newFacingDYaw = -0x8000;
        }
    }

    m->faceAngle[1] = m->slideYaw + newFacingDYaw;

    m->vel[0] = m->slideVelX;
    m->vel[1] = 0.0f;
    m->vel[2] = m->slideVelZ;

    //! Speed is capped a frame late (butt slide HSG)
    m->forwardVel = sqrtf(m->slideVelX * m->slideVelX + m->slideVelZ * m->slideVelZ);
    if (m->forwardVel > 100.0f) {
        m->slideVelX = m->slideVelX * 100.0f / m->forwardVel;
        m->slideVelZ = m->slideVelZ * 100.0f / m->forwardVel;
    }

    if (newFacingDYaw < -0x4000 || newFacingDYaw > 0x4000) {
        m->forwardVel *= -1.0f;
    }
}

s32 update_sliding(struct MarioState* m, f32 stopSpeed) {
    f32 lossFactor;
    f32 accel;
    f32 oldSpeed;
    f32 newSpeed;

    s32 stopped = FALSE;

    s16 intendedDYaw = m->intendedYaw - m->slideYaw;
    f32 forward = coss(intendedDYaw);
    f32 sideward = sins(intendedDYaw);

    //! 10k glitch
    if (forward < 0.0f && m->forwardVel >= 0.0f) {
        forward *= 0.5f + 0.5f * m->forwardVel / 100.0f;
    }

    switch (mario_get_floor_class(m)) {
    case SURFACE_CLASS_VERY_SLIPPERY:
        accel = 10.0f;
        lossFactor = m->intendedMag / 32.0f * forward * 0.02f + 0.98f;
        break;

    case SURFACE_CLASS_SLIPPERY:
        accel = 8.0f;
        lossFactor = m->intendedMag / 32.0f * forward * 0.02f + 0.96f;
        break;

    default:
        accel = 7.0f;
        lossFactor = m->intendedMag / 32.0f * forward * 0.02f + 0.92f;
        break;

    case SURFACE_CLASS_NOT_SLIPPERY:
        accel = 5.0f;
        lossFactor = m->intendedMag / 32.0f * forward * 0.02f + 0.92f;
        break;
    }

    oldSpeed = sqrtf(m->slideVelX * m->slideVelX + m->slideVelZ * m->slideVelZ);

    //! This is attempting to use trig derivatives to rotate Mario's speed.
    // It is slightly off/asymmetric since it uses the new X speed, but the old
    // Z speed.
    m->slideVelX += m->slideVelZ * (m->intendedMag / 32.0f) * sideward * 0.05f;
    m->slideVelZ -= m->slideVelX * (m->intendedMag / 32.0f) * sideward * 0.05f;

    newSpeed = sqrtf(m->slideVelX * m->slideVelX + m->slideVelZ * m->slideVelZ);

    if (oldSpeed > 0.0f && newSpeed > 0.0f) {
        m->slideVelX = m->slideVelX * oldSpeed / newSpeed;
        m->slideVelZ = m->slideVelZ * oldSpeed / newSpeed;
    }

    update_sliding_angle(m, accel, lossFactor);

    if (!mario_floor_is_slope(m) && m->forwardVel * m->forwardVel < stopSpeed * stopSpeed) {
        mario_set_forward_vel(m, 0.0f);
        stopped = TRUE;
    }

    return stopped;
}

void apply_slope_accel(struct MarioState* m) {
    f32 slopeAccel;

    struct Surface* floor = m->floor;
    f32 steepness = sqrtf(floor->normal.x * floor->normal.x + floor->normal.z * floor->normal.z);

    UNUSED f32 normalY = floor->normal.y;
    s16 floorDYaw = m->floorAngle - m->faceAngle[1];

    if (mario_floor_is_slope(m)) {
        s16 slopeClass = 0;

        if (m->action != ACT_SOFT_BACKWARD_GROUND_KB && m->action != ACT_SOFT_FORWARD_GROUND_KB) {
            slopeClass = mario_get_floor_class(m);
        }

        switch (slopeClass) {
        case SURFACE_CLASS_VERY_SLIPPERY:
            slopeAccel = 5.3f;
            break;
        case SURFACE_CLASS_SLIPPERY:
            slopeAccel = 2.7f;
            break;
        default:
            slopeAccel = 1.7f;
            break;
        case SURFACE_CLASS_NOT_SLIPPERY:
            slopeAccel = 0.0f;
            break;
        }

        if (floorDYaw > -0x4000 && floorDYaw < 0x4000) {
            m->forwardVel += slopeAccel * steepness;
        }
        else {
            m->forwardVel -= slopeAccel * steepness;
        }
    }

    m->slideYaw = m->faceAngle[1];

    m->slideVelX = m->forwardVel * sins(m->faceAngle[1]);
    m->slideVelZ = m->forwardVel * coss(m->faceAngle[1]);

    m->vel[0] = m->slideVelX;
    m->vel[1] = 0.0f;
    m->vel[2] = m->slideVelZ;
}

s32 apply_landing_accel(struct MarioState* m, f32 frictionFactor) {
    s32 stopped = FALSE;

    apply_slope_accel(m);

    if (!mario_floor_is_slope(m)) {
        m->forwardVel *= frictionFactor;
        if (m->forwardVel * m->forwardVel < 1.0f) {
            mario_set_forward_vel(m, 0.0f);
            stopped = TRUE;
        }
    }

    return stopped;
}

s32 apply_slope_decel(struct MarioState* m, f32 decelCoef) {
    f32 decel;
    s32 stopped = FALSE;

    switch (mario_get_floor_class(m)) {
    case SURFACE_CLASS_VERY_SLIPPERY:
        decel = decelCoef * 0.2f;
        break;
    case SURFACE_CLASS_SLIPPERY:
        decel = decelCoef * 0.7f;
        break;
    default:
        decel = decelCoef * 2.0f;
        break;
    case SURFACE_CLASS_NOT_SLIPPERY:
        decel = decelCoef * 3.0f;
        break;
    }

    if ((m->forwardVel = approach_f32(m->forwardVel, 0.0f, decel, decel)) == 0.0f) {
        stopped = TRUE;
    }

    apply_slope_accel(m);
    return stopped;
}

s32 update_decelerating_speed(struct MarioState* m) {
    s32 stopped = FALSE;

    if ((m->forwardVel = approach_f32(m->forwardVel, 0.0f, 1.0f, 1.0f)) == 0.0f) {
        stopped = TRUE;
    }

    mario_set_forward_vel(m, m->forwardVel);

    return stopped;
}

void update_walking_speed(struct MarioState* m) {
    f32 maxTargetSpeed;
    f32 targetSpeed;

    if (m->floor != NULL && m->floor->type == SURFACE_SLOW) {
        maxTargetSpeed = 24.0f;
    }
    else {
        maxTargetSpeed = 32.0f;
    }

    targetSpeed = m->intendedMag < maxTargetSpeed ? m->intendedMag : maxTargetSpeed;

    if (m->quicksandDepth > 10.0f) {
        targetSpeed *= 6.25 / m->quicksandDepth;
    }

    if (m->forwardVel <= 0.0f) {
        m->forwardVel += 1.1f;
    }
    else if (m->forwardVel <= targetSpeed) {
        m->forwardVel += 1.1f - m->forwardVel / 43.0f;
    }
    else if (m->floor->normal.y >= 0.95f) {
        m->forwardVel -= 1.0f;
    }

    if (m->forwardVel > 48.0f) {
        m->forwardVel = 48.0f;
    }

    m->faceAngle[1] =
        m->intendedYaw - approach_s32((s16)(m->intendedYaw - m->faceAngle[1]), 0, 0x800, 0x800);
    apply_slope_accel(m);
}

s32 should_begin_sliding(struct MarioState* m) {
    if (m->input & INPUT_ABOVE_SLIDE) {
        s32 slideLevel = (m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE;
        s32 movingBackward = m->forwardVel <= -1.0f;

        if (slideLevel || movingBackward || mario_facing_downhill(m, FALSE)) {
            return TRUE;
        }
    }

    return FALSE;
}

s32 analog_stick_held_back(struct MarioState* m) {
    s16 intendedDYaw = m->intendedYaw - m->faceAngle[1];
    return intendedDYaw < -0x471C || intendedDYaw > 0x471C;
}

s32 check_ground_dive_or_punch(struct MarioState* m) {
    if (m->input & INPUT_B_PRESSED) {
        //! Speed kick (shoutouts to SimpleFlips)
        if (m->forwardVel >= 29.0f && m->controller->stickMag > 48.0f) {
            m->vel[1] = 20.0f;
            return set_mario_action(m, ACT_DIVE, 1);
        }

        return set_mario_action(m, ACT_MOVE_PUNCHING, 0);
    }

    return FALSE;
}

s32 begin_braking_action(struct MarioState* m) {
    if (m->actionState == 1) {
        m->faceAngle[1] = m->actionArg;
        return set_mario_action(m, ACT_STANDING_AGAINST_WALL, 0);
    }

    if (m->forwardVel >= 16.0f && m->floor->normal.y >= 0.17364818f) {
        return set_mario_action(m, ACT_BRAKING, 0);
    }

    return set_mario_action(m, ACT_DECELERATING, 0);
}

void anim_and_audio_for_walk(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 val14;
    struct Object* marioObj = m->marioObj;
    s32 val0C = TRUE;
    s16 targetPitch = 0;
    f32 val04;

    val04 = m->intendedMag > m->forwardVel ? m->intendedMag : m->forwardVel;

    if (val04 < 4.0f) {
        val04 = 4.0f;
    }

    if (m->quicksandDepth > 50.0f) {
        val14 = (s32)(val04 / 4.0f * 0x10000);
        set_mario_anim_with_accel(m, MARIO_ANIM_MOVE_IN_QUICKSAND, val14);
        m->actionTimer = 0;
    }
    else {
        while (val0C) {
            switch (m->actionTimer) {
            case 0:
                if (val04 > 8.0f) {
                    m->actionTimer = 2;
                }
                else {
                    //! (Speed Crash) If Mario's speed is more than 2^17.
                    if ((val14 = (s32)(val04 / 4.0f * 0x10000)) < 0x1000) {
                        val14 = 0x1000;
                    }
                    set_mario_anim_with_accel(m, MARIO_ANIM_START_TIPTOE, val14);
                    if (is_anim_past_frame(m, 23)) {
                        m->actionTimer = 2;
                    }

                    val0C = FALSE;
                }
                break;

            case 1:
                if (val04 > 8.0f) {
                    m->actionTimer = 2;
                }
                else {
                    //! (Speed Crash) If Mario's speed is more than 2^17.
                    if ((val14 = (s32)(val04 * 0x10000)) < 0x1000) {
                        val14 = 0x1000;
                    }
                    set_mario_anim_with_accel(m, MARIO_ANIM_TIPTOE, val14);

                    val0C = FALSE;
                }
                break;

            case 2:
                if (val04 < 5.0f) {
                    m->actionTimer = 1;
                }
                else if (val04 > 22.0f) {
                    m->actionTimer = 3;
                }
                else {
                    //! (Speed Crash) If Mario's speed is more than 2^17.
                    val14 = (s32)(val04 / 4.0f * 0x10000);
                    set_mario_anim_with_accel(m, MARIO_ANIM_WALKING, val14);

                    val0C = FALSE;
                }
                break;

            case 3:
                if (val04 < 18.0f) {
                    m->actionTimer = 2;
                }
                else {
                    //! (Speed Crash) If Mario's speed is more than 2^17.
                    val14 = (s32)(val04 / 4.0f * 0x10000);
                    set_mario_anim_with_accel(m, MARIO_ANIM_RUNNING, val14);
                    targetPitch = tilt_body_running(m, surfaceLists);

                    val0C = FALSE;
                }
                break;
            }
        }
    }

    marioObj->oMarioWalkingPitch =
        (s16)approach_s32(marioObj->oMarioWalkingPitch, targetPitch, 0x800, 0x800);
    marioObj->header.gfx.angle[0] = marioObj->oMarioWalkingPitch;
}

void anim_and_audio_for_hold_walk(struct MarioState* m) {
    s32 val0C;
    s32 val08 = TRUE;
    f32 val04;

    val04 = m->intendedMag > m->forwardVel ? m->intendedMag : m->forwardVel;

    if (val04 < 2.0f) {
        val04 = 2.0f;
    }

    while (val08) {
        switch (m->actionTimer) {
        case 0:
            if (val04 > 6.0f) {
                m->actionTimer = 1;
            }
            else {
                //! (Speed Crash) Crashes if Mario's speed exceeds or equals 2^15.
                val0C = (s32)(val04 * 0x10000);
                set_mario_anim_with_accel(m, MARIO_ANIM_SLOW_WALK_WITH_LIGHT_OBJ, val0C);

                val08 = FALSE;
            }
            break;

        case 1:
            if (val04 < 3.0f) {
                m->actionTimer = 0;
            }
            else if (val04 > 11.0f) {
                m->actionTimer = 2;
            }
            else {
                //! (Speed Crash) Crashes if Mario's speed exceeds or equals 2^15.
                val0C = (s32)(val04 * 0x10000);
                set_mario_anim_with_accel(m, MARIO_ANIM_WALK_WITH_LIGHT_OBJ, val0C);

                val08 = FALSE;
            }
            break;

        case 2:
            if (val04 < 8.0f) {
                m->actionTimer = 1;
            }
            else {
                //! (Speed Crash) Crashes if Mario's speed exceeds or equals 2^16.
                val0C = (s32)(val04 / 2.0f * 0x10000);
                set_mario_anim_with_accel(m, MARIO_ANIM_RUN_WITH_LIGHT_OBJ, val0C);

                val08 = FALSE;
            }
            break;
        }
    }
}

void anim_and_audio_for_heavy_walk(struct MarioState* m) {
    s32 val04 = (s32)(m->intendedMag * 0x10000);
    set_mario_anim_with_accel(m, MARIO_ANIM_WALK_WITH_HEAVY_OBJ, val04);
}

void push_or_sidle_wall(struct MarioState* m, struct Surfaces* surfaceLists, Vec3f startPos) {
    s16 wallAngle;
    s16 dWallAngle;
    f32 dx = m->pos[0] - startPos[0];
    f32 dz = m->pos[2] - startPos[2];
    f32 movedDistance = sqrtf(dx * dx + dz * dz);
    //! (Speed Crash) If a wall is after moving 16384 distance, this crashes.
    s32 val04 = (s32)(movedDistance * 2.0f * 0x10000);

    if (m->forwardVel > 6.0f) {
        mario_set_forward_vel(m, 6.0f);
    }

    if (m->wall != NULL) {
        wallAngle = atan2s(m->wall->normal.z, m->wall->normal.x);
        dWallAngle = wallAngle - m->faceAngle[1];
    }

    if (m->wall == NULL || dWallAngle <= -0x71C8 || dWallAngle >= 0x71C8) {
        m->flags |= MARIO_UNKNOWN_31;
        set_mario_animation(m, MARIO_ANIM_PUSHING);
    }
    else {
        if (dWallAngle < 0) {
            set_mario_anim_with_accel(m, MARIO_ANIM_SIDESTEP_RIGHT, val04);
        }
        else {
            set_mario_anim_with_accel(m, MARIO_ANIM_SIDESTEP_LEFT, val04);
        }

        m->actionState = 1;
        m->actionArg = wallAngle + 0x8000;
        m->marioObj->header.gfx.angle[1] = wallAngle + 0x8000;
        m->marioObj->header.gfx.angle[2] = find_floor_slope(m, surfaceLists, 0x4000);
    }
}

s32 act_walking(struct MarioState* m, struct Surfaces* surfaceLists) {
    Vec3f startPos;
    s16 startYaw = m->faceAngle[1];

    if (should_begin_sliding(m)) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    if (m->input & INPUT_FIRST_PERSON) {
        return begin_braking_action(m);
    }

    if (check_ground_dive_or_punch(m)) {
        return TRUE;
    }

    if (m->input & INPUT_UNKNOWN_5) {
        return begin_braking_action(m);
    }

    if (analog_stick_held_back(m) && m->forwardVel >= 16.0f) {
        return set_mario_action(m, ACT_TURNING_AROUND, 0);
    }

    if (m->input & INPUT_Z_PRESSED) {
        return set_mario_action(m, ACT_CROUCH_SLIDE, 0);
    }

    m->actionState = 0;

    vec3f_copy(startPos, m->pos);
    update_walking_speed(m);

    switch (perform_ground_step(m, surfaceLists)) {
    case GROUND_STEP_LEFT_GROUND:
        set_mario_action(m, ACT_FREEFALL, 0);
        set_mario_animation(m, MARIO_ANIM_GENERAL_FALL);
        break;

    case GROUND_STEP_NONE:
        anim_and_audio_for_walk(m, surfaceLists);
        break;

    case GROUND_STEP_HIT_WALL:
        push_or_sidle_wall(m, surfaceLists, startPos);
        m->actionTimer = 0;
        break;
    }

    check_ledge_climb_down(m, surfaceLists);
    return FALSE;
}

s32 act_move_punching(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (should_begin_sliding(m)) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    m->actionState = 1;

    mario_update_punch_sequence(m);

    if (m->forwardVel >= 0.0f) {
        apply_slope_decel(m, 0.5f);
    }
    else {
        if ((m->forwardVel += 8.0f) >= 0.0f) {
            m->forwardVel = 0.0f;
        }
        apply_slope_accel(m);
    }

    switch (perform_ground_step(m, surfaceLists)) {
    case GROUND_STEP_LEFT_GROUND:
        set_mario_action(m, ACT_FREEFALL, 0);
        break;

    case GROUND_STEP_NONE:
        break;
    }

    return FALSE;
}

s32 act_turning_around(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    if (m->input & INPUT_UNKNOWN_5) {
        return set_mario_action(m, ACT_BRAKING, 0);
    }

    if (!analog_stick_held_back(m)) {
        return set_mario_action(m, ACT_WALKING, 0);
    }

    if (apply_slope_decel(m, 2.0f)) {
        return begin_walking_action(m, 8.0f, ACT_FINISH_TURNING_AROUND, 0);
    }

    switch (perform_ground_step(m, surfaceLists)) {
    case GROUND_STEP_LEFT_GROUND:
        set_mario_action(m, ACT_FREEFALL, 0);
        break;

    case GROUND_STEP_NONE:
        break;
    }

    if (m->forwardVel >= 18.0f) {
        set_mario_animation(m, MARIO_ANIM_TURNING_PART1);
    }
    else {
        set_mario_animation(m, MARIO_ANIM_TURNING_PART2);
        if (is_anim_at_end(m)) {
            if (m->forwardVel > 0.0f) {
                begin_walking_action(m, -m->forwardVel, ACT_WALKING, 0);
            }
            else {
                begin_walking_action(m, 8.0f, ACT_WALKING, 0);
            }
        }
    }

    return FALSE;
}

s32 act_finish_turning_around(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    update_walking_speed(m);
    set_mario_animation(m, MARIO_ANIM_TURNING_PART2);

    if (perform_ground_step(m, surfaceLists) == GROUND_STEP_LEFT_GROUND) {
        set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (is_anim_at_end(m)) {
        set_mario_action(m, ACT_WALKING, 0);
    }

    m->marioObj->header.gfx.angle[1] += 0x8000;
    return FALSE;
}

s32 act_braking(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (!(m->input & INPUT_FIRST_PERSON)
        && (m->input
            & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE))) {
        return check_common_action_exits(m);
    }

    if (apply_slope_decel(m, 2.0f)) {
        return set_mario_action(m, ACT_BRAKING_STOP, 0);
    }

    if (m->input & INPUT_B_PRESSED) {
        return set_mario_action(m, ACT_MOVE_PUNCHING, 0);
    }

    switch (perform_ground_step(m, surfaceLists)) {
    case GROUND_STEP_LEFT_GROUND:
        set_mario_action(m, ACT_FREEFALL, 0);
        break;

    case GROUND_STEP_NONE:
        break;

    case GROUND_STEP_HIT_WALL:
        slide_bonk(m, ACT_BACKWARD_GROUND_KB, ACT_BRAKING_STOP);
        break;
    }

    set_mario_animation(m, MARIO_ANIM_SKID_ON_GROUND);
    return FALSE;
}

s32 act_decelerating(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 val0C;
    s16 slopeClass = mario_get_floor_class(m);

    if (!(m->input & INPUT_FIRST_PERSON)) {
        if (should_begin_sliding(m)) {
            return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
        }

        if (check_ground_dive_or_punch(m)) {
            return TRUE;
        }

        if (m->input & INPUT_NONZERO_ANALOG) {
            return set_mario_action(m, ACT_WALKING, 0);
        }

        if (m->input & INPUT_Z_PRESSED) {
            return set_mario_action(m, ACT_CROUCH_SLIDE, 0);
        }
    }

    if (update_decelerating_speed(m)) {
        return set_mario_action(m, ACT_IDLE, 0);
    }

    switch (perform_ground_step(m, surfaceLists)) {
    case GROUND_STEP_LEFT_GROUND:
        set_mario_action(m, ACT_FREEFALL, 0);
        break;

    case GROUND_STEP_HIT_WALL:
        if (slopeClass == SURFACE_CLASS_VERY_SLIPPERY) {
            mario_bonk_reflection(m, TRUE);
        }
        else {
            mario_set_forward_vel(m, 0.0f);
        }
        break;
    }

    if (slopeClass == SURFACE_CLASS_VERY_SLIPPERY) {
        set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_LEFT);
    }
    else {
        // (Speed Crash) Crashes if speed exceeds 2^17.
        if ((val0C = (s32)(m->forwardVel / 4.0f * 0x10000)) < 0x1000) {
            val0C = 0x1000;
        }

        set_mario_anim_with_accel(m, MARIO_ANIM_WALKING, val0C);
    }

    return FALSE;
}

s32 act_crawling(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 val04;

    if (should_begin_sliding(m)) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    if (m->input & INPUT_FIRST_PERSON) {
        return set_mario_action(m, ACT_STOP_CRAWLING, 0);
    }

    if (check_ground_dive_or_punch(m)) {
        return TRUE;
    }

    if (m->input & INPUT_UNKNOWN_5) {
        return set_mario_action(m, ACT_STOP_CRAWLING, 0);
    }

    if (!(m->input & INPUT_Z_DOWN)) {
        return set_mario_action(m, ACT_STOP_CRAWLING, 0);
    }

    m->intendedMag *= 0.1f;

    update_walking_speed(m);

    switch (perform_ground_step(m, surfaceLists)) {
    case GROUND_STEP_LEFT_GROUND:
        set_mario_action(m, ACT_FREEFALL, 0);
        break;

    case GROUND_STEP_HIT_WALL:
        if (m->forwardVel > 10.0f) {
            mario_set_forward_vel(m, 10.0f);
        }
        //! Possibly unintended missing break

    case GROUND_STEP_NONE:
        align_with_floor(m, surfaceLists);
        break;
    }

    val04 = (s32)(m->intendedMag * 2.0f * 0x10000);
    set_mario_anim_with_accel(m, MARIO_ANIM_CRAWLING, val04);
    return FALSE;
}

void common_slide_action(struct MarioState* m, struct Surfaces* surfaceLists, u32 endAction, u32 airAction, s32 animation) {
    Vec3f pos;

    vec3f_copy(pos, m->pos);

    switch (perform_ground_step(m, surfaceLists)) {
    case GROUND_STEP_LEFT_GROUND:
        set_mario_action(m, airAction, 0);
        break;

    case GROUND_STEP_NONE:
        set_mario_animation(m, animation);
        align_with_floor(m, surfaceLists);
        break;

    case GROUND_STEP_HIT_WALL:
        if (!mario_floor_is_slippery(m)) {
            slide_bonk(m, ACT_GROUND_BONK, endAction);
        }
        else if (m->wall != NULL) {
            s16 wallAngle = atan2s(m->wall->normal.z, m->wall->normal.x);
            f32 slideSpeed = sqrtf(m->slideVelX * m->slideVelX + m->slideVelZ * m->slideVelZ);

            if ((slideSpeed *= 0.9) < 4.0f) {
                slideSpeed = 4.0f;
            }

            m->slideYaw = wallAngle - (s16)(m->slideYaw - wallAngle) + 0x8000;

            m->vel[0] = m->slideVelX = slideSpeed * sins(m->slideYaw);
            m->vel[2] = m->slideVelZ = slideSpeed * coss(m->slideYaw);
        }

        align_with_floor(m, surfaceLists);
        break;
    }
}

s32 common_slide_action_with_jump(struct MarioState* m, struct Surfaces* surfaceLists, u32 stopAction, u32 jumpAction, u32 airAction,
    s32 animation) {
    m->actionTimer++;

    if (update_sliding(m, 4.0f)) {
        return set_mario_action(m, stopAction, 0);
    }

    common_slide_action(m, surfaceLists, stopAction, airAction, animation);
    return FALSE;
}

s32 act_butt_slide(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 cancel = common_slide_action_with_jump(m, surfaceLists, ACT_BUTT_SLIDE_STOP, ACT_JUMP, ACT_BUTT_SLIDE_AIR,
        MARIO_ANIM_SLIDE);
    return cancel;
}

s32 act_crouch_slide(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 cancel;

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BUTT_SLIDE, 0);
    }

    if (m->actionTimer < 30) {
        m->actionTimer++;
    }

    if (m->input & INPUT_B_PRESSED) {
        if (m->forwardVel >= 10.0f) {
            return set_mario_action(m, ACT_SLIDE_KICK, 0);
        }
        else {
            return set_mario_action(m, ACT_MOVE_PUNCHING, 0x0009);
        }
    }

    if (m->input & INPUT_FIRST_PERSON) {
        return set_mario_action(m, ACT_BRAKING, 0);
    }

    cancel = common_slide_action_with_jump(m, surfaceLists, ACT_CROUCHING, ACT_JUMP, ACT_FREEFALL,
        MARIO_ANIM_START_CROUCHING);
    return cancel;
}

s32 act_slide_kick_slide(struct MarioState* m, struct Surfaces* surfaceLists) {
    set_mario_animation(m, MARIO_ANIM_SLIDE_KICK);
    if (is_anim_at_end(m) && m->forwardVel < 1.0f) {
        return set_mario_action(m, ACT_SLIDE_KICK_SLIDE_STOP, 0);
    }

    update_sliding(m, 1.0f);
    switch (perform_ground_step(m, surfaceLists)) {
    case GROUND_STEP_LEFT_GROUND:
        set_mario_action(m, ACT_FREEFALL, 2);
        break;

    case GROUND_STEP_HIT_WALL:
        mario_bonk_reflection(m, TRUE);
        set_mario_action(m, ACT_BACKWARD_GROUND_KB, 0);
        break;
    }

    return FALSE;
}

s32 stomach_slide_action(struct MarioState* m, struct Surfaces* surfaceLists, u32 stopAction, u32 airAction, s32 animation) {
    if (m->actionTimer == 5) {
        if (!(m->input & INPUT_ABOVE_SLIDE) && (m->input & (INPUT_B_PRESSED))) {
            return drop_and_set_mario_action(
                m, m->forwardVel >= 0.0f ? ACT_FORWARD_ROLLOUT : ACT_BACKWARD_ROLLOUT, 0);
        }
    }
    else {
        m->actionTimer++;
    }

    if (update_sliding(m, 4.0f)) {
        return set_mario_action(m, stopAction, 0);
    }

    common_slide_action(m, surfaceLists, stopAction, airAction, animation);
    return FALSE;
}

s32 act_stomach_slide(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 cancel = stomach_slide_action(m, surfaceLists, ACT_STOMACH_SLIDE_STOP, ACT_FREEFALL, MARIO_ANIM_SLIDE_DIVE);
    return cancel;
}

s32 act_dive_slide(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (!(m->input & INPUT_ABOVE_SLIDE) && (m->input & (INPUT_B_PRESSED))) {
        return set_mario_action(m, m->forwardVel > 0.0f ? ACT_FORWARD_ROLLOUT : ACT_BACKWARD_ROLLOUT,
            0);
    }

    //! If the dive slide ends on the same frame that we pick up on object,
    // Mario will not be in the dive slide action for the call to
    // mario_check_object_grab, and so will end up in the regular picking action,
    // rather than the picking up after dive action.

    if (update_sliding(m, 8.0f) && is_anim_at_end(m)) {
        mario_set_forward_vel(m, 0.0f);
        set_mario_action(m, ACT_STOMACH_SLIDE_STOP, 0);
    }

    common_slide_action(m, surfaceLists, ACT_STOMACH_SLIDE_STOP, ACT_FREEFALL, MARIO_ANIM_DIVE);
    return FALSE;
}

s32 common_ground_knockback_action(struct MarioState* m, struct Surfaces* surfaceLists, s32 animation, s32 arg2, s32 arg3, s32 arg4) {
    s32 animFrame;

    if (m->forwardVel > 32.0f) {
        m->forwardVel = 32.0f;
    }
    if (m->forwardVel < -32.0f) {
        m->forwardVel = -32.0f;
    }

    animFrame = set_mario_animation(m, animation);
    if (animFrame < arg2) {
        apply_landing_accel(m, 0.9f);
    }
    else if (m->forwardVel >= 0.0f) {
        mario_set_forward_vel(m, 0.1f);
    }
    else {
        mario_set_forward_vel(m, -0.1f);
    }

    if (perform_ground_step(m, surfaceLists) == GROUND_STEP_LEFT_GROUND) {
        if (m->forwardVel >= 0.0f) {
            set_mario_action(m, ACT_FORWARD_AIR_KB, arg4);
        }
        else {
            set_mario_action(m, ACT_BACKWARD_AIR_KB, arg4);
        }
    }
    else if (is_anim_at_end(m)) {
        if (arg4 > 0) {
            m->invincTimer = 30;
        }
        set_mario_action(m, ACT_IDLE, 0);
    }

    return animFrame;
}

s32 act_hard_backward_ground_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 animFrame =
        common_ground_knockback_action(m, surfaceLists, MARIO_ANIM_FALL_OVER_BACKWARDS, 43, TRUE, m->actionArg);

    return FALSE;
}

s32 act_hard_forward_ground_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 animFrame =
        common_ground_knockback_action(m, surfaceLists, MARIO_ANIM_LAND_ON_STOMACH, 21, TRUE, m->actionArg);

    return FALSE;
}

s32 act_backward_ground_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    common_ground_knockback_action(m, surfaceLists, MARIO_ANIM_BACKWARD_KB, 22, TRUE, m->actionArg);
    return FALSE;
}

s32 act_forward_ground_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    common_ground_knockback_action(m, surfaceLists, MARIO_ANIM_FORWARD_KB, 20, TRUE, m->actionArg);
    return FALSE;
}

s32 act_soft_backward_ground_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    common_ground_knockback_action(m, surfaceLists, MARIO_ANIM_SOFT_BACK_KB, 100, FALSE, m->actionArg);
    return FALSE;
}

s32 act_soft_forward_ground_kb(struct MarioState* m, struct Surfaces* surfaceLists) {
    common_ground_knockback_action(m, surfaceLists, MARIO_ANIM_SOFT_FRONT_KB, 100, FALSE, m->actionArg);
    return FALSE;
}

s32 act_ground_bonk(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 animFrame =
        common_ground_knockback_action(m, surfaceLists, MARIO_ANIM_GROUND_BONK, 32, TRUE, m->actionArg);
    return FALSE;
}

u32 common_landing_action(struct MarioState* m, struct Surfaces* surfaceLists, s16 animation, u32 airAction) {
    u32 stepResult;

    if (m->input & INPUT_NONZERO_ANALOG) {
        apply_landing_accel(m, 0.98f);
    }
    else if (m->forwardVel >= 16.0f) {
        apply_slope_decel(m, 2.0f);
    }
    else {
        m->vel[1] = 0.0f;
    }

    stepResult = perform_ground_step(m, surfaceLists);
    switch (stepResult) {
    case GROUND_STEP_LEFT_GROUND:
        set_mario_action(m, airAction, 0);
        break;

    case GROUND_STEP_HIT_WALL:
        set_mario_animation(m, MARIO_ANIM_PUSHING);
        break;
    }

    set_mario_animation(m, animation);

    return stepResult;
}

s32 common_landing_cancels(struct MarioState* m, struct LandingAction* landingAction,
    s32(*setAPressAction)(struct MarioState*, u32, u32)) {
    //! Everything here, including floor steepness, is checked before checking
    // if Mario is actually on the floor. This leads to e.g. remote sliding.

    if (m->floor->normal.y < 0.2923717f) {
        return mario_push_off_steep_floor(m, landingAction->verySteepAction, 0);
    }

    m->doubleJumpTimer = landingAction->unk02;

    if (should_begin_sliding(m)) {
        return set_mario_action(m, landingAction->slideAction, 0);
    }

    if (m->input & INPUT_FIRST_PERSON) {
        return set_mario_action(m, landingAction->endAction, 0);
    }

    if (++m->actionTimer >= landingAction->numFrames) {
        return set_mario_action(m, landingAction->endAction, 0);
    }

    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, landingAction->offFloorAction, 0);
    }

    return FALSE;
}

s32 act_freefall_land(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (common_landing_cancels(m, &sFreefallLandAction, NULL)) {
        return TRUE;
    }

    common_landing_action(m, surfaceLists, MARIO_ANIM_GENERAL_LAND, ACT_FREEFALL);
    return FALSE;
}

s32 check_common_moving_cancels(struct MarioState* m) {
    if (m->input & INPUT_SQUISHED) {
        return drop_and_set_mario_action(m, ACT_SQUISHED, 0);
    }

    return FALSE;
}

s32 mario_execute_moving_action(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 cancel;

    if (check_common_moving_cancels(m)) {
        return TRUE;
    }

    /* clang-format off */
    switch (m->action) {
    case ACT_WALKING:                  cancel = act_walking(m, surfaceLists);                  break;
    case ACT_TURNING_AROUND:           cancel = act_turning_around(m, surfaceLists);           break;
    case ACT_FINISH_TURNING_AROUND:    cancel = act_finish_turning_around(m, surfaceLists);    break;
    case ACT_BRAKING:                  cancel = act_braking(m, surfaceLists);                  break;
    case ACT_CRAWLING:                 cancel = act_crawling(m, surfaceLists);                 break;
    case ACT_DECELERATING:             cancel = act_decelerating(m, surfaceLists);             break;
    case ACT_BUTT_SLIDE:               cancel = act_butt_slide(m, surfaceLists);               break;
    case ACT_STOMACH_SLIDE:            cancel = act_stomach_slide(m, surfaceLists);            break;
    case ACT_DIVE_SLIDE:               cancel = act_dive_slide(m, surfaceLists);               break;
    case ACT_MOVE_PUNCHING:            cancel = act_move_punching(m, surfaceLists);            break;
    case ACT_CROUCH_SLIDE:             cancel = act_crouch_slide(m, surfaceLists);             break;
    case ACT_SLIDE_KICK_SLIDE:         cancel = act_slide_kick_slide(m, surfaceLists);         break;
    case ACT_HARD_BACKWARD_GROUND_KB:  cancel = act_hard_backward_ground_kb(m, surfaceLists);  break;
    case ACT_HARD_FORWARD_GROUND_KB:   cancel = act_hard_forward_ground_kb(m, surfaceLists);   break;
    case ACT_BACKWARD_GROUND_KB:       cancel = act_backward_ground_kb(m, surfaceLists);       break;
    case ACT_FORWARD_GROUND_KB:        cancel = act_forward_ground_kb(m, surfaceLists);        break;
    case ACT_SOFT_BACKWARD_GROUND_KB:  cancel = act_soft_backward_ground_kb(m, surfaceLists);  break;
    case ACT_SOFT_FORWARD_GROUND_KB:   cancel = act_soft_forward_ground_kb(m, surfaceLists);   break;
    case ACT_GROUND_BONK:              cancel = act_ground_bonk(m, surfaceLists);              break;
    case ACT_FREEFALL_LAND:            cancel = act_freefall_land(m, surfaceLists);            break;
    }
    /* clang-format on */

    return cancel;
}

/**
 * Used by act_punching() to determine Mario's forward velocity during each
 * animation frame.
 */
s8 sPunchingForwardVelocities[8] = { 0, 1, 1, 2, 3, 5, 7, 10 };

void animated_stationary_ground_step(struct MarioState* m, struct Surfaces* surfaceLists, s32 animation, u32 endAction) {
    stationary_ground_step(m, surfaceLists);
    set_mario_animation(m, animation);
    if (is_anim_at_end(m)) {
        set_mario_action(m, endAction, 0);
    }
}

s32 mario_update_punch_sequence(struct MarioState* m) {
    u32 endAction, crouchEndAction;
    s32 animFrame;

    if (m->action & ACT_FLAG_MOVING) {
        endAction = ACT_WALKING, crouchEndAction = ACT_CROUCH_SLIDE;
    }
    else {
        endAction = ACT_IDLE, crouchEndAction = ACT_CROUCHING;
    }

    switch (m->actionArg) {
    case 0:
        // fallthrough
    case 1:
        set_mario_animation(m, MARIO_ANIM_FIRST_PUNCH);
        if (is_anim_past_end(m)) {
            m->actionArg = 2;
        }
        else {
            m->actionArg = 1;
        }

        if (m->marioObj->header.gfx.animInfo.animFrame >= 2) {
            m->flags |= MARIO_PUNCHING;
        }

        break;

    case 2:
        set_mario_animation(m, MARIO_ANIM_FIRST_PUNCH_FAST);

        if (m->marioObj->header.gfx.animInfo.animFrame <= 0) {
            m->flags |= MARIO_PUNCHING;
        }

        if (m->input & INPUT_B_PRESSED) {
            m->actionArg = 3;
        }

        if (is_anim_at_end(m)) {
            set_mario_action(m, endAction, 0);
        }
        break;

    case 3:
        // fallthrough
    case 4:
        set_mario_animation(m, MARIO_ANIM_SECOND_PUNCH);
        if (is_anim_past_end(m)) {
            m->actionArg = 5;
        }
        else {
            m->actionArg = 4;
        }

        if (m->marioObj->header.gfx.animInfo.animFrame > 0) {
            m->flags |= MARIO_PUNCHING;
        }

        break;

    case 5:
        set_mario_animation(m, MARIO_ANIM_SECOND_PUNCH_FAST);
        if (m->marioObj->header.gfx.animInfo.animFrame <= 0) {
            m->flags |= MARIO_PUNCHING;
        }

        if (m->input & INPUT_B_PRESSED) {
            m->actionArg = 6;
        }

        if (is_anim_at_end(m)) {
            set_mario_action(m, endAction, 0);
        }
        break;

    case 6:
        animFrame = set_mario_animation(m, MARIO_ANIM_GROUND_KICK);

        if (animFrame >= 0 && animFrame < 8) {
            m->flags |= MARIO_KICKING;
        }

        if (is_anim_at_end(m)) {
            set_mario_action(m, endAction, 0);
        }
        break;

    case 9:
        set_mario_animation(m, MARIO_ANIM_BREAKDANCE);
        animFrame = m->marioObj->header.gfx.animInfo.animFrame;

        if (animFrame >= 2 && animFrame < 8) {
            m->flags |= MARIO_TRIPPING;
        }

        if (is_anim_at_end(m)) {
            set_mario_action(m, crouchEndAction, 0);
        }
        break;
    }

    return FALSE;
}

s32 act_punching(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE)) {
        return check_common_action_exits(m);
    }

    m->actionState = 1;
    if (m->actionArg == 0) {
        m->actionTimer = 7;
    }

    mario_set_forward_vel(m, sPunchingForwardVelocities[m->actionTimer]);
    if (m->actionTimer > 0) {
        m->actionTimer--;
    }

    mario_update_punch_sequence(m);
    perform_ground_step(m, surfaceLists);
    return FALSE;
}

s32 act_stomach_slide_stop(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_STOMPED) {
        return set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    }

    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    animated_stationary_ground_step(m, surfaceLists, MARIO_ANIM_SLOW_LAND_FROM_DIVE, ACT_IDLE);
    return FALSE;
}

s32 mario_execute_object_action(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 cancel;

    /* clang-format off */
    switch (m->action) {
    case ACT_PUNCHING:           cancel = act_punching(m, surfaceLists);           break;
    case ACT_STOMACH_SLIDE_STOP: cancel = act_stomach_slide_stop(m, surfaceLists); break;
    }
    /* clang-format on */

    return cancel;
}

s32 check_common_idle_cancels(struct MarioState* m) {
    if (m->floor->normal.y < 0.29237169f) {
        return mario_push_off_steep_floor(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    if (m->input & INPUT_FIRST_PERSON) {
        return set_mario_action(m, ACT_FIRST_PERSON, 0);
    }

    if (m->input & INPUT_NONZERO_ANALOG) {
        m->faceAngle[1] = (s16)m->intendedYaw;
        return set_mario_action(m, ACT_WALKING, 0);
    }

    if (m->input & INPUT_B_PRESSED) {
        return set_mario_action(m, ACT_PUNCHING, 0);
    }

    if (m->input & INPUT_Z_DOWN) {
        return set_mario_action(m, ACT_START_CROUCHING, 0);
    }

    return FALSE;
}

s32 act_idle(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (!(m->actionArg & 1) && m->health < 0x300) {
        return set_mario_action(m, ACT_PANTING, 0);
    }

    if (check_common_idle_cancels(m)) {
        return TRUE;
    }

    if (m->actionState == 3) {
        return set_mario_action(m, ACT_START_SLEEPING, 0);
    }

    if (m->actionArg & 1) {
        set_mario_animation(m, MARIO_ANIM_STAND_AGAINST_WALL);
    }
    else {
        switch (m->actionState) {
        case 0:
            set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_LEFT);
            break;

        case 1:
            set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_RIGHT);
            break;

        case 2:
            set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_CENTER);
            break;
        }

        if (is_anim_at_end(m)) {
            // Fall asleep after 10 head turning cycles.
            // act_start_sleeping is triggered earlier in the function
            // when actionState == 3. This happens when Mario's done
            // turning his head back and forth. However, we do some checks
            // here to make sure that Mario would be able to sleep here,
            // and that he's gone through 10 cycles before sleeping.
            // actionTimer is used to track how many cycles have passed.
            if (++m->actionState == 3) {
                f32 deltaYOfFloorBehindMario = m->pos[1] - find_floor_height_relative_polar(m, surfaceLists, -0x8000, 60.0f);
                if (deltaYOfFloorBehindMario < -24.0f || 24.0f < deltaYOfFloorBehindMario || m->floor->flags & SURFACE_FLAG_DYNAMIC) {
                    m->actionState = 0;
                }
                else {
                    // If Mario hasn't turned his head 10 times yet, stay idle instead of going to sleep.
                    m->actionTimer++;
                    if (m->actionTimer < 10) {
                        m->actionState = 0;
                    }
                }
            }
        }
    }

    stationary_ground_step(m, surfaceLists);

    return FALSE;
}

s32 act_start_sleeping(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (check_common_idle_cancels(m)) {
        return TRUE;
    }

    if (m->quicksandDepth > 30.0f) {
        return set_mario_action(m, ACT_IN_QUICKSAND, 0);
    }

    if (m->actionState == 4) {
        return set_mario_action(m, ACT_SLEEPING, 0);
    }

    switch (m->actionState) {
    case 0:
            set_mario_animation(m, MARIO_ANIM_START_SLEEP_IDLE);
        break;

    case 1:
            set_mario_animation(m, MARIO_ANIM_START_SLEEP_SCRATCH);
        break;

    case 2:
            set_mario_animation(m, MARIO_ANIM_START_SLEEP_YAWN);
        break;

    case 3:
            set_mario_animation(m, MARIO_ANIM_START_SLEEP_SITTING);
        break;
    }

    if (is_anim_at_end(m)) {
        m->actionState++;
    }

    stationary_ground_step(m, surfaceLists);
    return FALSE;
}

s32 act_sleeping(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 animFrame;
    if (m->input
        & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE
            | INPUT_FIRST_PERSON | INPUT_STOMPED | INPUT_B_PRESSED | INPUT_Z_PRESSED)) {
        return set_mario_action(m, ACT_WAKING_UP, m->actionState);
    }

    if (m->quicksandDepth > 30.0f) {
        return set_mario_action(m, ACT_WAKING_UP, m->actionState);
    }

    if (m->pos[1] - find_floor_height_relative_polar(m, surfaceLists, -0x8000, 60.0f) > 24.0f) {
        return set_mario_action(m, ACT_WAKING_UP, m->actionState);
    }

    stationary_ground_step(m, surfaceLists);
    switch (m->actionState) {
    case 0:
        animFrame = set_mario_animation(m, MARIO_ANIM_SLEEP_IDLE);

        if (is_anim_at_end(m)) {
            m->actionTimer++;
            if (m->actionTimer > 45) {
                m->actionState++;
            }
        }
        break;

    case 1:
        if (set_mario_animation(m, MARIO_ANIM_SLEEP_START_LYING) == 18) {
        }

        if (is_anim_at_end(m)) {
            m->actionState++;
        }
        break;

    case 2:
        animFrame = set_mario_animation(m, MARIO_ANIM_SLEEP_LYING);
        break;
    }
    return FALSE;
}

s32 act_waking_up(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    m->actionTimer++;

    if (m->actionTimer > 20) {
        return set_mario_action(m, ACT_IDLE, 0);
    }

    stationary_ground_step(m, surfaceLists);

    set_mario_animation(m, !m->actionArg ? MARIO_ANIM_WAKE_FROM_SLEEP : MARIO_ANIM_WAKE_FROM_LYING);

    return FALSE;
}

s32 act_shivering(struct MarioState* m, struct Surfaces* surfaceLists) {
    s32 animFrame;

    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    if (m->input
        & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE
            | INPUT_FIRST_PERSON | INPUT_STOMPED | INPUT_B_PRESSED | INPUT_Z_PRESSED)) {
        m->actionState = 2;
    }

    stationary_ground_step(m, surfaceLists);
    switch (m->actionState) {
    case 0:
        animFrame = set_mario_animation(m, MARIO_ANIM_SHIVERING_WARMING_HAND);
        if (is_anim_past_end(m)) {
            m->actionState = 1;
        }
        break;

    case 1:
        animFrame = set_mario_animation(m, MARIO_ANIM_SHIVERING);
        break;

    case 2:
        set_mario_animation(m, MARIO_ANIM_SHIVERING_RETURN_TO_IDLE);
        if (is_anim_past_end(m)) {
            set_mario_action(m, ACT_IDLE, 0);
        }
        break;
    }
    return FALSE;
}

s32 act_standing_against_wall(struct MarioState* m, struct Surfaces* surfaceLists) {

    if (m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE)) {
        return check_common_action_exits(m);
    }

    if (m->input & INPUT_FIRST_PERSON) {
        return set_mario_action(m, ACT_FIRST_PERSON, 0);
    }

    if (m->input & INPUT_B_PRESSED) {
        return set_mario_action(m, ACT_PUNCHING, 0);
    }

    set_mario_animation(m, MARIO_ANIM_STAND_AGAINST_WALL);
    stationary_ground_step(m, surfaceLists);
    return FALSE;
}

s32 act_crouching(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    if (m->input & INPUT_FIRST_PERSON) {
        return set_mario_action(m, ACT_STOP_CROUCHING, 0);
    }

    if (!(m->input & INPUT_Z_DOWN)) {
        return set_mario_action(m, ACT_STOP_CROUCHING, 0);
    }

    if (m->input & INPUT_NONZERO_ANALOG) {
        return set_mario_action(m, ACT_START_CRAWLING, 0);
    }

    if (m->input & INPUT_B_PRESSED) {
        return set_mario_action(m, ACT_PUNCHING, 9);
    }

    stationary_ground_step(m, surfaceLists);
    set_mario_animation(m, MARIO_ANIM_CROUCHING);
    return FALSE;
}

s32 act_panting(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->health >= 0x500) {
        return set_mario_action(m, ACT_IDLE, 0);
    }

    if (check_common_idle_cancels(m)) {
        return TRUE;
    }

    if (set_mario_animation(m, MARIO_ANIM_WALK_PANTING) == 1) {
    }

    stationary_ground_step(m, surfaceLists);
    return FALSE;
}

void stopping_step(struct MarioState* m, struct Surfaces* surfaceLists, s32 animID, u32 action) {
    stationary_ground_step(m, surfaceLists);
    set_mario_animation(m, animID);
    if (is_anim_at_end(m)) {
        set_mario_action(m, action, 0);
    }
}

s32 act_braking_stop(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_B_PRESSED) {
        return set_mario_action(m, ACT_PUNCHING, 0);
    }

    if (!(m->input & INPUT_FIRST_PERSON)
        && m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE)) {
        return check_common_action_exits(m);
    }

    stopping_step(m, surfaceLists, MARIO_ANIM_STOP_SKID, ACT_IDLE);
    return FALSE;
}

s32 act_butt_slide_stop(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE)) {
        return check_common_action_exits(m);
    }

    stopping_step(m, surfaceLists, MARIO_ANIM_STOP_SLIDE, ACT_IDLE);

    return FALSE;
}

s32 act_slide_kick_slide_stop(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return drop_and_set_mario_action(m, ACT_FREEFALL, 0);
    }

    stopping_step(m, surfaceLists, MARIO_ANIM_CROUCH_FROM_SLIDE_KICK, ACT_CROUCHING);
    return FALSE;
}

s32 act_start_crouching(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    stationary_ground_step(m, surfaceLists);
    set_mario_animation(m, MARIO_ANIM_START_CROUCHING);
    if (is_anim_past_end(m)) {
        set_mario_action(m, ACT_CROUCHING, 0);
    }
    return FALSE;
}

s32 act_stop_crouching(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    stationary_ground_step(m, surfaceLists);
    set_mario_animation(m, MARIO_ANIM_STOP_CROUCHING);
    if (is_anim_past_end(m)) {
        set_mario_action(m, ACT_IDLE, 0);
    }
    return FALSE;
}

s32 act_start_crawling(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_FIRST_PERSON) {
        return set_mario_action(m, ACT_STOP_CROUCHING, 0);
    }

    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    stationary_ground_step(m, surfaceLists);
    set_mario_animation(m, MARIO_ANIM_START_CRAWLING);
    if (is_anim_past_end(m)) {
        set_mario_action(m, ACT_CRAWLING, 0);
    }

    return FALSE;
}

s32 act_stop_crawling(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_OFF_FLOOR) {
        return set_mario_action(m, ACT_FREEFALL, 0);
    }

    if (m->input & INPUT_ABOVE_SLIDE) {
        return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    }

    stationary_ground_step(m, surfaceLists);
    set_mario_animation(m, MARIO_ANIM_STOP_CRAWLING);
    if (is_anim_past_end(m)) {
        set_mario_action(m, ACT_CROUCHING, 0);
    }
    return FALSE;
}

s32 landing_step(struct MarioState* m, struct Surfaces* surfaceLists, s32 arg1, u32 action) {
    stationary_ground_step(m, surfaceLists);
    set_mario_animation(m, arg1);
    if (is_anim_at_end(m)) {
        return set_mario_action(m, action, 0);
    }
    return FALSE;
}

s32 check_common_landing_cancels(struct MarioState* m, u32 action) {
    if (m->input & INPUT_FIRST_PERSON) {
        return set_mario_action(m, ACT_IDLE, 0);
    }

    if (m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE)) {
        return check_common_action_exits(m);
    }

    if (m->input & INPUT_B_PRESSED) {
        return set_mario_action(m, ACT_PUNCHING, 0);
    }

    return FALSE;
}

s32 act_freefall_land_stop(struct MarioState* m, struct Surfaces* surfaceLists) {
    if (check_common_landing_cancels(m, 0)) {
        return TRUE;
    }

    landing_step(m, surfaceLists, MARIO_ANIM_GENERAL_LAND, ACT_IDLE);
    return FALSE;
}

s32 act_lava_boost_land(struct MarioState* m, struct Surfaces* surfaceLists) {
    m->input &= ~(INPUT_FIRST_PERSON | INPUT_B_PRESSED);

    if (check_common_landing_cancels(m, 0)) {
        return TRUE;
    }

    landing_step(m, surfaceLists, MARIO_ANIM_STAND_UP_FROM_LAVA_BOOST, ACT_IDLE);
    return FALSE;
}

s32 act_first_person(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    s32 sp1C = (m->input & (INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE | INPUT_STOMPED)) != 0;

    if (m->actionState == 0) {
        set_camera_mode(m->area->camera, cameraData, surfaceLists, CAMERA_MODE_C_UP, 0x10);
        m->actionState = 1;
    }
    else if (!(m->input & INPUT_FIRST_PERSON) || sp1C) {
        // Go back to the last camera mode
        set_camera_mode(m->area->camera, cameraData, surfaceLists, -1, 1);
        return set_mario_action(m, ACT_IDLE, 0);
    }

    stationary_ground_step(m, surfaceLists);
    set_mario_animation(m, MARIO_ANIM_FIRST_PERSON);
    return FALSE;
}

s32 check_common_stationary_cancels(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    if (m->input & INPUT_SQUISHED) {
        update_mario_sound_and_camera(m, cameraData, surfaceLists);
        return drop_and_set_mario_action(m, ACT_SQUISHED, 0);
    }

    return FALSE;
}

s32 mario_execute_stationary_action(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    s32 cancel;

    if (check_common_stationary_cancels(m, cameraData, surfaceLists)) {
        return TRUE;
    }

    /* clang-format off */
    switch (m->action) {
    case ACT_IDLE:                    cancel = act_idle(m, surfaceLists);                             break;
    case ACT_START_SLEEPING:          cancel = act_start_sleeping(m, surfaceLists);                   break;
    case ACT_SLEEPING:                cancel = act_sleeping(m, surfaceLists);                         break;
    case ACT_WAKING_UP:               cancel = act_waking_up(m, surfaceLists);                        break;
    case ACT_PANTING:                 cancel = act_panting(m, surfaceLists);                          break;
    case ACT_STANDING_AGAINST_WALL:   cancel = act_standing_against_wall(m, surfaceLists);            break;
    case ACT_SHIVERING:               cancel = act_shivering(m, surfaceLists);                        break;
    case ACT_CROUCHING:               cancel = act_crouching(m, surfaceLists);                        break;
    case ACT_START_CROUCHING:         cancel = act_start_crouching(m, surfaceLists);                  break;
    case ACT_STOP_CROUCHING:          cancel = act_stop_crouching(m, surfaceLists);                   break;
    case ACT_START_CRAWLING:          cancel = act_start_crawling(m, surfaceLists);                   break;
    case ACT_STOP_CRAWLING:           cancel = act_stop_crawling(m, surfaceLists);                    break;
    case ACT_SLIDE_KICK_SLIDE_STOP:   cancel = act_slide_kick_slide_stop(m, surfaceLists);            break;
    case ACT_FIRST_PERSON:            cancel = act_first_person(m, cameraData, surfaceLists);         break;
    case ACT_FREEFALL_LAND_STOP:      cancel = act_freefall_land_stop(m, surfaceLists);               break;
    case ACT_LAVA_BOOST_LAND:         cancel = act_lava_boost_land(m, surfaceLists);                  break;
    case ACT_BRAKING_STOP:            cancel = act_braking_stop(m, surfaceLists);                     break;
    case ACT_BUTT_SLIDE_STOP:         cancel = act_butt_slide_stop(m, surfaceLists);                  break;
    }
    /* clang-format on */

    return cancel;
}

void copy_mario_state_to_object(struct MarioState* m, struct Object* o) {
    o->oVelX = m->vel[0];
    o->oVelY = m->vel[1];
    o->oVelZ = m->vel[2];

    o->oPosX = m->pos[0];
    o->oPosY = m->pos[1];
    o->oPosZ = m->pos[2];

    o->oMoveAnglePitch = o->header.gfx.angle[0];
    o->oMoveAngleYaw = o->header.gfx.angle[1];
    o->oMoveAngleRoll = o->header.gfx.angle[2];

    o->oFaceAnglePitch = o->header.gfx.angle[0];
    o->oFaceAngleYaw = o->header.gfx.angle[1];
    o->oFaceAngleRoll = o->header.gfx.angle[2];

    o->oAngleVelPitch = m->angleVel[0];
    o->oAngleVelYaw = m->angleVel[1];
    o->oAngleVelRoll = m->angleVel[2];
}

/**
 * Mario's primary behavior update function.
 */
void bhv_mario_update(struct MarioState* m, struct CameraData* cameraData, struct Surfaces* surfaceLists) {
    u32 particleFlags = 0;
    s32 i;

    particleFlags = execute_mario_action(m, cameraData, surfaceLists);

    // Mario code updates MarioState's versions of position etc, so we need
    // to sync it with the Mario object
    copy_mario_state_to_object(m, m->marioObj);
}