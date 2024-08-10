#include "biblioteca.h"

//Fun��es com operator: 
istream& operator>>(istream& is, Datas& m){
	is >> m.dia;
	is.get();
	is >> m.mes;
	is.get();
	is >> m.ano;

	return is;
}

ostream& operator<<(ostream& os, Datas& m) {
	cout.width(2); cout.fill('0');
	os << m.dia;
	cout.width(1);
	os << "/";
	cout.width(2); cout.fill('0');
	os << m.mes;
	cout.width(1);
	os << "/";
	cout.width(2); cout.fill('0');
	os << m.ano;

	return os;
}

istream& operator>>(istream& is, Biblioteca& m){
	cout << left; cout.width(10);  cout << "Aluno";
	cout << right; cout.width(2); cout << ": ";
	is >> m.matricula;
	cout << left; cout.width(10);  cout << "Livro";
	cout << right; cout.width(2); cout << ": ";
	is >> m.identificador;
	cout << left; cout.width(10);  cout << "Emprestimo";
	cout << right; cout.width(2); cout << ": ";
	is >> m.DatasEmprestimos;

	return is;
}

int operator-(Datas& Inicio, Datas& Fim) {
	int Meses[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int Dias = 0;
	/*Calculo de dias: o parametro da fun��o inicia no mes de Inicio/Data de emprestimo e vai at� o mes anterior ao de devolu��o, no fim, � somado o total de dias + 
	do mes de devolu��oo subraido pelos dias do mes de emprestimo.*/

	for (short i = Inicio.mes; i < Fim.mes; i++) {
		Dias += Meses[i - 1];
	}
	return Dias - Inicio.dia + Fim.dia;
}

//fun��es normais:

void linha(char ch, int repeticoes) {
	for (short i = 0; i < repeticoes; i++) {
		cout << ch;
	}
	cout << endl;
}

void resumo(Biblioteca* vet, Datas* dataDevolucao) {
	double atraso{};

	atraso = (vet->DatasEmprestimos - *dataDevolucao - 3);

	for (short i = 0; atraso < 0; i++) {
		atraso++; //Zera atraso se for menor que 0;
	}
	
	cout << vet->matricula << " " << vet->identificador << " ";
	cout << vet->DatasEmprestimos;
	cout << " -> " << "R$" << int((atraso) * 0.8) << ",";
	cout.width(2); cout.fill('0');
	cout << (((atraso) * 0.8) - int((atraso) * 0.8)) * 100 << endl; 
	cout.fill(' '); //Para n�o acrescentar 0 nos proximos couts;

}

double SomaMultas(Biblioteca vet[], Datas dataDevolucao, int tam) {
	double TotalMultas{}, Multas{}, atraso{};
	for (short i = 0; i < tam; i++) {

		atraso = vet[i].DatasEmprestimos - dataDevolucao - 3;

		for (short j = 0; atraso < 0; j++) {
			atraso++; //Zera atraso para que n�o fique com valores negativos, problema encontrado em testes;
		}
		
		Multas = atraso * 0.8;
		TotalMultas += Multas;
		
	}
	
	return TotalMultas;
}