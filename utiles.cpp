#include <iostream>
#include "utiles.h"
#include <fstream>

using namespace std;
const int LISTAR_MATERIALES_CONSTRUCCION = 1;
const int CONSTRUIR_EDIFICIO_NOMBRE = 2;
const int LISTAR_EDIFICIOS_CONSTRUIDOS = 3;
const int LISTAR_TODOS_EDIFICIOS = 4;
const int DEMOLER_EDIFICIO_NOMBRE = 5;


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

void mostrar_edificios_construidos(Edificios* edificios){
    cout << "EDIFICIOS CONSTRUIDOS" << endl;
    for(int i = 0; i < edificios -> cantidad_de_edificios; i++){
        if (edificios -> edificiosAtributo[i] -> cantidad_construidos >0 ) {
            cout << "-----------------------" << endl
                 << '\t' << "Edificio: " << edificios->edificiosAtributo[i]->nombre_edificio << endl
                 << '\t' << "Cantidad construidos: " << edificios->edificiosAtributo[i]->cantidad_construidos << endl
                 << "-----------------------" << endl;
        }
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
    string nombre_edificio;
    nombre_edificio = pedir_nombre_edificio();
    int i = 0;
    bool existe_edificio = verificar_nombre_edificio (nombre_edificio, edificios, i);
    if (existe_edificio ){
        bool hay_piedra = ((materiales -> piedra) >= (edificios -> edificiosAtributo [i-1] ->piedra));
        bool hay_madera = ((materiales -> madera) >= (edificios -> edificiosAtributo [i-1] ->madera));
        bool hay_metal = ((materiales -> metal) >= (edificios -> edificiosAtributo [i-1] ->metal));
        bool no_supera_max = ((edificios -> edificiosAtributo [i-1] ->cantidad_construidos) < (edificios -> edificiosAtributo [i-1] ->maxima_cantidad_permitida));
        if (hay_piedra || hay_madera || hay_metal || no_supera_max) {
            bool desea_construir = preguntar_usuario_construccion();
            if (desea_construir) {
                (materiales->piedra) = (materiales->piedra) - (edificios->edificiosAtributo[i-1]->piedra);
                (materiales->madera) = (materiales->madera) - (edificios->edificiosAtributo[i-1]->madera);
                (materiales->metal) = (materiales->metal) - (edificios->edificiosAtributo[i-1]->metal);
                (edificios->edificiosAtributo[i-1]->cantidad_construidos) = (edificios->edificiosAtributo[i-1]->cantidad_construidos + 1);
            }
        }
        else{
            imprimir_motivo_no_construccion(hay_metal,hay_madera,hay_piedra, no_supera_max);
         }
    }
    else{
        cout << "No es un nombre de edificio válido" << endl;
    }
}

string pedir_nombre_edificio(){
    string nombre_edificio;
    cout << "Ingrese el nombre del edificio : ";
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

bool preguntar_usuario_construccion(){
    cout << "Es posible construir el edificio. Si desea construirlo marque 1, en caso contrario cualquier otra tecla." << endl;
    string respuesta;
    cin >> respuesta;
    if (respuesta == "1"){
        return true;
    }
    else{
        return false;
    }
}

void imprimir_motivo_no_construccion(bool hay_metal,bool hay_madera,bool hay_piedra,bool no_supera_max){
    if (not hay_piedra){
        cout << "No se puede construir porque no hay la cantidad de piedra necesaria"<< endl;
    }
    if (not hay_madera){
            cout << "No se puede construir porque no hay la cantidad de madera necesaria"<< endl;
    }
    if (not hay_metal){
        cout << "No se puede construir porque no hay la cantidad de metal necesaria"<< endl;
    }
    if (not no_supera_max){
        cout << "No se puede construir porque no hay la cantidad de metal necesaria"<< endl;
    }


}

void demoler_edificio_por_nombre(Edificios* edificios, Materiales* materiales){
    string nombre_edificio;
    nombre_edificio = pedir_nombre_edificio();
    int i = 0;
    bool existe_edificio = verificar_nombre_edificio (nombre_edificio, edificios, i);
    if (existe_edificio ){
        (edificios->edificiosAtributo[i-1]->cantidad_construidos) = (edificios->edificiosAtributo[i-1]->cantidad_construidos - 1);
        materiales -> piedra += (edificios->edificiosAtributo[i-1]->piedra)/2;
        materiales -> madera += (edificios->edificiosAtributo[i-1]->madera)/2;
        materiales -> metal += (edificios->edificiosAtributo[i-1]->metal)/2;
    }
    else{
        cout << "No es un nombre de edificio válido" << endl;
    }
}
void cerrar_edificios(Edificios* edificios){
    ofstream archivo_edificios(PATH_EDIFICIOS);

    int cantidad_de_edificios = edificios -> cantidad_de_edificios;

    for(int i = 0; i < cantidad_de_edificios; i++){
        archivo_edificios << edificios -> edificiosAtributo[i] -> nombre_edificio << ' '
                          << edificios -> edificiosAtributo[i] -> piedra << ' '
                          << edificios -> edificiosAtributo[i] -> madera << ' '
                          << edificios -> edificiosAtributo[i] -> metal << ' '
                          << edificios -> edificiosAtributo[i] -> cantidad_construidos << ' '
                          << edificios -> edificiosAtributo[i] -> maxima_cantidad_permitida << '\n';
        delete edificios -> edificiosAtributo[i];
        edificios -> cantidad_de_edificios--;
    }

    delete[] edificios -> edificiosAtributo;
    edificios -> edificiosAtributo = nullptr;
}

void cerrar_materiales(Materiales* materiales){
    ofstream archivo_materiales(PATH_MATERIALES);

    archivo_materiales << "piedra" << ' '
                       << materiales -> piedra << '\n'
                       << "madera" << ' '
                       << materiales -> madera << '\n'
                       << "metal" << ' '
                       << materiales -> metal << '\n';

}

void procesar_opcion(Edificios* edificios,Materiales* materiales,int opcion){
    switch (opcion) {
        case LISTAR_MATERIALES_CONSTRUCCION :
            mostrar_materiales(materiales);
            break;

        case CONSTRUIR_EDIFICIO_NOMBRE:
            construir_edificio_por_nombre(edificios, materiales);
            break;

        case LISTAR_EDIFICIOS_CONSTRUIDOS:
            mostrar_edificios_construidos(edificios);
            break;

        case LISTAR_TODOS_EDIFICIOS:
            mostrar_edificios(edificios);
            break;

        case DEMOLER_EDIFICIO_NOMBRE:
            demoler_edificio_por_nombre(edificios, materiales);


    }
}