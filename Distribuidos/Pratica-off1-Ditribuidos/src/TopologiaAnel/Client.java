package TopologiaAnel;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Client{

    public ClientSocket clientSocket;

    public ClientSocket next;

    public void run() throws IOException {

        System.out.println("HostAddress = " + clientSocket.getHostAddress());
        System.out.println("HostName = " + clientSocket.getHostName());

        System.out.println(clientSocket.getLogin() + " " + clientSocket.getIp());


        ImplClient c = new ImplClient(clientSocket);
        Thread t = new Thread(c);
        t.start();

    }


    public Client(String host, int port, int n){
        try {
            clientSocket = new ClientSocket(new Socket(host, port));
            clientSocket.setIp(host);
            this.run();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}

class Client1{
    public static void main(String[] args) {
        new Client("localhost", 2222, 3333); //2222
    }
}

class Client2{
    public static void main(String[] args) {
        new Client("localhost", 3333, 4444); //2222
    }
}

class Client3{
    public static void main(String[] args) {
        new Client("localhost", 4444, 1111); //2222
    }
}

class Client4{
    public static void main(String[] args) {
        new Client("localhost", 1111, 2222); //2222
    }
}