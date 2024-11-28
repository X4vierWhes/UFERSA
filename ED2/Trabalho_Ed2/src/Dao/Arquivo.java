package Dao;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;

import Entity.Veiculo;

public class Arquivo {
	
	@SuppressWarnings("unused")
	public static void escreverADD(Veiculo veiculo) {
        String nomeArquivo = "src/Resources/log_ADD.txt";
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(nomeArquivo, true));
            writer.write("-----------------------------------------------------------");
            writer.newLine();
            writer.write("Veículo ADICIONADO:");
            writer.newLine();
            writer.write("Placa: " + veiculo.getPlaca());
            writer.newLine();
            writer.write("Renavam: " + veiculo.getRenavam());
            writer.newLine();
            writer.write("Modelo: " + veiculo.getModelo());
            writer.newLine();
            writer.write("Ano: " + veiculo.getFabricacao());
            writer.newLine();
            writer.write("Nome: " + veiculo.getName());
            writer.newLine();
            writer.write("CPF: " + veiculo.getCpf());
            writer.newLine();
            writer.write("-----------------------------------------------------------");
            writer.newLine();
            writer.close();
        } catch (IOException e) {
            System.err.println("Erro ao escrever no arquivo: " + e.getMessage());
        }
    }

    // Função para escrever informações de remoção no arquivo
    @SuppressWarnings("unused")
	public static void escreverREMOVE(Veiculo veiculo) {
    	 String nomeArquivo = "src/Resources/log_REMOVE.txt";
         try {
             BufferedWriter writer = new BufferedWriter(new FileWriter(nomeArquivo, true));
             writer.write("-----------------------------------------------------------");
             writer.newLine();
             writer.write("Veículo REMOVIDO:");
             writer.newLine();
             writer.write("Placa: " + veiculo.getPlaca());
             writer.newLine();
             writer.write("Renavam: " + veiculo.getRenavam());
             writer.newLine();
             writer.write("Modelo: " + veiculo.getModelo());
             writer.newLine();
             writer.write("Ano: " + veiculo.getFabricacao());
             writer.newLine();
             writer.write("Nome: " + veiculo.getName());
             writer.newLine();
             writer.write("CPF: " + veiculo.getCpf());
             writer.newLine();
             writer.write("-----------------------------------------------------------");
             writer.newLine();
             writer.close();
         } catch (IOException e) {
             System.err.println("Erro ao escrever no arquivo: " + e.getMessage());
         }
    }

    
 // Função para escrever informações de atualização de altura no arquivo
    @SuppressWarnings("unused")
	public static <T> void escreverAltura(Node<T> noAtual) {
        String nomeArquivo = "src/Resources/log_HEIGHT.txt";
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(nomeArquivo, true));
            writer.write("-----------------------------------------------------------");
            writer.newLine();
            writer.write("Atualização de altura:");
            writer.newLine();
            writer.write("Nó - Chave: " + noAtual.getChave());
            writer.newLine();
            writer.write("Nova altura: " + noAtual.getAltura());
            writer.write("-----------------------------------------------------------");
            writer.newLine();
            writer.close();
        } catch (IOException e) {
            System.err.println("Erro ao escrever no arquivo: " + e.getMessage());
        }
    }
    
    // Função para escrever informações de rotação no arquivo
    @SuppressWarnings("unused")
	public static <T> void escreverROTATIO(Node<T> noAntigo, Node<T> noNovo, String direcao) {
    	if (noAntigo != null && noNovo != null) {
	    	String nomeArquivo = "src/Resources/log_ROTATION.txt";
	    	Veiculo antigo = (Veiculo) noAntigo.getValor();
	    	Veiculo novo = (Veiculo) noNovo.getValor();
	        try {
	            BufferedWriter writer = new BufferedWriter(new FileWriter(nomeArquivo, true));
	            writer.write("-----------------------------------------------------------");
	            writer.newLine();
	            writer.write("Rotação realizada: " + direcao);
	            writer.newLine();
	            writer.write("Nó antigo - Chave: " + noAntigo.getChave());
	            writer.newLine();
	            writer.write("Nó antigo - nome: " + antigo.getName());
	            writer.newLine();
	            if(noAntigo.getDireita() != null) {
	            writer.write("Nó antigo - Chave - DIREITA: " + noAntigo.getDireita().getChave());
	            writer.newLine();
	            }else {
	            	writer.write("Nó antigo - Chave - DIREITA: NULL");
		            writer.newLine();
	            }
	            
	            if(noAntigo.getEsquerda() != null) {
	            writer.write("Nó antigo - Chave - ESQUERDA: " + noAntigo.getEsquerda().getChave());
	            writer.newLine();
	            }else {
	            	writer.write("Nó antigo - Chave - ESQUERDA: NULL");
		            writer.newLine();
	            }
	            writer.write("Nó novo - Chave: " + noNovo.getChave());
	            writer.newLine();
	            writer.write("Nó novo - nome: " + antigo.getName());
	            writer.newLine();
	            if(noNovo.getDireita() != null) {
	            writer.write("Nó novo - Chave - DIREITA: " + noNovo.getDireita().getChave());
	            writer.newLine();
	            }else {
	            	writer.write("Nó novo - Chave - DIREITA: NULL");
		            writer.newLine();
	            }
	            if(noNovo.getEsquerda() != null) {
	            writer.write("Nó novo - Chave - ESQUERDA: " + noNovo.getEsquerda().getChave());
	            writer.newLine();
	            }else {
	            	writer.write("Nó novo - Chave - ESQUERDA: NULL" );
		            writer.newLine();
	            }
	            writer.write("-----------------------------------------------------------");
	            writer.newLine();
	            writer.close();
	        } catch (IOException e) {
	            System.err.println("Erro ao escrever no arquivo: " + e.getMessage());
	        }
    	}
    }

}
