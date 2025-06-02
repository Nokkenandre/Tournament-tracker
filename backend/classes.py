from dataclasses import dataclass
from enum import Enum

class Match_format(Enum):
    RACETO2 = 1
    MERCY5 = 2


class Tournament: 
    def __init__(self, tournament_id, name, match_format):
        self.obj_id = tournament_id # Todo: add id
        self.name = name
        self.teams: Team = []
        self.match_format = match_format
        self.bracket = Bracket()
        
    def print_values(self):
        print(f"{self.obj_id=} \n{self.name=} \n{self.teams=} \n{self.match_format=}")
    
    def to_dict(self):
        return {
            "id": self.obj_id, 
            "name": self.name,
            "teams": [{"id": t.obj_id, "name": t.name} for t in self.teams],
            "match_format": self.match_format.name
        }

class Team:
    def __init__(self, team_id, name):
        self.obj_id = team_id
        self.name = name

        self.tournaments: Tournament = []
        
    def print_values(self):
        print(f"{self.team_id=} \n{self.name=} \n{self.Players=}")
    
    def to_dict(self):
        return {
            "id": self.obj_id,
            "name": self.name,
            "tournaments": [{"id": t.obj_id, "name": t.name} for t in self.tournaments]
        }


class Bracket:
    def __init__(self):
        self.matches: Match = []
    

class Match:
    def __init__(self, team_a, team_b):
        team_a: Team = team_a
        team_b: Team = team_b
        winner: Team
        score = {
            team_a:0,
            team_b:0
        }
