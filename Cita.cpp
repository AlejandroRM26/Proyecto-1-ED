#pragma once
//Hecho por: David Leon

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Paciente.cpp"
#include "Medico.cpp"

using namespace std;

class NodoCita {
    public:
        NodoCita(int pID, int pIDPaciente, int pIDMedico, int pIDEspecialidad,
                  string pFecha, string pHora, string pMotivo, int pEstado) {
            IDCita = pID;
            IDPaciente = pIDPaciente;
            IDMedico = pIDMedico;
            IDEspecialidad = pIDEspecialidad;
            fecha = pFecha;
            hora = pHora;
            motivo = pMotivo;
            estado = pEstado;
            siguiente = NULL;
            anterior = NULL;
        }

    private:
        int IDCita;
        int IDPaciente;
        int IDMedico;
        int IDEspecialidad;
        string fecha;
        string hora;
        string motivo;
        int estado;

        NodoCita *siguiente;
        NodoCita *anterior;

        friend class Citas;
};

typedef NodoCita *pnodoCita;

class Citas {
    public:
        Citas() { primero = NULL; ultimo = NULL; }
        ~Citas();

        bool ListaVacia() { return primero == NULL; }
        bool ExisteID(int IDCita);

        void Insertar(int IDCita, int IDPaciente, int IDMedico, int IDEspecialidad,
                      string fecha, string hora, string motivo, int estado,
                      TablaHashingPaciente &pacientes, TablaHashingMedico &medicos);
        bool Buscar(int IDCita, TablaHashingPaciente &pacientes, TablaHashingMedico &medicos);
        bool ModificarMotivoEstado(int IDCita, string nuevoMotivo, int nuevoEstado,
                                    TablaHashingPaciente &pacientes, TablaHashingMedico &medicos);
        void Mostrar();

        void LeerDesdeArchivo(string nombreArchivo, TablaHashingPaciente &pacientes, TablaHashingMedico &medicos);

    private:
        pnodoCita primero;
        pnodoCita ultimo;
};

Citas::~Citas() {
    pnodoCita aux = primero;
    while (aux != NULL) {
        pnodoCita borrar = aux;
        aux = aux->siguiente;
        delete borrar;
    }
    primero = NULL;
    ultimo = NULL;
}

bool Citas::ExisteID(int IDCita) {
    pnodoCita aux = primero;
    while (aux != NULL) {
        if (aux->IDCita == IDCita)
            return true;
        aux = aux->siguiente;
    }
    return false;
}

void Citas::Insertar(int IDCita, int IDPaciente, int IDMedico, int IDEspecialidad,
                      string fecha, string hora, string motivo, int estado,
                      TablaHashingPaciente &pacientes, TablaHashingMedico &medicos) {

    if (!pacientes.ExisteID(IDPaciente)) {
        cout << "El IDPaciente " << IDPaciente << " no existe" << endl;
        return;
    }

    if (!medicos.Buscar(IDMedico)) {
        return;
    }

    if (ExisteID(IDCita)) {
        cout << "El IDCita " << IDCita << " ya existe" << endl;
        return;
    }

    pnodoCita nuevo = new NodoCita(IDCita, IDPaciente, IDMedico, IDEspecialidad,
                                    fecha, hora, motivo, estado);

    if (ListaVacia()) {
        primero = nuevo;
        ultimo = nuevo;
    }
    else {
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }

    cout << "Cita " << IDCita << " insertada correctamente." << endl;
}

bool Citas::Buscar(int IDCita, TablaHashingPaciente &pacientes, TablaHashingMedico &medicos) {
    pnodoCita aux = primero;
    while (aux != NULL) {
        if (aux->IDCita == IDCita) {

            if (!pacientes.ExisteID(aux->IDPaciente)) {
                cout << "El IDPaciente " << aux->IDPaciente << " asociado no existe" << endl;
                return false;
            }

            if (!medicos.Buscar(aux->IDMedico)) {
                return false;
            }

            cout << endl << "IDCita: " << aux->IDCita << endl;
            cout << "IDPaciente: " << aux->IDPaciente << endl;
            cout << "IDMedico: " << aux->IDMedico << endl;
            cout << "IDEspecialidad: " << aux->IDEspecialidad << endl;
            cout << "Fecha: " << aux->fecha << endl;
            cout << "Hora: " << aux->hora << endl;
            cout << "Motivo: " << aux->motivo << endl;
            cout << "Estado: " << (aux->estado == 1 ? "Confirmada" : "Pendiente") << endl;
            return true;
        }
        aux = aux->siguiente;
    }

    cout << "El IDCita " << IDCita << " no existe" << endl;
    return false;
}

bool Citas::ModificarMotivoEstado(int IDCita, string nuevoMotivo, int nuevoEstado,
                                   TablaHashingPaciente &pacientes, TablaHashingMedico &medicos) {
    pnodoCita aux = primero;
    while (aux != NULL) {
        if (aux->IDCita == IDCita) {

            if (!pacientes.ExisteID(aux->IDPaciente)) {
                cout << "El IDPaciente " << aux->IDPaciente << " asociado no existe" << endl;
                return false;
            }

            if (!medicos.Buscar(aux->IDMedico)) {
                return false;
            }

            aux->motivo = nuevoMotivo;
            aux->estado = nuevoEstado;
            cout << "Motivo y estado actualizados correctamente." << endl;
            return true;
        }
        aux = aux->siguiente;
    }

    cout << "El IDCita " << IDCita << " no existe" << endl;
    return false;
}

void Citas::Mostrar() {
    if (ListaVacia()) {
        cout << "No hay citas registradas" << endl;
        return;
    }

    pnodoCita aux = primero;
    while (aux != NULL) {
        cout << aux->IDCita << " -> ";
        aux = aux->siguiente;
    }
    cout << "NULL" << endl;
}

void Citas::LeerDesdeArchivo(string nombreArchivo, TablaHashingPaciente &pacientes, TablaHashingMedico &medicos) {
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
        string campoID, campoIDPaciente, campoIDMedico, campoIDEspecialidad;
        string fecha, hora, motivo, campoEstado;

        getline(ss, campoID, ';');
        getline(ss, campoIDPaciente, ';');
        getline(ss, campoIDMedico, ';');
        getline(ss, campoIDEspecialidad, ';');
        getline(ss, fecha, ';');
        getline(ss, hora, ';');
        getline(ss, motivo, ';');
        getline(ss, campoEstado);

        if (campoID.empty() || campoIDPaciente.empty() || campoIDMedico.empty() ||
            campoIDEspecialidad.empty() || fecha.empty() || hora.empty() ||
            motivo.empty() || campoEstado.empty()) {
            cout << "Linea " << numeroLinea << " mal formada, se omite: " << linea << endl;
            continue;
        }

        int IDCita = stoi(campoID);
        int IDPaciente = stoi(campoIDPaciente);
        int IDMedico = stoi(campoIDMedico);
        int IDEspecialidad = stoi(campoIDEspecialidad);
        int estado = stoi(campoEstado);

        Insertar(IDCita, IDPaciente, IDMedico, IDEspecialidad, fecha, hora, motivo, estado,
                 pacientes, medicos);
    }

    archivo.close();
}