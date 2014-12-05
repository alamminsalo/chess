/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
/**
 *
 * @author antti
 */
public class ServerDatabaseConnector implements java.io.Serializable{
    String dburl;
    String dbuser;
    String dbpass;
    
    Connection conn;

    public ServerDatabaseConnector(){
        dburl = "jdbc:mysql://localhost/chess";
        dbuser = "antti";
        dbpass = "pass";
        
        conn = null;
        
        connect();
    }
    
    public void connect(){
        try {
            Class.forName("com.mysql.jdbc.Driver");
            
            System.out.println("Attempting connection..");
            conn = DriverManager.getConnection(dburl, dbuser, dbpass);
            
            //System.out.println("Creating statement");
            //statement = conn.createStatement();

        } catch(Exception e) {
            e.printStackTrace();
        }
    }
    
    public void closeConn() throws SQLException{
        if (conn != null)
            conn.close();
    }
        
    public ServerDatabaseConnector(String dburl, String dbuser, String dbpass){
        dburl = dburl;
        dbuser = dbuser;
        dbpass = dbpass;
        
        conn = null;
        
        connect();
    }
    
    public ArrayList<Player> getPlayerData(){
        ArrayList<Player> PlayerList = null;
        ResultSet result;
        PreparedStatement statement;
        try {

            String query = "select * from Player";
            statement = conn.prepareStatement(query);
            result = statement.executeQuery();
            
            PlayerList = new ArrayList<Player>();
            
            while (result.next()){
                PlayerList.add(new Player(
                        result.getInt("Player_Id"),
                        result.getString("Player_Name"),
                        result.getInt("Games_Total"),
                        result.getInt("Games_Wins"),
                        result.getInt("Games_Draws"))
                );
            }

        } catch(Exception e) {
            e.printStackTrace();
        }
        return PlayerList;
    }
    
    public ArrayList<Game> getGameData(){
        ArrayList<Game> GameList = null;
        ResultSet result;
        PreparedStatement statement = null;
        try {
            String query = "select * from Game";
            statement = conn.prepareStatement(query);
            result = statement.executeQuery();
            
            GameList = new ArrayList<Game>();
            
            while (result.next()){
                GameList.add(new Game(
                        result.getInt("Game_Id"),
                        getName(result.getInt("Player_White_Id")),
                        getName(result.getInt("Player_Black_Id")),
                        result.getInt("Turns"),
                        result.getString("Winner")
                ));
            }         
            statement.close();

        } catch(Exception e) {
            e.printStackTrace();
        }
        return GameList;
    }
    
    public ArrayList<Move> getMoveData(){
        ArrayList<Move> MoveList = null;
        ResultSet result;
        PreparedStatement statement;
        try {
            String query = "select * from GameMoves";
            statement = conn.prepareStatement(query);
            result = statement.executeQuery();
            
            MoveList = new ArrayList<Move>();
            
            while (result.next()){
                MoveList.add(new Move(
                        result.getInt("Game_Id"),
                        result.getString("Move"),
                        result.getString("Team"),
                        result.getString("Piece"),
                        result.getString("Status"),
                        result.getInt("Turn")
                ));
            }    

        } catch(Exception e) {
            e.printStackTrace();
        }
        return MoveList;
    }
    
    private String getName(int playerId){
        ResultSet result;
        PreparedStatement statement;
        String name = "";
        System.out.println("Searching name..");
        try{
            String query = "select Player_Name from Player where Player_Id=?";
            statement = conn.prepareStatement(query);
            statement.setInt(1, playerId);
            result = statement.executeQuery();
            if (result.first()){
                name = result.getString("Player_Name");
            }
            result.close();
            statement.close();
        }catch(Exception e) {
                e.printStackTrace();
            }
        System.out.println("Name got: "+name);
        return name;
    }
    
    int findPlayerByName(String name){
        ResultSet result;
        PreparedStatement statement;
        System.out.println("Searching player from db..");
        try{
            String query = "select Player_Name from Player where Player_Name=?";
            statement = conn.prepareStatement(query);
            statement.setString(1, name);
            result = statement.executeQuery();
            if (result.first()){
                System.out.println("Found match!");
                return 0;
            }
            }catch(Exception e) {
                e.printStackTrace();
            }
        return -1;
    }
    
    public  ArrayList<Game> findGameById(int GameId){
        ArrayList<Game> GameList = null;
        ResultSet result;
        PreparedStatement statement = null;
        System.out.println("Searching game with id="+GameId);
        try {
            String query = "select * from Game where Game_Id=?";
            statement = conn.prepareStatement(query);
            statement.setInt(1, GameId);
            result = statement.executeQuery();
            
            GameList = new ArrayList<Game>();
            
            while (result.next()){
                GameList.add(new Game(
                        result.getInt("Game_Id"),
                        getName(result.getInt("Player_White_Id")),
                        getName(result.getInt("Player_Black_Id")),
                        result.getInt("Turns"),
                        result.getString("Winner")
                ));
            }         
            statement.close();
            statement.close();

        } catch(Exception e) {
            e.printStackTrace();
        }
        return GameList;
    }
    
