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

    fstream archivo_materiales(PATH_MATERIALES, ios::in);

    string nombre_material;
    string cantidad_material;

    while(archivo_materiales>> nombre_material){
        archivo_materiales >> cantidad_material;
        if (nombre_material == "piedra"){
            materiales -> piedra = atoi(cantidad_material.c_str() );
        }
        if (nombre_material == "madera"){
            materiales -> madera = atoi(cantidad_material.c_str() );
        }
        if (nombre_material == "metal"){
            materiales -> metal = atoi(cantidad_material.c_str() );
        }
    }
    archivo_materiales.close();
}

void mostrar_materiales(Materiales* materiales){
    cout << "Materiales" << endl
         << "-----------------------" << endl
         << '\t' << "Piedra " << endl
         << '\t' << "Cantidad de piedra: " << materiales -> piedra << endl
         << '\t' << "Madera " << endl
         << '\t' << "Cantidad de madera: " << materiales -> madera << endl
         << '\t' << "Metal " << endl
         << '\t' << "Cantidad de metal: " << materiales -> metal << endl
         << "-----------------------" << endl;
}


void mostrar_edificio(Edificios* edificios, int posicion){
    cout << "-----------------------" << endl
         << '\t' << "Edificio: " << edificios -> edificiosAtributo[posicion] -> nombre_edificio << endl
         << '\t' << "Cantidad de piedra: " << edificios -> edificiosAtributo[posicion] -> piedra << endl
         << '\t' << "Cantidad de madera: " << edificios -> edificiosAtributo[posicion] -> madera << endl
         << '\t' << "Cantidad de metal: " << edificios -> edificiosAtributo[posicion] -> metal << endl
         << '\t' << "Cantidad construidos: " << edificios -> edificiosAtributo[posicion] -> cantidad_construidos << endl
         << '\t' << "Cantidad que se puede construir sin superar el maximo permitido: " << ((edificios -> edificiosAtributo[posicion] -> maxima_cantidad_permitida) - (edificios -> edificiosAtributo[posicion] -> cantidad_construidos) )<< endl
         << "-----------------------" << endl;
}


void mostrar_edificios(Edificios* edificios){
    cout << "EDIFICIOS" << endl;
    for(int i = 0; i < edificios -> cantidad_de_edificios; i++){
        mostrar_edificio(edificios, i);
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

void construir_edificio_por_nombre(Edificios* edificios, Materiales* materiales){
    //falta que imprima porque no se podria construir
    string nombre_edificio;
    nombre_edificio = pedir_nombre_edificio();
    int i = 0;
    bool existe_edificio = verificar_nombre_edificio (nombre_edificio, edificios, i);
    if (existe_edificio ){
        bool hay_piedra = ((materiales -> piedra) >= (edificios -> edificiosAtributo [i] ->piedra));
        bool hay_madera = ((materiales -> madera) >= (edificios -> edificiosAtributo [i] ->madera));
        bool hay_metal = ((materiales -> metal) >= (edificios -> edificiosAtributo [i] ->metal));
        bool se_puede_construir = ((edificios -> edificiosAtributo [i] ->cantidad_construidos) < (edificios -> edificiosAtributo [i] ->maxima_cantidad_permitida));
        if (hay_piedra || hay_madera || hay_metal || se_puede_construir){
            (materiales -> piedra) = (materiales -> piedra) - (edificios -> edificiosAtributo [i] ->piedra);
            (materiales -> madera) = (materiales -> madera) - (edificios -> edificiosAtributo [i] ->madera);
            (materiales -> metal) = (materiales -> metal) - (edificios -> edificiosAtributo [i] ->metal);
            (edificios -> edificiosAtributo [i] ->cantidad_construidos) = (edificios -> edificiosAtributo [i] ->cantidad_construidos + 1);
        }
    }

}

string pedir_nombre_edificio(){
    string nombre_edificio;
    cout << "Ingrese el nombre del edificio que quiere construir : ";
    cin >> nombre_edificio;

    return nombre_edificio;
}

bool verificar_nombre_edificio (string nombre_edificio, Edificios* edificios, int &i) {
    bool existe_edificio = false;

    while (i < edificios->cantidad_de_edificios || existe_edificio == false)  {
        if (nombre_edificio == (edificios -> edificiosAtributo[i]) -> nombre_edificio) {
            existe_edificio = true;
        }
        i++;
    }
    return existe_edificio;
}

void cerrar_edificios(Edificios* edificios){

}
void cerrar_materiales(Materiales* materiales){

}

void procesar_opcion(Edificios* edificios,Materiales* materiales,int opcion){

}