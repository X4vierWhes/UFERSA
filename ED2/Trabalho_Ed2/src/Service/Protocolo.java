package Service;

import java.util.List;

import Dao.Servidor;

public class Protocolo<T> {
	Servidor<T> server;
	
	public Protocolo(){
		server = new Servidor<T>();
	}
	
	public T buscarRenavam(long renavam) {
		return server.buscarRenavam(renavam); 
	}
	
	public void cadastrar(T elemento) {
		server.cadastrar(elemento);
	}
	
	public void remover(T elemento) {
		server.remover(elemento);
	}
	
	public void listar() {
		server.listar();
	}
	
	public List<T> OrdemToArray(){
		return server.OrdemToArray();
	}

	public int Quantidade() {
		
		return server.Quantidade();
	}


}
