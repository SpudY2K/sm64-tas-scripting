#include <tasfw/Script.hpp>
#include <chrono>

bool Script::checkPreconditions()
{
	bool validated = false;

	auto start = std::chrono::high_resolution_clock::now();
	try
	{
		validated = validation();
	}
	catch (std::exception& e)
	{
		BaseStatus[_adhocLevel].validationThrew = true;
	}
	auto finish = std::chrono::high_resolution_clock::now();

	BaseStatus[_adhocLevel].validationDuration =
		std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
			.count();

	// Revert state regardless of validation results
	Restore(_initialFrame);

	BaseStatus[_adhocLevel].validated = validated;
	return validated;
}

bool Script::execute()
{
	bool executed = false;

	auto start = std::chrono::high_resolution_clock::now();
	try
	{
		executed = execution();
	}
	catch (std::exception& e)
	{
		BaseStatus[_adhocLevel].executionThrew = true;
	}
	auto finish = std::chrono::high_resolution_clock::now();

	BaseStatus[_adhocLevel].executionDuration =
		std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
			.count();

	// Revert state if there are any execution errors
	if (!executed)
		Restore(_initialFrame);

	BaseStatus[_adhocLevel].executed = executed;
	return executed;
}

bool Script::checkPostconditions()
{
	bool asserted = false;

	auto start = std::chrono::high_resolution_clock::now();
	try
	{
		asserted = assertion();
	}
	catch (std::exception& e)
	{
		BaseStatus[_adhocLevel].assertionThrew = true;

		// Revert state only if assertion throws exception
		Restore(_initialFrame);
	}
	auto finish = std::chrono::high_resolution_clock::now();

	BaseStatus[_adhocLevel].assertionDuration =
		std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
			.count();

	BaseStatus[_adhocLevel].asserted = asserted;
	return asserted;
}

void Script::CopyVec3f(Vec3f dest, Vec3f source)
{
	dest[0] = source[0];
	dest[1] = source[1];
	dest[2] = source[2];
}

uint64_t Script::GetCurrentFrame()
{
	return game->getCurrentFrame();
}

void Script::AdvanceFrameRead()
{
	SetInputs(GetInputsMetadataAndCache(GetCurrentFrame()).inputs);
	game->advance_frame();
	BaseStatus[_adhocLevel].nFrameAdvances++;
}

/*
void Script::AdvanceFrameRead(uint64_t& counter)
{
	SetInputs(GetInputsTracked(GetCurrentFrame(), counter));
	game->advance_frame();
	BaseStatus[_adhocLevel].nFrameAdvances++;
}
*/

void Script::AdvanceFrameWrite(Inputs inputs)
{
	// Save inputs to diff
	uint64_t currentFrame = GetCurrentFrame();
	BaseStatus[_adhocLevel].m64Diff.frames[currentFrame] = inputs;

	// Erase all saves, cached saves, and frame counters after this point, as well as the cached input on this frame
	inputsCache[_adhocLevel].erase(currentFrame);
	frameCounter[_adhocLevel].erase(frameCounter[_adhocLevel].upper_bound(currentFrame), frameCounter[_adhocLevel].end());
	saveBank[_adhocLevel].erase(saveBank[_adhocLevel].upper_bound(currentFrame), saveBank[_adhocLevel].end());
	saveCache[_adhocLevel].erase(saveCache[_adhocLevel].upper_bound(currentFrame), saveCache[_adhocLevel].end());

	// Set inputs and advance frame
	SetInputs(inputs);
	game->advance_frame();
	BaseStatus[_adhocLevel].nFrameAdvances++;
}

