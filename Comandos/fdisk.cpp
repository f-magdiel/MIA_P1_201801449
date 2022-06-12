#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <fstream>
#include "mkdisk.h"
#include "../Estructuras/MBR.h"
#include "../Estructuras/EBR.h"
#include "../Comandos/mount.h"
using namespace std;

bool validacionDisco(char path[]){
    FILE *file;
    if(file = fopen(path,"r")){
        fclose(file);
        return true;
    }
    fclose(file);
    return false;

}
//contador de particiones primarias
int contadorPrimaria(MBR *mbr){
    int contadorPrimaria =0;
    for (int i = 0; i < 4; ++i) {
        if('p'==mbr->mbr_particion[i].part_type){
            contadorPrimaria++;
        }
    }
    return contadorPrimaria;

}

//contador de particiones extendidas
int contadorExtendida(MBR *mbr){
    int contadorExtendida=0;
    for (int i = 0; i < 4; ++i) {
        if('e'==mbr->mbr_particion[i].part_type){
            contadorExtendida++;
        }
    }
    return contadorExtendida;
}

int contadorLogicas(MBR*mbr,EBR*ebr,FILE*file){
    int contadorEBR=0;
    int next=0;
    for (int i = 0; i < 4; ++i) {
        if(mbr->mbr_particion[i].part_type=='e'){
            fseek(file,mbr->mbr_particion[i].part_start+sizeof (EBR)+1,SEEK_SET);
            fread(ebr,sizeof (EBR),1,file);
            next = ebr->part_next;
            while(next!=-1){
                fseek(file,next,SEEK_SET);
                fread(ebr,sizeof (EBR),1,file);
                next = ebr->part_next;
                contadorEBR++;
            }
            contadorEBR++;
            break;
        }
    }
    return contadorEBR;
}
//validacion nombre de particioens primarias y extendidas
bool validacionNombrePE(MBR *mbr,char name[]){
    for (int i = 0; i < 4; ++i) {
        if(strcmp(mbr->mbr_particion[i].part_name,name)==0){
            return true;
        }
    }
    return false;
}

