#include <sm64/Math.hpp>
#include <cmath>
#include <sm64/Surface.hpp>
#include <sm64/Trig.hpp>

void linear_mtxf_mul_vec3f(Mat4 m, Vec3f dst, Vec3f v)
{
	for (int i = 0; i < 3; i++)
	{
		dst[i] = m[0][i] * v[0] + m[1][i] * v[1] + m[2][i] * v[2];
	}
}

void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw)
{
	Vec3f lateralDir = {gSineTable[yaw], 0, gCosineTable[yaw]};
	Vec3f leftDir;
	Vec3f forwardDir;

	vec3f_normalize(upDir);

	vec3f_cross(leftDir, upDir, lateralDir);
	vec3f_normalize(leftDir);

	vec3f_cross(forwardDir, leftDir, upDir);
	vec3f_normalize(forwardDir);

	dest[0][0] = leftDir[0];
	dest[0][1] = leftDir[1];
	dest[0][2] = leftDir[2];
	dest[3][0] = pos[0];

	dest[1][0] = upDir[0];
	dest[1][1] = upDir[1];
	dest[1][2] = upDir[2];
	dest[3][1] = pos[1];

	dest[2][0] = forwardDir[0];
	dest[2][1] = forwardDir[1];
	dest[2][2] = forwardDir[2];
	dest[3][2] = pos[2];

	dest[0][3] = 0.0f;
	dest[1][3] = 0.0f;
	dest[2][3] = 0.0f;
	dest[3][3] = 1.0f;
}

/**
 * Set 'mtx' to a transformation matrix that aligns an object with the terrain
 * based on 3 height samples in an equilateral triangle around the object.
 * Used for Mario when crawling or sliding.
 * 'yaw' is the angle which it should face
 * 'pos' is the object's position in the world
 * 'radius' is the distance from each triangle vertex to the center
 */
void mtxf_align_terrain_triangle(struct Surfaces* surfaceLists, Mat4 mtx, Vec3f pos, s16 yaw, f32 radius) {
    struct Surface* sp74;
    Vec3f point0;
    Vec3f point1;
    Vec3f point2;
    Vec3f forward;
    Vec3f xColumn;
    Vec3f yColumn;
    Vec3f zColumn;
    f32 avgY;
    f32 minY = -radius * 3;

    point0[0] = pos[0] + radius * sins(yaw + 0x2AAA);
    point0[2] = pos[2] + radius * coss(yaw + 0x2AAA);
    point1[0] = pos[0] + radius * sins(yaw + 0x8000);
    point1[2] = pos[2] + radius * coss(yaw + 0x8000);
    point2[0] = pos[0] + radius * sins(yaw + 0xD555);
    point2[2] = pos[2] + radius * coss(yaw + 0xD555);

    point0[1] = find_floor(surfaceLists, point0[0], pos[1] + 150, point0[2], &sp74);
    point1[1] = find_floor(surfaceLists, point1[0], pos[1] + 150, point1[2], &sp74);
    point2[1] = find_floor(surfaceLists, point2[0], pos[1] + 150, point2[2], &sp74);

    if (point0[1] - pos[1] < minY) {
        point0[1] = pos[1];
    }

    if (point1[1] - pos[1] < minY) {
        point1[1] = pos[1];
    }

    if (point2[1] - pos[1] < minY) {
        point2[1] = pos[1];
    }

    avgY = (point0[1] + point1[1] + point2[1]) / 3;

    vec3f_set(forward, sins(yaw), 0, coss(yaw));
    find_vector_perpendicular_to_plane(yColumn, point0, point1, point2);
    vec3f_normalize(yColumn);
    vec3f_cross(xColumn, yColumn, forward);
    vec3f_normalize(xColumn);
    vec3f_cross(zColumn, xColumn, yColumn);
    vec3f_normalize(zColumn);

    mtx[0][0] = xColumn[0];
    mtx[0][1] = xColumn[1];
    mtx[0][2] = xColumn[2];
    mtx[3][0] = pos[0];

    mtx[1][0] = yColumn[0];
    mtx[1][1] = yColumn[1];
    mtx[1][2] = yColumn[2];
    mtx[3][1] = (avgY < pos[1]) ? pos[1] : avgY;

    mtx[2][0] = zColumn[0];
    mtx[2][1] = zColumn[1];
    mtx[2][2] = zColumn[2];
    mtx[3][2] = pos[2];

    mtx[0][3] = 0;
    mtx[1][3] = 0;
    mtx[2][3] = 0;
    mtx[3][3] = 1;
}

/**
 * Set 'dest' the normal vector of a triangle with vertices a, b and c.
 * It is similar to vec3f_cross, but it calculates the vectors (c-b) and (b-a)
 * at the same time.
 */
