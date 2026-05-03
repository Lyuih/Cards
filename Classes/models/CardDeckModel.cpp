#include "models/CardDeckModel.h"

CardDeckModel* CardDeckModel::create(int deckId, DeckType type)
{
    auto deck = new CardDeckModel();
    deck->_deckId = deckId;
    deck->_type = type;
    deck->autorelease();
    return deck;
}

CardDeckModel::~CardDeckModel()
{
    for (auto* card : _cards) {
        if (card) {
            card->release();
        }
    }
    _cards.clear();
    _positions.clear();
}

int CardDeckModel::getDeckId() const
{
    return _deckId;
}

CardDeckModel::DeckType CardDeckModel::getDeckType() const
{
    return _type;
}

void CardDeckModel::addCard(CardModel* card, const cocos2d::Vec2& position)
{
    if (card) {
        card->retain();
    }
    _cards.push_back(card);
    _positions.push_back(position);
}

void CardDeckModel::insertCardAt(CardModel* card, int index, const cocos2d::Vec2& position)
{
    if (index < 0 || index > static_cast<int>(_cards.size())) {
        index = static_cast<int>(_cards.size());
    }
    if (card) {
        card->retain();
    }
    _cards.insert(_cards.begin() + index, card);
    _positions.insert(_positions.begin() + index, position);
}

CardModel* CardDeckModel::removeCardAt(int index)
{
    if (index < 0 || index >= static_cast<int>(_cards.size())) {
        return nullptr;
    }
    CardModel* card = _cards.at(index);
    _cards.erase(_cards.begin() + index);
    _positions.erase(_positions.begin() + index);
    if (card) {
        card->release();
    }
    return card;
}

int CardDeckModel::getCardCount() const
{
    return static_cast<int>(_cards.size());
}

CardModel* CardDeckModel::getCardAt(int index) const
{
    if (index < 0 || index >= static_cast<int>(_cards.size())) {
        return nullptr;
    }
    return _cards.at(index);
}

int CardDeckModel::getCardIndexById(int cardId) const
{
    for (int i = 0; i < static_cast<int>(_cards.size()); ++i) {
        if (_cards[i]->getCardId() == cardId) {
            return i;
        }
    }
    return -1;
}

cocos2d::Vec2 CardDeckModel::getPositionAt(int index) const
{
    if (index < 0 || index >= static_cast<int>(_positions.size())) {
        return cocos2d::Vec2::ZERO;
    }
    return _positions.at(index);
}

void CardDeckModel::setPositionAt(int index, const cocos2d::Vec2& position)
{
    if (index < 0 || index >= static_cast<int>(_positions.size())) {
        return;
    }
    _positions[index] = position;
}

const std::vector<CardModel*>& CardDeckModel::getCards() const
{
    return _cards;
}

const std::vector<cocos2d::Vec2>& CardDeckModel::getPositions() const
{
    return _positions;
}
