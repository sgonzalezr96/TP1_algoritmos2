#include <iostream>
#include "utiles.h"
#include <fstream>

using namespace std;

void mostrar_menu(){
    cout << endl << endl << endl;
    cout << "MENU" << endl
    << '\t' << "1_ Listar materiales de construcci�n" << endl
    << '\t' << "2_ Construir edificio por nombre" << endl
    << '\t' << "3_ Listar los edificios construidos" << endl
    << '\t' << "4_ Listar todos los edificios " << endl
    << '\t' << "5_ Demoler un edificio por nombre" << endl
    << '\t' << "6_ Guardar y salir" << endl;
}


int pedir_opcion(){
    int opcion_elegida;
    cout << "Ingrese el n�mero de su acci�n elegida : ";
    cin >> opcion_elegida;

    return opcion_elegida;
}

void validar_opcion_elegida(int &opcion_elegida){
    bool es_opcion_valida = opcion_elegida > 0 && opcion_elegida <= OPCIONES_VALIDAS;
    while(!es_opcion_valida){
        cout << "La opci�n elegida no es una opcion v�lida, por favor ingrese otra opci�n: ";
        cin >> opcion_elegida;
        es_opcion_valida = opcion_elegida > 0 && opcion_elegida <= OPCIONES_VALIDAS;
    }
}

void cargar_materiales(Materiales* materiales){
    materiales -> cantidad_de_materiales = 0;

    fstream archivo_materiales(PATH_MATERIALES, ios::in);

    string nombre_material;
    string cantidad_material;

    Material* material;

    while(archivo_materiales>> nombre_material){
        archivo_materiales >> cantidad_material;
        material = new Material;
        material -> nombre_material = nombre_material;
        material -> cantidad_material = atoi(cantidad_material.c_str() );

        agregar_material(materiales, material);
    }

    archivo_materiales.close();
}

void agregar_material(Materiales* materiales, Material* material) {
    int tope_viejo = materiales->cantidad_de_materiales;
    Material **nuevo_vector_materiales = new Material *[tope_viejo + 1];

    for (int i = 0; i < materiales->cantidad_de_materiales; i++) {
        nuevo_vector_materiales[i] = materiales->materialesAtributo[i];
    }
    nuevo_vector_materiales[tope_viejo] = material;
    if (materiales->cantidad_de_materiales != 0) {
        delete[] materiales->materialesAtributo;
    }

    materiales->materialesAtributo = nuevo_vector_materiales;
    materiales->cantidad_de_materiales++;
}

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
    string piedra;
    string madera;
    string metal;
    string cantidad_construidos;
    string maxima_cantidad_permitida;

    Edificio* edificio;

    while(archivo_edificios>> nombre_edificio){
        archivo_edificios >> piedra;
        archivo_edificios >> madera;
        archivo_edificios >> metal;
        archivo_edificios >> cantidad_construidos;
        archivo_edificios >> maxima_cantidad_permitida;

        edificio = new Edificio;
        edificio -> nombre_edificio = nombre_edificio;
        edificio -> piedra = stoi(piedra);
        edificio -> madera = stoi(madera);
        edificio -> metal = stoi(metal);
        edificio -> cantidad_construidos = stoi(cantidad_construidos);
        edificio -> maxima_cantidad_permitida = stoi(maxima_cantidad_permitida);

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

    edificios -> edificiosAtributo = nuevo_vector_edificios;
    edificios -> cantidad_de_edificios++;
}

void cerrar_edificios(Edificios* edificios){

}
void cerrar_materiales(Materiales* materiales){

}

void procesar_opcion(Edificios* edificios,Materiales* materiales,int opcion){

}