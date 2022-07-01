import { Component, OnInit,ChangeDetectorRef } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';

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
    tipo:''
  }

  consultaCarpetas(){
    this.serviceConsult.getAllCarpetas()
    .subscribe(
      res =>{
        for(let i in res.carpetas){
          this.arrayResult.push(res.carpetas[i])
          
        }
      
        
      }
    )
  }
  
  


  
 
  
}
