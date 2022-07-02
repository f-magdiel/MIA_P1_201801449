import { Component, OnInit,Input } from '@angular/core';
import { RegistroService } from 'src/app/services/registro.service';
@Component({
  selector: 'app-correo',
  templateUrl: './correo.component.html',
  styleUrls: ['./correo.component.css']
})
export class CorreoComponent implements OnInit {
  @Input() dataEntrante:any
  constructor(private servicioReg:RegistroService) { }
  arrayMail:any =[]
  ngOnInit(): void {
    this.consultaCorreos()
  }
  user={
    usuario:''
  }
  consultaCorreos(){
    this.user.usuario = this.dataEntrante
    
    this.servicioReg.getCorreo(this.user)
    .subscribe(
      res=>{
        console.log(res)
        for(let dat in res.correo){
          this.arrayMail.push(res.correo[dat])
        }
      }
    )

  }

}
