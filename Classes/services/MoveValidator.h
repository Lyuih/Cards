/**
 * MoveValidator - 静态类，提供纯函数判断卡牌移动是否合法。
 */

#ifndef MOVEVALIDATOR_H
#define MOVEVALIDATOR_H

#include "configs/models/LevelConfig.h"
#include "models/GameModel.h"

class MoveValidator {
public:
    /** Check if a card can move from one deck to another. */
    static bool canMove(const CardDeckModel& fromDeck, int cardIndex,
                        const CardDeckModel& toDeck, const LevelConfig& config);

    /** Check whether game auto-complete is available. */
    static bool canAutoComplete(const GameModel& model, const LevelConfig& config);
};

#endif