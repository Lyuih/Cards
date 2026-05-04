#include "views/HUDView.h"

USING_NS_CC;

HUDView* HUDView::create()
{
    auto view = new HUDView();
    if (view && view->init()) {
        view->autorelease();
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

bool HUDView::init()
{
    if (!Node::init()) {
        return false;
    }

    auto label = Label::createWithTTF("Undo", "fonts/Marker Felt.ttf", 36);
    _undoItem = MenuItemLabel::create(label, CC_CALLBACK_1(HUDView::onUndoPressed, this));
    _undoItem->setPosition(Vec2(980.0f, 1900.0f));

    auto menu = Menu::create(_undoItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);

    return true;
}

void HUDView::setUndoCallback(const std::function<void()>& callback)
{
    _undoCallback = callback;
}

void HUDView::onUndoPressed(cocos2d::Ref* sender)
{
    (void)sender;
    if (_undoCallback) {
        _undoCallback();
    }
}
