/**
 * CardView - 一张卡牌的视觉表现。
 * 可以持有 const CardModel* 和 const CardController* 用于显示与回调，
 * 但不直接修改 Model。
 */
#ifndef CARDVIEW_H
#define CARDVIEW_H
#include <functional>
#include "cocos2d.h"
#include "models/CardModel.h"

class CardView : public cocos2d::Node {
public:
    static CardView* create();

    /** 设置回调，当卡片被点击时调用，传回 cardId */
    void setClickCallback(const std::function<void(int cardId)>& callback);

    /** 绑定数据，更新 UI */
    void bindModel(const CardModel* model, int cardId);

    /** Get card id. */
    int getCardId() const;

    // 动画接口（由 Controller 驱动）
    void playFlipAnimation();          // 翻牌动画
    void playMoveToAnimation(const cocos2d::Vec2& target, std::function<void()> onComplete);
    void playRemoveAnimation(std::function<void()> onComplete);

private:
    bool init();
    void refreshFace();
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    int _cardId;
    const CardModel* _cardModel;
    std::function<void(int)> _clickCallback;
    cocos2d::Sprite* _faceSprite;
    cocos2d::Sprite* _backSprite;
    cocos2d::Sprite* _numberSprite;
    cocos2d::Sprite* _suitSprite;
    cocos2d::Sprite* _centerSuitSprite;
    cocos2d::EventListenerTouchOneByOne* _touchListener;
};

#endif