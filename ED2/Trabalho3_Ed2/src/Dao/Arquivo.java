package Dao;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import Entity.Veiculo;

public class Arquivo {
	
	public static void logFc(double loadFactor) {
	    try {
	        FileWriter writer = new FileWriter("src/Resources/log_FC.txt", true); // Abre o arquivo em modo de apêndice
	        writer.write("Fator de Carga Atual: " + loadFactor + "\n");
	        writer.close();
	    } catch (IOException e) {
	        e.printStackTrace();
	    }
	}

	
	@SuppressWarnings("unused")
	public static void logAdd(Veiculo veiculo) {
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
	public static void logREMOVE(Veiculo veiculo) {
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
    
    public static void clear() {
    	// Especifique o caminho do arquivo que você deseja limpar
        String logADD ="src/Resources/log_ADD.txt";

        // Crie um objeto File com base no caminho do arquivo
        File arquivo = new File(logADD);

        try {
            // Verifique se o arquivo existe
            if (arquivo.exists()) {
                // Delete o arquivo existente
                if (arquivo.delete()) {
                    System.out.println("Arquivo antigo excluído com sucesso.");
                } else {
                    System.out.println("Falha ao excluir o arquivo antigo.");
                }
            }

            // Agora, você pode criar um novo arquivo, se necessário
            if (arquivo.createNewFile()) {
                System.out.println("Arquivo limpo e recriado com sucesso.");
            } else {
                System.out.println("Falha ao criar o novo arquivo.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
     // Especifique o caminho do arquivo que você deseja limpar
        String logRemover ="src/Resources/log_REMOVE.txt";

        // Crie um objeto File com base no caminho do arquivo
        File arquivo2 = new File(logRemover);

        try {
            // Verifique se o arquivo existe
            if (arquivo2.exists()) {
                // Delete o arquivo existente
                if (arquivo2.delete()) {
                    System.out.println("Arquivo antigo excluído com sucesso.");
                } else {
                    System.out.println("Falha ao excluir o arquivo antigo.");
                }
            }

            // Agora, você pode criar um novo arquivo, se necessário
            if (arquivo2.createNewFile()) {
                System.out.println("Arquivo limpo e recriado com sucesso.");
            } else {
                System.out.println("Falha ao criar o novo arquivo.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        
        // Especifique o caminho do arquivo que você deseja limpar
        String logFC ="src/Resources/log_FC.txt";

        // Crie um objeto File com base no caminho do arquivo
        File arquivo3 = new File(logFC);

        try {
            // Verifique se o arquivo existe
            if (arquivo3.exists()) {
                // Delete o arquivo existente
                if (arquivo3.delete()) {
                    System.out.println("Arquivo antigo excluído com sucesso.");
                } else {
                    System.out.println("Falha ao excluir o arquivo antigo.");
                }
            }

            // Agora, você pode criar um novo arquivo, se necessário
            if (arquivo3.createNewFile()) {
                System.out.println("Arquivo limpo e recriado com sucesso.");
            } else {
                System.out.println("Falha ao criar o novo arquivo.");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    } 
}

    
 
