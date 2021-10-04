#ifndef UTILES_H_INCLUDED
#define UTILES_H_INCLUDED

#include <string>

using namespace std;

const int OPCIONES_VALIDAS = 6;
const int SALIR = 6;
const string PATH_MATERIALES = "materiales.txt";
const string PATH_EDIFICIOS = "edificios.txt";


struct Materiales{
    int madera;
    int piedra;
    int metal;
};

struct Edificio{
    string nombre_edificio;
    int piedra;
    int madera;
    int metal;
    int cantidad_construidos;
    int maxima_cantidad_permitida;
};

struct Edificios{
    Edificio** edificiosAtributo;
    int cantidad_de_edificios;
};



//Precondiciones: -
//Postcondiciones: imprime por pantalla el menu
void mostrar_menu();

//Precondiciones: -
//Postcondiciones: Le solicita al usuario que ingrese el numero de la opcion que desea seleccionar
int pedir_opcion();

//Precondiciones: recibe la opcion elegida precargada
//Postcondiciones: Verifica que la opcion sea un numero entre 0 y el valor de OPCIONES_VALIDAS y si no lo es vuelve a solicitar los datos
void validar_opcion_elegida(int &opcion_elegida);

void procesar_opcion(Edificios* edificios,Materiales* materiales,int opcion);

//
//
void cargar_materiales(Materiales* materiales);


//Precondiciones: -
//Postcondiciones: Imprime por pantalla los materiales que contiene materiales
void mostrar_materiales(Materiales* materiales);

//Precondiciones:
//Postcondiciones: Muestra por pantalla los datos del material que se encuentra en la posicion indicada
void mostrar_edificio(Edificios* edificios, int posicion);

//Precondiciones: -
//Postcondiciones: Imprime por pantalla los materiales que contiene materiales
void mostrar_edificios(Edificios* edificios);

//
//
void cargar_edificios(Edificios* edificios);

//
//
void agregar_edificio(Edificios* edificios, Edificio* edificio);


void construir_edificio_por_nombre(Edificios* edificios, Materiales* materiales);

//Pre:
//Pos: devuelve un string con el nombre del edificio que le solicito al usuario
string pedir_nombre_edificio();

//
//Pos: devuelve true si el nombre del edificio existe y false en caso contrario
bool verificar_nombre_edificio (string nombre_edificio, Edificios* edificios, int &i);

void cerrar_edificios(Edificios* edificios);
void cerrar_materiales(Materiales* materiales);
#endif // UTILES_H_INCLUDED
