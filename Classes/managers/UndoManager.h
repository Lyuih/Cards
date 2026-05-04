/**
 * UndoManager - 管理撤销/重做功能。
 * 持有 UndoModel 队列，并执行撤销时直接操作 GameModel。
 */

#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H
#include "cocos2d.h"
#include "models/UndoModel.h"
#include "models/GameModel.h"

class UndoManager : public cocos2d::Ref {
public:
    static UndoManager* create();

    ~UndoManager();

    /** Record an action for undo. */
    void recordAction(const UndoAction& action);

    /** Undo latest action and output it for animation. */
    bool undo(GameModel* model, UndoAction& outAction);

    /** Redo latest action and output it for animation. */
    bool redo(GameModel* model, UndoAction& outAction);

    /** 清除所有记录 */
    void reset();

private:
    UndoModel* _undoModel;
};

#endif