//validacion nombres logicas
bool validacionNombreLogica(MBR*mbr,EBR*ebr,FILE*file,char _name[]){
    bool flagName = false;
    int next=0;
    for (int i = 0; i < 4; ++i) {
        if(mbr->mbr_particion[i].part_type=='e'){
            fseek(file,mbr->mbr_particion[i].part_start+sizeof(EBR)+1,SEEK_SET);
            fread(ebr,sizeof (EBR),1,file);
            next = ebr->part_next;
            while(next!=-1){
                if(strcmp(ebr->part_name,_name)==0){
                    flagName=true;
                    break;
                }
                fseek(file,next,SEEK_SET);
                fread(ebr,sizeof (EBR),1,file);
                next=ebr->part_next;
            }
            if(strcmp(ebr->part_name,_name)==0){
                flagName = true;
            }
            break;
        }
    }
    return flagName;
}
//para crear las particiones
//                   size, unit, path, type, fit, name
void crearParticion(char _size[],char _unit,char _path[],char _type,char _fit[],char _name[]){

    FILE *file;
    MBR *mbr = (MBR*) malloc(sizeof (MBR));

    file = fopen(_path,"rb+");
    fseek(file,0,SEEK_SET);
    fread(mbr,sizeof (MBR),1,file);//se lee el mbr
    //contadores
    int contador_P = contadorPrimaria(mbr);
    int contador_E = contadorExtendida(mbr);

    //validacion el tipo de particon

    if(_type=='p'){//para primaria
        if(contador_P<4){
            bool flag_name = validacionNombrePE(mbr,_name);
            if(!flag_name){//no existe nombre repetido
                for (int i = 0; i < 4; ++i) {//busca que particion está disponible para asignar ya que si hay una disponible
                    if(mbr->mbr_particion[i].part_type=='-'){//esta disponible
                        int size_total = mbr->mbr_tamano;
                        int size_usado = mbr->mbr_particion[0].part_size+mbr->mbr_particion[1].part_size+mbr->mbr_particion[2].part_size+mbr->mbr_particion[3].part_size;
                        int size_disponible = size_total-size_usado-sizeof(MBR);
                        string tamano = charToString(_size);
                        int size_Particion=0;
                        //para el tamaño
                        if(_unit=='b'){
                            size_Particion = stoi(tamano);
                        }else if(_unit=='k'){
                            size_Particion = stoi(tamano)*1024;
                        }else if(_unit=='m'){
                            size_Particion = stoi(tamano)*1024*1024;
                        }


                        if(size_disponible>size_Particion){// existe espacio en disco para esa particion
                            mbr->mbr_particion[i].part_status = '1';
                            mbr->mbr_particion[i].part_type = 'p';
                            mbr->mbr_particion[i].part_start = size_usado+sizeof(MBR)+1;
                            mbr->mbr_particion[i].part_size = size_Particion;
                            strcpy(mbr->mbr_particion[i].part_fit,_fit);
                            strcpy(mbr->mbr_particion[i].part_name,_name);

                            //para agregar en el mount
                            agregarParticionMount(_path,_name,size_Particion,'p',_fit,mbr->mbr_particion[i].part_start,0);
                            //se actualiza el mbr
                            fseek(file,0,SEEK_SET);
                            fwrite(mbr,sizeof(MBR),1,file);

                            //se escribe la particion
                            fseek(file,mbr->mbr_particion[i].part_start,SEEK_SET);
                            fwrite(&mbr->mbr_particion[i],sizeof(mbr->mbr_particion[i]),1,file);
                            fclose(file);
                            cout << "Particion"<<i+1<<" primaria creada exitosamente"<<endl;
                            break;
                        }else{
                            cout << "Error -> Espacio insuficiente en disco para particion primaria"<<endl;
                            break;
                        }

                    }

                }
            }else{
                cout << "Error -> Nombre de particion se repite"<<endl;
            }
        }else{
            cout <<"Error -> Se llego a la capacidad maxima de particiones primarias"<<endl;
        }
    }else if(_type=='e'){//para extendidad
        if(contador_E<1){//solo debe existir una extendidad
            bool flag_name = validacionNombrePE(mbr,_name);
            if(!flag_name){//si no existe nombre
                for (int i = 0; i < 4; ++i) {
                    if(mbr->mbr_particion[i].part_type=='-'){
                        int size_total = mbr->mbr_tamano;
                        int size_usado = mbr->mbr_particion[0].part_size+mbr->mbr_particion[1].part_size+mbr->mbr_particion[2].part_size+mbr->mbr_particion[3].part_size;
                        int size_disponible = size_total-size_usado-sizeof(MBR);
                        string tamano = charToString(_size);
                        int size_Particion=0;
                        //para el tamaño
                        if(_unit=='b'){
                            size_Particion = stoi(tamano);
                        }else if(_unit=='k'){
                            size_Particion = stoi(tamano)*1024;
                        }else if(_unit=='m'){
                            size_Particion = stoi(tamano)*1024*1024;
                        }
                        if(size_disponible>size_Particion){//hay espacio disponible
                            mbr->mbr_particion[i].part_status = '1';
                            mbr->mbr_particion[i].part_type = 'e';
                            mbr->mbr_particion[i].part_start = size_usado+sizeof(MBR)+1;
                            mbr->mbr_particion[i].part_size = size_Particion;
                            strcpy(mbr->mbr_particion[i].part_fit,_fit);
                            strcpy(mbr->mbr_particion[i].part_name,_name);

                            agregarParticionMount(_path,_name,size_Particion,'p',_fit,mbr->mbr_particion[i].part_start,0);
                            //ebr se setea
                            EBR *ebr = (EBR*) malloc(sizeof (EBR));
                            ebr->part_start = 0;
                            ebr->part_size = 0;
                            ebr->part_next = -1;
                            memset(ebr->part_name,0,16);
                            memset(ebr->part_fit,0,3);

                            //se actualiza el mbr
                            fseek(file,0,SEEK_SET);
                            fwrite(mbr,sizeof(MBR),1,file);

                            //se escribe la particion
                            fseek(file,mbr->mbr_particion[i].part_start,SEEK_SET);
                            fwrite(&mbr->mbr_particion[i],sizeof(mbr->mbr_particion[i]),1,file);

                            //se escribe el ebr
                            fseek(file,mbr->mbr_particion[i].part_start+sizeof (EBR)+1,SEEK_SET);
                            fwrite(ebr,sizeof(EBR),1,file);

                            fclose(file);
                            cout << "Particion"<<i+1<<" extendida creada exitosamente"<<endl;
                            break;

                        }else{
                            cout << "Error -> Espacio insuficiente en disco para particion primaria"<<endl;
                            break;
                        }
                    }
                }
            }else{
                cout << "Error -> Nombre de particion se repite"<<endl;
            }
        }else{
            cout << "Error -> Se llego a la capacidad maxima de particion extendidad"<<endl;
        }
    }else if(_type=='l'){//para logica
        EBR *ebr = (EBR*) malloc(sizeof (EBR));
        int contadorLog = contadorLogicas(mbr,ebr,file);

        if(contadorLog<=24){
            bool repeatNameLogica = validacionNombreLogica(mbr,ebr,file,_name);
            //se validara si existe nombre repetidos y se creara mas ebr
            if(!repeatNameLogica){// no hay nada repetido
                for (int i = 0; i < 4; ++i) {
                    if(mbr->mbr_particion[i].part_type=='e'){// se busca la particion extendida
                        fseek(file,mbr->mbr_particion[i].part_start+sizeof(EBR)+1,SEEK_SET);
                        fread(ebr,sizeof (EBR),1,file);

                        if(ebr->part_next==-1){//primera asigacion
                            //conversiones
                            string tamano = charToString(_size);
                            int size =0;
                            if(_unit=='b'){
                                size = stoi(tamano);
                            }else if(_unit=='k'){
                                size = stoi(tamano)*1024;
                            }else if(_unit=='m'){
                                size = stoi(tamano)*1024*1024;
                            }

                            ebr->part_start = mbr->mbr_particion[i].part_start+sizeof (EBR)+1;
                            ebr->part_size = size;
                            strcpy(ebr->part_fit,_fit);
                            strcpy(ebr->part_name,_name);
                            ebr->part_next = ebr->part_start+ebr->part_size+1;

                            agregarParticionMount(_path,_name,size,'l',_fit,ebr->part_start,ebr->part_next);

                            //actualizo el ebr
                            fseek(file,ebr->part_start,SEEK_SET);
                            fwrite(ebr,sizeof (EBR),1,file);

                            //se crea un nuevo ebr para su uso posterior
                            fseek(file,ebr->part_next,SEEK_SET);
                            EBR* ebrnew = (EBR*) malloc(sizeof (EBR));
                            ebrnew->part_start = 0;
                            ebrnew->part_size = 0;
                            ebrnew->part_next = -1;
                            memset(ebr->part_fit,0,3);
                            memset(ebr->part_name,0,16);

                            fwrite(ebrnew,sizeof (EBR),1,file);
                            fclose(file);
                            cout << " Aviso -> Particion logica creada y agregada correctamente"<<endl;
                        }else{// si no es primero
                            int pos = ebr->part_next;
                            int ant=0;

                            while(pos!=-1){
                                ant = pos;
                                fseek(file,pos,SEEK_SET);
                                fread(ebr,sizeof (EBR),1,file);
                                pos = ebr->part_next;
                            }

                            if(contadorLog<=23){
                                string tamano = charToString(_size);
                                int size =0;
                                if(_unit=='b'){
                                    size = stoi(tamano);
                                }else if(_unit=='k'){
                                    size = stoi(tamano)*1024;
                                }else if(_unit=='m'){
                                    size = stoi(tamano)*1024*1024;
                                }
                                ebr->part_start = ant;
                                ebr->part_size = size;
                                ebr->part_next = ebr->part_size+ebr->part_start+1;
                                strcpy(ebr->part_fit,_fit);
                                strcpy(ebr->part_name,_name);

                                agregarParticionMount(_path,_name,size,'l',_fit,ebr->part_start,ebr->part_next);

                                fseek(file,ebr->part_start,SEEK_SET);
                                fwrite(ebr,sizeof (EBR),1,file);
                                cout << " Aviso -> Particion logica creada y agregada correctamente"<<endl;
                            }else{
                                if(contadorLog==24 && ebr->part_next==-1){
                                    string tamano = charToString(_size);
                                    int size =0;
                                    if(_unit=='b'){
                                        size = stoi(tamano);
                                    }else if(_unit=='k'){
                                        size = stoi(tamano)*1024;
                                    }else if(_unit=='m'){
                                        size = stoi(tamano)*1024*1024;
                                    }
                                    ebr->part_start = ant;
                                    ebr->part_size = size;
                                    ebr->part_next = -1;
                                    strcpy(ebr->part_fit,_fit);
                                    strcpy(ebr->part_name,_name);

                                    agregarParticionMount(_path,_name,size,'l',_fit,ebr->part_start,ebr->part_next);

                                    fseek(file,ebr->part_start,SEEK_SET);
                                    fwrite(ebr,sizeof (EBR),1,file);
                                    cout << " Aviso -> Particion logica creada y agregada correctamente"<<endl;
                                }else{
                                    cout << "Error -> Particiones logicas llego al máximo"<<endl;
                                }
                            }

                            if(contadorLog<=23){
                                EBR* ebrnew = (EBR*) malloc(sizeof (EBR));
                                ebrnew->part_start = 0;
                                ebrnew->part_size = 0;
                                ebrnew->part_next = -1;
                                memset(ebrnew->part_fit,0,3);
                                memset(ebrnew->part_name,0,16);
                                fseek(file,ebr->part_next,SEEK_SET);
                                fwrite(ebrnew,sizeof (EBR),1,file);
                            }
                            fclose(file);
                        }
                        break;
                    }
                }
            }
        }
    }

}

