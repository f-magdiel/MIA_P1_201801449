#include <iostream>
#include <cstring>

//importaciones
#include "./Analizador/Analizador.h"

using namespace std;
int main() {
    bool salir=false;
    char comando [100]="";

    while(!salir){
     cout << "╔═══════════════════════════════════════════╗"<<endl;
     cout << "║                 PROYECTO 1                ║"<<endl;
     cout << "║ MANEJO E IMPLEMENTACION DE ARCHIVOS       ║"<<endl;
     cout << "║ FRANCISCO MAGDIEL ASICONA MATEO 201801449 ║"<<endl;
     cout << "║ VACACIONES JUNIO 2022                     ║"<<endl;
     cout << "╚═══════════════════════════════════════════╝"<<endl;
     cout << "COMANDO >> ";

     cin.getline(comando,100);

     if (strcmp(comando,"salir")==0){
        salir = true;
     }else{
         if (strcmp(comando,"")!=0){
             analizadorGeneral(comando);
         }else{
             cout << "Error -> Comando vacio"<<endl;
         }
     }

    }
    return 0;
}
