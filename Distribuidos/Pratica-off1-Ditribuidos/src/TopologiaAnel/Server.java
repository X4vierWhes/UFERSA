package TopologiaAnel;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;

public class Server{

    ServerSocket serverSocket;
    ClientSocket clientSocket;

    String [] names = {"Whesley", "Joao", "Davi", "Kevny"};

    int port;

    int next;

    public Server(int port){
        this.port = port;
        this.run();
    }

    public Server(int port, int next){
        this.port = port;
        this.next = next;
        this.run();
    }


    public void run() {
        try {
            serverSocket = new ServerSocket(this.port); //Iniciando socket do servidor;

            System.out.println("Servidor rodando na porta " +
                    serverSocket.getLocalPort());
            System.out.println("HostAddress = " +
                    InetAddress.getLocalHost().getHostAddress());
            System.out.println("HostName = " +
                    InetAddress.getLocalHost().getHostName());

            System.out.println("Aguardando conexão do cliente...");

            this.connectionLoop(); //Entrando em loop que conectara os clientes

        } catch (IOException e) {
           e.printStackTrace();
        }
    }

    private void connectionLoop() throws IOException {
        //Conexão com cliente
        //String msg;

            clientSocket = new ClientSocket(serverSocket.accept());
            switch (clientSocket.getLocalPort()) {
                case 1111:
                    clientSocket.login = names[0];
                    clientSocket.next = 2222;
                    break;
                case 2222:
                    clientSocket.login = names[1];
                    clientSocket.next = 3333;
                    break;
                case 3333:
                    clientSocket.login = names[2];
                    clientSocket.next = 4444;
                    break;
                case 4444:
                    clientSocket.login = names[3];
                    clientSocket.next = 1111;
                    break;
                default: break;

            }

            System.out.print(" Conectado como -> " + clientSocket.getLogin());
            System.out.println();

            ImplServer server = new ImplServer(clientSocket);
            Thread t = new Thread(server);
            t.start();

    }
}



class server1{
    public static void main(String[] args) {
        new Server(2222); //2222
    }
}

class server2{
    public static void main(String[] args) {
        new Server(3333); //2222
    }
}

class server3{
    public static void main(String[] args) {
        new Server(4444); //2222
    }
}

class server4{
    public static void main(String[] args) {
        new Server(1111); //2222
    }
}