#include "api_client.h"
#include <cpr/cpr.h>

// Json expected by /create_tournament
// {
//   "name": "string",
//   "match_format": int
nlohmann::json ApiClient::create_tournament(const QString& name, int match_format) {
    nlohmann::json payload = {
        {"name", name.toStdString()},
        {"match_format", match_format}
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
nlohmann::json ApiClient::create_team(const QString& name) {
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

nlohmann::json ApiClient::create_player(const QString& name) {
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
