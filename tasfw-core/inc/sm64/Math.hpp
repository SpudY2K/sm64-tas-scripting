#pragma once

#ifndef MATH_H
#define MATH_H

#include <sm64/Types.hpp>

#define min(a, b) ((a) <= (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

void* vec3f_copy(Vec3f dest, Vec3f src);
void* vec3f_set(Vec3f dest, f32 x, f32 y, f32 z);
void* vec3f_add(Vec3f dest, Vec3f a);
void* vec3f_sum(Vec3f dest, Vec3f a, Vec3f b);
void* vec3s_copy(Vec3s dest, Vec3s src);
void* vec3s_set(Vec3s dest, s16 x, s16 y, s16 z);
void* vec3s_add(Vec3s dest, Vec3s a);
void* vec3s_sum(Vec3s dest, Vec3s a, Vec3s b);
void* vec3s_sub(Vec3s dest, Vec3s a);
void* vec3s_to_vec3f(Vec3f dest, Vec3s a);
void* vec3f_to_vec3s(Vec3s dest, Vec3f a);
void linear_mtxf_mul_vec3f(Mat4 m, Vec3f dst, Vec3f v);
void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw);
void mtxf_align_terrain_triangle(struct Surfaces* surfaceLists, Mat4 mtx, Vec3f pos, s16 yaw, f32 radius);
void* find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c);
void vec3f_cross(Vec3f dest, Vec3f a, Vec3f b);
void vec3f_normalize(Vec3f dest);
void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32* dist, s16* pitch, s16* yaw);
void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32  dist, s16  pitch, s16  yaw);
s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec);
f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec);

#endif