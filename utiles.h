#ifndef UTILES_H_INCLUDED
#define UTILES_H_INCLUDED

#include <string>

using namespace std;

const int OPCIONES_VALIDAS = 6;
const int SALIR = 6;
const string PATH_MATERIALES = "materiales.txt";

struct Material{
    string nombre;
    int cantidad;
};

struct Materiales{
    Material** materialesAtributo;
    int cantidad_de_materiales;
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

//
//
void cargar_materiales(int* materiales);

//
//
void agregar_material(int* materiales, Material* material);


#endif // UTILES_H_INCLUDED
