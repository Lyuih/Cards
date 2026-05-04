/**
 * HUDController - Connects HUD view events to callbacks.
 */
#ifndef HUDCONTROLLER_H
#define HUDCONTROLLER_H

#include <functional>
#include "cocos2d.h"
#include "views/HUDView.h"

class HUDController : public cocos2d::Ref {
public:
    static HUDController* create(HUDView* view);

    /** Bind undo action. */
    void bindUndoCallback(const std::function<void()>& callback);

private:
    HUDView* _hudView;
};

#endif
