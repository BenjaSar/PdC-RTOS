import { Injectable } from '@angular/core';
import { Dispositivos } from '../model/Dispositivo';

@Injectable({
  providedIn: 'root'
})
export class ListadoService {
  //Se simula el backend a traves del JSON
  listadoDispositivo: Dispositivos[]= {
  [{
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
  }]
}

  constructor() {
   
   }

  getDispositivos(){
  return this.listadoDispositivo;
   }
}
