import Service.Protocolo;
import Entity.Condutor;
import Entity.Veiculo;

public class Cliente {

	Protocolo protocol;

	public Cliente(int tam, boolean adress) {
		protocol = new Protocolo(tam, adress);
	}

	public void Cadastrar(Veiculo cadastro) {
		protocol.Cadastrar(cadastro);
	}
	
	
	public void Remover(String placa, long chave) {
		protocol.Remover(placa, chave);
	}
	
	public Veiculo Buscar(String placa, long chave) {
		return protocol.Buscar(placa ,chave);
	}
	
	public boolean Editar(String placa, long chave) {
		return protocol.Editar(placa, chave);
	}
	
	public void Listar() {
		protocol.Listar();
	}

	public int Quantidade() {
		return protocol.Quantidade();
	}
	
	public void Printar(long keyPrintar) {
		protocol.Printar(keyPrintar);
	}

	public void Init() {
		
		  this.protocol.Cadastrar(new Veiculo("ABC1234", "12345678901", "Ford Ka", 2007, new
		  Condutor("Whesley", "12371060445")));
		  this.protocol.Cadastrar(new Veiculo("DEF5678", "23456789012", "Toyota Corolla",
		  2015, new Condutor("Ana", "22222222222")));
		  this.protocol.Cadastrar(new Veiculo("GHI9012", "34567890123", "Honda Civic", 2010,
		  new Condutor("Carlos", "33333333333")));
		  this.protocol.Cadastrar(new Veiculo("JKL3456", "45678901234", "Chevrolet Cruze",
		  2018, new Condutor("Emily", "44444444444")));
		  this.protocol.Cadastrar(new Veiculo("MNO6789", "56789012345", "Volkswagen Golf",
		  2014, new Condutor("Gabriel", "55555555555")));
		  this.protocol.Cadastrar(new Veiculo("PQR0123", "67890123456", "Nissan Sentra", 2013,
		  new Condutor("Dorivaldiola", "66666666666")));
		  this.protocol.Cadastrar(new Veiculo("STU4567", "78901234567", "Hyundai Elantra",
		  2016, new Condutor("Lucas", "77777777777")));
		  this.protocol.Cadastrar(new Veiculo("VWX7890", "89012345678", "Kia Optima", 2012,
		  new Condutor("Mariana", "88888888888")));
		  this.protocol.Cadastrar(new Veiculo("YZA1234", "90123456789", "Ford Focus", 2009,
		  new Condutor("Nathan", "99999999999")));
		  this.protocol.Cadastrar(new Veiculo("BCD5678", "01234567890", "Toyota Camry", 2020,
		  new Condutor("Olivia", "00000000000")));
		  this.protocol.Cadastrar(new Veiculo("EFG9012", "11223344556", "Honda Accord", 2017,
		  new Condutor("Paul", "12345678901")));
		  this.protocol.Cadastrar(new Veiculo("HIJ2345", "22334455667", "Chevrolet Malibu",
		  2019, new Condutor("Sarah", "23456789012")));
		  this.protocol.Cadastrar(new Veiculo("KLM4567", "33445566778", "Volkswagen Jetta",
		  2011, new Condutor("Thomas", "34567890123")));
		  this.protocol.Cadastrar(new Veiculo("NOP7890", "44556677889", "Nissan Altima", 2014,
		  new Condutor("Victoria", "45678901234")));
		  this.protocol.Cadastrar(new Veiculo("QRS0123", "55667788990", "Hyundai Sonata",
		  2018, new Condutor("William", "56789012345")));
		  this.protocol.Cadastrar(new Veiculo("TUV3456", "66778899001", "Kia Forte", 2013, new
		  Condutor("Emma", "67890123456")));
		  this.protocol.Cadastrar(new Veiculo("WXY6789", "77889900112", "Mazda Mazda3", 2015,
		  new Condutor("Liam", "78901234567")));
		  this.protocol.Cadastrar(new Veiculo("ZAB9012", "88990011223", "Subaru Impreza",
		  2010, new Condutor("Ava", "89012345678")));
		  this.protocol.Cadastrar(new Veiculo("CDE1234", "99001122334", "Ford Mustang", 2022,
		  new Condutor("Noah", "90123456789")));
		  this.protocol.Cadastrar(new Veiculo("FGH5678", "00112233445", "Chevrolet Camaro",
		  2016, new Condutor("Joao Lucas", "01234567890")));
		  this.protocol.Cadastrar(new Veiculo("IJK9012", "11223344556", "Dodge Challenger",
		  2019, new Condutor("Chichi", "12345678901")));
		  this.protocol.Cadastrar(new Veiculo("LMN2345", "22334455667", "Porsche 911", 2020,
		  new Condutor("Goku", "23456789012")));
		  this.protocol.Cadastrar(new Veiculo("OPQ4567", "33445566778", "BMW M3", 2017, new
		  Condutor("Fernanda", "34567890123")));
		  this.protocol.Cadastrar(new Veiculo("RST7890", "44556677889",
		  "Mercedes-Benz C-Class", 2018, new Condutor("Liam", "45678901234")));
		  this.protocol.Cadastrar(new Veiculo("UVW0123", "55667788990", "Audi A4", 2015, new
		  Condutor("Emma", "56789012345")));
		  this.protocol.Cadastrar(new Veiculo("XYZ3456", "66778899001", "Lexus IS", 2013, new
		  Condutor("William", "67890123456")));
		  this.protocol.Cadastrar(new Veiculo("ABC6789", "77889900112", "Infiniti Q50", 2014,
		  new Condutor("Ava", "78901234567")));
		  this.protocol.Cadastrar(new Veiculo("DEF9012", "88990011223", "Jaguar XE", 2019, new
		  Condutor("Noah", "89012345678")));
		  this.protocol.Cadastrar(new Veiculo("GHI1234", "99001122334", "Tesla Model 3", 2021,
		  new Condutor("Gonzaga", "90123456789")));
		  this.protocol.Cadastrar(new Veiculo("JKL5678", "00112233445", "Ford Escape", 2016,
		  new Condutor("Sophia", "01234567890")));
		  this.protocol.Cadastrar(new Veiculo("MNO9012", "11223344556", "Chevrolet Equinox",
		  2017, new Condutor("Lucas", "12345678901")));
		  this.protocol.Cadastrar(new Veiculo("PQR2345", "22334455667", "Toyota RAV4", 2020,
		  new Condutor("Isabella", "23456789012")));
		  this.protocol.Cadastrar(new Veiculo("STU4567", "33445566778", "Honda CR-V", 2019,
		  new Condutor("Gabriel", "34567890123")));
		  this.protocol.Cadastrar(new Veiculo("VWX7890", "44556677889", "Nissan Rogue", 2018,
		  new Condutor("Mariana", "45678901234")));
		  this.protocol.Cadastrar(new Veiculo("YZA0123", "55667788997", "Hyundai Tucson",
		  2015, new Condutor("Nathan", "56789012345")));
		  this.protocol.Cadastrar(new Veiculo("BCD3456", "66778899001", "Kia Sportage", 2014,
		  new Condutor("Marta", "67890123456")));
		  this.protocol.Cadastrar(new Veiculo("EFG6789", "77889900112", "Mazda CX-5", 2016,
		  new Condutor("Paul", "78901234567")));
		  this.protocol.Cadastrar(new Veiculo("HIJ9012", "88990011223", "Subaru Forester",
		  2013, new Condutor("Mikasa", "89012345678")));
		  this.protocol.Cadastrar(new Veiculo("KLM2345", "99001122334", "Ford Edge", 2017, new
		  Condutor("Thomas", "90123456789")));
		  this.protocol.Cadastrar(new Veiculo("NOP4567", "00112233445", "Chevrolet Traverse",
		  2018, new Condutor("Victoria", "01234567890")));
		  this.protocol.Cadastrar(new Veiculo("QRS7890", "11223344556", "Volkswagen Tiguan",
		  2015, new Condutor("William", "12345678901")));
		  this.protocol.Cadastrar(new Veiculo("TUV0123", "22334455667", "Nissan Murano", 2014,
		  new Condutor("Emma", "23456789012")));
		  this.protocol.Cadastrar(new Veiculo("WXY3456", "33445566778", "Hyundai Santa Fe",
		  2019, new Condutor("Liam", "34567890123")));
		  this.protocol.Cadastrar(new Veiculo("ZAB6789", "44556677889", "Toyota Highlander",
		  2016, new Condutor("Ava", "45678901234")));
		  this.protocol.Cadastrar(new Veiculo("CDE9012", "55667788995", "Kia Sorento", 2018,
		  new Condutor("Noah", "56789012345")));
		  this.protocol.Cadastrar(new Veiculo("FGH2345", "66778899001", "Ford Expedition",
		  2017, new Condutor("Oliveira", "67890123456")));
		  this.protocol.Cadastrar(new Veiculo("IJK4567", "77889900112", "Chevrolet Tahoe",
		  2020, new Condutor("Serlandia", "78901234567")));
		  this.protocol.Cadastrar(new Veiculo("LMN7890", "88990011223", "Honda Pilot", 2019,
		  new Condutor("Aizen", "89012345678")));
		  this.protocol.Cadastrar(new Veiculo("OPQ0123", "99001122334", "GMC Acadia", 2015,
		  new Condutor("Valentina", "90123456789")));
		  this.protocol.Cadastrar(new Veiculo("RST3456", "00112233445", "Jeep Grand Cherokee",
		  2018, new Condutor("Lucas", "01234567890")));
		 
	}

	public void Encerrar() {
		protocol.Encerrar();
		System.out.println("Cliente encerrado.");
		
	}

}
