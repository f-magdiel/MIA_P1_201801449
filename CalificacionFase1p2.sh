/*Debería generar los ids: vda1, vdb1, vda2, vdb2, vda3, vdb3*/
/*vda para el D3.dsk y vdb para d1.dsk*/
mouNt $NamE=>PRI1 $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" 
mouNt $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $NamE=>PRI1 
moUnt $PAth=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $name=>PRI2 
moUnt $name=>PRI2 $PAth=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" 
mOunt $name=>LOG1 $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk"  
mouNt $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG1 
mount
/*Crea el sistema de archivos EXT3 en todas las particiones primarias PRI1*/ 
mkfs $id=>vdb1 @type=>Full 
/*Mkfs $id=>vdb1*/ 
/*Crea el sistema de archivos EXT3 en todas las particiones Logicas*/
/*mkfs $id=>vda3 @type=>Full*/ 
/*Mkfs $id=>vdb3 @type=>FasT*/
/*Crearemos la ruta y las padres que no existan
mkdir $id=>vdb1 $path=>"/home/user/mia/fase1" @p 


rep $NAMe=>sb $patH=>"/home/magdiel/Escritorio/archivos/reportes/sb01.jpg" $id=>vdb1 
rep $NamE=>journaling $patH=>"/home/magdiel/Escritorio/archivos/reportes/bitacora01.jpg" $id=>vdb1 
rep $NAME=>tree $patH=>"/home/magdiel/Escritorio/archivos/reportes/directorio01UsoApuntadoresCarpetas.jpg" $id=>vdb1 
rep $nAmE=>block $Path=>"/home/magdiel/Escritorio/archivos/reportes/block.jpg" $id=>vdb1 
rep $nAmE=>inode $Path=>"/home/magdiel/Escritorio/archivos/reportes/inode.jpg" $id=>vdb1 
rep $nAmE=>bm_inode $Path=>"/home/magdiel/Escritorio/archivos/reportes/bm_inode01.jpg" $id=>vdb1 
rep $NaMe=>bm_block $Path=>"/home/magdiel/Escritorio/archivos/reportes/bm_block01.jpg" $id=>vdb1 
/*uso de bloques e inodos*/

