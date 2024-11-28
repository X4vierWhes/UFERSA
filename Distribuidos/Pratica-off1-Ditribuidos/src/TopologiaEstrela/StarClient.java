package TopologiaEstrela;

import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

public class StarClient implements Runnable{

    private StarSocket starSocket; //Socket principal da classe cliente;

    //Construtor:
    public StarClient(String host, int port) throws IOException {
        starSocket = new StarSocket(new Socket(host, port)); //Criar novo socket estrela;
        init(); //Iniciar processo do cliente;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    //Funções do cliente:

    private void init() {
        String login;
        Scanner cin = new Scanner(System.in);
        System.out.println("Login: ");
        login = cin.next();
        starSocket.login = login;
        starSocket.sendMsg(login);
        System.out.println("O cliente conectou ao servidor como " +
                starSocket.getLogin());
        System.out.println("Porta: " + starSocket.getPort());
        System.out.println("Porta local: " + starSocket.getLocalPort());
        System.out.println("BEM VINDO AO GRUPO! INICIE SUA CONVERSA:");
        System.out.println("*********COMANDOS***********");
        System.out.println("use @ e o nome de quem deseja mandar uma mensagem privada;");
        System.out.println("Digite FIM para desconectar do servidor.");

        new Thread(this).start();
        this.msgLoop();
        starSocket.close();
    }

    private void msgLoop() {
        String msg;
        Scanner cin = new Scanner(System.in);
        while(true){
            msg = cin.nextLine();
            if (!"FIM".equalsIgnoreCase(msg)){
                starSocket.sendMsg("1 " + starSocket.login + " -> " + msg);
                //System.out.println(msg);
            }else{
                break;
            }
        }
    }


    @Override
    public void run() {
        String msg;
        String[] info;
        String login;
        String mensagem;
        int index = 0;
        int marcador = 0;

        while(true){
            try {
                msg = starSocket.readMsg();
                if(msg != null){
                info = msg.split(" ");
                login = info[1];

                for(char a : msg.toCharArray()){
                    if(a == '>'){
                        marcador = index;
                    }
                    index++;
                }
                index = 0;
                mensagem = msg.substring(marcador + 2);
                    if(!"fim".equalsIgnoreCase(mensagem)){
                        System.out.println(login + ": " + mensagem);
                    }

                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

class InitClient{
    public static void main(String[] args) {
        try {
            new StarClient("localhost", 4000);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}