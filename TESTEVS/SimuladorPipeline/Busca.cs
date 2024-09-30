// See https://aka.ms/new-console-template for more information
//Console.WriteLine("Hello, World!");
using SimuladorPipeline;

class Busca : Load
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
    
    //Esse método deve ser adaptado para receber um array de instruções da classe load, onde na classe main iremos percorrer o array com a load
    // e colocar essa linha nos parâmetros do método busca abaixo:
    public void Buscar(String Opcode, int Op1, int Op2, int Op3, int Temp1=0, int Temp2=0, int Temp3=0, bool Valida = true, int ValSal = 0)
    {
        this.Opcode = Opcode;
        this.Op1 = Op1;
        this.Op2 = Op2;
        this.Op3 = Op3;
        this.Temp1 = Temp1;
        this.Temp2 = Temp2;
        this.Temp3 = Temp3;
        this.Valida = Valida;
        this.ValSal = ValSal;

        Console.WriteLine("Op1: "+Op1);
        Console.WriteLine("Op2: "+Op2);
        Console.WriteLine("Op3: "+Op3);
        Console.WriteLine("Temp1: "+Temp1);
        Console.WriteLine("Temp2: " + Temp2);
        Console.WriteLine("Temp3: " + Temp3);
        Console.WriteLine("Valida: "+Valida);
        if(ValSal == 0)
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