void Script::Apply(const M64Diff& m64Diff)
{
	if (m64Diff.frames.empty())
		return;

	uint64_t firstFrame = m64Diff.frames.begin()->first;
	uint64_t lastFrame = m64Diff.frames.rbegin()->first;

	Load(firstFrame);

	// Erase all saves, cached saves, and frame counters after this point
	uint64_t currentFrame = GetCurrentFrame();
	frameCounter[_adhocLevel].erase(frameCounter[_adhocLevel].upper_bound(currentFrame), frameCounter[_adhocLevel].end());
	saveBank[_adhocLevel].erase(saveBank[_adhocLevel].upper_bound(currentFrame), saveBank[_adhocLevel].end());
	saveCache[_adhocLevel].erase(saveCache[_adhocLevel].upper_bound(currentFrame), saveCache[_adhocLevel].end());

	while (currentFrame <= lastFrame)
	{
		// Use default inputs if diff doesn't override them
		auto inputs = GetInputs(currentFrame);
		if (m64Diff.frames.contains(currentFrame))
		{
			inputs = m64Diff.frames.at(currentFrame);
			BaseStatus[_adhocLevel].m64Diff.frames[currentFrame] = inputs;
			inputsCache[_adhocLevel].erase(currentFrame);
		}

		SetInputs(inputs);
		game->advance_frame();
		BaseStatus[_adhocLevel].nFrameAdvances++;

		currentFrame = GetCurrentFrame();
	}
}
void Script::ApplyChildDiff(const BaseScriptStatus& status, int64_t initialFrame)
{
	uint64_t firstFrame = status.m64Diff.frames.begin()->first;
	uint64_t lastFrame = status.m64Diff.frames.rbegin()->first;

	// Erase all saves, cached saves, and frame counters after this point
	frameCounter[_adhocLevel].erase(frameCounter[_adhocLevel].upper_bound(firstFrame), frameCounter[_adhocLevel].end());
	saveBank[_adhocLevel].erase(saveBank[_adhocLevel].upper_bound(firstFrame), saveBank[_adhocLevel].end());
	saveCache[_adhocLevel].erase(saveCache[_adhocLevel].upper_bound(firstFrame), saveCache[_adhocLevel].end());

	//Apply diff. State is already synced from child script, so no need to update it
	int64_t frame = firstFrame;
	while (frame <= lastFrame)
	{
		if (status.m64Diff.frames.count(frame))
		{
			BaseStatus[_adhocLevel].m64Diff.frames[frame] = status.m64Diff.frames.at(frame);
			inputsCache[_adhocLevel].erase(frame);
		}

		frame++;
	}

	//Forward state to end of diff
	Load(lastFrame + 1);
}

/*
Inputs Script::GetInputs(int64_t frame)
{
	//Check ad-hoc script hierarchy first, then current script
	for (int64_t adhocLevel = _adhocLevel; adhocLevel >= 0; adhocLevel--)
	{
		if (BaseStatus[adhocLevel].m64Diff.frames.contains(frame))
			return BaseStatus[adhocLevel].m64Diff.frames[frame];
	}

	//Then check parent script
	if (_parentScript)
		return _parentScript->GetInputs(frame);

	//This should be impossible
	return Inputs(0, 0, 0);
}

Inputs TopLevelScript::GetInputs(int64_t frame)
{
	//Check ad-hoc script hierarchy first, then current script
	for (int64_t adhocLevel = _adhocLevel; adhocLevel >= 0; adhocLevel--)
	{
		if (BaseStatus[adhocLevel].m64Diff.frames.contains(frame))
			return BaseStatus[adhocLevel].m64Diff.frames[frame];
	}

	//Then check actual m64
	if (_m64.frames.count(frame))
		return _m64.frames[frame];

	//Default to no input
	return Inputs(0, 0, 0);
}
*/

Inputs Script::GetInputs(int64_t frame)
{
	return GetInputsMetadataAndCache(frame).inputs;
}

InputsMetadata Script::GetInputsMetadata(int64_t frame)
{
	//Check ad-hoc script hierarchy first, then current script
	for (int64_t adhocLevel = _adhocLevel; adhocLevel >= 0; adhocLevel--)
	{
		if (BaseStatus[adhocLevel].m64Diff.frames.contains(frame))
			return InputsMetadata(BaseStatus[adhocLevel].m64Diff.frames[frame], this, frame, adhocLevel);

		if (inputsCache[adhocLevel].contains(frame))
			return inputsCache[adhocLevel][frame];
	}

	//Then check parent script
	if (_parentScript)
		return _parentScript->GetInputsMetadata(frame);

	//This should be impossible
	std::runtime_error("Failed to get inputs, possible error in recursion logic.");
	return InputsMetadata();
}

