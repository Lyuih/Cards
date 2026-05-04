#include "managers/SaveManager.h"

SaveManager* SaveManager::create(const std::string& savePath)
{
    auto manager = new SaveManager();
    manager->_savePath = savePath;
    manager->autorelease();
    return manager;
}

void SaveManager::saveGame(const GameModel& model)
{
    (void)model;
}

GameModel* SaveManager::loadGame()
{
    return nullptr;
}
