//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;
//using System.Threading.Tasks;

//namespace SimuladorPipeline
//{
//    internal class Teste
//    {
//    }
//}

using System;
using System.Collections.Generic;

public class Pipeline
{
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

        // Simulando um pipeline com 5 estágios
        for (int i = 0; i < instrucoes.Count; i++)
        {
            string instrucao = instrucoes[i];
            Console.WriteLine($"Instrução {i + 1}: {instrucao}");

            // Dividindo a instrução em partes
            string[] partesInstrucao = instrucao.Split(' ');

            // Etapa 1: Buscar instrução da memória
            string instrucaoAtual = partesInstrucao[0]; // Exemplo: ADD

            // Etapa 2: Decodificar instrução
            string operacao = partesInstrucao[1]; // Exemplo: R1,
            string operando1 = partesInstrucao[2]; // Exemplo: R2,
            string operando2 = partesInstrucao[3]; // Exemplo: R3

            // Etapa 3: Executar a instrução
            int valor1 = 10; // Valor fictício para R2
            int valor2 = 20; // Valor fictício para R3
            int resultado = 0;

            switch (operacao)
            {
                case "ADD":
                    resultado = valor1 + valor2;
                    break;
                case "SUB":
                    resultado = valor1 - valor2;
                    break;
                case "MUL":
                    resultado = valor1 * valor2;
                    break;
                case "DIV":
                    resultado = valor1 / valor2;
                    break;
                // Mais operações aqui...
                default:
                    Console.WriteLine("Operação não suportada");
                    break;
            }

            // Etapa 4: Acesso à memória
            // Neste exemplo simples, não é necessário

            // Etapa 5: Escrever de volta no registrador
            Console.WriteLine($"Resultado da operação {operacao}: {resultado}");
            Console.WriteLine();
        }
    }
}

