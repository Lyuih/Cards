#include "services/MoveValidator.h"
#include <cmath>

bool MoveValidator::canMove(const CardDeckModel& fromDeck, int cardIndex,
                            const CardDeckModel& toDeck, const LevelConfig& config)
{
    (void)config;

    if (cardIndex < 0 || cardIndex >= fromDeck.getCardCount()) {
        return false;
    }

    if (toDeck.getDeckType() != CardDeckModel::DeckType::Hand) {
        return false;
    }

    CardModel* movingCard = fromDeck.getCardAt(cardIndex);
    if (!movingCard) {
        return false;
    }

    if (!movingCard->isFaceUp()) {
        return false;
    }

    if (fromDeck.getDeckType() == CardDeckModel::DeckType::Stack) {
        // Only allow the top stack card to move.
        return cardIndex == fromDeck.getCardCount() - 1;
    }

    if (fromDeck.getDeckType() == CardDeckModel::DeckType::Playfield) {
        if (toDeck.getCardCount() == 0) {
            return true;
        }
        CardModel* topCard = toDeck.getCardAt(toDeck.getCardCount() - 1);
        if (!topCard) {
            return false;
        }
        int fromRank = static_cast<int>(movingCard->getRank());
        int toRank = static_cast<int>(topCard->getRank());
        return std::abs(fromRank - toRank) == 1;
    }

    return false;
}

bool MoveValidator::canAutoComplete(const GameModel& model, const LevelConfig& config)
{
    (void)model;
    (void)config;
    return false;
}
