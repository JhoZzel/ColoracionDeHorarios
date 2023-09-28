#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

//============= ESTRUCTURAS PARA GUARDAR LOS DATOS DE ENTRADA =============
struct Curso{
    string nombre;
    int periodos;
};
struct Profe{
    string nombre;
    Curso cursos[10];
};
struct VerticeDelLineal{
    string x; // ETIQUETA : PROFESORES
    string y; // ETIQUETA : CURSOS
    int p; // ETIQUETA : DIFERENCIADOR -- ejemplo (Mass,diferencial,1) y (Mass,diferencial,2)
};

// ==== TIPOS DE DATOS GLOBALES A USAR ========
ifstream fin;
ofstream fout;
string str;
int nVertices=0, nProfes=0, nCursos=0, nCromatico=0;
size_t pos;
VerticeDelLineal vertices[100];
Profe profesor[10];
string cursos[25], horario[100][100];
int matriz[100][100];

//================ FUNCIONES ================ 
void anadirCursos(string nuevoCurso);
void asignarVertices(VerticeDelLineal v[], int tam);
void inicializarHorario();
int obtenerPosicionCurso(string str);
int obtenerPosicionProfe(string str);
void imprimirMatrizAdyacenciaDelLinealTXT(int n);
void imprimirResultados();

int main() {
    // A PARTIR DEL ARCHIVO .TXT, GUARDARAMOS LOS NOMBRES DE LOS PROFES CON SUS RESPECTIVOS CURSOS Y PERIODOS
    fin.open("datosEntrada.txt");

    int i=0;
    while (!fin.eof()){
        getline(fin, str);
        
        pos = str.find(':');
        profesor[i].nombre = str.substr(0, pos);
        str.erase(0,pos+1);
        
        int j = 0;
        while (str.find(',')!=-1){
            pos = str.find('-');
            profesor[i].cursos[j].nombre = str.substr(0, pos);
            profesor[i].cursos[j].periodos = stoi(str.substr(pos+1, 1));
            str.erase(0,pos+3);

            anadirCursos(profesor[i].cursos[j].nombre);
            nVertices += profesor[i].cursos[j].periodos;
            j++;
        }

        pos = str.find('-');
        profesor[i].cursos[j].nombre = str.substr(0,pos);
        profesor[i].cursos[j].periodos = stoi(str.substr(pos+1,1 ));
        
        anadirCursos(profesor[i].cursos[j].nombre);
        nVertices += profesor[i].cursos[j].periodos;
        i++;
    }   nProfes=i;
    
    fin.close();

    // HALLANDO LOS VERTICES DEL GRAFO LINEAL DE G
    asignarVertices(vertices, nVertices);

    // CREAMOS EL HORARIO 
        inicializarHorario(); 
        fin.open("coloring.txt");
        while (!fin.eof()){
            getline(fin,str);
            int pos = str.find(' ');

            int i_vert = stoi(str.substr(0,pos+1)) - 1;
            int j = stoi(str.substr(pos+1,1)) - 1;
            if (j>nCromatico) nCromatico = j+1;
            int i = obtenerPosicionProfe(vertices[i_vert].x);
            horario[i][j] = vertices[i_vert].y;
        }

    imprimirResultados(); 
    return 0;    
}

void anadirCursos(string nuevoCurso){
    bool flag=true;
    for (int i=0; i<nCursos; i++){
        if (cursos[i].compare(nuevoCurso) == 0) flag=false;
    }
    if (flag){
        cursos[nCursos] = nuevoCurso;
        nCursos++;
    }
}

void asignarVertices(VerticeDelLineal v[], int tam) {
    int l = 0;
    for (int i = 0; i < nProfes; i++) {
        for (int j = 0; j < nCursos; j++) {
            int nPeriodos = profesor[i].cursos[j].periodos;
            int k = 1;
            while (nPeriodos != 0) {
                v[l].x = profesor[i].nombre;
                v[l].y = profesor[i].cursos[j].nombre;
                v[l].p = k;
                k++;
                l++;
                nPeriodos--;
            }
        }
    }
}

void inicializarHorario(){
    for (int i=0; i<nCursos; i++){
        for (int j=0; j<20; j++){
            horario[i][j]="---";
        }
    }
}

int obtenerPosicionCurso(string str){
    int r;
    for (int i=0; i<nCursos; i++){
        if (cursos[i].compare(str)){
            r = i;
            break;
        } 
    }   
    return r;
}

int obtenerPosicionProfe(string str){
    int r;
    for (int i=0; i<nProfes; i++){
        if (profesor[i].nombre.compare(str) == 0){
            r=i;
            break;
        }
    }
    return r;
}

void imprimirMatrizAdyacenciaDelLinealTXT(int n){
  fout << n << endl;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;++j){
      fout << matriz[i][j] <<'\t';
    }
    fout <<'\n';
  }
}

void imprimirResultados(){
    cout<<"Profesores: \n";
    for (int i=0; i<nProfes; i++){
        cout<<"\t"<<profesor[i].nombre<<endl;
    }   cout<<endl;

    cout<<"Cursos: \n";
    for (int i=0; i<nCursos; i++){
        cout<<"\t"<<cursos[i]<<endl;
    }   cout<<endl;

    cout<<"Vertices del Lineal: \n";
    for (int i=0; i<nVertices; i++){
        cout<<"\t"<<i+1<<".  "<<vertices[i].x<<setw(25)<<vertices[i].y<<" - "<<vertices[i].p<<endl;
    }

    cout<<"\n\n HORARIO \n\t\t\t";
    for (int i=1; i<= nCromatico; i++ ){
        printf("%*d",25,i);
    }   cout<<endl;
    for (int i=0; i<nProfes; i++){
        printf("%*s",30,profesor[i].nombre.c_str());
        for (int j=0; j<nCromatico; j++){
            printf("%*s",25,horario[i][j].c_str());
        }   cout<<endl;
    }
}