#include "controllers/GameController.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "services/GameModelGenerator.h"
#include "models/CardDeckModel.h"

GameController* GameController::create()
{
    auto controller = new GameController();
    controller->_gameModel = nullptr;
    controller->_levelConfig = nullptr;
    controller->_gameView = nullptr;
    controller->_cardController = nullptr;
    controller->_hudController = nullptr;
    controller->_undoManager = nullptr;
    controller->_saveManager = nullptr;
    controller->autorelease();
    return controller;
}

GameController::~GameController()
{
    CC_SAFE_RELEASE_NULL(_cardController);
    CC_SAFE_RELEASE_NULL(_hudController);
    CC_SAFE_RELEASE_NULL(_undoManager);
    CC_SAFE_RELEASE_NULL(_saveManager);
    CC_SAFE_RELEASE_NULL(_gameModel);
}

void GameController::startLevel(int levelId)
{
    loadConfig(levelId);
    generateModel();
    initView();
    initSubControllers();
    bindHUD();
}

void GameController::onGameWon()
{
}

void GameController::onGameLost()
{
}

const GameModel* GameController::getGameModel() const
{
    return _gameModel;
}

GameView* GameController::getGameView() const
{
    return _gameView;
}

void GameController::loadConfig(int levelId)
{
    static LevelConfig config;
    if (!LevelConfigLoader::loadLevelConfig(levelId, config)) {
        config = LevelConfig();
    }
    _levelConfig = &config;
}

void GameController::generateModel()
{
    CC_SAFE_RELEASE_NULL(_gameModel);
    if (_levelConfig) {
        _gameModel = GameModelGenerator::generate(*_levelConfig);
        if (_gameModel) {
            _gameModel->retain();
        }
    }
}

void GameController::initSubControllers()
{
    if (!_gameModel || !_gameView) {
        return;
    }
    _undoManager = UndoManager::create();
    if (_undoManager) {
        _undoManager->retain();
    }
    _cardController = CardController::create(_gameModel, _gameView, _undoManager, _levelConfig);
    if (_cardController) {
        _cardController->retain();
    }
    _cardController->initViewBindings();

    if (_gameView) {
        _hudController = HUDController::create(_gameView->getHUDView());
        if (_hudController) {
            _hudController->retain();
        }
    }
}

void GameController::initView()
{
    if (!_gameModel) {
        return;
    }
    _gameView = GameView::create();

    std::vector<DeckLayoutInfo> layouts;
    DeckLayoutInfo playfieldLayout;
    playfieldLayout.deckId = 0;
    playfieldLayout.deckType = CardDeckModel::DeckType::Playfield;
    playfieldLayout.useFixedPositions = true;
    layouts.push_back(playfieldLayout);

    DeckLayoutInfo handLayout;
    handLayout.deckId = 1;
    handLayout.deckType = CardDeckModel::DeckType::Hand;
    handLayout.basePosition = cocos2d::Vec2(760.0f, 230.0f);
    handLayout.stackOffset = cocos2d::Vec2(0.0f, 0.0f);
    layouts.push_back(handLayout);

    DeckLayoutInfo stackLayout;
    stackLayout.deckId = 2;
    stackLayout.deckType = CardDeckModel::DeckType::Stack;
    stackLayout.basePosition = cocos2d::Vec2(320.0f, 230.0f);
    stackLayout.stackOffset = cocos2d::Vec2(0.0f, 0.0f);
    layouts.push_back(stackLayout);

    _gameView->setupLayout(layouts);

    for (auto* deckModel : _gameModel->getDecks()) {
        auto deckView = _gameView->getDeckView(deckModel->getDeckId());
        if (deckView) {
            deckView->bindModel(deckModel);
        }
    }
}

void GameController::bindHUD()
{
    if (_hudController) {
        _hudController->bindUndoCallback([this]() {
            this->handleUndo();
        });
    }
}

void GameController::handleUndo()
{
    if (!_undoManager || !_gameModel || !_gameView) {
        return;
    }

    UndoAction action;
    if (!_undoManager->undo(_gameModel, action)) {
        return;
    }

    _gameView->moveCardBetweenDecks(action.toDeckId, action.cardId, action.fromDeckId,
                                    action.fromPosition, nullptr);
}
