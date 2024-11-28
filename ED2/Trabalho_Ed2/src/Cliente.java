import java.util.List;
import Service.Protocolo;

public class Cliente<T> {
	
	Protocolo<T> protocol;
	
	public Cliente() {
		protocol = new Protocolo<T>();
	}
	
	
	public T BuscarRenavam(long renavam) {
		return protocol.buscarRenavam(renavam);
	}
	
	public void Cadastrar(T elemento) {
		protocol.cadastrar(elemento);
	}
	
	public void Remover(T elemento) {
		protocol.remover(elemento);
	}
	
	public void Listar() {
		protocol.listar();
	}
	
	public List<T> OrdemToArray(){
		return protocol.OrdemToArray();
	}
	
	public int Quantidade() {
		return protocol.Quantidade();
	}

	
	
}
