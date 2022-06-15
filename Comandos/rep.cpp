#include <iostream>
#include <cstring>
#include <dirent.h>
#include <string>
#include <fstream>

#include "../Comandos/mkdisk.h"
#include "../Comandos/mount.h"
#include "../Estructuras/MBR.h"
#include "../Estructuras/SUPER_BLOQUE.h"
#include "../Estructuras/INODOS.h"
#include "../Estructuras/BLOQUEARCHIVO.h"
#include "../Estructuras/BLOQUECARPETA.h"
#include "../Estructuras/APUNTADORES.h"

using namespace std;
string BlockPointer_Tabla(int indice,APUNTADORES *blockpointer,int tree){
    string tablepointer = "";
    string conexionesBloque;    //BLOQUE - BLOQUE
    //SOLO POSEE CONEXIONES A BLOQUES SOLAMENTE
    tablepointer += "Bloque"+to_string(indice)+" [\n";
    tablepointer += "shape=plaintext\n";
    tablepointer += "label=<\n";
    tablepointer += "<table border=\'0\' cellborder=\'1\' color=\'brown\' cellspacing=\'0\'>\n";
    tablepointer += "\t<tr><td PORT = \"BL"+to_string(indice)+"\" >Bloque de Apuntadores</td></tr>\n";
    tablepointer += "\t<tr><td cellpadding=\'4\'>\n";
    tablepointer += "\t\t<table color=\'orange\' cellspacing=\'0\'>\n";
    //INICIO DE INFORMACION
    for(int i=0; i<16;i++){
        string indiceBloque =  (((int)blockpointer->b_apuntadores[i])>0)?"PORT = \"B"+to_string(i)+"\"":"";
        tablepointer += "\t\t\t<tr><td>i_block"+to_string(i)+"</td><td "+indiceBloque+" >"+to_string(blockpointer->b_apuntadores[i])+"</td></tr>\n";
        conexionesBloque += indiceBloque !="" ?"\nBloque"+to_string(indice)+":"+"B"+to_string(i)+" -> Bloque"+to_string(blockpointer->b_apuntadores[i])+":BL"+to_string(blockpointer->b_apuntadores[i])+";":"";
    }


    //FINAL DE INFORMACION
    tablepointer += "\t\t</table>\n";
    tablepointer +="</td>\n";
    tablepointer += "</tr>\n";
    tablepointer += "\t<tr><td>APUNTADOR</td></tr>\n";
    tablepointer += "</table>\n";
    tablepointer += " >];\n";
    if(tree){
        tablepointer +="\n\n";
        tablepointer += conexionesBloque;
    }
    return tablepointer;

}

string BlockFile_Tabla(int indice,BLOQUEARCHIVO *blockfile,int tree){
    string tablefile="";
    //NO POSEE CONEXION A OTRO BLOQUE O INODO
    tablefile += "Bloque"+to_string(indice)+" [\n";
    tablefile += "shape=plaintext\n";
    tablefile += "label=<\n";
    tablefile += "<table border=\'0\' cellborder=\'1\' color=\'black\' cellspacing=\'0\'>\n";
    tablefile += "\t<tr><td PORT =\"BL"+to_string(indice)+"\">Bloque de Archivo</td></tr>\n";
    tablefile += "\t<tr><td cellpadding=\'4\'>\n";
    tablefile += "\t\t<table color=\'red\' cellspacing=\'0\'>\n";
    //INICIO DE INFORMACION
    tablefile += "\t\t\t<tr><td>Contenido</td></tr>\n";
    tablefile += "\t\t\t<tr><td>";
    for(int i=0;i<64;i++){
        if(blockfile->b_content[i]!='\0')
            tablefile += to_string(blockfile->b_content[i]);
    }
    tablefile +="</td></tr>\n";
    tablefile += "\t\t</table>\n";
    tablefile +="</td>\n";
    tablefile += "</tr>\n";
    //FINAL DE INFORMACION
    tablefile += "\t<tr><td>ARCHIVO</td></tr>\n";
    tablefile += "</table>\n";
    tablefile += " >];\n";
    return tablefile;
}

