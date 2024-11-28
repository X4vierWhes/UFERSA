package TopologiaEstrela;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class StarServer{

    private ServerSocket serverSocket;

    private List<StarSocket> clientsList;

    public StarServer(int port) throws IOException {
        this.serverSocket = new ServerSocket(port);
        this.clientsList = new ArrayList<>();
        this.start();
    }

    private void start() {
        try {

            System.out.println("Servidor rodando na porta " +
                    serverSocket.getLocalPort());
            System.out.println("HostAddress = " +
                    InetAddress.getLocalHost().getHostAddress());
            System.out.println("HostName = " +
                    InetAddress.getLocalHost().getHostName());

            System.out.println("Aguardando conexão do cliente...");

            this.connectionLoop(); //Entrando em loop que conectara os clientes

            serverSocket.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void connectionLoop() throws IOException {
        while(true){
            try {
                StarSocket st = new StarSocket(serverSocket.accept());
                //Primeira mensagem enviada será o login
                st.login = st.readMsg(); //Setando o login
                System.out.println("Cliente com Login: " + st.login + " conectado.");



                ///////////////////////////////////////////////
                new Thread(() -> msgLoop(st)).start();//Iniciando thread de msgLoop

                clientsList.add(st); //Adicionando elementos na lista de clientes do servidor;
                /*for(StarSocket a : clientsList){
                    System.out.println(a.login);
                }*/
            }catch (SocketException e){
                e.printStackTrace();
            }

        }
    }



    private void msgLoop(StarSocket starSocket){
        String msg;
        String mensagem;
        String login;
        String[] info;
        int marcador = 0;
        int index = 0;
        //Retirando informações da mensagem;
        //Mensagens são enviadas com 2 padrões:
        //(Marcador) (Remetente) -> (Mensagem)
        //(Marcador) (Remetente) REMETENTE REENVIADA POR SERVIDOR -> (MENSAGEM)
        //Servidor envia a mensagem utilizando o segundo padrão;

        //System.out.println("Entrou na msgloop");

        while(true){
            try {
                msg = starSocket.readMsg(); //Lendo mensagem do teclado;
                if(msg != null){
                    info = msg.split(" "); //Separando informações;
                    login = info[1]; //Login sempre estará no indice 1 do vetor;
                    for(char a : msg.toCharArray()){
                        if(a == '>'){
                            marcador = index;//Marca inicio da mensagem;
                        }
                        index++;
                    }
                    index = 0;
                    mensagem = msg.substring(marcador+2); //Retirando conteudo da mensagem;
                    System.out.println("Mensagem recebida de " + login + " -> " + mensagem);
                    if(mensagem.charAt(0) == '@'){ //Se primeiro caracter da mensagem for um '@', a mensagem será enviada para somente uma pessoa
                        this.unicast(login,mensagem); //Unicast
                    }else{ //Senao, será enviada para todos;
                        this.broadcast(login, mensagem);
                    }
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void broadcast(String login, String mensagem) {
        Iterator<StarSocket> iterator = clientsList.iterator(); //Usando iterator pra possivel remorção de cliente da lista
        //System.out.println("Entrou na broadcast");
        while (iterator.hasNext()){
            StarSocket st = iterator.next();
            if(!st.login.equalsIgnoreCase(login)){
                if(st.sendMsg("2 " + login + " passada pelo Servidor com conteudo -> " + mensagem)){
                    System.out.println("Mensagem repassada para " + st.login);
                }else{
                    iterator.remove();
                }
            }
        }
    }

    private void unicast(String login, String mensagem) {
        Iterator<StarSocket> iterator = clientsList.iterator(); //Usando iterator para possivel remorção da lista

        String[] info = mensagem.split(" ");

        String destinatario = info[0].substring(1);


        while(iterator.hasNext()){
            StarSocket st = iterator.next();

            if(st.login.equalsIgnoreCase(destinatario)){
                if(st.sendMsg("2 " + login + " passada pelo servidor com conteudo -> " + mensagem)){
                    System.out.println("Mensagem unicast passada para " + destinatario + " por " + login);
                }else{
                    iterator.remove();
                }
            }

        }
    }
}

class InitServer{
    public static void main(String[] args){
        try {
            new StarServer(4000);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
