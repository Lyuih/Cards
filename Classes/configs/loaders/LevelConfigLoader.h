/**
 * LevelConfigLoader - Loads level config from json file.
 */

#ifndef LEVELCONFIGLOADER_H
#define LEVELCONFIGLOADER_H

#include <string>
#include "configs/models/LevelConfig.h"

class LevelConfigLoader {
public:
	/** Load level config by level id. Returns true on success. */
	static bool loadLevelConfig(int levelId, LevelConfig& outConfig);

	/** Load level config by explicit path. Returns true on success. */
	static bool loadLevelConfigFromPath(const std::string& path, LevelConfig& outConfig);
};

#endif