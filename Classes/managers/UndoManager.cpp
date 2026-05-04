#include "managers/UndoManager.h"
#include "models/CardDeckModel.h"

UndoManager* UndoManager::create()
{
    auto manager = new UndoManager();
    manager->_undoModel = new UndoModel();
    manager->autorelease();
    return manager;
}

UndoManager::~UndoManager()
{
    delete _undoModel;
    _undoModel = nullptr;
}

void UndoManager::recordAction(const UndoAction& action)
{
    _undoModel->push(action);
}

bool UndoManager::undo(GameModel* model, UndoAction& outAction)
{
    if (!_undoModel->popUndo(outAction)) {
        return false;
    }

    auto* fromDeck = model->getDeckById(outAction.toDeckId);
    auto* toDeck = model->getDeckById(outAction.fromDeckId);
    if (!fromDeck || !toDeck) {
        return false;
    }

    CardModel* card = fromDeck->getCardAt(outAction.toIndex);
    if (!card) {
        return false;
    }

    card->retain();
    fromDeck->removeCardAt(outAction.toIndex);
    toDeck->insertCardAt(card, outAction.fromIndex, outAction.fromPosition);
    card->release();
    _undoModel->pushRedo(outAction);
    return true;
}

bool UndoManager::redo(GameModel* model, UndoAction& outAction)
{
    if (!_undoModel->popRedo(outAction)) {
        return false;
    }

    auto* fromDeck = model->getDeckById(outAction.fromDeckId);
    auto* toDeck = model->getDeckById(outAction.toDeckId);
    if (!fromDeck || !toDeck) {
        return false;
    }

    CardModel* card = fromDeck->getCardAt(outAction.fromIndex);
    if (!card) {
        return false;
    }

    card->retain();
    fromDeck->removeCardAt(outAction.fromIndex);
    toDeck->insertCardAt(card, outAction.toIndex, outAction.toPosition);
    card->release();
    _undoModel->push(outAction);
    return true;
}

void UndoManager::reset()
{
    _undoModel->reset();
}
