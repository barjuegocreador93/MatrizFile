#include "Esquema.h"

class fila
{
public:
    fila() {}
    ~fila()
    {
        f.clear();
    }
    void get(string data)
    {
        f.push_back(data);
    }
    vector <string> f;
};


class MatrizFile
{
public:
    MatrizFile(string="var_name",string="null",string="null");
    ~MatrizFile();
    void readFile(string,string);
    void inputUser();
    string give(int,int);
    string givekey(int);
    template <class t2>
    void giveforkey(int,string,t2 &var);
    template <class t1>
    void get(int,int,t1 data);
    void getEsquema(esquema &);
    void getfila(fila &);
    void saveEsquema(string);
    void save(string,string lang);
    int giveNfilas();
    int giveNcolumnas();
    void getDataonFila(int,string data);
    void getEsqumaColumn(string,string,int);
    void print();
    esquema giveEsquema();
protected:
    string name;
    esquema sqm;
    vector<fila> matriz;

private:
    string validador(string type,int i);
};
void MatrizFile::print()
{
    for(int i=0;i<giveNfilas();i++)
    {
        for(int j=0;j<giveNcolumnas();j++)
        {
            cout<<givekey(j)<<": "<<give(i,j);
            if(j<giveNcolumnas()-1)
                cout<<" ";
            else
                cout<<"\n";
        }
    }

}
esquema MatrizFile::giveEsquema()
{
    return sqm;
}
void MatrizFile::getEsqumaColumn(string type,string key, int Rep)
{
    sqm.getColumn(type,key,Rep);
}

MatrizFile::MatrizFile(string nombre,string columnas_file, string filas_file)
{
    readFile(columnas_file,filas_file);
    name=nombre;
}
MatrizFile::~MatrizFile()
{
    matriz.clear();
}
void MatrizFile::readFile(string columnas_file,string filas_file)
{
    sqm.readFile(columnas_file);
    if(filas_file!="null")
    {
        if(matriz.size()!=0)
        {
            matriz.clear();
        }
        ifstream  Open(strTochar(filas_file),ios::in);
        string lee;
        if(Open.is_open() )
        {
            while (!Open.eof())
            {
                fila a;
                string lee2;
                for(int i=0; i<sqm.givesize(); i++)
                {
                    Open>>lee;
                    lee2=lee;
                    for(int j=2; j<=sqm.giveconca(i); j++)
                    {
                        Open>>lee;
                        lee2=lee2+" "+lee;
                    }
                    a.f.push_back(lee2);
                }
                matriz.push_back(a);

            }
            Open.close();
            matriz.pop_back();
        }
    }
}


void MatrizFile::inputUser()
{
    if(sqm.givesize()==0)
        sqm.inputUser();
    char x='s';

    while((x=='s'||x=='S')&&sqm.givesize()!=0)
    {
        system(cls);
        cout<<"Crear una nueva fila(s/n): ";
        cin>>x;
        if(x=='s'||x=='S')
        {
            fila a;
            for(int i=0; i<sqm.givesize(); i++)
            {
                system(cls);
                string lee=validador(sqm.givetype(i),i);
                a.get(lee);
            }
            matriz.push_back(a);
        }
        else if(x!='n'&&x!='N')
        {
            x='s';
        }
    }
}

string MatrizFile::validador(string type, int i)
{
    if(type=="string")
    {
        string lee;
        cout<<"entre el dato para la columna "<<sqm.givekey(i)<<" con tipo de dato "<<sqm.givetype(i)<<": ";
        cin>>lee;
        string lee2=lee;
        for(int j=2; j<=sqm.giveconca(i); j++)
        {
            cout<<"Entre la concatenacion de la columna: ";
            cin>>lee;
            lee2=lee2+" "+lee;
        }
        return lee2;
    }
    if(type=="int")
    {
        int lee;
        cout<<"entre el dato para la columna "<<sqm.givekey(i)<<" con tipo de dato "<<sqm.givetype(i)<<": ";
        typeValidador(lee);

        string lee2=to_string(lee);
        for(int j=2; j<=sqm.giveconca(i); j++)
        {
            cout<<"Entre la concatenacion de la columna: ";
            typeValidador(lee);
            lee2=lee2+" "+to_string(lee);
        }
        return lee2;

    }
    if(type=="double")
    {
        double lee;
        cout<<"entre el dato para la columna "<<sqm.givekey(i)<<" con tipo de dato "<<sqm.givetype(i)<<": ";
        typeValidador(lee);

        string lee2=to_string(lee);
        for(int j=2; j<=sqm.giveconca(i); j++)
        {
            cout<<"Entre la concatenacion de la columna: ";
            typeValidador(lee);
            lee2=lee2+" "+to_string(lee);
        }
        return lee2;

    }
    return "null";
}


