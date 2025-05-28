#include "apiClient.h"
#include <cpr/cpr.h>

// Json expected by /create_tournament
// {
//   "name": "string",
//   "matchFormat": int
nlohmann::json ApiClient::createTournament(const QString& name, QString matchFormat) {
    matchFormat.remove(' ');
    nlohmann::json payload = {
        {"name", name.toStdString()},
        {"matchFormat", matchFormat.toStdString()}
    };

    cpr::Response r = cpr::Post(
        cpr::Url{"http://127.0.0.1:5000/create_tournament"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{payload.dump()}
    );

    if (r.status_code == 200) {
        return nlohmann::json::parse(r.text);
    } else {
        return {{"error", "Request failed"}, {"status", r.status_code}};
    }
}

//  Json expected by /create_team
//  {
//    "name": "string",
//  }
nlohmann::json ApiClient::createTeam(const QString& name) {
    nlohmann::json payload = {
        {"name", name.toStdString()}
    };

    cpr::Response r = cpr::Post(
        cpr::Url{"http://127.0.0.1:5000/process"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{payload.dump()}
    );

    if (r.status_code == 200) {
        return nlohmann::json::parse(r.text);
    } else {
        return {{"error", "Request failed"}, {"status", r.status_code}};
    }
}

// Json expected by /create_player
// {
//   "name": "string",
// }

nlohmann::json ApiClient::createPlayer(const QString& name) {
    nlohmann::json payload = {
        {"name", name.toStdString()}
    };

    cpr::Response r = cpr::Post(
        cpr::Url{"http://127.0.0.1:5000/process"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{payload.dump()}
    );

    if (r.status_code == 200) {
        return nlohmann::json::parse(r.text);
    } else {
        return {{"error", "Request failed"}, {"status", r.status_code}};
    }
}
