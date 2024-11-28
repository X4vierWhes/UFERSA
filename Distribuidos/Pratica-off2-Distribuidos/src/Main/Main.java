package Main;

import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.List;
import java.util.Scanner;
import  Gateway.*;

public class Main {

    static GatewayInterface stub;
    private static Client client;

    public static void main(String[] args) throws RemoteException {

        Scanner cin = new Scanner(System.in);
        System.out.println("Informe o nome/endereço do RMIRegistry");
        String host = cin.nextLine();

        try{
            Registry registro = LocateRegistry.getRegistry(host, Registry.REGISTRY_PORT);
            stub = (GatewayInterface) registro.lookup("Gateway");
            //System.out.println(stub.oi());
            //stub.init();

            System.out.print("login:");
            String login = cin.nextLine();
            System.out.print("senha:");
            String password = cin.nextLine();
            System.out.println();

            if (stub.connect(login, password)) {
                client = new Client(new User(login, password), new Vehicle(), 100000.0);
                clientLoop(client);
            } else {
                System.out.println("Não foi possivel conectar, cliente nao possui conta.");
                System.out.println("Cadastre-se no sistema: ");
                while(true) {
                    System.out.print("login:");
                    login = cin.nextLine();
                    System.out.print("senha:");
                    password = cin.nextLine();
                    System.out.println();
                    if (stub.signUp(login, password)) {
                        client = new Client(new User(login, password), new Vehicle(), 100000.0);
                        clientLoop(client);
                        break;
                    } else {
                        System.err.println("Não foi possivel cadastrar, tente novamente");
                    }
                }

            }


        }catch (RemoteException e){
            e.printStackTrace();
        }catch (NotBoundException e){
            e.printStackTrace();
        }

    }

