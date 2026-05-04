/**
 * DeckLayoutInfo - Visual layout information for a deck view.
 */
#ifndef DECKLAYOUTINFO_H
#define DECKLAYOUTINFO_H

#include "cocos2d.h"
#include "models/CardDeckModel.h"

struct DeckLayoutInfo {
    int deckId = -1;
    CardDeckModel::DeckType deckType = CardDeckModel::DeckType::Playfield;
    cocos2d::Vec2 basePosition = cocos2d::Vec2::ZERO;
    cocos2d::Vec2 stackOffset = cocos2d::Vec2::ZERO;
    bool useFixedPositions = false;
};

#endif
