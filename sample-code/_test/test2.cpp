#include<iostream>
#include<cstring>
using namespace std;
int main(){
    string Cursos[] = {"abc", "abc", "cde", "cde"};
    string newCursos[sizeof(Cursos)];
    bool flag = true;
    int k=0;
    newCursos[0] = Cursos[0];
    for (int i = 0; i < sizeof(Cursos); i++)
    {
        for(int j = 0; j < sizeof(newCursos); j++){
            if(newCursos[j]==Cursos[i]){flag = false; }
        }
        if(flag = true){newCursos[k]=Cursos[i];}

        k++;
    }
}