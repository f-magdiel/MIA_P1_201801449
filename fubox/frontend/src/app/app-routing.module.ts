import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { RegistroComponent } from './components/registro/registro.component';
import { LoginComponent } from './components/login/login.component';
import { InicioComponent } from './components/inicio/inicio.component';
import { PanelusuarioComponent } from './components/panelusuario/panelusuario.component';
import { SistemausuarioComponent } from './components/sistemausuario/sistemausuario.component';
import { PaneladminComponent } from './components/paneladmin/paneladmin.component';


const routes: Routes = [
  {path:'',component:InicioComponent},
  {path:'registro',component:RegistroComponent},
  {path:'login',component:LoginComponent},
  {path:'panelusuario/:id',component:PanelusuarioComponent},
  {path:'paneladmin',component:PaneladminComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
