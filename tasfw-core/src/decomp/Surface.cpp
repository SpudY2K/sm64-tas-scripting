#include <sm64/Types.hpp>
#include <sm64/UltraTypes.hpp>
#include <sm64/Surface.hpp>
#include <sm64/SurfaceTerrains.hpp>
#include <cmath>

/**
 * Add a surface to the correct cell list of surfaces.
 * @param dynamic Determines whether the surface is static or dynamic
 * @param cellX The X position of the cell in which the surface resides
 * @param cellZ The Z position of the cell in which the surface resides
 * @param surface The surface to add
 */

void add_surface(s16 dynamic, struct Surface* surface, struct SurfaceNode* newNode, struct Surfaces* surfaceLists) {
    struct SurfaceNode* list;
    s16 surfacePriority;
    s16 priority;
    s16 sortDir;
    s16 listIndex;

    if (surface->normal.y > 0.01) {
        if (dynamic) {
            list = surfaceLists->dynamicFloors;
        }
        else {
            list = surfaceLists->staticFloors;
        }
        sortDir = 1; // highest to lowest, then insertion order
    }
    else if (surface->normal.y < -0.01) {
        if (dynamic) {
            list = surfaceLists->dynamicCeilings;
        }
        else {
            list = surfaceLists->staticCeilings;
        }
        sortDir = -1; // lowest to highest, then insertion order
    }
    else {
        if (dynamic) {
            list = surfaceLists->dynamicWalls;
        }
        else {
            list = surfaceLists->staticWalls;
        }
        sortDir = 0; // insertion order

        if (surface->normal.x < -0.707 || surface->normal.x > 0.707) {
            surface->flags |= SURFACE_FLAG_X_PROJECTION;
        }
    }

    //! (Surface Cucking) Surfaces are sorted by the height of their first
    //  vertex. Since vertices aren't ordered by height, this causes many
    //  lower triangles to be sorted higher. This worsens surface cucking since
    //  many functions only use the first triangle in surface order that fits,
    //  missing higher surfaces.
    //  upperY would be a better sort method.
    surfacePriority = surface->vertex1[1] * sortDir;

    newNode->surface = surface;

    // Loop until we find the appropriate place for the surface in the list.
    while (list->next != NULL) {
        priority = list->next->surface->vertex1[1] * sortDir;

        if (surfacePriority > priority) {
            break;
        }

        list = list->next;
    }

    newNode->next = list->next;
    list->next = newNode;
}

/**
 * Initializes a Surface struct using the given vertex data
 * @param vertexData The raw data containing vertex positions
 * @param vertexIndices Helper which tells positions in vertexData to start reading vertices
 */
