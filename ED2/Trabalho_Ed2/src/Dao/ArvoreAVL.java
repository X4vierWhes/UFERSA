package Dao;

import java.util.ArrayList;
import java.util.List;

import Entity.Veiculo;

public class ArvoreAVL<T> {
	  Node<T> root;
	
	 

////////////////////////////////////////////////////////////
	  //Construtores:
	  public ArvoreAVL() {
		  this.root = null;
	  }
	  
	 
/////////////////////////////////////////////////////////////	 
	 //Funções:
	  //Retorna quantidade em numeros na arvore0
	  public int Quantidade() {
		  return this.Quantidade(this.root);
	  }
	  
	  private int Quantidade(Node<T> node) {
	        if (node == null)
	            return 0;
	        return 1 + Quantidade(node.getEsquerda()) + Quantidade(node.getDireita());
	    }
	 
	 //Funçao de ordem
	 public void Ordem() {
		 this.Ordem(getRaiz());
	 }
	 
	 private void Ordem(Node<T> node) {
		 if(node != null) {
			// Veiculo veiculo = (Veiculo) node.getValor();
			 this.Ordem(node.getEsquerda());
			 //node.getChave() + " : " +
			 System.out.println(node.toString());
			 this.Ordem(node.getDireita());
			 
		 }
		 return;
	 }
	 
	 public List<T> OrdemToArray() {
		 List<T> lista = new ArrayList<T>();
		 OrdemToArray(root, lista);
		 return lista;
	 }
	 
	 public void OrdemToArray(Node<T> noAtual, List<T> lista){
		 
		 if(noAtual != null) {
			 this.OrdemToArray(noAtual.getEsquerda(), lista);
			 lista.add(noAtual.getValor());
			 this.OrdemToArray(noAtual.getDireita(), lista);
		 }else {
			 return;
		 }
	 }
	 
	//Funcao para calcular o balanceamento do no
	public void VerificarBalanceamento() {
		root = VerificarBalanceamento(root);
	}
	
	//Função de altura
	public int Altura(Node<T> no) {
		if(no == null) {
			return -1;
		}
		return no.getAltura();
	}
	
	//Verifica quem é maior
	private int Maior(int a, int b) {
		return (a > b) ? a : b;
	}
	
	//Função que obtem o fator de balanceamento
	private int ObterFatorBalanceamento(Node<T> no) {
		if(no == null) {
			return 0;
		}
		return (this.Altura(no.getEsquerda()) - this.Altura(no.getDireita()));
	}

	//Função que verifica o balanceamento e faz as rotações
	public Node<T> VerificarBalanceamento(Node<T> noAtual) {
		
		//Fator balanceamento = alturaDireita - alturaEsquerda;
		//Fator balanceamento deve estar entra -1 >= x <= 1;
		//Se fator de balancemaneto do node pai for +2 esta desbalanceado para a direita, logo será feito balancemento pra esquerda;
		//Se fator de balancemaneto do node pai for -2 esta desbalanceado para a esquerda, logo será feito balancemento pra direita;
		//Se fator de balancemento do node pai for +2 e do filho -1, sera feito rotaçao dupla direita esquerda;
		//Se fator de balancemento do node pai for -2 e do filho +1, sera feito rotaçao dupla esquerda direita;
		
		 int FatorBalanceamento = this.ObterFatorBalanceamento(noAtual);
		 int FatorEsquerda = this.ObterFatorBalanceamento(noAtual.getEsquerda());
		 int FatorDireita = this.ObterFatorBalanceamento(noAtual.getDireita());
		    
		 if (FatorBalanceamento > 1 && FatorEsquerda >= 0) {
			 return RSD(noAtual); // Rotação Simples Direita
		 } else if (FatorBalanceamento > 1 && FatorEsquerda < 0) {
			 noAtual.setEsquerda(RSE(noAtual.getEsquerda())); // Rotação Simples Esquerda no filho esquerdo
		     return RSD(noAtual); // Rotação Simples Direita no nó atual
		 } else if (FatorBalanceamento < -1 && FatorDireita <= 0) {
		        	return RSE(noAtual); // Rotação Simples Esquerda
		          } else if (FatorBalanceamento < -1 && FatorDireita > 0) {
		        	  noAtual.setDireita(RSD(noAtual.getDireita())); // Rotação Simples Direita no filho direito
		              return RSE(noAtual); // Rotação Simples Esquerda no nó atual
		          } else if (FatorBalanceamento > 1 && FatorEsquerda < 0) {
		        	  noAtual.setEsquerda(RSE(noAtual.getEsquerda())); // Rotação Simples Esquerda no filho esquerdo
		        	  return RSD(noAtual); // Rotação Simples Direita no nó atual
		          } else if (FatorBalanceamento < -1 && FatorDireita > 0) {
		        	  noAtual.setDireita(RSD(noAtual.getDireita())); // Rotação Simples Direita no filho direito
		        	  return RSE(noAtual); // Rotação Simples Esquerda no nó atual
		          }
		    return noAtual;
	}
	 
