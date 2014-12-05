/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Controller;

import java.io.IOException;

/**
 *
 * @author antti
 */
public class Test {
    
    public static void main(String []args) throws IOException, InterruptedException{
        //ServerDatabaseConnector serverdbc = new ServerDatabaseConnector();
        //serverdbc.getData();
        Server ssc = new Server(3333);
        ssc.closeDBConnection();
    }
}
