//Hecho por: Alejandro Rodriguez
//13/09/2026

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class nodo { 
    private:
        int codPais = 0;
        string nombre = "";
        nodo *siguiente;
        
    public:
        nodo(int IDPais, string pNombre) {        
            codPais = IDPais;
            nombre = pNombre;
            siguiente = NULL;
        }

        nodo(int IDPais, string pNombre, nodo *signodo) {
            codPais = IDPais;
            nombre = pNombre;
            siguiente = signodo;
        }
        
    friend class Pais;
};

typedef nodo *pnodo;

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
        void CargarDesdeArchivo(string nombreArchivo);
    
    private:
        pnodo primero;
};

Pais::~Pais() {
    pnodo aux;
   
    while(primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }

    primero = NULL;
}
 
void Pais::Insertar(int IDPais, string pNombre) {
    if (ListaVacia()) {
        primero = new nodo(IDPais, pNombre);
    }
    else {
        pnodo aux = primero;

        while (true) {

            if (aux->codPais == IDPais) {
                cout << "El codigo " << aux->codPais << " proporcionado para el Pais "
                     << pNombre << " ya existe" << endl;
                return;
            }

            if (aux->siguiente == NULL) {
                aux->siguiente = new nodo(IDPais, pNombre);
                return;
            }

            aux = aux->siguiente;
        }
    }
}

void Pais::MostrarTodaLista() {
    
    nodo *aux;
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
    nodo *aux;
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

void Pais::CargarDesdeArchivo(string nombreArchivo) {
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

