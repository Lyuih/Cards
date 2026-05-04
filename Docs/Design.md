# Cards MVP Design Notes

## Overview
- Model: CardModel, CardDeckModel, GameModel, UndoModel
- View: CardView, CardDeckView, GameView, HUDView
- Controller: GameController, CardController, HUDController
- Services: MoveValidator, GameModelGenerator
- Config: LevelConfig loaded from JSON

## Data Flow
1. User clicks a card (CardView).
2. CardDeckView forwards the event to CardController.
3. CardController validates the move and records an UndoAction.
4. GameView animates the card MoveTo between decks.

## Add a New Card
1. Update the level JSON (Resources/levels/level_1.json) with a new entry.
2. If the card is in Playfield, set its Position; if in Stack, keep Position at 0,0.
3. GameModelGenerator will assign ids and build decks at load.

## Add a New Undo Type
1. Extend UndoAction to include any extra data needed for the new operation.
2. Record the action in CardController before mutating the model.
3. Implement reverse logic in UndoManager::undo.
4. Call GameView animation helpers to move views back.
