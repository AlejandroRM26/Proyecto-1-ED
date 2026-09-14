//Hecho por: Alejandro Rodriguez
 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Pais.cpp"
 
using namespace std;
 
class nodoCiudad { 
public:  
    nodoCiudad(int IDPais, int IDCiudad, string pnombre) { 
        codPais = IDPais;
        codCiudad = IDCiudad;
        nombre = pnombre;
        siguiente = NULL;
    }
 
    private:
        int codPais;
        int codCiudad;
        string nombre;
        nodoCiudad *siguiente;
 
    friend class listaCiudad;
};
 
typedef nodoCiudad *pnodoCiudad;
 
class listaCiudad {
   public:
    listaCiudad() { primero = NULL; }
    ~listaCiudad();
 
    void Insertar(int codPais, int codCiudad, string nombre, Pais &listaPaises);
    bool ListaVacia() { return primero == NULL; }
    bool ExisteCiudad(int codCiudad);
    void Mostrar();
    void BuscarCiudad(int IDCiudad, int IDPais, Pais &listaPaises);
    void CargarArchivoCiudad(string nombreArchivo, Pais &listaPaises);
 
    private:
    pnodoCiudad primero;
};
 
listaCiudad::~listaCiudad() {
    if (ListaVacia()) return;
 
    pnodoCiudad aux = primero->siguiente;
    pnodoCiudad borrar;
    while (aux != primero) {
        borrar = aux;
        aux = aux->siguiente;
        delete borrar;
    }
    delete primero;
    primero = NULL;
}
 
bool listaCiudad::ExisteCiudad(int codCiudad) {
    if (ListaVacia()) return false;
 
    pnodoCiudad aux = primero;
    do {
        if (aux->codCiudad == codCiudad) {
            return true;
        }
        aux = aux->siguiente;
    } while (aux != primero);
 
    return false;
}
 
void listaCiudad::Insertar(int IDPais, int IDCiudad, string pNombre, Pais &listaPaises) {
    if (!listaPaises.ExistePais(IDPais)) {
        cout << "El codigo de pais " << IDPais << " no existe" << endl;
        return;
    }
    if (ExisteCiudad(IDCiudad)) {
        cout << "El codigo de ciudad " << IDCiudad << " ya existe" << endl;
        return;
    }
 
    pnodoCiudad nuevo = new nodoCiudad(IDPais, IDCiudad, pNombre);
 
    if (ListaVacia()) {
        primero = nuevo;
        nuevo->siguiente = primero;
    } 
    else {
        pnodoCiudad aux = primero;
        while (aux->siguiente != primero) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
        nuevo->siguiente = primero;
    }
}
 
void listaCiudad::Mostrar() {
    if (ListaVacia()) {
        cout << "No hay ciudades" << endl;
        return;
    }
    pnodoCiudad aux = primero;
    do {
        cout << aux->codPais << " - " << aux->codCiudad << " - " << aux->nombre << " -> ";
        aux = aux->siguiente;
    } while (aux != primero);
    cout << endl;
}
 
void listaCiudad::BuscarCiudad(int IDCiudad, int IDPais, Pais &listaPaises) {
    if (!listaPaises.ExistePais(IDPais)) {
        cout << "El codigo de pais " << IDPais << " no existe" << endl;
        return;
    }
    if (!ExisteCiudad(IDCiudad)) {
        cout << "El codigo de ciudad " << IDCiudad << " no existe" << endl;
        return;
    }
 
    pnodoCiudad aux = primero;
    do {
        if (aux->codCiudad == IDCiudad) {
            cout << "El codigo del pais es: " << aux->codPais << endl;
            cout << "El codigo de la ciudad es: " << aux->codCiudad << endl;
            cout << "El nombre de la ciudad es: " << aux->nombre << endl;
            return;
        }
        aux = aux->siguiente;
    } while (aux != primero);
 
    cout << "La ciudad no existe" << endl;
}

void listaCiudad::CargarArchivoCiudad(string nombreArchivo, Pais &listaPaises) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string campoPais, campoCiudad, nombre;

        getline(ss, campoPais, ';');
        getline(ss, campoCiudad, ';');
        getline(ss, nombre);

        int codPais = stoi(campoPais);
        int codCiudad = stoi(campoCiudad);

        Insertar(codPais, codCiudad, nombre, listaPaises);
    }

    archivo.close();
    cout << "Archivo cargado correctamente." << endl;
}
