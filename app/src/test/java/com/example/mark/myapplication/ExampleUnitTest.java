package com.example.mark.myapplication;

import org.junit.Test;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.Scanner;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() throws Exception {
        assertEquals(4, 2 + 2);
//        Socket socket = new Socket("172.16.14.115", 12345);

        Socket socket = new Socket();
        SocketAddress socketAddress = new InetSocketAddress("127.0.0.1", 12345);
        socket.connect(socketAddress);

        System.out.printf("socket is connected %b\n", socket.isConnected());
        OutputStream outputStream = socket.getOutputStream();
        PrintWriter writer = new PrintWriter(outputStream);


        writer.print("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww");
        writer.close();

        InputStream inputStream = socket.getInputStream();
        Scanner in = new Scanner(inputStream);
        while (in.hasNext()){
            String line = in.nextLine();
            System.out.println(line);
        }

    }
}