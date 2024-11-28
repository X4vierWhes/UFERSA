package Dao;

import java.util.Scanner;

import Entity.Veiculo;

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
	
	public void Remover(String placa, long chave) {
		Veiculo remover = this.Buscar(placa, chave);
		boolean flag = ((remover != null) ? true: false);
		if(flag) {
			System.out.println(remover.toString());
			
			System.out.println("Tem certeza que deseja remover? (S/N)");
			String escolha = cin.next();
			
			switch(escolha) {
			case "s": 
			case "S":
				System.out.println("removido.");
				root.Remove(placa, chave);
				break;
			case "n":
			case "N": System.out.println("Naõ removido.");
				break;
			}
		}else {
			System.out.println("Naõ encontrado.");
		}
	}
	
	public Veiculo Buscar(String placa, long chave) {
		return root.Search(placa ,chave);
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
	
	public void ListarVet() {
		root.ListarVet();
	}

	public int Quantidade() {
		
		return root.Amount();
	}

}
