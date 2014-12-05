/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

/**
 *
 * @author antti
 */
public class Move {
    int gameId;
    String move;
    String team;
    String piece;
    String status;
    int turn;

    public String getMove() {
        return move;
    }

    public String getTeam() {
        return team;
    }

    public String getPiece() {
        return piece;
    }

    public String getStatus() {
        return status;
    }
    
    public int getTurn(){
        return turn;
    }
    
    public int getGameId(){
        return gameId;
    }

    
    public Move(int game_id, String move_str, String team_str, String piece_str, String status_str, int turn_int){
        gameId = game_id;
        move = move_str; 
        team = team_str; 
        piece = piece_str; 
        status = status_str;
        turn = turn_int;
    }
}
