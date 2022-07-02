import { Component, OnInit } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';
import Swal from 'sweetalert2';
@Component({
  selector: 'app-gestoruser',
  templateUrl: './gestoruser.component.html',
  styleUrls: ['./gestoruser.component.css']
})
export class GestoruserComponent implements OnInit {
  arrayUser:any=[]
  constructor(private serviceConsult:RegistroService) { }

  ngOnInit(): void {
    this.consultaUser()
  }
  usuario={
    nombre:''
  }

  reset={
    usuario:''
  }

  consultaUser(){
    this.serviceConsult.getAllUsers()
    .subscribe(
      res=>{
        console.log(res)
        for(let i in res.usuarios){
          this.arrayUser.push(res.usuarios[i])
        }
      }
    )
  }

  cambiarEstadoCuenta(){
    this.serviceConsult.changeEstadoCuenta(this.usuario)
    .subscribe(
      res=>{
        if(res.validate){
          Swal.fire({
            icon: 'success',
            title: 'Cambio estado de cuenta',
            text: 'Cambiado exitosamente',
          })
        }else{
          Swal.fire({
            icon: 'error',
            title: 'Error',
            text: 'Usuario no disponible',
          })

        }
      }
    )
  }

  resetClave(){
    this.serviceConsult.resetClave(this.reset)
    .subscribe(
      res=>{
        console.log(res)
        Swal.fire({
          icon: 'success',
          title: 'Reset Clave',
          text: 'Se ha reseteado la clave del usuario',
        })
      }
    )
  }

}