	 //Funçao para inserir na arvore
	public void Add(T elemento) {
		if(elemento != null) {
			Veiculo veiculo = (Veiculo) elemento;
			this.root = this.Add(root, elemento, veiculo.getChave());
			//root.toString();
			Arquivo.escreverADD(veiculo);
		}else {
			System.out.println("ERROR.");
		}
	}

	public Node<T> Add(Node<T> noAtual, T elemento, long chave) {
	    if (noAtual == null) {
	    	//Veiculo veiculo = (Veiculo) elemento;
	    	//System.out.println(veiculo.getName() + " Adicionado.");
	        return new Node<T>(elemento, chave);
	    }

	    if (chave < noAtual.getChave()) {
	        noAtual.setEsquerda(Add(noAtual.getEsquerda(), elemento, chave));
	    } else if (chave > noAtual.getChave()) {
	        noAtual.setDireita(Add(noAtual.getDireita(), elemento, chave));
	    } else {
	        // Chave já existe, não faz nada
	        return noAtual;
	    }

	    // Atualizar altura
	    noAtual.setAltura(1 + Maior(Altura(noAtual.getEsquerda()), Altura(noAtual.getDireita())));
	    Arquivo.escreverAltura(noAtual);

	    // Verificar e realizar balanceamento, se necessário
	    
		 int FatorBalanceamento = this.ObterFatorBalanceamento(noAtual);
		 int FatorEsquerda = this.ObterFatorBalanceamento(noAtual.getEsquerda());
		 int FatorDireita = this.ObterFatorBalanceamento(noAtual.getDireita());
		    
		 if (FatorBalanceamento > 1 && FatorEsquerda >= 0) {
			 return RSD(noAtual); // Rotação Simples Direita
		 } else if (FatorBalanceamento > 1 && FatorEsquerda < 0) {
			 noAtual.setEsquerda(RSE(noAtual.getEsquerda())); // Rotação Simples Esquerda no filho esquerdo
		     return RSD(noAtual); // Rotação Simples Direita no nó atual
		 } else if (FatorBalanceamento < -1 && FatorDireita <= 0) {
		        	return RSE(noAtual); // Rotação Simples Esquerda
		          } else if (FatorBalanceamento < -1 && FatorDireita > 0) {
		        	  noAtual.setDireita(RSD(noAtual.getDireita())); // Rotação Simples Direita no filho direito
		              return RSE(noAtual); // Rotação Simples Esquerda no nó atual
		          } else if (FatorBalanceamento > 1 && FatorEsquerda < 0) {
		        	  noAtual.setEsquerda(RSE(noAtual.getEsquerda())); // Rotação Simples Esquerda no filho esquerdo
		        	  return RSD(noAtual); // Rotação Simples Direita no nó atual
		          } else if (FatorBalanceamento < -1 && FatorDireita > 0) {
		        	  noAtual.setDireita(RSD(noAtual.getDireita())); // Rotação Simples Direita no filho direito
		        	  return RSE(noAtual); // Rotação Simples Esquerda no nó atual
		          }
		    return noAtual;
	    //return VerificarBalanceamento(noAtual);
	}

	
	public void Remover(T elemento) {
	    Veiculo veiculo = (Veiculo) elemento;
	    this.root = Remover(root, elemento, veiculo.getChave());
	    Arquivo.escreverREMOVE(veiculo);
	}

	private Node<T> Remover(Node<T> noAtual, T elemento, long chave) {
		//Se noAtual for nulo retorna nulo
	    if (noAtual == null) {
	        return null;
	    }

	    if (chave < noAtual.getChave()) { //Se chave for menor, vai para esquerda
	        noAtual.setEsquerda(Remover(noAtual.getEsquerda(), elemento, chave));
	    } else if (chave > noAtual.getChave()) { //Se for maior, vai para a direita
	        noAtual.setDireita(Remover(noAtual.getDireita(), elemento, chave));
	    } else {
	        // Encontrou o nó a ser removido

	        if (noAtual.getEsquerda() == null || noAtual.getDireita() == null) {
	            Node<T> novoNo = (noAtual.getEsquerda() != null) ? noAtual.getEsquerda() : noAtual.getDireita();

	            if (novoNo == null) {
	                noAtual = null;
	            } else {
	                noAtual = novoNo;
	            }
	        } else {
	            // Nó possui dois filhos, encontre o sucessor in-order
	            Node<T> sucessor = EncontrarSucessor(noAtual.getDireita());
	            noAtual.setValor(sucessor.getValor());
	            noAtual.setChave(sucessor.getChave());
	            noAtual.setDireita(Remover(noAtual.getDireita(), sucessor.getValor(), sucessor.getChave()));
	        }
	    }

	    if (noAtual != null) {
	        // Atualizar altura e verificar balanceamento
	        noAtual.setAltura(1 + Maior(Altura(noAtual.getEsquerda()), Altura(noAtual.getDireita())));
	        Arquivo.escreverAltura(noAtual);
	        return VerificarBalanceamento(noAtual);
	    }

	    return noAtual;
	}


