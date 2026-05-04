#include "controllers/CardController.h"

CardController* CardController::create(GameModel* model, GameView* view, UndoManager* undoManager,
                                       const LevelConfig* levelConfig)
{
    auto controller = new CardController();
    controller->_gameModel = model;
    controller->_gameView = view;
    controller->_undoManager = undoManager;
    controller->_moveValidator = nullptr;
    controller->_levelConfig = levelConfig;
    controller->autorelease();
    return controller;
}

void CardController::initViewBindings()
{
    if (!_gameView || !_gameModel) {
        return;
    }

    for (int i = 0; i < static_cast<int>(_gameModel->getDecks().size()); ++i) {
        auto deckView = _gameView->getDeckView(i);
        if (!deckView) {
            continue;
        }
        deckView->setClickCallback([this](int deckId, int cardId) {
            this->handleCardTouchBegin(deckId, cardId);
        });
    }
}

bool CardController::handleCardTouchBegin(int deckId, int cardId)
{
    if (!_gameModel) {
        return false;
    }

    if (deckId == 1) {
        return false;
    }

    return moveCardToHand(deckId, cardId);
}

bool CardController::moveCards(int fromDeck, int fromIndex, int toDeck)
{
    (void)fromDeck;
    (void)fromIndex;
    (void)toDeck;
    return false;
}

bool CardController::isMoveValid(int fromDeck, int fromIndex, int toDeck) const
{
    auto fromDeckModel = _gameModel->getDeckById(fromDeck);
    auto toDeckModel = _gameModel->getDeckById(toDeck);
    if (!fromDeckModel || !toDeckModel || !_levelConfig) {
        return false;
    }

    return MoveValidator::canMove(*fromDeckModel, fromIndex, *toDeckModel, *_levelConfig);
}

bool CardController::moveCardToHand(int fromDeckId, int cardId)
{
    auto fromDeckModel = _gameModel->getDeckById(fromDeckId);
    auto handDeckModel = _gameModel->getDeckById(1);
    if (!fromDeckModel || !handDeckModel) {
        return false;
    }

    int fromIndex = fromDeckModel->getCardIndexById(cardId);
    if (fromIndex < 0) {
        return false;
    }
    if (!isMoveValid(fromDeckId, fromIndex, 1)) {
        return false;
    }

    auto fromDeckView = _gameView->getDeckView(fromDeckId);
    auto handDeckView = _gameView->getDeckView(1);
    if (!fromDeckView || !handDeckView) {
        return false;
    }

    auto cardView = fromDeckView->getCardViewById(cardId);
    cocos2d::Vec2 fromPosition = cardView ? cardView->getPosition() : cocos2d::Vec2::ZERO;

    int toIndex = handDeckModel->getCardCount();
    DeckLayoutInfo handLayout = handDeckView->getLayoutInfo();
    cocos2d::Vec2 toPosition = handLayout.basePosition + handLayout.stackOffset * toIndex;

    CardModel* card = fromDeckModel->getCardAt(fromIndex);
    if (!card) {
        return false;
    }

    card->retain();
    fromDeckModel->removeCardAt(fromIndex);
    handDeckModel->insertCardAt(card, toIndex, toPosition);
    card->release();

    UndoAction action;
    action.cardId = cardId;
    action.fromDeckId = fromDeckId;
    action.toDeckId = 1;
    action.fromIndex = fromIndex;
    action.toIndex = toIndex;
    action.fromPosition = fromPosition;
    action.toPosition = toPosition;
    _undoManager->recordAction(action);

    _gameView->moveCardBetweenDecks(fromDeckId, cardId, 1, toPosition, nullptr);
    return true;
}
