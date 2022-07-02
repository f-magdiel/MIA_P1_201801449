import { Component, OnInit,Input } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';
import Swal from 'sweetalert2';
@Component({
  selector: 'app-colaboracionusuario',
  templateUrl: './colaboracionusuario.component.html',
  styleUrls: ['./colaboracionusuario.component.css']
})
export class ColaboracionusuarioComponent implements OnInit {
  @Input() dataEntrante:any
  constructor(private registroService:RegistroService) { }
  arrayCarpetasColab:any=[]
  ngOnInit(): void {
    this.obtenerCarpetasColaborador()
  }

  colab={
    usuario:''
  }

  fincolab={
    carpeta:'',
    usuario:''
  }

  obtenerCarpetasColaborador(){
    this.colab.usuario = this.dataEntrante
    this.registroService.getAllCarpetas()
    .subscribe(
      res=>{
        for(let i in res.carpetas){
          
            for(let j in res.carpetas[i].colaborador){
              if(res.carpetas[i].colaborador[j].usuario==this.colab.usuario){
                  this.arrayCarpetasColab.push(res.carpetas[i])
              }
            }
          
        }


      }
    )
  }

  finalizarColaboracion(){
    this.fincolab.usuario = this.dataEntrante
    this.registroService.deleteColaborador(this.fincolab)
    .subscribe(
      res=>{
        console.log(res)
        if(res.validate){
          Swal.fire({
            icon: 'success',
            title: 'Colaboracion',
            text: 'Colaboracion Terminada Exitosamente',
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
