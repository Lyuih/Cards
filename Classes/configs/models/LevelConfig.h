/**
 * LevelConfig - 一个关卡的所有静态参数。
 * 由 LevelConfigLoader 从 json/plist 文件构建。
 */

#ifndef LEVELCONFIG_H
#define LEVELCONFIG_H

#include <vector>
#include "cocos2d.h"

//卡片的配置
struct CardConfig {
    int cardFace;   // 0-12
    int cardSuit;   // 0-3
    cocos2d::Vec2 position;
};

/**
 * LevelConfig - 关卡的静态数据
 * Built by LevelConfigLoader from json.
 */
struct LevelConfig {
    int levelId = 0;
    std::vector<CardConfig> playfieldCards;
    std::vector<CardConfig> stackCards;
};

#endif