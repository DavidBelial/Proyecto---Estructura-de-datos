//Importamos las librerías necesarias para funciones como 
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>

using namespace std;

// -------------------- ESTRUCTURAS --------------------
struct Operacion{
    char user[40];
    int tipoOper;  // "1. compra" o "2. venta"
    int tipoCrypto;
    float monto;
};

string lista_tipoOper[3] = {"", "Compra", "Venta"};
string lista_tipoCrypto[5] = {"", "BTC", "ETHEREUM", "SOLANA", "XRP"};
    

struct ElNodo {
    Operacion datos;
    ElNodo* siguiente;
};

// Lista enlazada (historial general)
ElNodo* historial = NULL;

// Cola de solicitudes de compra
struct Cola {
    ElNodo* frente;
    ElNodo* final;
};

// Pila de actividad reciente
struct Pila {
    ElNodo* cima;
};

// -------------------- FUNCIONES LISTA --------------------
void registrarOperacionHistorial(ElNodo *& cabeza) {
    ElNodo* nuevo = new ElNodo;

    cout << "Usuario: "; cin.ignore(); cin.getline(nuevo->datos.user, 40);
    cout << "Tipo (1. compra/ 2. venta): "; cin >> nuevo->datos.tipoOper; cin.ignore(); 
    cout << "Criptomoneda (1. BTC / 2. ETH / 3. SOL / 4. XRP): "; cin>> nuevo->datos.tipoCrypto; cin.ignore();
    cout << "Monto en USD: "; cin >> nuevo->datos.monto; cin.ignore();

    nuevo->siguiente = cabeza;
    cabeza = nuevo;

    cout << "Operacion registrada en el historial." << endl;
}

void mostrarHistorial(ElNodo* cabeza) {
    cout << "\n--- HISTORIAL DE OPERACIONES ---\n";
    
    
    
    while (cabeza) {
        cout << "Usuario: " << cabeza->datos.user
             << "\nTipo: " << lista_tipoOper[cabeza->datos.tipoOper]
             << "\nCripto: " << lista_tipoCrypto[cabeza->datos.tipoCrypto]
             << "\nMonto: $" << cabeza->datos.monto << endl;
        cabeza = cabeza->siguiente;
    }
}

// -------------------- FUNCIONES COLA --------------------
void inicializarCola(Cola& c) {
    c.frente = c.final = NULL;
}

void encolarCompra(Cola& c) {
    ElNodo* nuevo = new ElNodo;
    cout << "Usuario: "; cin.ignore(); cin.getline(nuevo->datos.user, 40);
    
    
    nuevo->datos.tipoOper = 1; //Por defecto es el tipo 1.- Compra; ya que la función es encolar una operación del tipo compra

    
	cout << "Criptomoneda (1. BTC / 2. ETH / 3. SOL / 4. XRP): "; cin >> nuevo->datos.tipoCrypto; cin.ignore();
    cout << "Monto en USD: "; cin >> nuevo->datos.monto; cin.ignore();
    nuevo->siguiente = NULL;

    if (!c.frente) {
        c.frente = c.final = nuevo;
    } else {
        c.final->siguiente = nuevo;
        c.final = nuevo;
    }

    cout << "Solicitud de compra encolada." << endl;
}

void mostrarCola(Cola c) {
    ElNodo* actual = c.frente;
    cout << "\n--- COLA DE COMPRAS ---\n";
    while (actual) {
        cout << "Usuario: " << actual->datos.user
             << ", Cripto: " << lista_tipoCrypto[actual->datos.tipoCrypto]
             << ", Monto: $" << actual->datos.monto << endl;
        actual = actual->siguiente;
    }
}

// -------------------- FUNCIONES PILA --------------------
void inicializarPila(Pila& p) {
    p.cima = NULL;
}

void apilarActividad(Pila& p) {
    ElNodo* nuevo = new ElNodo;
    cout << "Usuario: "; cin.ignore(); cin.getline(nuevo->datos.user, 40);
    cout << "Tipo (1. compra/ 2. venta): "; cin >> nuevo->datos.tipoOper; cin.ignore(); 
    cout << "Criptomoneda (1. BTC / 2. ETH / 3. SOL / 4. XRP): "; cin>> nuevo->datos.tipoCrypto; cin.ignore();
    cout << "Monto en USD: "; cin >> nuevo->datos.monto;

    nuevo->siguiente = p.cima;
    p.cima = nuevo;
    cout << "Actividad reciente registrada." << endl;
}

void mostrarActividadReciente(Pila p) {
    ElNodo* actual = p.cima;
    cout << "\n--- ACTIVIDAD RECIENTE ---\n";
    while (actual) {
        cout << "Usuario: " << actual->datos.user
             << ", Tipo: " << lista_tipoCrypto[actual->datos.tipoOper]
             << ", Cripto: " << lista_tipoCrypto[actual->datos.tipoCrypto]
             << ", Monto: $" << actual->datos.monto << endl;
        actual = actual->siguiente;
    }
}

// -------------------- MENÚ PRINCIPAL --------------------
int main() {
    Cola colaCompras;
    Pila actividad;
    inicializarCola(colaCompras);
    inicializarPila(actividad);

    int opcion;

    do {
        cout << "\n--- Billetera Crypto: Blockchain bebé ---\n";
        cout << "1. Registrar operación en historial\n";
        cout << "2. Mostrar historial de operaciones\n";
        cout << "3. Encolar solicitud de compra\n";
        cout << "4. Mostrar cola de compras\n";
        cout << "5. Registrar actividad reciente\n";
        cout << "6. Mostrar actividad reciente\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();  // Limpiar buffer

        switch (opcion) {
            case 1:
                registrarOperacionHistorial(historial);
                break;
            case 2:
                mostrarHistorial(historial);
                break;
            case 3:
                encolarCompra(colaCompras);
                break;
            case 4:
                mostrarCola(colaCompras);
                break;
            case 5:
                apilarActividad(actividad);
                break;
            case 6:
                mostrarActividadReciente(actividad);
                break;
            case 0:
                cout << "Saliendo del sistema Billetera Crypto..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}
