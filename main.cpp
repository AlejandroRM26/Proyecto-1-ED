// Elaborado por: David Leon y Alejandro Rodriguez

#include <iostream>
#include <string>
#include <limits>
#include "Hospitalizacion.cpp"
#include "Cita.cpp"

using namespace std;

Pais paises;
listaCiudad ciudades;
TablaHashingPaciente pacientes;
listaEspecialidad especialidades;
TablaHashingMedico medicos;
listaHabitacion habitaciones;
Hospitalizaciones hospitalizaciones;
Citas citas;

const string CARPETA = "Archivos/";

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

// ---------- Carga de archivos ----------
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

// ---------- Insertar ----------
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

// ---------- Buscar ----------
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

// ---------- Menu principal ----------
void MenuPrincipal() {
    int opcion;
    do {
        cout << "\n================ MENU PRINCIPAL ================" << endl;
        cout << "1. Leer Archivos" << endl;
        cout << "2. Insertar" << endl;
        cout << "3. Buscar" << endl;
        cout << "0. Salir" << endl;
        opcion = leerEntero("Opcion: ");

        switch (opcion) {
            case 1: LeerArchivos(); break;
            case 2: MenuInsertar(); break;
            case 3: MenuBuscar(); break;
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