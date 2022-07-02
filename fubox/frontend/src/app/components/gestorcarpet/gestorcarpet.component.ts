import { Component, OnInit,ChangeDetectorRef } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';
import Swal from 'sweetalert2';
var result = [];
@Component({
  selector: 'app-gestorcarpet',
  templateUrl: './gestorcarpet.component.html',
  styleUrls: ['./gestorcarpet.component.css']
})
export class GestorcarpetComponent implements OnInit {
  //para mostrar las carpetas
  arrayResult:any=[]
  typesOfShoes: string[] = ['Boots', 'Clogs', 'Loafers', 'Moccasins', 'Sneakers'];
  constructor(private serviceConsult:RegistroService) {}

  ngOnInit(): void {
    this.consultaCarpetas()
  }
  carpeta={
    "propietario":"simon"
  }
  modelData={
    nombre:'',
    propietario:'',
    tipo:''
  }

  seleccionado={
    nombre:'',
    propietario:'',
  }

  consultaCarpetas(){
    this.serviceConsult.getAllCarpetas()
    .subscribe(
      res =>{
        for(let i in res.carpetas){
          if(res.carpetas[i].nombre!=''){
            this.arrayResult.push(res.carpetas[i])
          }
          
        }
      
        
      }
    )
  }
  
  agregarPropietario(){
    this.serviceConsult.addPropietario(this.seleccionado)
    .subscribe(
      res=>{
        console.log(res)
        if(res.validate){
          Swal.fire({
            icon: 'success',
            title: 'Cambio de propietario',
            text: 'Cambiado exitosamente',
          })
        }else{
          Swal.fire({
            icon: 'error',
            title: 'Cambio de propietario',
            text: 'No se pudo cambiar de propietario',
          })

        }
      }
    )
  }


  
 
  
}