	private Node<T> EncontrarSucessor(Node<T> node) {
	    Node<T> current = node;
	    while (current.getEsquerda() != null) {
	        current = current.getEsquerda();
	    }
	    return current;
	}

	
	public T BuscarRenavam(long chave) {
	    Node<T> value = BuscarChave(this.root, chave); // Aqui corrigi o nome do método chamado
	    return value.getValor();
	}

	public Node<T> BuscarChave(Node<T> noAtual, long chave) { // Aqui também corrigi o nome do método
	    if (noAtual == null) {
	        return null;
	    } 
	    if(noAtual.getChave() > chave) {
	    	 return BuscarChave(noAtual.getEsquerda(), chave);
	    }
	    if(noAtual.getChave() < chave) {
	    	 return BuscarChave(noAtual.getDireita(), chave);
	    }
		return noAtual;
	}
	// Função para fazer rotação simples para direita
	public Node<T> RSD(Node<T> node) {
	    Node<T> novo = node.getEsquerda();
	    node.setEsquerda(novo.getDireita()); // Passo 1: Atualize a referência esquerda do nó original
	    novo.setDireita(node); // Passo 2: Configure o nó original como filho direito do novo nó

	    // Atualize alturas
	    node.setAltura(1 + Maior(Altura(node.getEsquerda()), Altura(node.getDireita())));
	    novo.setAltura(1 + Maior(Altura(novo.getEsquerda()), Altura(novo.getDireita())));
	    
	    
	    Arquivo.escreverROTATIO(node, novo, "DIREITA");

	    return novo; // Retorne o novo nó como raiz da subárvore
	}

	// Função para fazer rotação simples para esquerdaA
	public Node<T> RSE(Node<T> node) {
	    Node<T> novo = node.getDireita();
	    node.setDireita(novo.getEsquerda()); // Passo 1: Atualize a referência direita do nó original
	    novo.setEsquerda(node); // Passo 2: Configure o nó original como filho esquerdo do novo nó

	    // Atualize alturas
	    node.setAltura(1 + Maior(Altura(node.getEsquerda()), Altura(node.getDireita())));
	    novo.setAltura(1 + Maior(Altura(novo.getEsquerda()), Altura(novo.getDireita())));
	    
	    Arquivo.escreverROTATIO(node, novo, "ESQUERDA");

	    return novo; // Retorne o novo nó como raiz da subárvore
	}

/////////////////////////////////////////////////////////////////////
		//Getters e Setters
	
		 public void setRaiz(Node<T> no) {
			  this.root = no;
		  }
		  
		  public Node<T> getRaiz(){return this.root;}
}


class Node<T>{
	private T valor;
	private Node<T> direita, esquerda;
	private int  altura;
	private long chave;
	
	public Node(){
		this.setChave(0);
		this.setAltura(0);
		this.setValor(null);
		this.setDireita(null);
		this.setEsquerda(null);
	}
	
	public Node(T value, long chave){
		this.setChave(chave);
		this.setAltura(0);
		this.setValor(value);
		this.setDireita(null);
		this.setEsquerda(null);
	}

	
	public T getValor() {
		return valor;
	}

	public void setValor(T valor) {
		this.valor = valor;
	}


	public Node<T> getDireita() {
			return direita;
	}


	public void setDireita(Node<T> direita) {
		this.direita = direita;
	}


	public Node<T> getEsquerda() {
		return esquerda;
		
	}


	public void setEsquerda(Node<T> esquerda) {
		this.esquerda = esquerda;
	}


	public long getChave() {
		return chave;
	}


	public void setChave(long chave) {
		this.chave = chave;
	}


	public int getAltura() {
		return altura;
	}

	public void setAltura(int altura) {
		this.altura = altura;
	}
	
	public String toString() {
		Veiculo veiculo = (Veiculo) this.getValor();
		//String resultado ="";
		
		//if(this.getEsquerda() != null ) {
			//resultado += ("Esquerda = " + getEsquerda().getChave() + "\n");
		//}else {
			//resultado += "Esquerda = null \n";
		//}
		
		//if(this.getDireita() != null ) {
			//resultado += ("Direita = " + getDireita().getChave() + "\n");
		//}else {
		//	resultado += "Direita = null \n";
		//}
		//resultado + 
		return veiculo.toString();
	}
	

	
}