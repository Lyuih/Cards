/**
 * SaveManager - 负责将 GameModel 序列化到本地文件，以及反序列化恢复。
 * 不关心 UI，只处理 I/O 和转换。
 */
#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H
#include "cocos2d.h"
#include "models/GameModel.h"

class SaveManager : public cocos2d::Ref {
public:
    static SaveManager* create(const std::string& savePath);

    void saveGame(const GameModel& model);
    GameModel* loadGame();

private:
    std::string _savePath;
};

#endif