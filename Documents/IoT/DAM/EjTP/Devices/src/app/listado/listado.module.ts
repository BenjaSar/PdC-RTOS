import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ListadoComponent } from './listado.component';



@NgModule({
  declarations: [ListadoComponent],
  imports: [
    CommonModule
  ],
  //Lo que quiero tener disponible para los demas modulos
 exports: [ListadoComponent]
})
export class ListadoModule { }
