#include <sm64/Area.hpp>
#include <sm64/Camera.hpp>
#include <sm64/game_init.hpp>
#include <sm64/Mario.hpp>
#include <sm64/Math.hpp>
#include <sm64/ObjectFields.hpp>
#include <sm64/Pyramid.hpp>
#include <sm64/Surface.hpp>
#include <sm64/SurfaceTerrains.hpp>
#include <sm64/Track.hpp>
#include <sm64/Types.hpp>

#include "tasfw/Script.hpp"

#include "BitFSPlatformSim.hpp"

s16 StaticSurfaceData[staticSurfaceLength][10] = {
	{-8191, -3071, 8192, 8192, -3071, -8191, -8191, -3071, -8191, SURFACE_BURNING},
	{-8191, -3071, 8192, 8192, -3071, 8192, 8192, -3071, -8191, SURFACE_BURNING}
};

s16 DynamicSurfaceData[dynamicSurfaceLength][10] = {
	{307, 307, -306, -306, 307, -306, -306, 307, 307, SURFACE_DEFAULT},
	{307, 307, -306, -306, 307, 307, 307, 307, 307, SURFACE_DEFAULT},
	{-306, 307, 307, -306, 307, -306, 0, 0, 0, SURFACE_DEFAULT},
	{0, 0, 0, 307, 307, 307, -306, 307, 307, SURFACE_DEFAULT},
	{307, 307, -306, 0, 0, 0, -306, 307, -306, SURFACE_DEFAULT},
	{0, 0, 0, 307, 307, -306, 307, 307, 307, SURFACE_DEFAULT},
	{307, 0, -306, -306, 205, -306, 307, 205, -306, SURFACE_DEFAULT},
	{307, 0, -306, -306, 0, -306, -306, 205, -306, SURFACE_DEFAULT},
	{307, 0, -306, 307, 205, 307, 307, 0, 307, SURFACE_DEFAULT},
	{307, 0, -306, 307, 205, -306, 307, 205, 307, SURFACE_DEFAULT},
	{307, 205, -306, -306, 205, -306, -306, 205, 307, SURFACE_DEFAULT},
	{-306, 0, 307, -306, 205, 307, -306, 205, -306, SURFACE_DEFAULT},
	{-306, 0, 307, -306, 205, -306, -306, 0, -306, SURFACE_DEFAULT},
	{307, 205, -306, -306, 205, 307, 307, 205, 307, SURFACE_DEFAULT},
	{307, 205, 307, -306, 0, 307, 307, 0, 307, SURFACE_DEFAULT},
	{307, 205, 307, -306, 205, 307, -306, 0, 307, SURFACE_DEFAULT},
};

void BitFSPlatformSim::loadStaticSurfaces() {
	surfaceLists.staticFloors->next = NULL;
	surfaceLists.staticWalls->next = NULL;
	surfaceLists.staticCeilings->next = NULL;

	for (int i = 0; i < staticSurfaceLength; i++) {
		if (read_surface_data(&(StaticSurfaceData[i][0]), &(sSurfacePool[i]), NULL)) {
			add_surface(FALSE, &(sSurfacePool[i]), &(sSurfaceNodePool[6 + i]), &surfaceLists);
		}
	}
}

void BitFSPlatformSim::loadDynamicSurfaces() {
	surfaceLists.dynamicFloors->next = NULL;
	surfaceLists.dynamicWalls->next = NULL;
	surfaceLists.dynamicCeilings->next = NULL;

	for (int i = 0; i < dynamicSurfaceLength; i++) {
		struct Object* object;

		if (i >= pyramidSurfaceStart && i < (pyramidSurfaceStart + pyramidSurfaceLength)) {
			object = pyramidPlatform;
		}
		else if (i >= trackSurfaceStart && i < (trackSurfaceStart + trackSurfaceLength)) {
			if (!includeTrackPlatform) continue;

			object = trackPlatform;
		}

		if (read_surface_data(&(DynamicSurfaceData[i][0]), &(sSurfacePool[staticSurfaceLength + i]), object)) {
			add_surface(TRUE, &(sSurfacePool[staticSurfaceLength + i]), &(sSurfaceNodePool[6 + staticSurfaceLength + i]), &surfaceLists);
		}
	}
}

