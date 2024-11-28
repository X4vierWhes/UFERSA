package Gateway;

import java.rmi.Remote;
import java.rmi.RemoteException;

import Autentication.AutenticationInterface;
import Store.StoreInterface;


public interface GatewayInterface extends Remote, AutenticationInterface, StoreInterface {
    String oi() throws RemoteException;

    void init() throws RemoteException;
}
