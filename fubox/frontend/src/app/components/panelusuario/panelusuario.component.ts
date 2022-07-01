import { Component, OnInit } from '@angular/core';
import { ChildActivationEnd } from '@angular/router';
import { SistemausuarioComponent } from '../sistemausuario/sistemausuario.component';

@Component({
  selector: 'app-panelusuario',
  templateUrl: './panelusuario.component.html',
  styleUrls: ['./panelusuario.component.css'],
})
export class PanelusuarioComponent implements OnInit {

  constructor() { }

  visibleSistema:boolean=false;
  visibleColaborador:boolean=false;
  ngOnInit(): void {
  }

  showSistema(){
    console.log("muestra sistema")
    this.visibleSistema = this.visibleSistema?false:true
  }

  showColaborador(){
    this.visibleColaborador = this.visibleColaborador?false:true
  }

}