    public boolean createPlayer(String name, String pass){
        PreparedStatement statement;
        System.out.println("Attempting to create player if new..");
        if (findPlayerByName(name) == -1){
            try{
                String query = "insert into Player(Player_Name,md5_Hash) values (?,?)";
                statement = conn.prepareStatement(query);
                statement.setString(1, name);
                statement.setString(2, getHash(pass));
                statement.executeUpdate();
                return true;
            }catch(Exception e) {
                e.printStackTrace();
            }
        }
        return false;
    }
    
    public int createGame(String name1, String name2){
        //createPlayer(name1);
        //createPlayer(name2);
        ResultSet result;
        PreparedStatement statement;
        try{
            String query = "insert into Game (Player_White_Id,Player_Black_Id,Turns,Date) "
                    + "values ((select Player_Id from Player where Player_Name=?)"
                    + ",(select Player_Id from Player where Player_Name=?),"
                    + "0,curdate())";
            statement = conn.prepareStatement(query);
            statement.setString(1,name1);
            statement.setString(2,name2);
            statement.executeUpdate();

            query = "select last_insert_id()";
            statement = conn.prepareStatement(query);
            result = statement.executeQuery();

            int val = 0;
            while (result.next()){
                val = result.getInt("last_insert_id()");
                System.out.println(val);
            }
            return val;

        }catch(Exception e) {
            e.printStackTrace();
        }
        return -1;
    }
    
    public int finishGame(int GameId, int turns, String winner, String whitename, String blackname){
        PreparedStatement statement;
        try{
            String query = "update Game set Turns=?, Winner=? where Game_Id=?";
            statement = conn.prepareStatement(query);
            statement.setInt(1, turns);
            statement.setString(2,winner);
            statement.setInt(3,GameId);
            statement.executeUpdate();
            
            query = "update Player set Games_Total=Games_Total+1 where Player_Name=? or Player_Name=?";
            statement = conn.prepareStatement(query);
            statement.setString(1,whitename);
            statement.setString(2,blackname);
            statement.executeUpdate();
            
            if (!winner.equals("draw")){
                query = "update Player set Games_Wins=Games_Wins+1 where Player_Name=?";
                statement = conn.prepareStatement(query);
                statement.setString(1,(winner.equals("white")) ? whitename : blackname);
                statement.executeUpdate();
            }
            else{
                query = "update Player set Games_Draws=Games_Draws+1 where Player_Name=? or Player_name=?";
                statement.setString(1,whitename);
                statement.setString(2,blackname);
                statement.executeUpdate();
            }
            
            return 0;
            }catch(Exception e) {
                e.printStackTrace();
            }
        return -1;
    }
    
    public int insertMove(int GameId,String move,String team,String piece,String status,int turn){
        PreparedStatement statement;
        try{
            String query = "insert into GameMoves (Game_Id,Move,Team,Piece,Status,Turn) values "
                    + "((select Game_Id from Game where Game_Id=?),?,?,?,?,?)";
            statement = conn.prepareStatement(query);
            statement.setInt(1,GameId);
            statement.setString(2,parseMove(move));
            statement.setString(3,team);
            statement.setString(4,piece);
            statement.setString(5,status);
            statement.setInt(6,turn);
            statement.executeUpdate();
            return 0;
            }catch(Exception e) {
                e.printStackTrace();
            }
        return -1;
    }
    
    public boolean loginPlayer(String name, String pass){
        ResultSet result;
        PreparedStatement statement;
        System.out.println("Searching player from db..");
        try{
            String query = "select Player_Id from Player where Player_Name=? and md5_Hash=?";
            statement = conn.prepareStatement(query);
            statement.setString(1, name);
            statement.setString(2, getHash(pass));
            result = statement.executeQuery();
            if (result.first()){
                System.out.println("Player "+name+" logged in");
                return true;
            }
            }catch(Exception e) {
                e.printStackTrace();
            }
        return false;
    }
    
    private String getHash(String pass){
        try{
            MessageDigest md = MessageDigest.getInstance("MD5");
            md.update(pass.getBytes());
            
            byte[] bytes = md.digest();
            StringBuilder sb = new StringBuilder();
            for (int i=0; i<bytes.length; i++){
                sb.append(Integer.toString((bytes[i] & 0xff) + 0x100, 16).substring(1));
            }
            return sb.toString();
        }
        catch (NoSuchAlgorithmException e)
        {
            e.printStackTrace();
        }
        
        return null;
    }
    
    private String parseMove(String move){
        String parsedstr = "";
        
        parsedstr += (char)((int)move.charAt(0)+49);
        parsedstr += move.charAt(1);
        parsedstr += (char)((int)move.charAt(2)+49);
        parsedstr += move.charAt(3);
        
        return parsedstr;
    } 
}
