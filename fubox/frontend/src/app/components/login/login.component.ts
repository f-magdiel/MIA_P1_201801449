import { Component, OnInit } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';
import { Router } from '@angular/router';
import Swal from 'sweetalert2';
let datauser:any;
@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent implements OnInit {
  
  constructor(private loginForm: RegistroService, private _router:Router) { }

  ngOnInit(): void {
  }
  //guardar datos user
  

  //modelo user login
  data={
    usuario:'',
    clave:''
  }
  
  validationLogin(){
    console.log(this.data)
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
          this._router.navigate(['/panelusuario'])
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
