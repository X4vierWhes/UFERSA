package Store;

import Main.Client;
import Main.Vehicle;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.List;

public interface StoreInterface extends Remote {
    boolean deleteCar(String renavam) throws RemoteException;
    Vehicle searchCar(String renavam) throws RemoteException;
    boolean editCar(String renavam) throws RemoteException;
    Client buyCar(String renavam, Client client) throws RemoteException;
    void init() throws RemoteException;
    boolean addCar(Vehicle a) throws RemoteException;
    List<Vehicle> listAll() throws RemoteException;
    List<Vehicle> listModel(String model) throws RemoteException;
    List<Vehicle> listCategory(String category) throws RemoteException;
    int size() throws RemoteException;
    String oi() throws RemoteException;

}
