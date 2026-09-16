//Hecho por: David Leon

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Especialidad.cpp"

using namespace std;

const int Tam_TablaMedico = 13;

class NodoMedico {
    public:
        NodoMedico(int pID, string pNombre, string pTelefono, string pCorreo, int pIdEspecialidad) {
            IDMedico = pID;
            nombre = pNombre;
            telefono = pTelefono;
            correo = pCorreo;
            idEspecialidad = pIdEspecialidad;
            siguiente = NULL;
        }

    private:
        int IDMedico;
        string nombre;
        string telefono;
        string correo;
        int idEspecialidad;
        NodoMedico *siguiente;

        friend class listaMedicos;
};

typedef NodoMedico *pnodoMedico;

class listaMedicos {
    public:
        listaMedicos() { primero = NULL; }
        ~listaMedicos();

        bool ListaVacia() { return primero == NULL; }
        bool ExisteID(int IDMedico);
        void Insertar(int IDMedico, string nombre, string telefono, string correo, int idEspecialidad);
        bool Buscar(int IDMedico);
        bool ModificarTelefonoCorreo(int IDMedico, string telefono, string correo);
        void Mostrar();
    private:
        pnodoMedico primero;
};

listaMedicos::~listaMedicos() {
    pnodoMedico aux = primero;
    while (aux != NULL) {
        pnodoMedico borrar = aux;
        aux = aux->siguiente;
        delete borrar;
    }
    primero = NULL;
}

bool listaMedicos::ExisteID(int IDMedico) {
    pnodoMedico aux = primero;
    while (aux != NULL) {
        if (aux->IDMedico == IDMedico)
            return true;
        aux = aux->siguiente;
    }
    return false;
}

void listaMedicos::Insertar(int IDMedico, string nombre, string telefono, string correo, int idEspecialidad) {
    pnodoMedico nuevo = new NodoMedico(IDMedico, nombre, telefono, correo, idEspecialidad);
    if (ListaVacia()) {
        primero = nuevo;
    }
    else {
        pnodoMedico aux = primero;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
    }
}

bool listaMedicos::Buscar(int IDMedico) {
    pnodoMedico aux = primero;
    while (aux != NULL) {
        if (aux->IDMedico == IDMedico) {
            cout << endl << "IDMedico: " << aux->IDMedico << endl;
            cout << "Nombre: " << aux->nombre << endl;
            cout << "Telefono: " << aux->telefono << endl;
            cout << "Correo: " << aux->correo << endl;
            cout << "Codigo de especialidad: " << aux->idEspecialidad << endl;
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

bool listaMedicos::ModificarTelefonoCorreo(int IDMedico, string telefono, string correo) {
    pnodoMedico aux = primero;
    while (aux != NULL) {
        if (aux->IDMedico == IDMedico) {
            aux->telefono = telefono;
            aux->correo = correo;
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

void listaMedicos::Mostrar() {
    pnodoMedico aux = primero;
    while (aux != NULL) {
        cout << aux->IDMedico << " -> ";
        aux = aux->siguiente;
    }
    cout << "NULL";
}

class TablaHashingMedico {
private:
    listaMedicos *tabla[Tam_TablaMedico];

    int FuncionHash(int IDMedico) {
        return IDMedico % Tam_TablaMedico;
    }

public:
    TablaHashingMedico() {
        for (int i = 0; i < Tam_TablaMedico; i++) {
            tabla[i] = new listaMedicos();
        }
    }
    ~TablaHashingMedico() {
        for (int i = 0; i < Tam_TablaMedico; i++) {
            delete tabla[i];
        }
    }

    void Insertar(int IDMedico, string nombre, string telefono, string correo, int idEspecialidad,
                  listaEspecialidad &listaEspecialidades);
    bool Buscar(int IDMedico);
    bool ModificarTelefonoCorreo(int IDMedico, string telefono, string correo);
    void Mostrar();
    void CargarArchivoMedico(string nombreArchivo, listaEspecialidad &listaEspecialidades);
};

void TablaHashingMedico::Insertar(int IDMedico, string nombre, string telefono, string correo,
                                   int idEspecialidad, listaEspecialidad &listaEspecialidades) {

    if (!listaEspecialidades.ExisteEspecialidad(idEspecialidad)) {
        cout << "El codigo de especialidad " << idEspecialidad << " no existe" << endl;
        return;
    }

    int pos = FuncionHash(IDMedico);

    if (tabla[pos]->ExisteID(IDMedico)) {
        cout << "El IDMedico " << IDMedico << " ya existe" << endl;
        return;
    }

    tabla[pos]->Insertar(IDMedico, nombre, telefono, correo, idEspecialidad);
    cout << "Medico " << IDMedico << " insertado en la posicion " << pos << endl;
}

bool TablaHashingMedico::Buscar(int IDMedico) {
    int pos = FuncionHash(IDMedico);
    if (!tabla[pos]->Buscar(IDMedico)) {
        cout << "El medico con IDMedico " << IDMedico << " no existe" << endl;
        return false;
    }
    return true;
}

bool TablaHashingMedico::ModificarTelefonoCorreo(int IDMedico, string telefono, string correo) {
    int pos = FuncionHash(IDMedico);
    if (!tabla[pos]->ModificarTelefonoCorreo(IDMedico, telefono, correo)) {
        cout << "El medico con IDMedico " << IDMedico << " no existe" << endl;
        return false;
    }
    cout << "Telefono y correo actualizados correctamente." << endl;
    return true;
}

void TablaHashingMedico::Mostrar() {
    cout << "\nTabla Hash de Medicos:\n";
    for (int i = 0; i < Tam_TablaMedico; i++) {
        cout << "[" << i << "]: ";
        tabla[i]->Mostrar();
        cout << endl;
    }
}

void TablaHashingMedico::CargarArchivoMedico(string nombreArchivo, listaEspecialidad &listaEspecialidades) {
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
        string campoID, nombre, telefono, correo, campoIdEspecialidad;

        getline(ss, campoID, ';');
        getline(ss, nombre, ';');
        getline(ss, telefono, ';');
        getline(ss, correo, ';');
        getline(ss, campoIdEspecialidad);

        int IDMedico = stoi(campoID);
        int idEspecialidad = stoi(campoIdEspecialidad);

        Insertar(IDMedico, nombre, telefono, correo, idEspecialidad, listaEspecialidades);
    }

    archivo.close();
    cout << "Archivo de medicos cargado correctamente." << endl;
}