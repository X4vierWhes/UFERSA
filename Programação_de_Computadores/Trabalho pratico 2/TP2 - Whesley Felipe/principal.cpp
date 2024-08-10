#include "biblioteca.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//Função main;
int main(){
	setlocale(LC_ALL, "portuguese");
	//Dados:
	int devolucoes{};
	Datas dataDevolucao{};
	double atraso{};

	//Leitura de dados;
	cout << "Qual o numero de devoluções para hoje? ";
	cin >> devolucoes;
	cout << "Qual a data de devolução: ";
	cin >> dataDevolucao;
	linha( '-', 43); //Função linha que acrescenta "-" no programa a quantidade de vezes desejada;

	//Criando vetor dinamico:

	Biblioteca * vet = new Biblioteca[devolucoes];

	//Entrada de dados com laço for:
	for (short i = 0; i < devolucoes; i++) {
		cin >> vet[i];//Usando istream para leiura de dados;

		/////////////
	
		cout << left; cout.width(10);  cout << "Atraso";
		cout << right; cout.width(2); cout << ": ";
		atraso = vet[i].DatasEmprestimos - dataDevolucao - 3; //calculo de atraso;

		for (short j = 0; atraso < 0; j++) { 
			atraso++; //Zera atraso para que não fique com valores negativos, problema encontrado em testes;
		}

		cout << (int)atraso << " Dia(s)" << endl;
		
		/////////////
	
		cout << left; cout.width(10);  cout << "Multa";
		cout << right; cout.width(4); cout << ": R$";
		cout << int((atraso) * 0.8) << ","; //Parte decimal da multa vezes 0,8 para poder colocar virgula inves de ponto;
		cout.width(2); cout.fill('0');
		cout << (((atraso) * 0.8) - int((atraso) * 0.8)) * 100 << endl; //parte fracionaria;
		cout.fill(' '); //Para não acrescentar 0 nos proximos couts;

		linha('-', 33); 
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//Função resumo: 
	cout << endl;

	 const char * meses[12]{ "Janeiro", "Fevereiro", "Março", "Abril"
		, "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"
	}; // Nome dos meses para fazer função resumo escrevendo por extenso os nomes dos meses: 
	const char* ptr = meses[0];
	cout << "Resumo do dia " << dataDevolucao.dia << " de ";

	for (int k = 0; k <= dataDevolucao.mes; k++) {
		ptr = meses[k - 1]; //Ponteiro que aponta para o const char do mes de devolução;
	}
	cout << ptr << " de " << dataDevolucao.ano << endl << endl;

	///////
	for (short w = 0; w < devolucoes; w++) {
		resumo(&vet[w], &dataDevolucao); //Chama de função resumo;
	}
	cout << endl;
	
	double TotalMultas = SomaMultas(vet, dataDevolucao, devolucoes); //chamada de função que volta o total pago em multas;
	cout.width(2); cout.fill('0');
	cout << "Total em multas: R$" << (int)TotalMultas << ",";
	cout.width(2); cout.fill('0');
	cout << (TotalMultas - (int)TotalMultas) * 100 << endl << endl;
	cout.fill(' ');

	///////////////////////////////////////////////////////////////////////////////////////////////////

	linha('-', 43);

	cout << "Encerrando programa...\n";

	//Deletando vetor dinamico:

	delete[]vet;

	return 0;
}