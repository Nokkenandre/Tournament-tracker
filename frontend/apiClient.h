#pragma once
#include <QString>
#include <nlohmann/json.hpp>

class ApiClient {
public:
    static nlohmann::json createTournament(const QString& name, const QString matchFormat);
    static nlohmann::json createPlayer(const QString& name);
    static nlohmann::json createTeam(const QString& name);
};