BitFSPlatformSim::BitFSPlatformSim(const BitFSPlatConfig& config) : config(config), dll(config.dllPath), includeTrackPlatform(config.includeTrackPlatform), startFrame(config.startFrame)
{
	gPlayer1Controller = &gControllers[0];
	gPlayer1Controller->controllerData = &gControllerPads[0];
	gMarioState = &gMarioStates[0];
	cameraData.sMarioCamState = &(cameraData.gPlayerCameraState[0]);
	surfaceLists.staticFloors = &sSurfaceNodePool[0];
	surfaceLists.dynamicFloors = &sSurfaceNodePool[1];
	surfaceLists.staticWalls = &sSurfaceNodePool[2];
	surfaceLists.dynamicWalls = &sSurfaceNodePool[3];
	surfaceLists.staticCeilings = &sSurfaceNodePool[4];
	surfaceLists.dynamicCeilings = &sSurfaceNodePool[5];

	gMarioObject = &(gObjectPool[0]);
	pyramidPlatform = &(gObjectPool[pyramidPlatformIdx]);
	trackPlatform = &(gObjectPool[trackPlatformIdx]);

	cameraData.gCamera = &camera;

	areaData.gCurrLevelNum = LEVEL_BITFS;

	gGlobalTimer = 1;
	gAreaUpdateCounter = 0;

	loadStaticSurfaces();
	
	slotManager._saveMemLimit = int64_t(8000) * 1024 * 1024; //8 GB

	// constructor of SharedLib will throw if it can't load
	void* processID = dll.get("sm64_init");

	// Macro evalutes to nothing on Linux and __stdcall on Windows
	// looks cleaner
	using pICFUNC = int(TAS_FW_STDCALL*)();

	pICFUNC sm64_init = pICFUNC(processID);

	sm64_init();

	M64 m64 = M64(std::filesystem::path(config.m64Path));
	m64.load();

	processID = dll.get("sm64_update");

	pICFUNC sm64_update;
	sm64_update = pICFUNC(processID);

	OSContPad* pad = (OSContPad*)dll.get("gControllerPads");

	for (int i = 0; i < startFrame; i++) {
		Inputs inputs = m64.frames[i];
		pad->button = inputs.buttons;
		pad->stick_x = inputs.stick_x;
		pad->stick_y = inputs.stick_y;

		sm64_update();
	}

	loadVariables();
}

void BitFSPlatformSim::save(StateBitFS& state) const
{
	state.pyramidPlatform = *pyramidPlatform;
	state.trackPlatform = *trackPlatform;
	state.gMarioState = *gMarioState;
	state.gMarioObject = *gMarioObject;
	state.camera = camera;
	state.gLakituState = cameraData.gLakituState;
	state.sMarioCamState = *cameraData.sMarioCamState;
	state.sModeTransition = cameraData.sModeTransition;
	state.sMarioGeometry = cameraData.sMarioGeometry;
	state.sOldPosition[0] = cameraData.sOldPosition[0];
	state.sOldPosition[1] = cameraData.sOldPosition[1];
	state.sOldPosition[2] = cameraData.sOldPosition[2];
	state.sOldFocus[0] = cameraData.sOldFocus[0];
	state.sOldFocus[1] = cameraData.sOldFocus[1];
	state.sOldFocus[2] = cameraData.sOldFocus[2];
	state.sAvoidYawVel = cameraData.sAvoidYawVel;
	state.sSelectionFlags = cameraData.sSelectionFlags;
	state.gCameraMovementFlags = cameraData.gCameraMovementFlags;
	state.sStatusFlags = cameraData.sStatusFlags;
	state.sLakituDist = cameraData.sLakituDist;
	state.sLakituPitch = cameraData.sLakituPitch;
	state.sZoomAmount = cameraData.sZoomAmount;
	state.sCSideButtonYaw = cameraData.sCSideButtonYaw;
	state.sCUpCameraPitch = cameraData.sCUpCameraPitch;
	state.sModeOffsetYaw = cameraData.sModeOffsetYaw;
	state.s8DirModeYawOffset = cameraData.s8DirModeYawOffset;
	state.sPanDistance = cameraData.sPanDistance;
	state.sModeInfo = cameraData.sModeInfo;
	state.sCameraStoreCUp = cameraData.sCameraStoreCUp;
	state.sYawSpeed = cameraData.sYawSpeed;
	state.gCameraZoomDist = cameraData.gCameraZoomDist;
	state.gAreaUpdateCounter = gAreaUpdateCounter;
	state.gGlobalTimer = gGlobalTimer;
}