InputsMetadata TopLevelScript::GetInputsMetadata(int64_t frame)
{
	//Check ad-hoc script hierarchy first, then current script
	for (int64_t adhocLevel = _adhocLevel; adhocLevel >= 0; adhocLevel--)
	{
		if (BaseStatus[adhocLevel].m64Diff.frames.contains(frame))
			return InputsMetadata(BaseStatus[adhocLevel].m64Diff.frames[frame], this, frame, adhocLevel);

		if (inputsCache[adhocLevel].contains(frame))
			return inputsCache[adhocLevel][frame];
	}

	//Then check actual m64.
	//For the purposes of the frame counter, mark as adhoc level 0.
	if (_m64.frames.count(frame))
		return InputsMetadata(_m64.frames[frame], this, frame, 0, InputsMetadata::InputsSource::ORIGINAL);

	//Default to no input
	//For the purposes of the frame counter, mark as adhoc level 0.
	return InputsMetadata(Inputs(0, 0, 0), this, frame, 0, InputsMetadata::InputsSource::DEFAULT);
}

InputsMetadata Script::GetInputsMetadataAndCache(int64_t frame)
{
	InputsMetadata inputs = GetInputsMetadata(frame);
	inputsCache[_adhocLevel][frame] = inputs;
	return inputs;
}

/*
// Seeks inputs from script hierarchy diffs recursively.
// If a nonzero counter is provided, save if performant.
// Return the counter, incremented by the frame counter for the frame with the inputs.
Inputs Script::GetInputsTracked(uint64_t frame, uint64_t& counter)
{
	//Check ad-hoc script hierarchy first, then current script
	for (int64_t adhocLevel = _adhocLevel; adhocLevel >= 0; adhocLevel--)
	{
		if (BaseStatus[adhocLevel].m64Diff.frames.contains(frame))
		{
			if (counter != 0 && game->shouldSave(counter + frameCounter[adhocLevel][frame]))
			{
				Save();
				counter = 0;
			}
			else
				counter += frameCounter[adhocLevel][frame]++;

			return BaseStatus[adhocLevel].m64Diff.frames[frame];
		}	
	}

	//Then check parent
	if (_parentScript)
		return _parentScript->GetInputsTracked(frame, counter);

	//This should never happen
	return Inputs(0, 0, 0);
}

// Seeks inputs from the top level script or base m64.
// If a nonzero counter is provided, save if performant.
// Returns the inputs, and the counter incremented by the frame counter for the frame with the inputs.
Inputs TopLevelScript::GetInputsTracked(uint64_t frame, uint64_t& counter)
{
	//Check ad-hoc script hierarchy first, then current script
	for (int64_t adhocLevel = _adhocLevel; adhocLevel >= 0; adhocLevel--)
	{
		if (BaseStatus[adhocLevel].m64Diff.frames.contains(frame))
		{
			if (counter != 0 && game->shouldSave(counter + frameCounter[adhocLevel][frame]))
			{
				Save();
				counter = 0;
			}
			else
				counter += frameCounter[adhocLevel][frame]++;

			return BaseStatus[adhocLevel].m64Diff.frames[frame];
		}	
	}

	//Then check actual m64. M64 inputs and default inputs should contribute to the root frame counter
	if (counter != 0 && game->shouldSave(counter + frameCounter[0][frame]))
	{
		Save();
		counter = 0;
	}
	else
		counter += frameCounter[0][frame]++;

	if (_m64.frames.count(frame))
		return _m64.frames[frame];

	return Inputs(0, 0, 0);
}
*/

uint64_t Script::GetFrameCounter(InputsMetadata cachedInputs)
{
	if (!cachedInputs.script->frameCounter[cachedInputs.adhocLevel].contains(cachedInputs.frame))
		cachedInputs.script->frameCounter[cachedInputs.adhocLevel][cachedInputs.frame] = 0;

	return cachedInputs.script->frameCounter[cachedInputs.adhocLevel][cachedInputs.frame];
}

