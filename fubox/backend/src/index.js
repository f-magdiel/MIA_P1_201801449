const express = require('express');
var bodyParser = require('body-parser')

const app = express();
app.use(bodyParser.json());
const port = process.env.PORT || 8080;

//al inicio
app.get('/',function(req,res){
    res.send('hola mundo')
});

//para login

//para registro

//para admin
var obj;
//para leer el json 

app.post('/readjson',function(req,res){
    obj = req.body;//se guarda el objeto json
    //mensaje para responder
    res.send({
        "ok":200
    })
    estructurarCarpetas(obj)
}) 

var inodo='Inodo0';
//siempre don dos parametros Inodo,Bloque
function estructurarCarpetas(inodo,bloque,obj){
    //se empieza a buscar en inodo0

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
