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
function estructurarCarpetas(obj){
    //se empieza a buscar en inodo0

    for(var num in obj.Inodos){
        console.log(obj.Inodos[num])
    }

}


//funcion para recorrer el json


app.listen(port);
console.log('Server started at http://localhost:' + port);
