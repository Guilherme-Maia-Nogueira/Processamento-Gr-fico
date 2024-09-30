using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimuladorPipeline
{
    internal class Decodificacao : Load

    {

        protected String Opcode;
        protected int Op1;
        protected int Op2;
        protected int Op3;
        protected int Temp1;
        protected int Temp2;
        protected int Temp3;
        protected bool Valida;
        protected int ValSal;

        public void Decodificar(string Opcode, int Op1, int Op2, int Op3, bool Valida = true, int ValSal = 0) 
        {

            this.Opcode = Opcode;
            this.Op1 = Op1;
            this.Op2 = Op2;
            this.Op3 = Op3;
            this.Temp1 = Get(1);
            this.Temp2 = Get(2);
            this.Temp3 = Get(3);
            this.Valida = Valida;
            this.ValSal = ValSal;

            Console.WriteLine("Op1: " + Op1);
            Console.WriteLine("Op2: " + Op2);
            Console.WriteLine("Op3: " + Op3);
            Console.WriteLine("Temp1: " + Temp1);
            Console.WriteLine("Temp2: " + Temp2);
            Console.WriteLine("Temp3: " + Temp3);
            Console.WriteLine("Valida: " + Valida);
            if (ValSal == 0)
            {
                Console.WriteLine("ValSal = 0");
            }

            Console.WriteLine("Pressione qualquer tecla para continuar...");

            while (!Console.KeyAvailable)
            {
                // Aguarda até que uma tecla seja pressionada
            }



        }




    }
}
