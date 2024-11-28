package lanches;

import decorator.LancheDecorator;
import interfaces.Lanche;

public class MilkShake extends LancheDecorator{

	public MilkShake(Lanche lanche) {
		super(lanche);
	}

	@Override
	public String name() {
		return "Milk Shake";
	}

	@Override
	public double value() {
		return 12.50;
	}

}
