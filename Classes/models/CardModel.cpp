#include "models/CardModel.h"
#include <cstdio>

USING_NS_CC;

CardModel* CardModel::create(int cardId, Suit suit, Rank rank, bool faceUp)
{
    auto card = new CardModel();
    card->_cardId = cardId;
    card->_suit = suit;
    card->_rank = rank;
    card->_faceUp = faceUp;
    card->autorelease();
    return card;
}

int CardModel::getCardId() const
{
    return _cardId;
}

CardModel::Suit CardModel::getSuit() const
{
    return _suit;
}

CardModel::Rank CardModel::getRank() const
{
    return _rank;
}

bool CardModel::isFaceUp() const
{
    return _faceUp;
}

void CardModel::setFaceUp(bool value)
{
    _faceUp = value;
}

std::string CardModel::serialize() const
{
    return StringUtils::format("%d,%d,%d,%d", _cardId, static_cast<int>(_suit),
                              static_cast<int>(_rank), _faceUp ? 1 : 0);
}

CardModel* CardModel::deserialize(const std::string& data)
{
    int cardId = 0;
    int suit = 0;
    int rank = 0;
    int faceUp = 0;
    if (sscanf(data.c_str(), "%d,%d,%d,%d", &cardId, &suit, &rank, &faceUp) != 4) {
        return nullptr;
    }

    return CardModel::create(cardId, static_cast<Suit>(suit),
                             static_cast<Rank>(rank), faceUp != 0);
}
