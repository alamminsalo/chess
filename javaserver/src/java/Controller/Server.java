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
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *
 * @author antti
 */
public class Server extends ServerSocket {
    ServerDatabaseConnector dbconn;
    
    public Server(int port) throws IOException, InterruptedException{
        super(port);
        
        System.out.println("Starting dbconnector..");
        dbconn = new ServerDatabaseConnector();
        dbconn.connect();
        
        System.out.println("Testing DB Connection...");
        if (dbconn.findPlayerByName("John Doe") != -1)
            System.out.println("DB Connection OK");
        else System.out.println("DB Connection Error");
        
        System.out.println("Initialized server");
        listen();
    }
    
    public void startThread(Socket s1, Socket s2, String name1, String name2) throws IOException, InterruptedException{
        Thread t1 = new ListenerThread(this,dbconn,s1,s2,name1,name2);
        
        t1.start();
        
        //Socket cl_socket[] = new Socket[2];

        //listen(cl_socket[0], cl_socket[1]);
    }
    
    public void listen() throws IOException, InterruptedException{
        
        while (true){
                Socket sock_pl1 = null;
                Socket sock_pl2 = null;
                String whiteName = null;
                String blackName = null;
                PrintWriter out1 = null;
                PrintWriter out2 = null;
                BufferedReader in1 = null;
                BufferedReader in2 = null;
                boolean s1_connected = false;
                boolean s2_connected = false;
                String pass = null;
            while(!(s1_connected && s2_connected)){
                
                if (!s1_connected){
                    System.out.println("Waiting for client1...");
                    while (true){
                        sock_pl1 = accept();
                        System.out.println("Accepted client1");
                        out1 = new PrintWriter(sock_pl1.getOutputStream(),true);
                        in1 = new BufferedReader(new InputStreamReader(sock_pl1.getInputStream()));

                        System.out.println("Waiting for credentials..");
                        whiteName = in1.readLine();
                        pass = in1.readLine();

                        if (!dbconn.loginPlayer(whiteName.trim(), pass.trim())){
                            out1.println("LOGIN_ERROR");
                            System.out.println("False credentials");
                        }
                        else {
                            out1.println("LOGIN_OK");
                            break;
                        }
                    }
                    System.out.println("Client1 connected.");
                }
                
                if (!s2_connected){
                    System.out.println("Waiting for client2...");
                    while (true){
                        sock_pl2 = accept();

                        out2 = new PrintWriter(sock_pl2.getOutputStream(),true);
                        in2 = new BufferedReader(new InputStreamReader(sock_pl2.getInputStream()));

                        blackName = in2.readLine();
                        pass = in2.readLine();
                        if (!dbconn.loginPlayer(blackName.trim(), pass.trim())){
                            out2.println("LOGIN_ERROR");
                        }
                        else {
                            out2.println("LOGIN_OK");
                            break;
                        }
                    }
                    System.out.println("Client2 connected.");
                }
                
                
                out1.println("PING");
                System.out.println("Sent PING to client 1..");
                if (in1.readLine() == null){
                    System.out.println("CLIENT 1 IS OFFLINE");
                    if (s2_connected)
                        out2.println("CLOSE_CL");
                    s1_connected = false;
                }
                else{
                    System.out.println("CLIENT 1 RESPONDED");
                    s1_connected = true;
                }
                
                out2.println("PING");
                System.out.println("Sent PING to client 2..");
                if (in2.readLine() == null){
                    System.out.println("CLIENT 2 IS OFFLINE");
                    if (s1_connected)
                        out1.println("CLOSE_CL");
                    s2_connected = false;
                }
                else {
                    System.out.println("CLIENT 2 RESPONDED");
                    s2_connected = true;
                }
            }

            System.out.println("Moving to thread...");
            startThread(sock_pl1,sock_pl2,whiteName,blackName);
        }
    }
    
    public int closeDBConnection(){
        try {
            dbconn.closeConn();
        } catch (SQLException ex) {
            Logger.getLogger(Server.class.getName()).log(Level.SEVERE, null, ex);
        }
        return 0;
    }
}
