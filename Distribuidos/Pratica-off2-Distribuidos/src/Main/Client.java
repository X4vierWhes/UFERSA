package Main;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Client implements Serializable {
    private User user;

    private Vehicle car;

    private List<Vehicle> cars;
    private double wallet;

    private boolean admin = false;

    private boolean buy = false;

    public Client(){
        this.cars = new ArrayList<>();
    }

    public Client(User user, Vehicle car, double wallet){
        this.cars = new ArrayList<>();
        this.user = user;
        //this.cars.add(car);
        this.wallet = wallet;


        if(user.getLogin().equalsIgnoreCase("admin")){
            this.admin = true;
        }
    }

    public User getUser() {
        return user;
    }

    public void buy(Vehicle car){
        this.cars.add(car);
    }

    public void attWallet(double price){
        this.wallet -= price;
    }

    public void myCars(){
        System.out.println("Carteira: " + this.getWallet());
        if(this.cars != null && !this.cars.isEmpty()) {
            for (Vehicle a : this.cars) {
                a.print();
            }
        }else{
            System.err.println("Não possui nenhum carro.");
        }
    }

    public void setUser(User user) {
        this.user = user;
    }

    public Vehicle getCar() {
        return car;
    }

    public void setCar(Vehicle car) {
        this.car = car;
    }

    public double getWallet() {
        return wallet;
    }

    public void setWallet(double wallet) {
        this.wallet = wallet;
    }

    public boolean isAdmin() {
        return admin;
    }

    public void setAdmin(boolean admin) {
        this.admin = admin;
    }

    public boolean isBuy() {
        return buy;
    }

    public void setBuy(boolean buy) {
        this.buy = buy;
    }
}
