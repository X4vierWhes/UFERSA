public class Fila<T> {
    private int size;
    private T[] vet;
    private int first;
    private int last;

    public Fila(int size) {
        vet = (T[]) new Object[size];
        size = 0;
        first = 0;
        last = -1;
    }

    public void pull(T element) {
        if (size == vet.length) {
            throw new IllegalArgumentException("Fila cheia");
        }

        last = (last + 1) % vet.length;
        vet[last] = element;
        size++;
    }

    public T peek() {
        if (size == 0) {
            throw new IllegalArgumentException("Fila vazia");
        }
        T element = vet[first];
        vet[first] = null;
        first = (first + 1) % vet.length;
        size--;
        return element;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public boolean isFull() {
        return size == vet.length;
    }

    public void espiar() {
        if (size == 0) {
            System.out.println("Fila vazia");
        } else {
            System.out.print(vet[first]);
        }
    }

    public String toString() {
        String np = "";

        if (size == 0) {
            return "Fila vazia";
        }

        int indice = first;

        for (int i = 0; i < size; i++) {
            np += vet[indice] + " ";
            indice = (indice + 1) % vet.length;
        }
        return np;
    }

    public static void main(String[] args) {
        Fila<Integer> queue = new Fila<Integer>(5);

        queue.espiar();
        queue.pull(1);
        queue.pull(2);
        queue.pull(3);
        queue.pull(4);
        queue.pull(5);
        System.out.println(queue.toString());
        queue.peek();
        queue.peek();
        queue.pull(6);
        queue.pull(7);
        System.out.println(queue.toString());

    }
}