void MatrizFile::getfila(fila &a)
{
    if(a.f.size()==sqm.givesize())
        for(int i=0; matriz.size(); i++)
        {
            int comp=0;
            for(int j=0;
                    j<matriz[i].f.size();
                    j++)
            {
                if(a.f[j]==matriz[i].f[j])
                    comp++;
            }
            if(comp==matriz[i].f.size()-1)return;
        }
    matriz.push_back(a);
}

string MatrizFile::give(int i,int j)
{
    if(i>=0&&i<matriz.size())
        if(j>=0&&j<matriz[i].f.size())
            return matriz[i].f[j];
    return " ";
}

void MatrizFile::getDataonFila(int i,string data)
{
     if(i>=0&&i<matriz.size())
        matriz[i].get(data);
}

template <class t1>
void MatrizFile::get(int i,int j,t1 data)
{
    if(i>=0&&i<matriz.size())
        if(j>=0&&j<matriz[i].f.size())
            matriz[i].f[j]=to_string(data);

}

void MatrizFile::saveEsquema(string file)
{
    sqm.save(file);
}

void MatrizFile::save(string file, string lang)
{

    if(lang=="ArrayPHP")
    {
        ofstream Close(strTochar(file),ios::out);

        Close<<"<? \n";
        Close<<"$array=[\n";
        for(int i=0; i<matriz.size(); i++)
        {
            Close<<"[";
            for(int j=0; j<matriz[i].f.size(); j++)
            {
                if(sqm.givetype(j)=="string")
                {
                    Close<<"'"<<sqm.givekey(j)<<"' => '"<<matriz[i].f[j]<<"' ";
                }
                else if(sqm.givetype(j)=="char")
                {
                    Close<<" '"<<sqm.givekey(j)<<"' => '"<<matriz[i].f[j]<<"'";
                }
                else
                {
                    Close<<"'"<<sqm.givekey(j)<<"' =>"<<matriz[i].f[j];
                }
                if(matriz[i].f.size()-1!=j)
                {
                    Close<<",";
                }
            }
            Close<<"]";
            if(matriz.size()-1!=i&&matriz.size()!=1)
                Close<<",\n";
        }
        Close<<"];\n";

        Close.close();
    }
    else if(lang=="hoja de calculo")
    {
        ofstream Close(strTochar(file),ios::out);


        for(int i=0; i<matriz.size(); i++)
        {

            for(int j=0; j<matriz[i].f.size(); j++)
            {
                Close<<matriz[i].f[j];
                if(j!=matriz[i].f.size()-1)
                {
                    Close<<" ";
                }
                else
                {
                    Close<<"\n";
                }
            }

        }
        Close.close();
    }

}

template <class t2>
void MatrizFile::giveforkey(int i,string key, t2 & var)
{

    int k=sqm.giveikey(key);
    if(sqm.givetype(k)=="string")
    {
        var=give(i,k);
    }
    else if(sqm.givetype(k)=="double")
    {
        var=atof(strTochar(give(i,k)));
    }
    else if(sqm.givetype(k)=="int")
    {
        var=atoi(strTochar(give(i,k)));
    }
    else if(sqm.givetype(k)=="char")
    {
        char *x=strTochar(give(i,k));
        var=x[0];
    }
}
string MatrizFile::givekey(int i)
{
    return sqm.givekey(i);
}

int MatrizFile::giveNfilas()
{
    return matriz.size();

}

int MatrizFile::giveNcolumnas()
{
    if(give(0,0)!=" ")
    {
        return matriz[0].f.size();

    }
    return 0;
}

void MatrizFile::getEsquema(esquema & a)
{
    sqm=a;
}
