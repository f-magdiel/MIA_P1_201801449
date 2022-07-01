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
          console.log(usuario+""+clave)
          if(jsonusuarios.length!=0){
            for(let i in jsonusuarios.usuarios){
              console.log(jsonusuarios.usuarios[i].usuario)
              if(usuario == jsonusuarios.usuarios[i].usuario && clave == jsonusuarios.usuarios[i].clave){
                  datoscompletos = jsonusuarios.usuarios[i];
                  flag_res = false;
                  return res.send({
                    datoscompletos,
                      "estado":200,
                      "validate":true
                  });
                  
              }
            }
          }
    
          if(flag_res){
            res.send({
              "estado":400,
              "validate":false
            });
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
                                  "tipo":'0'
                                }
                                dataJsonSalida.carpetas.push(carpeta)
                                estructurarCarpetas(obj.Bloques[j].Inodo,obj);
                                
                            }else{
                                console.log("Es carpeta--"+obj.Bloques[j].Name)
                                //se estructura un obj
                                carpeta ={
                                  "nombre":obj.Bloques[j].Name,
                                  "propietario":'',
                                  "tipo":'1'
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
}
  
module.exports = userRoutes;