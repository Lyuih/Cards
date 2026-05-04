/**
 * HUDView - Simple HUD with buttons like Undo.
 */
#ifndef HUDVIEW_H
#define HUDVIEW_H

#include <functional>
#include "cocos2d.h"

class HUDView : public cocos2d::Node {
public:
    static HUDView* create();

    /** Set undo button callback. */
    void setUndoCallback(const std::function<void()>& callback);

private:
    bool init();
    void onUndoPressed(cocos2d::Ref* sender);

    std::function<void()> _undoCallback;
    cocos2d::MenuItemLabel* _undoItem;
};

#endif
