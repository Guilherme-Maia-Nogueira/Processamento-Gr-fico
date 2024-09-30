using SimuladorPipeline;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimuladorPipeline
{
    internal class Load

    {
        protected String Opcode;
        protected String Op1;
        protected int Op2;
        protected int Op3;
        protected int Temp1;
        protected int Temp2;
        protected int Temp3;
        protected bool Valida;
        protected int ValSal; 

        //int[] BancoReg = new int[5];
        int[] BancoReg = new int[5] { 1, 2, 3, 4, 5 };

        String[] BancoInst = new string[] { "0","1","2" };



        public int Get(int index)
        {
            return BancoReg[index];
        }

        public void SetOp1(String valor)
        {
            this.Op1 = valor;
        }


        //Método para carregar arquivo TXT e que deve criar o Ray com dados;
        public void load()
        {
            BancoReg = new int[5]{ 1, 2, 3, 4, 5 };

        }

     }
   
}

//// class Program
//{
//    static void Main()
//    {


//        // Para testar: primeiro cirar um objeto do load, depois ler o TXT e usar somente os métodos do Load




//        Load teste = new Load();// No load iremos carregar as intruções do TXT em um Array e enquanto houverem linhas a serem processadas, irá manter um loop
//        Busca B = new Busca();
//        Decodificacao D = new Decodificacao();



//        B.Buscar("ADD", 1, 2, 3);
//        D.Decodificar("ADD", 1, 2, 3);//Aqui está sendo passado por parâmetro: string Opcode, int Op1, int Op2, int Op3 mas depois será possível preencher os dados direto do array de isntrução que vai estar nessa classe, e as outras classes filhas poderãoa acessar.



//        //aqui iremos iniciar o loop



//        // Obtém e exibe os valores do array
//        for (int i = 0; i < 5; i++)
//        {
//            Console.WriteLine("Valor no índice " + i + ": ");
//        }
//    }


//}
