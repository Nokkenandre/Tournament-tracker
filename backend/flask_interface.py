from classes import *
from backend_services import *
from flask import Flask, jsonify, request, abort
import sys

app = Flask(__name__)

tournaments: Tournament = []
teams: Team = []

# Json expected by /create_tournament
# {
#   "name": "string",
#   "match_format": int
# }

@app.route("/create_tournament", methods=["POST"])
def create_tournament():
    data = request.get_json()

    if not data or "name" not in data or "match_format" not in data:
        print("Error: Missing required fields", file=sys.stderr)
        return jsonify({"error": "Missing required fields"}), 400

    name = data.get("name")
    tournament_id = len(tournaments)+1
    
    raw_match_format = data.get("match_format").upper()
    match_format = Match_format[raw_match_format]
    
    tournament = Tournament(tournament_id, name, match_format)
    tournaments.append(tournament)

    response_data = {
        "name": name,
        "match_format": raw_match_format
    }
    print("Succesfully created new tournament:")
    tournament.print_values()
    return jsonify(response_data), 201


# Json expected by /create_team
# {
#   "name": "string",
#}

@app.route("/create_team", methods=["POST"])
def add_team():
    data = request.get_json()

    if not data or "name" not in data:
        print("Error: Missing required fields", file=sys.stderr)
        return jsonify({"error": "Missing required fields"}), 400

    name = data.get("name")
    team_id = len(teams)+1
    
    team = Team(team_id, name)
    teams.append(team)

    response_data = {
        "name": name,
    }
    print("Succesfully created new team:")
    team.print_values()
    return jsonify(response_data), 201

# Json expected by /add_team_to_tournament
# {
#   "tournament_id": tournament_id,
#   "team_id": team_id
# }

@app.route("/add_team_to_tournament", methods=["POST"])
def add_team_to_tournament():
    data = request.get_json()
    
    tournament_id = data.get("tournament_id")
    team_id = data.get("team_id")
    
    tournament = get_object_by_id(tournament_id)
    team = get_object_by_id(team_id)
    
    tournament.teams.append(team) # Add team to the tournament
    team.tournaments.append(tournament) # Add tournament to the team to track what tournament they are in
    
# Returns a subset of tournaments
@app.route("/get_tournaments", methods=["POST"])
def get_tournaments():
    data = request.get_json()
    start = int(data.get("start_index"))
    subset_size = int(data.get("subset_size"))
    end = start + subset_size
    subset = tournaments[start:end]
    subset_dicts = [t.to_dict() for t in subset]
    return jsonify(subset_dicts)

@app.route("/set_up_tournament", methods=["POST"])
def set_up_tournaments():
    data = request.get_json()
    
    # Padds the list with dummy entries up to the closest power of 2 (E.g. 2, 4, 8, 16 etc.)
    n = len(teams)
    power = 1
    while power < n:
        power <<= 1
    teams.extend(['BYE'] * (power - n))
    
if __name__ == "__main__":
    app.run(host="localhost", port=5000)  # Running the server on localhost:5000
    
    

    
    
