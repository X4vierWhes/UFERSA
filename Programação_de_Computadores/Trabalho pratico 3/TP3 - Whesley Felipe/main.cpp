#include "Restaurante.h"

/////////////////////////////////////////////////////////////////////////////////////////////
//Fun��o main:
int main() {
	setlocale(LC_ALL, "portuguese");
	ifstream fin;
	ofstream fout;
	int tamEstoque{}, elementos{}, excluir{}, expoente{};
	char ch{}, escolha{};
	bool chave = true;
	Pizzaria* Estoque; //Vetor estoque que servir� como auxiliar;

	fin.open("Estoque.dat", ios_base::in | ios_base::binary); //Abrindo estoque;
	
	if (!fin.is_open()) {
		cout << "Seu arquivo n�o pode ser aberto, ser� encaminhado para o menu principal...\n" << endl;
		system("pause");
		system("cls");
		Estoque = new Pizzaria[tamEstoque];
	}
	else {
		fin.read((char*)&expoente, sizeof(int));
		fin.read((char*) &tamEstoque, sizeof(int));
		fin.read((char*) &elementos, sizeof(int));

		Estoque = new Pizzaria[tamEstoque];

		for (int i{}; i < elementos; i++) {
			fin.read((char*) &Estoque[i], sizeof(Estoque[i]));
		}
	}

	fin.close();

	Pizzaria* vet = Estoque; //Ponteiro principal;
	while (escolha != 's' && escolha != 'S') {
		
		menu(); //Chamando menu;	
		cin >> escolha;

		switch (escolha) {
		case 'p': //Pedir;
		case 'P': system("cls");
			Pedir(vet, tamEstoque); //Chamada da fun��o pedido que leva endere�o de vetor de Pizzaria e seus tamanho respectivo;
			break;

		case 'a': //Adicionar;
		case 'A': system("cls");
			chave = true; //Chave servir� como parametro se o novo produto existe ou n�o, se for TRUE: N�O EXISTE, FALSE: EXISTE;
			if (elementos == tamEstoque) { //Se elementos maior ou igual ao tamanho do estoque ser� criado um vetor maior que comporte o novo produto;
				vet = Adicionar(vet, &tamEstoque, &elementos, &expoente); //Chamada fun��o que adicionara elementos e crescer� vetor;
				cout << "Adicionar\n"
					"---------\n";
				cout << "Produto: ";
				cin >> vet[elementos - 1].nome;
				Padronizar(vet, elementos); //Padroniza nome para comparar;
				for (int i{}; i < elementos - 1 && chave; i++) {
					if (strcmp(vet[i].nome, vet[elementos - 1].nome) == 0) {
						cout << vet[i].nome << " j� existe no estoque.\n";
						cout << "Atualize o pre�o: ";
						cin >> vet[i].preco;
						cout << "Atualize a quantidade: ";
						cin >> vet[i].qntd;
						chave = false;
						system("cls");
						cout << "Estoque atualizado com sucesso...\n\n";
						elementos--;
					}
					else {
						chave = true;
					}
					
					
				}
				if (chave) {
					cout << "Pre�o: ";
					cin >> vet[elementos - 1].preco;
					cout << "Quantidade: ";
					cin >> vet[elementos - 1].qntd;
					system("cls");
					cout << "Item adicionado com sucesso...\n\n";
				}
		
			}
			else { // Senao, ser� lido somente o elemento e aumentado o tamanho de elementos;
				cout << "Adicionar\n"
					"---------\n";
				cout << "Produto: ";
				
				cin >> vet[elementos].nome;
				elementos++;
				Padronizar(vet, elementos);
				for (int i{}; i < elementos - 1  && chave; i++) {
					if (strcmp(vet[i].nome, vet[elementos - 1].nome) == 0) {
						cout << vet[i].nome << " j� existe no estoque.\n";
						cout << "Atualize o pre�o: ";
						cin >> vet[i].preco;
						cout << "Atualize a quantidade: ";
						cin >> vet[i].qntd;
						chave = false;
						system("cls");
						cout << "Estoque atualizado com sucesso...\n\n";
						elementos--;
					}
					else {
						chave = true;
					}


				}
				if (chave) {
					cout << "Pre�o: ";
					cin >> vet[elementos - 1].preco;
					cout << "Quantidade: ";
					cin >> vet[elementos - 1].qntd;
					system("cls");
					cout << "Item adicionado com sucesso...\n\n";
					

				}
			}
			
			system("pause");

			break;

		case 'e': //Excluir;
		case 'E':  system("cls");
			cout << "Excluir\n"
				    "-------\n";
			for (int i{}; i < elementos; i++) {
				cout << i + 1 << ") " << vet[i].nome << endl;
			}
			cout << "N�mero do produto: ";
			cin >> excluir;
			cout << "Deseja excluir \"";
			cout << vet[excluir - 1].nome;
			cout << "\" (S/N)? ";
			cin >> ch;
			cout << endl;

			if ((ch == 's' || ch == 'S')) {
				vet = Excluir(vet, &elementos, excluir);
				system("cls");
				cout << "Item excluido com sucesso...\n\n";
			}
			else {
				system("cls");
				cout << "Voltando para o menu principal...\n\n";
			}

			system("pause");
			break;

		case 'l': //Listar;
		case 'L': system("cls");
			Listar(vet, elementos); //Chamada da fun��o Listar, que mostra os produtos do estoque;
			break;

		case 's': //Sair;
		case 'S':  system("cls");
			break;

		default: cout << "Op��o invalida...\n"; 
			system("pause");
			cin.clear(); //Prevenir de erros de bug no cin;
			break;
		}
		system("cls");

	}

	fout.open("Estoque.dat", ios_base::out | ios_base::binary ); //Salvando estoque;

		fout.write((char*) &expoente, sizeof(int));
		fout.write((char*) &tamEstoque, sizeof(int));
		fout.write((char*) &elementos, sizeof(int));

		for (int i{}; i < elementos; i++) {
			fout.write((char*) &vet[i], sizeof(vet[i]));
		}

	fout.close();

	delete[]vet; //Deletando conteudo em vet;
}

