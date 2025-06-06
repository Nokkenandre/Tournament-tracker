#pragma once
#include <QString>
#include <nlohmann/json.hpp>

class apiClient {
public:
    static nlohmann::json createTournament(const QString& name, const QString matchFormat);
    static nlohmann::json createTeam(const QString& name);
    static nlohmann::json getTournaments(const int startIndex, const int subsetSize);
};
