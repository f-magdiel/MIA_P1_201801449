/*crearemos 8 discos...*/
/*verificar tamaño de discos...*/
MKdisk $size=>120 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d1.dsk 
mkdisK $size=>32 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d2.dsk 
MKdisk $size=>64 $PatH=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d3.dsk 
MKdisk $size=>80 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d4.dsk  
MKdisk $size=>120 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d5.dsk 
MKdisk $size=>8 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d6.dsk 
MKdis $size=>8 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d6.dsk 

/*vamos a verificar si hicieron validaciones con datos incorrectos*/
/*primero el tamaNio tiene numero menor a 0, segundo el 60 no es multiplo de 8*/
MKdisk $size=>-60 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d7.dsk 
MKdisk $size=>60 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d8.dsk 

/*Eliminar discos, solo quedaran 3 discos*/
/*Verificacion de mensaje de confirmacion de eliminacion de discos*/
RMdisk $patH=>"/home/magdiel/Escritorio/archivos/fase1/d5.dsk" 
RMdisk $patH=>"/home/magdiel/Escritorio/archivos/fase1/d4.dsk" 

/*Verificando validaciones con datos incorrectos en el rmdisk*/
/*Deberia de dar error ya que el disco 8 no existe*/
rmDiSK $path=>"/home/magdiel/Escritorio/archivos/fase1/d8.dsk" 

/*Crear 12 particiones del mismo tamaño en el primer disco con ajustes diferentes*/
/*PrimarIA 1 es de 10 Mb*/
/*Todas son de 5 Mb (La extendida es de 50 Mb)*/
/*Tipo:		Primaria	Primaria	Extendida	Logica	Logica	Logica	Logica	Logica	Logica	Logica	Logica Primaria*/
/*Ajuste:	Primer 		Mejor		$			Peor	Peor	Peor	Peor	Peor	Peor	Peor	Mejor   Peor*/
/*Nombre:	PRI 1		PRI 2		EXT			LOG 1	LOG 2	LOG 3	LOG 4	LOG 5	LOG 6	LOG 7	LOG8   PRI 3*/
fdisk $size=>10 @UniT=>M $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" @type=>P @fit=>FF $name=>PRI1 
fdisk $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $size=>5120 @fit=>BF $name=>PRI2 
fdisk $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" @type=>E $name=>EXT $size=>51200 
fdisk @type=>L $size=>5120 @Unit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG1 
fdisK $name=>LOG2 $size=>5120 $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" @type=>L 
fdisk @type=>L $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG3 $size=>5120 @uniT=>K 
fdiSk @type=>L $size=>5120 @unIt=>K $PAth=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG4 
fdisk @type=>L $size=>5120 @unit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG5 
FdisK $size=>5120 $name=>LOG6 @UNit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" @type=>L 
fdIsk @type=>L $size=>5120 @unit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG7 
fdIsk @type=>L $size=>5120 @unit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG8 @fit=>BF 
fdisk @unit=>B $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $size=>5242880 $name=>PRI3 

/*Crearemos las mismas 12 particiones en el tercer disco*/
/*PrimarIA 1 es de 10 Mb*/
/*eL RESTO son de 5 Mb (La extendida es de 50 Mb)*/
/*Tipo:		Primaria	Primaria	Extendida	Logica	Logica	Logica	Logica	Logica	Logica	Logica	Logica Primaria*/
/*Ajuste:	Primer 		Mejor		$			Peor	Peor	Peor	Peor	Peor	Peor	Peor	Mejor   Peor*/
/*Nombre:	PRI 1		PRI 2		EXT			LOG 1	LOG 2	LOG 3	LOG 4	LOG 5	LOG 6	LOG 7	LOG8   PRI 3*/

fdisk $size=>10 @UniT=>M $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" @type=>P @fit=>FF $name=>PRI1 
fdisk $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $size=>5120 @fit=>BF $name=>PRI2 
FdisK $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" @type=>E $name=>EXT $size=>51200 
fdisk @type=>L $size=>5120 @Unit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $name=>LOG1 
fdisK $name=>LOG2 $size=>5120 $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" @type=>L 
fdisk @type=>L $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $name=>LOG3 $size=>5120 @uniT=>K 
fdiSk $size=>5120 @unIt=>K $PAth=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $name=>LOG4 @type=>L 
fdisk @type=>L $size=>5120 @unit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $name=>LOG5 
FdisK $size=>5120 $name=>LOG6 @UNit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" @type=>L 
fdIsk @type=>L $size=>5120 @unit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $name=>LOG7 
fdIsk @type=>L $size=>5120 @unit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $name=>LOG8 @fit=>BF 
fdisk @unit=>B $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $size=>5242880 $name=>PRI3 

/*Verificar generacion de ids al montar*/
/*Debería generar los ids: vda1, vdb1, vda2, vdb2*/
/*vda para el d3.dsk y vdb para d1.dsk*/
mouNt $name=>PRI3 $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" 
moUnt $PAth=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>PRI3 
mOunt $name=>PRI2 $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" 
mouNt $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>PRI2 

/*Validaciones al montar, no deberia cargarlos*/
moUnt $name=>PX $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" 
/*moUNt $path=>"/home/magdiel/Escritorio/archivos/fase1/DX.dsk" $name=>PRI3*/ 

