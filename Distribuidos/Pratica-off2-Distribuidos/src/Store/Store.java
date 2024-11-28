package Store;

import Main.Client;
import Main.Vehicle;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;

public class Store implements StoreInterface{
    private HashMap<String, Vehicle> store;

    public Store(){
        this.store = new HashMap<>();
    }

    public HashMap<String, Vehicle> getStore() {
        return store;
    }

    public void setStore(HashMap<String, Vehicle> store) {
        this.store = store;
    }

    @Override
    public boolean deleteCar(String renavam) throws RemoteException {
        try{
            this.store.remove(renavam);
            return true;
        }catch (Exception e){
            System.err.println("Não foi possivel deletar carro do banco de dados.");
            e.printStackTrace();
        }
        return false;
    }

    @Override
    public Vehicle searchCar(String renavam) throws RemoteException {
        return store.get(renavam);
    }

    @Override
    public boolean editCar(String renavam) throws RemoteException {
        return false;
    }

    @Override
    public Client buyCar(String renavam, Client client) throws RemoteException {
        Vehicle buy = this.store.get(renavam);
        if(buy != null && client.getWallet() >= buy.getPrice()){
            client.buy(buy);
            client.attWallet(buy.getPrice());
            this.store.remove(renavam);
            client.setBuy(true);
            return client;
        }
        return client;
    }

    @Override
    public boolean addCar(Vehicle a) throws RemoteException {
        try{
            this.store.put(a.getRenavam(), a);
            return true;
        }catch (Exception e){
            System.err.println("Não foi possivel adicionar no banco de dados.");
            e.printStackTrace();
        }
        return false;
    }

    @Override
    public List<Vehicle> listAll() throws RemoteException {
        return new ArrayList<>(this.store.values());
    }

    @Override
    public List<Vehicle> listModel(String model) throws RemoteException {
        List<Vehicle> models = new ArrayList<>();
        for(Vehicle a: this.store.values()){
            if(a.getModel().equalsIgnoreCase(model)){
                models.add(a);
            }
        }
        return models;
    }

    @Override
    public List<Vehicle> listCategory(String category) throws RemoteException {
        List<Vehicle> categorys = new ArrayList<>();

        for(Vehicle a : this.store.values()){
            if(a.getCategory().equalsIgnoreCase(category)){
                categorys.add(a);
            }
        }

        return categorys;
    }

    @Override
    public int size() throws RemoteException {
        return store.size();
    }


    @Override
    public String oi() throws RemoteException {
        return "Store conectado!";
    }

    @Override
    public void init() throws RemoteException {
        //if(this.store == null) {
        this.store = new HashMap<>();
        this.store.put("123900", new Vehicle("RX-7", "123900", 2024, 22000.0));
        this.store.put("123901", new Vehicle("Civic", "123901", 2024, 64000.0));
        this.store.put("123902", new Vehicle("Ford-Ka", "123902", 2007, 3000.0));
        this.store.put("123903", new Vehicle("Prisma", "123903", 2007, 10000.0));
        this.store.put("123904", new Vehicle("Ethios", "123904", 2007, 9000.0));
        this.store.put("123905", new Vehicle("Corolla", "123905", 2007, 75000.0));
        this.store.put("123906", new Vehicle("Civic", "123906", 2024, 18000.0));
        this.store.put("123907", new Vehicle("Ford-Ka", "123907", 2007, 3800.0));
        this.store.put("123908", new Vehicle("Ethios", "123908", 2007, 8900.0));

        System.err.println("Loja iniciado.");
        //}
    }

    public static void main(String[] args) {
        try{
            Store refObjRemoto = new Store();

            StoreInterface sklt = (StoreInterface) UnicastRemoteObject.exportObject(refObjRemoto, 6000);
            LocateRegistry.createRegistry(Registry.REGISTRY_PORT + 2);
            Registry registro = LocateRegistry.getRegistry(Registry.REGISTRY_PORT + 2);
            registro.bind("Store", sklt);

            System.err.println("Store iniciado!");

        }catch (Exception e){
            System.err.println("Servidor: " + e.toString());
            e.printStackTrace();
        }
    }
}
