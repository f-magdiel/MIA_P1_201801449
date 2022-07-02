import { Component, OnInit } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';
import { EnviodatosService } from 'src/app/services/enviodatos.service';
import { Router } from '@angular/router';
import Swal from 'sweetalert2';
let datauser:any;
@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  
  constructor(private loginForm: RegistroService, private _router:Router,private sendDatos:EnviodatosService) { }

  ngOnInit(): void {
  }
  //guardar datos user
  

  //modelo user login
  data={
    usuario:'',
    clave:''
  }
  
  validationLogin(){
    
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
          this._router.navigate(['/panelusuario',res.usuarios.usuario])
        }else{
          Swal.fire({
            icon: 'error',
            title: 'Inicio de Sesión',
            text: 'Error de inicio de Sesión',
          })
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