bool read_surface_data(TerrainData* vertexData, struct Surface* surface, struct Object* o) {
    s32 x1, y1, z1;
    s32 x2, y2, z2;
    s32 x3, y3, z3;
    s32 maxY, minY;
    f32 nx, ny, nz;
    f32 mag;
    TerrainData offset1, offset2, offset3;

    offset1 = 0;
    offset2 = 3;
    offset3 = 6;

    if (o) {
        x1 = (TerrainData)(*(vertexData + offset1 + 0) * o->transform[0][0] + *(vertexData + offset1 + 1) * o->transform[1][0] + *(vertexData + offset1 + 2) * o->transform[2][0] + o->transform[3][0]);
        y1 = (TerrainData)(*(vertexData + offset1 + 0) * o->transform[0][1] + *(vertexData + offset1 + 1) * o->transform[1][1] + *(vertexData + offset1 + 2) * o->transform[2][1] + o->transform[3][1]);
        z1 = (TerrainData)(*(vertexData + offset1 + 0) * o->transform[0][2] + *(vertexData + offset1 + 1) * o->transform[1][2] + *(vertexData + offset1 + 2) * o->transform[2][2] + o->transform[3][2]);

        x2 = (TerrainData)(*(vertexData + offset2 + 0) * o->transform[0][0] + *(vertexData + offset2 + 1) * o->transform[1][0] + *(vertexData + offset2 + 2) * o->transform[2][0] + o->transform[3][0]);
        y2 = (TerrainData)(*(vertexData + offset2 + 0) * o->transform[0][1] + *(vertexData + offset2 + 1) * o->transform[1][1] + *(vertexData + offset2 + 2) * o->transform[2][1] + o->transform[3][1]);
        z2 = (TerrainData)(*(vertexData + offset2 + 0) * o->transform[0][2] + *(vertexData + offset2 + 1) * o->transform[1][2] + *(vertexData + offset2 + 2) * o->transform[2][2] + o->transform[3][2]);

        x3 = (TerrainData)(*(vertexData + offset3 + 0) * o->transform[0][0] + *(vertexData + offset3 + 1) * o->transform[1][0] + *(vertexData + offset3 + 2) * o->transform[2][0] + o->transform[3][0]);
        y3 = (TerrainData)(*(vertexData + offset3 + 0) * o->transform[0][1] + *(vertexData + offset3 + 1) * o->transform[1][1] + *(vertexData + offset3 + 2) * o->transform[2][1] + o->transform[3][1]);
        z3 = (TerrainData)(*(vertexData + offset3 + 0) * o->transform[0][2] + *(vertexData + offset3 + 1) * o->transform[1][2] + *(vertexData + offset3 + 2) * o->transform[2][2] + o->transform[3][2]);
    }
    else {
        x1 = *(vertexData + offset1 + 0);
        y1 = *(vertexData + offset1 + 1);
        z1 = *(vertexData + offset1 + 2);

        x2 = *(vertexData + offset2 + 0);
        y2 = *(vertexData + offset2 + 1);
        z2 = *(vertexData + offset2 + 2);

        x3 = *(vertexData + offset3 + 0);
        y3 = *(vertexData + offset3 + 1);
        z3 = *(vertexData + offset3 + 2);
    }

    // (v2 - v1) x (v3 - v2)
    nx = (y2 - y1) * (z3 - z2) - (z2 - z1) * (y3 - y2);
    ny = (z2 - z1) * (x3 - x2) - (x2 - x1) * (z3 - z2);
    nz = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);
    mag = sqrtf(nx * nx + ny * ny + nz * nz);

    // Could have used min_3 and max_3 for this...
    minY = y1;
    if (y2 < minY) {
        minY = y2;
    }
    if (y3 < minY) {
        minY = y3;
    }

    maxY = y1;
    if (y2 > maxY) {
        maxY = y2;
    }
    if (y3 > maxY) {
        maxY = y3;
    }

    // Checking to make sure no DIV/0
    if (mag < 0.0001) {
        return FALSE;
    }
    mag = (f32)(1.0 / mag);
    nx *= mag;
    ny *= mag;
    nz *= mag;

    surface->vertex1[0] = x1;
    surface->vertex2[0] = x2;
    surface->vertex3[0] = x3;

    surface->vertex1[1] = y1;
    surface->vertex2[1] = y2;
    surface->vertex3[1] = y3;

    surface->vertex1[2] = z1;
    surface->vertex2[2] = z2;
    surface->vertex3[2] = z3;

    surface->normal.x = nx;
    surface->normal.y = ny;
    surface->normal.z = nz;

    surface->originOffset = -(nx * x1 + ny * y1 + nz * z1);

    surface->lowerY = minY - 5;
    surface->upperY = maxY + 5;

    surface->room = 0;
    surface->type = *(vertexData + 9);
    surface->force = 0;
    surface->flags = 0;
    surface->object = o;

    if (surface->object) {
        surface->flags |= SURFACE_FLAG_DYNAMIC;
    }

    if (!(surface->normal.y > 0.01 || surface->normal.y < -0.01) && (surface->normal.x < -0.707 || surface->normal.x > 0.707)) {
        surface->flags |= SURFACE_FLAG_X_PROJECTION;
    }

    return TRUE;
}

/**************************************************
 *                      WALLS                     *
 **************************************************/

 /**
  * Iterate through the list of walls until all walls are checked and
  * have given their wall push.
  */
