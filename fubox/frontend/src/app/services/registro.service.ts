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
}