uint64_t Script::IncrementFrameCounter(InputsMetadata cachedInputs)
{
	if (!cachedInputs.script->frameCounter[cachedInputs.adhocLevel].contains(cachedInputs.frame))
		cachedInputs.script->frameCounter[cachedInputs.adhocLevel][cachedInputs.frame] = 0;

	//Return value BEFORE incrementing
	return cachedInputs.script->frameCounter[cachedInputs.adhocLevel][cachedInputs.frame]++;
}

/*
uint64_t Script::GetFrameCounter(int64_t frame)
{
	//Check ad-hoc script hierarchy first, then current script
	for (int64_t adhocLevel = _adhocLevel; adhocLevel >= 0; adhocLevel--)
	{
		if (BaseStatus[adhocLevel].m64Diff.frames.contains(frame))
			return frameCounter[adhocLevel][frame];	
	}

	//Then check parent script
	if (_parentScript)
		return _parentScript->GetFrameCounter(frame);

	//This should be impossible
	return 0;
}

uint64_t TopLevelScript::GetFrameCounter(int64_t frame)
{
	//Check ad-hoc script hierarchy first
	for (int64_t adhocLevel = _adhocLevel; adhocLevel > 0; adhocLevel--)
	{
		if (BaseStatus[adhocLevel].m64Diff.frames.contains(frame))
			return frameCounter[adhocLevel][frame];	
	}

	//Then check current script
	return frameCounter[0][frame];
}
*/

SaveMetadata Script::GetLatestSave(int64_t frame)
{
	//Check ad-hoc script hierarchy first, then current script
	int64_t earlyFrame = frame;
	SaveMetadata bestSave;
	for (int64_t adhocLevel = _adhocLevel; adhocLevel >= 0; adhocLevel--)
	{
		//Get most recent save in script

		auto save = saveBank[adhocLevel].empty() || earlyFrame < saveBank[adhocLevel].begin()->first
			? saveBank[adhocLevel].end()
			: std::prev(saveBank[adhocLevel].upper_bound(earlyFrame));

		//Select the more recent save
		if (save != saveBank[adhocLevel].end() && save->first >= bestSave.frame)
			bestSave = SaveMetadata(this, save->first, adhocLevel);

		//Check for cached save
		auto cachedSave = saveCache[adhocLevel].empty() || earlyFrame < saveCache[adhocLevel].begin()->first
			? saveCache[adhocLevel].end()
			: std::prev(saveCache[adhocLevel].upper_bound(earlyFrame));

		if (cachedSave != saveCache[adhocLevel].end())
		{
			//This is the purpose of caching saves: end recursion when a cached save is found. Boosts performance.
			if (cachedSave->second.IsValid())
			{
				if (cachedSave->first >= bestSave.frame)
					return cachedSave->second;
			}
			else
				saveCache[adhocLevel].erase(cachedSave->first); // Delete stale cached save	
		}

		// Don't search past start of m64 diff to avoid desync
		earlyFrame = !BaseStatus[adhocLevel].m64Diff.frames.empty() ?
			(std::min)(BaseStatus[adhocLevel].m64Diff.frames.begin()->first, (uint64_t)earlyFrame) : frame;

		//If save is not before the start of the diff, we have the best possible save, so return it
		if (bestSave.frame >= 0 && bestSave.frame >= earlyFrame)
			return bestSave;
	}

	//Then check parent script
	if (_parentScript)
	{
		auto ancestorSave = _parentScript->GetLatestSave(earlyFrame);

		//Select the more recent save
		if (ancestorSave.frame >= bestSave.frame)
			return ancestorSave;
	}
		
	//Return most recent save if it exists
	if (bestSave.frame >= 0)
		return bestSave;

	//Default to initial save
	return SaveMetadata(this);
}

SaveMetadata Script::GetLatestSaveAndCache(int64_t frame)
{
	SaveMetadata save = GetLatestSave(frame);
	saveCache[_adhocLevel][save.frame] = save; // Cache save to save recursion time later
	return save;
}