static s32 find_wall_collisions_from_list(struct SurfaceNode* surfaceNode,
    struct WallCollisionData* data) {
    struct Surface* surf;
    f32 offset;
    f32 radius = data->radius;
    f32 x = data->x;
    f32 y = data->y + data->offsetY;
    f32 z = data->z;
    f32 px, pz;
    f32 w1, w2, w3;
    f32 y1, y2, y3;
    s32 numCols = 0;

    // Max collision radius = 200
    if (radius > 200.0f) {
        radius = 200.0f;
    }

    // Stay in this loop until out of walls.
    while (surfaceNode != NULL) {
        surf = surfaceNode->surface;
        surfaceNode = surfaceNode->next;

        // Exclude a large number of walls immediately to optimize.
        if (y < surf->lowerY || y > surf->upperY) {
            continue;
        }

        offset = surf->normal.x * x + surf->normal.y * y + surf->normal.z * z + surf->originOffset;

        if (offset < -radius || offset > radius) {
            continue;
        }

        px = x;
        pz = z;

        //! (Quantum Tunneling) Due to issues with the vertices walls choose and
        //  the fact they are floating point, certain floating point positions
        //  along the seam of two walls may collide with neither wall or both walls.
        if (surf->flags & SURFACE_FLAG_X_PROJECTION) {
            w1 = -surf->vertex1[2];            w2 = -surf->vertex2[2];            w3 = -surf->vertex3[2];
            y1 = surf->vertex1[1];            y2 = surf->vertex2[1];            y3 = surf->vertex3[1];

            if (surf->normal.x > 0.0f) {
                if ((y1 - y) * (w2 - w1) - (w1 - -pz) * (y2 - y1) > 0.0f) {
                    continue;
                }
                if ((y2 - y) * (w3 - w2) - (w2 - -pz) * (y3 - y2) > 0.0f) {
                    continue;
                }
                if ((y3 - y) * (w1 - w3) - (w3 - -pz) * (y1 - y3) > 0.0f) {
                    continue;
                }
            }
            else {
                if ((y1 - y) * (w2 - w1) - (w1 - -pz) * (y2 - y1) < 0.0f) {
                    continue;
                }
                if ((y2 - y) * (w3 - w2) - (w2 - -pz) * (y3 - y2) < 0.0f) {
                    continue;
                }
                if ((y3 - y) * (w1 - w3) - (w3 - -pz) * (y1 - y3) < 0.0f) {
                    continue;
                }
            }
        }
        else {
            w1 = surf->vertex1[0];            w2 = surf->vertex2[0];            w3 = surf->vertex3[0];
            y1 = surf->vertex1[1];            y2 = surf->vertex2[1];            y3 = surf->vertex3[1];

            if (surf->normal.z > 0.0f) {
                if ((y1 - y) * (w2 - w1) - (w1 - px) * (y2 - y1) > 0.0f) {
                    continue;
                }
                if ((y2 - y) * (w3 - w2) - (w2 - px) * (y3 - y2) > 0.0f) {
                    continue;
                }
                if ((y3 - y) * (w1 - w3) - (w3 - px) * (y1 - y3) > 0.0f) {
                    continue;
                }
            }
            else {
                if ((y1 - y) * (w2 - w1) - (w1 - px) * (y2 - y1) < 0.0f) {
                    continue;
                }
                if ((y2 - y) * (w3 - w2) - (w2 - px) * (y3 - y2) < 0.0f) {
                    continue;
                }
                if ((y3 - y) * (w1 - w3) - (w3 - px) * (y1 - y3) < 0.0f) {
                    continue;
                }
            }
        }

        //! (Wall Overlaps) Because this doesn't update the x and z local variables,
        //  multiple walls can push mario more than is required.
        data->x += surf->normal.x * (radius - offset);
        data->z += surf->normal.z * (radius - offset);

        //! (Unreferenced Walls) Since this only returns the first four walls,
        //  this can lead to wall interaction being missed. Typically unreferenced walls
        //  come from only using one wall, however.
        if (data->numWalls < 4) {
            data->walls[data->numWalls++] = surf;
        }

        numCols++;
    }

    return numCols;
}

/**
 * Formats the position and wall search for find_wall_collisions.
 */