void* find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c) {
    dest[0] = (b[1] - a[1]) * (c[2] - b[2]) - (c[1] - b[1]) * (b[2] - a[2]);
    dest[1] = (b[2] - a[2]) * (c[0] - b[0]) - (c[2] - b[2]) * (b[0] - a[0]);
    dest[2] = (b[0] - a[0]) * (c[1] - b[1]) - (c[0] - b[0]) * (b[1] - a[1]);
    return &dest; //! warning: function returns address of local variable
}

/// Make vector 'dest' the cross product of vectors a and b.
void vec3f_cross(Vec3f dest, Vec3f a, Vec3f b)
{
	dest[0] = a[1] * b[2] - b[1] * a[2];
	dest[1] = a[2] * b[0] - b[2] * a[0];
	dest[2] = a[0] * b[1] - b[0] * a[1];
}

/// Scale vector 'dest' so it has length 1
void vec3f_normalize(Vec3f dest)
{
	//! Possible division by zero
	float invsqrt =
		1.0f / sqrtf(dest[0] * dest[0] + dest[1] * dest[1] + dest[2] * dest[2]);

	dest[0] *= invsqrt;
	dest[1] *= invsqrt;
	dest[2] *= invsqrt;
}

/**
 * Take the vector starting at 'from' pointed at 'to' an retrieve the length
 * of that vector, as well as the yaw and pitch angles.
 * Basically it converts the direction to spherical coordinates.
 */
void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32* dist, s16* pitch, s16* yaw) {
    f32 x = to[0] - from[0];
    f32 y = to[1] - from[1];
    f32 z = to[2] - from[2];

    *dist = sqrtf(x * x + y * y + z * z);
    *pitch = atan2s(sqrtf(x * x + z * z), y);
    *yaw = atan2s(z, x);
}

/**
 * Construct the 'to' point which is distance 'dist' away from the 'from' position,
 * and has the angles pitch and yaw.
 */
void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32 dist, s16 pitch, s16 yaw) {
    to[0] = from[0] + dist * coss(pitch) * sins(yaw);
    to[1] = from[1] + dist * sins(pitch);
    to[2] = from[2] + dist * coss(pitch) * coss(yaw);
}

/// Copy vector 'src' to 'dest'
void* vec3f_copy(Vec3f dest, Vec3f src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return &dest; //! warning: function returns address of local variable
}

/// Set vector 'dest' to (x, y, z)
void* vec3f_set(Vec3f dest, f32 x, f32 y, f32 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return &dest; //! warning: function returns address of local variable
}

/// Add vector 'a' to 'dest'
void* vec3f_add(Vec3f dest, Vec3f a) {
    dest[0] += a[0];
    dest[1] += a[1];
    dest[2] += a[2];
    return &dest; //! warning: function returns address of local variable
}

/// Make 'dest' the sum of vectors a and b.
void* vec3f_sum(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return &dest; //! warning: function returns address of local variable
}

/// Copy vector src to dest
void* vec3s_copy(Vec3s dest, Vec3s src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
    return &dest; //! warning: function returns address of local variable
}

/// Set vector 'dest' to (x, y, z)
void* vec3s_set(Vec3s dest, s16 x, s16 y, s16 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
    return &dest; //! warning: function returns address of local variable
}

/// Add vector a to 'dest'
void* vec3s_add(Vec3s dest, Vec3s a) {
    dest[0] += a[0];
    dest[1] += a[1];
    dest[2] += a[2];
    return &dest; //! warning: function returns address of local variable
}

/// Make 'dest' the sum of vectors a and b.
void* vec3s_sum(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
    dest[2] = a[2] + b[2];
    return &dest; //! warning: function returns address of local variable
}

/// Subtract vector a from 'dest'
void* vec3s_sub(Vec3s dest, Vec3s a) {
    dest[0] -= a[0];
    dest[1] -= a[1];
    dest[2] -= a[2];
    return &dest; //! warning: function returns address of local variable
}

/// Convert short vector a to float vector 'dest'
void* vec3s_to_vec3f(Vec3f dest, Vec3s a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
    return &dest; //! warning: function returns address of local variable
}

/**
 * Convert float vector a to a short vector 'dest' by rounding the components
 * to the nearest integer.
 */
void* vec3f_to_vec3s(Vec3s dest, Vec3f a) {
    // add/subtract 0.5 in order to round to the nearest s32 instead of truncating
    dest[0] = a[0] + ((a[0] > 0) ? 0.5f : -0.5f);
    dest[1] = a[1] + ((a[1] > 0) ? 0.5f : -0.5f);
    dest[2] = a[2] + ((a[2] > 0) ? 0.5f : -0.5f);
    return &dest; //! warning: function returns address of local variable
}

/**
 * Return the value 'current' after it tries to approach target, going up at
 * most 'inc' and going down at most 'dec'.
 */
s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec) {
    //! If target is close to the max or min s32, then it's possible to overflow
    // past it without stopping.

    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    }
    else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}

/**
 * Return the value 'current' after it tries to approach target, going up at
 * most 'inc' and going down at most 'dec'.
 */
f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec) {
    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    }
    else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}
