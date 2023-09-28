#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
//=====ESTRUCTURAS PARA GUARDAR LOS DATOS DE ENTRADA=====
struct Curso{
    string Cnombre;
    int periodos;
};

struct Profe{
    string nombre;
    Curso cursos[100];
};
// ===============VERTICES DEL GRAFO LINEAL ==========
struct VerticeDelLineal{
    string x; // ETIQUETA : PROFESORES
    string y; // ETIQUETA : CURSOS
    int p; // ETIQUETA : DIFERENCIADOR -- ejemplo (Mass,diferencial,1) y (Mass,diferencial,2)
};


// ==== TIPOS DE DATOS GLOBALES A USAR ========
ifstream infile;
ofstream fout;
int nProfes, nCursos=0;
size_t pos;
string str, aux;
VerticeDelLineal vertices[100];
Profe profesor[10];
string cursos[25];
string horario[100][100];
int matriz[100][100];
int nCromatico=0;

//=======================================================
int CantidadVertices(Profe[]);
void AsignandoVertices(VerticeDelLineal[], int);
void inicializarHorario();
void inicializarMatriz(int);
void llenarMatriz(int, VerticeDelLineal[]);
void salidatxt(int);
int obtenerPosicionCurso(string str);
int obtenerPosicionProfe(string str);
void anadirCursos(string nuevoCurso);
void salidaHorariotxt();


int main() {
    /*======== GUARDAREMOS, DEL ARCHIVO.TXT, LOS NOMBRES DE LOS PROFES CON SUS RESPECTIVOS CURSOS Y PERIODOS,
                CON LA AYUDA DE LAS ESTRUCTURAS DEFINIDAS EN LA PARTE SUPERIOR              ==================*/
    infile.open("datosEntrada.txt");
    //getline(infile, str);
    //aux = str[0]; nProfes = stoi(aux);
    //aux = str[2]; nCursos = stoi(aux);
    int i=0;
    while (!infile.eof()){
        getline(infile, str);
        pos = str.find(':');
        profesor[i].nombre = str.substr(0, pos);
        str.erase(0,pos+1);
        int j = 0;
        while (str.find(',')!=-1){
            pos = str.find('-');
            profesor[i].cursos[j].Cnombre = str.substr(0, pos);
            anadirCursos(profesor[i].cursos[j].Cnombre);
            profesor[i].cursos[j].periodos = stoi(str.substr(pos+1, 1));
            str.erase(0,pos+3);
            j++;
        }
        pos = str.find('-');
        profesor[i].cursos[j].Cnombre = str.substr(0,pos);
        anadirCursos(profesor[i].cursos[j].Cnombre);
        profesor[i].cursos[j].periodos = stoi(str.substr(pos+1,1 ));
        i++;
    }
    nProfes=i;


    infile.close();
    // ==========================================================================

    // ===========HALLANDO EL GRAFO LINEAL DE G============
    int n = CantidadVertices(profesor);
    AsignandoVertices(vertices, n);
    // ===========MATRIZ DE ADYACENCIA DE L(G)=============
    fout.open("graph.txt");
    inicializarMatriz(n);
    llenarMatriz(n, vertices);
    salidatxt(n);
    fout.close();

    inicializarHorario();

    infile.open("coloring.txt");
    while (!infile.eof()){
        getline(infile,str);
        int pos = str.find(' ');

        int i_vert = stoi(str.substr(0,pos+1)) - 1;
        int j = stoi(str.substr(pos+1,1)) - 1;
        if (j>nCromatico) nCromatico = j+1;
        int i = obtenerPosicionProfe(vertices[i_vert].x);
        horario[i][j] = vertices[i_vert].y;
    }

    
    fout.open("horario.txt");
    salidaHorariotxt();
    fout.close();
    
    return 0;    
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

int CantidadVertices(Profe prof[]){
    int suma=0;
    for (int i = 0; i < nProfes; i++){
        for (int j = 0; j < nCursos; j++){
            suma += prof[i].cursos[j].periodos;}
    }
    return suma;
}

void AsignandoVertices(VerticeDelLineal v[], int tam) {
    int l = 0;
    for (int i = 0; i < nProfes; i++) {
        for (int j = 0; j < nCursos; j++) {
            int nPeriodos = profesor[i].cursos[j].periodos;
            int k = 1;
            while (nPeriodos != 0) {
                v[l].x = profesor[i].nombre;
                v[l].y = profesor[i].cursos[j].Cnombre;
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
            horario[i][j]="-----";
        }
    }
}

void inicializarMatriz(int n){
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n; ++j) {
            matriz[i][j]=0;
        }
    }
}
void llenarMatriz(int n, VerticeDelLineal v[]){
    for (int i = 0; i < n; i++){
        string str1_1 = v[i].x;
        string str1_2= v[i].y;
        for (int j = 0; j < n; j++){
            string str2_1 = v[j].x;
            string str2_2= v[j].y;
            if(str1_1.compare(str2_1)==0 && i!=j)
                matriz[i][j]= 1;
            else if(str1_2.compare(str2_2)==0 && i!=j)
                matriz[i][j]=1;
        }
    }
}


void salidaHorariotxt(){
    for (int i=1; i<= nCromatico; i++ ){
        fout<<setw(36)<<i;
    }   fout<<endl;
    for (int i=0; i<nProfes; i++){
        fout<<profesor[i].nombre<<setw(30);
        for (int j=0; j<4; j++){
            fout<<setw(20)<<horario[i][j];
        }   fout<<endl;
    }
}

void salidatxt(int n){
  fout << n << endl;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;++j){
      fout << matriz[i][j] <<'\t';
    }
    fout <<'\n';
  }
}