    public static void clientLoop(Client client) throws RemoteException {
        System.out.println("************************************");
        System.out.println("          Loja de Carros");
        System.out.println("Seja bem vindo!");
        Scanner cin = new Scanner(System.in);
        int escolha = 0;
        while (escolha != 9){
            System.out.println("************************************");
            System.out.println("               MENU");
            if(client.isAdmin()) {
                System.out.println("""
                        USUARIO: ADMINISTRADOR
                        ---------------------------------------------
                        1 | ADICIONAR CARRO
                        2 | DELETAR CARRO
                        3 | LISTAR TODOS OS CARROS
                        4 | LISTAR POR MODELO
                        5 | LISTAR POR CATEGORIA
                        6 | PESQUISAR CARRO
                        7 | ALTERAR CARRO
                        8 | QUANTIDADE DE CARROS NO SISTEMA
                        9 | SAIR \s
                        Digite sua opção:""");
                //try {
                    escolha = cin.nextInt();

                    switch (escolha){
                        case 1: //Adicionar carro
                            if(stub.addCar(Vehicle.create())){
                                System.err.println("Carro adicionado");
                            }else{
                                System.err.println("Erro ao adicionar Carro");
                            }
                            break;
                        case 2: //Deletar carro
                            System.out.println("Digite o renavam do carro que deseja DELETAR:");
                            String delete = cin.next();

                            Vehicle del = stub.searchCar(delete);

                            System.out.println("Informações do carro:");
                            del.print();

                            System.out.println("Tem certeza que deseja deletar esse carro (sim) ou (nao):");
                            String esc = cin.next();

                            if("sim".equalsIgnoreCase(esc)){
                                if(stub.deleteCar(delete)){
                                    System.err.println("Carro deletado.");
                                }else{
                                    System.err.println("Não foi possivel deletar.");
                                }
                            }

                            break;
                        case 3: //Listar todos os veiculos
                           List<Vehicle> all = stub.listAll();

                           if(all != null) {
                               all.sort(new CompareVehicle());
                               for (Vehicle a : all) {
                                   a.print();
                               }
                           }
                        break;
                        case 4: //Listar por modelo
                            System.out.println("Digite o MODELO do carro:");
                            String model = cin.next();
                            List<Vehicle> models = stub.listModel(model);

                            if(models != null){
                                models.sort(new CompareVehicle());
                                for(Vehicle a : models){
                                    a.print();
                                }
                            }else{
                                System.err.println("Não encontrado modelo do carro");
                            }
                            break;
                        case 5: //Listar por categoria
                            System.out.println("""                
                                    ---------------------------------------------------------------
                                    1 | ECONOMICO
                                    2 | INTERMEDIARIO
                                    3 | EXECUTIVO
                                    Digite o numero da categoria desejada:
                                    """);
                            String escolhanum = cin.next();
                            List<Vehicle> categorys = null;
                            switch (escolhanum){
                                case "1":
                                    categorys = stub.listCategory("Economico");
                                    break;
                                case "2":
                                    categorys = stub.listCategory("Intermediario");
                                    break;
                                case "3":
                                    categorys = stub.listCategory("Executivo");
                                    break;
                                default:
                                    System.err.println("Escolha fora do escopo.");
                                    break;
                            }

                            if(categorys != null){
                                categorys.sort(new CompareVehicle());
                                for(Vehicle a: categorys){
                                    a.print();
                                }
                            }else{
                                System.out.println("Nenhum carro encontrado na categoria.");
                            }

                            break;
                        case 6: //Pesquisar carro
                            System.out.println("Digite o RENAVAM do carro que esta procurando: ");
                            String renavam = cin.next();

                            Vehicle search = stub.searchCar(renavam);

                            if(search != null){
                                search.print();
                            }else{
                                System.out.println("Carro não encontrado.");
                            }

                            break;
                        case 7: //Alterar carro
                            System.out.println("Digite o RENAVAM do carro que deseja alterar: ");
                            String editRenavam = cin.next();
                            Vehicle editCar = stub.searchCar(editRenavam);


                            if(editCar != null){
                                stub.deleteCar(editRenavam);
                                editCar.print();
                                int escolha2 = 0;
                                while(escolha2 != 5) {
                                    System.out.println("""
                                    ---------------------------------------------------------------
                                    1 | MODELO
                                    2 | RENAVAM
                                    3 | ANO
                                    4 | PREÇO
                                    5 | SAIR
                                    Digite:""");

                                    escolha2 = cin.nextInt();

                                    switch (escolha2){
                                        case 1:
                                            System.out.println("Digite o novo modelo: ");
                                            editCar.setModel(cin.next());
                                            break;
                                        case 2:
                                            System.out.println("Digite o novo renavam:");
                                            editCar.setRenavam(cin.next());
                                            break;
                                        case 3:
                                            System.out.println("Digite o novo ano:");
                                            editCar.setYear(cin.nextInt());
                                            break;
                                        case 4:
                                            System.out.println("Digite o novo preço:");
                                            editCar.setPrice(Double.parseDouble(cin.next()));
                                            break;
                                        case 5:
                                            break;
                                        default: break;

                                    }
                                }

                                stub.addCar(editCar);


                            }else{
                                System.err.println("Carro não encontrado.");
                            }

                            break;
                        case 8: //Quantidade de carros na loja
                            System.out.println("Quantidade de carros na loja: " + stub.size());
                            break;
                        case 9:
                            break;
                        default:
                            break;

                    }

                /*}catch(Exception e){
                    System.out.println("Numero invalido");
                }*/


            }else{
                System.out.println("USUARIO: " + client.getUser().getLogin());
                System.out.println("""                   
                        ---------------------------------------------              \s
                        1 | LISTAR TODOS OS CARROS
                        2 | LISTAR POR MODELO
                        3 | LISTAR POR CATEGORIA
                        4 | PESQUISAR CARRO
                        5 | QUANTIDADE DE CARROS NO SISTEMA
                        6 | COMPRAR CARRO
                        7 | MEUS CARROS
                        8 | SAIR \s
                        Digite sua opção:
                        """);
                //try {
                    escolha = cin.nextInt();

                    switch (escolha){

                        case 1: //Listar todos os veiculos
                            List<Vehicle> all = stub.listAll();
                            if(all != null) {
                                all.sort(new CompareVehicle());
                                for (Vehicle a : all) {
                                    a.print();
                                }
                            }else{
                                System.err.println("Não existem carros no site");
                            }
                            break;

                        case 2: //Listar por modelo
                            System.out.println("Digite o MODELO do carro: ");
                            String model = cin.next();
                            List<Vehicle> models = stub.listModel(model);

                            if(models != null){
                                models.sort(new CompareVehicle());
                                for(Vehicle a : models){
                                    a.print();
                                }
                            }else{
                                System.err.println("Não encontrado modelo do carro");
                            }
                            break;
                        case 3: //Listar por categoria
                            System.out.println("""                
                                    ---------------------------------------------------------------
                                    1 | ECONOMICO
                                    2 | INTERMEDIARIO
                                    3 | EXECUTIVO
                                    Digite o numero da categoria desejada:
                                    """);
                            String escolhanum = cin.next();
                            List<Vehicle> categorys = null;
                            switch (escolhanum){
                                case "1":
                                    categorys = stub.listCategory("Economico");
                                    break;
                                case "2":
                                    categorys = stub.listCategory("Intermediario");
                                    break;
                                case "3":
                                    categorys = stub.listCategory("Executivo");
                                    break;
                                default:
                                    System.err.println("Escolha fora do escopo.");
                                    break;
                            }

                            if(categorys != null){
                                categorys.sort(new CompareVehicle());
                                for(Vehicle a: categorys){
                                    a.print();
                                }
                            }else{
                                System.out.println("Nenhum carro encontrado na categoria.");
                            }

                            break;
                        case 4: //Pesquisar carro
                            System.out.println("Digite o RENAVAM do carro que esta procurando: ");
                            String renavam = cin.next();

                            Vehicle search = stub.searchCar(renavam);

                            if(search != null){
                                search.print();
                            }else{
                                System.out.println("Carro não encontrado.");
                            }

                            break;
                        case 5: //Quantidade de carros na loja
                            System.out.println("Quantidade de carros na loja: " + stub.size());
                            break;
                        case 6: //Comprar carro
                            System.out.println("Digite o RENAVAM do carro que deseja comprar: ");
                            String buy = cin.next();
                            client = stub.buyCar(buy, client);

                            if(client.isBuy()){
                                System.err.println("Carro comprado com sucesso.");
                                client.setBuy(false);
                            }else{
                                System.err.println("Não foi possivel comprar o carro.");
                            }

                           /* if(stub.buyCar(buy, client)){
                                System.err.println("Carro comprado com sucesso.");
                            }else{
                                System.err.println("Não foi possivel comprar o carro.");
                            }*/
                            break;
                        case 7:
                            client.myCars();
                            break;
                        case 8:
                        case 9: escolha = 9; break;
                        default: break;

                    }



               /* }catch(Exception e){
                    System.out.println("Numero invalido");
                }*/
            }
        }

        System.err.println("Volte sempre!");
    }

}

