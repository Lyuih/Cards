#include "controllers/HUDController.h"

HUDController* HUDController::create(HUDView* view)
{
    auto controller = new HUDController();
    controller->_hudView = view;
    controller->autorelease();
    return controller;
}

void HUDController::bindUndoCallback(const std::function<void()>& callback)
{
    if (_hudView) {
        _hudView->setUndoCallback(callback);
    }
}
