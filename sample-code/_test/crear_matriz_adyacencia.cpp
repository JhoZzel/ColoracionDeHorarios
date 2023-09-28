#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>

using namespace std;

struct VertLineal{
    int v1;
    int v2;
} ;

ifstream infile;
ofstream fout;
string str,aux,cursos[100],profesores[100];
int k=0,l=0,nProf,nCursos;
int p[100][100]={};
int p_lineal[100][100]={};
VertLineal v[100];
string cursos1[100];

//void imprimirMatriz();
int obtenerVertice(string s);
bool NoSeRepite(string s, string c1[]);

int main(){
    infile.open("input.txt");
    getline(infile, str);
    aux = str[0]; nProf = stoi(aux);
    aux = str[2]; nCursos = stoi(aux);

    while (!infile.eof()){
        getline(infile, str);        
        int pos =  str.find(":");
        profesores[l] = str.substr(0,pos); l++;
        str.erase(0,pos + 2);

        while(str.find(",")!=-1){
            int pos_f = str.find(", ");
            cursos[k] = str.substr(0,pos_f);
            str.erase(0,pos_f + 2);
            k++;
        }

        cursos[k] = str;
        k++;
    }   infile.close();

    
    // codigo del cpp / cursos repetidos
    //string cursos1[nCursos];
    cursos1[0] = cursos[0];
    int j=1;
    for(int i=1; i < k; i++){
        if(NoSeRepite(cursos[i], cursos1)){
            cursos1[j]=cursos[i];
            j++;
        }
    }


    // Creamos la matriz de adyacencia original
    infile.open("input.txt");
    getline(infile, str);
    int fila=0, col=0;
    while (!infile.eof()){
        getline(infile, str);
        int pos =  str.find(":");
        str.erase(0,pos + 2);
        
        while(str.find(",")!=-1){
            int pos_f = str.find(", ");
            string curso = str.substr(0,pos_f);
            col = obtenerVertice(curso);
            p[fila][col]=1;
            p[col][fila]=1;

            str.erase(0,pos_f + 2);
        }
        col = obtenerVertice(str);
        p[fila][col]=1;
        p[col][fila]=1;
        fila++;
    }

    

    k=0; //  cantidad de vertices del grafo lineal

    for (int i=0; i<nProf; i++){
        for (int j=nProf; j<nProf+nCursos; j++){
            if (p[i][j]==1){
                v[k].v1=i;  
                v[k].v2=j;       
                k++;      
            }
        }
    }

    for (int i=0; i<k; i++){
        for (int j=0; j<k; j++){
            if ( (i!=j) && (v[i].v1 == v[j].v1 || v[i].v2==v[j].v2) ){
                p_lineal[i][j]=1;
            }
        }
    }
      
    fout.open("salida.txt");
    fout<<k<<endl;
    for (int i=0; i<k; i++){
        for (int j=0; j<k; j++){
            fout<<p_lineal[i][j]<<" ";
        }   fout<<endl;
    }   fout.close();
    

    for (int i=0; i<k; i++){
        cout<<i+1<<" => ("<<v[i].v1<<", "<<v[i].v2<<")"<<endl;
    }
    

    return 0;
}

int obtenerVertice(string s){
    int n;
    for (int i=0; i<nCursos; i++){
        if (cursos1[i].compare(s)==0) n=i;
    }   n+=nProf;
    return n;
}

bool NoSeRepite(string s, string c1[]){
    for (int i = 0; i < nCursos; i++){ 
        if(s.compare(c1[i])==0){
            return false;
            break;
        }
    }
    return true;
}

/*
void imprimirMatriz(){
    int n = nProf + nCursos;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout<<p[i][j]<<" ";
        }   cout<<endl;
    }  
}
*/