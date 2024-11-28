package TopologiaEstrela;

import java.io.*;
import java.net.Socket;

public class StarSocket implements Closeable {

    private Socket socket; //Socket principal

    private int port; //Porta do socket

    public String login;

    private final BufferedReader cin; //Ler mensagens do enviadas ou recebidas do cliente;

    private final PrintWriter cout; // Enviar mensagens do Cliente para o Servidor e vice versa;

    public StarSocket(Socket socket) throws IOException {
        this.socket = socket;
        this.port = socket.getPort();
        this.cin = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.cout = new PrintWriter(socket.getOutputStream(), true);
    }

    public boolean sendMsg(String msg){
        cout.println(msg);

        return !cout.checkError();
    }

    public String readMsg() throws IOException {
        return cin.readLine();
    }



    public int getPort(){
        return socket.getPort();
    }

    public int getLocalPort(){
        return socket.getLocalPort();
    }

    public String getHostAddress(){
        return socket.getInetAddress().getHostAddress();
    }

    public String getHostName() {
        return socket.getInetAddress().getHostName();
    }

    public boolean isClosed(){
        return socket.isClosed();
    }

    @Override
    public void close(){
        try {
            socket.close();
            cin.close();
            cout.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String getLogin() {
        return this.login;
    }
}
