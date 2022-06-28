class Nodo {
    constructor(nombre) {
        this.nombre = nombre;
        this.siguiente = null;
        this.anterior = null;
        this.archivo = [100];
        this.propietario = '';
        this.colaboradores = ''; 
    }
}

class Lista {
    constructor() {
        this.primero = null;
        this.ultimo = null;
        this.size = 0;
    }

    add(dato) {
        let nuevo = new Nodo(dato)
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