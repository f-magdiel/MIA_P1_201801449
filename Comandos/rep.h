#ifndef MIA_P1_201801449_REP_H
#define MIA_P1_201801449_REP_H

#include "../Estructuras/INODOS.h"
#include "../Estructuras/BLOQUECARPETA.h"
#include "../Estructuras/BLOQUEARCHIVO.h"
#include "../Estructuras/APUNTADORES.h"
#include <istream>

using namespace std;
void analisisRep(char []);
bool validacionReporte(char []);
bool validacionDirectorioReporte(char []);
void repTree(char [],char [], char [],char []);
void repSuper(char[],char [], char [],char []);
void repBitmapInode(char [],char [],char [],char []);
void repBitmapBlock(char [],char [],char [],char []);
void repInodos(char [],char [],char [],char []);
void repBlock(char [],char [],char [],char []);
void repJournaling(char [],char [],char [],char []);

string InodoTabla(int indice,INODOS * inode,int tree);
string BlockFolder_Tabla(int indice,BLOQUECARPETA *blockfolder,int tree);
string BlockFile_Tabla(int indice,BLOQUEARCHIVO *blockfile,int tree);
string BlockPointer_Tabla(int indice,APUNTADORES *blockpointer,int tree);


#endif //MIA_P1_201801449_REP_H
