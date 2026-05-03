#include "configs/models/CardResConfig.h"

namespace {
std::string getRankToken(CardModel::Rank rank)
{
    switch (rank) {
    case CardModel::Rank::Ace: return "A";
    case CardModel::Rank::Two: return "2";
    case CardModel::Rank::Three: return "3";
    case CardModel::Rank::Four: return "4";
    case CardModel::Rank::Five: return "5";
    case CardModel::Rank::Six: return "6";
    case CardModel::Rank::Seven: return "7";
    case CardModel::Rank::Eight: return "8";
    case CardModel::Rank::Nine: return "9";
    case CardModel::Rank::Ten: return "10";
    case CardModel::Rank::Jack: return "J";
    case CardModel::Rank::Queen: return "Q";
    case CardModel::Rank::King: return "K";
    default: return "A";
    }
}

bool isRedSuit(CardModel::Suit suit)
{
    return suit == CardModel::Suit::Hearts || suit == CardModel::Suit::Diamonds;
}
}

std::string CardResConfig::getCardBackgroundPath()
{
    return "res/res/card_general.png";
}

std::string CardResConfig::getSuitPath(CardModel::Suit suit)
{
    switch (suit) {
    case CardModel::Suit::Clubs:
        return "res/res/suits/club.png";
    case CardModel::Suit::Diamonds:
        return "res/res/suits/diamond.png";
    case CardModel::Suit::Hearts:
        return "res/res/suits/heart.png";
    case CardModel::Suit::Spades:
        return "res/res/suits/spade.png";
    default:
        return "res/res/suits/club.png";
    }
}

std::string CardResConfig::getNumberPath(CardModel::Suit suit, CardModel::Rank rank)
{
    const char* color = isRedSuit(suit) ? "red" : "black";
    std::string token = getRankToken(rank);
    return "res/res/number/small_" + std::string(color) + "_" + token + ".png";
}
