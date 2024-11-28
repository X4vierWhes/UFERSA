package Service;

import Dao.Servidor;
import Entity.Veiculo;
import java.util.Scanner;

public class Protocolo {
	Servidor server;
	Huffman huff;
	private Scanner cin = new Scanner(System.in);
	

	public Protocolo(int tam, boolean adress) {
		server = new Servidor(tam, adress);
		
	}

	public void Cadastrar(Veiculo cadastro) {
		huff = new Huffman();
		String tostring = cadastro.toString(1);
		//System.out.println("Entrada: " + tostring);
		String codificado = huff.comprimir(tostring);
		//System.out.println("Codificado: " + codificado);
		server.Cadastrar(codificado, huff);
		
		
		
	}

	public void Remover(String placa, long chave) {
		huff = new Huffman();
		String tostring = placa + "#" + chave;
		String codificado = huff.comprimir(tostring);
		server.Remover(codificado, huff);
	}
	
	public Veiculo Buscar(String placa, long chave) {
		huff = new Huffman();
		String tostring = placa + "#" + chave;
		String codificado = huff.comprimir(tostring);
		//return server.Buscar(placa, chave);
		return server.Buscar(codificado, huff);
	}
	
	public boolean Editar(String placa, long chave) {
		Veiculo editar = Buscar(placa, chave);
		
		if(editar != null) {
			System.out.println(editar.toString());
			System.out.println("Deseja editar? (S/N)");
			String escolha = cin.next();
			
			switch(escolha) {
			case "n":
			case "N": 
				break;
			case "s":
			case "S": 
				return server.Editar(placa, chave);
				
			}
		}
		
		return false;
	}
	
	public void Listar() {
		server.Listar();
	}

	public int Quantidade() {
		return server.Quantidade();
	}
	
	public void Printar(long keyPrintar) {
		server.Printar(keyPrintar);
	}

	public void Encerrar() {
		server.Encerrar();
		System.out.println("Protocolo encerrado.");
		cin.close();
		
	}
}
