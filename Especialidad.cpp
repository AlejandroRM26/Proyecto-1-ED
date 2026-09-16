#pragma once
//Hecho por: David Leon
 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
 
using namespace std;
 
class nodoEspecialidad {
public:
    nodoEspecialidad(int pID, string pNombre, string pDescripcion) {
        idEspecialidad = pID;
        nombre = pNombre;
        descripcion = pDescripcion;
        siguiente = NULL;
        anterior = NULL;
    }
 
    private:
        int idEspecialidad;
        string nombre;
        string descripcion;
        nodoEspecialidad *siguiente;
        nodoEspecialidad *anterior;
 
    friend class listaEspecialidad;
};
 
typedef nodoEspecialidad *pnodoEspecialidad;
 
class listaEspecialidad {
   public:
    listaEspecialidad() { cabeza = NULL; }
    ~listaEspecialidad();
 
    void Insertar(int idEspecialidad, string nombre, string descripcion);
    bool ListaVacia() { return cabeza == NULL; }
    bool ExisteEspecialidad(int idEspecialidad);
    void Mostrar();
    void BuscarEspecialidad(int idEspecialidad);
    void ModificarDescripcion(int idEspecialidad, string nuevaDescripcion);
    void CargarArchivoEspecialidad(string nombreArchivo);
 
    private:
    pnodoEspecialidad cabeza;
};
 
listaEspecialidad::~listaEspecialidad() {
    if (ListaVacia()) return;
 
    pnodoEspecialidad aux = cabeza->siguiente;
    pnodoEspecialidad borrar;
    while (aux != cabeza) {
        borrar = aux;
        aux = aux->siguiente;
        delete borrar;
    }
    delete cabeza;
    cabeza = NULL;
}
 
bool listaEspecialidad::ExisteEspecialidad(int idEspecialidad) {
    if (ListaVacia()) return false;
 
    pnodoEspecialidad aux = cabeza;
    do {
        if (aux->idEspecialidad == idEspecialidad) {
            return true;
        }
        aux = aux->siguiente;
    } while (aux != cabeza);
 
    return false;
}
 
void listaEspecialidad::Insertar(int idEspecialidad, string nombre, string descripcion) {
    if (ExisteEspecialidad(idEspecialidad)) {
        cout << "El codigo de especialidad " << idEspecialidad << " ya existe" << endl;
        return;
    }
 
    pnodoEspecialidad nuevo = new nodoEspecialidad(idEspecialidad, nombre, descripcion);
 
    if (ListaVacia()) {
        cabeza = nuevo;
        nuevo->siguiente = cabeza;
        nuevo->anterior = cabeza;
    }
    else {
        pnodoEspecialidad ultimo = cabeza->anterior;
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
    }
}
 
void listaEspecialidad::Mostrar() {
    if (ListaVacia()) {
        cout << "No hay especialidades" << endl;
        return;
    }
    pnodoEspecialidad aux = cabeza;
    do {
        cout << aux->idEspecialidad << " - " << aux->nombre << " - " << aux->descripcion << " -> ";
        aux = aux->siguiente;
    } while (aux != cabeza);
    cout << endl;
}
 
void listaEspecialidad::BuscarEspecialidad(int idEspecialidad) {
    if (!ExisteEspecialidad(idEspecialidad)) {
        cout << "El codigo de especialidad " << idEspecialidad << " no existe" << endl;
        return;
    }
 
    pnodoEspecialidad aux = cabeza;
    do {
        if (aux->idEspecialidad == idEspecialidad) {
            cout << "El codigo de la especialidad es: " << aux->idEspecialidad << endl;
            cout << "El nombre de la especialidad es: " << aux->nombre << endl;
            cout << "La descripcion de la especialidad es: " << aux->descripcion << endl;
            return;
        }
        aux = aux->siguiente;
    } while (aux != cabeza);
 
    cout << "La especialidad no existe" << endl;
}
 
void listaEspecialidad::ModificarDescripcion(int idEspecialidad, string nuevaDescripcion) {
    if (!ExisteEspecialidad(idEspecialidad)) {
        cout << "El codigo de especialidad " << idEspecialidad << " no existe" << endl;
        return;
    }
 
    pnodoEspecialidad aux = cabeza;
    do {
        if (aux->idEspecialidad == idEspecialidad) {
            aux->descripcion = nuevaDescripcion;
            cout << "Descripcion actualizada correctamente." << endl;
            return;
        }
        aux = aux->siguiente;
    } while (aux != cabeza);
}
 
void listaEspecialidad::CargarArchivoEspecialidad(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
 
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }
 
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
 
        stringstream ss(linea);
        string campoID, nombre, descripcion;
 
        getline(ss, campoID, ';');
        getline(ss, nombre, ';');
        getline(ss, descripcion);
 
        int idEspecialidad = stoi(campoID);
 
        Insertar(idEspecialidad, nombre, descripcion);
    }
 
    archivo.close();
    cout << "Archivo cargado correctamente." << endl;
}