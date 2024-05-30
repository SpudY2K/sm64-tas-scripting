#ifndef AREA_H
#define AREA_H

#include <sm64/UltraTypes.hpp>
#include <sm64/Types.hpp>
#include <sm64/Camera.hpp>

enum LevelNum {
    LEVEL_NONE,
    LEVEL_UNKNOWN_1,
    LEVEL_UNKNOWN_2,
    LEVEL_UNKNOWN_3,
    LEVEL_BBH,
    LEVEL_CCM,
    LEVEL_CASTLE,
    LEVEL_HMC,
    LEVEL_SSL,
    LEVEL_BOB,
    LEVEL_SL,
    LEVEL_WDW,
    LEVEL_JRB,
    LEVEL_THI,
    LEVEL_TTC,
    LEVEL_RR,
    LEVEL_CASTLE_GROUNDS,
    LEVEL_BITDW,
    LEVEL_VCUTM,
    LEVEL_BITFS,
    LEVEL_SA,
    LEVEL_BITS,
    LEVEL_LLL,
    LEVEL_DDD,
    LEVEL_WF,
    LEVEL_ENDING,
    LEVEL_CASTLE_COURTYARD,
    LEVEL_PSS,
    LEVEL_COTMC,
    LEVEL_TOTWC,
    LEVEL_BOWSER_1,
    LEVEL_WMOTR,
    LEVEL_UNKNOWN_32,
    LEVEL_BOWSER_2,
    LEVEL_BOWSER_3,
    LEVEL_UNKNOWN_35,
    LEVEL_TTM,
    LEVEL_UNKNOWN_37,
    LEVEL_UNKNOWN_38,
    LEVEL_COUNT,
    LEVEL_MAX = LEVEL_COUNT - 1,
    LEVEL_MIN = LEVEL_NONE + 1
};

struct WarpNode {
    /*00*/ u8 id;
    /*01*/ u8 destLevel;
    /*02*/ u8 destArea;
    /*03*/ u8 destNode;
};

struct ObjectWarpNode {
    /*0x00*/ struct WarpNode node;
    /*0x04*/ struct Object* object;
    /*0x08*/ struct ObjectWarpNode* next;
};

// From Surface 0x1B to 0x1E
#define INSTANT_WARP_INDEX_START  0x00 // Equal and greater than Surface 0x1B
#define INSTANT_WARP_INDEX_STOP   0x04 // Less than Surface 0x1F

struct InstantWarp {
    /*0x00*/ u8 id; // 0 = 0x1B / 1 = 0x1C / 2 = 0x1D / 3 = 0x1E
    /*0x01*/ u8 area;
    /*0x02*/ Vec3s displacement;
};

struct SpawnInfo {
    /*0x00*/ Vec3s startPos;
    /*0x06*/ Vec3s startAngle;
    /*0x0C*/ s8 areaIndex;
    /*0x0D*/ s8 activeAreaIndex;
    /*0x10*/ u32 behaviorArg;
    /*0x14*/ void* behaviorScript;
    /*0x18*/ struct GraphNode* model;
    /*0x1C*/ struct SpawnInfo* next;
};

struct UnusedArea28 {
    /*0x00*/ s16 unk00;
    /*0x02*/ s16 unk02;
    /*0x04*/ s16 unk04;
    /*0x06*/ s16 unk06;
    /*0x08*/ s16 unk08;
};

struct Whirlpool {
    /*0x00*/ Vec3s pos;
    /*0x03*/ s16 strength;
};

struct Area {
    /*0x00*/ s8 index;
    /*0x01*/ s8 flags; // Only has 1 flag: 0x01 = Is this the active area?
    /*0x02*/ u16 terrainType; // default terrain of the level (set from level script cmd 0x31)
    /*0x04*/ struct GraphNodeRoot* unk04; // geometry layout data
    /*0x10*/ s16* macroObjects; // Macro Objects Ptr (set from level script cmd 0x39)
    /*0x14*/ struct ObjectWarpNode* warpNodes;
    /*0x18*/ struct WarpNode* paintingWarpNodes;
    /*0x1C*/ struct InstantWarp* instantWarps;
    /*0x20*/ struct SpawnInfo* objectSpawnInfos;
    /*0x24*/ struct Camera* camera;
    /*0x28*/ struct UnusedArea28* unused; // Filled by level script 0x3A, but is unused.
    /*0x2C*/ struct Whirlpool* whirlpools[2];
    /*0x34*/ u8 dialog[2]; // Level start dialog number (set by level script cmd 0x30)
    /*0x36*/ u16 musicParam;
    /*0x38*/ u16 musicParam2;
};

// All the transition data to be used in screen_transition.c
struct WarpTransitionData {
    /*0x00*/ u8 red;
    /*0x01*/ u8 green;
    /*0x02*/ u8 blue;

    /*0x04*/ s16 startTexRadius;
    /*0x06*/ s16 endTexRadius;
    /*0x08*/ s16 startTexX;
    /*0x0A*/ s16 startTexY;
    /*0x0C*/ s16 endTexX;
    /*0x0E*/ s16 endTexY;

    /*0x10*/ s16 texTimer; // always 0, does seems to affect transition when disabled
};

#define WARP_TRANSITION_FADE_FROM_COLOR  0x00
#define WARP_TRANSITION_FADE_INTO_COLOR  0x01
#define WARP_TRANSITION_FADE_FROM_STAR   0x08
#define WARP_TRANSITION_FADE_INTO_STAR   0x09
#define WARP_TRANSITION_FADE_FROM_CIRCLE 0x0A
#define WARP_TRANSITION_FADE_INTO_CIRCLE 0x0B
#define WARP_TRANSITION_FADE_FROM_MARIO  0x10
#define WARP_TRANSITION_FADE_INTO_MARIO  0x11
#define WARP_TRANSITION_FADE_FROM_BOWSER 0x12
#define WARP_TRANSITION_FADE_INTO_BOWSER 0x13

struct WarpTransition {
    /*0x00*/ u8 isActive;       // Is the transition active. (either TRUE or FALSE)
    /*0x01*/ u8 type;           // Determines the type of transition to use (circle, star, etc.)
    /*0x02*/ u8 time;           // Amount of time to complete the transition (in frames)
    /*0x03*/ u8 pauseRendering; // Should the game stop rendering. (either TRUE or FALSE)
    /*0x04*/ struct WarpTransitionData data;
};

enum MenuOption {
    MENU_OPT_NONE,
    MENU_OPT_1,
    MENU_OPT_2,
    MENU_OPT_3,
    MENU_OPT_DEFAULT = MENU_OPT_1,

    // Course Pause Menu
    MENU_OPT_CONTINUE = MENU_OPT_1,
    MENU_OPT_EXIT_COURSE = MENU_OPT_2,
    MENU_OPT_CAMERA_ANGLE_R = MENU_OPT_3,

    // Save Menu
    MENU_OPT_SAVE_AND_CONTINUE = MENU_OPT_1,
    MENU_OPT_SAVE_AND_QUIT = MENU_OPT_2,
    MENU_OPT_CONTINUE_DONT_SAVE = MENU_OPT_3
};

struct AreaData {
    struct Area* gCurrentArea;
    s16 gCurrAreaIndex;
    s16 gCurrCourseNum;
    s16 gCurrLevelNum;
    s32 gCurrLevelArea = 0;
    u32 gPrevLevel = 0;
    struct Area gAreaData[8];
};

#endif // AREA_H