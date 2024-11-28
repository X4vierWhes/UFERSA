package Main;

import java.io.Serializable;
import java.util.Comparator;
import java.util.Scanner;

public class Vehicle implements Serializable {

    private String model;
    private String renavam;
    private int year;
    private double price;
    private String category;

    public Vehicle(){
        //this.model = "none";
        //this.renavam = "none";
        //this.year = 0;
        //this.category = "none";
        //this.price = 0.0;
    }

    public Vehicle(String model, String renavam, int year, double price){
        this.model = model;
        this.renavam = renavam;
        this.year = year;
        this.price = price;
        this.setCategory(price);
    }

    public void print(){
        System.out.println("------------------------------------------");
        System.out.println("MODELO: " + this.getModel());
        System.out.println("RENAVAM: " + this.getRenavam());
        System.out.println("ANO: " + this.getYear());
        System.out.println("PREÇO: " + this.getPrice());
        System.out.println("Categoria: " + this.getCategory());
    }

    public static Vehicle create(){
        Scanner cin = new Scanner(System.in);
        System.out.println("------------------------------------------");
        System.out.print("MODELO: ");
        String model = cin.nextLine();
        System.out.print("RENAVAM: ");
        String renavam = cin.nextLine();
        System.out.print("ANO: ");
        int year = cin.nextInt();
        System.out.print("PREÇO: ");
        double price = Double.parseDouble(cin.next());

        return new Vehicle(model, renavam, year, price);
    }

    public String getRenavam() {
        return renavam;
    }

    public void setRenavam(String renavam) {
        this.renavam = renavam;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public double getPrice() {
        return price;
    }

    public void setPrice(double price) {
        this.price = price;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(double price) {
        if(price <= 12000){
            this.category = "Economico";
        } else if (price <= 35000) {
            this.category = "Intermediario";
        }else{
            this.category = "Executivo";
        }
    }
}

class CompareVehicle implements Comparator<Vehicle>{

    @Override
    public int compare(Vehicle o1, Vehicle o2) {
        return o1.getModel().compareTo(o2.getModel());
    }
}
