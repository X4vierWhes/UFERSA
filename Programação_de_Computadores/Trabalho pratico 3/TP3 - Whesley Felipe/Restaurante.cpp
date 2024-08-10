#include "Restaurante.h"

//Inicializações das Funções:

void menu();
void Pedir(Pizzaria*, int);
void Listar(Pizzaria*, int);
void Padronizar(Pizzaria*, int a);
Pizzaria* Adicionar(Pizzaria*, int*, int*,int*);
Pizzaria* Excluir(Pizzaria*, int*, int);
void GerarRecibo(Pizzaria*, int, Pizzaria*, int, char*);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Funções:

void menu() {
	cout << "Sistema de Controle\n"
		"====================\n"
		"(P)edir\n"
		"(A)dicionar\n"
		"(E)xcluir\n"
		"(L)istar\n"
		"(S)air\n"
		"====================\n"
		"Opção: [_]\b\b";
}

void Pedir(Pizzaria* vet, int tamEstoque) {
	cout << "Pedir\n"
		"-----\n";
	cout << "Arquivo: ";
	char arquivo[100]{}; //Tamanho grande para se for necessário colocar o endereço do arquivo
	cin.get();
	cin.getline(arquivo, 100);
	cout << endl;

	int elementosPedido{}, tamPedido{}, expoente{};
	char ignore[40]{};
	Pizzaria* Pedido = new Pizzaria[tamPedido];


	ifstream fin;
	fin.open(arquivo);
	if (!fin.is_open()) {
		cout << "Seu arquivo não pode ser aberto, será encaminhado para o menu principal...\n" << endl;
		system("pause");
		
	}
	else {

		fin.getline(ignore, 40); //pegando toda linha com o nome do restaurante;
		fin.getline(ignore, 40); //pegando os "-----------------";

		while (!fin.eof()) { //Lendo arquivo e colocando em vetor dinamico usando a função adicionar;

			if (elementosPedido >= tamPedido) {
				Pedido = Adicionar(Pedido, &tamPedido, &elementosPedido, &expoente);
				fin >> Pedido[elementosPedido - 1].nome;
				fin >> Pedido[elementosPedido - 1].qntd;
			}
			else {
				fin >> Pedido[elementosPedido].nome;
				fin >> Pedido[elementosPedido].qntd;
				elementosPedido++;
			}
		}

		fin.close(); //fechando arquivo

		Padronizar(Pedido, tamPedido);
		Padronizar(vet, tamEstoque);

		////////////////////////////////////////////////////////////////////////////////////////////////
		//Aqui será juntado as quantidades de pedidos com o mesmo nome;
		int barras{};
		for (int cont = 0; cont < elementosPedido - 1; cont++) {
			if (Pedido[cont].nome[0] == '\0') {
				continue;
			}
			for (int cont2 = 1; cont2 < elementosPedido - 1; cont2++) {
				if (Pedido[cont2].nome[0] == '\0' || (cont == cont2)) {
					continue;
				}

				if (strcmp(Pedido[cont].nome, Pedido[cont2].nome) == 0)
				{

					Pedido[cont].qntd += Pedido[cont2].qntd; //Pedido anterior recebe qntd de seu igual;
					Pedido[cont2].nome[0] = '\0'; //Proximo tem o nome zerado para sair das proximas comparações;
				}
			}
		}

		// Verificando pedido no estoque

		for (int cont2 = 0; cont2 < elementosPedido - 1; cont2++)
		{
			if (Pedido[cont2].nome[0] == '\0')
				continue;
			barras++;
		}

		Pizzaria* vetNovo = new Pizzaria[barras]; //VetNovo que servirá para fazer o primeiro teste do pedido;
		int vetNovoCont{};
		for (int i{}; i < tamEstoque; i++) {

			for (int j{}; j < elementosPedido - 1; j++) {
				if (Pedido[j].nome[0] == '\0')
					continue;

				if (strcmp(vet[i].nome, Pedido[j].nome) == 0) {
					vetNovo[vetNovoCont] = vet[i];
					vetNovoCont++;
				}
			}
		}


		// Testando pedido;
		bool flag = true;   //Servirá como "CHAVE" para criar o recibo e realmente fazer o pedido, 
		int cont{};        //Se teste der erro de alguma forma será trocada para "FALSE" e cancelará o pedido;
		int contGlobal{}; //Contador que servirá para testar se produto existe;

		for (int j{}; j < elementosPedido - 1; j++) {
			contGlobal = 0;
			if (Pedido[j].nome[0] == '\0')
				continue;

			for (int i{}; i < vetNovoCont; i++) {
				if (strcmp(vetNovo[i].nome, Pedido[j].nome) == 0) {
					contGlobal++;

					if (Pedido[j].qntd > vetNovo[i].qntd) {
						cont++;
						if (cont <= 1) {
							cout << "Pedido falhou!\n";
						}

						cout << Pedido[j].nome << ": Solicitado = " << Pedido[j].qntd << "kg / Em estoque = " << vetNovo[i].qntd << "kg" << endl;

						flag = false;
					}
					else {
						vetNovo[i].qntd -= Pedido[j].qntd;
					}
				}
				else {
					if ((i == (vetNovoCont - 1)) && (contGlobal == 0)) {
						cont++;
						if (cont <= 1) {
							cout << "Pedido falhou!\n";
						}
						cout << Pedido[j].nome << " Não existe no estoque." << endl;
						flag = false;
					}
				}
			}
		}
		if (vetNovoCont == 0) { //Se não existir nenhum dos arquivos do pedido no estoque, flag será false;
	
			for (int j{}; j < elementosPedido - 1; j++) {

				if (j < 1) {
					cout << "Pedido falhou!\n";
				}
				if (Pedido[j].nome[0] == '\0')
					continue;

				cout << Pedido[j].nome << " Não existe no estoque." << endl;
				
			}
			flag = false;

		
		}
		delete[] vetNovo; //Deletando vetNovo;

		cout << endl << endl;

		if (flag) {
			for (int i{}; i < tamEstoque; i++) {
				for (int j{}; j < elementosPedido - 1; j++) {
					if (Pedido[j].nome[0] == '\0')
						continue;

					if (strcmp(vet[i].nome, Pedido[j].nome) == 0) {
						vet[i].qntd -= Pedido[j].qntd;
					}
				}
			}
			GerarRecibo(vet, tamEstoque, Pedido, elementosPedido - 1, arquivo);
			cout << "Pedido realizado com sucesso...\n"
				"Recibo enviado por E-MAIL...\n\n";
		}



		delete[] Pedido; //Deletando pedido;


		system("pause");
	}
}

