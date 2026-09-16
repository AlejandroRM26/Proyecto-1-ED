#pragma once
//Hecho por: Alejandro Rodriguez
 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Ciudad.cpp"

using namespace std;

const int Tam_TablaPaciente = 13;

class NodoPaciente {
    public:
        NodoPaciente(int pID, string pNombre, string pFecha, string pTelefono,
                    int pCodCiudad, int pCodPais, string pCorreo) {
            IDPaciente = pID;
            nombre = pNombre;
            fechaNacimiento = pFecha;
            telefono = pTelefono;
            codCiudad = pCodCiudad;
            codPais = pCodPais;
            correo = pCorreo;
            siguiente = NULL;
            }

private:
    int IDPaciente;
    string nombre;
    string fechaNacimiento;
    string telefono;
    int codCiudad;
    int codPais;
    string correo;
    NodoPaciente *siguiente;

    friend class listaPacientes;
};

typedef NodoPaciente *pnodoPaciente;

class listaPacientes {
    public:
        listaPacientes() { primero = NULL; }
        ~listaPacientes();

        bool ListaVacia() { return primero == NULL; }
        bool ExisteID(int IDPaciente);
        void Insertar(int IDPaciente, string nombre, string fechaNacimiento,
                        string telefono, int codCiudad, int codPais, string correo);
        bool Buscar(int IDPaciente);
        void Mostrar();
    private:
        pnodoPaciente primero;
    };

listaPacientes::~listaPacientes() {
    pnodoPaciente aux = primero;
    while (aux != NULL) {
        pnodoPaciente borrar = aux;
        aux = aux->siguiente;
        delete borrar;
    }
    primero = NULL;
}

bool listaPacientes::ExisteID(int IDPaciente) {
    pnodoPaciente aux = primero;
    while (aux != NULL) {
        if (aux->IDPaciente == IDPaciente) 
            return true;
        aux = aux->siguiente;
    }
    return false;
}

void listaPacientes::Insertar(int IDPaciente, string nombre, string fechaNacimiento,
                                    string telefono, int codCiudad, int codPais, string correo) {
    pnodoPaciente nuevo = new NodoPaciente(IDPaciente, nombre, fechaNacimiento, telefono,
                                            codCiudad, codPais, correo);
    if (ListaVacia()) {
        primero = nuevo;
        } 
    else {
        pnodoPaciente aux = primero;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
        }
    }

bool listaPacientes::Buscar(int IDPaciente) {
    pnodoPaciente aux = primero;
    while (aux != NULL) {
        if (aux->IDPaciente == IDPaciente) {
            cout << endl << "IDPaciente: " << aux->IDPaciente << endl;
            cout << "Nombre: " << aux->nombre << endl;
            cout << "Fecha de nacimiento: " << aux->fechaNacimiento << endl;
            cout << "Telefono: " << aux->telefono << endl;
            cout << "Codigo de ciudad: " << aux->codCiudad << endl;
            cout << "Codigo de pais: " << aux->codPais << endl;
            cout << "Correo: " << aux->correo << endl;
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

void listaPacientes::Mostrar() {
    pnodoPaciente aux = primero;
    while (aux != NULL) {
        cout << aux->IDPaciente << " -> ";
        aux = aux->siguiente;
    }
    cout << "NULL";
}

class TablaHashingPaciente {
private:
    listaPacientes *tabla[Tam_TablaPaciente];

    int FuncionHash(int IDPaciente) {
        return IDPaciente % Tam_TablaPaciente;
    }

public:
    TablaHashingPaciente() {
        for (int i = 0; i < Tam_TablaPaciente; i++) {
            tabla[i] = new listaPacientes();
        }
    }
    ~TablaHashingPaciente() {
        for (int i = 0; i < Tam_TablaPaciente; i++) {
            delete tabla[i];
        }
    }

    void Insertar(int IDPaciente, string nombre, string fechaNacimiento, string telefono,
                  int codCiudad, int codPais, string correo,
                  listaCiudad &listaCiudades, Pais &listaPaises);
    bool Buscar(int IDPaciente);
    bool ExisteID(int IDPaciente);
    void Mostrar();
    void CargarArchivoPaciente(string nombreArchivo, listaCiudad &listaCiudades, Pais &listaPaises);
};

void TablaHashingPaciente::Insertar(int IDPaciente, string nombre, string fechaNacimiento,
                                     string telefono, int codCiudad, int codPais, string correo,
                                     listaCiudad &listaCiudades, Pais &listaPaises) {

    if (!listaPaises.ExistePais(codPais)) {
        cout << "El codigo de pais " << codPais << " no existe" << endl;
        return;
    }
  
    if (!listaCiudades.ExisteCiudad(codCiudad)) {
        cout << "El codigo de ciudad " << codCiudad << " no existe" << endl;
        return;
    }

    int pos = FuncionHash(IDPaciente);

    if (tabla[pos]->ExisteID(IDPaciente)) {
        cout << "El IDPaciente " << IDPaciente << " ya existe" << endl;
        return;
    }

    tabla[pos]->Insertar(IDPaciente, nombre, fechaNacimiento, telefono, codCiudad, codPais, correo);
    cout << "Paciente " << IDPaciente << " insertado en la posicion " << pos << endl;
}

bool TablaHashingPaciente::Buscar(int IDPaciente) {
    int pos = FuncionHash(IDPaciente);
    if (!tabla[pos]->Buscar(IDPaciente)) {
        cout << "El paciente con IDPaciente " << IDPaciente << " no existe" << endl;
        return false;
    }
    return true;
}

bool TablaHashingPaciente::ExisteID(int IDPaciente) {
    int pos = FuncionHash(IDPaciente);
    return tabla[pos]->ExisteID(IDPaciente);
}

void TablaHashingPaciente::Mostrar() {
    cout << "\nTabla Hash de Pacientes:\n";
    for (int i = 0; i < Tam_TablaPaciente; i++) {
        cout << "[" << i << "]: ";
        tabla[i]->Mostrar();
        cout << endl;
    }
}

void TablaHashingPaciente::CargarArchivoPaciente(string nombreArchivo, listaCiudad &listaCiudades, Pais &listaPaises) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) 
            continue;

        stringstream ss(linea);
        string campoID, nombre, fechaNacimiento, telefono, campoCodPais, campoCodCiudad, correo;

        getline(ss, campoID, ';');
        getline(ss, nombre, ';');
        getline(ss, fechaNacimiento, ';');
        getline(ss, telefono, ';');
        getline(ss, campoCodPais, ';');
        getline(ss, campoCodCiudad, ';');
        getline(ss, correo);

        int IDPaciente = stoi(campoID);
        int codPais = stoi(campoCodPais);
        int codCiudad = stoi(campoCodCiudad);

        Insertar(IDPaciente, nombre, fechaNacimiento, telefono, codCiudad, codPais, correo,
                 listaCiudades, listaPaises);
    }

    archivo.close();
    cout << "Archivo de pacientes cargado correctamente." << endl;
}