package lanches;

import decorator.LancheDecorator;
import interfaces.Lanche;

public class MistoQuente extends LancheDecorator {

	public MistoQuente(Lanche lanche) {
		super(lanche);
	}

	@Override
	public String name() {
		return "Misto Quente";
	}

	@Override
	public double value() {
		return lanchedecorado.value() + 5.2;
	}

}