bool validacionFit(char fit[]){

    if(fit[0]=='b' && fit[1]=='f'){
        return true;
    }else if(fit[0]=='w' && fit[1]=='f') {
        return true;
    }else if(fit[0]=='f' && fit[1]=='f'){
        return true;
    }
    return false;
}
bool validacionSizeParticion(char tamano[]){
    string _size = charToString(tamano);
    int size = stoi(_size);
    if(size>0){
        return true;
    }
    return false;
}

//cambio de path
string cambioPathCopia(char path[]){
    int contadorDia=0;
    int contadorFind=0;
    int contador=0;
    char nuevoPath[100]="";
    char nombre[7]="Copia_";

    while(path[contador]!=NULL){
        if(path[contador]=='/'){
            contadorDia++;
        }
        contador++;
    }
    contador=0;
    while(path[contador]!=NULL){
        if(path[contador]=='/'){
            contadorFind++;
            char aux[1]="";
            aux[0]=path[contador];
            strncat(nuevoPath,aux,1);
            contador++;

            if(contadorDia==contadorFind){
                strncat(nuevoPath,nombre,7);
            }
        }else{
            char aux[1]="";
            aux[0]=path[contador];
            strncat(nuevoPath,aux,1);
            contador++;
        }
    }
    string newpath = charToString(nuevoPath);
    return newpath;

}