void BitFSPlatformSim::load(const StateBitFS& state)
{
	*pyramidPlatform = state.pyramidPlatform;
	*trackPlatform = state.trackPlatform;
	*gMarioState = state.gMarioState;
	*gMarioObject = state.gMarioObject;
	camera = state.camera;
	cameraData.gLakituState = state.gLakituState;
	*cameraData.sMarioCamState = state.sMarioCamState;
	cameraData.sModeTransition = state.sModeTransition;
	cameraData.sMarioGeometry = state.sMarioGeometry;
	cameraData.sOldPosition[0] = state.sOldPosition[0];
	cameraData.sOldPosition[1] = state.sOldPosition[1];
	cameraData.sOldPosition[2] = state.sOldPosition[2];
	cameraData.sOldFocus[0] = state.sOldFocus[0];
	cameraData.sOldFocus[1] = state.sOldFocus[1];
	cameraData.sOldFocus[2] = state.sOldFocus[2];
	cameraData.sAvoidYawVel = state.sAvoidYawVel;
	cameraData.sSelectionFlags = state.sSelectionFlags;
	cameraData.gCameraMovementFlags = state.gCameraMovementFlags;
	cameraData.sStatusFlags = state.sStatusFlags;
	cameraData.sLakituDist = state.sLakituDist;
	cameraData.sLakituPitch = state.sLakituPitch;
	cameraData.sZoomAmount = state.sZoomAmount;
	cameraData.sCSideButtonYaw = state.sCSideButtonYaw;
	cameraData.sCUpCameraPitch = state.sCUpCameraPitch;
	cameraData.sModeOffsetYaw = state.sModeOffsetYaw;
	cameraData.s8DirModeYawOffset = state.s8DirModeYawOffset;
	cameraData.sPanDistance = state.sPanDistance;
	cameraData.sModeInfo = state.sModeInfo;
	cameraData.sCameraStoreCUp = state.sCameraStoreCUp;
	cameraData.sYawSpeed = state.sYawSpeed;
	cameraData.gCameraZoomDist = state.gCameraZoomDist;
	gAreaUpdateCounter = state.gAreaUpdateCounter;
	gGlobalTimer = state.gGlobalTimer;
}

void BitFSPlatformSim::advance()
{
	if (gGlobalTimer < startFrame) {
		//Do nothing until you reach the starting frame
	}
	else {
		read_controller_inputs(gControllers);
		gAreaUpdateCounter++;
		bhv_tilting_inverted_pyramid_loop(pyramidPlatform, gMarioState);
		if (includeTrackPlatform) bhv_platform_on_track_update(trackPlatform, gMarioState);
		loadDynamicSurfaces();
		bhv_mario_update(gMarioState, &cameraData, &surfaceLists);
		geo_set_animation_globals(&(gMarioObject->header.gfx.animInfo), TRUE, gAreaUpdateCounter);
		update_camera(areaData.gCurrentArea->camera, &cameraData, gMarioState, &areaData, &surfaceLists, gPlayer1Controller);
		gPlayer1Controller->controllerData->button = 0x0;
		gPlayer1Controller->controllerData->stick_x = 0;
		gPlayer1Controller->controllerData->stick_y = 0;
	}

	gGlobalTimer++;
}

void* BitFSPlatformSim::addr(const char* symbol) const
{
	if (strcmp(symbol, "gControllerPads") == 0) {
		return (void*)(&gControllerPads);
	}
	else if (strcmp(symbol, "gMarioState") == 0) {
		return (void*)(&gMarioState);
	}
	else if (strcmp(symbol, "gMarioStates") == 0) {
		return (void*)(&gMarioStates);
	}
	else if (strcmp(symbol, "gMarioObject") == 0) {
		return (void*)(&gMarioObject);
	}
	else if (strcmp(symbol, "gCamera") == 0) {
		return (void*)(&(cameraData.gCamera));
	}
	else if (strcmp(symbol, "gGlobalTimer") == 0) {
		return (void*)(&gGlobalTimer);
	}
	else if (strcmp(symbol, "gObjectPool") == 0) {
		return (void*)(&gObjectPool);
	}
	else if (strcmp(symbol, "gCurrAreaIndex") == 0) {
		return (void*)(&(areaData.gCurrAreaIndex));
	}
	else if (strcmp(symbol, "gCurrCourseNum") == 0) {
		return (void*)(&(areaData.gCurrCourseNum));
	}
	else if (strcmp(symbol, "gCurrLevelNum") == 0) {
		return (void*)(&(areaData.gCurrLevelNum));
	}
	else if (strcmp(symbol, "bhvLllTiltingInvertedPyramid") == 0 || strcmp(symbol, "bhvBitfsTiltingInvertedPyramid") == 0) {
		return (void*)(pyramidPlatform->behavior);
	}
	else {
		return nullptr;
	}
}

std::size_t BitFSPlatformSim::getStateSize(const StateBitFS& state) const
{
	return sizeof(state);
}

