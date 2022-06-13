#include <iostream>
#include <cstring>
#include <dirent.h>
#include <string>

#include "../Comandos/mkdisk.h"
#include "../Comandos/mount.h"
using namespace std;

bool validacionReporte(char _path[]){
    FILE *file;
    if(file= fopen(_path,"r")){
        fclose(file);
        return true;
    }else{
        //fclose(file);
        return false;
    }
}

bool validacionDirectorioReporte(char _direc[]){
    DIR* directorio;
    if(directorio= opendir(_direc)){
        closedir(directorio);
        return true;
    }else{
        closedir(directorio);
        return false;
    }
}

void analisisRep(char comando[]){
    char lineacomando[100]="";
    char valor_id[10]="";
    char valor_path[100]="";
    char valor_name[20]="";
    int contador=0;
    //tipos de reportes
    bool flag_mbr=false;
    bool flag_disk=false;
    bool flag_block=false;
    bool flag_bm_block=false;
    bool flag_bm_inode=false;
    bool flag_inode=false;
    bool flag_journaling=false;
    bool flag_tree=false;
    bool flag_sb=false;
    bool flag_file=false;

    while(comando[contador]!=NULL){
        if (comando[contador] == ' ') {
            contador++;
            memset(lineacomando, 0, 100);
        } else if (comando[contador] == '>') {
            char aux[1] = "";
            aux[0] = tolower(comando[contador]);
            strncat(lineacomando, aux, 1);
            contador++;
        } else {
            char aux[1] = "";
            aux[0] = tolower(comando[contador]);
            strncat(lineacomando, aux, 1);
            contador++;
        }

        //validacion tipo de reportes
        if(strcmp(lineacomando,"rep")==0){
            cout << "Encontro: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            contador++;
        }else if(strcmp(lineacomando,"$name=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);

            while (comando[contador] != NULL) {
                if (comando[contador] == ' ' || comando[contador] == '\n') {
                    contador++;
                    break;
                } else {
                    char aux[1] = "";
                    aux[0] = tolower(comando[contador]);
                    strncat(valor_name, aux, 1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_name<<endl;
        }else if(strcmp(lineacomando,"$id=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            while (comando[contador] != NULL) {
                if (comando[contador] == ' ' || comando[contador] == '\n') {
                    contador++;
                    break;
                } else {
                    char aux[1] = "";
                    aux[0] = tolower(comando[contador]);
                    strncat(valor_id, aux, 1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_id<<endl;

        }else if(strcmp(lineacomando,"$path=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);

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

    //validacion argumentos de rep
    //validacion directorio
    int cont_barra1=0;
    int cont_1=0;
    char direc[100]="";
    //busca donde está el último / para guardar
    while(valor_path[cont_1]!=NULL){
        if(valor_path[cont_1]=='/'){
            cont_barra1++;
            cont_1++;
        }
        cont_1++;
    }
    //empieza a generar solo el directorio con el valor anteriro de cont_barra1
    int cont_barra2=0;
    int cont_2=0;
    while(valor_path[cont_2]!=NULL){
        if(valor_path[cont_2]=='/'){
            char aux[1]="";
            aux[0] = valor_path[cont_2];
            strncat(direc,aux,1);
            cont_barra2++;
            cont_2++;
        }

        if(cont_barra1==cont_barra2){
            break;
        }else{
            char aux[1]="";
            aux[0] = valor_path[cont_2];
            strncat(direc,aux,1);
            cont_2++;
        }
    }

    char nombre_rep[20]="";
    while(valor_path[cont_2]!=NULL){
        if(valor_path[cont_2]=='.'){
            break;
        }else{
            char aux[1]="";
            aux[0] = valor_path[cont_2];
            strncat(nombre_rep,aux,1);
            cont_2++;
        }
    }
    //obtengo el nombre del reporte

    cout << "Directorio = "<<direc<<endl;
    cout << "Path = "<<valor_path<<endl;
    cout << "nombre rep = "<<nombre_rep<<endl;
    bool flag_directorio = validacionDirectorioReporte(direc);
    bool flag_rep = validacionReporte(valor_path);

    //tipo de reporte de generar
    bool flag_generador=true;
    if(strcmp(valor_name,"mbr")==0){
        flag_mbr = true;
    }else if(strcmp(valor_name,"disk")==0){
        flag_disk = true;
    }else if(strcmp(valor_name,"block")==0){
        flag_block = true;
    }else if(strcmp(valor_name,"bm_block")==0){
        flag_bm_block=true;
    }else if(strcmp(valor_name,"mb_inode")==0){
        flag_bm_inode = true;
    }else if(strcmp(valor_name,"inode")==0){
        flag_inode=true;
    }else if(strcmp(valor_name,"journaling")==0){
        flag_journaling=true;
    }else if(strcmp(valor_name,"tree")==0){
        flag_tree=true;
    }else if(strcmp(valor_name,"sb")==0){
        flag_sb=true;
    }else if(strcmp(valor_name,"file")==0){
        flag_file = true;
    }else{
        flag_generador=false;
        cout << "Error -> El reporte solicitado es incorrecto "<<valor_name<<endl;
    }
    //flag. paara generar reporte
    if(flag_generador){
        if(flag_directorio){//existe directorio
            if(flag_rep){//existe rep
                cout << "Error -> Ya existe ese reporte con el mismo nombre"<<endl;
            }{//no existe rep
                cout << "Aviso -> Se genera reporte "<<valor_name<<endl;

            }
        }else{// no existe directorio
            //se crea directorio
            cout << "Aviso -> No existe directorio para generar rep, pero se crea"<<endl;
            string path = charToString(direc);
            string dir = "mkdir -p \""+path+"\"";
            system(dir.c_str());
            cout << "Aviso -> Se genera reporte "<<valor_name<<endl;
            if(flag_mbr){
                repMbr(valor_id,valor_name,valor_path,direc);
            }else if(flag_disk){

            }


        }
    }


}