//delelte
void deleteParticion(char _name[],char _path[],char _delete[]){
    MBR *mbr = (MBR*) malloc(sizeof (MBR));
    FILE *file;
    bool validacionParticion = false;
    file = fopen(_path,"rb+");
    fseek(file,0,SEEK_SET);
    fread(mbr,sizeof (MBR),1,file);
    //tipo de delete
    if(strcmp(_delete,"fast")==0){
        //se busca en las 4 particiones el nombre
        for (int i = 0; i < 4; ++i) {
            if(strcmp(mbr->mbr_particion[i].part_name,_name)==0){// si existe particion
                //mensaje
                validacionParticion = true;//existe
                char res;
                cout << "Desea eliminar la particion "<<_name<< " (S/N): ";
                cin >> res;
                if(res=='s'|| res=='S'){
                    //se actuliaza el mbr
                    mbr->mbr_particion[i].part_size  = 0;
                    mbr->mbr_particion[i].part_start = 0;
                    mbr->mbr_particion[i].part_type = '-';
                    mbr->mbr_particion[i].part_status = '-';
                    memset(mbr->mbr_particion[i].part_fit,0,3);
                    memset(mbr->mbr_particion[i].part_name,0,16);

                    elimininarParticionMount(_path,_name);

                    //se escribe
                    fseek(file,0,SEEK_SET);
                    fwrite(mbr,sizeof (MBR),1,file);
                    fclose(file);
                    cout << "Aviso -> Particion eliminada correctamente en modo fast "<<_name<<endl;
                    break;
                }else if(res=='n'||res=='N'){
                    fclose(file);
                    break;
                }else{
                    fclose(file);
                    cout << "Error -> Caracter incorrecta"<<endl;
                }


            }
            //para buscar en las logicas
            if(mbr->mbr_particion[i].part_type=='e'){

                //se leen los ebr
                EBR *ebrlog = (EBR*) malloc(sizeof (EBR));
                fseek(file,mbr->mbr_particion[i].part_start+sizeof (EBR)+1,SEEK_SET);
                fread(ebrlog,sizeof (EBR),1,file);
                int next = ebrlog->part_next;
                while(next!=-1){
                    if(strcmp(ebrlog->part_name,_name)==0){//si encuentra el nombre
                        validacionParticion=true;
                        char res;
                        cout << "Desea eliminar la partiicon "<<_name<<" (S/N): ";
                        cin>>res;

                        if(res=='s'||res=='S'){
                            int start = ebrlog->part_start;
                            ebrlog->part_start = 0;
                            ebrlog->part_size = 0;
                            memset(ebrlog->part_fit,0,3);
                            memset(ebrlog->part_name,0,16);

                            elimininarParticionMount(_path,_name);

                            fseek(file,start,SEEK_SET);
                            fwrite(ebrlog,sizeof (EBR),1,file);
                            fclose(file);
                            cout << "Aviso -> Particion eliminada correctamente en modo fast "<<_name<<endl;
                            break;
                        }else if(res=='n'||res=='N'){
                            fclose(file);
                            break;
                        }else{
                            fclose(file);
                            cout << "Error -> Caracter incorrecta"<<endl;
                        }


                    }
                    fseek(file,next,SEEK_SET);
                    fread(ebrlog,sizeof(EBR),1,file);
                    next = ebrlog->part_next;

                }
            }
        }


        if(!validacionParticion){
            cout << "Error -> La particion no existe para ser eliminado "<< _name<<endl;
        }
    }else if(strcmp(_delete,"full")==0){
        for (int i = 0; i < 4; ++i) {
            if(strcmp(mbr->mbr_particion[i].part_name,_name)==0){//busco el nombre
                validacionParticion = true;
                if(mbr->mbr_particion[i].part_type=='p'){//que tipo de particion es, es primaria
                    char res;
                    cout << "Desea eliminar la particion "<<_name<<" (S/N) : ";
                    cin >> res;
                    if(res=='s'||res=='S'){
                        for (int j = mbr->mbr_particion[i].part_start; j < mbr->mbr_particion[i].part_start+sizeof (MBR); ++j) {
                            fseek(file,j,SEEK_SET);
                            fwrite("0",1,1,file);
                        }
                        //se actualizae el mbr
                        mbr->mbr_particion[i].part_size  = 0;
                        mbr->mbr_particion[i].part_start = 0;
                        mbr->mbr_particion[i].part_type = '-';
                        mbr->mbr_particion[i].part_status = '-';
                        memset(mbr->mbr_particion[i].part_fit,0,3);
                        memset(mbr->mbr_particion[i].part_name,0,16);

                        elimininarParticionMount(_path,_name);

                        //se escribe
                        fseek(file,0,SEEK_SET);
                        fwrite(mbr,sizeof (MBR),1,file);
                        fclose(file);

                        cout << "Aviso -> Particion eliminada correctamente en modo full "<<_name<<endl;
                        break;
                    }else if(res=='n'||res=='N'){
                        fclose(file);
                        break;
                    }else{
                        fclose(file);
                        cout << "Error -> Caracter incorrecta"<<endl;
                    }


                }else if(mbr->mbr_particion[i].part_type == 'e'){//es extendida
                    char res;
                    cout << "Desea eliminar la particion "<<_name<<" (S/N): ";
                    cin >> res;
                    if(res=='s' || res=='S'){
                        //primero se eliminan las logicas
                        EBR *ebr = (EBR*) malloc(sizeof (EBR));
                        fseek(file,mbr->mbr_particion[i].part_start+sizeof (EBR)+1,SEEK_SET);
                        fread(ebr,sizeof (EBR),1,file);
                        int pos =0;
                        while(ebr->part_next!=-1){
                            pos = ebr->part_next;
                            for (int j = ebr->part_start; j < ebr->part_start+sizeof (EBR); ++j) {
                                fseek(file,j,SEEK_SET);
                                fwrite("0",1,1,file);
                            }
                            elimininarParticionMount(_path,ebr->part_name);
                            fseek(file,pos,SEEK_SET);
                            fread(ebr,sizeof (EBR),1,file);
                        }
                        for (int j = ebr->part_start; j < ebr->part_start+sizeof (EBR); ++j) {
                            fseek(file,j,SEEK_SET);
                            fwrite("0",1,1,file);
                        }

                        //se elimina particion de las 4
                        for (int j = mbr->mbr_particion[i].part_start; j < mbr->mbr_particion[i].part_start+sizeof (MBR); ++j) {
                            fseek(file,j,SEEK_SET);
                            fwrite("0",1,1,file);
                        }
                        //se actualiza el mbr
                        mbr->mbr_particion[i].part_size  = 0;
                        mbr->mbr_particion[i].part_start = 0;
                        mbr->mbr_particion[i].part_type = '-';
                        mbr->mbr_particion[i].part_status = '-';
                        memset(mbr->mbr_particion[i].part_fit,0,3);
                        memset(mbr->mbr_particion[i].part_name,0,16);

                        elimininarParticionMount(_path,_name);

                        //se escribe
                        fseek(file,0,SEEK_SET);
                        fwrite(mbr,sizeof (MBR),1,file);
                        fclose(file);

                        cout << "Aviso -> Particion eliminada correctamente en modo full "<<_name<<endl;
                        break;
                    }else if(res=='n'||res=='N'){
                        fclose(file);
                        break;
                    }else{
                        fclose(file);
                        cout << "Error -> Caracter incorrecta"<<endl;
                    }
                }

            }

            //para buscar en las logicas
            if(mbr->mbr_particion[i].part_type=='e'){
                EBR *ebrlog = (EBR*) malloc(sizeof (EBR));
                int inicio = mbr->mbr_particion[i].part_start+sizeof (EBR)+1;
                fseek(file,inicio,SEEK_SET);
                fread(ebrlog,sizeof(EBR),1,file);
                int next = ebrlog->part_next;
                while(next!=-1){
                    validacionParticion=true;
                    char res;
                    cout << "Desea eliminar la particin "<<_name<<" (S/N): ";
                    cin >> res;
                    if(res=='s'||res=='S'){
                        int start = ebrlog->part_start;
                        ebrlog->part_start = 0;
                        ebrlog->part_size = 0;
                        memset(ebrlog->part_fit,0,3);
                        memset(ebrlog->part_name,0,16);

                        elimininarParticionMount(_path,_name);

                        fseek(file,start,SEEK_SET);
                        fwrite(ebrlog,sizeof (EBR),1,file);
                        fclose(file);
                        cout << "Aviso -> Particion eliminada correctamente en modo full "<<_name<<endl;
                        break;
                    }else if(res=='n' || res=='N'){
                        fclose(file);
                        break;
                    }else{
                        fclose(file);
                        cout << "Error -> Caracter incorrecta"<<endl;
                    }

                }
            }
        }
        if(!validacionParticion){
            cout << "Error -> La particion no existe para ser eliminado "<< _name<<endl;
        }
    }
}

