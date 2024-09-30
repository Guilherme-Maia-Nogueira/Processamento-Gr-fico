using System;

class Program
{
    static int totalOperations = 0; // Contador para o número total de operações

    static void Main()
    {
        // Solicita a entrada do usuário
        Console.WriteLine("Digite os elementos do array separados por espaço:");
        string input = Console.ReadLine();

        // Converte a entrada em um array de inteiros
        int[] array = Array.ConvertAll(input.Split(' '), int.Parse);

        // Executa o quicksort
        Quicksort(array, 0, array.Length - 1);

        // Exibe o array ordenado
        Console.WriteLine("Array ordenado:");
        Console.WriteLine(string.Join(" ", array));

        // Exibe o número total de operações
        Console.WriteLine($"Número total de operações: {totalOperations}");
    }

    static void Quicksort(int[] array, int low, int high)
    {
        if (low < high)
        {
            // Particiona o array e obtém o índice do pivô
            int pivotIndex = Partition(array, low, high);

            // Ordena recursivamente os sub-arrays à esquerda e à direita do pivô
            Quicksort(array, low, pivotIndex - 1);
            Quicksort(array, pivotIndex + 1, high);
        }
    }

    static int Partition(int[] array, int low, int high)
    {
        totalOperations += 2; // Escolha do pivô e inicialização de i (2 operações)

        int pivot = array[high]; // 1 operação
        int i = low - 1;         // 1 operação

        for (int j = low; j < high; j++) // (high - low) iterações
        {
            totalOperations += 1; // 1 operação por comparação no if

            if (array[j] <= pivot)
            {
                i++; // 1 operação
                totalOperations += 1; // Contabilizando incremento de i

                Swap(array, i, j); // Troca de elementos
            }
        }

        Swap(array, i + 1, high); // Troca final com o pivô
        totalOperations += 3; // Contabilizando a troca final

        return i + 1; // Retorna o índice do pivô
    }

    static void Swap(int[] array, int i, int j)
    {
        totalOperations += 3; // 3 operações para a troca
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
