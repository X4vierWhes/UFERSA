package TopologiaAnel;

import java.io.IOException;
import java.net.Socket;
import java.util.*;

public class ImplServer implements Runnable {

    public ClientSocket clientSocket;

    public ClientSocket next;

    public Scanner s = null;


    public ImplServer(ClientSocket clientSocket) throws IOException {
        this.clientSocket = clientSocket;
        this.next = new ClientSocket(new Socket("localhost", clientSocket.next));
    }

    @Override
    public void run() {
        this.mensageLoop();
    }

    public void mensageLoop() {
        String msg;

        //Servidor recebendo mensagens dos clientes
        while(true) {
            //for(ClientSocket clientSocket : list) {
            //Retirando informações da mensagem
            msg = clientSocket.readMessage(); //Mensagem recebida
            String mensagem = "";
            String login = "";
            String[] infMsg = msg.split(" "); //segundo elemento do vetor sera login

            if (msg != null) {

                login = infMsg[1]; //login
                //Pegando inicio da mensagem.
                int index = 0;
                int escolha = 0;
                for (char i : msg.toCharArray()) {
                    if (i == '>') {
                        escolha = index;
                    }
                    index++;
                }

                mensagem = msg.substring(escolha + 2);
            }

            if ((msg != null && !("fim".equalsIgnoreCase(mensagem)))) {
                if (infMsg[0].equals("1")) {
                    System.out.println("Mensagem recebida de " +
                            " /Login: @" + login +
                            " -> " + mensagem);
                } else {
                    System.out.println("Mensagem de destinatario: " + login + " Encamihada por "
                            + infMsg[7] + " Conteudo: " + mensagem);
                }

                //clientSocket.sendMensage(msg);

                if (destinationToAll(mensagem)) { //Funçao que verifica se alguem foi mencionado no inicio da mensagem
                    try {
                        this.sendMsgToAll(mensagem, login); //Enviar mensagens para todos;
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                } else {
                    this.sendMsgToOne(mensagem, login); //Enviar mensagens so para uma pessoa;
                }

            } else {
                break;
            }
        }

    }

    private boolean destinationToAll(String msg) {
        if (msg.charAt(0) != '@') { //Se primeiro caracter da mensagem for um @, alguem foi mencionado no chat e a mensagem sera privada;
            return true;
        } else {
            return false;
        }
    }


    public void sendMsgToAll(String msg, String login) throws IOException { //Broadcast
        //remetente.sendMensage(remetente.getLogin()+ " :" +msg);
        //Como a mensagem é para  todos, deve percorrer ate voltar ao remetente;
        //Escreverá menagem e repassara pro proximo.
        clientSocket.sendMensage( login + " -> " + msg);

        //next = new ClientSocket(new Socket("localhost", clientSocket.next));
        next.sendMensage("2 " + login + " = " + "Remetente " + " Reenviada por " + clientSocket.getLogin() +
                " Conteudo -> " + msg);
        //next.close();

    }


    public void sendMsgToOne(String msg, String login) { //Unicast
        /*Se mensagem for individual,verficara se é para si mesmo.*/
        System.out.println("passou");
        String[] split = msg.split(" ");
        String marcacao = split[0].substring(1);
        if(clientSocket.getLogin().equalsIgnoreCase(marcacao)){
            clientSocket.sendMensage(  login + " -> " + msg);
            System.out.println(login + ": " + msg);
        }else{
            System.out.println("Mensagem para outro destinatario, enviada para o proximo a direita");
            next.sendMensage("2 " + login + " = " + "Remetente " + " Reenviada por " + clientSocket.getLogin() +
                    " Conteudo -> " + msg);
        }
    }


}
