#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
void ordenar(vector<T*>& lista, bool criterio(T* a, T* b)) {
    if (lista.empty()) throw runtime_error("No hay documentos para ordenar.");
    if (!criterio) throw invalid_argument("Criterio de ordenamiento invalido.");

    int n = lista.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (!criterio(lista[j], lista[j + 1])) {
                T* temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}


class Documento {
private:
    int numero;
    string tipo;
    string fecha;
    string calificacion;
public:
    Documento(int n, string t, string f, string c)
        : numero(n), tipo(t), fecha(f), calificacion(c) {}

    int getNumero() const { return numero; }
    string getTipo() const { return tipo; }
    string getFecha() const { return fecha; }
    string getCalificacion() const { return calificacion; }

    void setTipo(const string& type){ tipo = type; }
    void setFecha(const string& date){ fecha = date; }
    void setCalificacion(const string& grade){ calificacion = grade; }

    virtual void mostrarInfo() const{
        cout << "Numero: " << numero << '\n';
        cout << "Tipo: " << tipo << '\n';
        cout << "Fecha: " << fecha << '\n';
        cout << "Calificacion: " << calificacion << '\n';
    }

    virtual ~Documento() {}
};

class Contrato : public Documento {
private:
    string PartesInvo;
public:
    Contrato(int n, string t, string f, string c, string partes)
        : Documento(n, t, f, c), PartesInvo(partes) {}

    void mostrarInfo() const override {
        Documento::mostrarInfo();
        cout << "Partes Involucradas: " << PartesInvo << '\n';
    }
};

class Testamento : public Documento {
private:
    string NombreTestador;
    string beneficiario;
public:
    Testamento(int n, string t, string f, string c, string test, string benf)
        : Documento(n, t, f, c), NombreTestador(test), beneficiario(benf) {}

    void mostrarInfo() const override {
        Documento::mostrarInfo();
        cout << "Nombre Testador: " << NombreTestador << '\n';
        cout << "Beneficiario: " << beneficiario << '\n';
    }
};

class Factura : public Documento {
private:
    string NombreCliente;
    double MontoTotal;
    string MetodoPago;
public:
    Factura(int n, string t, string f, string c, string client, double mont, string metod)
        : Documento(n, t, f, c), NombreCliente(client), MontoTotal(mont), MetodoPago(metod) {}

    void mostrarInfo() const override {
        Documento::mostrarInfo();
        cout << "Cliente: " << NombreCliente << '\n';
        cout << "Monto Total: " << MontoTotal << '\n';
        cout << "Metodo de Pago: " << MetodoPago << '\n';
    }
};

class EscrituraPublica : public Documento {
private:
    string actoJuridico;
    string inmuebleDetalle;
    string intervinientes;
public:
    EscrituraPublica(int n, string t, string f, string c,
                     string aJ, string iD, string interv)
        : Documento(n, t, f, c), actoJuridico(aJ), inmuebleDetalle(iD), intervinientes(interv) {}

    void mostrarInfo() const override {
        Documento::mostrarInfo();
        cout << "Acto juridico: " << actoJuridico << '\n';
        cout << "Detalle del inmueble: " << inmuebleDetalle << '\n';
        cout << "Intervinientes: " << intervinientes << '\n';
    }
};

class PoderNotarial : public Documento {
private:
    string otorgante;
    string apoderado;
    string poder;
public:
    PoderNotarial(int n, string t, string f, string c,
                  string ot, string ap, string p)
        : Documento(n, t, f, c), otorgante(ot), apoderado(ap), poder(p) {}

    void mostrarInfo() const override {
        Documento::mostrarInfo();
        cout << "Otorgante: " << otorgante << '\n';
        cout << "Apoderado: " << apoderado << '\n';
        cout << "Poder: " << poder << '\n';
    }
};

class DeclaracionJuramentada : public Documento {
private:
    string declarante;
    string contenido;
public:
    DeclaracionJuramentada(int n, string t, string f, string c, string dec, string cont)
        : Documento(n, t, f, c), declarante(dec), contenido(cont) {}

    void mostrarInfo() const override{
        Documento::mostrarInfo();
        cout << "Declarante: " << declarante << '\n';
        cout << "Contenido de la declaración: " << contenido << '\n';
    }
};

class ControlDocumento {
public:
    void validarNumero(int n) {
        if (n <= 0) throw invalid_argument("El numero debe ser mayor a 0.");
    }

    void validarTexto(const string& texto) {
        if (texto.empty()) throw invalid_argument("El campo de texto no puede estar vacio.");
        for (char c : texto)
            if (isdigit(c))
                throw invalid_argument("El texto no puede contener numeros.");
    }

    bool existeDocumento(const vector<Documento*>& docs, int num) {
        for (auto d : docs)
            if (d->getNumero() == num) return true;
        return false;
    }
};

      bool ordenarPorNumero(Documento*a, Documento*b){
         return a->getNumero()<b->getNumero(); 
      }
        bool ordenarPorTipo(Documento*a, Documento*b){
            return a->getTipo()<b->getTipo(); 
        }
        bool ordenarPorFecha(Documento*a, Documento*b){
            return a->getFecha()<b->getFecha(); 
        }

        bool ordenarPorCalificacion(Documento*a,Documento*b){
            return a->getCalificacion()<b->getCalificacion();
        }

class GestorDocumento {
private:
    vector<Documento*> documentos;
    ControlDocumento control;

    void limpiarBuffer() {
        int c;
        while ((c = cin.get()) != '\n' && c != EOF) {}
    }

public:
    void AgregarDocumento() {
        try {
            int tipoDoc;
            cout << "Seleccione tipo de documento:\n1. Contrato\n2. Testamento\n3. Factura\n4. Escritura Publica\n5. Poder notarial\n6. Declaracion Juramentada\nOpcion: ";
            if (!(cin >> tipoDoc)) throw invalid_argument("Entrada no numerica para tipo de documento.");
            limpiarBuffer();

            if (tipoDoc < 1 || tipoDoc > 6) throw out_of_range("Opcion de documento no valida.");

            int numero;
            string tipo, fecha, calificacion;

            cout << "Ingrese numero: ";
            if (!(cin >> numero)) throw invalid_argument("Entrada no numerica para numero de documento.");
            limpiarBuffer();

            control.validarNumero(numero);
            if (control.existeDocumento(documentos, numero))
                throw runtime_error("El numero de documento ya existe.");

            cout << "Ingrese tipo: ";
            getline(cin, tipo);
            control.validarTexto(tipo);

            cout << "Ingrese fecha: ";
            getline(cin, fecha);
            control.validarTexto(fecha);

            cout << "Ingrese calificacion: ";
            getline(cin, calificacion);
            control.validarTexto(calificacion);

            Documento* nuevo = nullptr;

            if (tipoDoc == 1) { 
                string partes;
                cout << "Ingrese partes involucradas: ";
                getline(cin, partes);
                control.validarTexto(partes);
                nuevo = new Contrato(numero, tipo, fecha, calificacion, partes);

            } else if (tipoDoc == 2) { 
                string testador, beneficiario;
                cout << "Ingrese nombre del testador: ";
                getline(cin, testador);
                control.validarTexto(testador);

                cout << "Ingrese beneficiario: ";
                getline(cin, beneficiario);
                control.validarTexto(beneficiario);

                nuevo = new Testamento(numero, tipo, fecha, calificacion, testador, beneficiario);

            } else if (tipoDoc == 3) { 
                string cliente, metodo;
                double monto;
                cout << "Ingrese nombre del cliente: ";
                getline(cin, cliente);
                control.validarTexto(cliente);

                cout << "Ingrese monto total: ";
                if (!(cin >> monto)) throw invalid_argument("Monto invalido.");
                limpiarBuffer();

                cout << "Ingrese metodo de pago: ";
                getline(cin, metodo);
                control.validarTexto(metodo);

                nuevo = new Factura(numero, tipo, fecha, calificacion, cliente, monto, metodo);

            } else if (tipoDoc == 4) { 
                string actojur, detalleIn, intervinientes;
                cout << "Ingrese el acto juridico: ";
                getline(cin, actojur);
                control.validarTexto(actojur);

                cout << "Ingrese detalle del inmueble: ";
                getline(cin, detalleIn);
                control.validarTexto(detalleIn);

                cout << "Ingrese intervinientes: ";
                getline(cin, intervinientes);
                control.validarTexto(intervinientes);

                nuevo = new EscrituraPublica(numero, tipo, fecha, calificacion, actojur, detalleIn, intervinientes);

            } else if (tipoDoc == 5) {
                string otorgante, apoderado, poder;
                cout << "Ingrese el otorgante: ";
                getline(cin, otorgante);
                control.validarTexto(otorgante);

                cout << "Ingrese el apoderado: ";
                getline(cin, apoderado);
                control.validarTexto(apoderado);

                cout << "Ingrese el alcance del poder: ";
                getline(cin, poder);
                control.validarTexto(poder);

                nuevo = new PoderNotarial(numero, tipo, fecha, calificacion, otorgante, apoderado, poder);

            } else if (tipoDoc == 6) { 
                string declarante, declaracion;
                cout << "Ingrese el declarante: ";
                getline(cin, declarante);
                control.validarTexto(declarante);

                cout << "Ingrese la declaracion: ";
                getline(cin, declaracion);
                control.validarTexto(declaracion);

                nuevo = new DeclaracionJuramentada(numero, tipo, fecha, calificacion, declarante, declaracion);
            }

            if (nuevo != nullptr) {
                documentos.push_back(nuevo);
                cout << "Documento agregado correctamente.\n";
            } else {
                cout << "No se creo ningun documento.\n";
            }

        } catch (const exception& e) {
            cout << "Error al agregar documento: " << e.what() << '\n';
            cin.clear();
            limpiarBuffer();
        }
    }

    void listarDocumentos() const {
        if (documentos.empty()) {
            cout << "No existen documentos registrados.\n";
            return;
        }
        for (auto d : documentos) {
            d->mostrarInfo();
            cout << "---------------------\n";
        }
    }

    void buscarDocumento() {
        try {
            if (documentos.empty())
                throw runtime_error("No existen documentos registrados.");

            int num;
            cout << "Ingrese numero del documento a buscar: ";
            if (!(cin >> num)) throw invalid_argument("Entrada no valida.");
            limpiarBuffer();

            if (!control.existeDocumento(documentos, num))
                throw runtime_error("Documento no registrado");

            for (auto d : documentos) {
                if (d->getNumero() == num) {
                    d->mostrarInfo();
                    return;
                }
            }

        } catch (const exception& e) {
            cout << "Error en busqueda: " << e.what() << '\n';
            cin.clear();
            limpiarBuffer();
        }
    }

    void modificarDocumento() {
        try {
            if (documentos.empty())
                throw runtime_error("No existen documentos registrados");

            int num;
            string newDate, newType, newGrade;

            cout << "Ingrese el numero de documento a modificar: ";
            if (!(cin >> num)) throw invalid_argument("Numero invalido");
            limpiarBuffer();

            if (!control.existeDocumento(documentos, num))
                throw runtime_error("Documento no encontrado");

            for (auto d : documentos) {
                if (d->getNumero() == num) {
                    cout << "Informacion actual:\n";
                    d->mostrarInfo();

                    cout << "Ingresa el nuevo tipo: ";
                    getline(cin, newType);
                    control.validarTexto(newType);
                    d->setTipo(newType);

                    cout << "Ingresa la nueva fecha: ";
                    getline(cin, newDate);
                    control.validarTexto(newDate);
                    d->setFecha(newDate);

                    cout << "Ingresa la nueva calificacion: ";
                    getline(cin, newGrade);
                    control.validarTexto(newGrade);
                    d->setCalificacion(newGrade);

                    cout << "Documento modificado exitosamente\n";
                    return;
                }
            }

        } catch (const exception& e) {
            cout << "Error al modificar: " << e.what() << '\n';
            cin.clear();
            limpiarBuffer();
        }
    }

    void eliminarDocumento() {
        try {
            if (documentos.empty()) throw runtime_error("No hay documentos para eliminar.");

            int num;
            char confirmacion;

            cout << "Ingrese el numero de documento a eliminar: ";
            if (!(cin >> num)) throw invalid_argument("Entrada no valida.");
            limpiarBuffer();

            if (!control.existeDocumento(documentos, num))
                throw runtime_error("Documento no encontrado");

            for (size_t i = 0; i < documentos.size(); ++i) {
                if (documentos[i]->getNumero() == num) {

                    while (true) {
                        cout << "Estas seguro de querer borrar el documento con numero " 
                             << documentos[i]->getNumero() << "? (S/N): ";

                        if (!(cin >> confirmacion)) {
                            cout << "Entrada invalida.\n";
                            cin.clear();
                            limpiarBuffer();
                            continue;
                        }

                        limpiarBuffer();

                        if (confirmacion == 'S' || confirmacion == 's') {
                            delete documentos[i];
                            documentos.erase(documentos.begin() + i);
                            cout << "Eliminado correctamente.\n";
                            return;
                        } 
                        else if (confirmacion == 'N' || confirmacion == 'n') {
                            cout << "Eliminacion cancelada.\n";
                            return;
                        } 
                        else {
                            cout << "Respuesta no valida. Ingrese S o N.\n";
                        }
                    }
                }
            }
    
  

        } catch (const exception& e) {
            cout << "Error al eliminar: " << e.what() << '\n';
            cin.clear();
            limpiarBuffer();
        }
    }

    void ordenarDocumentos(){
        int option; 
        cout<<"Elige que criterio quieres que se use: \n"<<endl; 
        cout<<"1. Tipo\n"<<endl; 
        cout<<"2. Numero\n"<<endl;
        cout<<"3. Fecha\n"<<endl;
        cout<<"4. Calificacion\n"<<endl; 
        cin>>option; 
        switch(option){
            case 1: ordenar(documentos, ordenarPorTipo);
            break; 
            case 2: ordenar(documentos, ordenarPorNumero);
            break; 
            case 3: ordenar(documentos, ordenarPorFecha);
            break; 
            case 4: ordenar(documentos, ordenarPorCalificacion); 
            break; 
            default: 
            cout<<"Opción inválida"<<endl; 
        }
    }

    void menu() {
        int opcion = -1;
        do {
            try {
                cout << "\n---- MENU DE GESTOR DE DOCUMENTOS ----\n";
                cout << "1. Agregar documento\n";
                cout << "2. Listar documentos\n";
                cout << "3. Buscar documento\n";
                cout << "4. Modificar documento\n";
                cout << "5. Eliminar documento\n";
                cout<<" 6. Ordenar documentos por criterio\n"; 
                cout << "0. Salir\n";
                cout << "Seleccione una opcion: ";

                if (!(cin >> opcion)) throw invalid_argument("Opcion debe ser un numero.");
                limpiarBuffer();

                switch (opcion) {
                    case 1: AgregarDocumento(); break;
                    case 2: listarDocumentos(); break;
                    case 3: buscarDocumento(); break;
                    case 4: modificarDocumento(); break;
                    case 5: eliminarDocumento(); break;
                    case 6: ordenarDocumentos(); break;
                    case 0: cout << "Saliendo del programa...\n"; break;
                    default: cout << "Opcion invalida.\n"; break;
                }

            } catch (const exception& e) {
                cout << "Error en el menu: " << e.what() << '\n';
                cin.clear();
                limpiarBuffer();
            }
        } while (opcion != 0);
    }

    ~GestorDocumento() {
        for (auto d : documentos) delete d;
    }
};

class Usuario {
private:
    string Usuario1 = "notario67";
    string contrasena1 = "n0tario";
    string Usuario2 = "asistentenotario67";
    string contrasena2 = "asisten0tario";
    string inputUser, inputPassw;
public:
    bool autenticar() {
        cout << "Ingrese el usuario: ";
        cin >> inputUser;
        cout << "Ingrese la contrasena: ";
        cin >> inputPassw;
        if ((inputUser == Usuario1 && inputPassw == contrasena1) ||
            (inputUser == Usuario2 && inputPassw == contrasena2)) {
            cout << "Acceso exitoso\n";
            return true;
        } else {
            cout << "Credenciales incorrectas.\n";
            return false;
        }
    }
};

class SistemaNotarial {
private:
    Usuario admin;
    GestorDocumento gestor;
public:
    bool login() {
        if (admin.autenticar()) {
            gestor.menu();
            return true;
        } else {
            cout << "Acceso denegado.\n";
            return false;
        }
    }
};

int main() {
    try {
        SistemaNotarial sistema;
        sistema.login();
    } catch (const exception& e) {
        cerr << "Error critico del sistema: " << e.what() << '\n';
    } catch (...) {
        cerr << "Error desconocido.\n";
    }
    return 0;
}
