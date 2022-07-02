import { Component, OnInit,Input } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';
import { EnviodatosService } from 'src/app/services/enviodatos.service';
import Swal from 'sweetalert2';
@Component({
  selector: 'app-sistemausuario',
  templateUrl: './sistemausuario.component.html',
  styleUrls: ['./sistemausuario.component.css']
})
export class SistemausuarioComponent implements OnInit {
  @Input() dataEntrante:any
  constructor(private registroService:RegistroService,private sendDatos:EnviodatosService) { }
  arrayResult:any=[]
  nameuser:any
  ngOnInit(): void {
    this.getSistemaUsuario()
  }

  eliminarCarpeta={
    nombre:''
  }

  crearCarpeta={
    nombre:'',
    propietario:'',
    tipo:0
  }

  getSistemaUsuario(){
    this.registroService.getAllCarpetas()
    .subscribe(
      res =>{
        for(let i in res.carpetas){
          
          if(this.dataEntrante==res.carpetas[i].propietario){
            this.arrayResult.push(res.carpetas[i])
          }
          
          
        }
      
        
      }
    )
  }

  sendCreateCarpeta(){
    if(this.crearCarpeta.nombre.includes('.txt')){
      this.crearCarpeta.propietario = this.dataEntrante
      this.crearCarpeta.tipo = 0
      this.registroService.createCarpetaByUser(this.crearCarpeta)
    .subscribe(
      res=>{
        console.log(res)
        if(res.validate){
          Swal.fire({
            icon: 'success',
            title: 'Crear',
            text: 'Carpeta o archivo creado exitosamente',
          })
        }else{
          Swal.fire({
            icon: 'error',
            title: 'Error',
            text: 'No se puede crear archivo o carpeta',
          })
        }
      }
    )
    }else{
      this.crearCarpeta.propietario = this.dataEntrante
      this.crearCarpeta.tipo = 1
      this.registroService.createCarpetaByUser(this.crearCarpeta)
    .subscribe(
      res=>{
        console.log(res)
        if(res.validate){
          Swal.fire({
            icon: 'success',
            title: 'Crear',
            text: 'Carpeta o archivo creado exitosamente',
          })
        }else{
          Swal.fire({
            icon: 'error',
            title: 'Error',
            text: 'No se puede crear archivo o carpeta',
          })
        }
      }
    )
    }
    
    
  }

  deleteCarpeta(){
    this.registroService.deleteCarpetaByUser(this.eliminarCarpeta)
    .subscribe(
      res=>{
        console.log(res)
        if(res.validate){
          Swal.fire({
            icon: 'success',
            title: 'Eliminar',
            text: 'Carpeta o archivo eliminado exitosamente',
          })
        }else{
          Swal.fire({
            icon: 'error',
            title: 'Error',
            text: 'Erro al eliminar carpeta o archivo',
          })
        }
      }
    )
  }

 

}
