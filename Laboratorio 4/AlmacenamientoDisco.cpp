#include <iostream>
#include <unordered_map>

#define TAM_PAGINA 4
#define TAM_BLOQUE 2
#define MAX_BLOQUES 10

using namespace std;

struct Registro {
    int id;
    string dato;

    Registro(){
        id=0;
        dato="";
    }

    Registro(int id, string dato) {
        this->id = id;
        this->dato = dato;
    }
};

struct Pagina {
    Registro registros[TAM_PAGINA];
    int count; //count para los registros

    Pagina() {
        count = 0;
    }

    bool hayEspacio() {
        return count<TAM_PAGINA;
    }

    void agregarRegistro(const Registro& reg) {
        if (hayEspacio()) {
            registros[count] = reg;
            count++;
        } else {
            cout << "Sin espacio" << endl;
        }
    }

    Registro* buscarRegistro(int id) {
        for (int i = 0; i < count; ++i) {
            if (registros[i].id == id) {
                return &registros[i]; //devuelve el registro
            }
        }
        return nullptr;
    }
};

struct Bloque {
    Pagina paginas[TAM_BLOQUE];
    int count; // count para páginas

    Bloque() {
        count = 0;
    }

    bool hayEspacio() {
        return count < TAM_BLOQUE;
    }

    void agregarPagina(const Pagina& pag) {
        if (hayEspacio()) {
            paginas[count++] = pag;
        } else {
            cout << "Sin espacio" << endl;
        }
    }
};

class Disco {
private:
    Bloque bloques[MAX_BLOQUES];
    int count; //count para bloques
    unordered_map<int, pair<int, int>> regUbicacion;

public:
    Disco() {
        count=0;
    }

    void insertarRegistro(int id, const string& dato) {
    if (regUbicacion.find(id) != regUbicacion.end()) {
        cout << "El ID " << id << " ya existe. Agrega un nuevo registro con otro ID" << endl;
        return;
    }

    Registro nuevoRegistro(id, dato);
        for(int i=0; i<count; ++i) {
            Bloque& bloque = bloques[i];
            for(int j=0; j<bloque.count; ++j) {
                Pagina& pagina = bloque.paginas[j];
                if(pagina.hayEspacio()){
                    pagina.agregarRegistro(nuevoRegistro);
                    regUbicacion[id] = make_pair(i, j); //guarda el I del registro
                    return;
                }
            }
        }

        // Si no hay espacio, creamos un nuevo bloque y página
        if (count < MAX_BLOQUES) {
            Bloque nuevoBloque;
            Pagina nuevaPagina;
            nuevaPagina.agregarRegistro(nuevoRegistro); //nuevo registro a nueva página
            nuevoBloque.agregarPagina(nuevaPagina); //nueva página al nuevo bloque
            bloques[count]=nuevoBloque; //nuevo bloque al disco
            count++;
            regUbicacion[id]=make_pair(count-1,0); //guarda índice
        }
    }

    Registro* buscarRegistro(int id) {
        if (regUbicacion.find(id)!=regUbicacion.end()) {
            int bloqUbicacion=regUbicacion[id].first;
            int pagUbicacion=regUbicacion[id].second;
            return bloques[bloqUbicacion].paginas[pagUbicacion].buscarRegistro(id);
        }
        return nullptr;
    }

    void mostrarDisco() {
        if(count==0){
            cout<<"\n\tEl disco esta vacio"<<endl;
        }

        for (int i = 0; i < count; ++i) {
            cout << "Bloque " << i + 1 << ":\n";
            for (int j = 0; j < bloques[i].count; ++j) {
                cout << "  Página " << j + 1 << ":\n";
                for (int k = 0; k < bloques[i].paginas[j].count; ++k) {
                    cout << "    Registro ID: " << bloques[i].paginas[j].registros[k].id
                                << ", Data: " << bloques[i].paginas[j].registros[k].dato << "\n";
                }
            }
        }
    }
};

int main() {
    Disco disco;
    int opcion;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insertar nuevo registro\n";
        cout << "2. Buscar registro por ID\n";
        cout << "3. Mostrar contenido del disco\n";
        cout << "0. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: { // insertar nuevo registro
                int id;
                string data;
                cout << "Ingrese el ID del registro: ";
                cin >> id;
                cout << "Ingrese los datos del registro: ";
                cin.ignore(); // Limpiar el buffer
                getline(cin, data);
                disco.insertarRegistro(id, data);
                break;
            }
            case 2: { // Buscar registro por id
                int id;
                cout << "Ingrese el ID del registro a buscar: ";
                cin >> id;
                Registro* reg = disco.buscarRegistro(id);
                if (reg != nullptr) {
                    cout << "\n\tRegistro encontrado: ID = " << reg->id << ", Dato = " << reg->dato << "\n";
                } else {
                    cout << "\n\tRegistro no encontrado.\n";
                }
                break;
            }
            case 3: { // Mostrar contenido del disco
                disco.mostrarDisco();
                break;
            }
            case 0: // Salir
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida, intente de nuevo.\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}
