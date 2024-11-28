package TopologiaAnel;

import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

public class ImplClient implements Runnable{

    private final ClientSocket clientSocket;
    private ClientSocket next;

    public ImplClient(ClientSocket clientSocket) throws IOException {
        this.clientSocket = clientSocket;
        this.next = new ClientSocket(new Socket("localhost", clientSocket.next));
    }

    @Override
    public void run() {
        System.out.println("O cliente conectou ao servidor como " +
                clientSocket.getLogin());
        System.out.println("Porta: " + clientSocket.getPort());
        System.out.println("Porta local: " + clientSocket.getLocalPort());
        System.out.println("BEM VINDO AO GRUPO! INICIE SUA CONVERSA:");
        System.out.println("*********COMANDOS***********");
        System.out.println("use @ e o nome de quem deseja mandar uma mensagem privada;");
        System.out.println("Digite FIM para desconectar do servidor.");


        new Thread(this::msgLoop).start();
        this.sendMsg();




        clientSocket.close();

        System.out.println("Voce desconectou.");

    }


    protected void sendMsg(){
        Scanner teclado = new Scanner(System.in);
        String msg;
        boolean connect = true;
        while(connect) {
            msg = teclado.nextLine();
            if (!msg.equalsIgnoreCase("fim")) {
                //clientSocket.nsendMensage(msg);

                clientSocket.sendMensage("1 " + clientSocket.getLogin() + " -> " + msg);
                //next.sendMensage(clientSocket.getLogin() + " -> " + msg);
            } else {
                connect = false;
            }
        }
    }

    protected void msgLoop() {
        String msg;
        boolean connect = true;
        while(connect) {
            if ((msg = clientSocket.readMessage()) != null && !msg.equalsIgnoreCase("fim")) {
                if (msg.charAt(0) != '@') {
                    System.out.println(msg);
                } else {
                    String[] temp = msg.split(" ");
                    String login = temp[0];
                    login = login.substring(1, login.length());
                    if (login.equalsIgnoreCase(clientSocket.getLogin())) {
                        System.out.println(msg);
                    } else {
                        //clientSocket.nsendMensage(msg);
                    }
                }
            } else {
                connect = false;
            }
        }

    }
}
