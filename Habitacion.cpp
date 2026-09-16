//Hecho por: David Leon

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class nodoHabitacion {
public:
    nodoHabitacion(int pID, string pNumero, string pPiso, int pTipo, int pEstado) {
        idHabitacion = pID;
        numero = pNumero;
        piso = pPiso;
        tipo = pTipo;
        estado = pEstado;
        siguiente = NULL;
        anterior = NULL;
    }

    private:
        int idHabitacion;
        string numero;
        string piso;
        int tipo;
        int estado;
        nodoHabitacion *siguiente;
        nodoHabitacion *anterior;

    friend class listaHabitacion;
};

typedef nodoHabitacion *pnodoHabitacion;

class listaHabitacion {
   public:
    listaHabitacion() { cabeza = NULL; }
    ~listaHabitacion();

    void Insertar(int idHabitacion, string numero, string piso, int tipo, int estado);
    bool ListaVacia() { return cabeza == NULL; }
    bool ExisteHabitacion(int idHabitacion);
    void Mostrar();
    void BuscarHabitacion(int idHabitacion);
    void ModificarEstado(int idHabitacion, int nuevoEstado);
    void ReporteHabitacionesPorEstado(int estado);
    void CargarArchivoHabitacion(string nombreArchivo);

    private:
    pnodoHabitacion cabeza;
};

listaHabitacion::~listaHabitacion() {
    if (ListaVacia()) return;

    pnodoHabitacion aux = cabeza->siguiente;
    pnodoHabitacion borrar;
    while (aux != cabeza) {
        borrar = aux;
        aux = aux->siguiente;
        delete borrar;
    }
    delete cabeza;
    cabeza = NULL;
}

bool listaHabitacion::ExisteHabitacion(int idHabitacion) {
    if (ListaVacia()) return false;

    pnodoHabitacion aux = cabeza;
    do {
        if (aux->idHabitacion == idHabitacion) {
            return true;
        }
        aux = aux->siguiente;
    } while (aux != cabeza);

    return false;
}

void listaHabitacion::Insertar(int idHabitacion, string numero, string piso, int tipo, int estado) {
    if (ExisteHabitacion(idHabitacion)) {
        cout << "El codigo de habitacion " << idHabitacion << " ya existe" << endl;
        return;
    }

    pnodoHabitacion nuevo = new nodoHabitacion(idHabitacion, numero, piso, tipo, estado);

    if (ListaVacia()) {
        cabeza = nuevo;
        nuevo->siguiente = cabeza;
        nuevo->anterior = cabeza;
    }
    else {
        pnodoHabitacion ultimo = cabeza->anterior;
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
    }
}

void listaHabitacion::Mostrar() {
    if (ListaVacia()) {
        cout << "No hay habitaciones" << endl;
        return;
    }
    pnodoHabitacion aux = cabeza;
    do {
        cout << aux->idHabitacion << " - " << aux->numero << " - " << aux->piso
             << " - " << aux->tipo << " - " << aux->estado << " -> ";
        aux = aux->siguiente;
    } while (aux != cabeza);
    cout << endl;
}

void listaHabitacion::BuscarHabitacion(int idHabitacion) {
    if (!ExisteHabitacion(idHabitacion)) {
        cout << "El codigo de habitacion " << idHabitacion << " no existe" << endl;
        return;
    }

    pnodoHabitacion aux = cabeza;
    do {
        if (aux->idHabitacion == idHabitacion) {
            cout << "El codigo de la habitacion es: " << aux->idHabitacion << endl;
            cout << "El numero es: " << aux->numero << endl;
            cout << "El piso es: " << aux->piso << endl;
            cout << "El tipo es: " << aux->tipo << endl;
            cout << "El estado es: " << aux->estado << endl;
            return;
        }
        aux = aux->siguiente;
    } while (aux != cabeza);

    cout << "La habitacion no existe" << endl;
}

void listaHabitacion::ModificarEstado(int idHabitacion, int nuevoEstado) {
    if (!ExisteHabitacion(idHabitacion)) {
        cout << "El codigo de habitacion " << idHabitacion << " no existe" << endl;
        return;
    }

    pnodoHabitacion aux = cabeza;
    do {
        if (aux->idHabitacion == idHabitacion) {
            aux->estado = nuevoEstado;
            cout << "Estado actualizado correctamente." << endl;
            return;
        }
        aux = aux->siguiente;
    } while (aux != cabeza);
}

void listaHabitacion::ReporteHabitacionesPorEstado(int estado) {
    if (ListaVacia()) {
        cout << "No hay habitaciones" << endl;
        return;
    }

    pnodoHabitacion aux = cabeza;
    do {
        if (aux->estado == estado) {
            cout << aux->idHabitacion << " - " << aux->numero << " - " << aux->piso
                 << " - " << aux->tipo << " -> ";
        }
        aux = aux->siguiente;
    } while (aux != cabeza);
    cout << endl;
}

void listaHabitacion::CargarArchivoHabitacion(string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string campoID, numero, piso, campoTipo, campoEstado;

        getline(ss, campoID, ';');
        getline(ss, numero, ';');
        getline(ss, piso, ';');
        getline(ss, campoTipo, ';');
        getline(ss, campoEstado);

        int idHabitacion = stoi(campoID);
        int tipo = stoi(campoTipo);
        int estado = stoi(campoEstado);

        Insertar(idHabitacion, numero, piso, tipo, estado);
    }

    archivo.close();
    cout << "Archivo cargado correctamente." << endl;
}