import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class RegistroService {

  private URL = 'http://localhost:3000'
  constructor(private http:HttpClient) { }

  //para registrarse
  postUser(user:any){
    return this.http.post<any>(this.URL+'/register',user);
    
  }

  //para logearse
  loginUser(data:any){
    return this.http.post<any>(this.URL+'/login',data);
  }

  //para mandar el json
  postInsertJson(carpetas:any){
    return this.http.post<any>(this.URL+'/insertarJson',carpetas);
  }

  //para obtener todas las carpetas
  getAllCarpetas(){
    return this.http.get<any>(this.URL+'/allCarpetas');
  }
  //para agregar prop 
  addPropietario(propietario:any){
    return this.http.post<any>(this.URL+'/addPropietario',propietario);
  }
  //para obtener y mostrar todas la cuentas
  getAllUsers(){
    return this.http.get<any>(this.URL+'/allUsers');
  }

  //para cambiar estado cuenta
  changeEstadoCuenta(cuenta:any){
    return this.http.post<any>(this.URL+'/changeCuenta',cuenta);
  }

  //para crear carpeta por un usuario
  createCarpetaByUser(carpeta:any){
    return this.http.post<any>(this.URL+'/createCarpeta',carpeta);
  }

  //para eliminar carpeta por un usuario
  deleteCarpetaByUser(carpeta:any){
    return this.http.post<any>(this.URL+'/deleteCarpeta',carpeta);
  }
}
