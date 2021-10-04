#include <iostream>
#include "utiles.h"
using namespace std;

int main()
{
    cout << "llegue hasta aca" << endl;
    Edificios* edificios = new Edificios;
    cargar_edificios(edificios);
    mostrar_edificios( edificios);
    mostrar_edificios_construidos( edificios);

    Materiales* materiales = new Materiales;
    cargar_materiales(materiales);
    mostrar_materiales(materiales);


    int opcion = 0;

    mostrar_menu();
    opcion = pedir_opcion();
    validar_opcion_elegida(opcion);

    while(opcion != SALIR){
        procesar_opcion(edificios, materiales, opcion);
        mostrar_menu();
        opcion = pedir_opcion();
        validar_opcion_elegida(opcion);
    }

    cerrar_edificios(edificios);
    cerrar_materiales(materiales);
    delete materiales;
    delete edificios;

    return 0;
}