void Script::Load(uint64_t frame)
{
	// Load most recent save at or before frame. Check child saves before
	// parent. If target frame is in future, check if faster to frame advance or load.
	int64_t currentFrame = GetCurrentFrame();
	auto latestSave = GetLatestSaveAndCache(frame);
	if (frame < currentFrame)
	{
		game->load_state(latestSave.GetSlotHandle()->slotId);
		BaseStatus[_adhocLevel].nLoads++;
	}
	else if (latestSave.frame > currentFrame && game->shouldLoad(latestSave.frame - currentFrame))
		game->load_state(latestSave.GetSlotHandle()->slotId);

	// If save is before target frame, play back until frame is reached
	currentFrame = GetCurrentFrame();
	uint64_t frameCounter = 0;
	while (currentFrame++ < frame)
	{
		auto cachedInputs = GetInputsMetadataAndCache(frame);
		frameCounter += IncrementFrameCounter(cachedInputs);
		AdvanceFrameRead();

		//Estimate future frame advances from aggregate of historical frame advances on this input segment
		//If it reaches a certain threshold, creating a save is performant
		if (game->shouldSave(frameCounter * 1))
			saveCache[_adhocLevel][currentFrame] = cachedInputs.script->Save(_adhocLevel);
	}
}

// Load method specifically for Script.Execute() and Script.Modify(), checks for desyncs
void Script::Revert(uint64_t frame, const M64Diff& m64)
{
	// Check if script altered state
	int64_t currentFrame = GetCurrentFrame();
	bool desync =
		(!m64.frames.empty()) && (m64.frames.begin()->first < currentFrame);

	// Load most recent save at or before frame. Check child saves before
	// parent. If target frame is in future, check if faster to frame advance or load.
	auto latestSave = GetLatestSaveAndCache(frame);
	if (desync || frame < currentFrame)
	{
		game->load_state(latestSave.GetSlotHandle()->slotId);
		BaseStatus[_adhocLevel].nLoads++;
	}
	else if (latestSave.frame > frame && game->shouldLoad(latestSave.frame - currentFrame))
		game->load_state(latestSave.GetSlotHandle()->slotId);

	// If save is before target frame, play back until frame is reached
	currentFrame = GetCurrentFrame();
	uint64_t frameCounter = 0;
	while (currentFrame++ < frame)
	{
		auto cachedInputs = GetInputsMetadataAndCache(frame);
		frameCounter += IncrementFrameCounter(cachedInputs);
		AdvanceFrameRead();

		//Estimate future frame advances from aggregate of historical frame advances on this input segment
		//If it reaches a certain threshold, creating a save is performant
		if (game->shouldSave(frameCounter * 1))
			saveCache[_adhocLevel][currentFrame] = cachedInputs.script->Save(_adhocLevel);
	}
}

void Script::Rollback(uint64_t frame)
{
	// Roll back diff and savebank to target frame. Note that rollback on diff
	// includes target frame.
	BaseStatus[_adhocLevel].m64Diff.frames.erase(
		BaseStatus[_adhocLevel].m64Diff.frames.lower_bound(frame),
		BaseStatus[_adhocLevel].m64Diff.frames.end());
	inputsCache[_adhocLevel].erase(inputsCache[_adhocLevel].lower_bound(frame), inputsCache[_adhocLevel].end());
	frameCounter[_adhocLevel].erase(frameCounter[_adhocLevel].upper_bound(frame), frameCounter[_adhocLevel].end());
	saveBank[_adhocLevel].erase(saveBank[_adhocLevel].upper_bound(frame), saveBank[_adhocLevel].end());
	saveCache[_adhocLevel].erase(saveCache[_adhocLevel].upper_bound(frame), saveCache[_adhocLevel].end());

	Load(frame);
}

