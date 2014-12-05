/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import javax.faces.bean.*;
/**
 *
 * @author antti
 */
@ManagedBean
@RequestScoped
public class Player implements java.io.Serializable{
    int id;
    String name;
    int gamesTotal;
    int gamesDraw;
    int gamesWon;
    
    public Player(int pid, String pname, int total, int won, int draw){
        id = pid;
        name = pname;
        gamesTotal = total;
        gamesWon = won;
        gamesDraw = draw;
    }
    
    public int getId(){
        return id;
    }
    
    public String getName(){
        return name;
    }
    
    public int getTotal(){
        return gamesTotal;
    }
    
    public int getWon(){
        return gamesWon;
    }
    
    public int getDraw(){
        return gamesDraw;
    }
}
