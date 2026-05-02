/**
 * @author yui
 * CardModel - 存储单张卡牌的逻辑信息（花色、点数、是否正面朝上等）。
 * 不关心任何 UI 表现。
 */

#ifndef CARDMODEL_H
#define CARDMODEL_H

#include <string>
#include "cocos2d.h"

class CardModel : public cocos2d::Ref {
public:
    //纸牌花色
    enum class Suit {
        NODE = -1,
        Clubs = 0, 
        Diamonds = 1,
        Hearts = 2,
        Spades = 3
    };

    //纸牌数字
    enum class Rank {
        NODE = -1,
        Ace = 0,
        Two = 1,
        Three = 2,
        Four = 3,
        Five = 4,
        Six = 5,
        Seven = 6,
        Eight = 7,
        Nine = 8,
        Ten = 9,
        Jack = 10,
        Queen = 11,
        King = 12
    };

    /** Create a card model with a stable card id. */
    static CardModel* create(int cardId, Suit suit, Rank rank, bool faceUp = false);

    /** Get the unique card id. */
    int getCardId() const;

    /** Get card suit. */
    Suit getSuit() const;

    /** Get card rank. */
    Rank getRank() const;

    /** Return true if card is face up. */
    bool isFaceUp() const;

    /** Set face up flag. */
    void setFaceUp(bool value);

    // Serialization support
    std::string serialize() const;
    static CardModel* deserialize(const std::string& data);

private:
    int _cardId;
    Suit _suit;
    Rank _rank;
    bool _faceUp;
};

#endif