void Listar(Pizzaria* estoque, int tam) {
	cout << "Listagem\n"
		"--------\n";

	Padronizar(estoque, tam);

	for (int i{}; i < tam; i++) {
		cout << left; cout.width(10);
		cout << estoque[i].nome;
		cout.width(4);
		cout << " - R$";
		cout << fixed;  cout.precision(2); 
		cout.width(5);
		cout << estoque[i].preco;
		cout.width(3);
		cout << " - ";
		cout << estoque[i].qntd;
		cout << "kg.\n";
	}

	system("pause");
}

void Padronizar(Pizzaria* vet, int tam) {

	for (int i{}; i < tam; i++) { //Aqui será feito a padronização dos nomes para primeira letra maiscula e as seguintes minusculas;

		for (int j{}; vet[i].nome[j] != '\0'; j++) {
			vet[i].nome[0] = toupper(vet[i].nome[0]);
			vet[i].nome[j + 1] = tolower(vet[i].nome[j + 1]);
		}

	}
}

Pizzaria* Adicionar(Pizzaria* vet, int* tam, int* elementos, int* n) {
	
	Pizzaria* aux = new Pizzaria[*tam + pow(2, *n)]; //criando endereço auxiliar que cresce 
	*elementos += 1;
	for (int i{}; i < *elementos - 1; i++) {
		aux[i] = vet[i]; //copiando elementos;
	}

	delete[]vet;
	*tam += pow(2, *n);
	*n+=1;
	vet = aux;

	return vet;
}

Pizzaria* Excluir(Pizzaria* vet, int* elementos, int escolha) {
	//Como será eliminado somente um elemento do vetor, pensei não ser necessário criar um vetor com o tamanho menor, somente sobrescreve-lo;

	for (int i = escolha; i < *elementos; i++) {
		vet[i - 1] = vet[i]; //Eliminando elemento escolhido;
	}

	vet[*elementos - 1] = vet[*elementos]; //Copiando ultimo elemento que acaba se perdendo com o for;

	*elementos -= 1; //Diminuindo a quantidade de elementos

	return vet;
}

void GerarRecibo(Pizzaria* vet, int tamEstoque, Pizzaria* Pedido, int tamPedido, char* arquivo) {

	ofstream fout;
	double compra{}, desconto{};
	for (int i{}; arquivo[i] != '\0'; i++) {
		if (arquivo[i] == '.') {
			arquivo[i + 1] = '\0';
		}
	}
	strcat(arquivo, "nfc");

	fout.open(arquivo);

	fout << "Pizzaria Mamute\n"
		"--------------------------------------------------\n";
	for (int i{}; i < tamEstoque; i++) {
		for (int j{}; j < tamPedido; j++) {
			if (Pedido[j].nome[0] == '\0')
				continue;

			if (strcmp(vet[i].nome, Pedido[j].nome) == 0) { 
				fout << left; fout.width(11);
				fout << vet[i].nome;
				fout.width(2);
				fout << Pedido[j].qntd;
				fout << "kg";
				fout << right; fout.width(4);
				fout << "a";
				fout << right; fout.width(3);
				fout << " ";
				fout << fixed; fout.precision(2); fout.width(4);
				fout << double(vet[i].preco);
				if (double(vet[i].preco) >= 10.00) {
					fout << left; fout.width(6);
				}
				else {
					fout << left; fout.width(7);
				}
				fout << "/kg";
				fout << right; fout.width(1);
				fout << "=";
				fout.width(6);
				fout << "R$";
				fout << left;
				fout << Pedido[j].qntd * vet[i].preco;
				fout << endl;
				compra += Pedido[j].qntd * vet[i].preco;
			}
		}
	}
	if (compra >= 1000.00) {
		desconto = compra * 0.10;
	}

	fout << "--------------------------------------------------\n";
	fout << right; fout.width(31);
	fout << "Compra";
	fout.width(3);
	fout << "=";
	fout.width(5);
	fout << "R$";
	fout << compra;
	fout << endl;
	fout << right; fout.width(31);
	fout << "Desconto";
	fout.width(3);
	fout << "=";
	fout.width(5);
	fout << "R$";
	fout << desconto;
	fout << endl;
	fout << right; fout.width(31);
	fout << "Total";
	fout.width(3);
	fout << "=";
	fout.width(5);
	fout << "R$";
	fout << compra - desconto;
	fout << endl;

	fout.close();
}