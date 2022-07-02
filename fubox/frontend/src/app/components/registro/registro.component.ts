import { Component, OnInit } from '@angular/core';
import {FormControl, Validators} from '@angular/forms';
import { RegistroService } from 'src/app/services/registro.service';
import Swal from 'sweetalert2';

@Component({
  selector: 'app-registro',
  templateUrl: './registro.component.html',
  styleUrls: ['./registro.component.css']
})

export class RegistroComponent implements OnInit {
  
  
  constructor(private registroform: RegistroService) { }

  ngOnInit(): void {
  }

  email = new FormControl('', [Validators.required, Validators.email]);

  getErrorMessage() {
    if (this.email.hasError('required')) {
      return 'You must enter a value';
    }

    return this.email.hasError('email') ? 'Not a valid email' : '';
  }
  //modelo para recibir los valores del usuario
  user = {
    nombre:'',
    apellido:'',
    usuario:'',
    correo:'',
    telefono:'',
    clave:'',
    fecha_nacimiento:'',
    fecha_creacion:'03/07/2022',
    estado_cuenta:0,
    contador:0,
    contenido:[]
  }
 
  addUser(){
    
    //hacer peticion al servidor de agregar
   this.registroform.postUser(this.user)
   .subscribe(
    res => {
      
      if(res.validate==true){
        Swal.fire({
          icon: 'success',
          title: 'Registrado',
          text: 'Cuenta creada',
        })
      }else{
        Swal.fire({
          icon: 'error',
          title: 'Cuenta duplicada',
          text: 'No se puede crear cuenta',
        })
      }
      
      
    },
    err => {
      Swal.fire({
        icon: 'error',
        title: 'No se pudo registrar',
        text: 'No se creo cuenta',
      })
    }
   )
  }

  

}
