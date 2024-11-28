package TopologiaAnel;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;


public class ClientSocket implements Closeable { //Implementando closeable para fazer o proprio socket;
    private final Socket socket; //Socket padrão;

    protected Socket nextS;

    private String ip; //Host

    private final int port; //Porta de conexao

    public  int next; //Porta do proximo

    private final InetAddress inet; //Host

    public String login; //Nome do usuario;

    private  BufferedReader nextIn; //Ler mensagens do enviadas ou recebidas do cliente;

    private  PrintWriter nextOut; // Enviar mensagens do Cliente para o Servidor e vice versa;

    private final BufferedReader cin; //Ler mensagens do enviadas ou recebidas do cliente;

    private final PrintWriter cout; // Enviar mensagens do Cliente para o Servidor e vice versa;




    public ClientSocket(Socket socket) throws IOException { //Construtor do Socket;
        this.socket = socket;
        inet = socket.getInetAddress();
        this.port = socket.getPort();
        this.cin = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.cout = new PrintWriter(socket.getOutputStream(), true);
        switch (socket.getPort()){
            case 1111:
                this.login = "Whesley";
                this.next = 2222;
                break;
            case 2222:
                this.login = "Joao";
                this.next = 3333;
                break;
            case 3333:
                this.login = "Davi";
                this.next = 4444;
                break;
            case 4444:
                this.login = "Kevny";
                this.next = 1111;
                break;
            default: break;
        }
        System.out.println("Next: " + this.next);
        //nextS = new Socket("localhost", this.next);
        //this.nextIn = new BufferedReader(new InputStreamReader(nextS.getInputStream()));
        //this.nextOut = new PrintWriter(nextS.getOutputStream(), true);
    }


    public boolean nsendMensage(String str){
        nextOut.println(str);

        return !nextOut.checkError();
    }

    public String nreadMessage(){
        try {
            return nextIn.readLine();
        } catch (IOException e) {
            return null;
        }
    }
    public boolean sendMensage(String str){
        cout.println(str);

        return !cout.checkError();
    }

    public String readMessage(){
        try {
            return cin.readLine();
        } catch (IOException e) {
            return null;
        }
    }



    public String getLogin(){
        return this.login;
    }

    public void setLogin(String str){
        this.login = login;
    }

    public void setIp(String str){
        this.ip = str;
    }

    public String getIp(){
        return this.ip;
    }

    @Override
    public void close(){
        try {
            cin.close();
            cout.close();
            socket.close();
            nextS.close();
            nextIn.close();
            nextOut.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public boolean isClosed(){
        return socket.isClosed();
    }

    public String getHostAddress(){
        return socket.getInetAddress().getHostAddress();
    }

    public String getHostName() {
        return socket.getInetAddress().getHostName();
    }

    public int getLocalPort(){
        return socket.getLocalPort();
    }
    public int getPort(){
        return socket.getPort();
    }
}
