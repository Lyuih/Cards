/**
 * CardDeckModel - 运行时卡组模型，拥有有序的卡片和位置，不了解视图行为。
 * 
 */
#ifndef CARDDECKMODEL_H
#define CARDDECKMODEL_H

#include <vector>
#include "cocos2d.h"
#include "models/CardModel.h"

class CardDeckModel : public cocos2d::Ref {
public:
    enum class DeckType {
        Playfield = 0, //牌堆
        Hand = 1, //手牌区
        Stack = 2 //备用牌堆
    };

    ~CardDeckModel();

    /** Create a deck with id and type. */
    static CardDeckModel* create(int deckId, DeckType type);

    /** Get deck id. */
    int getDeckId() const;

    /** Get deck type. */
    DeckType getDeckType() const;

    /** Add a card at the end of the deck. */
    void addCard(CardModel* card, const cocos2d::Vec2& position);

    /** Insert a card at a specific index. */
    void insertCardAt(CardModel* card, int index, const cocos2d::Vec2& position);

    /** Remove and return the card at index. */
    CardModel* removeCardAt(int index);

    /** Get card count. */
    int getCardCount() const;

    /** Get card by index. */
    CardModel* getCardAt(int index) const;

    /** Find card index by id. */
    int getCardIndexById(int cardId) const;

    /** Get stored position by index. */
    cocos2d::Vec2 getPositionAt(int index) const;

    /** Set stored position by index. */
    void setPositionAt(int index, const cocos2d::Vec2& position);

    /** Get readonly cards. */
    const std::vector<CardModel*>& getCards() const;

    /** Get readonly positions. */
    const std::vector<cocos2d::Vec2>& getPositions() const;

private:
    int _deckId;
    DeckType _type;
    std::vector<CardModel*> _cards;
    std::vector<cocos2d::Vec2> _positions;
};

#endif
