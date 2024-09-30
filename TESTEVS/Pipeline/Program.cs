using System;
using System.Collections.Generic;
using System.Threading;

public class Pipeline
{
    private static int[] registradores = new int[32]; // Registradores R0 a R31

    public static void Main()
    {
        Console.WriteLine("Pipeline com 5 estágios");

        // Lista de instruções para processar
        List<string> instrucoes = new List<string>
        {
            "ADD R1, R2, R3",
            "SUB R4, R5, R6",
            "MUL R7, R8, R9",
            "DIV R10, R11, R12"
        };

        // Cria threads para simular os estágios do pipeline
        Thread[] threads = new Thread[5];

        // Thread para buscar a instrução da memória
        threads[0] = new Thread(() =>
        {
            foreach (string instrucao in instrucoes)
            {
                // Simula o estágio de busca da instrução
                Thread.Sleep(100);
                Console.WriteLine("Buscando instrução: " + instrucao);
            }
        });

        // Threads para os estágios de decodificação, execução, acesso à memória e escrita no registrador
        for (int i = 1; i < threads.Length; i++)
        {
            int index = i - 1; // Índice da instrução atual
            threads[i] = new Thread(() =>
            {
                foreach (string instrucao in instrucoes)
                {
                    // Simula os estágios de decodificação, execução, acesso à memória e escrita no registrador
                    Thread.Sleep(100);
                    Console.WriteLine($"Estágio {index}: Executando instrução: " + instrucao);
                }
            });
        }

        // Inicia as threads
        foreach (Thread thread in threads)
        {
            thread.Start();
        }

        // Aguarda as threads terminarem
        foreach (Thread thread in threads)
        {
            thread.Join();
        }

        Console.WriteLine("Execução concluída");
    }
}