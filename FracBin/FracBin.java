package FracBin;

public class FracBin {
    public FracBin() {
    }

    public FracBin(double num) {
        convert(num);
    }

    public static String convert(double num) {
        String bin = "";
        bin += parteInteira((int) num);
        bin += parteFracionaria(num);

        return bin;
    }

    public static String parteInteira(int num) {
        String bin = "";
        double mod = 0;

        // convertendo parte inteira
        if (num == 0) {
            return "0";
        } else {
            while (num > 0) {
                mod = num % 2;
                num = num / 2;
                if (mod == 0) {
                    bin += "0";
                } else {
                    bin += "1";
                }

            }
        }
        //
        return inverter(bin);
    }

    public static String parteFracionaria(double num) {
        String bin = "";
        System.out.println("Chegou: " + num);
        double fracion = transformar(num);
        double primeiroNumero = fracion;
        System.out.println("Primeiro numero: " + primeiroNumero);

        int i = 0;
        while (i < 10) {

            fracion = fracion * 2;
            System.out.println(fracion);
            if (fracion >= 1.0) {
                bin += "1";
            } else {
                bin += "0";
            }
            fracion = transformar(fracion);
            System.out.println(fracion);

            if (fracion == 1.0 || fracion == primeiroNumero || fracion == 0.0) {
                break;
            }
            i++;
        }

        return "," + bin;
    }

    public static double transformar(double num) {
        int resto = (int) Math.round((num - (int) num));
        String fracionario = "0.";

        if (resto >= 100) {
            resto = (int) Math.round((num - (int) num) * 1000);
            fracionario += resto;
        } else {
            resto = (int) Math.round((num - (int) num) * 100);
            fracionario += resto;
        }
        // System.out.println("Fracionario: " + fracionario);
        double fracion = Double.parseDouble(fracionario);

        return fracion;
    }

    public static String inverter(String bin) {
        String invert = new StringBuilder(bin).reverse().toString();
        return invert;
    }
}