/**
 * GameView - 游戏主场景的根视图。
 * 初始化时创建所有子视图（牌堆、按钮等），并对外提供动画方法。
 */
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <vector>
#include "cocos2d.h"
#include "views/DeckLayoutInfo.h"
#include "views/CardDeckView.h"
#include "views/HUDView.h"

class GameView : public cocos2d::Node {
public:
    static GameView* create();

    // 初始化布局（传入牌堆配置）
    void setupLayout(const std::vector<DeckLayoutInfo>& deckInfos);

    // 动画入口
    void playDealAnimation(std::function<void()> onComplete);
    void playMatchAnimation(int deckId, int cardId, std::function<void()> onComplete);

    /** Move a card between decks with a simple MoveTo animation. */
    void moveCardBetweenDecks(int fromDeckId, int cardId, int toDeckId,
                              const cocos2d::Vec2& targetPosition,
                              std::function<void()> onComplete);

    // 暴露子视图以便 Controller 绑定
    CardDeckView* getDeckView(int index);
    HUDView* getHUDView();

private:
    bool init();
    std::vector<CardDeckView*> _deckViews;
    HUDView* _hudView;
};

#endif