s32 f32_find_wall_collision(struct Surfaces* surfaceLists, f32* xPtr, f32* yPtr, f32* zPtr, f32 offsetY, f32 radius) {
    struct WallCollisionData collision;
    s32 numCollisions = 0;

    collision.offsetY = offsetY;
    collision.radius = radius;

    collision.x = *xPtr;
    collision.y = *yPtr;
    collision.z = *zPtr;

    collision.numWalls = 0;

    numCollisions = find_wall_collisions(surfaceLists, &collision);

    *xPtr = collision.x;
    *yPtr = collision.y;
    *zPtr = collision.z;

    return numCollisions;
}

/**
 * Find wall collisions and receive their push.
 */
s32 find_wall_collisions(struct Surfaces* surfaceLists, struct WallCollisionData* colData) {
    struct SurfaceNode* node;
    s32 numCollisions = 0;
    TerrainData x = colData->x;
    TerrainData z = colData->z;

    colData->numWalls = 0;

    // Check for surfaces belonging to objects.
    numCollisions += find_wall_collisions_from_list(surfaceLists->dynamicWalls->next, colData);

    // Check for surfaces that are a part of level geometry.
    numCollisions += find_wall_collisions_from_list(surfaceLists->staticWalls->next, colData);

    return numCollisions;
}

/**************************************************
 *                     CEILINGS                   *
 **************************************************/

 /**
  * Iterate through the list of ceilings and find the first ceiling over a given point.
  */
static struct Surface* find_ceil_from_list(struct SurfaceNode* surfaceNode, s32 x, s32 y, s32 z, f32* pheight) {
    struct Surface* surf;
    s32 x1, z1, x2, z2, x3, z3;
    struct Surface* ceil = NULL;

    ceil = NULL;

    // Stay in this loop until out of ceilings.
    while (surfaceNode != NULL) {
        surf = surfaceNode->surface;
        surfaceNode = surfaceNode->next;

        x1 = surf->vertex1[0];
        z1 = surf->vertex1[2];
        z2 = surf->vertex2[2];
        x2 = surf->vertex2[0];

        // Checking if point is in bounds of the triangle laterally.
        if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) > 0) {
            continue;
        }

        // Slight optimization by checking these later.
        x3 = surf->vertex3[0];
        z3 = surf->vertex3[2];
        if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) > 0) {
            continue;
        }
        if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) > 0) {
            continue;
        }

        {
            f32 nx = surf->normal.x;
            f32 ny = surf->normal.y;
            f32 nz = surf->normal.z;
            f32 oo = surf->originOffset;
            f32 height;

            // If a wall, ignore it. Likely a remnant, should never occur.
            if (ny == 0.0f) {
                continue;
            }

            // Find the ceil height at the specific point.
            height = -(x * nx + nz * z + oo) / ny;

            // Checks for ceiling interaction with a 78 unit buffer.
            //! (Exposed Ceilings) Because any point above a ceiling counts
            //  as interacting with a ceiling, ceilings far below can cause
            // "invisible walls" that are really just exposed ceilings.
            if (y - (height - -78.0f) > 0.0f) {
                continue;
            }

            *pheight = height;
            ceil = surf;
            break;
        }
    }

    //! (Surface Cucking) Since only the first ceil is returned and not the lowest,
    //  lower ceilings can be "cucked" by higher ceilings.
    return ceil;
}

/**
 * Find the lowest ceiling above a given position and return the height.
 */
f32 find_ceil(struct Surfaces* surfaceLists, f32 posX, f32 posY, f32 posZ, struct Surface** pceil) {
    struct Surface* ceil, * dynamicCeil;
    struct SurfaceNode* surfaceList;

    f32 height = CELL_HEIGHT_LIMIT;
    f32 dynamicHeight = CELL_HEIGHT_LIMIT;

    //! (Parallel Universes) Because position is casted to an s16, reaching higher
    //  float locations can return ceilings despite them not existing there.
    //  (Dynamic ceilings will unload due to the range.)
    TerrainData x = (TerrainData)posX;
    TerrainData y = (TerrainData)posY;
    TerrainData z = (TerrainData)posZ;

    *pceil = NULL;

    // Check for surfaces belonging to objects.
    dynamicCeil = find_ceil_from_list(surfaceLists->dynamicCeilings->next, x, y, z, &dynamicHeight);

    // Check for surfaces that are a part of level geometry.
    ceil = find_ceil_from_list(surfaceLists->staticCeilings->next, x, y, z, &height);

    if (dynamicHeight < height) {
        ceil = dynamicCeil;
        height = dynamicHeight;
    }

    *pceil = ceil;

    return height;
}

