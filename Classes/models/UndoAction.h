/**
 * UndoAction - Records a reversible card move.
 */
#ifndef UNDOACTION_H
#define UNDOACTION_H

#include "cocos2d.h"

struct UndoAction {
    int cardId = 0;
    int fromDeckId = -1;
    int toDeckId = -1;
    int fromIndex = -1;
    int toIndex = -1;
    cocos2d::Vec2 fromPosition = cocos2d::Vec2::ZERO;
    cocos2d::Vec2 toPosition = cocos2d::Vec2::ZERO;
};

#endif
