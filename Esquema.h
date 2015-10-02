#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<string.h>
#include <string>
#include <sstream>
using namespace std;
//Creado por Camilo Barbosa

template <typename T>
string to_string(const T& value)
{
    std::ostringstream s;
    s << value;
    return s.str();
}



char * strTochar(string a)
{
    char * x=new char[a.length()+1];
    strcpy(x,a.c_str());
    return x;
}

char * cls=strTochar("clear");

template <class t1>
void typeValidador(t1 & numero)
{


    int cont = 0;
    bool continuar;

    do
    {

        continuar = false;
        cin.clear();
        if(cont > 0) cin.ignore(1024, '\n');
        cout << "Introduce un numero: ";
        cin >> numero;
        cont++;
        if(cin.fail() && cin.rdstate())
        {
            cout << "NO ES UN NUMERO" << endl;
            continuar = true;
        }
    }
    while (continuar);

}





class esquema
{
public:
    esquema(string="null");
    ~esquema();
    void readFile(string file);
    void inputUser();
    void save(string file);
    void getColumn(string,string,int);
    string givetype(int);
    string givekey(int);
    int giveikey(string);
    int giveconca(int);
    int givesize();
    esquema & operator=(esquema& a);
private:
    vector<string>types;
    vector<string>keys;
    vector<int>conca;
    bool typeV(string type);
    string givekeyforstr(string key);

};
bool esquema::typeV(string type)
{
    if(type=="string")return 1;
    if(type=="char")return 1;
    if(type=="int")return 1;
    if(type=="double")return 1;
    return 0;
}
esquema::esquema(string file)
{

    readFile(file);

}

esquema::~esquema()
{
    types.clear();
    keys.clear();
    conca.clear();
}
string esquema::givekeyforstr(string key)
{
    for(int i=0;i<keys.size();i++)
    {
        if(key==keys[i])return keys[i];
    }
    return " ";
}
void esquema::readFile(string file)
{
    if(file!="null")
    {
        if(givesize()!=0)
        {
            types.clear();
            keys.clear();
            conca.clear();
        }


        ifstream  Open(strTochar(file),ios::in);
        if(Open.is_open() )
        {
            string lee1="", lee3="";
            int lee2=0;
            while (!Open.eof())
            {

                Open>>lee1;
                Open>>lee3;
                Open>>lee2;

                    getColumn(lee1,lee3,lee2);

            }
            Open.close();
        }
    }
}

void esquema::getColumn(string type, string key, int rep)
{
    int xs=0;
    for(int i=0; i<types.size(); i++)
    {
        if(key==keys[i])
        {
            xs++;
        }
    }
    if(!xs)
    {
        types.push_back(type);
        conca.push_back(rep);
        keys.push_back(key);
    }
}

string esquema::givetype(int i)
{
    if(i>=0&&i<types.size())
        return types[i];
    return " ";
}
string esquema::givekey(int i)
{
    if(i>=0&&i<keys.size())
        return keys[i];
    return " ";
}

int esquema::giveconca(int i)
{
    if(i>=0&&i<conca.size())
        return conca[i];
    return 0;
}

int esquema::givesize()
{
    return types.size();
}
void esquema::inputUser()
{
    char x='a', o='1';
    while('a'==x)
    {
        system(cls);
        cout<<"Creando un esquma de columnas:\n\n";
        cout<<"Escriba 1 para string, 2 char, 3 int, 4 double, 5 Termianr: ";
        cin>>x;
        switch(x)
        {
        case '1':
            types.push_back("string");
            x='a';
            o='1';
            break;
        case '2':
            types.push_back("char");
            x='a';
            o='1';
            break;
        case '3':
            types.push_back("int");
            x='a';
            o='1';
            break;
        case '4':
            types.push_back("double");
            x='a';
            o='1';
            break;
        case '5':
            if(givesize()==0)
            {
                cout<<"No a esqumatizado, entre 1. si tiene un esquema en archivo, 2. para volver a llenar el esquma o  3. Salir: ";
                cin>>x;

                if(x=='1'){
                    string file;
                    cout<<"Entre el nombre del archivo: ";
                    cin>>file;
                    readFile(file);
                    }
                 if(x=='2'){
                    x='a';
                    o='0';
                    }
            }else
            {
                string file;
                cout<<"Desea guardar el esquma expuesto (nombre file / null): ";
                 cin>>file;
                save(file);
            }

            break;
        default:
            x='a';
            o='0';

        }
        if(x=='a'&&o=='1')
        {
            string colum;
            do{

            cout<<"Asignele una nombre a la columna: ";
            cin>>colum;
            }while(colum==givekeyforstr(colum));

            keys.push_back(colum);
            int concas=0;
            cout<<"Concatenar, cuantas veces: ",
                cin>>concas;
            conca.push_back(concas);
        }
    }
}

void esquema::save(string file)
{
    ofstream Close(strTochar(file),ios::out);
    for(int i=0; i<types.size(); i++)
    {
        Close<<types[i]<<" ";
        Close<<keys[i]<<" ";
        Close<<conca[i]<<"\n";
    }
    Close.close();
}

int esquema::giveikey(string key)
{
    for(int i=0; i<types.size(); i++)
    {
        if(key==keys[i])
        {
            return i;
        }
    }
    return -1;
}
esquema &esquema::operator=(esquema &a)
{
    keys=a.keys;
    types=a.types;
    conca=a.conca;
    return *this;
}