// Same as Rollback, but starts from current frame. Useful for scripts that edit past frames
void Script::RollForward(int64_t frame)
{
	// Roll back diff and savebank to current frame. Note that roll forward on diff
	// includes current frame.
	uint64_t currentFrame = GetCurrentFrame();
	BaseStatus[_adhocLevel].m64Diff.frames.erase(
		BaseStatus[_adhocLevel].m64Diff.frames.lower_bound(currentFrame),
		BaseStatus[_adhocLevel].m64Diff.frames.end());
	inputsCache[_adhocLevel].erase(inputsCache[_adhocLevel].lower_bound(currentFrame), inputsCache[_adhocLevel].end());
	frameCounter[_adhocLevel].erase(frameCounter[_adhocLevel].upper_bound(currentFrame), frameCounter[_adhocLevel].end());
	saveBank[_adhocLevel].erase(saveBank[_adhocLevel].upper_bound(currentFrame), saveBank[_adhocLevel].end());
	saveCache[_adhocLevel].erase(saveCache[_adhocLevel].upper_bound(currentFrame), saveCache[_adhocLevel].end());

	Load(frame);
}

// Load and clear diff and savebank
void Script::Restore(int64_t frame)
{
	// Clear diff, frame counter and savebank
	BaseStatus[_adhocLevel].m64Diff.frames.erase(
		BaseStatus[_adhocLevel].m64Diff.frames.begin(),
		BaseStatus[_adhocLevel].m64Diff.frames.end());
	inputsCache[_adhocLevel].erase(inputsCache[_adhocLevel].begin(), inputsCache[_adhocLevel].end());
	frameCounter[_adhocLevel].erase(frameCounter[_adhocLevel].begin(), frameCounter[_adhocLevel].end());
	saveBank[_adhocLevel].erase(saveBank[_adhocLevel].begin(), saveBank[_adhocLevel].end());
	saveCache[_adhocLevel].erase(saveCache[_adhocLevel].begin(), saveCache[_adhocLevel].end());

	Load(frame);
}

void Script::Save()
{
	Save(_adhocLevel);
}

//Internal version of Save() that specifies adhoc level, that can be called by a child script 
SaveMetadata Script::Save(int64_t adhocLevel)
{
	//Desyncs should always clear future saves, so if a save already exists there is no need to overwrite it
	int64_t currentFrame = GetCurrentFrame();
	if (!saveBank[adhocLevel].contains(currentFrame))
	{
		saveBank[adhocLevel].emplace(
			std::piecewise_construct,
			std::forward_as_tuple(currentFrame),
			std::forward_as_tuple(game, game->save_state(this, currentFrame, adhocLevel)));
		BaseStatus[adhocLevel].nSaves++;
	}

	//Return metadat for caching
	return SaveMetadata(this, currentFrame, adhocLevel);
}

//Do a cost-benefit analysis to decide whether a save should be created
//CBA is only for creating a save in the current script on tthe current frame
void Script::OptionalSave()
{
	//Integrate frame counter, saving only if threshold is reached
	int64_t currentFrame = GetCurrentFrame();
	int64_t latestSaveFrame = GetLatestSaveAndCache(currentFrame).frame;
	uint64_t frameCounter = 0;
	for (int64_t frame = latestSaveFrame; frame <= currentFrame; frame++)
	{
		if (game->shouldSave(frameCounter * 2))
		{
			//Create save in this script at the current frame
			Save();
			break;
		}

		//Increment AFTER save check. We want to know if a save on the NEXT frame is worthwhile based on the counter from this frame
		frameCounter += GetFrameCounter(GetInputsMetadataAndCache(frame));
	}
}

void Script::DeleteSave(int64_t frame, int64_t adhocLevel)
{
	saveBank[adhocLevel].erase(frame);
}

void Script::SetInputs(Inputs inputs)
{
	uint16_t* buttonDllAddr = (uint16_t*) game->addr("gControllerPads");
	buttonDllAddr[0] = inputs.buttons;

	int8_t* xStickDllAddr = (int8_t*) game->addr("gControllerPads") + 2;
	xStickDllAddr[0] = inputs.stick_x;

	int8_t* yStickDllAddr = (int8_t*) game->addr("gControllerPads") + 3;
	yStickDllAddr[0] = inputs.stick_y;
}

bool Script::IsDiffEmpty()
{
	return BaseStatus[_adhocLevel].m64Diff.frames.empty();
}

M64Diff Script::GetDiff()
{
	return BaseStatus[_adhocLevel].m64Diff;
}