//add particion
void addParticion(char _add[],char _unit,char _path[],char _name[]){
//validacion add
    string s_add = charToString(_add);
    int add_valor =0;
    //validacion unit
    if(_unit=='b'){
        add_valor = stoi(s_add);
    }else if(_unit=='k'){
        add_valor = stoi(s_add)*1024;
    }else if(_unit=='m'){
        add_valor = stoi(s_add)*1024*1024;
    }


    if(add_valor>0){//es positivo para agregar mas espacio
        //leer mbr
        EBR ebrs[25];
        MBR* mbr = (MBR*) malloc(sizeof (MBR));
        MBR* mbraux = (MBR*) malloc(sizeof (MBR));
        EBR* ebraux = (EBR*) malloc(sizeof (EBR));
        EBR* ebr = (EBR*) malloc(sizeof(EBR));
        FILE*file;
        file = fopen(_path,"rb+");
        fseek(file,0,SEEK_SET);
        fread(mbr,sizeof(MBR),1,file);
        int total_usado = mbr->mbr_particion[0].part_size+mbr->mbr_particion[1].part_size+mbr->mbr_particion[2].part_size+mbr->mbr_particion[3].part_size+sizeof (MBR);
        int total_disk = mbr->mbr_tamano;
        int total_disponible = total_disk-total_usado;
        int contador_ebr =0;
        if(total_disponible>add_valor){//existe espacio
            //se obtienen todos los datos del disco
            for (int i = 0; i < 4; ++i) {//solo en la extendida hay mas datos
                if(mbr->mbr_particion[i].part_type=='e'){
                    fseek(file,mbr->mbr_particion[i].part_start+sizeof(EBR)+1,SEEK_SET);
                    fread(ebr,sizeof (EBR),1,file);
                    int next = ebr->part_start;
                    if(next!=-1){
                        while(next!=0){
                            fseek(file,next,SEEK_SET);
                            fread(ebr,sizeof (EBR),1,file);
                            //se guardan las logicas
                            ebrs[contador_ebr].part_next = ebr->part_next;
                            ebrs[contador_ebr].part_start = 0;
                            ebrs[contador_ebr].part_size = ebr->part_size;
                            strcpy(ebrs[contador_ebr].part_name,ebr->part_name);
                            strcpy(ebrs[contador_ebr].part_fit,ebr->part_fit);
                            contador_ebr++;
                            next = ebr->part_next;
                        }
                        //se guardan las logicas
                        ebrs[contador_ebr].part_next = ebr->part_next;
                        ebrs[contador_ebr].part_start = ebr->part_start;
                        ebrs[contador_ebr].part_size = ebr->part_size;
                        strcpy(ebrs[contador_ebr].part_name,ebr->part_name);
                        strcpy(ebrs[contador_ebr].part_fit,ebr->part_fit);
                    }

                }
            }

            //limpio disco
            cout << "Aviso -> Limpiando disco........"<<endl;
            fseek(file,0,SEEK_SET);
            for (int i = 0; i < mbr->mbr_tamano; ++i) {
                fwrite("0",1,1,file);
            }
            //se modifica especificamente el tamaño de la particion que  SE SOLICITA
            for (int i = 0; i < 4; ++i) {
                if(strcmp(mbr->mbr_particion[i].part_name,_name)==0){
                    mbr->mbr_particion[i].part_size += add_valor;
                    break;
                }
            }

            //solo mbr
            mbraux->mbr_tamano = mbr->mbr_tamano;
            mbraux->mbr_disk_signature = mbr->mbr_disk_signature;
            mbraux->mbr_fecha_creacion = mbr->mbr_fecha_creacion;

            //modificaciones al mbr y ebr
            for (int i = 0; i < 4; ++i) {
                int nuevosize = mbr->mbr_particion[i].part_size;
                if(mbr->mbr_particion[i].part_type=='p'){
                    int size_usado = mbraux->mbr_particion[0].part_size+mbraux->mbr_particion[1].part_size+mbraux->mbr_particion[2].part_size+mbraux->mbr_particion[3].part_size;
                    mbraux->mbr_particion[i].part_start = size_usado+sizeof (MBR)+1;

                    //paso de datos
                    mbraux->mbr_particion[i].part_status = mbr->mbr_particion[i].part_status;
                    mbraux->mbr_particion[i].part_size = nuevosize;
                    mbraux->mbr_particion[i].part_type = mbr->mbr_particion[i].part_type;
                    strcpy(mbraux->mbr_particion[i].part_fit,mbr->mbr_particion[i].part_fit);
                    strcpy(mbraux->mbr_particion[i].part_name,mbr->mbr_particion[i].part_name);

                    //se actualiza mbr
                    fseek(file,0,SEEK_SET);
                    fwrite(mbraux,sizeof (MBR),1,file);

                    //se escribe la particion modificada
                    fseek(file,mbraux->mbr_particion[i].part_start,SEEK_SET);
                    fwrite(&mbraux->mbr_particion[i],sizeof (mbraux->mbr_particion[i]),1,file);
                    cout << "Aviso -> Se ha incrementado el espacio en particion primaria "<<_name<<endl;

                }else if(mbr->mbr_particion[i].part_type=='e'){
                    int size_usado = mbraux->mbr_particion[0].part_size+mbraux->mbr_particion[1].part_size+mbraux->mbr_particion[2].part_size+mbraux->mbr_particion[3].part_size;
                    mbraux->mbr_particion[i].part_start = size_usado+sizeof (MBR)+1;

                    //paso de datos
                    mbraux->mbr_particion[i].part_status = mbr->mbr_particion[i].part_status;
                    mbraux->mbr_particion[i].part_size = nuevosize;
                    mbraux->mbr_particion[i].part_type = mbr->mbr_particion[i].part_type;
                    strcpy(mbraux->mbr_particion[i].part_fit,mbr->mbr_particion[i].part_fit);
                    strcpy(mbraux->mbr_particion[i].part_name,mbr->mbr_particion[i].part_name);

                    //se actualiza mbr
                    fseek(file,0,SEEK_SET);
                    fwrite(mbraux,sizeof (MBR),1,file);

                    //se reescribe la particion modificada
                    fseek(file,mbraux->mbr_particion[i].part_start,SEEK_SET);
                    fwrite(&mbraux->mbr_particion[i],sizeof (mbraux->mbr_particion[i]),1,file);

                    //se reescribe los ebr
                    int contador_array = 0;
                    int siguiente=0;
                    int inicio =0;

                    inicio = mbraux->mbr_particion[i].part_start+sizeof (EBR)+1;
                    int c_log=0;
                    while(ebrs[contador_array].part_next!=-1){
                        c_log++;
                        ebraux->part_size = ebrs[contador_array].part_size;
                        ebraux->part_start = inicio;
                        siguiente = ebraux->part_size+ebraux->part_start+1;
                        ebraux->part_next = ebraux->part_size+ebraux->part_start+1;
                        strcpy(ebraux->part_fit,ebrs[contador_array].part_fit);
                        strcpy(ebraux->part_name,ebrs[contador_array].part_name);
                        cout << ebraux->part_name<<endl;
                        fseek(file,inicio,SEEK_SET);
                        fwrite(ebraux,sizeof (EBR),1,file);
                        inicio = siguiente;
                        contador_array++;
                        if(c_log<=23){
                            EBR* ebrc = (EBR*) malloc(sizeof (EBR));
                            ebrc->part_start = 0;
                            ebrc->part_size = 0;
                            ebrc->part_next = -1;
                            memset(ebrc->part_fit,0,3);
                            memset(ebrc->part_name,0,16);
                            fseek(file,inicio,SEEK_SET);
                            fwrite(ebrc,sizeof (EBR),1,file);

                        }

                    }

                    //cuanod no hay particiones logicas en el mbr
                    if(c_log==0){
                        EBR* ebrc = (EBR*) malloc(sizeof (EBR));
                        ebrc->part_start = 0;
                        ebrc->part_size = 0;
                        ebrc->part_next = -1;
                        memset(ebrc->part_fit,0,3);
                        memset(ebrc->part_name,0,16);
                        fseek(file,inicio,SEEK_SET);
                        fwrite(ebrc,sizeof (EBR),1,file);
                    }


                   /* //último
                    fseek(file,inicio,SEEK_SET);
                    ebraux->part_next = -1;
                    ebraux->part_start = inicio;
                    ebraux->part_size = ebrs[contador_array].part_size;
                    strcpy(ebraux->part_fit,ebrs[contador_array].part_fit);
                    strcpy(ebraux->part_name,ebrs[contador_array].part_name);
                    fwrite(ebraux,sizeof (EBR),1,file);*/

                    cout << "Aviso -> Se ha incrementado el espacio en particion extendida "<<_name<<endl;

                }
            }
            fclose(file);

        }else{
            cout << "Error -> Espacio insuficiente para add positivo"<<endl;
        }

    }else if(add_valor<0){//es negativo para quitarle
        //leer mbr
        EBR ebrs[25];
        MBR* mbr = (MBR*) malloc(sizeof (MBR));
        MBR* mbraux = (MBR*) malloc(sizeof (MBR));
        EBR* ebraux = (EBR*) malloc(sizeof (EBR));
        EBR* ebr = (EBR*) malloc(sizeof(EBR));
        FILE*file;
        file = fopen(_path,"rb+");
        fseek(file,0,SEEK_SET);
        fread(mbr,sizeof(MBR),1,file);
        int total_particion = 0;
        int total_disponible = 0;
        int contador_ebr =0;
        //para buscar la particion
        for (int i = 0; i < 4; ++i) {
            if(strcmp(mbr->mbr_particion[i].part_name,_name)==0){
                total_particion = mbr->mbr_particion[i].part_size;
                total_disponible = total_particion+add_valor;
            }
        }

        //es posible
        if(total_disponible>0){//no sea respuesta negativa
            //se obtienen todos los datos del disco
            for (int i = 0; i < 4; ++i) {//solo en la extendida hay mas datos
                if(mbr->mbr_particion[i].part_type=='e'){
                    fseek(file,mbr->mbr_particion[i].part_start+sizeof(EBR)+1,SEEK_SET);
                    fread(ebr,sizeof (EBR),1,file);
                    int next = ebr->part_start;
                    // no se ha escrito nada el nexto es -1 al principio
                    if(next!=-1){
                        while(next!=0){
                            fseek(file,next,SEEK_SET);
                            fread(ebr,sizeof (EBR),1,file);
                            //se guardan las logicas
                            ebrs[contador_ebr].part_next = ebr->part_next;
                            ebrs[contador_ebr].part_start = 0;
                            ebrs[contador_ebr].part_size = ebr->part_size;
                            strcpy(ebrs[contador_ebr].part_name,ebr->part_name);
                            strcpy(ebrs[contador_ebr].part_fit,ebr->part_fit);
                            contador_ebr++;
                            next = ebr->part_next;
                        }
                        //se guardan las logicas
                        ebrs[contador_ebr].part_next = ebr->part_next;
                        ebrs[contador_ebr].part_start = ebr->part_start;
                        ebrs[contador_ebr].part_size = ebr->part_size;
                        strcpy(ebrs[contador_ebr].part_name,ebr->part_name);
                        strcpy(ebrs[contador_ebr].part_fit,ebr->part_fit);
                    }


                }
            }

            //limpio disco
            cout << "Aviso -> Limpiando disco........"<<endl;
            fseek(file,0,SEEK_SET);
            for (int i = 0; i < mbr->mbr_tamano; ++i) {
                fwrite("0",1,1,file);
            }
            //se modifica especificamente el tamaño de la particion que  SE SOLICITA
            for (int i = 0; i < 4; ++i) {
                if(strcmp(mbr->mbr_particion[i].part_name,_name)==0){
                    mbr->mbr_particion[i].part_size += add_valor;
                    break;
                }
            }

            //solo mbr
            mbraux->mbr_tamano = mbr->mbr_tamano;
            mbraux->mbr_disk_signature = mbr->mbr_disk_signature;
            mbraux->mbr_fecha_creacion = mbr->mbr_fecha_creacion;

            //modificaciones al mbr y ebr
            for (int i = 0; i < 4; ++i) {
                int nuevosize = mbr->mbr_particion[i].part_size;
                if(mbr->mbr_particion[i].part_type=='p'){
                    int size_usado = mbraux->mbr_particion[0].part_size+mbraux->mbr_particion[1].part_size+mbraux->mbr_particion[2].part_size+mbraux->mbr_particion[3].part_size;
                    mbraux->mbr_particion[i].part_start = size_usado+sizeof (MBR)+1;

                    //paso de datos
                    mbraux->mbr_particion[i].part_status = mbr->mbr_particion[i].part_status;
                    mbraux->mbr_particion[i].part_size = nuevosize;
                    mbraux->mbr_particion[i].part_type = mbr->mbr_particion[i].part_type;
                    strcpy(mbraux->mbr_particion[i].part_fit,mbr->mbr_particion[i].part_fit);
                    strcpy(mbraux->mbr_particion[i].part_name,mbr->mbr_particion[i].part_name);

                    //se actualiza mbr
                    fseek(file,0,SEEK_SET);
                    fwrite(mbraux,sizeof (MBR),1,file);

                    //se escribe la particion modificada
                    fseek(file,mbraux->mbr_particion[i].part_start,SEEK_SET);
                    fwrite(&mbraux->mbr_particion[i],sizeof (mbraux->mbr_particion[i]),1,file);
                    cout << "Aviso -> Se ha reducido el espacio en particion primaria "<<_name<<endl;

                }else if(mbr->mbr_particion[i].part_type=='e'){
                    int size_usado = mbraux->mbr_particion[0].part_size+mbraux->mbr_particion[1].part_size+mbraux->mbr_particion[2].part_size+mbraux->mbr_particion[3].part_size;
                    mbraux->mbr_particion[i].part_start = size_usado+sizeof (MBR)+1;

                    //paso de datos
                    mbraux->mbr_particion[i].part_status = mbr->mbr_particion[i].part_status;
                    mbraux->mbr_particion[i].part_size = nuevosize;
                    mbraux->mbr_particion[i].part_type = mbr->mbr_particion[i].part_type;
                    strcpy(mbraux->mbr_particion[i].part_fit,mbr->mbr_particion[i].part_fit);
                    strcpy(mbraux->mbr_particion[i].part_name,mbr->mbr_particion[i].part_name);

                    //se actualiza mbr
                    fseek(file,0,SEEK_SET);
                    fwrite(mbraux,sizeof (MBR),1,file);

                    //se reescribe la particion modificada
                    fseek(file,mbraux->mbr_particion[i].part_start,SEEK_SET);
                    fwrite(&mbraux->mbr_particion[i],sizeof (mbraux->mbr_particion[i]),1,file);

                    //se reescribe los ebr
                    int contador_array = 0;
                    int siguiente=0;
                    int inicio =0;

                    inicio = mbraux->mbr_particion[i].part_start+sizeof (EBR)+1;
                    int c_log=0;
                    while(ebrs[contador_array].part_next!=-1){
                        ebraux->part_size = ebrs[contador_array].part_size;
                        ebraux->part_start = inicio;
                        siguiente = ebraux->part_size+ebraux->part_start+1;
                        ebraux->part_next = ebraux->part_size+ebraux->part_start+1;
                        strcpy(ebraux->part_fit,ebrs[contador_array].part_fit);
                        strcpy(ebraux->part_name,ebrs[contador_array].part_name);
                        cout << ebraux->part_name<<endl;
                        fseek(file,inicio,SEEK_SET);
                        fwrite(ebraux,sizeof (EBR),1,file);
                        c_log++;
                        inicio = siguiente;
                        contador_array++;
                        if(c_log<=23){
                            EBR* ebrc = (EBR*) malloc(sizeof (EBR));
                            ebrc->part_start = 0;
                            ebrc->part_size = 0;
                            ebrc->part_next = -1;
                            memset(ebrc->part_fit,0,3);
                            memset(ebrc->part_name,0,16);
                            fseek(file,inicio,SEEK_SET);
                            fwrite(ebrc,sizeof (EBR),1,file);

                        }
                    }

                    //cuanod no hay particiones logicas en el mbr
                    if(c_log==0){
                        EBR* ebrc = (EBR*) malloc(sizeof (EBR));
                        ebrc->part_start = 0;
                        ebrc->part_size = 0;
                        ebrc->part_next = -1;
                        memset(ebrc->part_fit,0,3);
                        memset(ebrc->part_name,0,16);
                        fseek(file,inicio,SEEK_SET);
                        fwrite(ebrc,sizeof (EBR),1,file);
                    }


                    cout << "Aviso -> Se ha reducido el espacio en particion extendida "<<_name<<endl;

                }
            }
            fclose(file);

        }else{
            cout << "Error -> No se puede reducir la particion solicidato con el add"<<endl;
        }


    }

}

