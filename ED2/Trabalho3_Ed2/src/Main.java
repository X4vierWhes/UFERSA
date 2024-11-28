import java.util.InputMismatchException;
import Entity.*;
import java.util.Scanner;

import Dao.Arquivo;

public class Main {

	public static void main(String[] args) {
		Scanner cin = new Scanner(System.in);
		Cliente client = null;  //= new Cliente(tam, true);
		int tam = 100;
		boolean flag = true;
		int i = 0;
		
		/*System.out.println(12345678901l%199);
		System.out.println(12345678901l%199);
		System.out.println(12345678901l%199);*/
		
		System.out.println("Deseja utilizar enderaçamento ABERTO(1) ou EXTERIOR(2): ");
		int enderecamento = cin.nextInt();
		/*int enderecamento = 0;
		while(true) {
			try {
				enderecamento = cin.nextInt();
				cin.nextLine();
				break;
			} catch (InputMismatchException e) {
				System.out.println("Erro: O valor inserido não é um número inteiro válido.");
				cin.nextLine();
				continue;
			}
		}*/
		
		Arquivo.clear();
		System.out.println();
		switch(enderecamento) {
			case 1: client = new Cliente(tam, true); break; //Aberto
			case 2: client = new Cliente(tam, false); break; //Fechado
			default: System.out.println("Opção invalida."); flag = false; break;
		}
		
		//System.out.println(12345678901l%100);
		if(flag) {
			client.Init();
			//client.Cadastrar(new Veiculo("ABC1234", "12345678901", "Ford Ka", 2007, new Condutor("Whesley", "11111111111")));
			//client.Cadastrar(new Veiculo("DEF5678", "12345678901", "Toyota Corolla", 2015, new Condutor("Ana", "22222222222")));
			//client.Cadastrar(new Veiculo("GHI9012", "12345678901", "Honda Civic", 2010, new Condutor("Carlos", "33333333333")));
		}else {
			System.out.println("Encerrando.");
		}

		

		while (flag) {

			System.out.println(
					"------------------------------------------------------\n" +
							"Cadastrar (1) \n" +
							"Listar (2) \n" +
							"Editar (3) \n" +
							"Remover (4) \n" +
							"Quantidade (5) \n" +
							"Buscar (6) \n" +
							"Sair (7) \n" +
							"------------------------------------------------------\n" +
							"Digite sua opção: ");

			try {
				i = cin.nextInt();
				cin.nextLine();
			} catch (InputMismatchException e) {
				System.out.println("Erro: O valor inserido não é um número inteiro válido.");
				cin.nextLine();
				continue;
			}

			switch (i) {
				// Cadastrar
				case 1:
					
					System.out.println("Entre com o Nome do Condutor: ");
					String name = cin.next();
					System.out.println("Entre com o CPF do Condutor: ");
					String cpf = cin.next();
					System.out.println("Entre com o MODELO do veiculo: ");
					String modelo = cin.next();
					System.out.println("Entre com o ano de FABRICAÇÃO do veiculo: ");
					int ano;
					 try {   
				           ano  = cin.nextInt();
				          cin.nextLine();
				        } catch (InputMismatchException e) {
				            System.out.println("Erro: O valor inserido não é um número inteiro válido.");
				            cin.nextLine();
				            continue;
				        }
					System.out.println("Entre com o RENAVAM do veiculo: ");
					String renavam = cin.next();
					
					try {
						long teste = Long.parseLong(renavam);
					}catch(NumberFormatException e) {
						System.out.println("erro: Renavam invalido, tente novamente");
						continue;
					}
					System.out.println("Entre com o PLACA do veiculo: ");
					String placa = cin.next();
						
						
						
					client.Cadastrar(new Veiculo(placa, renavam, modelo, ano, new Condutor(name, cpf)));
					break;
				// Listar
				case 2:
					 client.Listar();
					break;
				// Editar
				case 3:
					
					System.out.println("Digite a PLACA do veiculo que deseja editar:");
					String placaEditar = cin.next();
					System.out.println("Digite a RENAVAM do veiculo que deseja editar:");
					String renavamEditar = cin.next();
					long keyEditar = -1;
					try {
						 keyEditar = Long.parseLong(renavamEditar);
					}catch(NumberFormatException e) {
						System.out.println("erro: Renavam invalido, tente novamente");
						continue;
					}
					
					System.out.println(client.Editar(placaEditar, keyEditar) ? "Veiculo editado." : "Não editado.");
					break;
				// Remover
				case 4:
					System.out.println("Digite a PLACA do veiculo que deseja remover:");
					String placaRemover = cin.next();
					System.out.println("Digite a RENAVAM do veiculo que deseja remover:");
					String renavamRemover = cin.next();
					long keyRemover = -1;
					try {
						 keyRemover = Long.parseLong(renavamRemover);
					}catch(NumberFormatException e) {
						System.out.println("erro: Renavam invalido, tente novamente");
						continue;
					}
					
					
					client.Remover(placaRemover, keyRemover);
					break;
				// Quantidade
				case 5:
					System.out.println("Quantidade de elementos na HASH: " + client.Quantidade());
					break;
				// Buscar
				case 6:
					System.out.println("Digite a PLACA do veiculo que deseja buscar:");
					String placaBuscar = cin.next();
					System.out.println("Digite a RENAVAM do veiculo que deseja buscar:");
					String renavamBuscar = cin.next();
					long keyBuscar = -1;
					try {
						 keyBuscar = Long.parseLong(renavamBuscar);
					}catch(NumberFormatException e) {
						System.out.println("erro: Renavam invalido, tente novamente");
						continue;
					}
					
					
					Veiculo a = client.Buscar(placaBuscar, keyBuscar);
					
					System.out.println(a != null ? a.toString(): "Não encontrado.");
					break;
				// Sair
				case 7:
					client.Encerrar();
					flag = false;
					break;
					
				case 8:
					System.out.println("Renavam: ");
					String renavamPrintar = cin.next();
					long keyPrintar = 0;
					try {
						 keyPrintar = Long.parseLong(renavamPrintar);
					}catch(NumberFormatException e) {
						System.out.println("erro: Renavam invalido, tente novamente");
						continue;
					}
					
					client.Printar(keyPrintar);
					break;
				default:
					System.out.println("Por favor digite um numero valido.");
					break;

			}

		}
		System.out.println("Volte sempre.");
		cin.close();
	}
}
