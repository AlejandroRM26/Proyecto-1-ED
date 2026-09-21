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

        int codigo = stoi(codigoStr);
        Insertar(codigo, nombre);
        }
    archivo.close();
    cout << "Archivo cargado correctamente." << endl;
}
 
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

#include <limits>

Pais paises;
listaCiudad ciudades;
TablaHashingPaciente pacientes;
listaEspecialidad especialidades;
TablaHashingMedico medicos;
listaHabitacion habitaciones;
Hospitalizaciones hospitalizaciones;
Citas citas;

const string CARPETA = "";

int leerEntero(string mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        cout << "Entrada invalida. Intente de nuevo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

string leerLinea(string mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.get();
}

void LeerArchivos() {
    paises.CargarDesdeArchivoPais(CARPETA + "Paises.txt");
    ciudades.CargarArchivoCiudad(CARPETA + "Ciudades.txt", paises);
    especialidades.CargarArchivoEspecialidad(CARPETA + "Especialidades.txt");
    pacientes.CargarArchivoPaciente(CARPETA + "Pacientes.txt", ciudades, paises);
    medicos.CargarArchivoMedico(CARPETA + "Medicos.txt", especialidades);
    habitaciones.CargarArchivoHabitacion(CARPETA + "Habitaciones.txt");
    hospitalizaciones.LeerDesdeArchivo(CARPETA + "Hospitalizaciones.txt", pacientes, habitaciones);
    citas.LeerDesdeArchivo(CARPETA + "Citas.txt", pacientes, medicos);

    cout << "\nTodos los archivos fueron leidos." << endl;
}

void InsertarPais() {
    int cod = leerEntero("Codigo de pais: ");
    string nombre = leerLinea("Nombre: ");
    paises.Insertar(cod, nombre);
}

void InsertarCiudad() {
    int codPais = leerEntero("Codigo de pais: ");
    int codCiudad = leerEntero("Codigo de ciudad: ");
    string nombre = leerLinea("Nombre: ");
    ciudades.Insertar(codPais, codCiudad, nombre, paises);
}

void InsertarPaciente() {
    int id = leerEntero("IDPaciente: ");
    string nombre = leerLinea("Nombre: ");
    string fecha = leerLinea("Fecha de nacimiento (dd-mm-aaaa): ");
    string telefono = leerLinea("Telefono: ");
    int codCiudad = leerEntero("Codigo de ciudad: ");
    int codPais = leerEntero("Codigo de pais: ");
    string correo = leerLinea("Correo: ");
    pacientes.Insertar(id, nombre, fecha, telefono, codCiudad, codPais, correo, ciudades, paises);
}

void InsertarEspecialidad() {
    int id = leerEntero("IDEspecialidad: ");
    string nombre = leerLinea("Nombre: ");
    string descripcion = leerLinea("Descripcion: ");
    especialidades.Insertar(id, nombre, descripcion);
}

void InsertarMedico() {
    int id = leerEntero("IDMedico: ");
    string nombre = leerLinea("Nombre: ");
    string telefono = leerLinea("Telefono: ");
    string correo = leerLinea("Correo: ");
    int idEspecialidad = leerEntero("IDEspecialidad: ");
    medicos.Insertar(id, nombre, telefono, correo, idEspecialidad, especialidades);
}

void InsertarHabitacion() {
    int id = leerEntero("IDHabitacion: ");
    string numero = leerLinea("Numero: ");
    string piso = leerLinea("Piso: ");
    int tipo = leerEntero("Tipo (1 individual, 2 compartida, 3 UCI): ");
    int estado = leerEntero("Estado (0 Disponible, 1 Ocupada): ");
    habitaciones.Insertar(id, numero, piso, tipo, estado);
}

void InsertarHospitalizacion() {
    int id = leerEntero("IDHospitalizacion: ");
    int idPaciente = leerEntero("IDPaciente: ");
    int idHabitacion = leerEntero("IDHabitacion: ");
    int idMedico = leerEntero("IDMedico: ");
    string fechaIngreso = leerLinea("Fecha de ingreso (dd-mm-aaaa): ");
    string fechaSalida = leerLinea("Fecha de salida (0000 si no indica): ");
    string motivo = leerLinea("Motivo: ");
    hospitalizaciones.Insertar(id, idPaciente, idHabitacion, idMedico, fechaIngreso, fechaSalida, motivo,
                                pacientes, habitaciones);
}

void InsertarCita() {
    int id = leerEntero("IDCita: ");
    int idPaciente = leerEntero("IDPaciente: ");
    int idMedico = leerEntero("IDMedico: ");
    int idEspecialidad = leerEntero("IDEspecialidad: ");
    string fecha = leerLinea("Fecha (dd-mm-aaaa): ");
    string hora = leerLinea("Hora (hh:mm): ");
    string motivo = leerLinea("Motivo: ");
    int estado = leerEntero("Estado (0 Pendiente, 1 Confirmada): ");
    citas.Insertar(id, idPaciente, idMedico, idEspecialidad, fecha, hora, motivo, estado, pacientes, medicos);
}

void MenuInsertar() {
    int opcion;
    do {
        cout << "\n--- Insertar ---" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Paciente" << endl;
        cout << "4. Medico" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Cita" << endl;
        cout << "7. Habitacion" << endl;
        cout << "8. Hospitalizacion" << endl;
        cout << "0. Volver" << endl;
        opcion = leerEntero("Opcion: ");

        switch (opcion) {
            case 1: InsertarPais(); break;
            case 2: InsertarCiudad(); break;
            case 3: InsertarPaciente(); break;
            case 4: InsertarMedico(); break;
            case 5: InsertarEspecialidad(); break;
            case 6: InsertarCita(); break;
            case 7: InsertarHabitacion(); break;
            case 8: InsertarHospitalizacion(); break;
            case 0: break;
            default: cout << "Opcion invalida" << endl;
        }
    } while (opcion != 0);
}

void BuscarPais() {
    int cod = leerEntero("Codigo de pais: ");
    paises.BuscarPais(cod);
    cout << endl;
}

void BuscarCiudad() {
    int codPais = leerEntero("Codigo de pais: ");
    int codCiudad = leerEntero("Codigo de ciudad: ");
    ciudades.BuscarCiudad(codCiudad, codPais, paises);
}

void BuscarPaciente() {
    int id = leerEntero("IDPaciente: ");
    pacientes.Buscar(id);
}

void BuscarEspecialidad() {
    int id = leerEntero("IDEspecialidad: ");
    especialidades.BuscarEspecialidad(id);
}

void BuscarMedico() {
    int id = leerEntero("IDMedico: ");
    medicos.Buscar(id);
}

void BuscarHabitacion() {
    int id = leerEntero("IDHabitacion: ");
    habitaciones.BuscarHabitacion(id);
}

void BuscarHospitalizacion() {
    int id = leerEntero("IDHospitalizacion: ");
    hospitalizaciones.Buscar(id, pacientes, habitaciones);
}

void BuscarCita() {
    int id = leerEntero("IDCita: ");
    citas.Buscar(id, pacientes, medicos);
}

void MenuBuscar() {
    int opcion;
    do {
        cout << "\n--- Buscar ---" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Paciente" << endl;
        cout << "4. Medico" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Cita" << endl;
        cout << "7. Habitacion" << endl;
        cout << "8. Hospitalizacion" << endl;
        cout << "0. Volver" << endl;
        opcion = leerEntero("Opcion: ");

        switch (opcion) {
            case 1: BuscarPais(); break;
            case 2: BuscarCiudad(); break;
            case 3: BuscarPaciente(); break;
            case 4: BuscarMedico(); break;
            case 5: BuscarEspecialidad(); break;
            case 6: BuscarCita(); break;
            case 7: BuscarHabitacion(); break;
            case 8: BuscarHospitalizacion(); break;
            case 0: break;
            default: cout << "Opcion invalida" << endl;
        }
    } while (opcion != 0);
}

void MenuMantenimiento() {
    int opcion;
    do {
        cout << "\n--- Mantenimiento de la Base de Datos ---" << endl;
        cout << "1. Inserciones" << endl;
        cout << "2. Busqueda" << endl;
        cout << "0. Volver" << endl;
        opcion = leerEntero("Opcion: ");

        switch (opcion) {
            case 1: MenuInsertar(); break;
            case 2: MenuBuscar(); break;
            case 0: break;
            default: cout << "Opcion invalida" << endl;
        }
    } while (opcion != 0);
}

void MenuPrincipal() {
    int opcion;
    do {
        cout << "\n================ MENU PRINCIPAL ================" << endl;
        cout << "1. Leer Archivos" << endl;
        cout << "2. Mantenimiento de la Base de Datos" << endl;
        cout << "0. Salir" << endl;
        opcion = leerEntero("Opcion: ");

        switch (opcion) {
            case 1: LeerArchivos(); break;
            case 2: MenuMantenimiento(); break;
            case 0: cout << "Saliendo del sistema..." << endl; break;
            default: cout << "Opcion invalida" << endl;
        }
    } while (opcion != 0);
}

int main() {
    cout << "Sistema Hospitalario - Estructuras de Datos" << endl;

    MenuPrincipal();
    return 0;
}
