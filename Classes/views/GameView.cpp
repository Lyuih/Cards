#include "views/GameView.h"

USING_NS_CC;

GameView* GameView::create()
{
    auto view = new GameView();
    if (view && view->init()) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool GameView::init()
{
    if (!Node::init()) {
        return false;
    }
    _hudView = nullptr;
    return true;
}

void GameView::setupLayout(const std::vector<DeckLayoutInfo>& deckInfos)
{
    _deckViews.clear();
    for (const auto& info : deckInfos) {
        auto deckView = CardDeckView::create(info);
        this->addChild(deckView);
        _deckViews.push_back(deckView);
    }

    if (!_hudView) {
        _hudView = HUDView::create();
        this->addChild(_hudView, 10);
    }
}

void GameView::playDealAnimation(std::function<void()> onComplete)
{
    if (onComplete) {
        onComplete();
    }
}

void GameView::playMatchAnimation(int deckId, int cardId, std::function<void()> onComplete)
{
    (void)deckId;
    (void)cardId;
    if (onComplete) {
        onComplete();
    }
}

void GameView::moveCardBetweenDecks(int fromDeckId, int cardId, int toDeckId,
                                    const cocos2d::Vec2& targetPosition,
                                    std::function<void()> onComplete)
{
    auto fromDeck = getDeckView(fromDeckId);
    auto toDeck = getDeckView(toDeckId);
    if (!fromDeck || !toDeck) {
        return;
    }

    CardView* cardView = fromDeck->removeCardView(cardId);
    if (!cardView) {
        return;
    }

    Vec2 worldStart = fromDeck->convertToWorldSpace(cardView->getPosition());
    Vec2 worldTarget = toDeck->convertToWorldSpace(targetPosition);
    Vec2 localStart = this->convertToNodeSpace(worldStart);
    Vec2 localTarget = this->convertToNodeSpace(worldTarget);

    this->addChild(cardView, 1000);
    cardView->setPosition(localStart);

    auto move = MoveTo::create(0.25f, localTarget);
    auto finish = CallFunc::create([this, cardView, toDeck, targetPosition, onComplete]() {
        cardView->removeFromParent();
        toDeck->addExistingCardView(cardView, targetPosition);
        cardView->release();
        if (onComplete) {
            onComplete();
        }
    });
    cardView->runAction(Sequence::create(move, finish, nullptr));
}

CardDeckView* GameView::getDeckView(int index)
{
    for (auto* deck : _deckViews) {
        if (deck->getDeckId() == index) {
            return deck;
        }
    }
    return nullptr;
}

HUDView* GameView::getHUDView()
{
    return _hudView;
}
