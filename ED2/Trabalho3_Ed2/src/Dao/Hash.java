package Dao;

import java.util.Scanner;

import Entity.Veiculo;

public class Hash {
	Node[] root;
	
	private int tam;
	private int elementos;
	private boolean openAdress;
	private Scanner cin = new Scanner(System.in);
	
	///////////////////////////////////////////////////////////////////////////////
	//Construtores
	public Hash(int tam, boolean adress) {
		if(adress) { //Endereçamento aberto
			this.tam = calcTam(tam);
			root = new Node[this.tam];
			this.elementos = 0;
			
			if(this.tam >= tam) {
				for(int i = 0; i < this.tam; i++) {
					root[i] = new Node();
				}
			}else {
				System.out.println("Error");
			}
			
			this.openAdress = true;
			Arquivo.logFc(this.calcFc());
			
		}else { //Endereçamento fechado
			this.tam = calcTam(tam);
			root = new Node[this.tam];
			this.elementos = 0;
			
			if(this.tam >= tam) {
				for(int i = 0; i < this.tam; i++) {
					root[i] = new Node();
				}
			}else {
				System.out.println("Error.");
			}
			this.openAdress = false;
			Arquivo.logFc(this.calcFc());
		}
	}
	
	//Função que calcula o tamanho procurando o primo mais proximo;
	public int calcTam(int tam) {
		int newTam = tam*2;
		boolean flag = true;
		
		while(flag) {
			if(isPrimo(newTam)) {
				flag = false;
			}else {
				newTam--;
			}
		}
		
		return newTam;
	}
	
