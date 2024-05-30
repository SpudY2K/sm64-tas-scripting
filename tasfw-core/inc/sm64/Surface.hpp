#pragma once
#ifndef SURFACE_H
#define SURFACE_H
#include <sm64/Types.hpp>

#define LEVEL_BOUNDARY_MAX  0x2000 // 8192

#define CELL_HEIGHT_LIMIT           20000
#define FLOOR_LOWER_LIMIT           -11000
#define FLOOR_LOWER_LIMIT_MISC      (FLOOR_LOWER_LIMIT + 1000)
#define FLOOR_LOWER_LIMIT_SHADOW    (FLOOR_LOWER_LIMIT + 1000.0)

struct WallCollisionData {
    /*0x00*/ f32 x, y, z;
    /*0x0C*/ f32 offsetY;
    /*0x10*/ f32 radius;
    /*0x14*/ u8 filler[2];
    /*0x16*/ s16 numWalls;
    /*0x18*/ struct Surface* walls[4];
};

struct FloorGeometry {
    u8 filler[16]; // possibly position data?
    f32 normalX;
    f32 normalY;
    f32 normalZ;
    f32 originOffset;
};

struct SurfaceNode {
	struct SurfaceNode* next;
	struct Surface* surface;
};

struct Surfaces {
    struct SurfaceNode* staticFloors;
    struct SurfaceNode* staticWalls;
    struct SurfaceNode* staticCeilings;
    struct SurfaceNode* dynamicFloors;
    struct SurfaceNode* dynamicWalls;
    struct SurfaceNode* dynamicCeilings;
};

void find_floor(
	Vec3f* marioPos, struct Surface* surfaces, int surfaceCount,
	struct Surface** floor);
bool floor_is_slope(struct Surface* floor);
static short get_floor_class(struct Surface* floor);
void transform_surfaces(
	struct Surface* surfaces, int numSurfaces, Mat4* transform);
int get_surfaces(struct Object* obj, struct Surface** surfaces);
static void load_object_surfaces(
	short** data, short* vertexData, struct Surface** surfaces);
static short surface_has_force(short surfaceType);
static void get_object_vertices(
	struct Object* obj, short** data, short* vertexData);
static void read_surface_data(
	short* vertexData, short** vertexIndices, struct Surface* surface);

void add_surface(s16 dynamic, struct Surface* surface, struct SurfaceNode* newNode, struct Surfaces* surfaceLists);
bool read_surface_data(TerrainData* vertexData, struct Surface* surface, struct Object* o);
s32 f32_find_wall_collision(struct Surfaces* surfaceLists, f32* xPtr, f32* yPtr, f32* zPtr, f32 offsetY, f32 radius);
s32 find_wall_collisions(struct Surfaces* surfaceLists, WallCollisionData* colData);
f32 find_ceil(struct Surfaces* surfaceLists, f32 posX, f32 posY, f32 posZ, struct Surface** pceil);
f32 find_floor(struct Surfaces* surfaceLists, f32 xPos, f32 yPos, f32 zPos, struct Surface** pfloor);
f32 find_water_level(f32 x, f32 z);
f32 find_poison_gas_level(f32 x, f32 z);
#endif