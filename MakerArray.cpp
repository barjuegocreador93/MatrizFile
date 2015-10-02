#include "MatrizFile.h"



int main()
{
    MatrizFile a;
    a.readFile("Prueva/esquma.txt","Prueva/Nota_final.txt");

    a.print();

    for(int i=0;i<a.giveNfilas();i++)
    {
        double cortes[3],def;
        for(int j=1;j<=3;j++)
        {
            cortes[j-1]=atof(strTochar(a.give(i,j)));
        }
        def=(cortes[0]*0.5)+(cortes[1]*0.2)+(cortes[2]*0.3);
        a.getDataonFila(i,to_string(def));
    }
    a.save("Prueva/Definitivas.txt","hoja de calculo");

    a.getEsqumaColumn("double","definitiva",1);
    a.saveEsquema("Prueva/defEsquema.txt");

    a.save("Prueva/Definitivas.php","ArrayPHP");
    return 0;
}


