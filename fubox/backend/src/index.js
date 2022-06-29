const express = require('express');
var bodyParser = require('body-parser');
const Lista = require('./Estructura');

const app = express();
app.use(bodyParser.json());
const port = process.env.PORT || 8080;

//al inicio
app.get('/',function(req,res){
    res.send('hola mundo')
});

//inicio la lista
let listaCarpeta = new Lista();

//para login

//para registro

//para admin
var obj;
//para leer el json 

app.post('/readjson',function(req,res){
    obj = req.body;//se guarda el objeto json
    //mensaje para responder
    estructurarCarpetas(obj.Inodos[0].Inodo,obj)
    res.send({
        "ok":200
    })
    //console.log("A mandar "+obj.Inodos[0].Inodo)
    
}) 

var inodo='Inodo0';
//siempre don dos parametros Inodo--> para inicializar
function estructurarCarpetas(inodo,obj){
    //se empieza a buscar en inodo0
   
    let bloquebuscar;
    for(let i in obj.Inodos){
        //console.log(obj.Inodos[i].Inodo)
        if(inodo==obj.Inodos[i].Inodo){
            
            bloquebuscar = obj.Inodos[i].Bloque;
            //busco las 4 veces en bloques
            for(let j in obj.Bloques){
                if(bloquebuscar==obj.Bloques[j].Bloque){
                    //valido que no sea .,..,"","-"
                    if('.'!=obj.Bloques[j].Name && '..'!=obj.Bloques[j].Name && '-'!=obj.Bloques[j].Name && ""!=obj.Bloques[j].Name){
                        //console.log("Se agrega  "+obj.Bloques[j].Name)
                        
                        if(obj.Bloques[j].Name.includes('.txt')){
                            console.log("Es archivo--"+obj.Bloques[j].Name)
                            listaCarpeta.add(obj.Bloques[j].Name,'0')
                            estructurarCarpetas(obj.Bloques[j].Inodo,obj);
                            
                        }else{
                            console.log("Es carpeta--"+obj.Bloques[j].Name)
                            listaCarpeta.add(obj.Bloques[j].Name,'1')
                            estructurarCarpetas(obj.Bloques[j].Inodo,obj);
                            
                        }
                    }
                }
            }
        } 
    }

    /* for(var num in obj.Inodos){
        var inodobusar = obj.Inodos[num].Inodo
        var bloquebuscar = obj.Inodos[num].Bloque
        for(var i in obj.Bloques){
            if(inodobusar==obj.Bloques[i].Inodo){//encuetro en inodo
                console.log(obj.Bloques[i].Bloque)
                console.log(obj.Bloques[i].Bloque)
                console.log(obj.Bloques[i].Bloque)
                console.log(obj.Bloques[i].Bloque)
            }
        }
    } */

}


app.listen(port);
console.log('Server started at http://localhost:' + port);
