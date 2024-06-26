#pragma once

#ifndef PYRAMID_H
#define PYRAMID_H
#include <sm64/Types.hpp>

bool simulate_platform_tilt(
	struct Object* marioObj, struct Object* pyramidPlatform, short* floorAngle,
	bool* isSlope);
void bhv_tilting_inverted_pyramid_loop(	Vec3f& platNormal, Vec3f& platPos, Vec3f& marioPos, bool onPlatform,
	Mat4& transform);
float approach_by_increment(float goal, float src, float inc);
void create_transform_from_normals(Mat4& transform, Vec3f& normal, Vec3f& pos);

void bhv_tilting_inverted_pyramid_loop(struct Object* o, struct MarioState* m);
#endif