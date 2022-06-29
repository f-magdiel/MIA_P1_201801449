class Nodo {
    constructor(nombre,tipo) {
        this.nombre = nombre;
        this.siguiente = null;
        this.anterior = null;
        this.propietario = '';
        this.colaboradores = ''; 
        this.tipo = tipo;//1 si es carpeta y 0 si es archivo
    }
}

class Lista {
    constructor() {
        this.primero = null;
        this.ultimo = null;
        this.size = 0;
    }

    add(nombre,tipo) {
        let nuevo = new Nodo(nombre,tipo)
        if (this.primero == null) {
            this.primero = nuevo;
            this.ultimo = this.primero;
            this.size++;
        } else {
            this.ultimo.siguiente = nuevo;
            nuevo.anterior = this.ultimo;
            this.ultimo = nuevo;
            this.size++;
        }

    }

}


module.exports = Lista;