import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

import Entity.Condutor;
import Entity.Veiculo;

public class Main {

	public static void main(String [] args) {
		Cliente<Veiculo> client = new Cliente<Veiculo>();
		List<Veiculo> list = new ArrayList<Veiculo>();

		client.Cadastrar(new Veiculo("ABC1234", "12345678901", "Ford Ka", 2007, new Condutor("Whesley", "11111111111")));
		client.Cadastrar(new Veiculo("DEF5678", "23456789012", "Toyota Corolla", 2015, new Condutor("Ana", "22222222222")));
		client.Cadastrar(new Veiculo("GHI9012", "34567890123", "Honda Civic", 2010, new Condutor("Carlos", "33333333333")));
		client.Cadastrar(new Veiculo("JKL3456", "45678901234", "Chevrolet Cruze", 2018, new Condutor("Emily", "44444444444")));
		client.Cadastrar(new Veiculo("MNO6789", "56789012345", "Volkswagen Golf", 2014, new Condutor("Gabriel", "55555555555")));
		client.Cadastrar(new Veiculo("PQR0123", "67890123456", "Nissan Sentra", 2013, new Condutor("Natasha", "66666666666")));
		client.Cadastrar(new Veiculo("STU4567", "78901234567", "Hyundai Elantra", 2016, new Condutor("Lucas", "77777777777")));
		client.Cadastrar(new Veiculo("VWX7890", "89012345678", "Kia Optima", 2012, new Condutor("Mariana", "88888888888")));
		client.Cadastrar(new Veiculo("YZA1234", "90123456789", "Ford Focus", 2009, new Condutor("Nathan", "99999999999")));
		client.Cadastrar(new Veiculo("BCD5678", "01234567890", "Toyota Camry", 2020, new Condutor("Olivia", "00000000000")));
		client.Cadastrar(new Veiculo("EFG9012", "11223344556", "Honda Accord", 2017, new Condutor("Paul", "12345678901")));
		client.Cadastrar(new Veiculo("HIJ2345", "22334455667", "Chevrolet Malibu", 2019, new Condutor("Sarah", "23456789012")));
		client.Cadastrar(new Veiculo("KLM4567", "33445566778", "Volkswagen Jetta", 2011, new Condutor("Thomas", "34567890123")));
		client.Cadastrar(new Veiculo("NOP7890", "44556677889", "Nissan Altima", 2014, new Condutor("Victoria", "45678901234")));
		client.Cadastrar(new Veiculo("QRS0123", "55667788990", "Hyundai Sonata", 2018, new Condutor("William", "56789012345")));
		client.Cadastrar(new Veiculo("TUV3456", "66778899001", "Kia Forte", 2013, new Condutor("Emma", "67890123456")));
		client.Cadastrar(new Veiculo("WXY6789", "77889900112", "Mazda Mazda3", 2015, new Condutor("Liam", "78901234567")));
		client.Cadastrar(new Veiculo("ZAB9012", "88990011223", "Subaru Impreza", 2010, new Condutor("Ava", "89012345678")));
		client.Cadastrar(new Veiculo("CDE1234", "99001122334", "Ford Mustang", 2022, new Condutor("Noah", "90123456789")));
		client.Cadastrar(new Veiculo("FGH5678", "00112233445", "Chevrolet Camaro", 2016, new Condutor("Joao Lucas", "01234567890")));
		client.Cadastrar(new Veiculo("IJK9012", "11223344556", "Dodge Challenger", 2019, new Condutor("Chichi", "12345678901")));
		client.Cadastrar(new Veiculo("LMN2345", "22334455667", "Porsche 911", 2020, new Condutor("Goku", "23456789012")));
		client.Cadastrar(new Veiculo("OPQ4567", "33445566778", "BMW M3", 2017, new Condutor("Fernanda", "34567890123")));
		client.Cadastrar(new Veiculo("RST7890", "44556677889", "Mercedes-Benz C-Class", 2018, new Condutor("Liam", "45678901234")));
		client.Cadastrar(new Veiculo("UVW0123", "55667788990", "Audi A4", 2015, new Condutor("Emma", "56789012345")));
		client.Cadastrar(new Veiculo("XYZ3456", "66778899001", "Lexus IS", 2013, new Condutor("William", "67890123456")));
		client.Cadastrar(new Veiculo("ABC6789", "77889900112", "Infiniti Q50", 2014, new Condutor("Ava", "78901234567")));
		client.Cadastrar(new Veiculo("DEF9012", "88990011223", "Jaguar XE", 2019, new Condutor("Noah", "89012345678")));
		client.Cadastrar(new Veiculo("GHI1234", "99001122334", "Tesla Model 3", 2021, new Condutor("Gonzaga", "90123456789")));
		client.Cadastrar(new Veiculo("JKL5678", "00112233445", "Ford Escape", 2016, new Condutor("Sophia", "01234567890")));
		client.Cadastrar(new Veiculo("MNO9012", "11223344556", "Chevrolet Equinox", 2017, new Condutor("Lucas", "12345678901")));
		client.Cadastrar(new Veiculo("PQR2345", "22334455667", "Toyota RAV4", 2020, new Condutor("Isabella", "23456789012")));
		client.Cadastrar(new Veiculo("STU4567", "33445566778", "Honda CR-V", 2019, new Condutor("Gabriel", "34567890123")));
		client.Cadastrar(new Veiculo("VWX7890", "44556677889", "Nissan Rogue", 2018, new Condutor("Mariana", "45678901234")));
		client.Cadastrar(new Veiculo("YZA0123", "55667788990", "Hyundai Tucson", 2015, new Condutor("Nathan", "56789012345")));
		client.Cadastrar(new Veiculo("BCD3456", "66778899001", "Kia Sportage", 2014, new Condutor("Marta", "67890123456")));
		client.Cadastrar(new Veiculo("EFG6789", "77889900112", "Mazda CX-5", 2016, new Condutor("Paul", "78901234567")));
		client.Cadastrar(new Veiculo("HIJ9012", "88990011223", "Subaru Forester", 2013, new Condutor("Mikasa", "89012345678")));
		client.Cadastrar(new Veiculo("KLM2345", "99001122334", "Ford Edge", 2017, new Condutor("Thomas", "90123456789")));
		client.Cadastrar(new Veiculo("NOP4567", "00112233445", "Chevrolet Traverse", 2018, new Condutor("Victoria", "01234567890")));
		client.Cadastrar(new Veiculo("QRS7890", "11223344556", "Volkswagen Tiguan", 2015, new Condutor("William", "12345678901")));
		client.Cadastrar(new Veiculo("TUV0123", "22334455667", "Nissan Murano", 2014, new Condutor("Emma", "23456789012")));
		client.Cadastrar(new Veiculo("WXY3456", "33445566778", "Hyundai Santa Fe", 2019, new Condutor("Liam", "34567890123")));
		client.Cadastrar(new Veiculo("ZAB6789", "44556677889", "Toyota Highlander", 2016, new Condutor("Ava", "45678901234")));
		client.Cadastrar(new Veiculo("CDE9012", "55667788990", "Kia Sorento", 2018, new Condutor("Noah", "56789012345")));
		client.Cadastrar(new Veiculo("FGH2345", "66778899001", "Ford Expedition", 2017, new Condutor("Oliveira", "67890123456")));
		client.Cadastrar(new Veiculo("IJK4567", "77889900112", "Chevrolet Tahoe", 2020, new Condutor("Serlandia", "78901234567")));
		client.Cadastrar(new Veiculo("LMN7890", "88990011223", "Honda Pilot", 2019, new Condutor("Aizen", "89012345678")));
		client.Cadastrar(new Veiculo("OPQ0123", "99001122334", "GMC Acadia", 2015, new Condutor("Valentina", "90123456789")));
		client.Cadastrar(new Veiculo("RST3456", "00112233445", "Jeep Grand Cherokee", 2018, new Condutor("Lucas", "01234567890")));
		
			boolean flag = true;
			int i = 0;
			Scanner cin = new Scanner(System.in);
			
			while(flag) {
				
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
						"Digite sua opção: "
						);
				
					
				  try {   
			          i  = cin.nextInt();
			          cin.nextLine();
			        } catch (InputMismatchException e) {
			            System.out.println("Erro: O valor inserido não é um número inteiro válido.");
			            cin.nextLine();
			            continue;
			        }
				
			
				switch(i) {
				//Cadastrar
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
			//Listar
				case 2: 
					client.Listar();
					break;
					//Editar
				case 3: 
					System.out.println("Digite o RENAVAM do Veiculo que deseja Editar: ");
					String ren = cin.next();
					Veiculo editar = client.BuscarRenavam(Long.parseLong(ren));
					System.out.println("Editar Nome do Condutor: ");
					String name1 = cin.next();
					System.out.println("Editar CPF do Condutor: ");
					String cpf1 = cin.next();
					System.out.println("Editar MODELO do veiculo: ");
					String modelo1 = cin.next();
					System.out.println("Editar ano de FABRICAÇÃO do veiculo: ");
					int ano1 = cin.nextInt();
					System.out.println("Editar PLACA do veiculo: ");
					String placa1 = cin.next();
					String renavam1 = editar.getRenavam();
					
					client.Remover(editar);
					client.Cadastrar(new Veiculo(placa1, renavam1, modelo1, ano1, new Condutor(name1, cpf1)));
					
					
					break;
			//Remover
				case 4: 
					
					list = client.OrdemToArray();
					Veiculo remover = null;
					boolean achou = false;
					System.out.println("Digite o NOME do condutor que deseja excluir: ");
					String procurando = cin.next();
					
						for(Veiculo a : list) {
							if(a.getName().equalsIgnoreCase(procurando)) {
								remover = a;
								achou = true;
								break;
							}
						}
						
						if(achou) {
							System.out.println("Tem certeza que deseja remover " + remover.getName() + "\n" +
									"Dados: " + "\n" +
									"CPF: " + remover.getCpf() + "\n" +
									"Carro: " + remover.getModelo() + "\n" + 
									"Ano: " + remover.getFabricacao() + "\n" + 
									"Placa: " + remover.getPlaca() + "\n" +
									"Renavam: " + remover.getRenavam() + "\n" +
									"Digite (S) para SIM e (N) para NAO:" );
							
								String escolha = cin.next();
								
								switch(escolha) {
								case "s":
								case"S":
									client.Remover(remover);
									break;
								case "n":
								case "N":
									break;
								}
						}else {
							System.out.println("Não encontrado.");
						}
						
					break;
					//Quantidade
				case 5: 
					System.out.println("Veiculos cadastrados no sistema: " + client.Quantidade());
					
					break;
					//Buscar
				case 6:
					System.out.println("Deseja realizar a busca por PLACA (1) ou por RENAVAM (2): ");
					int escolha = cin.nextInt();
					Veiculo procurado = null;
					
					if(escolha == 2) {
						System.out.println("Digite o RENAVAM que deseja buscar:");
						String renavamProcurado = cin.next();
						long procura = Long.parseLong(renavamProcurado);
						procurado = client.BuscarRenavam(procura);
						System.out.println((procurado != null) ? procurado.toString(): "Não encontrado.");
					}else{
						list = client.OrdemToArray();
						System.out.println("Digite a Placa que deseja buscar:");
						String placaProcurada = cin.next();
						for(Veiculo a : list) {
							if(placaProcurada.equalsIgnoreCase(a.getPlaca())) {
								procurado = a;
								break;
							}
						}
						
						System.out.println((procurado != null) ? procurado.toString(): "Não encontrado.");
					}
					
					
					break;
					//Sair
				case 7: 
					flag = false;
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


