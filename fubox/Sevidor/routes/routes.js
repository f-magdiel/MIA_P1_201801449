const { json } = require("express");

const userRoutes = (app, fs) => {
    const path = './db.json'

    //para monstrar todas las carpetas
    app.get('/carpetas', (req, res) => {
        fs.readFile(path, 'utf8', (err, data) => {
          if (err) {
            throw err;
          }
          let aux = JSON.parse(data)
          console.log(aux.carpetas)
    
          res.send(aux.carpetas);
        });
      });


    //para agregar user
    app.post('/register',(req,res)=>{
        fs.readFile(path, 'utf8', (err, data) => {
            // Note: this needs to be more robust for production use. 
            // e.g. use a UUID or some kind of GUID for a unique ID value.
            //const newUserId = Date.now().toString();
        
            // add the new user
            //console.log(data)
            let flag_repeat = false;
            let username = req.body.usuario; 
            let datajson = JSON.parse(data);
            //valido que no hay datos
            
            if(datajson.usuarios.length!=0){
                for(let i in datajson.usuarios){
                    if(username===datajson.usuarios[i].usuario){
                        res.send({
                            "estado":400,
                            "validate":false
                        })
                        flag_repeat=true;
                        break;
                    }
                } 
            }

            if(flag_repeat==false){
                datajson.usuarios.push(req.body);
                data = JSON.stringify(datajson);
           
                fs.writeFile(path,data,(err) => {
                   
                  res.send({
                        "estado":200,
                        "validate":true
                    })
                });
            }

          }, true);
    })

    //login para user
    app.post('/login', (req, res) => {
        fs.readFile(path, 'utf8', (err, data) => {
          if (err) {
            throw err;
          }
          let flag_res = true;
          const {usuario,clave} = req.body;
          let jsonusuarios = JSON.parse(data)
          let datoscompletos;
          
          if(jsonusuarios.length!=0){
            for(let i in jsonusuarios.usuarios){
              //el user ingresas sus datos correctos
              if(usuario == jsonusuarios.usuarios[i].usuario && clave == jsonusuarios.usuarios[i].clave){
                  //esta dado de alta
                  if(jsonusuarios.usuarios[i].estado_cuenta==1){
                    datoscompletos = jsonusuarios.usuarios[i];
                  flag_res = false;
                  return res.send({
                    "usuarios":datoscompletos,
                      "estado":200,
                      "validate":true
                  });
                  }else{
                    return res.send({
                      datoscompletos,
                        "estado":400,
                        "validate":false
                    });
                  }
                  
              }else if(usuario == jsonusuarios.usuarios[i].usuario && clave != jsonusuarios.usuarios[i].clave){//user correcto pero pass no
                console.log("solo user corecto")
                let num = jsonusuarios.usuarios[i].contador
                num = 1 +num
                jsonusuarios.usuarios[i].contador = num
                console.log(jsonusuarios.usuarios[i].contador)
                
                //si es igual a 3 valio el inicio se sesion
                if(jsonusuarios.usuarios[i].contador==3){
                  jsonusuarios.usuarios[i].estado_cuenta = 0
                }
              }
            }
          }
    
          if(flag_res){
            data = JSON.stringify(jsonusuarios)
            fs.writeFile(path,data,(err)=> {
              res.send({
                "status":400,
                "validate":false
                })
              })
          }
        });
      });

      //para validar el jsonde entrdada<----------->
      
      let dataJsonSalida;
      app.post('/insertarJson',(req,res)=>{
        fs.readFile(path,'utf8',(err,data)=>{
          let jsonSalida = req.body//se obtiene el req
          dataJsonSalida = JSON.parse(data)//se obtiene la data
          //se realizar la funcion recursiva para agregar las carpetas y archivos
        estructurarCarpetas(jsonSalida.Inodos[0].Inodo,jsonSalida)
        data = JSON.stringify(dataJsonSalida)
        
        fs.writeFile(path,data,(err)=> {
          res.send({
            "status":200,
            "validate":true
            })
          })
        })
        

        
      })

      //funcion recursiva
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
                                //se estructura un obj
                                carpeta ={
                                  "nombre":obj.Bloques[j].Name,
                                  "propietario":'',
                                  "tipo":'0',
                                  "colaborador":[]
                                }
                                dataJsonSalida.carpetas.push(carpeta)
                                estructurarCarpetas(obj.Bloques[j].Inodo,obj);
                                
                            }else{
                                console.log("Es carpeta--"+obj.Bloques[j].Name)
                                //se estructura un obj
                                carpeta ={
                                  "nombre":obj.Bloques[j].Name,
                                  "propietario":'',
                                  "tipo":'1',
                                  "colaborador":[]
                                }
                                dataJsonSalida.carpetas.push(carpeta)
                                estructurarCarpetas(obj.Bloques[j].Inodo,obj);
                                
                            }
                        }
                    }
                }
            } 
        }
    
    }

    //para consultar todas las carpetas
    app.get('/allCarpetas',(req,res)=>{
      fs.readFile(path,'utf8',(err,data)=>{
        if(err){
          throw err;
        }
        let aux = JSON.parse(data)
        res.send({
          "carpetas":aux.carpetas
        })
      })
    })



    //para agregar proprietario carpetas
  app.post('/addPropietario',(req,res)=>{
    fs.readFile(path,'utf8',(err,data)=>{
      if(err){
        throw err;
      }
      const {nombre,propietario}=req.body;
      let aux = JSON.parse(data)
      //se busca nombre carpetas
      for(let i in aux.carpetas){
        if(aux.carpetas[i].nombre==nombre){
          aux.carpetas[i].propietario = propietario
          //se escribe el json 
          data = JSON.stringify(aux)
          fs.writeFile(path,data,(err)=> {
            res.send({
              "status":200,
              "validate":true
              })
            })
        }
      }
    })
  })

  //para mostrar todos los usuarios
  app.get('/allUsers',(req,res)=>{
    fs.readFile(path,'utf8',(err,data)=>{
      if(err){
        throw err;
      }
      let aux = JSON.parse(data)
      res.send({
        "usuarios":aux.usuarios
      })
    })
  })


  //para cambiar el estado de cuenta
