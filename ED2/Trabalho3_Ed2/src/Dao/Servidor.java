package Dao;

import java.util.Scanner;

import Entity.Condutor;
import Entity.Veiculo;
import Service.Huffman;

public class Servidor {
	Hash root;
	private Scanner cin = new Scanner(System.in);

	// Construtores
	public Servidor(int tam, boolean adress) {
		root = new Hash(tam, adress);
	}

	public void Cadastrar(Veiculo cadastro) {
		root.Insert(cadastro);
	}
	
	public void Cadastrar(String codificado, Huffman huff) {
		String decodificado = huff.descomprimir(codificado);
		//System.out.println("Decodificado: " + decodificado);
		//System.out.println();
		
		String[] veiculoS = decodificado.split("#");
		//String placa, String renavam, String modelo, int fabricacao, Condutor condutor
		Veiculo sign = new Veiculo(veiculoS[2], veiculoS[5], veiculoS[3], Integer.parseInt(veiculoS[4]), new Condutor(veiculoS[0], veiculoS[1]));
		this.Cadastrar(sign);
		//for(String a : veiculoS) {
			//System.out.println(a);
		//}
		//System.out.println();
	}
	
	public void Remover(String placa, long chave) {
		Veiculo remover = this.Buscar(placa, chave);
		boolean flag = ((remover != null) ? true: false);
		if(flag) {
			System.out.println(remover.toString());
			
			System.out.println("Tem certeza que deseja REMOVER? (S/N)");
			String escolha = cin.next();
			
			switch(escolha) {
			case "s": 
			case "S":
				System.out.println("Removido.");
				root.Remove(placa, chave);
				break;
			case "n":
			case "N": System.out.println("Não Removido.");
				break;
			}
		}else {
			System.out.println("Não encontrado.");
		}
	}
	
	public void Remover(String codificado, Huffman huff) {
		String decodificado = huff.descomprimir(codificado);
		
		String [] dados = decodificado.split("#");
		
		this.Remover(dados[0], Long.parseLong(dados[1]));
		
	}
	
	public Veiculo Buscar(String placa, long chave) {
		return root.Search(placa ,chave);
	}
	
	public Veiculo Buscar(String codificado, Huffman huff) {
		String decodificado = huff.descomprimir(codificado);
		
		String [] dados = decodificado.split("#");
		return this.Buscar(dados[0], Long.parseLong(dados[1]));
	}

	
	public boolean Editar(String placa, long chave) {
		if(root.Edit(placa, chave)) {
			return true;
		}
		return false;
	}
	
	
	public void Listar() {
		root.List();
	}

	public int Quantidade() {
		return root.Amount();
	}
	
	public void Printar(long keyPrintar) {
		root.PrintVector(keyPrintar);
	}

	public void Encerrar() {
		System.out.println("Servidor desconectado do sistema.");
		cin.close();
		
	}




}
