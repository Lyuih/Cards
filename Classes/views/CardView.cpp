#include "views/CardView.h"
#include "configs/models/CardResConfig.h"

USING_NS_CC;

CardView* CardView::create()
{
    auto view = new CardView();
    if (view && view->init()) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool CardView::init()
{
    if (!Node::init()) {
        return false;
    }

    _cardId = -1;
    _cardModel = nullptr;
    _faceSprite = Sprite::create(CardResConfig::getCardBackgroundPath());
    _backSprite = nullptr;
    _numberSprite = Sprite::create();
    _suitSprite = Sprite::create();
    _centerSuitSprite = Sprite::create();

    this->addChild(_faceSprite);
    _faceSprite->addChild(_centerSuitSprite);
    _faceSprite->addChild(_numberSprite);
    _faceSprite->addChild(_suitSprite);

    const auto size = _faceSprite->getContentSize();
    this->setContentSize(size);
    _faceSprite->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
    _numberSprite->setAnchorPoint(Vec2(0.0f, 1.0f));
    _suitSprite->setAnchorPoint(Vec2(0.0f, 1.0f));
    _centerSuitSprite->setAnchorPoint(Vec2(0.5f, 0.5f));

    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

    return true;
}

void CardView::setClickCallback(const std::function<void(int)>& callback)
{
    _clickCallback = callback;
}

void CardView::bindModel(const CardModel* model, int cardId)
{
    _cardModel = model;
    _cardId = cardId;
    refreshFace();
}

int CardView::getCardId() const
{
    return _cardId;
}

void CardView::refreshFace()
{
    if (!_cardModel) {
        return;
    }

    std::string numberPath = CardResConfig::getNumberPath(_cardModel->getSuit(), _cardModel->getRank());
    std::string suitPath = CardResConfig::getSuitPath(_cardModel->getSuit());
    _numberSprite->setTexture(numberPath);
    _suitSprite->setTexture(suitPath);
    _centerSuitSprite->setTexture(suitPath);

    const auto cardSize = _faceSprite->getContentSize();
    const float marginX = cardSize.width * 0.08f;
    const float marginY = cardSize.height * 0.08f;

    const auto numberSize = _numberSprite->getContentSize();
    float numberScale = 1.0f;
    if (numberSize.height > 0.0f) {
        numberScale = (cardSize.height * 0.12f) / numberSize.height;
    }
    _numberSprite->setScale(numberScale);

    const auto suitSize = _suitSprite->getContentSize();
    float suitScale = 1.0f;
    if (suitSize.height > 0.0f) {
        suitScale = (cardSize.height * 0.08f) / suitSize.height;
    }
    _suitSprite->setScale(suitScale);

    float suitYOffset = numberSize.height * numberScale + cardSize.height * 0.02f;
    _numberSprite->setPosition(Vec2(marginX, cardSize.height - marginY));
    _suitSprite->setPosition(Vec2(marginX, cardSize.height - marginY - suitYOffset));

    float centerScale = 1.0f;
    if (suitSize.height > 0.0f) {
        centerScale = (cardSize.height * 0.35f) / suitSize.height;
    }
    _centerSuitSprite->setScale(centerScale);
    _centerSuitSprite->setPosition(Vec2(cardSize.width * 0.5f, cardSize.height * 0.5f));
}

bool CardView::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 localPoint = this->convertToNodeSpace(touch->getLocation());
    Rect bounds(Vec2::ZERO, this->getContentSize());
    if (!bounds.containsPoint(localPoint)) {
        return false;
    }

    // 覆盖状态的牌不参与点击（需消除上方牌后才能翻开操作）
    if (_cardModel && !_cardModel->isFaceUp()) {
        return false;
    }

    if (_clickCallback) {
        _clickCallback(_cardId);
    }
    return true;
}

void CardView::playFlipAnimation()
{
    // Placeholder for flip animation.
}

void CardView::playMoveToAnimation(const cocos2d::Vec2& target, std::function<void()> onComplete)
{
    auto move = MoveTo::create(0.25f, target);
    if (onComplete) {
        auto callback = CallFunc::create(onComplete);
        runAction(Sequence::create(move, callback, nullptr));
    } else {
        runAction(move);
    }
}

void CardView::playRemoveAnimation(std::function<void()> onComplete)
{
    auto fade = FadeOut::create(0.2f);
    if (onComplete) {
        auto callback = CallFunc::create(onComplete);
        runAction(Sequence::create(fade, callback, nullptr));
    } else {
        runAction(fade);
    }
}
