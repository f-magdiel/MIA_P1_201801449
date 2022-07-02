import { EventEmitter, Injectable, Output } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class EnviodatosService {
  @Output() disparadorDeDatos: EventEmitter<any> = new EventEmitter();

  constructor() { }
}
