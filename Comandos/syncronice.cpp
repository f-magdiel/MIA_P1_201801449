#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "../Json/json.hpp"
#include "../Comandos/mount.h"
#include "../Estructuras/DISCO.h"
#include "../Comandos/mkdisk.h"
#include "../Estructuras/MBR.h"
#include "../Estructuras/SUPER_BLOQUE.h"
#include "../Estructuras/INODOS.h"
#include "../Estructuras/BLOQUEARCHIVO.h"
#include "../Estructuras/BLOQUECARPETA.h"
#include "../Estructuras/APUNTADORES.h"

using json = nlohmann::json;
json salida;//estructura vacia
json jsoninodos;//vacia pero array
json jsonbloques;
using namespace std;
string folderJson(int indice,BLOQUECARPETA *carpeta,int tree){
    json jsonbloquecarpeta;
    json bloque;

    for (int i = 0; i < 4; ++i) {
        bloque["Name"]=charToString(carpeta->b_content[i].b_name);
        bloque["Inodo"]="Inodo"+to_string(carpeta->b_content[i].b_inodo);
        bloque["Bloque"]="Bloque"+ to_string(indice);
        jsonbloques.push_back(bloque);
    }
    //jsonbloques["Bloque"+ to_string(indice)] = jsonbloquecarpeta;

    return "so";
}

string inodoJson(int indice,INODOS * inode,int tree){
    json jsoninod;
    json jsonbloque;
    string inodos="\t\t{\n";
    string conexionesinodos="";
    inodos+="\t\t\"Inodo"+ to_string(indice)+"\":[\n";
    for (int i = 0; i < 15; ++i) {
        if(inode->i_block[i]!=-1){
            inodos+="\t\t\t{\n";
            inodos+="\t\t\t\t\"Bloque\":"+to_string(inode->i_block[i])+"\n";
            inodos+="\t\t\t},\n";
            jsonbloque["Bloque"]= "Bloque"+to_string(inode->i_block[i]);
            jsonbloque["Inodo"]="Inodo"+ to_string(indice);
            //jsoninodos.push_back(jsonbloque);
        }
    }
   
    jsoninodos.push_back(jsonbloque);
    //jsoninodos["Inodosss"]=jsonbloque;
    inodos+="\t\t\t]\n";
    inodos+="\t\t},\n";

    return inodos;
}

