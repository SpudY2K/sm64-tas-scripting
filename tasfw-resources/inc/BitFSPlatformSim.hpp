#pragma once
#include <sm64/Types.hpp>
#include <sm64/Surface.hpp>
#include <sm64/Camera.hpp>
#include "tasfw/Resource.hpp"
#include <tasfw/Inputs.hpp>

#ifndef BITFS_SIM_H
#define BITFS_SIM_H

#define OBJECT_POOL_CAPACITY        240

#define staticSurfaceLength         2
#define pyramidSurfaceStart         0
#define pyramidSurfaceLength        6
#define trackSurfaceStart           pyramidSurfaceLength
#define trackSurfaceLength          10
#define dynamicSurfaceLength        (pyramidSurfaceLength + trackSurfaceLength)

class BitFSPlatConfig
{
public:
	std::filesystem::path dllPath;
	CountryCode countryCode;
	bool includeTrackPlatform;
	int startFrame;
	std::string m64Path;
};

class StateBitFS
{
public:
	struct Object pyramidPlatform;
	struct Object trackPlatform;
	struct MarioState gMarioState;
	struct Object gMarioObject;
	struct Camera camera;
	struct LakituState gLakituState;
	struct PlayerCameraState sMarioCamState;
	struct TransitionInfo sModeTransition;
	struct PlayerGeometry sMarioGeometry;
	Vec3f sOldPosition;
	Vec3f sOldFocus;
	s16 sAvoidYawVel;
	s16 sSelectionFlags;
	s16 gCameraMovementFlags;
	s16 sStatusFlags;
	s16 sLakituDist;
	s16 sLakituPitch;
	f32 sZoomAmount;
	s16 sCSideButtonYaw;
	s16 sCUpCameraPitch;
	s16 sModeOffsetYaw;
	s16 s8DirModeYawOffset;
	f32 sPanDistance;
	struct ModeTransitionInfo sModeInfo;
	struct CameraStoredInfo sCameraStoreCUp;
	s16 sYawSpeed;
	f32 gCameraZoomDist;
	u16 gAreaUpdateCounter;
	u32 gGlobalTimer;
};

class BitFSPlatformSim : public Resource<StateBitFS>
{
public:
	const int pyramidPlatformIdx = 84;
	const int trackPlatformIdx = 85;
	const int bullyIdx = 27;

	struct SurfaceNode sSurfaceNodePool[staticSurfaceLength + dynamicSurfaceLength + 6];
	struct Surface sSurfacePool[staticSurfaceLength + dynamicSurfaceLength];

	struct Surfaces surfaceLists;

	struct MarioAnimation gMarioAnimsBuf;

	struct Object gObjectPool[OBJECT_POOL_CAPACITY];

	struct Object* pyramidPlatform;
	struct Object* trackPlatform;

	struct Camera camera;

	struct MarioState gMarioStates[2];
	struct MarioState* gMarioState;
	struct Object* gMarioObject;

	struct CameraData cameraData;
	struct AreaData areaData;

	struct Controller gControllers[3];
	OSContPad gControllerPads[4];
	struct Controller* gPlayer1Controller;
	struct Controller* gPlayer2Controller;
	struct Controller* gPlayer3Controller;

	u16 gAreaUpdateCounter;

	u32 gGlobalTimer;

	SharedLib dll;
	std::vector<SegVal> segment;
	const BitFSPlatConfig config;
	bool includeTrackPlatform;
	int startFrame;

	BitFSPlatformSim(const BitFSPlatConfig& config);
	void loadStaticSurfaces();
	void loadDynamicSurfaces();
	void save(StateBitFS& state) const;
	void load(const StateBitFS& state);
	void advance();
	void* addr(const char* symbol) const;
	std::size_t getStateSize(const StateBitFS& state) const;
	uint32_t getCurrentFrame() const;
	void loadVariables();
};

#endif