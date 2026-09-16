#pragma once
//Hecho por: Alejandro Rodriguez
//13/09/2026

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class nodoPais { 
    private:
        int codPais = 0;
        string nombre = "";
        nodoPais *siguiente;
        
    public:
        nodoPais(int IDPais, string pNombre) {        
            codPais = IDPais;
            nombre = pNombre;
            siguiente = NULL;
        }

        nodoPais(int IDPais, string pNombre, nodoPais *signodo) {
            codPais = IDPais;
            nombre = pNombre;
            siguiente = signodo;
        }
        
    friend class Pais;
};

typedef nodoPais *pnodoPais;

class Pais {
    public:
        Pais() { 
            primero = NULL; 
        }

        ~Pais();

        void Insertar(int IDPais, string pNombre);
        bool ListaVacia() { return primero == NULL; }
        void MostrarTodaLista();
        void BuscarPais(int IDPais);
        bool ExistePais(int IDPais);
        void CargarDesdeArchivoPais(string nombreArchivo);
    
    private:
        pnodoPais primero;
};

Pais::~Pais() {
    pnodoPais aux;
   
    while(primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }

    primero = NULL;
}
 
void Pais::Insertar(int IDPais, string pNombre) {
    if (ListaVacia()) {
        primero = new nodoPais(IDPais, pNombre);
    }
    else {
        pnodoPais aux = primero;

        while (true) {

            if (aux->codPais == IDPais) {
                cout << "El codigo " << aux->codPais << " proporcionado para el Pais "
                     << pNombre << " ya existe" << endl;
                return;
            }

            if (aux->siguiente == NULL) {
                aux->siguiente = new nodoPais(IDPais, pNombre);
                return;
            }

            aux = aux->siguiente;
        }
    }
}

void Pais::MostrarTodaLista() {
    
    nodoPais *aux;
    if (primero == NULL) {
        cout << "No hay elementos AQUI";
    }
    else {
        aux = primero;
        while(aux) {
            cout << aux->codPais << " - ";
            cout << aux->nombre << " -> ";
            aux = aux->siguiente;
        }
        cout << endl;
    }
}

void Pais::BuscarPais(int IDPais) {
    nodoPais *aux;
    aux = primero;
    while(aux != NULL) {
        if(IDPais == aux->codPais) {
            cout << endl << aux->codPais << " - ";
            cout << aux->nombre;
            return;
        }
        aux = aux->siguiente;
    }
    cout <<endl << "No existe ese codigo de pais" << endl;
}

bool Pais::ExistePais(int IDPais) {
    nodoPais *aux = primero;
    while (aux != NULL) {
        if (aux->codPais == IDPais) {
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

void Pais::CargarDesdeArchivoPais(string nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string codigoStr, nombre;

        getline(ss, codigoStr, ';');
        getline(ss, nombre);

        int codigo = stoi(codigoStr); // convierte el codigo a int
        Insertar(codigo, nombre);
    }
    archivo.close();
    cout << "Archivo cargado correctamente." << endl;
}

