/**
 * GameModel - 整个游戏盘的运行时数据。
 * 包含多个 CardDeckModel，例如：发牌区、操作区、完成区等。
 */

#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <vector>
#include "cocos2d.h"
#include "models/CardDeckModel.h"

class GameModel : public cocos2d::Ref
{
public:
    static GameModel *create();

    ~GameModel();

    /** Add a deck to the model. */
    void addDeck(CardDeckModel* deck);

    /** Get all decks. */
    const std::vector<CardDeckModel *> &getDecks() const;

    /** Find deck by id. */
    CardDeckModel *getDeckById(int deckId) const;

    // Game state
    bool isGameWon() const;
    void setGameWon(bool val);

    // Serialization
    std::string serialize() const;
    static GameModel *deserialize(const std::string &data);

private:
    std::vector<CardDeckModel *> _decks;
    bool _gameWon;
};
#endif