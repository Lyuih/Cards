/**
 * CardController - 处理所有与卡牌交互的逻辑，包括点击、移动、连牌判断等。
 * 它持有对 GameModel 的引用，并通过服务完成合法性检测。
 */
#ifndef CARDCONTROLLER_H
#define CARDCONTROLLER_H
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/GameView.h"
#include "services/MoveValidator.h"
#include "managers/UndoManager.h"
#include "configs/models/LevelConfig.h"

class CardController : public cocos2d::Ref {
public:
    static CardController* create(GameModel* model, GameView* view, UndoManager* undoManager,
                                  const LevelConfig* levelConfig);

    /** 初始化：为所有 CardDeckView 绑定回调 */
    void initViewBindings();

    /** Handle card click. */
    bool handleCardTouchBegin(int deckId, int cardId);

    /** 执行一叠牌的移动（从 fromDeck 拖到 toDeck） */
    bool moveCards(int fromDeck, int fromIndex, int toDeck);

private:
    // Internal helpers
    bool isMoveValid(int fromDeck, int fromIndex, int toDeck) const;
    bool moveCardToHand(int fromDeckId, int cardId);

    GameModel* _gameModel;
    GameView* _gameView;
    MoveValidator* _moveValidator;  // 无状态服务
    UndoManager* _undoManager;      // 由 GameController 传入，非拥有
    const LevelConfig* _levelConfig;
};
#endif