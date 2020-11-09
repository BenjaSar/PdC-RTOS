import { Component, OnInit } from '@angular/core';
import {Dispositivos} from '../model/Dispositivo'
import { ListadoService } from '../service/listado.service';

@Component({
  selector: 'app-listado',
  templateUrl: './listado.component.html',
  styleUrls: ['./listado.component.css']
})
export class ListadoComponent implements OnInit {
  Devices: { dispositivoId: number; nombre: string; ubicacion: string; electrovalvulaId: number; }[];

  //listadoServ es una instancia de ListadoService
  constructor(public listadoServ:ListadoService, private Devic:Dispositivos) {
    this.Devices  = [{
      "dispositivoId": 1,
      "nombre": "Sensor 1",
      "ubicacion": "Patio",
      "electrovalvulaId": 1
    }, {
      "dispositivoId": 2,
      "nombre": "Sensor 2",
      "ubicacion": "Cocina",
      "electrovalvulaId": 2
    }, {
      "dispositivoId": 3,
      "nombre": "Sensor 3",
      "ubicacion": "Jardin Delantero",
      "electrovalvulaId": 3
    }, {
      "dispositivoId": 4,
      "nombre": "Sensor 2",
      "ubicacion": "Living",
      "electrovalvulaId": 4
    }],

    console.log(this.listadoServ.getDispositivos());
   }

  
  ngOnInit(): void {

  }

}
