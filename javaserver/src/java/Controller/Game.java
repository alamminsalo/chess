/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import java.util.ArrayList;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;

/**
 *
 * @author antti
 */
@ManagedBean
@RequestScoped
public class Game {
    int id;
    String white;
    String black;
    int moves;
    String winner;

    public int getMoves() {
        return moves;
    }

    public int getId() {
        return id;
    }

    public String getWhite() {
        return white;
    }

    public String getBlack() {
        return black;
    }

    public String getWinner() {
        return winner;
    }
    
    public Game(int gid, String pwhite, String pblack,int moves, String gwinner){
        id = gid;
        white = pwhite;
        black = pblack;
        winner = gwinner;
        this.moves = moves;
    }
}
