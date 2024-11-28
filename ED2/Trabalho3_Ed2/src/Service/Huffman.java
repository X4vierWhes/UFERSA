package Service;

import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;

public class Huffman {
    Map<Character, String> Codificacao = new HashMap<>();
    Map<String, Character> Decodificacao = new HashMap<>();
    
    public String comprimir(String entrada) {
    	HashMap<Character, Integer> freqs = new HashMap<>();
    	
    	for(char a : entrada.toCharArray()) { //Extraindo as frequencias e colocando num hash map
    		freqs.put(a, freqs.getOrDefault(a, 0) + 1);
    	}
    	
    	PriorityQueue<HuffmanNode> priority = new PriorityQueue<>();
    	
    	for(char key : freqs.keySet()) {
    		priority.add(new HuffmanNode(key, freqs.get(key)));
    	}
    	
    	HuffmanNode root = construir(priority); //Criando arvore de Huffman
    	HashMap<Character, String> codes = new HashMap<>();
    	gerarCodigos(root, "", codes);
    	
    	StringBuilder compress = new StringBuilder();
    	
    	for(char c : entrada.toCharArray()) {
    		compress.append(Codificacao.get(c));
    	}
		return compress.toString();
    	
    }
    
    private void gerarCodigos(HuffmanNode root, String cod, HashMap<Character, String> codes) {
		if(root == null) { //Se for nula, somente retorna
			return;
		}
		
		if (root.data != '\0') { 
			Codificacao.put(root.data, cod);
        }
		
		gerarCodigos(root.getLeft(), cod + "0", codes);
		gerarCodigos(root.getRight(), cod + "1", codes);
	}

	public String descomprimir(String comprimido) {
		
		StringBuilder descompress = new StringBuilder();
		StringBuilder currentCode = new StringBuilder();
		
		for(char bit : comprimido.toCharArray()) {
			currentCode.append(bit);
			
			for(char key : Codificacao.keySet()) {
				if(Codificacao.get(key).equals(currentCode.toString())) {
					descompress.append(key);
					currentCode.setLength(0);
				}
			}
		}
		
		return descompress.toString();
    	
    }
	
	/*public String descomprimir(String comprimido) {
		
		StringBuilder descompress = new StringBuilder();
		StringBuilder currentCode = new StringBuilder();
		
		for(char bit : comprimido.toCharArray()) {
			currentCode.append(bit);
			
			for(char key : Codificacao.keySet()) {
				if(Codificacao.get(key).equals(currentCode.toString())) {
					descompress.append(key);
					currentCode.setLength(0);
				}
			}
		}
		
		return descompress.toString();
    	
    }*/
    
    public HuffmanNode construir(PriorityQueue<HuffmanNode> pq) {
    	while(pq.size() > 1) {
    		HuffmanNode left = pq.poll(); //Primeira menor frenquencia vai para a esquerda
    		HuffmanNode right = pq.poll(); //Segunda menor frequencia vai para a direita
    		
    		HuffmanNode mergedNode = new HuffmanNode('\0', left.frequency + right.frequency);
    		
    		mergedNode.setLeft(left);
    		mergedNode.setRight(right);
    		
    		pq.add(mergedNode);
    	}
		return pq.poll();
    	
    }
    
}

//Classe para representar um nó da árvore de Huffman
class HuffmanNode implements Comparable<HuffmanNode> {
	char data; // Caractere armazenado no nó
	int frequency; // Frequência do caractere
	private HuffmanNode left, right; // Filhos esquerdo e direito

	public HuffmanNode(char data, int frequency) {
		this.data = data;
		this.frequency = frequency;
		setLeft(null);
		setRight(null);
	}
	
	public HuffmanNode(int frequencia, HuffmanNode left, HuffmanNode right) {
		this.frequency = frequencia;
		setLeft(left);
		setRight(right);
	}
	
	public HuffmanNode(char caracter, HuffmanNode left, HuffmanNode right) {
		this.data = caracter;
		setLeft(left);
		setRight(right);
	}

	@Override
	public int compareTo(HuffmanNode other) {
		return this.frequency - other.frequency;
	}

	public HuffmanNode getLeft() {
		return left;
	}

	public void setLeft(HuffmanNode left) {
		this.left = left;
	}

	public HuffmanNode getRight() {
		return right;
	}

	public void setRight(HuffmanNode right) {
		this.right = right;
	}
	
}