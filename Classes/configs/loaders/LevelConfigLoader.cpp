#include "configs/loaders/LevelConfigLoader.h"
#include "configs/models/LevelConfig.h"
#include "cocos2d.h"
#include "json/document.h"

namespace {
bool parseCardArray(const rapidjson::Value& arrayValue, std::vector<CardConfig>& outCards)
{
    if (!arrayValue.IsArray()) {
        return false;
    }

    for (rapidjson::SizeType i = 0; i < arrayValue.Size(); ++i) {
        const auto& cardValue = arrayValue[i];
        if (!cardValue.IsObject()) {
            continue;
        }

        CardConfig card;
        card.cardFace = cardValue["CardFace"].GetInt();
        card.cardSuit = cardValue["CardSuit"].GetInt();
        const auto& posValue = cardValue["Position"];
        card.position = cocos2d::Vec2(posValue["x"].GetFloat(), posValue["y"].GetFloat());
        outCards.push_back(card);
    }
    return true;
}
}

bool LevelConfigLoader::loadLevelConfig(int levelId, LevelConfig& outConfig)
{
    std::string path = cocos2d::StringUtils::format("levels/level_%d.json", levelId);
    return loadLevelConfigFromPath(path, outConfig);
}

bool LevelConfigLoader::loadLevelConfigFromPath(const std::string& path, LevelConfig& outConfig)
{
    std::string jsonText = cocos2d::FileUtils::getInstance()->getStringFromFile(path);
    if (jsonText.empty()) {
        return false;
    }

    rapidjson::Document doc;
    doc.Parse(jsonText.c_str());
    if (doc.HasParseError() || !doc.IsObject()) {
        return false;
    }

    outConfig = LevelConfig();
    if (doc.HasMember("LevelId")) {
        outConfig.levelId = doc["LevelId"].GetInt();
    }

    if (doc.HasMember("Playfield")) {
        parseCardArray(doc["Playfield"], outConfig.playfieldCards);
    }
    if (doc.HasMember("Stack")) {
        parseCardArray(doc["Stack"], outConfig.stackCards);
    }

    return true;
}
