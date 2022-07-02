import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, ChildActivationEnd } from '@angular/router';
import { EnviodatosService } from 'src/app/services/enviodatos.service';
import { SistemausuarioComponent } from '../sistemausuario/sistemausuario.component';


@Component({
  selector: 'app-panelusuario',
  templateUrl: './panelusuario.component.html',
  styleUrls: ['./panelusuario.component.css'],
})
export class PanelusuarioComponent implements OnInit {
  nameusuario:any;
  constructor(private route:ActivatedRoute,private sendDatos:EnviodatosService) { 
    
  }

  visibleSistema:boolean=false;
  visibleColaborador:boolean=false;
  ngOnInit(): void {
    console.log("Se recibe")
    const id = this.route.snapshot.params['id']
    this.nameusuario = id
    
  }

  showSistema(){
    console.log("muestra sistema")
    this.sendDatos.disparadorDeDatos.emit({
      "nombre":this.nameusuario
    })
    this.visibleSistema = this.visibleSistema?false:true
    
  }

  showColaborador(){
    this.visibleColaborador = this.visibleColaborador?false:true
  }

}
