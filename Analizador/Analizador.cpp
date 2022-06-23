#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;

//importaciones
#include "../Comandos/exec.h"
#include "../Comandos/mkdisk.h"
#include "../Comandos/rmdisk.h"
#include "../Comandos/fdisk.h"
#include "../Comandos/mount.h"
#include "../Comandos/unmount.h"
#include "../Comandos/rep.h"
#include "../Comandos/mkfs.h"
#include "../Comandos/mkdir.h"
#include "../Comandos/mkfile.h"

//analizador principal
void analizadorGeneral(char comando[]){
 char lineacomando[100]="";//aux para almacenar el primer comando y comparar
 int contador=0; //para iterar cada caracter

 if(comando==NULL){
     cout << "Error -> Comando vacio"<<endl;
 }else{
     while(comando[contador]!=NULL){
        if (comando[contador]==' '){//para separar los comandos
            contador++;
            break;
        }else{//para ir agregando cada caracter de un comando y después comparar
            char aux[1]="";
            aux[0]= tolower(comando[contador]);
            strncat(lineacomando,aux,1);
            contador++;
        }

        //para comparar los comandos
        if (strcmp(lineacomando,"exec")==0){
            analisisExec(comando);
            memset(lineacomando,0,100);
        }else if (strcmp(lineacomando,"mkdisk")==0){
            analisisMkdisk(comando);
            memset(lineacomando,0,100);
        }else if (strcmp(lineacomando,"rmdisk")==0){
            analisisRmdisk(comando);
            memset(lineacomando,0,100);
        }else if (strcmp(lineacomando,"fdisk")==0){
            analsisFdisk(comando);
            memset(lineacomando,0,100);
        }else if (strcmp(lineacomando,"mount")==0){
            analisisMount(comando);
            memset(lineacomando,0,100);
        }else if (strcmp(lineacomando,"unmount")==0){
            analisisUnmount(comando);
            memset(lineacomando,0,100);
        }else if (strcmp(lineacomando,"mkfs")==0){
            analisisMkfs(comando);
            memset(lineacomando,0,100);
        }else if (strcmp(lineacomando,"mkfile")==0){
            analisisMkfile(comando);
            memset(lineacomando,0,100);
        }else if (strcmp(lineacomando,"rm")==0){
            cout << "Encontro: "<< lineacomando<<endl;
        }else if (strcmp(lineacomando,"mkdir")==0){
            analisisMkdir(comando);
            memset(lineacomando,0,100);
        }else if (strcmp(lineacomando,"cp")==0){
            cout << "Encontro: "<< lineacomando<<endl;
        }else if (strcmp(lineacomando,"ls")==0){
            cout << "Encontro: "<< lineacomando<<endl;
        }else if (strcmp(lineacomando,"pause")==0){
            cout << "Encontro: "<< lineacomando<<endl;
        }else if (strcmp(lineacomando,"rep")==0){
            analisisRep(comando);
            memset(lineacomando,0,100);
        }
     }
 }
}