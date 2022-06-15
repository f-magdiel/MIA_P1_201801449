#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>

#include "../Estructuras/DISCO.h"
#include "../Estructuras/MBR.h"
#include "../Estructuras/EBR.h"
#include "../Comandos/mkdisk.h"
using namespace std;
DISCO disco[99];
char abdecedario[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int contador_abc=0;
int contador_disco=0;
vector <string> nodos;

//para mkfs
DISCO buscarDisco(char _id[]){
    DISCO nulo;
    for (int i = 0; i < 99; ++i) {
        if(disco[i].mbr_tamano!=0){
            for (int j = 0; j < 4; ++j) {
                if(strcmp(disco[i].mbr_particion[j].id,_id)==0){
                    return disco[i];
                    break;
                }

            }
        }
    }
    return nulo;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>REPORTES<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void repDisk(char _id[],char _namerep[],char _path[],char _dir[]){
    bool flag_rep=false;
    string dir = charToString(_dir);
    string name_dot = dir+charToString(_namerep)+".dot";
    int suma=0;

    for (int i = 0; i < 99; ++i) {
        if(disco[i].mbr_tamano!=0){
            for (int j = 0; j < 4; ++j) {
                if(strcmp(disco[i].mbr_particion[j].id,_id)==0){
                    flag_rep=true;
                    //generando .dot
                    ofstream fs(name_dot);
                    fs << "digraph G{"<<endl;
                    fs << "tbl ["<<endl;
                    fs << "shape=plaintext"<<endl;
                    fs << "label=<"<<endl,
                    fs << "<table border='2' cellborder='0' color='blue' cellspacing='1'>"<<endl;
                    fs << "<tr>"<<endl;
                    fs << "<td colspan='1' rowspan='1'>"<<endl;
                    fs << "<table color='orange' border='1' cellborder='1' cellpadding='10' cellspacing='0'>"<<endl;
                    fs << "<tr><td>MBR</td></tr>"<<endl;
                    fs << "</table>"<<endl;
                    fs << "</td>"<<endl;

                    for (int k = 0; k < 4; ++k) {
                        if(disco[i].mbr_particion[k].part_type=='p'){
                            int sizeP, sizeOP = 0;
                            sizeP = disco[i].mbr_particion[k].part_size;
                            sizeOP = (sizeP*100)/disco[i].mbr_tamano;
                            string tam = to_string(sizeOP);
                            suma +=sizeP;
                            fs << "<td colspan='1' rowspan='1'>"<<endl;
                            fs << "<table color='orange' border='1' cellborder='1' cellpadding='10' cellspacing='0'>"<<endl;
                            fs << "<tr><td>Primaria <br/>"+tam+"% del disco</td></tr>"<<endl;
                            fs << "</table>"<<endl;
                            fs << "</td>"<<endl;

                        }else if(disco[i].mbr_particion[k].part_type=='e'){
                            fs << "<td colspan='1' rowspan='1'>"<<endl;
                            fs << "<table color='red' border='1' cellborder='1' cellpadding='10' cellspacing='0'>"<<endl;
                            fs << "<tr>"<<endl;
                            int sizeP, sizeOP = 0;
                            sizeP = disco[i].mbr_particion[k].part_size;
                            sizeOP = (sizeP*100)/disco[i].mbr_tamano;
                            string tam = to_string(sizeOP);
                            suma+= sizeP;
                            for (int l = 0; l < 24; ++l) {
                                if(disco[i].ebr_logicas[l].part_size!=0){
                                    fs << "<td>EBR</td><td> Logica <br/>"<<endl;
                                    //<<<<<<<<<<<<<<<<<<<< PENDIENTE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
                                }
                            }

                        }
                    }

                }

            }

        }
    }
}

void repMbr(char _id[],char _namerep[],char _path[],char _dir[]){
    bool flag_rep = false;
    string dir = charToString(_dir);
    string name_dot = dir+charToString(_namerep)+".dot";

    for (int i = 0; i < 99; ++i) {
        if(disco[i].mbr_tamano!=0){//si existo disco
            for (int j = 0; j < 4; ++j) {
                if(strcmp(disco[i].mbr_particion[j].id,_id)==0){// si está en las 4 basica
                    //se realiza reporte mbr
                    flag_rep=true;
                    char *tt = ctime(&disco[i].mbr_fecha_creacion);
                    string time = charToString(tt);
                    ofstream fs(name_dot);
                    fs << "digraph G {"<<endl;
                    fs << "rankdir=LR;"<<endl;
                    fs << "mbr["<<endl;
                    fs << "shape=plaintext "<<endl;
                    fs << "label=<"<<endl;
                    fs << "<table border='0' cellborder='1' color='blue' cellspacing='0'>"<<endl;
                    fs << "<tr><td>MBR</td></tr>"<<endl;
                    fs << "<tr><td cellpadding='4'>"<<endl;
                    fs << "<table color='orange' cellspacing='0'>"<<endl;
                    fs << "<tr><td> MBR  </td></tr>"<<endl;
                    fs << "<tr><td> Mbr_tamaño: "+to_string(disco[i].mbr_tamano)+"</td></tr>"<<endl;
                    fs << "<tr><td> Mbr_fecha_creacion: "+time+"</td></tr>"<<endl;
                    fs << "<tr><td> Mbr_signature: "+ to_string(disco[i].mbr_disk_signature)+"</td></tr>"<<endl;
                    fs << "</table>"<<endl;
                    fs << "</td>"<<endl;
                    fs << "</tr>"<<endl;
                    fs <<"\n"<<endl;
                    //para los 4 basicos
                    for (int k = 0; k < 4; ++k) {
                        if(disco[i].mbr_particion[k].part_size!=0){
                            string s;
                            s += disco[i].mbr_particion[k].part_status;
                            string t;
                            t += disco[i].mbr_particion[k].part_type;
                            fs <<"<tr><td cellpadding='4'>"<<endl;
                            fs <<"<table color='orange' cellspacing='0'>"<<endl;
                            fs <<" <tr><td> PARTICION  </td></tr>"<<endl;
                            fs << "<tr><td> Nombre: "+ charToString(disco[i].mbr_particion[k].part_name)+"</td></tr>"<<endl;
                            fs << "<tr><td> Status: "+s+"</td></tr>"<<endl;
                            fs << "<tr><td> Tipo: "+t+"</td></tr>"<<endl;
                            fs << "<tr><td> Fit: "+charToString(disco[i].mbr_particion[k].part_fit)+"</td></tr>"<<endl;
                            fs << "<tr><td> Start: "+to_string(disco[i].mbr_particion[k].part_start)+"</td></tr>"<<endl;
                            fs << "<tr><td> Size: "+to_string(disco[i].mbr_particion[k].part_size)+"</td></tr>"<<endl;
                            fs << "</table>"<<endl;
                            fs << "</td>"<<endl;
                            fs << "</tr>"<<endl;
                            fs << "\n"<<endl;
                        }
                    }
                    //finaliza para el mbr
                    fs << "</table>"<<endl;
                    fs << ">];"<<endl;

                    //buscar las logicas
                    for (int k = 0; k < 24; ++k) {
                        if(disco[i].ebr_logicas[k].part_size!=0){
                            nodos.push_back("ebr"+to_string(k));
                            fs << "ebr"+to_string(k)+" ["<<endl;
                            fs << "shape=plaintext"<<endl;
                            fs << "label=<"<<endl;
                            fs << "<table border='0' cellborder='1' color='blue' cellspacing='0'>"<<endl;
                            fs << "<tr><td>ebr</td></tr>" <<endl;
                            fs << "<tr><td cellpadding='4'>"<<endl;
                            fs << "<table color='orange' cellspacing='0'>"<<endl;
                            fs << "<tr><td> Nombre: "+charToString(disco[i].ebr_logicas[k].part_name)+" </td></tr>"<<endl;
                            fs << "<tr><td> Fit: "+charToString(disco[i].ebr_logicas[k].part_fit)+" </td></tr>"<<endl;
                            fs << "<tr><td> Start: "+to_string(disco[i].ebr_logicas[k].part_start)+" </td></tr>"<<endl;
                            fs << "<tr><td> Size: "+to_string(disco[i].ebr_logicas[k].part_size)+" </td></tr>"<<endl;
                            fs << "<tr><td> Next: "+to_string(disco[i].ebr_logicas[k].part_next)+" </td></tr>"<<endl;
                            fs << "</table>"<<endl;
                            fs << "</td>"<<endl;
                            fs << "</tr>"<<endl;
                            fs << "</table>"<<endl;
                            fs << ">];\n"<<endl;
                            fs << "\n"<<endl;
                        }
                    }
                    int tam_vec = nodos.size();
                    if(tam_vec>=1){
                        //fs << nodos[0] +" -> "+ nodos[1] <<endl;
                        for (int k = 0; k < tam_vec-1; ++k) {
                            fs << nodos[k] +" -> "+ nodos[k+1]+"\n"<<endl;
                        }
                    }
                    fs << "}\n"<<endl;
                    fs.close();
                    break;
                }

                if(disco[i].mbr_particion[j].part_type=='e'){//si es extendida y nombre no es igual se busca en logicas
                    for (int k = 0; k < 24; ++k) {
                        if(strcmp(disco[i].ebr_logicas[k].id,_id)==0){
                            //se desmonta
                           flag_rep=true;
                            ofstream fs(name_dot);
                            char *tt = ctime(&disco[i].mbr_fecha_creacion);
                            string time = charToString(tt);
                            fs << "digraph G {"<<endl;
                            fs << "rankdir=LR;"<<endl;
                            fs << "mbr["<<endl;
                            fs << "shape=plaintext "<<endl;
                            fs << "label=<"<<endl;
                            fs << "<table border='0' cellborder='1' color='blue' cellspacing='0'>"<<endl;
                            fs << "<tr><td>MBR</td></tr>"<<endl;
                            fs << "<tr><td cellpadding='4'>"<<endl;
                            fs << "<table color='orange' cellspacing='0'>"<<endl;
                            fs << "<tr><td> MBR  </td></tr>"<<endl;
                            fs << "<tr><td> Mbr_tamaño: "+to_string(disco[i].mbr_tamano)+"</td></tr>"<<endl;
                            fs << "<tr><td> Mbr_fecha_creacion: "+time+"</td></tr>"<<endl;
                            fs << "<tr><td> Mbr_signature: "+ to_string(disco[i].mbr_disk_signature)+"</td></tr>"<<endl;
                            fs << "</table>"<<endl;
                            fs << "</td>"<<endl;
                            fs << "</tr>"<<endl;
                            fs <<"\n"<<endl;
                            //para los 4 basicos
                            for (int k = 0; k < 4; ++k) {
                                if(disco[i].mbr_particion[k].part_size!=0){
                                    string s;
                                    s += disco[i].mbr_particion[k].part_status;
                                    string t;
                                    t += disco[i].mbr_particion[k].part_type;
                                    fs <<"<tr><td cellpadding='4'>"<<endl;
                                    fs <<"<table color='orange' cellspacing='0'>"<<endl;
                                    fs <<" <tr><td> PARTICION  </td></tr>"<<endl;
                                    fs << "<tr><td> Nombre: "+ charToString(disco[i].mbr_particion[k].part_name)+"</td></tr>"<<endl;
                                    fs << "<tr><td> Status: "+s+"</td></tr>"<<endl;
                                    fs << "<tr><td> Tipo: "+t+"</td></tr>"<<endl;
                                    fs << "<tr><td> Fit: "+charToString(disco[i].mbr_particion[k].part_fit)+"</td></tr>"<<endl;
                                    fs << "<tr><td> Start: "+to_string(disco[i].mbr_particion[k].part_start)+"</td></tr>"<<endl;
                                    fs << "<tr><td> Size: "+to_string(disco[i].mbr_particion[k].part_size)+"</td></tr>"<<endl;
                                    fs << "</table>"<<endl;
                                    fs << "</td>"<<endl;
                                    fs << "</tr>"<<endl;
                                    fs << "\n"<<endl;
                                }
                            }
                            //finaliza para el mbr
                            fs << "</table>"<<endl;
                            fs << ">];"<<endl;

                            //buscar las logicas
                            for (int k = 0; k < 24; ++k) {
                                if(disco[i].ebr_logicas[k].part_size!=0){
                                    nodos.push_back("ebr"+to_string(k));
                                    fs << "ebr"+to_string(k)+" ["<<endl;
                                    fs << "shape=plaintext"<<endl;
                                    fs << "label=<"<<endl;
                                    fs << "<table border='0' cellborder='1' color='blue' cellspacing='0'>"<<endl;
                                    fs << "<tr><td>ebr</td></tr>" <<endl;
                                    fs << "<tr><td cellpadding='4'>"<<endl;
                                    fs << "<table color='orange' cellspacing='0'>"<<endl;
                                    fs << "<tr><td> Nombre: "+charToString(disco[i].ebr_logicas[k].part_name)+" </td></tr>"<<endl;
                                    fs << "<tr><td> Fit: "+charToString(disco[i].ebr_logicas[k].part_fit)+" </td></tr>"<<endl;
                                    fs << "<tr><td> Start: "+to_string(disco[i].ebr_logicas[k].part_start)+" </td></tr>"<<endl;
                                    fs << "<tr><td> Size: "+to_string(disco[i].ebr_logicas[k].part_size)+" </td></tr>"<<endl;
                                    fs << "<tr><td> Next: "+to_string(disco[i].ebr_logicas[k].part_next)+" </td></tr>"<<endl;
                                    fs << "</table>"<<endl;
                                    fs << "</td>"<<endl;
                                    fs << "</tr>"<<endl;
                                    fs << "</table>"<<endl;
                                    fs << ">];\n"<<endl;
                                    fs << "\n"<<endl;
                                }
                            }
                            int tam_vec = nodos.size();
                            if(tam_vec>=1){
                                //fs << nodos[0] +" -> "+ nodos[1] <<endl;
                                for (int k = 0; k < tam_vec-1; ++k) {
                                    fs << nodos[k] +" -> "+ nodos[k+1]+"\n"<<endl;
                                }
                            }
                            fs << "}\n"<<endl;
                            fs.close();

                            break;

                        }
                    }
                }
            }

        }
    }
    //para validar error
    if(flag_rep==false){
        cout << "Error -> No se puede generer reporte porque no se ha encontrado particion con id "<<_id<<endl;
    }
}


//para desmontar
void desmontarMount(char _id[]){
    bool flag_unmount=false;
    for (int i = 0; i < 99; ++i) {
        if(disco[i].mbr_tamano!=0){//si existo disco
            for (int j = 0; j < 4; ++j) {
                if(strcmp(disco[i].mbr_particion[j].id,_id)==0){// si está en las 4 basica
                    //se desmonta
                    disco[i].mbr_particion[j].part_type = '\000';
                    disco[i].mbr_particion[j].part_size = 0;
                    disco[i].mbr_particion[j].part_start = 0;
                    memset(disco[i].mbr_particion[j].part_fit,0,3);
                    memset(disco[i].mbr_particion[j].part_name,0,16);
                    memset(disco[i].mbr_particion[j].id,0,10);
                    cout << "Aviso -> Se ha desmontado particion con id "<<_id<<endl;
                    flag_unmount=true;
                    break;
                }

                if(disco[i].mbr_particion[j].part_type=='e'){//si es extendida y nombre no es igual se busca en logicas
                    for (int k = 0; k < 24; ++k) {
                        if(strcmp(disco[i].ebr_logicas[k].id,_id)==0){
                            //se desmonta
                            disco[i].ebr_logicas[k].part_size  = 0;
                            disco[i].ebr_logicas[k].part_next = 0;
                            disco[i].ebr_logicas[k].part_start = 0;
                            memset(disco[i].ebr_logicas[k].part_fit,0,3);
                            memset(disco[i].ebr_logicas[k].part_name,0,16);
                            memset(disco[i].ebr_logicas[k].id,0,10);
                            cout << "Aviso -> Se ha desmontado particion con id "<<_id<<endl;
                            flag_unmount=true;
                            break;

                        }
                    }
                }
            }

        }
    }

    //para validar error
    if(flag_unmount==false){
        cout << "Error -> No se ha encontrado particion con id "<<_id<<endl;
    }
}

//para eliminar
void elimininarParticionMount(char _path[],char _name[]){
    //busco en disco
    for (int i = 0; i < 99; ++i) {
        if(strcmp(disco[i].path,_path)==0){
            //busco en las 4 basica
            for (int j = 0; j < 4; ++j) {
                if(strcmp(disco[i].mbr_particion[j].part_name,_name)==0){
                    disco[i].mbr_particion[j].part_type = '\000';
                    disco[i].mbr_particion[j].part_size = 0;
                    disco[i].mbr_particion[j].part_start = 0;
                    memset(disco[i].mbr_particion[j].part_fit,0,3);
                    memset(disco[i].mbr_particion[j].part_name,0,16);
                    memset(disco[i].mbr_particion[j].id,0,10);
                    break;
                }
                //busco en extendida
                if(disco[i].mbr_particion[j].part_type=='e'){
                //buscao en las logicas
                    for (int k = 0; k < 24; ++k) {
                        if(strcmp(disco[i].ebr_logicas[k].part_name,_name)==0){
                            disco[i].ebr_logicas[k].part_size  = 0;
                            disco[i].ebr_logicas[k].part_next = 0;
                            disco[i].ebr_logicas[k].part_start = 0;
                            memset(disco[i].ebr_logicas[k].part_fit,0,3);
                            memset(disco[i].ebr_logicas[k].part_name,0,16);
                            memset(disco[i].ebr_logicas[k].id,0,10);
                            break;
                        }
                    }
                }

            }

        }
    }
}

//para agregar
void agregarParticionMount(char _path[],char _name[],int _size,char _type, char _fit[],int _start,int _next){

    for (int i = 0; i < 99; ++i) {//primero buscar el path o sea disco
        if(strcmp(disco[i].path,_path)==0){
            //que tipo de particion es
            if(_type=='p'){
                //busca espacio para p
                for (int j = 0; j < 4; ++j) {
                    if(disco[i].mbr_particion[j].part_type=='\000'){
                        //se copia
                        disco[i].mbr_particion[j].part_type = _type;
                        disco[i].mbr_particion[j].part_status = '1';
                        disco[i].mbr_particion[j].part_size = _size;
                        disco[i].mbr_particion[j].part_start = _start;
                        strcpy(disco[i].mbr_particion[j].part_name,_name);
                        strcpy(disco[i].mbr_particion[j].part_fit,_fit);
                        break;
                    }
                }
            }else if(_type=='e'){
                //busca espacio para e
                for (int j = 0; j < 4; ++j) {
                    if(disco[i].mbr_particion[j].part_type=='\000'){
                        //se copia
                        disco[i].mbr_particion[j].part_type = _type;
                        disco[i].mbr_particion[j].part_status = '1';
                        disco[i].mbr_particion[j].part_size = _size;
                        disco[i].mbr_particion[j].part_start = _start;
                        strcpy(disco[i].mbr_particion[j].part_name,_name);
                        strcpy(disco[i].mbr_particion[j].part_fit,_fit);
                        break;
                    }
                }
            }else if(_type=='l'){
                //busco espacio para l
                for (int j = 0; j < 24; ++j) {
                    if(disco[i].ebr_logicas[j].part_size!=0){
                        disco[i].ebr_logicas[j].part_size = _size;
                        disco[i].ebr_logicas[j].part_start = _start;
                        disco[i].ebr_logicas[j].part_next = _next;
                        strcpy(disco[i].ebr_logicas[j].part_fit,_fit);
                        strcpy(disco[i].ebr_logicas[j].part_name,_name);
                        break;
                    }
                }
            }
        }
    }
}

//para validar existe disco
bool validacionPathMount(char path[]){
    FILE *file;
    if(file = fopen(path,"r")){
        fclose(file);
        return true;
    }
    fclose(file);
    return false;
}

void montajeMount(char _path[],char _name[]){
    //variables
    char tipoParticion = ' ';
    bool existe_particion = false;
    bool existe_disk=false;
    char id_generado[10]="";
    FILE*file;
    file = fopen(_path,"rb+");
    MBR *mbr = (MBR*) malloc(sizeof(MBR));
    EBR *ebread =(EBR*) malloc(sizeof(EBR));
    fseek(file,0,SEEK_SET);
    fread(mbr,sizeof (MBR),1,file);
    //para validar particion
    int cont_Part=0;
    int posSig=0;
    int posStart=0;

    //buscar en particiones primarias en el mbr escrito en disco
    for (cont_Part = 0; cont_Part < 4; ++cont_Part) {
        if(strcmp(mbr->mbr_particion[cont_Part].part_name,_name)==0){//se busca el nombre de la particion a montar
            if(mbr->mbr_particion[cont_Part].part_type=='p'){
                tipoParticion='p';
                existe_particion=true;
                break;
            }else if(mbr->mbr_particion[cont_Part].part_type=='e'){
                tipoParticion='e';
                existe_particion=true;
                break;
            }

        }
        //para buscar en las logicas
        if(mbr->mbr_particion[cont_Part].part_type=='e'){
            //se busca en el ebr escrito en el disco
            int pos = mbr->mbr_particion[cont_Part].part_start +sizeof(EBR)+1;
            fseek(file,pos,SEEK_SET);
            fread(ebread,sizeof(EBR),1,file);
            posSig = ebread->part_next;
            while(posSig!=-1){
                if(strcmp(ebread->part_name,_name)==0){
                    existe_particion=true;
                    posStart = ebread->part_start;
                    tipoParticion='l';
                    break;
                }

                fseek(file,posSig,SEEK_SET);
                fread(ebread,sizeof (EBR),1,file);
                posSig = ebread->part_next;
            }
        }
    }

    //para validar path
    int cont_disk=0;
    for (cont_disk = 0; cont_disk < 99; ++cont_disk) {
        if(strcmp(disco[cont_disk].path,_path)==0){
            existe_disk = true;
            break;
        }
    }

    if(existe_particion){//si existe nombre particion
        if(existe_disk){//ya se ha ingresado una particion del mismo disco
            //mbr->mbr_particion[cont_Part].part_type=='p'
            if(tipoParticion=='p'){//el path ya existe
                //busco el nombre en el disco
                for (int i = 0; i < 4; ++i) {
                    if(strcmp(disco[cont_disk].mbr_particion[i].part_name,_name)==0){
                        //solo se le genera el id
                        char letra = disco[cont_disk].letra;
                        id_generado[0]='v';
                        id_generado[1]='d';
                        id_generado[2]=letra;
                        //into to string
                        disco[cont_disk].numeral++;
                        string s_num = to_string(disco[cont_disk].numeral);
                        char const *num_char = s_num.c_str();
                        strncat(id_generado,num_char,1);
                        strcpy(disco[cont_disk].mbr_particion[cont_Part].id,id_generado);
                        memset(id_generado,0,10);
                        break;

                    }
                }
                fclose(file);
                /*char letra = disco[cont_disk].letra;
                //se copia
                disco[cont_disk].mbr_particion[cont_Part].part_status = mbr->mbr_particion[cont_Part].part_status;
                disco[cont_disk].mbr_particion[cont_Part].part_type = mbr->mbr_particion[cont_Part].part_type;
                disco[cont_disk].mbr_particion[cont_Part].part_size = mbr->mbr_particion[cont_Part].part_size;
                disco[cont_disk].mbr_particion[cont_Part].part_start = mbr->mbr_particion[cont_Part].part_start;
                strcpy(disco[cont_disk].mbr_particion[cont_Part].part_name,mbr->mbr_particion[cont_Part].part_name);
                strcpy(disco[cont_disk].mbr_particion[cont_Part].part_fit,mbr->mbr_particion[cont_Part].part_fit);
                //generando id
                id_generado[0]='V';
                id_generado[1]='D';
                id_generado[2]=letra;
                //into to string
                disco[cont_disk].numeral++;
                string s_num = to_string(disco[cont_disk].numeral);
                char const *num_char = s_num.c_str();
                strncat(id_generado,num_char,1);
                strcpy(disco[cont_disk].mbr_particion[cont_Part].id,id_generado);
                memset(id_generado,0,10);
                cout << "Aviso -> Particion primaria ha sido montada "<<_name<<endl;*/

            }else if(tipoParticion=='e'){

                char letra = disco[cont_disk].letra;
                //se copia
                disco[cont_disk].mbr_particion[cont_Part].part_status = mbr->mbr_particion[cont_Part].part_status;
                disco[cont_disk].mbr_particion[cont_Part].part_type = mbr->mbr_particion[cont_Part].part_type;
                disco[cont_disk].mbr_particion[cont_Part].part_size = mbr->mbr_particion[cont_Part].part_size;
                disco[cont_disk].mbr_particion[cont_Part].part_start = mbr->mbr_particion[cont_Part].part_start;
                strcpy(disco[cont_disk].mbr_particion[cont_Part].part_name,mbr->mbr_particion[cont_Part].part_name);
                strcpy(disco[cont_disk].mbr_particion[cont_Part].part_fit,mbr->mbr_particion[cont_Part].part_fit);
                //generando id
                id_generado[0]='v';
                id_generado[1]='d';
                id_generado[2]=letra;
                //into to string
                disco[cont_disk].numeral++;
                string s_num = to_string(disco[cont_disk].numeral);
                char const *num_char = s_num.c_str();
                strncat(id_generado,num_char,1);
                strcpy(disco[cont_disk].mbr_particion[cont_Part].id,id_generado);
                memset(id_generado,0,10);

                EBR *ebr =(EBR*) malloc(sizeof(EBR));
                //se guardan las logicas
                fseek(file,mbr->mbr_particion[cont_Part].part_start+sizeof (EBR)+1,SEEK_SET);
                fread(ebr,sizeof (EBR),1,file);
                int pos=0;
                int cont_logicas=0;

                while(ebr->part_next!=-1){
                    pos = ebr->part_next;
                    //guardo ebr
                    disco[cont_disk].ebr_logicas[cont_logicas].part_next = ebr->part_next;
                    disco[cont_disk].ebr_logicas[cont_logicas].part_start =ebr->part_start;
                    disco[cont_disk].ebr_logicas[cont_logicas].part_size  = ebr->part_size;
                    strcpy(disco[cont_disk].ebr_logicas[cont_logicas].part_fit,ebr->part_fit);
                    strcpy(disco[cont_disk].ebr_logicas[cont_logicas].part_name,ebr->part_name);
                    fseek(file,pos,SEEK_SET);
                    fread(ebr,sizeof (EBR),1,file);
                    cont_logicas++;
                }
                cout << "Aviso -> Particiona extendida ha sido montada "<<_name<<endl;
                //para agregar el ultimo
                /*disco[cont_disk].ebr_logicas[cont_logicas].part_next = ebr->part_next;
                disco[cont_disk].ebr_logicas[cont_logicas].part_start =ebr->part_start;
                disco[cont_disk].ebr_logicas[cont_logicas].part_size  = ebr->part_size;
                strcpy(disco[cont_disk].ebr_logicas[cont_logicas].part_fit,ebr->part_fit);
                strcpy(disco[cont_disk].ebr_logicas[cont_logicas].part_name,ebr->part_name);*/
            }else if(tipoParticion=='l'){

                //busca la particion que es extendida
                char letra = disco[cont_disk].letra;
                for (int i = 0; i < 4; ++i) {
                    if(disco[cont_disk].mbr_particion[i].part_type=='e'){
                        for (int j = 0; j < 24; ++j) {
                            if(strcmp(disco[cont_disk].ebr_logicas[j].part_name,_name)==0){
                                //generar id
                                id_generado[0]='v';
                                id_generado[1]='d';
                                id_generado[2]=letra;
                                //into to string
                                disco[cont_disk].numeral++;
                                string s_num = to_string(disco[cont_disk].numeral);
                                char const *num_char = s_num.c_str();
                                strncat(id_generado,num_char,1);
                                strcpy(disco[cont_disk].ebr_logicas[j].id,id_generado);
                                memset(id_generado,0,10);
                                break;
                            }
                        }
                    }
                }
                fclose(file);
                /*EBR* ebrinsert = (EBR*) malloc(sizeof (EBR));
                fseek(file,posStart,SEEK_SET);
                fread(ebrinsert,sizeof (EBR),1,file);
                //busco espacio en disco array para almacenar
                for (int i = 0; i < 24; ++i) {
                    if(disco[cont_disk].ebr_logicas[i].part_size==0){
                        //se almacena
                        char letra = disco[cont_disk].letra;
                        disco[cont_disk].ebr_logicas[i].part_size = ebrinsert->part_size;
                        disco[cont_disk].ebr_logicas[i].part_next = ebrinsert->part_next;
                        disco[cont_disk].ebr_logicas[i].part_start = ebrinsert->part_start;
                        strcpy(disco[cont_disk].ebr_logicas[i].part_fit,ebrinsert->part_fit);
                        strcpy(disco[cont_disk].ebr_logicas[i].part_name,ebrinsert->part_name);
                        //generando id
                        id_generado[0]='V';
                        id_generado[1]='D';
                        id_generado[2]=letra;
                        //into to string
                        disco[cont_disk].numeral++;
                        string s_num = to_string(disco[cont_disk].numeral);
                        char const *num_char = s_num.c_str();
                        strncat(id_generado,num_char,1);
                        strcpy(disco[cont_disk].ebr_logicas[i].id,id_generado);
                        memset(id_generado,0,10);
                        break;
                    }
                }*/
            }

        }else{//disco es nuevo, primera vez que se ingresa en el array

           if(tipoParticion=='p'){
               //se copia el disco
               disco[contador_disco].letra = abdecedario[contador_abc];
               disco[contador_disco].mbr_disk_signature = mbr->mbr_disk_signature;
               disco[contador_disco].mbr_tamano = mbr->mbr_tamano;
               disco[contador_disco].mbr_fecha_creacion  = mbr->mbr_fecha_creacion;
               strcpy(disco[contador_disco].path,_path);

               //se copian las particion basicas
               for (int i = 0; i < 4; ++i) {
                   if(mbr->mbr_particion[i].part_size!=0){// solo se agregan las que tengan tamaño
                       if(strcmp(mbr->mbr_particion[i].part_name,_name)==0){//se agrega id a la basica que se monta
                           disco[contador_disco].mbr_particion[i].part_start = mbr->mbr_particion[i].part_start;
                           disco[contador_disco].mbr_particion[i].part_size = mbr->mbr_particion[i].part_size;
                           disco[contador_disco].mbr_particion[i].part_type = mbr->mbr_particion[i].part_type;
                           disco[contador_disco].mbr_particion[i].part_status = mbr->mbr_particion[i].part_status;
                           strcpy(disco[contador_disco].mbr_particion[i].part_fit,mbr->mbr_particion[i].part_fit);
                           strcpy(disco[contador_disco].mbr_particion[i].part_name,mbr->mbr_particion[i].part_name);
                           //generando id
                           id_generado[0]='v';
                           id_generado[1]='d';
                           id_generado[2]=abdecedario[contador_abc];
                           disco[contador_disco].numeral++;
                           string s_num = to_string(disco[contador_disco].numeral);
                           char const *num_char = s_num.c_str();
                           strncat(id_generado,num_char,1);
                           strcpy(disco[contador_disco].mbr_particion[i].id,id_generado);
                           memset(id_generado,0,10);

                           cout << "Aviso -> Particiona primaria ha sido montada "<<_name<<endl;

                       }else{//se copian las demas
                           if(mbr->mbr_particion[i].part_type=='e'){//para buscar las logicas
                               disco[contador_disco].mbr_particion[i].part_start = mbr->mbr_particion[i].part_start;
                               disco[contador_disco].mbr_particion[i].part_size = mbr->mbr_particion[i].part_size;
                               disco[contador_disco].mbr_particion[i].part_type = mbr->mbr_particion[i].part_type;
                               disco[contador_disco].mbr_particion[i].part_status = mbr->mbr_particion[i].part_status;
                               strcpy(disco[contador_disco].mbr_particion[i].part_fit,mbr->mbr_particion[i].part_fit);
                               strcpy(disco[contador_disco].mbr_particion[i].part_name,mbr->mbr_particion[i].part_name);

                               //valido si existe logicas
                               EBR *ebr_log = (EBR*) malloc(sizeof (EBR));
                               fseek(file,mbr->mbr_particion[i].part_start+sizeof (EBR)+1,SEEK_SET);
                               fread(ebr_log,sizeof (EBR),1,file);
                               int next = ebr_log->part_next;
                               int incre=0;
                               if(ebr_log->part_next!=0){// solo si existe ebr escritas
                                    while(next!=-1){
                                        disco[contador_disco].ebr_logicas[incre].part_size = ebr_log->part_size;
                                        disco[contador_disco].ebr_logicas[incre].part_next = ebr_log->part_next;
                                        disco[contador_disco].ebr_logicas[incre].part_start = ebr_log->part_start;
                                        strcpy(disco[contador_disco].ebr_logicas[incre].part_fit,ebr_log->part_fit);
                                        strcpy(disco[contador_disco].ebr_logicas[incre].part_name,ebr_log->part_name);
                                        fseek(file,next,SEEK_SET);
                                        fread(ebr_log,sizeof(EBR),1,file);
                                        next = ebr_log->part_next;
                                        incre++;
                                    }
                               }

                           }else{// sigue siendo primaria
                               disco[contador_disco].mbr_particion[i].part_start = mbr->mbr_particion[i].part_start;
                               disco[contador_disco].mbr_particion[i].part_size = mbr->mbr_particion[i].part_size;
                               disco[contador_disco].mbr_particion[i].part_type = mbr->mbr_particion[i].part_type;
                               disco[contador_disco].mbr_particion[i].part_status = mbr->mbr_particion[i].part_status;
                               strcpy(disco[contador_disco].mbr_particion[cont_Part].part_fit,mbr->mbr_particion[i].part_fit);
                               strcpy(disco[contador_disco].mbr_particion->part_name,mbr->mbr_particion[i].part_name);
                           }

                       }
                   }
               }

               contador_abc++;
               contador_disco++;
               fclose(file);
           }else if(tipoParticion=='e'){
               char letra = disco[cont_disk].letra;
               //se copia
               disco[contador_disco].mbr_particion[cont_Part].part_status = mbr->mbr_particion[cont_Part].part_status;
               disco[contador_disco].mbr_particion[cont_Part].part_type = mbr->mbr_particion[cont_Part].part_type;
               disco[contador_disco].mbr_particion[cont_Part].part_size = mbr->mbr_particion[cont_Part].part_size;
               disco[contador_disco].mbr_particion[cont_Part].part_start = mbr->mbr_particion[cont_Part].part_start;
               strcpy(disco[contador_disco].mbr_particion[cont_Part].part_name,mbr->mbr_particion[cont_Part].part_name);
               strcpy(disco[contador_disco].mbr_particion[cont_Part].part_fit,mbr->mbr_particion[cont_Part].part_fit);
               //generando id
               id_generado[0]='v';
               id_generado[1]='d';
               id_generado[2]=letra;
               //into to string
               disco[contador_disco].numeral++;
               string s_num = to_string(disco[contador_disco].numeral);
               char const *num_char = s_num.c_str();
               strncat(id_generado,num_char,1);
               strcpy(disco[contador_disco].mbr_particion[cont_Part].id,id_generado);
               memset(id_generado,0,10);

               EBR *ebr =(EBR*) malloc(sizeof(EBR));
               //se guardan las logicas
               fseek(file,mbr->mbr_particion[cont_Part].part_start+sizeof (EBR)+1,SEEK_SET);
               fread(ebr,sizeof (EBR),1,file);
               int pos=0;
               int cont_logicas=0;
               while(ebr->part_next!=-1){
                   pos = ebr->part_next;
                   //guardo ebr
                   disco[contador_disco].ebr_logicas[cont_logicas].part_next = ebr->part_next;
                   disco[contador_disco].ebr_logicas[cont_logicas].part_start =ebr->part_start;
                   disco[contador_disco].ebr_logicas[cont_logicas].part_size  = ebr->part_size;
                   strcpy(disco[contador_disco].ebr_logicas[cont_logicas].part_fit,ebr->part_fit);
                   strcpy(disco[contador_disco].ebr_logicas[cont_logicas].part_name,ebr->part_name);
                   fseek(file,pos,SEEK_SET);
                   fread(ebr,sizeof (EBR),1,file);
                   cont_logicas++;
               }
               contador_abc++;
               contador_disco++;
               cout << "Aviso -> Particiona extendida ha sido montada "<<_name<<endl;
           }else if(tipoParticion=='l'){
               // se copia disco

               //se copia el disco
               disco[contador_disco].letra = abdecedario[contador_abc];
               disco[contador_disco].mbr_disk_signature = mbr->mbr_disk_signature;
               disco[contador_disco].mbr_tamano = mbr->mbr_tamano;
               disco[contador_disco].mbr_fecha_creacion  = mbr->mbr_fecha_creacion;
               strcpy(disco[contador_disco].path,_path);

               //las particiones primarias basica
               //se copian las particion basicas
               for (int i = 0; i < 4; ++i) {
                   if(mbr->mbr_particion[i].part_size!=0){// solo se agregan las que tengan tamaño
                       if(mbr->mbr_particion[i].part_type=='e'){//se agrega id a la basica que se monta
                           //se copia la particion extendida
                           disco[contador_disco].mbr_particion[i].part_start = mbr->mbr_particion[i].part_start;
                           disco[contador_disco].mbr_particion[i].part_size = mbr->mbr_particion[i].part_size;
                           disco[contador_disco].mbr_particion[i].part_type = mbr->mbr_particion[i].part_type;
                           disco[contador_disco].mbr_particion[i].part_status = mbr->mbr_particion[i].part_status;
                           strcpy(disco[contador_disco].mbr_particion[i].part_fit,mbr->mbr_particion[i].part_fit);
                           strcpy(disco[contador_disco].mbr_particion[i].part_name,mbr->mbr_particion[i].part_name);

                           //valido si existe logicas
                           EBR *ebr_log = (EBR*) malloc(sizeof (EBR));
                           fseek(file,mbr->mbr_particion[i].part_start+sizeof (EBR)+1,SEEK_SET);
                           fread(ebr_log,sizeof (EBR),1,file);
                           int next = ebr_log->part_next;
                           int incre=0;
                           if(ebr_log->part_next!=0){// solo si existe ebr escritas
                               while(next!=-1){
                                   //si es el ebr que estoy buscando para montar
                                   if(strcmp(ebr_log->part_name,_name)==0){
                                       disco[contador_disco].ebr_logicas[incre].part_size = ebr_log->part_size;
                                       disco[contador_disco].ebr_logicas[incre].part_next = ebr_log->part_next;
                                       disco[contador_disco].ebr_logicas[incre].part_start = ebr_log->part_start;
                                       strcpy(disco[contador_disco].ebr_logicas[incre].part_fit,ebr_log->part_fit);
                                       strcpy(disco[contador_disco].ebr_logicas[incre].part_name,ebr_log->part_name);

                                       //generar id
                                       id_generado[0]='v';
                                       id_generado[1]='d';
                                       id_generado[2]=abdecedario[contador_abc];
                                       disco[contador_disco].numeral++;
                                       string s_num = to_string(disco[contador_disco].numeral);
                                       char const *num_char = s_num.c_str();
                                       strncat(id_generado,num_char,1);
                                       strcpy(disco[contador_disco].ebr_logicas[incre].id,id_generado);
                                       memset(id_generado,0,10);

                                       cout << "Aviso -> Particiona logica ha sido montada "<<_name<<endl;
                                       //leer siguiente
                                       fseek(file,ebr_log->part_next,SEEK_SET);
                                       fread(ebr_log,sizeof (EBR),1,file);
                                       next = ebr_log->part_next;
                                       incre++;
                                   }else{
                                       disco[contador_disco].ebr_logicas[incre].part_size = ebr_log->part_size;
                                       disco[contador_disco].ebr_logicas[incre].part_next = ebr_log->part_next;
                                       disco[contador_disco].ebr_logicas[incre].part_start = ebr_log->part_start;
                                       strcpy(disco[contador_disco].ebr_logicas[incre].part_fit,ebr_log->part_fit);
                                       strcpy(disco[contador_disco].ebr_logicas[incre].part_name,ebr_log->part_name);
                                       fseek(file,next,SEEK_SET);
                                       fread(ebr_log,sizeof(EBR),1,file);
                                       next = ebr_log->part_next;
                                       incre++;
                                   }

                               }
                           }

                       }else{//se copian las demas
                           // sigue siendo primaria
                               disco[contador_disco].mbr_particion[i].part_start = mbr->mbr_particion[i].part_start;
                               disco[contador_disco].mbr_particion[i].part_size = mbr->mbr_particion[i].part_size;
                               disco[contador_disco].mbr_particion[i].part_type = mbr->mbr_particion[i].part_type;
                               disco[contador_disco].mbr_particion[i].part_status = mbr->mbr_particion[i].part_status;
                               strcpy(disco[contador_disco].mbr_particion[i].part_fit,mbr->mbr_particion[i].part_fit);
                               strcpy(disco[contador_disco].mbr_particion[i].part_name,mbr->mbr_particion[i].part_name);

                       }
                   }
               }
               contador_disco++;
               contador_abc++;
               fclose(file);
               //se buscan si hay ebrs
               //poner la extendidad para reconocer la logica
             /*  EBR* ebrinsert = (EBR*) malloc(sizeof (EBR));
               fseek(file,posStart,SEEK_SET);
               fread(ebrinsert,sizeof (EBR),1,file);*/
               //busco espacio en disco array para almacenar
               /*for (int i = 0; i < 24; ++i) {
                   if(disco[contador_disco].ebr_logicas[i].part_size==0){
                       //se almacena
                       char letra = disco[contador_disco].letra;
                       disco[contador_disco].ebr_logicas[i].part_size = ebrinsert->part_size;
                       disco[contador_disco].ebr_logicas[i].part_next = ebrinsert->part_next;
                       disco[contador_disco].ebr_logicas[i].part_start = ebrinsert->part_start;
                       strcpy(disco[contador_disco].ebr_logicas[i].part_fit,ebrinsert->part_fit);
                       strcpy(disco[contador_disco].ebr_logicas[i].part_name,ebrinsert->part_name);
                       //generando id
                       id_generado[0]='V';
                       id_generado[1]='D';
                       id_generado[2]=letra;
                       //into to string
                       disco[contador_disco].numeral++;
                       string s_num = to_string(disco[contador_disco].numeral);
                       char const *num_char = s_num.c_str();
                       strncat(id_generado,num_char,1);
                       strcpy(disco[contador_disco].ebr_logicas[i].id,id_generado);
                       memset(id_generado,0,10);
                       break;
                   }
               }*/
           }


        }
    }else{
        cout << "Error -> No existe particion para ser montada "<<_name<<endl;
    }


}

void showMount(){
    cout <<"╔══════════LISTA DE PARTICIONES MONTADAS════════════╗"<<endl;
    cout <<"╠═════════════════╦════════════╦════════════════════╣"<<endl;
    cout <<"║ Nombre          ║     ID     ║  Tipo              ║"<<endl;
    cout <<"╚═════════════════╩════════════╩════════════════════╝"<<endl;
    for (int i = 0; i < 99; ++i) {
        if(disco[i].letra!='\000'){//cambios
            for (int j = 0; j < 4; ++j) {
                if(disco[i].mbr_particion[j].part_type=='p'){//es primaria
                    if(disco[i].mbr_particion[j].part_status=='1' && disco[i].mbr_particion[j].id[0]!='\000'){
                        cout << "║ "<<disco[i].mbr_particion[j].part_name<<"  ║  "<<disco[i].mbr_particion[j].id<<"║  "<<disco[i].mbr_particion[j].part_type<<"  ║"<<endl;
                    }
                }else if(disco[i].mbr_particion[j].part_type=='e'){
                    if(disco[i].mbr_particion[j].part_status=='1'){
                        for (int k = 0; k < 24; ++k) {
                            if (disco[i].ebr_logicas[k].part_size!=0 && disco[i].ebr_logicas[k].id[0]!='\000'){
                                cout << "║ "<<disco[i].ebr_logicas[k].part_name<<"  ║  "<<disco[i].ebr_logicas[k].id<<"║  "<<"l"<<"  ║"<<endl;
                            }
                        }
                    }
                }
            }
        }
    }
    cout <<""<<endl;
    cout <<""<<endl;
}

void analisisMount(char comando[]){
    int contador=0;
    char lineacomando[100]="";

    char valor_path[100]="";
    char valor_name[100]="";

    bool flag_path=false;
    bool flag_name=false;

    while(comando[contador]!=NULL){
        if(comando[contador]==' '|| comando[contador]=='\n'){
            contador++;
            memset(lineacomando,0,100);
        }else if(comando[contador]=='>'){
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

        //validacion de argumentos de mount
        if(strcmp(lineacomando,"mount")==0){
            cout << "Encontro: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            contador++;
        }else if(strcmp(lineacomando,"$path=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            flag_path=true;
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
        }else if(strcmp(lineacomando,"$name=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            flag_name=true;
            while(comando[contador]!=NULL){
                if(comando[contador]==' ' || comando[contador]=='\n'){
                    contador++;
                    break;
                }else{
                    char aux[1]="";
                    aux[0] = comando[contador];
                    strncat(valor_name,aux,1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_name<<endl;
        }
    }


    if(flag_name && flag_path){//es para montar
        bool flag_disk = validacionPathMount(valor_path);
        if(flag_disk){//existe disco
            montajeMount(valor_path,valor_name);
        }else{
            cout << "Error -> No existe el disco que se intenta montar "<<valor_path<<endl;
        }
    }else{//solo para listar

        showMount();
    }

}