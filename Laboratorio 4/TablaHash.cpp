#include <iostream>
const int TAM_TABLA = 10;

using namespace std;

struct Nodo{
    string clave;
    string valor;
    Nodo* siguiente;

    Nodo(string clave, string valor) {
        this->clave = clave;
        this->valor = valor;
        this->siguiente = nullptr;
    }
};

class HashTable {
private:
    Nodo* tabla[TAM_TABLA];

public:
    HashTable() {
        for (int i = 0; i < TAM_TABLA; ++i) {
            tabla[i] = nullptr;
        }
    }

    int hashFunction(string clave) {
        int hashValue = 0;
        for(int i = 0; i < clave.size(); i++)
            hashValue += ( (clave[i])*(i+1) );
        return hashValue % TAM_TABLA; //devuelve el indice para la tabla
    }

    bool insert(string clave, string valor) {
        int indice = hashFunction(clave);
        Nodo* nodo = new Nodo(clave, valor);

        if (tabla[indice] == nullptr) {
            tabla[indice] = nodo;
            return true;
        }
        else {
            Nodo* it = tabla[indice];
            while(it->clave != clave && it->siguiente != nullptr)
            {
                it = it->siguiente;
            }
            if (it->clave == clave) {
                delete nodo;
                return false;
            }
            it->siguiente = nodo;
            return true;
        }
    }

    string search(string clave) {
        int indice = hashFunction(clave);
        if (tabla[indice] == nullptr) {
            return "[no existe]";
        }
        else {
            Nodo* it = tabla[indice];
            while(it != nullptr && it->clave != clave) {
                it = it->siguiente;
            }
            if(it == nullptr) {
                return "[no existe]";
            }
            return it->valor;
        }
    }

    bool remove(string clave) {
        int indice = hashFunction(clave);
        if (tabla[indice] == nullptr) {
            return false;
        }
        else {
            Nodo** it = &tabla[indice];
            while(*it != nullptr && (*it)->clave != clave) {
                it = &((*it)->siguiente);
            }
            if(*it == nullptr) {
                return false;
            }
            else {
                Nodo* tmp = *it;
                *it = (*it)->siguiente;
                delete tmp;
                return true;
            }
        }
    }

    void displayTable() {
        cout<<"\nCONTENIDO DE LA TABLA HASH"<<endl;
        for(int i = 0; i < TAM_TABLA; i++) {
            cout << "pos " << i << ": ";
            if (tabla[i] == nullptr) {
                 cout << "vacio" << endl;
            }
            else {
                Nodo* it = tabla[i];
                while(it->siguiente != nullptr) {
                    cout << "[" << it->clave << "," << it->valor << "] ";
                    it = it->siguiente;
                }
                cout << "[" << it->clave << "," << it->valor << "] " << endl;
            }
        }
    }
};


int main()
{
    HashTable tabla;
    int opcion;

    do {
        cout << "\nMenu Tabla Hash:\n";
        cout << "1. Insertar nuevo par clave-valor\n";
        cout << "2. Buscar un valor por su clave\n";
        cout << "3. Eliminar un par clave-valor usando su clave\n";
        cout << "4. Mostrar contenido de la tabla\n";
        cout << "0. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: { // insertar nuevo par
                string clave;
                string valor;
                bool resultado;
                cout << "Ingrese la clave: ";
                cin >> clave;
                cout << "Ingrese el valor: ";
                cin >> valor;
                resultado = tabla.insert(clave, valor);
                if (resultado) {
                    cout << "El par [" << clave << ", " << valor << "] fue insertado.\n";
                } else {
                    cout << "No se inserto, ya existe un par con esa clave.\n";
                }
                break;
            }
            case 2: { //busca un valor por su clave
                string clave;
                string valor;
                cout << "Ingrese la clave del valor a buscar: ";
                cin >> clave;
                valor = tabla.search(clave);
                if(valor == "[no existe]") {
                    cout << "No se encontro un valor asociado a esa clave\n";
                } else {
                    cout << "\n\tEl valor asociado a la clave '" << clave << "' es '" << valor << "'\n";
                }
                break;
            }
            case 3: { //elimina un par usando su clave
                string clave;
                bool resultado;
                cout << "Ingrese la clave del par que desea eliminar: ";
                cin >> clave;
                resultado = tabla.remove(clave);

                if(resultado) {
                    cout << "\n\tEl par con la clave '" << clave << "' fue eliminado.\n";
                } else {
                    cout << "No existe un par con la clave '" << clave << "'\n";
                }
                break;
            }
            case 4: { //muestra contenido de la tabla
                tabla.displayTable();
                break;
            }

            case 0: //salir
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida, intente de nuevo.\n";
                break;
        }
    } while (opcion != 0);


    return 0;
}