uint32_t BitFSPlatformSim::getCurrentFrame() const
{
	return *(uint32_t*)(addr("gGlobalTimer")) - 1;
}

void BitFSPlatformSim::loadVariables()
{
	struct Object* objectPool = (Object*)dll.get("gObjectPool");
	*pyramidPlatform = objectPool[pyramidPlatformIdx];
	*trackPlatform = objectPool[trackPlatformIdx];

	areaData.gCurrAreaIndex = *((s16*)dll.get("gCurrAreaIndex"));
	struct Area* area = (Area*)dll.get("gAreaData");
	areaData.gAreaData[areaData.gCurrAreaIndex] = area[areaData.gCurrAreaIndex];
	areaData.gCurrentArea = &(areaData.gAreaData[areaData.gCurrAreaIndex]);

	camera = *(areaData.gCurrentArea->camera);

	areaData.gCurrentArea->camera = &camera;

	*gMarioObject = **((Object**)dll.get("gMarioObject"));

	if (gMarioObject->platform == &(objectPool[pyramidPlatformIdx])) {
		gMarioObject->platform = pyramidPlatform;
	}
	else if (gMarioObject->platform == &(objectPool[trackPlatformIdx])) {
		gMarioObject->platform = trackPlatform;
	}
	else {
		gMarioObject->platform = NULL;
	}

	*gMarioState = **((MarioState**)dll.get("gMarioState"));
	gMarioState->area = areaData.gCurrentArea;
	gMarioState->controller = gPlayer1Controller;
	gMarioState->marioObj = gMarioObject;
	gMarioState->statusForCamera = cameraData.sMarioCamState;
	gMarioState->marioBodyState = NULL;
	gMarioState->spawnInfo = NULL;
	s16 animIdx = gMarioState->marioObj->header.gfx.animInfo.animID;
	gMarioState->animation = &gMarioAnimsBuf;
	gMarioState->animation->targetAnim = &(animList[animIdx]);

	cameraData.gLakituState = *((LakituState*)dll.get("gLakituState"));
	*cameraData.sMarioCamState = **((PlayerCameraState**)dll.get("sMarioCamState"));
	cameraData.sModeTransition = *((TransitionInfo*)dll.get("sModeTransition"));
	cameraData.sMarioGeometry = *((PlayerGeometry*)dll.get("sMarioGeometry"));
	f32* sop = (f32*)dll.get("sOldPosition");
	cameraData.sOldPosition[0] = sop[0];
	cameraData.sOldPosition[1] = sop[1];
	cameraData.sOldPosition[2] = sop[2];
	f32* sof = (f32*)dll.get("sOldFocus");
	cameraData.sOldFocus[0] = sof[0];
	cameraData.sOldFocus[1] = sof[1];
	cameraData.sOldFocus[2] = sof[2];
	cameraData.sAvoidYawVel = *((s16*)dll.get("sAvoidYawVel"));
	cameraData.sSelectionFlags = *((s16*)dll.get("sSelectionFlags"));
	cameraData.gCameraMovementFlags = *((s16*)dll.get("gCameraMovementFlags"));
	cameraData.sStatusFlags = *((s16*)dll.get("sStatusFlags"));
	cameraData.sLakituDist = *((s16*)dll.get("sLakituDist"));
	cameraData.sLakituPitch = *((s16*)dll.get("sLakituPitch"));
	cameraData.sZoomAmount = *((f32*)dll.get("sZoomAmount"));
	cameraData.sCSideButtonYaw = *((s16*)dll.get("sCSideButtonYaw"));
	cameraData.sCUpCameraPitch = *((s16*)dll.get("sCUpCameraPitch"));
	cameraData.sModeOffsetYaw = *((s16*)dll.get("sModeOffsetYaw"));
	cameraData.s8DirModeYawOffset = *((s16*)dll.get("s8DirModeYawOffset"));
	cameraData.sPanDistance = *((f32*)dll.get("sPanDistance"));
	cameraData.sModeInfo = *((ModeTransitionInfo*)dll.get("sModeInfo"));
	cameraData.sCameraStoreCUp = *((CameraStoredInfo*)dll.get("sCameraStoreCUp"));
	cameraData.sYawSpeed = *((s16*)dll.get("sYawSpeed"));
	areaData.gCurrAreaIndex = *((s16*)dll.get("gCurrAreaIndex"));
	areaData.gCurrCourseNum = *((s16*)dll.get("gCurrCourseNum"));
	areaData.gCurrLevelNum = *((s16*)dll.get("gCurrLevelNum"));
	gAreaUpdateCounter = *((u16*)dll.get("gAreaUpdateCounter"));
}