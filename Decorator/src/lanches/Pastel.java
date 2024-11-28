package lanches;

import decorator.LancheDecorator;
import interfaces.Lanche;

public class Pastel extends LancheDecorator {

	public Pastel(Lanche lanche) {
		super(lanche);

	}

	@Override
	public String name() {
		return "Pastel";
	}

	@Override
	public double value() {
		return 8.50;
	}

}
