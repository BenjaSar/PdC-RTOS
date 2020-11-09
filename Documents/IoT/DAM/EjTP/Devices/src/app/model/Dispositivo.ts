
  export class Dispositivos {

    private _dispositivoId:number;
    private _nombre: string;
    private _ubicacion: string;
    private _electrovalvulaId: number;

    public constructor(dispostivoId:number, nombre:string, ubicacion:string, electrovalvulaId:number){
        this._dispositivoId = dispostivoId;
        this._nombre = nombre;
        this._ubicacion = ubicacion;
        this._electrovalvulaId= electrovalvulaId
    }

    public get dispositivoId():number{
    return this._dispositivoId;
        }

    public set dispositivoId(dId:number){
        if(dId <=0 || dId>=1000){
            throw new Error('The device number is invalid');
        }
        this._dispositivoId = dId;
    }    

    public get nombre():string{
        return this._nombre;
        }

    
    public set nombre(name:string){
        this._nombre = name;
        }      

    public get ubicacion():string{
        return this._ubicacion;
        }
    
    public set ubicacion(location:string){
        this._ubicacion = location;
        }      

    public get electrovalvulaId(): number{
            return this._electrovalvulaId;
        }
            
    public set electrovalvulaId(eValvulaId:number){
        this._electrovalvulaId = eValvulaId;
         } 

    Device1 = new Dispositivos(1, "Sensor 1", "Patio", 1);    
    Device2 = new Dispositivos(2, "Sensor 2", "Cocina", 2);
    Device3 = new Dispositivos(3, "Sensor 3", "Jardin delantero", 3);
    Device4 = new Dispositivos(4, "Sensor 4", "Living", 4);

    

}

  /*For each property:

A getter method returns the value of the property’s value. A getter is also called an accessor.
A setter method updates the property’s value. A setter is also known as a mutator.*/