void analsisFdisk(char comando[]){
    int contador=0;
    char lineacomando[100]="";

    char valor_size[20]="";
    char valor_unit='k';
    char valor_path[100]="";
    char valor_type='p';
    char valor_fit[3]={'w','f'};
    char valor_delete[20]="";
    char valor_name[16]="";
    char valor_add[20]="";

    //argumentos opcionales
    bool flag_unit = false;
    bool flag_type=false;
    bool flag_fit=false;
    bool flag_delete=false;
    bool flag_add=false;
    bool flag_mov=false;
    cout << "fit inicio "<<valor_fit<<endl;
    while(comando[contador]!=NULL){
        if (comando[contador]==' '){
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

        //validacioens argumentos
        if(strcmp(lineacomando,"fdisk")==0){
            cout << "Encontro: "<<lineacomando<<endl;
            memset(lineacomando,0,100);

        }else if(strcmp(lineacomando,"$size=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            //para obener valor
            while(comando[contador]!=NULL){
                if(comando[contador]==' '||comando[contador]=='\n'){
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
        }else if(strcmp(lineacomando,"@unit=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            flag_unit = true;
            memset(lineacomando,0,100);
            valor_unit = tolower(comando[contador]);
            contador++;
            cout << "Valor: "<<valor_unit<<endl;
        }else if(strcmp(lineacomando,"$path=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            //para obtener el valor
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
        }else if(strcmp(lineacomando,"@type=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            flag_type = true;
            memset(lineacomando,0,100);
            valor_type = tolower(comando[contador]);
            contador++;
            cout << "Valor: "<<valor_type<<endl;
        }else if(strcmp(lineacomando,"@fit=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            flag_fit = true;
            memset(lineacomando,0,100);
            memset(valor_fit,0,3);
            //para obtener valor fit
            while(comando[contador]!=NULL){
                if(comando[contador]==' '||comando[contador]=='\n'){
                    contador++;
                    break;
                }else{
                    char aux[1]="";
                    aux[0]= tolower(comando[contador]);
                    strncat(valor_fit,aux,1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_fit<<endl;
        }else if(strcmp(lineacomando,"@delete=>")==0){
            cout <<"Argumento: "<<lineacomando<<endl;
            flag_delete = true;
            memset(lineacomando,0,100);
            //para obtenre valor delete
            while(comando[contador]!=NULL){
                if(comando[contador]==' '||comando[contador]=='\n'){
                    contador++;
                    break;
                }else{
                    char aux[1]="";
                    aux[0]= tolower(comando[contador]);
                    strncat(valor_delete,aux,1);
                    contador++;
                }
            }
            cout <<"Valor: "<<valor_delete<<endl;
        }else if(strcmp(lineacomando,"$name=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            //para obtener valor name
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

        }else if(strcmp(lineacomando,"@add=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            flag_add=true;
            memset(lineacomando,0,100);
            //para obtener valor add
            while(comando[contador]!=NULL){
                if(comando[contador]==' '||comando[contador]=='\n'){
                    contador++;
                    break;
                }else{
                    char aux[1]="";
                    aux[0]= comando[contador];
                    strncat(valor_add,aux,1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_add<<endl;
        }else if(strcmp(lineacomando,"@mov=>")==0){
            cout << "Encontro :"<<lineacomando<<endl;
            flag_mov = true;
            memset(lineacomando,0,100);

        }
    }



    //validacion para crear particiones
    if(flag_add){//si es add
        //disco original
        addParticion(valor_add,valor_unit,valor_path,valor_name);
        //disco espejo
        string pathcopia = cambioPathCopia(valor_path);
        char nuevoPath [100]="";
        strcpy(nuevoPath,pathcopia.c_str());
        addParticion(valor_add,valor_unit,nuevoPath,valor_name);

    }else if(flag_delete){//si es delete
        //disco origonal
        deleteParticion(valor_name,valor_path,valor_delete);
        //disco espejo
        string pathcopia = cambioPathCopia(valor_path);
        char nuevoPath [100]="";
        strcpy(nuevoPath,pathcopia.c_str());
        deleteParticion(valor_name,nuevoPath,valor_delete);

    }else if(flag_mov){//si es mov
        cout << "Error -> Se está intentando moviendo particion"<<endl;
    }else{//es para particion
        bool flag_size = validacionSizeParticion(valor_size);
        bool flag_path = validacionDisco(valor_path);
        bool flags_fit = validacionFit(valor_fit);

        if(flag_size){//es positivo y mayor a cero
            if(valor_unit=='b'||valor_unit=='k'||valor_unit=='m'){// la letra de unit es correcta
                if(valor_type=='p'||valor_type=='l'||valor_type=='e'){// el tipo de particion

                    if(flags_fit){
                        if (flag_path) {
                            //al disco original
                            crearParticion(valor_size, valor_unit, valor_path, valor_type, valor_fit, valor_name);
                            //disco espejo
                            string pathcopia = cambioPathCopia(valor_path);
                            char nuevoPath [100]="";
                            strcpy(nuevoPath,pathcopia.c_str());
                            crearParticion(valor_size,valor_unit,nuevoPath,valor_type,valor_fit,valor_name);
                        }else {
                            cout << "Error -> El disco no existe para realizar la particion" << endl;
                        }
                    }else{
                        cout << "Error -> Valor de fit es invalido"<<endl;
                    }
                }else{
                    cout << "Error -> El tipo de particion es invalido"<<endl;
                }

            }else{
                cout << "Error -> El valor de unit es invalido"<<endl;
            }
        }else{
            cout << "Error -> El valor de size invalido"<<endl;
        }
    }
}