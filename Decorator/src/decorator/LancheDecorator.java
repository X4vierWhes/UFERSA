package decorator;

import interfaces.Lanche;

public abstract class LancheDecorator implements Lanche{
	public Lanche lanchedecorado;

	protected LancheDecorator(Lanche lanche){
		lanchedecorado = lanche;
	}

}