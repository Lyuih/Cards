/**
 * CardDeckView - Visual container for a deck of card views.
 */
#ifndef CARDDECKVIEW_H
#define CARDDECKVIEW_H

#include <unordered_map>
#include <functional>
#include "cocos2d.h"
#include "models/CardDeckModel.h"
#include "views/CardView.h"
#include "views/DeckLayoutInfo.h"

class CardDeckView : public cocos2d::Node {
public:
    static CardDeckView* create(const DeckLayoutInfo& layoutInfo);

    /** Bind model and create card views. */
    void bindModel(const CardDeckModel* model);

    /** Set callback for card clicks. */
    void setClickCallback(const std::function<void(int deckId, int cardId)>& callback);

    /** Add a new card view to this deck. */
    void addCardView(const CardModel* model, int cardId, const cocos2d::Vec2& position);

    /** Add an existing card view (reparent). */
    void addExistingCardView(CardView* view, const cocos2d::Vec2& position);

    /** Remove a card view from this deck. */
    CardView* removeCardView(int cardId);

    /** Get card view by id. */
    CardView* getCardViewById(int cardId) const;

    /** Get deck id. */
    int getDeckId() const;

    /** Get base position for this deck. */
    cocos2d::Vec2 getBasePosition() const;

    /** Get deck layout info. */
    DeckLayoutInfo getLayoutInfo() const;

private:
    bool init(const DeckLayoutInfo& layoutInfo);
    cocos2d::Vec2 resolveCardPosition(const cocos2d::Vec2& modelPosition, int index) const;

    int _deckId;
    DeckLayoutInfo _layoutInfo;
    std::unordered_map<int, CardView*> _cardViews;
    std::function<void(int, int)> _clickCallback;
};

#endif
