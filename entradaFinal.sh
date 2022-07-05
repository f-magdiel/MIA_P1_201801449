/*verificar tamaño de discos...*/
MKdisk $size=>120 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d1.dsk 
mkdisK $size=>32 $path=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d2.dsk 
MKdisk $size=>64 $PatH=>"/home/magdiel/Escritorio/archivos/fase1/" $name=>d3.dsk 


/* se realizan las particiones*/
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

mouNt $name=>PRI3 $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" 
moUnt $PAth=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>PRI3 
mOunt $name=>PRI2 $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" 
mouNt $path=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" $name=>PRI2 
moUnt $name=>PX $path=>"/home/magdiel/Escritorio/archivos/fase1/d3.dsk" 

mount 

/*raid se elimina un disco*/
RMdisk $patH=>"/home/magdiel/Escritorio/archivos/fase1/d1.dsk" 
RMdisk $patH=>"/home/magdiel/Escritorio/archivos/fase1/d2.dsk" 

mount 

/*se crea el sistema de archvios*/ 
mkfs $id=>vda2 @type=>Full 

mkdir $id=>vda2 $path=>"/home/user/mia/fase1" @p 
mkdir $id=>vda2 $path=>"/home/user/mia/carpeta2" 
mkdir $id=>vda2 $path=>"/home/user/mia/fase1/a1" 
mkdir $id=>vda2 $path=>"/home/user/mia/fase1/a2" 
mkdir $id=>vda2 $path=>"/home/user/mia/fase1/a3" 
mkdir $id=>vda2 $path=>"/home/user/mia/fase1/a4" 
mkdir $id=>vda2 $path=>"/home/user/mia/fase1/a5" 


/* se crean los archivos*/
mkfile $id=>vda2 $path=>"/home/user/mia/carpeta2/inicio.txt" @p 
mkfile $id=>vda2 $path=>"/home/user/mia/fase1/a1/a1.txt" 
mkfile $id=>vda2 $path=>"/home/user/mia/fase1/a2/a2.txt" 
mkfile $id=>vda2 $path=>"/home/user/mia/fase1/a3/a3.txt" 
mkfile $id=>vda2 $path=>"/home/user/mia/fase1/a4/a4.txt" 
mkfile $id=>vda2 $path=>"/home/user/mia/fase1/a5/a5.txt" 

/*se crean los reportes*/

rep $NAME=>tree $patH=>"/home/magdiel/Escritorio/archivos/reportes/directorio01UsoApuntadoresCarpetas.jpg" $id=>vda2  

/* se genera el json*/
syncronice @id=>vda2 @path=>"home/magdiel/Escritorio/archivos/reportes/salida.json" 