app.post('/changeCuenta',(req,res)=>{
  fs.readFile(path,'utf8',(err,data)=>{
    if(err){
      throw err;
    }
    console.log(req.body)
    let flag_error=true;
    let nombreusuario = req.body.nombre
    let aux = JSON.parse(data)
    for(let i in aux.usuarios){//se busca la cuenta para cambiar de estado
      if(nombreusuario==aux.usuarios[i].usuario){
        if(aux.usuarios[i].estado_cuenta==1){//estado cuenta activa se desactiva
          aux.usuarios[i].estado_cuenta = 0
          flag_error=false;
          data = JSON.stringify(aux)
          fs.writeFile(path,data,(err)=> {
            res.send({
              "status":200,
              "validate":true
              })
            })
            break
        }else{
          flag_error=false;
          aux.usuarios[i].estado_cuenta = 1
          data = JSON.stringify(aux)
          fs.writeFile(path,data,(err)=> {
            res.send({
              "status":200,
              "validate":true
              })
            })
            break
        }
      }
    }

    //para error
    if(flag_error){
      res.send({
        "status":400,
        "validate":false
        })
    }
  })
})

//crear carpetas por usuarios
app.post('/createCarpeta',(req,res)=>{
  fs.readFile(path,'utf8',(err,data)=>{
    if (err) {
      throw err;
    }
    //estructura carpeta
    carpeta={
      "nombre":req.body.nombre,
      "propietario":req.body.propietario,
      "tipo":req.body.tipo,
      "colaborador":[]
    }
    
    let jsoncarpetas = JSON.parse(data)
    jsoncarpetas.carpetas.push(carpeta)
    data = JSON.stringify(jsoncarpetas)
    fs.writeFile(path,data,(err)=> {
      res.send({
        "status":200,
        "validate":true
        })
      })

  })
})

//eliminar carpeta o archivo por usuario
app.post('/deleteCarpeta',(req,res)=>{
  fs.readFile(path,'utf8',(err,data)=>{
    if (err) {
      throw err;
    }
    let namecarpeta = req.body.nombre
    let jsonsalida = JSON.parse(data)

    //buscar carepta a eliminar
    for(let i in jsonsalida.carpetas){
      if(jsonsalida.carpetas[i].nombre==namecarpeta){
        jsonsalida.carpetas[i].nombre=''
        jsonsalida.carpetas[i].propietario=''
        jsonsalida.carpetas[i].tipo = ''
        data = JSON.stringify(jsonsalida)
        fs.writeFile(path,data,(err)=> {
          res.send({
            "status":200,
            "validate":true
            })
          })
          break
      }
    }
  })
})

