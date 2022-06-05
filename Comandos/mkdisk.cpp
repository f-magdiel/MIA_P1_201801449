#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <dirent.h>
#include <cstdlib>

//importaciones
#include "../Estructuras/MBR.h"

using namespace std;
//para convertir array de char a string
string charToString(char* a){
    string  s = a;
    return s;
}

//para validar el size
bool validacionSize(char valor[]){
    string size_string = charToString(valor);
    int size = stoi(size_string);

    if (size>0 && size % 8 == 0){
        return true;
    }
    return false;

}

//para validar el name, que venga de forma correcata
bool validacionName(char name[]){
    int ct;
    for (int i = 0; i < 20; ++i) {
        if(name[i]!=NULL){
            if (!isalnum(name[i]) && name[i]!='.' && name[i]!='_'){

                return false;
            }
            if(name[i]=='.'){
                ct=i;

            }
        }
    }

    //validacion extension
    if(name[ct+1]=='d'){
        if (name[ct+2]=='s'){
            if (name[ct+3]=='k'){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }


}

//para validar si existe el directorio
bool validacionPath(string path){
    DIR *directorio;//puntero de un directorio
    if(directorio = opendir(path.c_str())){
        closedir(directorio);
        return true;
    }else{

        return false;
    }

}
//solo para leer
void leerMkdisk(string path){
    FILE *file;
    file = fopen(path.c_str(),"rb");
    MBR *mbr = (MBR*) malloc(sizeof (MBR));
    fseek(file,0,SEEK_SET);
    fread(mbr,sizeof (MBR),1,file);
    cout << "tamaño "<<to_string(mbr->mbr_tamano)<<endl;
    cout << "fecha "<<ctime(&mbr->mbr_fecha_creacion)<<endl;
    cout << "signature "<<mbr->mbr_disk_signature<<endl;
}

//para crear el disco
void crearDiscos(char path[],char name[],char size[]){
    MBR* mbr = (MBR*) malloc(sizeof (MBR));
    string s_size = charToString(size);
    string s_path = charToString(path);
    string s_name = charToString(name);
    string path_disco = s_path+s_name;
    int _size = stoi(s_size);

    int size_bytes = _size*1024*1024;
    //se inicializa el mbr
    int start = (int)sizeof(MBR);
    mbr->mbr_disk_signature = rand()%100; //se asigna el signature con un random
    mbr->mbr_tamano = size_bytes;//se asigna en tamaño en bytes
    time_t tiempoactual;
    tiempoactual = time(NULL);
    mbr->mbr_fecha_creacion = tiempoactual;//se asigna el timepo de creacion

    //se inicializa las particiones
    mbr->mbr_particion_1.part_status = '0';
    mbr->mbr_particion_1.part_type = '-';
    mbr->mbr_particion_1.part_start = 0;
    mbr->mbr_particion_1.part_size = 0;

    mbr->mbr_particion_2.part_status = '0';
    mbr->mbr_particion_2.part_type = '-';
    mbr->mbr_particion_2.part_start = 0;
    mbr->mbr_particion_2.part_size = 0;

    mbr->mbr_particion_3.part_status = '0';
    mbr->mbr_particion_3.part_type = '-';
    mbr->mbr_particion_3.part_start = 0;
    mbr->mbr_particion_3.part_size = 0;

    mbr->mbr_particion_4.part_status = '0';
    mbr->mbr_particion_4.part_type = '-';
    mbr->mbr_particion_4.part_start = 0;
    mbr->mbr_particion_4.part_size = 0;

    //se escribe el disco
    FILE *file; //se crea el file para escribir en ello
    file = fopen(path_disco.c_str(),"w+b");// en modo escribir binario
    fseek(file,size_bytes,SEEK_SET);//se posicion donde termina el mbr
    fwrite("0",1,1,file);//se escribe el disco
    fseek(file,0,SEEK_SET);//se posiciona al principio del disco
    fwrite(mbr,sizeof (MBR),1,file);// se escribe el mbr

    fclose(file);
    cout << "Aviso -> El disco se creo exitosamente "<<endl;
    //leerMkdisk(path_disco);
}

//analisar argumentos de mkdisk
void analisisMkdisk(char comando[]){
    int contador=0;
    char lineacomando[100]="";

    char valor_size[20]="";
    char valor_path[100]="";
    char valor_name[50]="";


    while(comando[contador]!=NULL){
        if(comando[contador]==' '){
            contador++;
            memset(lineacomando,0,100);
        }else if (comando[contador]=='>'){
            char aux[1]="";
            aux[0]= tolower(comando[contador]);
            strncat(lineacomando,aux,1);
            contador++;
        }else{
            char aux[1]="";
            aux[0]= tolower(comando[contador]);
            strncat(lineacomando,aux,1);
            contador++;
        }

        //validacion argumentos y valores
        if(strcmp(lineacomando,"mkdisk")==0){
            cout << "Encontro: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            contador++;
        }else if (strcmp(lineacomando,"$size=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);

            while(comando[contador]!=NULL){
                if(comando[contador]==' ' || comando[contador]=='\n'){
                    contador++;
                    break;
                }else{
                    char aux[1]="";
                    aux[0]=comando[contador];
                    strncat(valor_size,aux,1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_size<<endl;
        }else if (strcmp(lineacomando,"$path=>")==0){
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
        }else if (strcmp(lineacomando,"$name=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);

            while(comando[contador]!=NULL){
                if (comando[contador]==' ' || comando[contador]=='\n'){
                    contador++;
                    break;
                }else{
                    char aux[1]="";
                    aux[0]=comando[contador];
                    strncat(valor_name,aux,1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_name<<endl;
        }
    }
    //>>>>>>>>>>>>>>>>>>Validaciones para crear el disco<<<<<<<<<<<<<<<<<<<<<<<<<<<
    string path = charToString(valor_path);
    bool flag_directorio = validacionPath(path);
    bool flag_size = validacionSize(valor_size);
    bool flag_name = validacionName(valor_name);
    //para agregar la la barra
    char barra[1];
    strcpy(barra,"/");
    strncat(valor_path,barra,1);
    //para realizar la copia
    char ext[10];
    strcpy(ext,"Copia_");

    if (flag_directorio){//existe directorio
        if (flag_size){// si el size es mayoy a cero y es multiplo de 8
            if (flag_name){// si el name es válido en nombre y extension
                // se procede a crear diso
                crearDiscos(valor_path,valor_name,valor_size);
                //se crea la copia
                strncat(valor_path,ext,7);
                crearDiscos(valor_path,valor_name,valor_size);
            }else{
                cout << "Error -> Name no válido "<<endl;
            }
        }else{
            cout << "Error -> Size no válido"<<endl;
        }
    }else{//no existe directorio
        cout << "Error -> Directorio no existe"<<endl;
        cout << "Aviso -> Se creo directorio"<<endl;
        //Como no existe el directorio se procede a crear
        string dir = "mkdir -p \""+path+"\"";
        system(dir.c_str());
        if (flag_size){// si el size es mayoy a cero y es multiplo de 8
            if (flag_name){// si el name es válido en nombre y extension
                // se procede a crear diso
                crearDiscos(valor_path,valor_name,valor_size);
                // se crea la copia
                strncat(valor_path,ext,7);
                crearDiscos(valor_path,valor_name,valor_size);
            }else{
                cout << "Error -> Name no válido "<<endl;
            }
        }else{
            cout << "Error -> Size no válido"<<endl;
        }
    }
}

