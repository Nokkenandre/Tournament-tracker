#include "apiClient.h"
#include <cpr/cpr.h>
#include <iostream>

// Json expected by /createTournament
// {
//   "name": "string",
//   "matchFormat": int
// }
nlohmann::json apiClient::createTournament(const QString& name, QString matchFormat) {
    matchFormat.remove(' ');
    nlohmann::json payload = {
        {"name", name.toStdString()},
        {"match_format", matchFormat.toStdString()}
    };

    cpr::Response r = cpr::Post(
        cpr::Url{"http://127.0.0.1:5000/create_tournament"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{payload.dump()}
    );

    if (r.status_code == 201) {
        return nlohmann::json::parse(r.text);
    } else {
        std::cerr << r.status_code << r.text << std::endl;
        return {{"error", "Request failed"}, {"status", r.status_code}};
    }
    
}

//  Json expected by /createTeam
//  {
//    "name": "string",
//  }
nlohmann::json apiClient::createTeam(const QString& name) {
    nlohmann::json payload = {
        {"name", name.toStdString()}
    };

    cpr::Response r = cpr::Post(
        cpr::Url{"http://127.0.0.1:5000/process"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{payload.dump()}
    );

    if (r.status_code == 201) {
        return nlohmann::json::parse(r.text);
    } else {
        std::cerr << r.status_code << r.text << std::endl;
        
        return {{"error", "Request failed"}, {"status", r.status_code}};
    }
    
}

// Returns info about all tournaments
nlohmann::json apiClient::getTournaments(const int startIndex, const int subsetSize) {
    nlohmann::json payload = {
        {"start_index", startIndex},
        {"subset_size", subsetSize}
    };

    cpr::Response r = cpr::Post(
        cpr::Url{"http://127.0.0.1:5000/get_tournaments"},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Body{payload.dump()}
    );

    if (r.status_code == 200) {
        return nlohmann::json::parse(r.text);
    } else {
        std::cerr << r.status_code << r.text << std::endl;
        return {{"error", "Request failed"}, {"status", r.status_code}};
    }
}