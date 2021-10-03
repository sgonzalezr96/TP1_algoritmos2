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

    while(archivo_material>> nombre_material){
        archivo_materiales >> cantidad_material;

        material = new material;
        material -> nombre_material = nombre_material;
        material -> cantidad_material = stol(cantidad_material);

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
//¿por que usaria un if no tengo que hacer el delete siempre?
    if(materiales -> cantidad_de_materiales != 0){
        delete[] materiales -> contactos;
    }

    materiales -> materialesAtributo = nuevo_vector_materiales;
    materiales -> cantidad_de_materiales++;
}

