import concretos.Lanchonete;
import interfaces.Lanche;
import lanches.MilkShake;
import lanches.MistoQuente;
import lanches.Pastel;

public class Main  {

	public static void main(String [] args) {
		Lanche lanche = new Lanchonete();
		lanche = new MistoQuente(new MilkShake(new Pastel(lanche)));
		System.out.println(lanche.value());
	}

}
