#include <iostream>
#include <string>

using namespace std;
int main(){
    string s[] = {"hola","asd","asdadsdsa","asa","a"};
    int tamano = sizeof(s)/sizeof(string);

    cout<<tamano<<endl;
    
    return EXIT_SUCCESS;
}