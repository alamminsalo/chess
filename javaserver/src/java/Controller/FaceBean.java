/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import java.util.ArrayList;
import javax.ejb.Stateful;
import javax.ejb.Stateless;
import javax.faces.bean.ManagedBean;
import javax.faces.bean.RequestScoped;

/**
 *
 * @author antti
 */
@Stateful
@ManagedBean
@RequestScoped
public class FaceBean {
    ArrayList<Game> GameList = null;
    ArrayList<Move> MoveList = null;
    ArrayList<Player> PlayerList = null;
    
    ServerDatabaseConnector dbc = null;
    
    String newname;
    String newpass;
    String retmsg;
    
    int searchId;
    
    public FaceBean(){
        dbc = new ServerDatabaseConnector();
    }

    public ArrayList<Game> getGameList() {
        return GameList;
    }
    public ArrayList<Move> getMoveList() {
        return MoveList;
    }
    public ArrayList<Player> getPlayerList() {
        return PlayerList;
    }

    public int getSearchId() {
        return searchId;
    }

    public void setSearchId(int searchId) {
        this.searchId = searchId;
    }
    
    public String getGames(){
        GameList = dbc.getGameData();
        return "printGames";
    }
    public String getMoves(){
        MoveList = dbc.getMoveData();
        return "printMoves";
    }
    public String getPlayers(){
        PlayerList = dbc.getPlayerData();
        return "printPlayers";
    }

    public String getNewname() {
        return newname;
    }

    public void setNewname(String newname) {
        this.newname = newname;
    }

    public String getNewpass() {
        return newpass;
    }

    public void setNewpass(String newpass) {
        this.newpass = newpass;
    }
    
    public void createPlayer(){
        if (dbc.createPlayer(this.newname, this.newpass))
            retmsg = "Success!";
        else retmsg = "Error: Player already exists";
    }
    
    public String createPage(){
        return "createUser";
    }
    
    public String toPage(int num){
        switch (num){
            case 1:
                return "createUser";
               
            case 2:
                return "searchGames";
                
            default:
                return "index";
        }
    }

    public String getRetmsg() {
        return retmsg;
    }

    public void setRetmsg(String retmsg) {
        this.retmsg = retmsg;
    }
    
    public String findGameById(){
        GameList = dbc.findGameById(searchId);
        return "printGames";
    }
}
