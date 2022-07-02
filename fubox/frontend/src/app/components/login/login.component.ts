import { Component, OnInit } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';
import { EnviodatosService } from 'src/app/services/enviodatos.service';
import { Router } from '@angular/router';
import { CookieService } from 'ngx-cookie-service';
import Swal from 'sweetalert2';
let datauser:any;
@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  
  constructor(private loginForm: RegistroService, private _router:Router,private sendDatos:EnviodatosService,private cookiserv:CookieService) { }

  ngOnInit(): void {
  }
  //guardar datos user
  

  //modelo user login
  data={
    usuario:'',
    clave:''
  }
  reset={
    usuario:''
  }
  
  validationLogin(){
    
   if(this.data.clave=='admin' && this.data.usuario=='admin'){
    Swal.fire({
      icon: 'success',
      title: 'Inicio de Sesión',
      text: 'Sesión iniciado',
    })
    this.cookiserv.set('token_acces','123456789',1,'/')
    this._router.navigate(['/paneladmin'])
   }else{
    this.loginForm.loginUser(this.data)
    .subscribe(
      res =>{
        if(res.validate){
          datauser = res
          
          Swal.fire({
            icon: 'success',
            title: 'Inicio de Sesión',
            text: 'Sesión iniciado',
          })
          this.cookiserv.set('token_acces_user','1234567891012131415',1,'/')
          this._router.navigate(['/panelusuario',res.usuarios.usuario])
        }else{
          Swal.fire({
            icon: 'error',
            title: 'Inicio de Sesión',
            text: 'Error de inicio de Sesión',
          })
          this._router.navigate(['/accesodenegado'])
        }
      },
      err =>{
        Swal.fire({
          icon: 'error',
          title: 'Inicio de Sesión',
          text: 'Error de petición',
        })
      }
    )
   }
    
  }

  resetClave(){
    this.loginForm.solicitarChange(this.reset)
    .subscribe(
      res=>{
        console.log(res)
        Swal.fire({
          icon: 'success',
          title: 'Solicitud',
          text: 'La solicitud se ha enviado al admin para reset clave',
        })
      }
    )
  }


}
