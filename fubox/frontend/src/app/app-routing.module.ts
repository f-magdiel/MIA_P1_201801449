import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { RegistroComponent } from './components/registro/registro.component';
import { LoginComponent } from './components/login/login.component';
import { InicioComponent } from './components/inicio/inicio.component';
import { PanelusuarioComponent } from './components/panelusuario/panelusuario.component';
import { SistemausuarioComponent } from './components/sistemausuario/sistemausuario.component';
import { PaneladminComponent } from './components/paneladmin/paneladmin.component';
import { Page404Component } from './components/page404/page404.component';
import { AccesodenegadoComponent } from './components/accesodenegado/accesodenegado.component';
import { VigilanteunoGuard } from './vigilanteuno.guard';
import { VigilantedosGuard } from './vigilantedos.guard';


const routes: Routes = [
  {path:'',component:InicioComponent},
  {path:'registro',component:RegistroComponent},
  {path:'login',component:LoginComponent},
  {path:'panelusuario/:id',component:PanelusuarioComponent,canActivate:[VigilantedosGuard]},
  {path:'paneladmin',component:PaneladminComponent,canActivate:[VigilanteunoGuard]},
  {path:'page404',component:Page404Component},
  {path:'accesodenegado',component:AccesodenegadoComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
