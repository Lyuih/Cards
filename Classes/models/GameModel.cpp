#include "models/GameModel.h"

GameModel* GameModel::create()
{
    auto model = new GameModel();
    model->_gameWon = false;
    model->autorelease();
    return model;
}

GameModel::~GameModel()
{
    for (auto* deck : _decks) {
        if (deck) {
            deck->release();
        }
    }
    _decks.clear();
}

void GameModel::addDeck(CardDeckModel* deck)
{
    if (deck) {
        deck->retain();
    }
    _decks.push_back(deck);
}

const std::vector<CardDeckModel*>& GameModel::getDecks() const
{
    return _decks;
}

CardDeckModel* GameModel::getDeckById(int deckId) const
{
    for (auto* deck : _decks) {
        if (deck->getDeckId() == deckId) {
            return deck;
        }
    }
    return nullptr;
}

bool GameModel::isGameWon() const
{
    return _gameWon;
}

void GameModel::setGameWon(bool val)
{
    _gameWon = val;
}

std::string GameModel::serialize() const
{
    return "";
}

GameModel* GameModel::deserialize(const std::string& data)
{
    (void)data;
    return nullptr;
}
