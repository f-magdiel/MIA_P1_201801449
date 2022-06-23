#include <iostream>
#include <cstring>
#include <cmath>
#include "../Estructuras/SUPER_BLOQUE.h"
#include "../Estructuras/INODOS.h"
#include "../Estructuras/BLOQUECARPETA.h"
#include "../Estructuras/JOURNALING.h"
#include "../Estructuras/MBR.h"
#include "../Estructuras/DISCO.h"
#include "../Estructuras/CONTENT.h"
#include "../Estructuras/BLOQUEARCHIVO.h"
#include "../Estructuras/APUNTADORES.h"

#include "../Comandos/mount.h"
#include "../Comandos/mkdisk.h"
using namespace std;

void crearEXT3(DISCO disco,char _id[]){

    FILE* file;
    file = fopen(disco.path,"rb+");
    //Se leer el mbr
    MBR *mbr = (MBR*) malloc(sizeof (MBR));
    fseek(file,0,SEEK_SET);
    fread(mbr,sizeof (MBR),1,file);//se leer el mbr
    //busco la particion en disco fisico
    int indice=0;
    string nombre_buscar;
    for (int i = 0; i < 4; ++i) {
        if(strcmp(disco.mbr_particion[i].id,_id)==0){//encuetro la particion
            nombre_buscar = charToString(disco.mbr_particion[i].part_name);
            break;
        }
    }
    for (int i = 0; i < 4; ++i) {
        if(strcmp(mbr->mbr_particion[i].part_name,nombre_buscar.c_str())==0){
            indice = i;
            break;
        }
    }

    // se calcula la n
    int n = (mbr->mbr_particion[indice].part_size-sizeof(SUPER_BLOQUE))/(4+sizeof(JOURNALING)+sizeof(INODOS)+3*sizeof(BLOQUECARPETA));
    n  = (int)floor(n);

    //valido que la particion sea capaz de soportar el ext
    if(mbr->mbr_particion[indice].part_size<1000){//debe tener la menos 1kb
        cout << "Error -> El tamano de la partición es muy pequeño"<<endl;
    }else{
        //se inicia formato
        fseek(file,mbr->mbr_particion[indice].part_start+sizeof (mbr->mbr_particion[indice])+1,SEEK_SET);
        for (int i = mbr->mbr_particion[indice].part_start+sizeof (mbr->mbr_particion[indice])+1; i < mbr->mbr_particion[indice].part_size; ++i) {
            fwrite("0",1,1,file);
            fseek(file,i,SEEK_SET);
        }

        //se inicializa super bloque
        SUPER_BLOQUE super;
        super.s_filesystem_type = 3;
        super.s_inode_count = n;
        super.s_block_count = 3*n;
        super.s_free_blocks_count = 3*n;//restar dspues
        super.s_free_inodes_count = n;//restar despues
        time_t time_mount;
        time_mount = time(NULL);
        super.s_mtime = time_mount;
        super.s_mnt_count++;
        super.s_magic = 0xEF53;
        super.s_inode_size = sizeof (INODOS);
        super.s_block_size = sizeof(BLOQUECARPETA);
        super.s_first_ino = 2;
        super.s_first_blo = 2;
        super.s_bm_inode_start = mbr->mbr_particion[indice].part_start+sizeof(SUPER_BLOQUE)+(n*sizeof(JOURNALING))+1;//1
        super.s_bm_block_start = super.s_bm_inode_start+n+1;
        super.s_inode_start = super.s_bm_block_start+(3*n)+1;
        super.s_block_start = super.s_inode_start+(n*sizeof (INODOS))+1;//1

        //escribir superbloque
        fseek(file,mbr->mbr_particion[indice].part_start+sizeof (mbr->mbr_particion[indice])+1,SEEK_SET);
        fwrite(&super,sizeof (SUPER_BLOQUE),1,file);

        //creacion bitmasp de inodos y bloques
        char bit_inodos[n];
        char bit_bloques[3*n];
        int start_bitinodos = mbr->mbr_particion[indice].part_start+sizeof(SUPER_BLOQUE)+(n*sizeof (JOURNALING))+1;//1
        for (int i = 0; i < n; ++i){ bit_inodos[i]='0';}
            bit_inodos[0]='1';//carpeta raiz


            // se escribe el bitmap de inodos
        fseek(file,start_bitinodos,SEEK_SET);
        fwrite(&bit_inodos,sizeof (char),n,file);

        int start_bloques = start_bitinodos+n+1;
        for (int i = 0; i < 3*n; ++i) { bit_bloques[i]='0';}
        bit_bloques[0]='1';//para dif carpeta
        //bit_bloques[1]='2';//para para dif archivos
        //se escribe el bitmap de bloques
        fseek(file,start_bloques,SEEK_SET);
        fwrite(&bit_bloques,sizeof(char),3*n,file);

        //escribo el journaling
        int start_journaling = mbr->mbr_particion[indice].part_start+sizeof (mbr->mbr_particion[indice])+sizeof(SUPER_BLOQUE)+1;//1
        JOURNALING jour;
        jour.jorunal_tipo_operacion[0]='-';
        jour.journal_contenido[0]='-';
        jour.journal_nombre[0]='-';
        jour.journal_persimo[0]='-';
        jour.journal_propietario[0]='-';
        jour.journal_tipo='-';
        //se escribe el journaling
        fseek(file,start_journaling,SEEK_SET);
        fwrite(&jour,sizeof(JOURNALING),1,file);

        //leo super blque otra vez
        SUPER_BLOQUE auxsuper;
        fseek(file,mbr->mbr_particion[indice].part_start+sizeof(mbr->mbr_particion[indice])+1,SEEK_SET);
        fread(&auxsuper,sizeof (SUPER_BLOQUE),1,file);

        //se crea el inodo raiz
        INODOS raiz;
        raiz.i_uid=1;
        raiz.i_gid=1;
        raiz.i_size=n*sizeof(INODOS);
        time_t fecha_c;
        fecha_c= time(NULL);
        raiz.i_ctime=fecha_c;
        raiz.i_atime=fecha_c;
        raiz.i_mtime=fecha_c;
        for (int i = 0; i < 15; ++i) { raiz.i_block[i]=-1;}// se crean los 15 espacios
        raiz.i_block[0]=0;
        raiz.i_type='0';//es carpeta
        //mas adelante se escribre

        //bloque carpeta raiz
        BLOQUECARPETA carpetaraiz;
        //BLOQUEARCHIVO archivoraiz;
        CONTENT contentraiz;
        //limpio
        strcpy(contentraiz.b_name,".");//carpeta actual
        contentraiz.b_inodo = 0;//apuntador al inodo que pertenece
        carpetaraiz.b_content[0] = contentraiz;//guardamos en la carpeta raiz
        strcpy(contentraiz.b_name,"..");
        contentraiz.b_inodo=0;
        carpetaraiz.b_content[1] = contentraiz;

        //strcpy(contentraiz.b_name,"-");//el padre
        //contentraiz.b_inodo=-1;
        //carpetaraiz.b_content[1]=contentraiz;// se agrega la carpeta padre

        //se escribe el inodo y el bloque de la carpeta raiz
        //escribe el inodo
        fseek(file,auxsuper.s_inode_start,SEEK_SET);
        fwrite(&raiz,sizeof(INODOS),1,file);
        auxsuper.s_free_inodes_count--;//se disminuye

        //escribe carpeta raiz
        fseek(file,auxsuper.s_block_start,SEEK_SET);
        fwrite(&carpetaraiz,sizeof (BLOQUECARPETA),1,file);
        auxsuper.s_free_blocks_count--;//se disminuye

        //escribo bloque archivo
        //fseek(file,auxsuper.s_block_start+64,SEEK_SET);
        //fwrite(&archivoraiz,64,1,file);
        //auxsuper.s_free_blocks_count--;

        //rescribo el SUPERBLOQUE
        fseek(file,mbr->mbr_particion[indice].part_start+sizeof (mbr->mbr_particion[indice])+1,SEEK_SET);
        fwrite(&auxsuper,sizeof (SUPER_BLOQUE),1,file);
        fclose(file);
        cout << "Aviso -> La particion ha sido formateada como EXT3 correctamente"<<endl;

    }



}

