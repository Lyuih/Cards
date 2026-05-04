/**
 * GameModelGenerator - Converts LevelConfig to GameModel.
 */
#ifndef GAMEMODELGENERATOR_H
#define GAMEMODELGENERATOR_H

#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"

class GameModelGenerator {
public:
    /** Generate a runtime game model from a level config. */
    static GameModel* generate(const LevelConfig& config);
};

#endif