/**
 * UndoModel - Stores undo and redo stacks.
 */
#ifndef UNDOMODEL_H
#define UNDOMODEL_H

#include <vector>
#include "models/UndoAction.h"

class UndoModel {
public:
    /** Reset history. */
    void reset();

    /** Push a new action and clear redo. */
    void push(const UndoAction& action);

    /** Pop the latest action into outAction. */
    bool popUndo(UndoAction& outAction);

    /** Push action to redo stack. */
    void pushRedo(const UndoAction& action);

    /** Pop latest redo action into outAction. */
    bool popRedo(UndoAction& outAction);

    /** Return true if there is anything to undo. */
    bool canUndo() const;

    /** Return true if there is anything to redo. */
    bool canRedo() const;

private:
    std::vector<UndoAction> _undoStack;
    std::vector<UndoAction> _redoStack;
};

#endif
