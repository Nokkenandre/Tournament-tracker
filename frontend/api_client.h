#pragma once
#include <QString>
#include <nlohmann/json.hpp>

class ApiClient {
public:
    static nlohmann::json create_tournament(const QString& name, const int match_format);
    static nlohmann::json create_player(const QString& name);
    static nlohmann::json create_team(const QString& name);
};
