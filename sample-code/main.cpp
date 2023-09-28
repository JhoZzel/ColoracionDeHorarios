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
void inicializarMatriz(int n);
void llenarMatriz(int n, VerticeDelLineal v[]);
void imprimirMatrizAdyacenciaDelLinealTXT(int n);


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

    // MATRIZ DE ADYACENCIA DE L(G
    fout.open("matrizAdy_GrafoLineal.txt");
    inicializarMatriz(nVertices);
    llenarMatriz(nVertices, vertices);
    imprimirMatrizAdyacenciaDelLinealTXT(nVertices);
    fout.close();

    cout<<"Archivo \"matrizAdy_GrafoLineal.txt\" creado exitosamente";
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

void imprimirMatrizAdyacenciaDelLinealTXT(int n){
  fout << n << endl;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;++j){
      fout << matriz[i][j] <<'\t';
    }
    fout <<'\n';
  }
}