#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Paciente.cpp"
#include "Habitacion.cpp"

using namespace std;

class NodoHospitalizacion {
    public:
        NodoHospitalizacion(int pID, int pIDPaciente, int pIDHabitacion, int pIDMedico,
                            string pFechaIngreso, string pFechaSalida, string pMotivo) {
            IDHospitalizacion = pID;
            IDPaciente = pIDPaciente;
            IDHabitacion = pIDHabitacion;
            IDMedico = pIDMedico;
            fechaIngreso = pFechaIngreso;
            fechaSalida = pFechaSalida;
            motivo = pMotivo;
            siguiente = NULL;
            anterior = NULL;
            }

    private:
        int IDHospitalizacion;
        int IDPaciente;
        int IDHabitacion;
        int IDMedico;
        string fechaIngreso;
        string fechaSalida;
        string motivo;
        
        NodoHospitalizacion *siguiente;
        NodoHospitalizacion *anterior;

        friend class Hospitalizaciones;
};

typedef NodoHospitalizacion *pnodoHospitalizacion;

class Hospitalizaciones {
    public:
        Hospitalizaciones() { primero = NULL; ultimo = NULL; }
        ~Hospitalizaciones();

        bool ListaVacia() { return primero == NULL; }
        bool ExisteID(int IDHospitalizacion);

        void Insertar(int IDHospitalizacion, int IDPaciente, int IDHabitacion, int IDMedico,
                      string fechaIngreso, string fechaSalida, string motivo,
                      TablaHashingPaciente &pacientes, listaHabitacion &habitaciones);
        bool Buscar(int IDHospitalizacion, TablaHashingPaciente &pacientes, listaHabitacion &habitaciones);
        void Mostrar();

        void LeerDesdeArchivo(string nombreArchivo, TablaHashingPaciente &pacientes, listaHabitacion &habitaciones);

    private:
        pnodoHospitalizacion primero;
        pnodoHospitalizacion ultimo;

        bool TieneFechaSalidaRegistrada(string fechaSalida);
    };

Hospitalizaciones::~Hospitalizaciones() {
    pnodoHospitalizacion aux = primero;
    while (aux != NULL) {
        pnodoHospitalizacion borrar = aux;
        aux = aux->siguiente;
        delete borrar;
    }
    primero = NULL;
    ultimo = NULL;
}

bool Hospitalizaciones::ExisteID(int IDHospitalizacion) {
    pnodoHospitalizacion aux = primero;
    while (aux != NULL) {
        if (aux->IDHospitalizacion == IDHospitalizacion)
            return true;
        aux = aux->siguiente;
    }
    return false;
}

const string SIN_FECHA_SALIDA = "0000";

bool Hospitalizaciones::TieneFechaSalidaRegistrada(string fechaSalida) {
    return fechaSalida != SIN_FECHA_SALIDA;
}

void Hospitalizaciones::Insertar(int IDHospitalizacion, int IDPaciente, int IDHabitacion, int IDMedico,
                                  string fechaIngreso, string fechaSalida, string motivo,
                                  TablaHashingPaciente &pacientes, listaHabitacion &habitaciones) {

    if (!pacientes.ExisteID(IDPaciente)) {
        cout << "El IDPaciente " << IDPaciente << " no existe" << endl;
        return;
    }

    if (!habitaciones.ExisteHabitacion(IDHabitacion)) {
        cout << "El IDHabitacion " << IDHabitacion << " no existe" << endl;
        return;
    }

    if (ExisteID(IDHospitalizacion)) {
        cout << "El IDHospitalizacion " << IDHospitalizacion << " ya existe" << endl;
        return;
    }

    pnodoHospitalizacion nuevo = new NodoHospitalizacion(IDHospitalizacion, IDPaciente, IDHabitacion, IDMedico,
                                                          fechaIngreso, fechaSalida, motivo);

    if (ListaVacia()) {
        primero = nuevo;
        ultimo = nuevo;
    }
    else {
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }

    cout << "Hospitalizacion " << IDHospitalizacion << " insertada correctamente." << endl;
}

bool Hospitalizaciones::Buscar(int IDHospitalizacion, TablaHashingPaciente &pacientes, listaHabitacion &habitaciones) {
    pnodoHospitalizacion aux = primero;
    while (aux != NULL) {
        if (aux->IDHospitalizacion == IDHospitalizacion) {

            if (!pacientes.ExisteID(aux->IDPaciente)) {
                cout << "El IDPaciente " << aux->IDPaciente << " asociado no existe" << endl;
                return false;
            }

            if (!habitaciones.ExisteHabitacion(aux->IDHabitacion)) {
                cout << "El IDHabitacion " << aux->IDHabitacion << " asociado no existe" << endl;
                return false;
            }

            cout << endl << "IDHospitalizacion: " << aux->IDHospitalizacion << endl;
            cout << "IDPaciente: " << aux->IDPaciente << endl;
            cout << "IDHabitacion: " << aux->IDHabitacion << endl;
            cout << "IDMedico: " << aux->IDMedico << endl;
            cout << "Fecha de ingreso: " << aux->fechaIngreso << endl;

            if (TieneFechaSalidaRegistrada(aux->fechaSalida)) {
                cout << "Fecha de salida: " << aux->fechaSalida << endl;
            }
            else {
                cout << "Fecha de salida: No indica (paciente aun hospitalizado)" << endl;
            }

            cout << "Motivo: " << aux->motivo << endl;
            return true;
        }
        aux = aux->siguiente;
    }

    cout << "El IDHospitalizacion " << IDHospitalizacion << " no existe" << endl;
    return false;
}

void Hospitalizaciones::Mostrar() {
    if (ListaVacia()) {
        cout << "No hay hospitalizaciones registradas" << endl;
        return;
    }

    pnodoHospitalizacion aux = primero;
    while (aux != NULL) {
        cout << aux->IDHospitalizacion << " -> ";
        aux = aux->siguiente;
    }
    cout << "NULL" << endl;
}

void Hospitalizaciones::LeerDesdeArchivo(string nombreArchivo, TablaHashingPaciente &pacientes, listaHabitacion &habitaciones) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    int numeroLinea = 0;

    while (getline(archivo, linea)) {
        numeroLinea++;

        if (linea.empty()) continue;

        stringstream ss(linea);
        string campoID, campoIDPaciente, campoIDHabitacion, campoIDMedico;
        string fechaIngreso, fechaSalida, motivo;

        getline(ss, campoID, ';');
        getline(ss, campoIDPaciente, ';');
        getline(ss, campoIDHabitacion, ';');
        getline(ss, campoIDMedico, ';');
        getline(ss, fechaIngreso, ';');
        getline(ss, fechaSalida, ';');
        getline(ss, motivo); // el motivo puede tener espacios, se toma hasta el final de la linea

        if (campoID.empty() || campoIDPaciente.empty() || campoIDHabitacion.empty() ||
            campoIDMedico.empty() || fechaIngreso.empty() || fechaSalida.empty() || motivo.empty()) {
            cout << "Linea " << numeroLinea << " mal formada, se omite: " << linea << endl;
            continue;
        }

        int IDHospitalizacion = stoi(campoID);
        int IDPaciente = stoi(campoIDPaciente);
        int IDHabitacion = stoi(campoIDHabitacion);
        int IDMedico = stoi(campoIDMedico);

        Insertar(IDHospitalizacion, IDPaciente, IDHabitacion, IDMedico,
                 fechaIngreso, fechaSalida, motivo, pacientes, habitaciones);
    }

    archivo.close();
}