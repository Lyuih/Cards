#include "services/GameModelGenerator.h"
#include "models/CardDeckModel.h"
#include "models/CardModel.h"

namespace {
CardModel::Suit toSuit(int value)
{
    return static_cast<CardModel::Suit>(value);
}

CardModel::Rank toRank(int value)
{
    return static_cast<CardModel::Rank>(value);
}
}

GameModel* GameModelGenerator::generate(const LevelConfig& config)
{
    auto model = GameModel::create();

    auto playfieldDeck = CardDeckModel::create(0, CardDeckModel::DeckType::Playfield);
    auto handDeck = CardDeckModel::create(1, CardDeckModel::DeckType::Hand);
    auto stackDeck = CardDeckModel::create(2, CardDeckModel::DeckType::Stack);

    int cardIdSeed = 1;
    for (const auto& cardConfig : config.playfieldCards) {
        auto card = CardModel::create(cardIdSeed++, toSuit(cardConfig.cardSuit),
                                      toRank(cardConfig.cardFace), true);
        playfieldDeck->addCard(card, cardConfig.position);
    }

    bool handAssigned = false;
    for (const auto& cardConfig : config.stackCards) {
        auto card = CardModel::create(cardIdSeed++, toSuit(cardConfig.cardSuit),
                                      toRank(cardConfig.cardFace), true);
        if (!handAssigned) {
            handDeck->addCard(card, cocos2d::Vec2::ZERO);
            handAssigned = true;
        } else {
            stackDeck->addCard(card, cocos2d::Vec2::ZERO);
        }
    }

    model->addDeck(playfieldDeck);
    model->addDeck(handDeck);
    model->addDeck(stackDeck);

    return model;
}
