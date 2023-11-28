#include <iostream>
#include <limits>

using namespace std;

class ConstanciaEscolar {
private:
    string nombreAlumno;
    string nombreCarrera;
    int materiaAprobada;
    float promedioGeneral;

public:
    ConstanciaEscolar(){};

    friend ostream &operator<<(ostream &O, ConstanciaEscolar &x) {
        O << "\tNombre del alumno: " << x.nombreAlumno << endl;
        O << "\tNombre de la Carrera: " << x.nombreCarrera << endl;
        O << "\tMaterias Aprobadas: " << x.materiaAprobada << endl;
        O << "\tPromedio General: " << x.promedioGeneral << endl;
        return O;
    }

    friend istream &operator>>(istream &O, ConstanciaEscolar &x) {
        cin.ignore();
        cout << "Nombre del alumno: ";
        getline(O, x.nombreAlumno);
        cout << "\nNombre de la Carrera: ";
        getline(O, x.nombreCarrera);
        cout << "\nMaterias Aprobadas: ";
        O >> x.materiaAprobada;
        cout << "\nPromedio General: ";
        O >> x.promedioGeneral;
        return O;
    }
};

template <class T>
class Cola;

template <class T>
class node {
private:
    T data;
    node<T> *sig;

public:
    node() : sig(nullptr){};
    friend class Cola<T>;
};

template <class T>
class Cola {
private:
    node<T> *lista;
    node<T> *ultimo() const;
    node<T> *primero() const;
    node<T> *anterior(node<T> *pos) const;
    void insertar(node<T> *pos, T elem);
    bool eliminar(node<T> *pos);

public:
    Cola() : lista(nullptr){};
    bool vacia() const;
    void imprimir() const;
    void Enqueue(T elem);
    void Dequeue();
    T Front();
};

template <class T>
T Cola<T>::Front() {
    if (!vacia()) {
        return primero()->data;
    }
}

template <class T>
void Cola<T>::Dequeue() {
    eliminar(primero());
}

template <class T>
void Cola<T>::Enqueue(T elem) {
    insertar(ultimo(), elem);
}

template <class T>
void Cola<T>::imprimir() const {
    node<T> *aux = lista;
    while (aux != nullptr) {
        cout << aux->data << "-> ";
        aux = aux->sig;
    }
}

template <class T>
bool Cola<T>::eliminar(node<T> *pos) {
    if (vacia() || pos == nullptr) {
        return false;
    }
    if (pos == lista) {
        lista = lista->sig;
    } else {
        anterior(pos)->sig = pos->sig;
    }
    delete pos;
    return true;
}

template <class T>
void Cola<T>::insertar(node<T> *pos, T elem) {
    node<T> *aux = new node<T>;
    aux->data = elem;
    if (pos == nullptr) {
        aux->sig = lista;
        lista = aux;
    } else {
        aux->sig = pos->sig;
        pos->sig = aux;
    }
}

template <class T>
node<T> *Cola<T>::anterior(node<T> *pos) const {
    if (vacia() || pos == nullptr) {
        return nullptr;
    }
    node<T> *aux = lista;
    while (aux != nullptr && aux->sig != pos) {
        aux = aux->sig;
    }
    return aux;
}

template <class T>
node<T> *Cola<T>::primero() const {
    if (vacia()) {
        return nullptr;
    }
    return lista;
}

template <class T>
node<T> *Cola<T>::ultimo() const {
    if (vacia()) {
        return nullptr;
    }
    node<T> *aux = lista;
    while (aux->sig != nullptr) {
        aux = aux->sig;
    }
    return aux;
}

template <class T>
bool Cola<T>::vacia() const {
    return lista == nullptr;
}

int Menu() {
    int opcion = 0;
    system("cls");
    cout << "DIRECCION ESCOLAR" << endl;
    cout << "\nSelecciona una opcion:" << endl;
    cout << "1. Dar de alta solicitud" << endl;
    cout << "2. Elaborar constancia" << endl;
    cout << "3. Salir" << endl;
    cout <<"\nOpcion: ";
    cin >> opcion;

    return opcion;
}

void pausa() {
    cout << "\nPresiona cualquier tecla para continuar...";
    cin.ignore();
    cin.get();
}

int main() {
    Cola<ConstanciaEscolar> ColaConstanciasEscolares;
    ConstanciaEscolar Solicitud;

    int OpcionMenu;

    do {
        OpcionMenu = Menu();

        switch (OpcionMenu) {
        case 1:
            system("cls");
            cin >> Solicitud;
            ColaConstanciasEscolares.Enqueue(Solicitud);
            break;
        case 2:
            system("cls");
            if (ColaConstanciasEscolares.vacia())
                cout << "\tNo hay solicitudes pendientes" << endl << endl;
            else {
                cout << "\t------CONSTANCIA ACADEMICA----" << endl << endl;
                Solicitud = ColaConstanciasEscolares.Front();
                cout << Solicitud << endl << endl;
                ColaConstanciasEscolares.Dequeue();
            }
            break;
        case 3:
            cout << "\nHasta luego!" << endl;
            break;
        default:
            cout << "\nPor favor elige una opcion valida\n";
            break;
        }

        pausa();

    } while (OpcionMenu != 3);

    return 0;
}
