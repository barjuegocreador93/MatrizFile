#include "MatrizFile.h"



int main()
{
    MatrizFile a;
    /*@param 1: Protocolo para leer @param 2*/
    a.readFile("Prueva/esquma.txt","Prueva/Nota_final.txt");
    
    /*Mostrar los datos obtenidos*/
    a.print();
    
    for(int i=0;i<a.giveNfilas();i++)
    {
        /*Tomamos tres notas de cortes para hallar la definitiva*/
        double cortes[3],def;
        for(int j=1;j<=3;j++)
        {
            /*Pasamos de string a char* y luego a float para que sea gusrdado en una variable double*/
            cortes[j-1]=atof(strTochar(a.give(i,j)));
        }
        def=(cortes[0]*0.5)+(cortes[1]*0.2)+(cortes[2]*0.3);
         /*Se arega un campo de dato nuevo a cada fila*/
        a.getDataonFila(i,to_string(def));
    }
    /*@param 1 url de archivo a guardar de fomra @param 2*/
    a.save("Prueva/Definitivas.txt","hoja de calculo");
     /*@param 1: Tipo de dato, @param 2: Nombre de la columna, @param 3 Número Concatenación de la columna*/
    a.getEsqumaColumn("double","definitiva",1);
     /*@param 1: Url de esquema a guardar*/
    a.saveEsquema("Prueva/defEsquema.txt");
    /*@param 1 url de archivo a guardar de fomra @param 2*/
    a.save("Prueva/Definitivas.php","ArrayPHP");
    return 0;
}


