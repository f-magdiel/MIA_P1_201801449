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
  visibleCorreo:boolean=false;

  ngOnInit(): void {
    console.log("Se recibe")
    const id = this.route.snapshot.params['id']
    this.nameusuario = id
  }

  showSistema(){
    
    this.visibleSistema = this.visibleSistema?false:true
    this.visibleColaborador = false
    this.visibleCorreo = false
  }

  showColaborador(){
    this.visibleColaborador = this.visibleColaborador?false:true
    this.visibleSistema = false
    this.visibleCorreo = false
  }

  showCorreo(){
    this.visibleCorreo = this.visibleCorreo?false:true
    this.visibleColaborador = false
    this.visibleSistema = false
  }
}
