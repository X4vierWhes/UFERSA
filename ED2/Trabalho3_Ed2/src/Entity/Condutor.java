package Entity;

public class Condutor {
	private String name;
	private String cpf;

	///////////////////////////////////////////
	// Construtores

	public Condutor() {
		setName(" ");
		setCpf(" ");
	}

	public Condutor(String name, String cpf) {
		setName(name);
		setCpf(cpf);
	}
	///////////////////////////////////////////
	// Getters e Setters
	public String getName() {
		return name;
	}

	@SuppressWarnings("null")
	public void setName(String name) {

		if (name != null && !(name.equals(" "))) {
			this.name = name;
		} else {
			this.name = "Não Informado";
		}
	}

	public String getCpf() {
		return cpf;
	}

	@SuppressWarnings("null")
	public void setCpf(String cpf) {
		if (cpf != null && !(cpf.equals(" "))) {
			this.cpf = cpf;
		} else {
			this.cpf = "000.000.000-00";
		}
	}

}