/*Listar las particiones montadas*/
mouNt 
/*SAlida es la siguiente*/
/*id=>vda1 $path=>"/home/magdiel/Escritorio/archivos/fase1/D3.dsk" $nOMbRe=>"PRI 3"*/
/*id=>vdb1 $PAth=>"/home/magdiel/Escritorio/archivos/fase1/D1.dsk" $nOMbRe=>"PRI 3"*/
/*id=>vda2 $path=>"/home/magdiel/Escritorio/archivos/fase1/D3.dsk" $nOMbRe=>"PRI 2"*/
/*id=>vdb2 $path=>"/home/magdiel/Escritorio/archivos/fase1/D1.dsk" $nOMbRe=>"PRI 2"*/

/*Reporte de las particiones del disco*/
/*Debe crear la carpeta de reportes*/
rep $name=>disk $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte1_Disco_Disco3.jpg" $id=>vda1 
rep $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte1_disco_Disco1.jpg" $id=>vdb1 $name=>disk 
rep $name=>mbr $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte1_MBR_Disco3.jpg" $id=>vda1 
rep $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte1_MBR_Disco1.jpg" $id=>vdb1 $name=>mbr 

/*Vericamos la eliminación*/
/*Elimina la primaria 2, logica 1, logica 2 y logica 5 del disco 1*/
/*Queda así: P1 EXT L2 L3 L6 L7 L8 P3*/
fdisk @delete=>Fast $name=>PRI2 $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" 
fdisk $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG1 @delete=>FasT 
fDisk $name=>LOG4 @delete=>FaST $PAth=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" 
fdisK $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG5 @delete=>FAsT 

/*Tambien elimina la partición extendida y la primaria 1 del disco 3*/
/*Verificar que no queden EBRs*/
/*Queda así: P2 P3*/
fDisk $DELete=>Full $name=>EXT $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" @Delete=>Full 
fdisk @Delete=>Full $name=>PRI1 @Delete=>Full $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" 

/*Reporte con particiones eliminadas*/
rep $id=>vda1 $name=>disk $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte2_disco_Disco3.jpg" 
rep $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte2_disco_Disco1.jpg" $name=>disk $id=>vdb1 
rep $name=>mbr $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte2_MBR_Disco3.jpg" $id=>vda1 
rep $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte2_MBR_Disco1.jpg" $id=>vdb1 $name=>mbr 

/*TEORIA DE PARTICIONES, (solo una extendida) debería dar error*/
fdisk $size=>2048 $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" @type=>E $name=>EXT2 

/*Verificar PRIMER AJUSTE creando de nuevo las particiones*/
/*Debe quedar de la siguiente forma:*/
/*Disco1: PRIMARIA1 PRIMARIA2 EXTENDIDA LOGICA1 LOGICA2 LOGICA3 LOGICA45 LOGICA6 LOGICA7 LOGICA8 PRIMARIA3*/
fdiSk @unit=>M $size=>5 $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" @type=>P @fit=>FF $name=>PRI2 
fdisk $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $size=>10240 @type=>L $name=>LOG45 @unit=>K 
fdisk $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $size=>5120 @type=>L $name=>LOG1 @unit=>K 


/*Disco 3: Primaria2 EXTENDIDA LOGICA1 PRIMARIA1 PRIMARIA3*/
fdisk @type=>E $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" $size=>10240 $name=>EXT 
fdiSk $name=>LOG1 @unit=>K $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" @type=>L $size=>5120 
fdisk $size=>10240 $name=>PRI1 $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" @type=>P 

/*Reporte de las particiones del disco*/
Rep $Path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte3_disco_Disco3.jpg" $id=>vda1 $name=>disk 
rep $name=>disk $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte3_disco_Disco2.jpg" $id=>vdb1 

/*Validaciones al crear o quitar espacio*/
/*No deberia ejecutar estas instrucciones*/
/*(porque no hay espacio después)*/
/*fdisk $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>PRI1 @add=>3*/
/*(porque no debe quedar espacio negativo) debe mostrar mensaje de cuanto puede quitarle*/
/*fdisk @add=>-20 @unit=>M $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>PRI1 @unit=>M */
/*(Porque no hay suficiente espacio)*/
fdisk @unit=>M $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>LOG7 @add=>150 

/*Quita y agrega 1 mb de la primer particion*/
/*fdisk @unit=>M $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>PRI1 @add=>-2*/  
rep $name=>Mbr $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte4_MBR_Espacio_Disco1.jpg" $id=>vdb2 
*/fdisk @unit=>M $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>PRI1 @add=>2*/ 
rep $name=>Mbr $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte5_MBR_Espacio_Disco1.jpg" $id=>vdb2 
/*Le quita 1 mb a la partición logica*/
/*fdisk @unit=>M $path=>"/home/magdiel/Escritorio/archivos/fase1/D1.dsk" $nOMbRe=>"LOG 45" @add=>$1*/
/*rep $nOMbRe=>Mbr $path=>"/home/magdiel/Escritorio/archivos/fase1/reportes/Reporte6_Espacio_MBR Disco1.jpg" $id=>vdb2*/

/*desmontar una lista de ids
unmount $id=>vda1 
unmount $id=>vdb2 
unmount $id=>vda2 
/*para corroborar que desmonto hacer un mount para listar las particiones montadas*/
mount 
/*Salida es la siguiente*/
/*id=>vdb1 $PAth=>"/home/magdiel/Escritorio/archivos/fase1/D1.dsk" $nOMbRe=>"PRI 3"*/
