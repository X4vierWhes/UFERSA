package Dao;

import java.util.List;

public class Servidor<T> {
	ArvoreAVL<T> root;
	
	//Construtores
	public Servidor() {
		root = new ArvoreAVL<T>();
	}
	
	public T buscarRenavam(long renavam) {
		return root.BuscarRenavam(renavam);
		
	}
	
	public void cadastrar(T elemento) {
		root.Add(elemento);
	}
	
	public void remover(T elemento) {
		root.Remover(elemento);
	}
	
	public void listar() {
		root.Ordem();
	}
	
	public List<T> OrdemToArray(){
		return root.OrdemToArray();
	}

	public int Quantidade() {
		
		return root.Quantidade();
	}

}