string BlockFolder_Tabla(int indice,BLOQUECARPETA *blockfolder,int tree){
    string tablefolder="";
    //SOLO POSEE CONEXION A OTROS INODOS QUE PUEDEN SER INODOS DE ARCHIVOS O CARPETAS
    string conexionesainodos ="";
    string indicebloque;
    tablefolder += "Bloque"+to_string(indice)+" [\n";
    tablefolder += "shape=plaintext\n";
    tablefolder += "label=<\n";
    tablefolder += "<table border=\'0\' cellborder=\'1\' color=\'yellow\' cellspacing=\'0\'>\n";
    tablefolder += "\t<tr><td PORT =\"BL"+to_string(indice)+"\">Bloque de Carpeta</td></tr>\n";
    tablefolder += "\t<tr><td cellpadding=\'4\'>\n";
    tablefolder += "\t\t<table color=\'gray\' cellspacing=\'0\'>\n";
    //INICIO DE INFORMACION
    tablefolder += "\t\t\t<tr><td>B_NAME</td><td>B_INODO</td></tr>\n";
    for(int i=0;i<4;i++){
        indicebloque =  (((int)blockfolder->b_content[i].b_inodo)>0)?"PORT = \"B"+to_string(i)+"\"":"";
        cout << "SUUUUUUUUUUUUUUUUUUUUUUUUUUIIIIIIII "<<blockfolder->b_content[i].b_name<<endl;
        tablefolder += "\t\t\t<tr><td>SIUUU"+charToString(blockfolder->b_content[i].b_name)+"</td><td "+indicebloque+">"+to_string(blockfolder->b_content[i].b_inodo)+"</td></tr>\n";
        if(charToString(blockfolder->b_content[i].b_name) =="."|| charToString(blockfolder->b_content[i].b_name) ==".."){

        }else{
            conexionesainodos += indicebloque != ""?"\nBloque"+to_string(indice)+":"+"B"+to_string(i)+" -> Inodo"+to_string(blockfolder->b_content[i].b_inodo)+":I"+to_string(blockfolder->b_content[i].b_inodo)+";":"";
        }
    }
    //FINAL DE INFORMACION
    tablefolder += "\t\t</table>\n";
    tablefolder += "</td>\n";
    tablefolder += "</tr>\n";
    tablefolder += "\t<tr><td>CARPETA</td></tr>\n";
    tablefolder += "</table>\n";
    tablefolder += " >];\n";
    if(tree){
        tablefolder +="\n\n";
        tablefolder += conexionesainodos;
    }
    return tablefolder;
}
string InodoTabla(int indice,INODOS * inode,int tree){

    string tableinode = "";
    string conexionesinodos ="";
    //SOLO POSEE CONEXIONES A BLOQUES
    tableinode += "Inodo"+to_string(indice)+" [\n";
    tableinode += "shape=plaintext\n";
    tableinode += "label=<\n";
    tableinode += "<table border=\'0\' cellborder=\'1\' color=\'green\' cellspacing=\'0\'>\n";
    tableinode += "\t<tr><td PORT = \"I"+to_string(indice)+"\" >INODO"+to_string(indice)+"</td></tr>\n";
    tableinode += "\t<tr><td cellpadding=\'4\'>\n";
    tableinode += "\t\t<table color=\'cyan4\' cellspacing=\'0\'>\n";
    //INICIO DE INFORMACION
    tableinode += "\t\t\t<tr><td>Nombre</td><td>Valor</td></tr>\n";
    tableinode += "\t\t\t<tr><td>i_uidt</td><td>";
    tableinode += to_string(inode->i_uid);
    tableinode +="</td></tr>\n";
    tableinode += "\t\t\t<tr><td>i_gid</td><td>";
    tableinode += to_string(inode->i_gid);
    tableinode += "</td></tr>\n";
    tableinode += "\t\t\t<tr><td>i_size</td><td>";
    tableinode += to_string(inode->i_size);
    tableinode += "</td></tr>\n";
    tableinode += "\t\t\t<tr><td>i_atime</td><td>00/00/00</td></tr>\n";
    tableinode += "\t\t\t<tr><td>i_ctime</td><td>00/00/00</td></tr>\n";
    tableinode += "\t\t\t<tr><td>i_mtime</td><td>00/00/00</td></tr>\n";
    for(int i=0;i<15;i++){
        string indiceconexion = (int)inode->i_block[i]>=0?"PORT = \"B"+to_string(i)+"\"":"";
        tableinode += "\t\t\t<tr><td>i_block"+to_string(i)+"</td><td "+indiceconexion+">";
        tableinode += to_string(inode->i_block[i]);
        tableinode += "</td></tr>\n";
        //CONEXIONES INODOS A BLOQUES
        conexionesinodos +=indiceconexion != "" ?"\nInodo"+to_string(indice)+":"+"B"+to_string(i)+" -> Bloque"+to_string(inode->i_block[i])+":BL"+to_string(inode->i_block[i])+";":"";
    }       //InodoA:BB -> BloqueC:BC
    /*
        Donde:
        A = Numero del Inodo en Lectura
        B = Numero del Bloque apuntador del Inodo en Lectura
        C = Numero del Bloque al que apunta el Bloque B
        El siguiente tiene el mismo valor C ya que es para que apunte al encabezado del bloque
    */
    tableinode += "\t\t\t<tr><td>i_type</td><td>";
    tableinode += to_string(inode->i_type);
    tableinode += "</td></tr>\n";
    tableinode += "\t\t\t<tr><td>i_perm</td><td>";
    tableinode += "Si";
    tableinode += "</td></tr>\n";
    //FINAL DE INFORMACION
    tableinode += "\t\t</table>\n";
    tableinode += "\t</td>\n";
    tableinode += "\t</tr>\n";
    tableinode += "\t<tr><td>Inodo</td></tr>\n";
    tableinode += "</table>\n";
    tableinode += " >];\n";

    if(tree){
        tableinode +=  conexionesinodos ;
    }

    return tableinode;
}

