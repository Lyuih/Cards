#ifndef CARDRESCONFIG_H
#define CARDRESCONFIG_H

#include <string>
#include "models/CardModel.h"

/**
 * CardResConfig - Maps card suit and rank to resource paths.
 */
class CardResConfig {
public:
	/** Get card background path. */
	static std::string getCardBackgroundPath();

	/** Get suit icon path. */
	static std::string getSuitPath(CardModel::Suit suit);

	/** Get number sprite path based on suit color and rank. */
	static std::string getNumberPath(CardModel::Suit suit, CardModel::Rank rank);
};

#endif
