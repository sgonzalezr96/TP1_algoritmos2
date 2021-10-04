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

//Precondiciones: La opcion es valida.
//Postcondiciones: Realiza la opcion indicada.
void procesar_opcion(Edificios* edificios,Materiales* materiales,int opcion);

//Precondiciones: -
//Postcondiciones: Carga el struct materiales con los datos del archivo de materiales
void cargar_materiales(Materiales* materiales);


//Precondiciones: -
//Postcondiciones: Imprime por pantalla los materiales que contiene materiales
void mostrar_materiales(Materiales* materiales);

//Precondiciones:
//Postcondiciones: Muestra por pantalla los datos del edicio que se encuentra en la posicion indicada
void mostrar_edificio(Edificios* edificios, int posicion);

//Precondiciones: -
//Postcondiciones: Imprime por pantalla todos los edificios
void mostrar_edificios(Edificios* edificios);

//Precondiciones: -
//Postcondiciones: Imprime por pantalla los edificios que estan construidos
void mostrar_edificios_construidos(Edificios* edificios);

//Precondiciones: -
//Postcondiciones: Carga el struct edificios con los datos del archivo de materiales
void cargar_edificios(Edificios* edificios);

//Precondiciones: -
//Postcondicion: agrega el edificio a edificios
void agregar_edificio(Edificios* edificios, Edificio* edificio);

//Pre:-
//Post:verificar que exista el edificio, se cuente con la cantidad de materiales necesaria para poder
//construir y que no se haya superado el máximo de construcciones permitidas del mismo. Si no cumple
//dichas condiciones se le avisara porque no es posible construir el edificio pedido, en caso contrario, se
//le deberá consultar al usuario si desea o no construir el edificio.
void construir_edificio_por_nombre(Edificios* edificios, Materiales* materiales);

//Pre:-
//Post:Se demolerá el edificio que tenga que el usuario ingrese el nombre indicado y se devolverán la mitad de los materiales
//utilizados para su construcción.
void demoler_edificio_por_nombre(Edificios* edificios, Materiales* materiales);

//Pre:-
//Pos: devuelve un string con el nombre del edificio que le solicito al usuario
string pedir_nombre_edificio();

//Pre:
//Pos: devuelve true si el nombre del edificio existe y false en caso contrario
bool verificar_nombre_edificio (string nombre_edificio, Edificios* edificios, int &i);

//Pre:-
//Pos: imprime por pantalla el motivo por el cual no se puede construir el edificio si el usuario quisiera construir un edificio válido
void imprimir_motivo_no_construccion(bool hay_metal,bool hay_madera,bool hay_piedra, bool no_supera_max);

//
//Pos: devuelve true si el usuario desea construir el edificio, false en caso contrario
bool preguntar_usuario_construccion();

//Precondiciones: -
//Postcondiciones: Guarda los edificios en el archivo edificios.txy y elimina edificios
void cerrar_edificios(Edificios* edificios);

//Precondiciones: -
//Postcondiciones: Guarda los materiales en el archivo materiales.txt y elimina materiales
void cerrar_materiales(Materiales* materiales);

#endif // UTILES_H_INCLUDED