	public double calcFc() {
	    return (double) this.elementos / this.tam;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	//Funções de inserir
	
	public void Insert(Veiculo inserir) {
		//////////////////////////////////////////////////////////////////////////
		//Calculando index que o veiculo será inserido
		int index = (int) (Math.abs(inserir.getChave())%this.tam);
		
		/////////////////////////////////////////////////////////////////////////
		//acrescentar
		if(openAdress) { //Se escolhido opção de endereçamento aberto
			this.OpenInsert(this.root, inserir, index);
		}else { //Se escolhido opção de endereçamento exterior/Fechado
			this.ClosedInsert(this.root[index], inserir, index);
		}
		
	}
	
	//Inserir em endereçamento aberto
	private void OpenInsert(Node[] root, Veiculo cadastrar, int index) {
		boolean flag = true;
		while(flag) {
			if(root[index] != null) {
				if(root[index].getValor() == null) {
					root[index] = new Node(cadastrar);
					this.elementos++;
					Arquivo.logADD(cadastrar);
					Arquivo.logFc(this.calcFc());
					flag = false;
				}else {
					index++;
				}
			}
		}
	}
	
	//Inserir em endereçamento exterior/fechado
	private void ClosedInsert(Node root, Veiculo cadastrar, int index) {
	    boolean flag = true;
	    while (flag) {
	        if (root.getValor() == null) {
	            root.setValor(cadastrar); // Define o valor do nó atual como o veículo a ser inserido
	            this.elementos++;
	            Arquivo.logADD(cadastrar);
	            Arquivo.logFc(this.calcFc());
	            flag = false;
	        } else if (root.getNext() == null) {
	            Node newNode = new Node(cadastrar);
	            root.setNext(newNode); // Define o próximo nó como o novo nó com o veículo
	            this.elementos++;
	            Arquivo.logADD(cadastrar);
	            Arquivo.logFc(this.calcFc());
	            flag = false;
	        } else {
	            root = root.getNext(); // Avança para o próximo nó na lista
	        }
	    }
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////////
	//Funções de Remover	
	public void Remove(String placa, long key) {
		//////////////////////////////////////////////////////////////////////////
		//Calculando index que o veiculo será removido
		int index = (int)(key%this.tam);
		
		//////////////////////////////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////////////////
		//acrescentar
		if(openAdress) { //Se escolhido opção de endereçamento aberto
			this.OpenRemove(this.root, index, placa);
		}else { //Se escolhido opção de endereçamento exterior/Fechado
			this.ClosedRemove(this.root[index], placa);
		}
		
	}
	
	private void ClosedRemove(Node root, String placa) {
	    if (root == null) {
	        return; // A lista está vazia, nada para remover
	    }
	    Veiculo copia = root.getValor();
	    Node prevNode = null;
	    Node currentNode = root;
	    
	    while (currentNode != null) {
	        if (currentNode.getValor() != null && currentNode.getValor().getPlaca().equals(placa)) {
	            if (prevNode == null) {
	                // Remover o primeiro nó da lista
	                root.setValor(null);
	            } else {
	                // Remover um nó no meio ou no final da lista
	                prevNode.setNext(currentNode.getNext());
	            }
	            this.elementos--;
	            Arquivo.logREMOVE(copia);
	            Arquivo.logFc(this.calcFc());
	            return; // Veículo removido com sucesso
	        }
	        prevNode = currentNode;
	        currentNode = currentNode.getNext();
	    }
	}

	private void OpenRemove(Node[] root, long key, String placa) {
	    int index = (int) (key % this.tam);
	    if (index < 0) {
	        return; // Índice negativo, saia da função
	    }

	    while (true) {
	        if (root[index] != null && root[index].getValor() != null && root[index].getValor().getPlaca().equals(placa)) {
	            // Encontrou o nó a ser removido
	            //System.out.println("Encontrou.");
	        	Arquivo.logREMOVE(root[index].getValor());
	            if (index + 1 < root.length && root[index + 1] != null && root[index + 1].getIndex() == index) {
	                root[index] = root[index + 1];
	                index++;
	            } else {
	                root[index] = null;
	                elementos--;
	                Arquivo.logFc(this.calcFc());
	                break; // Sai do loop após a remoção bem-sucedida
	            }
	        } else {
	            // Não encontrou, passa para o próximo índice
	            index++;

	            // Verifica se atingiu o final do array
	            if (index >= root.length) {
	                break; // Sai do loop se o final do array for atingido
	            }
	        }
	    }
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	//Funções de Edição
	public boolean Edit(String placa, long chave) {
		int index = (int) (chave%this.tam);
		if(openAdress) {
			if(this.OpenEdit(this.root, placa, index)) {
				return true;
			}
			return false;
		}else {
			if(this.ClosedEdit(this.root[index], placa)) {
				return true;
			}
		}
		
		return false;
	}
	
	private boolean ClosedEdit(Node node, String placa) {
	    boolean flag = true;

	    while (flag) {
	        if (node != null && node.getValor() != null && node.getValor().getPlaca().equals(placa)) {
	            // Encontrou o veículo a ser editado
	            System.out.println("Editar NOME do condutor: ");
	            node.getValor().setName(cin.next());
	            System.out.println("Editar CPF do condutor: ");
	            node.getValor().setCpf(cin.next());
	            System.out.println("Editar PLACA do veículo: ");
	            node.getValor().setPlaca(cin.next());
	            System.out.println("Editar Modelo do veículo: ");
	            node.getValor().setModelo(cin.next());
	            System.out.println("Editar Ano de FABRICAÇÃO do veículo: ");
	            node.getValor().setFabricacao(cin.nextInt());
	            return true; // Retorna true após a edição bem-sucedida
	        } else if (node == null || node.getValor() == null) {
	            flag = false; // Não encontrou o veículo, pode sair do loop
	        } else {
	            node = node.getNext(); // Avança para o próximo nó na lista
	        }
	    }
	    cin.close();
	    return false; // Retorna false se o veículo não for encontrado
	}

	private boolean OpenEdit(Node[] root, String placa, int index) {
		 
		 boolean flag = true;
		    while (flag) {
		        if (index >= 0 && index < root.length && root[index] != null && root[index].getValor() != null) {
		            if (root[index].getValor().getPlaca().equals(placa)) {
		            	System.out.println("Editar NOME do condutor: ");
		            	root[index].getValor().setName(cin.next());
		            	System.out.println("Editar CPF do condutor: ");
		            	root[index].getValor().setCpf(cin.next());
		            	System.out.println("Editar PLACA do veiculo: ");
		            	root[index].getValor().setPlaca(cin.next());
		            	System.out.println("Editar Modelo do veiculo: ");
		            	root[index].getValor().setModelo(cin.next());
		            	System.out.println("Editar Ano de FABRICACAO do veiculo: ");
		            	root[index].getValor().setFabricacao(cin.nextInt());
		                return true; // Retorna o valor encontrado
		            } else {
		                index++;
		            }
		        } else {
		            flag = false; // Não encontrou o elemento, pode sair do loop
		        }
		    }
		    cin.close();
		    return false; // Retorna null se o valor não for encontrado
		
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////
	//Funções de Buscar	
	public Veiculo Search(String placa, long key) {
	    int index = (int)(key%this.tam);
	    Veiculo encontrado = null;
	    if (openAdress) { // Buscar por endereçamento aberto
	         encontrado = this.OpenSearch(root, placa, index);
	        if (encontrado != null) {
	            return encontrado;
	        } else {
	           return null;
	        }
	    } else { // Buscar por endereçamento fechado
	    	 encontrado = this.ClosedSearch(root[index], placa, index);
		        if (encontrado != null) {
		            return encontrado;
		        } else {
		           return null;
		        }
	    }
	}
	
	
	private Veiculo ClosedSearch(Node root, String placa, int index) {
		boolean flag = true;
		Node prev = null;
		while(flag) {
			if (index >= 0 && index < this.tam && root != null && root.getValor() != null) {
	            if (root.getValor().getPlaca().equals(placa)) {
	            	Veiculo encontrado = root.getValor();
	            	Node no = this.root[index];
	            	while(no != null) {
	            		if(no.getValor().getPlaca().equals(placa)) {
	            			if(prev != null) {
	            				prev.setNext(no.getNext());
	            				no.setNext(this.root[index]);
	            				this.root[index] = no;
	            			}
	            		}
	            		
	            		prev = no;
	            		no = no.getNext();
	            	}
	            	
	                return encontrado; // Retorna o valor encontrado
	            } else {
	            	prev = root;
	                root = root.getNext();
	            }
	        } else {
	            flag = false; // Não encontrou o elemento, pode sair do loop
	        }
		}
		return null;
	}


	private Veiculo OpenSearch(Node[] root, String placa, int index) {
	    boolean flag = true;
	    while (flag) {
	        if (index >= 0 && index < root.length && root[index] != null && root[index].getValor() != null) {
	            if (root[index].getValor().getPlaca().equals(placa)) {
	                return root[index].getValor(); // Retorna o valor encontrado
	            } else {
	                index++;
	            }
	        } else {
	            flag = false; // Não encontrou o elemento, pode sair do loop
	        }
	    }
	    return null; // Retorna null se o valor não for encontrado
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	//Funções de listagem
	public void List() {
	    //System.out.println(this.tam + " - " + this.elementos);
	    if (openAdress) {
	        if (elementos != 0) {
	            for (int i = 0; i < this.tam; i++) {
	                if (root[i] != null && root[i].getValor() != null) { // Verifique se root[i] e root[i].getValor() não são nulos
	                    System.out.println(root[i].getValor().toString());
	                }
	            }
	        } else {
	            System.out.println("Hash vazia.");
	        }
	    } else {
	    	// Lógica para endereçamento exterior/Fechado
	    	
	    	System.out.println("-------------------------------------------");
	        for (int i = 0; i < this.tam; i++) {
	            Node currentNode = root[i];
	            while (currentNode != null) {
	                if (currentNode.getValor() != null) {
	                    System.out.println(currentNode.getValor().toString());
	                }
	                currentNode = currentNode.getNext();
	            }
	        }
	    }
	}
	////////////////////////////////////////////////////////////////////////////////////////////////
	//Funções de suporte
	// Função para verificar se um número é primo
    public static boolean isPrimo(int num) {
        if (num <= 1) {
            return false; // 0 e 1 não são primos
        }
        if (num <= 3) {
            return true; // 2 e 3 são primos
        }
        if (num % 2 == 0 || num % 3 == 0) {
            return false; // Números divisíveis por 2 ou 3 não são primos
        }

        // Verifica divisibilidade a partir de 5
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false; // Se for divisível por i ou i + 2, não é primo
            }
        }

        return true; // Se não foi divisível por nenhum número até a raiz quadrada, é primo
    }

	public int Amount() {
		return this.elementos;
	}
	
	public void PrintVector(long keyPrintar) {
		int index = (int) (keyPrintar % this.tam);
	    if (index < 0 || index >= tam) {
	        System.out.println("Índice inválido");
	        return;
	    }

	    System.out.print("Índice " + index + ": [");

	    Node currentNode = root[index];
	    StringBuilder valuesString = new StringBuilder();

	    boolean first = true;

	    while (currentNode != null) {
	        if (currentNode.getValor() != null) {
	            if (!first) {
	                valuesString.append(" "); // Adiciona um espaço entre os valores
	            }
	            valuesString.append(currentNode.getValor().getName() + ", " + currentNode.getCount());
	            first = false;
	        }
	        currentNode = currentNode.getNext();
	    }

	    System.out.print(valuesString.toString());
	    System.out.println("]");
	}



}

class Node {
	private Veiculo valor;
	private Node next;
	private Node prev;
	private long chave;
	private int index;
	private int count;

	public Node() {
		this.setChave(-1);
		this.setValor(null);
		this.setNext(null);
		this.setPrev(null);
		this.setIndex(-1);
		this.setCount(0);

	}

	public Node(Veiculo value) {
		this.setIndex(value.getChave());
		this.setChave(value.getChave());
		this.setValor(value);
		this.setNext(null);
		this.setPrev(null);
		this.setCount(0);
	}
	
	public String toString() {
	    if (this.prev != null && this.next != null) {
	        return "-------------------------------------------\n" +
	               "Next: " + (this.next.getValor() != null ? this.next.getValor().getName() : "Null") + "\n" +
	               "Prev: " + (this.prev.getValor() != null ? this.prev.getValor().getName() : "Null") + "\n" +
	               this.valor.toString();
	    } else if (this.next != null) {
	        return "-------------------------------------------\n" +
	               "Next: " + (this.next.getValor() != null ? this.next.getValor().getName() : "Null") + "\n" +
	               "Prev: Null\n" +
	               this.valor.toString();
	    } else if (this.prev != null) {
	        return "-------------------------------------------\n" +
	               "Next: Null\n" +
	               "Prev: " + (this.prev.getValor() != null ? this.prev.getValor().getName() : "Null") + "\n" +
	               this.valor.toString();
	    } else {
	        return "-------------------------------------------\n" +
	               "Next: Null\n" +
	               "Prev: Null\n" +
	               this.valor.toString();
	    }
	}

	

	public Node getNext() {
		return this.next;
	}

	public void setNext(Node next) {
		this.next = next;
	}

	public Veiculo getValor() {
		return valor;
	}

	public void setValor(Veiculo valor) {
		this.valor = valor;
	}

	public long getChave() {
		return chave;
	}

	public void setChave(long chave) {
		this.chave = chave;
	}

	public long getIndex() {
		return index;
	}

	public void setIndex(long index) {
		this.index = (int)index%100;
	}

	public int getCount() {
		return count;
	}

	public void setCount(int count) {
		this.count = count;
	}
	
	public void incrementCount() {
		this.count++;
	}

	public Node getPrev() {
		return prev;
	}

	public void setPrev(Node prev) {
		this.prev = prev;
	}

}