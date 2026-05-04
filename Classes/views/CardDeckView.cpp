#include "views/CardDeckView.h"

USING_NS_CC;

CardDeckView* CardDeckView::create(const DeckLayoutInfo& layoutInfo)
{
    auto view = new CardDeckView();
    if (view && view->init(layoutInfo)) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool CardDeckView::init(const DeckLayoutInfo& layoutInfo)
{
    if (!Node::init()) {
        return false;
    }
    _deckId = layoutInfo.deckId;
    _layoutInfo = layoutInfo;
    return true;
}

void CardDeckView::bindModel(const CardDeckModel* model)
{
    if (!model) {
        return;
    }

    const auto& cards = model->getCards();
    const auto& positions = model->getPositions();
    for (int i = 0; i < static_cast<int>(cards.size()); ++i) {
        cocos2d::Vec2 modelPos = Vec2::ZERO;
        if (i < static_cast<int>(positions.size())) {
            modelPos = positions[i];
        }
        addCardView(cards[i], cards[i]->getCardId(), resolveCardPosition(modelPos, i));
    }
}

void CardDeckView::setClickCallback(const std::function<void(int, int)>& callback)
{
    _clickCallback = callback;
}

void CardDeckView::addCardView(const CardModel* model, int cardId, const cocos2d::Vec2& position)
{
    auto view = CardView::create();
    view->bindModel(model, cardId);
    view->setPosition(position);
    view->setClickCallback([this](int clickedCardId) {
        if (_clickCallback) {
            _clickCallback(_deckId, clickedCardId);
        }
    });

    this->addChild(view, 1);
    _cardViews[cardId] = view;
}

void CardDeckView::addExistingCardView(CardView* view, const cocos2d::Vec2& position)
{
    if (!view) {
        return;
    }

    int cardId = view->getCardId();
    view->setPosition(position);
    view->setClickCallback([this](int clickedCardId) {
        if (_clickCallback) {
            _clickCallback(_deckId, clickedCardId);
        }
    });

    this->addChild(view, 1);
    _cardViews[cardId] = view;
}

CardView* CardDeckView::removeCardView(int cardId)
{
    auto it = _cardViews.find(cardId);
    if (it == _cardViews.end()) {
        return nullptr;
    }

    CardView* view = it->second;
    view->retain();
    view->removeFromParent();
    _cardViews.erase(it);
    return view;
}

CardView* CardDeckView::getCardViewById(int cardId) const
{
    auto it = _cardViews.find(cardId);
    if (it == _cardViews.end()) {
        return nullptr;
    }
    return it->second;
}

int CardDeckView::getDeckId() const
{
    return _deckId;
}

cocos2d::Vec2 CardDeckView::getBasePosition() const
{
    return _layoutInfo.basePosition;
}

DeckLayoutInfo CardDeckView::getLayoutInfo() const
{
    return _layoutInfo;
}

cocos2d::Vec2 CardDeckView::resolveCardPosition(const cocos2d::Vec2& modelPosition, int index) const
{
    if (_layoutInfo.useFixedPositions) {
        return modelPosition;
    }
    return _layoutInfo.basePosition + _layoutInfo.stackOffset * index;
}
