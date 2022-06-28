class Nodo {
    constructor(dato) {
        this.dato = dato;//nombre de la carpeta
        this.siguiente = [100];//sub carpetas
        for(var i in this.siguiente){
            this.siguiente[i]=null;
        }
        this.anterior = null;
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

module.exports = Estructura;