void formatoMkfs(char _id[], char _type[]){
    DISCO disco = buscarDisco(_id);
    if(disco.mbr_tamano!=0){
        //tipo de formato a crear
        if(strcmp(_type,"fast")==0){

        }else{
            //siempre es full, sino se especifica
            crearEXT3(disco,_id);

        }
    }else{
        cout << "Error -> ID no existe para realizar el Formato"<<endl;
    }

}

void analisisMkfs(char comando[]){
    int contador = 0;
    char lineacomando[100]="";
    char valor_id[10]="";
    char valor_type[10]="";
    char valor_add[10]="";
    char valor_unit;

    bool flag_type = false;
    bool flag_add = false;
    bool flag_unit=false;

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

        //para validar los argumentos
        if(strcmp(lineacomando,"mkfs")==0){
            cout << "Encontro: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            contador++;
        }else if(strcmp(lineacomando,"$id=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);

            while(comando[contador]!=NULL){
                if(comando[contador]==' ' || comando[contador]=='\n'){
                    contador++;
                    break;
                }else{
                    char aux[1]="";
                    aux[0] = tolower(comando[contador]);
                    strncat(valor_id,aux,1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_id<<endl;
        }else if(strcmp(lineacomando,"@type=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            flag_type=true;
            while(comando[contador]!=NULL){
                if(comando[contador]==' ' || comando[contador]=='\n'){
                    contador++;
                    break;
                }else{
                    char aux[1]="";
                    aux[0] = tolower(comando[contador]);
                    strncat(valor_type,aux,1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_type<<endl;
        }else if(strcmp(lineacomando,"@add=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            flag_add=true;
            while(comando[contador]!=NULL){
                if(comando[contador]==' ' || comando[contador]=='\n'){
                    contador++;
                    break;
                }else{
                    char aux[1]="";
                    aux[0] = comando[contador];
                    strncat(valor_add,aux,1);
                    contador++;
                }
            }
            cout << "Valor: "<<valor_add<<endl;
        }else if(strcmp(lineacomando,"@unit=>")==0){
            cout << "Argumento: "<<lineacomando<<endl;
            memset(lineacomando,0,100);
            flag_unit=true;
            valor_unit = tolower(comando[contador]);
            cout << "Valor: "<<valor_unit<<endl;
        }
    }

    //para realizar el formateo
    if(!flag_type){// si se manda en el argumento
        strcpy(valor_type,"full");
    }

    if(!flag_unit){
        valor_unit='k';
    }

    //se manda a formatear
    formatoMkfs(valor_id,valor_type);


}