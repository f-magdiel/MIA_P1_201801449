import { Component, OnInit } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';
import Swal from 'sweetalert2';
@Component({
  selector: 'app-paneladmin',
  templateUrl: './paneladmin.component.html',
  styleUrls: ['./paneladmin.component.css']
})
export class PaneladminComponent implements OnInit {
  public archivos:any = []
  text:string=""
  constructor(private register:RegistroService) { }

  ngOnInit(): void {
  }
  visibleGestorCarpeta:boolean=false;
  visibleGestorUsuario:boolean=false;
  visibleCarga:boolean=true;

  showGestorCarpeta(){
    this.visibleGestorCarpeta = this.visibleGestorCarpeta?false:true;
    this.visibleGestorUsuario = false;
    this.visibleCarga = false;
  }

  showGerstorUsuario(){
    this.visibleGestorUsuario = this.visibleGestorUsuario?false:true;
    this.visibleGestorCarpeta = false;
    this.visibleCarga = false;
  }
  
  capturarFile(event:any){
    const archivoCapturado = event.target.files[0]
    console.log(archivoCapturado)
    
    if(archivoCapturado){
      console.log("entra")
      let reader = new FileReader()
     
      reader.onload=event=>{
        const result = event.target?.result
        this.text = String(result)
        //console.log(this.text)
      }

      reader.readAsText(archivoCapturado)
    }
    
  }

  enviarAlServer(){
    console.log("Se manda...."+this.text)
    let jsonenviar = JSON.parse(this.text)
    this.register.postInsertJson(jsonenviar)
    .subscribe(
      res=>{
        console.log(res)
        Swal.fire({
          icon: 'success',
          title: 'Carga de Json',
          text: 'Carga exitosa',
        })
      }
    )
  }

}
