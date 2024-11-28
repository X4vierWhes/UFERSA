public class Lista<T> {
    private int tam;
    private T[] vet;

    public Lista() {
        this.tam = 0;
        this.vet = (T[]) new Object[10];
    }

    public int getSpace() {
        return vet.length;
    }

    public int getTam() {
        return tam;
    }

    public void add(T element) {
        if (tam == vet.length) {
            resize();
        }

        vet[tam] = element;
        tam++;
    }

    public void remove(int indice) {
        if (indice < 0 || indice >= vet.length) {
            throw new ArrayIndexOutOfBoundsException("Indices out of bounds");
        }

        for (int i = indice; indice < vet.length; indice++) {
            vet[i] = vet[i + 1];
        }

        tam--;
    }

    public T get(int indice) {
        if (indice < 0 || indice >= vet.length) {
            throw new ArrayIndexOutOfBoundsException("Indices out of bounds");
        }

        return vet[indice];
    }

    private void resize() {
        int newTam = vet.length * 2;
        T[] newVet = (T[]) new Object[newTam];

        for (int i = 0; i < vet.length; i++) {
            newVet[i] = vet[i];
        }

        vet = newVet;

    }

    public String toString() {
        String np = "";
        if (tam == 0) {
            return "Lista Vazia";
        }

        for (int i = 0; i < tam; i++) {
            np += vet[i] + " ";
        }

        return np;
    }

    public static void main(String[] args) {
        Lista<Integer> vet = new Lista<Integer>();
        for (int i = 0; i < 11; i++) {
            vet.add(i + 1);
        }

        System.out.println(vet.toString());
        System.out.println(vet.getTam());
        System.out.println(vet.getSpace());
    }
}
