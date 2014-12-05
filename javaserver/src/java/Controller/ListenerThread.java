/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import static java.lang.Thread.sleep;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author antti
 */
public class ListenerThread extends Thread {
    ServerSocket servsocket = null;
    ServerDatabaseConnector dbconn = null;
    Socket sock_pl1;
    Socket sock_pl2;
    String whiteName;
    String blackName;
    String status;
    String piece;
    String message;
    
    
    public ListenerThread(ServerSocket servsock, ServerDatabaseConnector dbc, Socket s1, Socket s2,String name1, String name2){
        servsocket = servsock;
        dbconn = dbc;
        sock_pl1 = s1;
        sock_pl2 = s2;
        whiteName = name1;
        blackName = name2;
        
    }
    
    @Override
    public void run(){
        try{
            PrintWriter out1 = new PrintWriter(sock_pl1.getOutputStream(),true);
            PrintWriter out2 = new PrintWriter(sock_pl2.getOutputStream(),true);
            BufferedReader in1 = new BufferedReader(new InputStreamReader(sock_pl1.getInputStream()));
            BufferedReader in2 = new BufferedReader(new InputStreamReader(sock_pl2.getInputStream()));

            System.out.println("Starting listener...");
        
            out1.println("WHITE");
            out2.println("BLACK");

            int turn = 0;

            int GameId = dbconn.createGame(whiteName, blackName);
            System.out.println("GameId is "+GameId);
            if (GameId == -1) {
                System.out.println("ERRORERROR");
                return;
            }



            System.out.println("Assigned teams. Starting..");
            while(sock_pl1.isConnected() && sock_pl2.isConnected()){
     
                System.out.println("Waiting move from player 1...");
                message = in1.readLine();
                if (message == null){
                    out2.println("CLOSE_CL");
                    System.out.println("CLIENT 1 DROPPED");
                    break;
                }
                System.out.println("Sending move white -> black :"+message);
                out2.println(message.trim());

                piece = in1.readLine();
                if (piece == null){
                    System.out.println("CLIENT 1 DROPPED");
                    out2.println("CLOSE_CL");
                    break;
                }
                status = in1.readLine();
                if (status == null){
                    System.out.println("CLIENT 1 DROPPED");
                    out2.println("CLOSE_CL");
                    break;
                }
                System.out.println(piece+", "+status);
                System.out.println("Got all from cl1");

                dbconn.insertMove(GameId, message.trim(), "white", piece, status, ++turn);
                if (status.equals("STALEMATE") || status.equals("CHECKMATE")){
                    break;
                }

                System.out.println("Waiting move from player 2...");
                message = in2.readLine();
                if (message == null){
                    System.out.println("CLIENT 2 DROPPED");
                    out1.println("CLOSE_CL");
                    break;
                }
                System.out.println("Sending move black -> white :"+message);
                out1.println(message.trim());

                piece = in2.readLine();
                if (piece == null){
                    System.out.println("CLIENT 2 DROPPED");
                    out1.println("CLOSE_CL");
                    break;
                }
                status = in2.readLine();
                if (status == null){
                    System.out.println("CLIENT 2 DROPPED");
                    out1.println("CLOSE_CL");
                    break;
                }
                System.out.println(piece+", "+status);
                System.out.println("Got all from cl2");
                
                dbconn.insertMove(GameId, message.trim(), "black", piece.trim(), status.trim(), ++turn);
                if (status.equals("STALEMATE") || status.equals("CHECKMATE")){
                    break;
                }
            }
            String winner = "STALEMATE".equals(status) ? "draw" : turn % 2 == 0 ? "black" : "white";
            dbconn.finishGame(GameId, turn, winner, whiteName, blackName);

            try {
                sleep(5000);
            } catch (InterruptedException ex) {
                Logger.getLogger(Server.class.getName()).log(Level.SEVERE, null, ex);
            }
            out1.println("CLOSE_SV");
            out2.println("CLOSE_SV");

            System.out.println("ListenerThread closing...");
            sock_pl1.close();
            sock_pl2.close();
        } catch (IOException ex) {
            Logger.getLogger(ListenerThread.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
