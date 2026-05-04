#include "views/GameView.h"

USING_NS_CC;

static const Color4B kPlayfieldColor(30, 100, 50, 255);    // 主牌区深绿色
static const Color4B kStackAreaColor(20, 75, 40, 255);     // 堆牌区稍深绿色
static const float kPlayfieldHeight = 1500.0f;
static const float kStackAreaHeight = 580.0f;

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
    auto winSize = Director::getInstance()->getWinSize();

    // 主牌区背景
    auto playfieldBg = LayerColor::create(kPlayfieldColor,
                                           winSize.width, kPlayfieldHeight);
    playfieldBg->setPosition(0, kStackAreaHeight);
    this->addChild(playfieldBg, -1);

    // 堆牌区背景
    auto stackBg = LayerColor::create(kStackAreaColor,
                                       winSize.width, kStackAreaHeight);
    stackBg->setPosition(0, 0);
    this->addChild(stackBg, -1);

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