void ejecutarSyncronice(DISCO disco,char _id[], char _path[]){

    string name_json = charToString(_path);
    //para raid
    bool generar=false;
    bool disk_or = validacionPathMount(disco.path);
    string nuevo = crearPathCopia(disco.path);
    char nuevopath[100]="";
    strcpy(nuevopath,nuevo.c_str());
    bool disk_cp = validacionPathMount(nuevopath);
    char pathreal[100]="";
    if(disk_cp && disk_or){
        strcpy(pathreal,disco.path);
        generar=true;
    }else if(disk_cp){
        strcpy(pathreal,nuevopath);
        generar=true;
    }

    if(generar){//es verdadero
        FILE *file;
        file = fopen(pathreal,"rb+");
        MBR mbr;
        fseek(file,0,SEEK_SET);
        fread(&mbr,sizeof(MBR),1,file);
        int indice=0;
        string nombre_buscar;
        for (int i = 0; i < 4; ++i) {
            if(strcmp(disco.mbr_particion[i].id,_id)==0){
                nombre_buscar = charToString(disco.mbr_particion[i].part_name);
                break;
            }
        }

        for (int i = 0; i < 4; ++i) {
            if(strcmp(mbr.mbr_particion[i].part_name,nombre_buscar.c_str())==0){
                indice=i;
                break;
            }
        }
        //se lee el super bloque
        SUPER_BLOQUE auxsuper;
        fseek(file,mbr.mbr_particion[indice].part_start+sizeof (mbr.mbr_particion[indice])+1,SEEK_SET);
        fread(&auxsuper,sizeof (SUPER_BLOQUE),1,file);

        int num_de_inodos = auxsuper.s_inode_count;
        int inodo_en_uso = auxsuper.s_inode_count-auxsuper.s_free_inodes_count;
        string graphInodos="\t\"Inodos\":[\n";
        char bit_nodos[num_de_inodos];
        fseek(file,auxsuper.s_bm_inode_start,SEEK_SET);
        fread(&bit_nodos,sizeof(char),num_de_inodos,file);

        //inicia contenidos
        for (int i = 0; i < num_de_inodos; ++i) {
            if(bit_nodos[i]=='1'){
                INODOS inodo_read;
                fseek(file,auxsuper.s_inode_start+i*sizeof (INODOS),SEEK_SET);
                fread(&inodo_read,sizeof (INODOS),1,file);
                graphInodos += inodoJson(i,&inodo_read,1);
                graphInodos += "\n\n";
            }
        }

        graphInodos+="\t]\n";

        //Siguen los bloques
        string allbloques;
        int num_bloques = auxsuper.s_block_count;
        char bit_bloques[num_bloques];
        int bloque_en_uso = auxsuper.s_block_count-auxsuper.s_free_blocks_count;

        //se lee
        fseek(file,auxsuper.s_bm_block_start,SEEK_SET);
        fread(&bit_bloques,sizeof (char),num_bloques,file);

        //se procede a conectarlos
        for (int i = 0; i < num_bloques; ++i) {
            if(bit_bloques[i] == '1'){
                //para carpetas
                BLOQUECARPETA readcarpeta;
                fseek(file,auxsuper.s_block_start+i*64,SEEK_SET);
                fread(&readcarpeta,64,1,file);
                allbloques+= folderJson(i,&readcarpeta,1);
            }else if(bit_bloques[i]=='2'){
                //para archivos
                /*BLOQUEARCHIVO readarchivo;
                fseek(file,auxsuper.s_block_start+i*64,SEEK_SET);
                fread(&readarchivo,64,1,file);
                allbloques+= folderJson(i,&readarchivo,1);*/

            }else if(bit_bloques[i]=='3'){
                //para apuntadores
               /* APUNTADORES readapuntador;
                fseek(file,auxsuper.s_block_start+i*64,SEEK_SET);
                fread(&readapuntador,64,1,file);
                allbloques+= folderJson(i,&readapuntador,1);*/
            }
        }
        salida["Inodos"]=jsoninodos;
        cout << salida<<endl;
        salida["Bloques"]=jsonbloques;
        //finalizando
        string arbol = "{\n"+graphInodos+"\n\n\n"+allbloques+"}\n";
        fclose(file);
        //generar .dot
        ofstream  fs(name_json);
        fs << salida<<endl;
        fs.close();
    }else{
        cout << "Error -> No se puede generar el JSON posiblemento disco no existe"<<endl;
    }

}

void analisisSyncronice(char comando[]){
    int contador=0;
    char valor_id[10]="";
    char valor_path[100]="";
    char lineacomando[100]="";

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
        //validar argumentos
        if(strcmp(lineacomando,"syncronice")==0){
            cout << "Encontro: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            contador++;
        }else if(strcmp(lineacomando,"@id=>")==0){
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
        }else if(strcmp(lineacomando,"@path=>")==0){
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

    if(valor_path[0]!='\000' && valor_id[0]!='\000'){
        //se valida que que el disco esté montado
        DISCO disco = buscarDisco(valor_id);
        if(disco.mbr_tamano!=0){//--->si está montado
            //validar formato
            if(disco.formato==3){//---> tiene formato ext3
                //siempre está la raiz -> se genera JSON
                ejecutarSyncronice(disco,valor_id,valor_path);
            }else{
                cout << "Error -> El disco no tiene formato"<<endl;
            }
        }else{
            cout << "Error -> El disco no está montado"<<endl;
        }

    }else{
        cout << "Error -> Comando viene vacio"<<endl;
    }

}