/**************************************************
 *                     FLOORS                     *
 **************************************************/

/**
 * Iterate through the list of floors and find the first floor under a given point.
 */
static struct Surface* find_floor_from_list(struct SurfaceNode* surfaceNode, s32 x, s32 y, s32 z, f32* pheight) {
    struct Surface* surf;
    s32 x1, z1, x2, z2, x3, z3;
    f32 nx, ny, nz;
    f32 oo;
    f32 height;
    struct Surface* floor = NULL;

    // Iterate through the list of floors until there are no more floors.
    while (surfaceNode != NULL) {
        surf = surfaceNode->surface;
        surfaceNode = surfaceNode->next;

        x1 = surf->vertex1[0];
        z1 = surf->vertex1[2];
        x2 = surf->vertex2[0];
        z2 = surf->vertex2[2];

        // Check that the point is within the triangle bounds.
        if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) < 0) {
            continue;
        }

        // To slightly save on computation time, set this later.
        x3 = surf->vertex3[0];
        z3 = surf->vertex3[2];

        if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) < 0) {
            continue;
        }
        if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) < 0) {
            continue;
        }

        nx = surf->normal.x;
        ny = surf->normal.y;
        nz = surf->normal.z;
        oo = surf->originOffset;

        // If a wall, ignore it. Likely a remnant, should never occur.
        if (ny == 0.0f) {
            continue;
        }

        // Find the height of the floor at a given location.
        height = -(x * nx + nz * z + oo) / ny;
        // Checks for floor interaction with a 78 unit buffer.
        if (y - (height + -78.0f) < 0.0f) {
            continue;
        }

        *pheight = height;
        floor = surf;
        break;
    }

    //! (Surface Cucking) Since only the first floor is returned and not the highest,
    //  higher floors can be "cucked" by lower floors.
    return floor;
}

/**
 * Find the highest floor under a given position and return the height.
 */
f32 find_floor(struct Surfaces* surfaceLists, f32 xPos, f32 yPos, f32 zPos, struct Surface** pfloor) {
    struct Surface* floor, * dynamicFloor;
    struct SurfaceNode* surfaceList;

    f32 height = FLOOR_LOWER_LIMIT;
    f32 dynamicHeight = FLOOR_LOWER_LIMIT;

    //! (Parallel Universes) Because position is casted to an s16, reaching higher
    //  float locations can return floors despite them not existing there.
    //  (Dynamic floors will unload due to the range.)
    TerrainData x = (TerrainData)xPos;
    TerrainData y = (TerrainData)yPos;
    TerrainData z = (TerrainData)zPos;

    *pfloor = NULL;

    // Check for surfaces belonging to objects.
    dynamicFloor = find_floor_from_list(surfaceLists->dynamicFloors->next, x, y, z, &dynamicHeight);

    // Check for surfaces that are a part of level geometry.
    floor = find_floor_from_list(surfaceLists->staticFloors->next, x, y, z, &height);

    if (dynamicHeight > height) {
        floor = dynamicFloor;
        height = dynamicHeight;
    }

    *pfloor = floor;

    return height;
}

/**************************************************
 *               ENVIRONMENTAL BOXES              *
 **************************************************/

 /**
  * Finds the height of water at a given location.
  */
f32 find_water_level(f32 x, f32 z) {
    return FLOOR_LOWER_LIMIT;
}

/**
 * Finds the height of the poison gas (used only in HMC) at a given location.
 */
f32 find_poison_gas_level(f32 x, f32 z) {
    return FLOOR_LOWER_LIMIT;
}