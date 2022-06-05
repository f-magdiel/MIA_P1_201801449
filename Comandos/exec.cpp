#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

//importaciones
#include "../Archivo/Archivo.h"

using namespace std;
//analizaor de comando exec
void analisisExec(char comando[]){
    int contador=0;
    char lineacomando[100]="";
    char valor_path[100]="";

    while(comando[contador]!=NULL){
        if(comando[contador]==' '){ //para separar argumentos del comando exec
            contador++;
            memset(lineacomando,0,100);
        }else if (comando[contador]=='>'){//para separar argumento y valor
            char aux[1]="";
            aux[0]= tolower(comando[contador]);
            strncat(lineacomando,aux,1);
            contador++;
        }else {//para obtener argumento
            char aux[1]="";
            aux[0]= tolower(comando[contador]);
            strncat(lineacomando,aux,1);
            contador++;
        }

        //validaciones de argumentos
        if (strcmp(lineacomando,"exec")==0){
            cout << "Encontro: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            contador++;
        }else if (strcmp(lineacomando,"$path=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            //para obtener el valor del argumento
            while(comando[contador]!=NULL){
                if(comando[contador]=='"'){//cuando viene con comillas el path
                    contador++;
                    while(comando[contador]!=NULL){
                        if(comando[contador]=='"'){
                            contador++;
                            break;
                        }else{
                            char aux[1]="";
                            aux[0]= comando[contador];
                            strncat(valor_path,aux,1);
                            contador++;
                        }
                    }
                }else{
                    if(comando[contador]==' ' || comando[contador]=='\n'){
                        contador++;
                        break;

                    }else{
                        char aux[1]="";
                        aux[0]= comando[contador];
                        strncat(valor_path,aux,1);
                        contador++;
                    }
                }

            }
            cout << "Valor: "<<valor_path<<endl;
        }
    }
    //se abre y lee el archivo script
    leerArchivo(valor_path);
}
