import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { InicioComponent } from './components/inicio/inicio.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import {MatMenuModule} from '@angular/material/menu';
import {MatToolbarModule} from '@angular/material/toolbar';
import {MatButtonModule} from '@angular/material/button';
import {LoginComponent } from './components/login/login.component';
import {RegistroComponent } from './components/registro/registro.component';
import {MatInputModule} from '@angular/material/input';
import {MatIconModule} from '@angular/material/icon';
import {MatFormFieldModule} from '@angular/material/form-field';
import {MatCardModule} from '@angular/material/card';
import {MatAutocompleteModule} from '@angular/material/autocomplete'
import {FormsModule, ReactiveFormsModule} from '@angular/forms';
import {MatDatepickerModule} from '@angular/material/datepicker';
import { MatNativeDateModule } from '@angular/material/core';
import { HttpClientModule } from '@angular/common/http';
import { PanelusuarioComponent } from './components/panelusuario/panelusuario.component';
import { PaneladminComponent } from './components/paneladmin/paneladmin.component';
import { SistemausuarioComponent } from './components/sistemausuario/sistemausuario.component';
import { ColaboracionusuarioComponent } from './components/colaboracionusuario/colaboracionusuario.component';
import {MatListModule} from '@angular/material/list';
import { GestorcarpetComponent } from './components/gestorcarpet/gestorcarpet.component';
import { GestoruserComponent } from './components/gestoruser/gestoruser.component';
import { ColaboradorComponent } from './components/colaborador/colaborador.component';
import { CorreoComponent } from './components/correo/correo.component';
import { Page404Component } from './components/page404/page404.component';
import { AccesodenegadoComponent } from './components/accesodenegado/accesodenegado.component';
import { CookieService } from 'ngx-cookie-service';

@NgModule({
  declarations: [
    AppComponent,
    InicioComponent,
    LoginComponent,
    RegistroComponent,
    PanelusuarioComponent,
    PaneladminComponent,
    SistemausuarioComponent,
    ColaboracionusuarioComponent,
    GestorcarpetComponent,
    GestoruserComponent,
    ColaboradorComponent,
    CorreoComponent,
    Page404Component,
    AccesodenegadoComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    BrowserAnimationsModule,
    MatMenuModule,
    MatToolbarModule,
    MatButtonModule,
    MatInputModule,
    MatIconModule,
    MatFormFieldModule,
    MatCardModule,
    MatAutocompleteModule,
    FormsModule,
    ReactiveFormsModule,
    MatDatepickerModule,
    MatNativeDateModule,
    HttpClientModule,
    MatListModule
  ],
  providers: [CookieService],
  bootstrap: [AppComponent]
})
export class AppModule { }