//para agregar colaborador
app.post('/addColaborador',(req,res)=>{
  fs.readFile(path,'utf8',(err,data)=>{
    if (err) {
      throw err;
    }
    colab ={
      usuario:''
    }
    let jsonSalida = JSON.parse(data)
    let usuario;
    let carpeta = req.body.carpeta
    let correo = req.body.correo
    //buscar usuario primero y mandarle correo
    for(let i in jsonSalida.usuarios){
      if(jsonSalida.usuarios[i].correo == correo){
        colab.usuario = jsonSalida.usuarios[i].usuario
        mail={
          mensaje:'Has sido agregado a un carpeta => '+carpeta
        }
        jsonSalida.usuarios[i].contenido.push(mail)
        break
      }
    }

    //buscar carpeta y agregar colaborador
    for (let j in jsonSalida.carpetas){
        if(jsonSalida.carpetas[j].nombre==carpeta){
          jsonSalida.carpetas[j].colaborador.push(colab)
          data = JSON.stringify(jsonSalida)
        fs.writeFile(path,data,(err)=> {
          res.send({
            "status":200,
            "validate":true
          })
        })
        break
        }
    }

  })
})

//finalizar colaboracion
app.post('/finColaboracion',(req,res)=>{
  fs.readFile(path,'utf8',(err,data)=>{
    if (err) {
      throw err;
    }
    fincolab={
      carpeta:req.body.carpeta,
      usuario:req.body.usuario
    }
    

    let jsonSalida = JSON.parse(data)

    for(let i in jsonSalida.carpetas){
      if(jsonSalida.carpetas[i].nombre==fincolab.carpeta){
        for(let j in jsonSalida.carpetas[i].colaborador){
          if(jsonSalida.carpetas[i].colaborador[j].usuario==fincolab.usuario){
            jsonSalida.carpetas[i].colaborador[j].usuario = ''
            break
          }
        }
      }
    }

    // se guarda
    data = JSON.stringify(jsonSalida)
        fs.writeFile(path,data,(err)=> {
          res.send({
            "status":200,
            "validate":true
          })
        })

  })
})

//para obtener los correos del user
app.post('/getMails',(req,res)=>{
  fs.readFile(path,'utf8',(err,data)=>{
    if (err) {
      throw err;
    }
    //obtendo el req
    let usuario = req.body.usuario
    let jsonSalida = JSON.parse(data)
    console.log(usuario)
    //busco el user y retorno el data
    for(let i in jsonSalida.usuarios){
      if(jsonSalida.usuarios[i].usuario==usuario){
        res.send({
          "correo":jsonSalida.usuarios[i].contenido
        })
        break
      }
    }

  })
})

//para reset pass
app.post('/solicitudClave',(req,res)=>{
  fs.readFile(path,'utf8',(err,data)=>{
    if (err) {
      throw err;
    }
    let usuario = req.body.usuario
    //busco usuario
    let jsonSalida = JSON.parse(data)
    for(let i in jsonSalida.usuarios){
      if(jsonSalida.usuarios[i].usuario==usuario){
        //se cambia estado
        jsonSalida.usuarios[i].estado_cuenta = 2//para soliictar cambio pass
        data = JSON.stringify(jsonSalida)
        fs.writeFile(path,data,(err)=> {
          res.send({
            "status":200,
            "validate":true
          })
        })

        break
      }
    }
  })
})

//resetar clave por admin
app.post('/resetClave',(req,res)=>{
  fs.readFile(path,'utf8',(err,data)=>{
    if (err) {
      throw err;
    }
    let usuario = req.body.usuario
    //busco usuario le cambio pass y mando correo
    let jsonSalida = JSON.parse(data)

    for(let i in jsonSalida.usuarios){
      if(jsonSalida.usuarios[i].usuario==usuario){
        //encuentro
        mail = {
          mensaje:"Se ha restablecido su clave: clave nuevo es 1234 tiene un 5m de tiempo"
        }
        jsonSalida.usuarios[i].clave='1234'
        jsonSalida.usuarios[i].contenido.push(mail)
        jsonSalida.usuarios[i].estado_cuenta = 1
        //se cierra y guarda
        data = JSON.stringify(jsonSalida)
        fs.writeFile(path,data,(err)=> {
          res.send({
            "status":200,
            "validate":true
          })
        })

        break
      }
    }

  })
})

}


  
  
module.exports = userRoutes;