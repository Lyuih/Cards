#include "models/UndoModel.h"

void UndoModel::reset()
{
    _undoStack.clear();
    _redoStack.clear();
}

void UndoModel::push(const UndoAction& action)
{
    _undoStack.push_back(action);
    _redoStack.clear();
}

bool UndoModel::popUndo(UndoAction& outAction)
{
    if (_undoStack.empty()) {
        return false;
    }
    outAction = _undoStack.back();
    _undoStack.pop_back();
    return true;
}

void UndoModel::pushRedo(const UndoAction& action)
{
    _redoStack.push_back(action);
}

bool UndoModel::popRedo(UndoAction& outAction)
{
    if (_redoStack.empty()) {
        return false;
    }
    outAction = _redoStack.back();
    _redoStack.pop_back();
    return true;
}

bool UndoModel::canUndo() const
{
    return !_undoStack.empty();
}

bool UndoModel::canRedo() const
{
    return !_redoStack.empty();
}
