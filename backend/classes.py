from dataclasses import dataclass
from enum import Enum

class MatchFormat(Enum):
    RACE_TO_2 = 1
    MERCY_5 = 2


class Tournament: 
    def __init__(self, tournament_id, name, match_format):
        self.boj_id = tournament_id # Todo: add id
        self.name = name
        self.teams: Team = []
        self.match_format = match_format
        self.bracket = Bracket()
        
    def print_values(self):
        print(f"{self.tournament_id=} \n{self.name=} \n{self.teams=} \n{self.tournament_format=} \n{self.match_format=}")
    
class Team:
    def __init__(self, team_id, name):
        self.obj_id = team_id
        self.name = name
        
        self.players: Player = []
        self.tournaments: Tournament = []
        
    def print_values(self):
        print(f"{self.team_id=} \n{self.name=} \n{self.Players}")
        
class Player:
    def __init__(self, player_id, name):
        self.obj_id = player_id
        self.name = name
        self.teams: Team = []
    
    def print_values(self):
        print(self)


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
