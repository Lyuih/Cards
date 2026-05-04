/**
 * GameController - 整个游戏流程的主控制器。
 * 启动游戏、响应菜单操作、管理所有子控制器。
 */

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "cocos2d.h"
#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"
#include "views/GameView.h"
#include "controllers/CardController.h"
#include "controllers/HUDController.h"
#include "managers/UndoManager.h"
#include "managers/SaveManager.h"

class GameController : public cocos2d::Ref {
public:
    static GameController* create();

    ~GameController();

    /** 启动指定关卡 */
    void startLevel(int levelId);

    /** 游戏结束处理 */
    void onGameWon();
    void onGameLost();

    // 提供给外界的 const 访问（View 可能需要）
    const GameModel* getGameModel() const;

    /** Get the root view. */
    GameView* getGameView() const;

private:
    // 初始化步骤
    void loadConfig(int levelId);
    void generateModel();
    void initSubControllers();
    void initView();
    void bindHUD();
    void handleUndo();

    GameModel* _gameModel;                      // 动态模型
    const LevelConfig* _levelConfig;            // 静态配置（只读）
    GameView* _gameView;                        // 主视图

    // 子控制器
    CardController* _cardController;
    HUDController* _hudController;

    // 管理器
    UndoManager* _undoManager;
    SaveManager* _saveManager;
};

#endif