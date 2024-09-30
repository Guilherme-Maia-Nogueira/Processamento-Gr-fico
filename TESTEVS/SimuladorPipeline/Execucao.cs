using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SimuladorPipeline
{
    internal class Execucao : Load
    {
        public Execucao(string Opcode, int Op1, int Op2, int Op3, int Temp1, int Temp2, int Temp3, bool Valida = true, int ValSal = 0) : base(Opcode, Op1, Op2, Op3, Temp1, Temp2, Temp3, Valida, ValSal)
        {
        }
    }
}