//reporte del tree
void repTree(char _id[], char _name[], char _path[],char _dir[]){
    string dir = charToString(_dir);
    string name_dot = dir+charToString(_name)+".dot";

    string graphsuper;
    DISCO disco = buscarDisco(_id);
    //se lee
    FILE *file;
    file = fopen(disco.path,"rb+");
    MBR mbr;
    fseek(file,0,SEEK_SET);
    fread(&mbr,sizeof (MBR),1,file);
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
    string graphInodos="";
    char bit_nodos[num_de_inodos];
    fseek(file,auxsuper.s_bm_inode_start,SEEK_SET);
    fread(&bit_nodos,sizeof(char),num_de_inodos,file);
    //inicia contenidos
    for (int i = 0; i < num_de_inodos; ++i) {
        if(bit_nodos[i]=='1'){
            INODOS inodo_read;
            fseek(file,auxsuper.s_inode_start+i*sizeof (INODOS),SEEK_SET);
            fread(&inodo_read,sizeof (INODOS),1,file);
            graphInodos += InodoTabla(i,&inodo_read,1);
            graphInodos += "\n\n";
        }
    }

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
            allbloques+= BlockFolder_Tabla(i,&readcarpeta,1);
        }else if(bit_bloques[i]=='2'){
            //para archivos
            BLOQUEARCHIVO readarchivo;
            fseek(file,auxsuper.s_block_start+i*64,SEEK_SET);
            fread(&readarchivo,64,1,file);
            allbloques+= BlockFile_Tabla(i,&readarchivo,1);

        }else if(bit_bloques[i]=='3'){
            //para apuntadores
            APUNTADORES readapuntador;
            fseek(file,auxsuper.s_block_start+i*64,SEEK_SET);
            fread(&readapuntador,64,1,file);
            allbloques+= BlockPointer_Tabla(i,&readapuntador,1);
        }
    }

    //finalizando
    string arbol = "digraph {\n rankdir=LR;\n"+graphInodos+"\n\n\n"+allbloques+"\n}\n";
    fclose(file);
    //generar .dot
    ofstream  fs(name_dot);
    fs << arbol<<endl;
    fs.close();

}

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
                if(flag_mbr){
                    repMbr(valor_id,valor_name,valor_path,direc);
                }else if(flag_disk){

                }

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

            }else if(flag_tree){
                //se genera rep del arbol
                repTree(valor_id,valor_name,valor_path,direc);
            }


        }
    }


}
