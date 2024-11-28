package Autentication;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashMap;


public class Autentication implements AutenticationInterface {

    private HashMap<String, String> users;

    public Autentication(){
        this.users = new HashMap<>();
    }

    public static void main(String[] args) {
        try{
            Autentication refObjRemoto = new Autentication();

            AutenticationInterface sklt = (AutenticationInterface) UnicastRemoteObject.exportObject(refObjRemoto, 5000);
            LocateRegistry.createRegistry(Registry.REGISTRY_PORT + 1);
            Registry registro = LocateRegistry.getRegistry(Registry.REGISTRY_PORT + 1);
            registro.bind("Autentication", sklt);

            System.err.println("Autenticaçao iniciado!");

        }catch (Exception e){
            System.err.println("Servidor: " + e.toString());
            e.printStackTrace();
        }
    }

    @Override
    public boolean connect(String login, String password) {
        if(users.containsKey(login) && users.get(login).equalsIgnoreCase(password)){
            return true;
        }
        return false;
    }

    @Override
    public boolean signUp(String login, String password) throws RemoteException {
        try {
            users.put(login, password);
            return true;
        }catch (Exception e){
            System.err.println("Não foi possivel cadastrar no sistema.");
            e.printStackTrace();
            return false;
        }
    }

    public String oi(){
        return "Autentication conectado!";
    }

    @Override
    public void init() throws RemoteException {
        //if(this.users == null) {
            this.users = new HashMap<>();

            this.users.put("admin", "admin");
            this.users.put("Whesley", "1234");
            this.users.put("Thiago", "6666");
            this.users.put("Davi", "7777");
            this.users.put("Kevny", "8888");
            this.users.put("Ryan", "9999");
            this.users.put("Valentina", "1010");
            this.users.put("Vinicius", "1111");
            this.users.put("Sarah", "1212");
            this.users.put("Joao Vitor", "1313");

            System.err.println("Autenticação iniciado.");
        //}
    }
}
