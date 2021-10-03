#include <iostream>
#include "utiles.h"
#include <fstream>

using namespace std;

void mostrar_menu(){
    cout << endl << endl << endl;
    cout << "MENU" << endl
    << '\t' << "1_ Listar materiales de construcción" << endl
    << '\t' << "2_ Construir edificio por nombre" << endl
    << '\t' << "3_ Listar los edificios construidos" << endl
    << '\t' << "4_ Listar todos los edificios " << endl
    << '\t' << "5_ Demoler un edificio por nombre" << endl;
    << '\t' << "5_ Guardar y salir" << endl;
}


int pedir_opcion(){
    int opcion_elegida;
    cout << "Ingrese el número de su acción elegida : ";
    cin >> opcion_elegida;

    return opcion_elegida;
}

void validar_opcion_elegida(int &opcion_elegida){
    bool es_opcion_valida = opcion_elegida > 0 && opcion_elegida <= OPCIONES_VALIDAS;
    while(!es_opcion_valida){
        cout << "La opción elegida no es una opcion válida, por favor ingrese otra opción: ";
        cin >> opcion_elegida;
        es_opcion_valida = opcion_elegida > 0 && opcion_elegida <= OPCIONES_VALIDAS;
    }
}

void cargar_materiales(Materiales* materiales){
    materiales -> cantidad_de_materiales = 0;

    fstream archivo_materiales(PATH_MATERIALES, ios::in);

    string nombre_material;
    int cantidad_material;

    Material* material;

    while(archivo_materiales>> nombre_material){
        archivo_materiales >> cantidad_material;

        material = new material;
        material -> nombre_material = nombre_material;
        material -> cantidad_material = stoi(cantidad_material);

        agregar_material(materiales, material);
    }

    archivo_materiales.close();
}

void agregar_material(Materiales* materiales, Material* material){
    int tope_viejo = materiales -> cantidad_de_materiales;
    Material** nuevo_vector_materiales = new Material*[tope_viejo + 1];

    for(int i = 0; i < materiales -> cantidad_de_materiales; i++){
        nuevo_vector_materiales[i] = materiales -> materialesAtributo[i];
    }
    nuevo_vector_materiales[tope_viejo] = material;
    if(materiales -> cantidad_de_materiales != 0){
        delete[] materiales -> materialesAtributo;
    }

    materiales -> materialesAtributo = nuevo_vector_materiales;
    materiales -> cantidad_de_materiales++;

void mostrar_material(Materiales* materiales, int posicion){
    cout << "-----------------------" << endl
         << '\t' << "Material: " << materiales -> materialesAtributo[posicion] -> nombre_material << endl
         << '\t' << "Cantidad: " << materiales -> materialesAtributo[posicion] -> cantidad_material << endl
         << "-----------------------" << endl;
}


void mostrar_materiales(Materiales* materiales){
    cout << "MATERIALES" << endl;
    for(int i = 0; i < materiales -> cantidad_de_materiales; i++){
        mostrar_material(materiales, i);
    }
}

void cargar_edificios(Edificios* edificios){
    edificios -> cantidad_de_edificios = 0;

    fstream archivo_edificios(PATH_EDIFICIOS, ios::in);

    string nombre_edificio;
    int piedra;
    int madera;
    int metal;
    int cantidad_construidos;
    int maxima_cantidad_permitida;

    Edificio* edificio;
    //no se hacer este while

    while(archivo_edificios>> nombre_edificio){
        archivo_edificios >> cantidad_material;

        edificio = new edificio;
        material -> nombre_material = nombre_material;
        material -> cantidad_material = stoi(cantidad_material);

        agregar_edificio(edificios, edificio);
    }

    archivo_edificios.close();
}

void agregar_edificio(Edificios* edificios, Edificio* edificio){
    int tope_viejo = edificios -> cantidad_de_edificios;
    Edificio** nuevo_vector_edificios = new Edificio*[tope_viejo + 1];

    for(int i = 0; i < edificios -> cantidad_de_edificios; i++){
        nuevo_vector_edificios[i] = edificios -> edificiosAtributo[i];
    }
    nuevo_vector_edificios[tope_viejo] = edificio;
    if(edificios -> cantidad_de_edificios != 0){
        delete[] edificios -> edificiosAtributo;
    }

    edificios -> edificioAtributo = nuevo_vector_edificios;
    edificios -> cantidad_de_edificios++;
}
