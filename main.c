#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#define CLIENTES = "clientes.bin"
#define HABITACIONES = "habitaciones.bin"
#define RESERVAS = "reservas.bin"

typedef struct{
    char nombre[20];
    char apellido[20];
    int edad;
    int dni;
}Cliente;

typedef struct{
    int numero;
    int ambientes;
    int costeNoche;
}Habitaciones;

typedef struct{
    Cliente reservadoPor;
    Habitaciones habitacionReservada;
    int costeTotal;
    int cantDias; ///Los dias que se va a quedar
    int checkIn[2]; ///[0] es para el dia y [1] es para el mes de entrada
    int checkOut[2]; ///[0] es para el dia y [1] es para el mes de salida
}Reservas;

///REGION Mostrar contenido del archivo
                                                                                                                           //P1: [4] [5] [6]
//TO DO mostrar archivos y sus respectivos contenions de manera recursiva (MOSTRAR LAS HABITACIONES COMO UNA MATRIZ, ejemplo pb: [1] [2] [3])

//TO DO crear una funciones que modifique los registros implementando un arreglo dinamico(en lo posible cargarlo con una funcion void con doble puntero)

//TO DO crear funciones que eliminen los registros de los archivos con un arreglo estatico

//TO DO

void mostrarArchivoClientes(){

}

///ENDREGION Mostrar contenido del archivo

///REGION Cargar registros

void cargarCliente(Cliente *aux){
    printf("Ingrese el nombre del cliente:\n");
    fflush(stdin);
    scanf("%s",aux->nombre);
    printf("\nIngrese el apellido del cliente:\n");
    fflush(stdin);
    scanf("%s",aux->apellido);
    printf("\nIngrese la edad del cliente:\n");
    fflush(stdin);
    scanf("%i",aux->edad);
    printf("\nIngrese el DNI del cliente:\n");
    fflush(stdin);
    scanf("%i",aux->dni);
}

void cargarHabitacion(Habitaciones *aux){
    printf("Ingrese el numero de la habitacion:\n");
    fflush(stdin);
    scanf("%s",aux->numero);
    printf("\nIngrese la cantidad de ambientes que tiene la habitacion:\n");
    fflush(stdin);
    scanf("%s",aux->ambientes);
    printf("\nIngrese el coste por noche de la habitacion:\n");
    fflush(stdin);
    scanf("%i",aux->costeNoche);
}

void cargarReserva(Reservas *aux){

}

///ENDREGION Cargar registros

///REGION Crear archivos

void crearArchivoCliente(Cliente aux){
    FILE *archi = fopen(CLIENTES,"wb")
    if(archi == NULL){
        fwrite(&aux,sizeof(Cliente),1,archi);
        printf("Se creo el archivos y se almaceno el registro ingresado");
    }
    fclose(archi);
}

void crearArchivoHabitaciones(Habitaciones aux){
    FILE *archi = fopen(HABITACIONES,"wb")
    if(archi == NULL){
        fwrite(&aux,sizeof(Habitaciones),1,archi);
        printf("Se creo el archivos y se almaceno el registro ingresado");
    }
    fclose(archi);
}

void crearArchivoReservas(Reservas aux){
    FILE *archi = fopen(RESERVAS,"wb")
    if(archi == NULL){
        fwrite(&aux,sizeof(Reservas),1,archi);
        printf("Se creo el archivos y se almaceno el registro ingresado");
    }
    fclose(archi);
}

///ENDREGION Crear archivos

///REGION Cargar archivos

//TO DO crear validaciones para las diferentes funciones, revisando el dato a cargar y los diferentes registros cargados coincidan

void cargarArchivoClientes (){
    Cliente aux;
    cargarCliente(&aux);
    FILE *archi = fopen(CLIENTES, "ab");
    if(archi != NULL){
        fwrite(&aux,sizeof(Cliente),1,archi);
    }else{
        fclose(archi);
        crearArchivoCliente(aux);
    }
    fclose(archi);
}

void cargarArchivoHabitaciones (){
    Habitaciones aux;
    cargarHabitacion(&aux);
    FILE *archi = fopen(HABITACIONES, "ab");
    if(archi != NULL){
        fwrite(&aux,sizeof(Habitaciones),1,archi);
    }else{
        fclose(archi);
        crearArchivoHabitaciones(aux);
    }
    fclose(archi);
}

void cargarArchivoReservas (){
    Reservas aux;
    cargarReservas(&aux);
    FILE *archi = fopen(RESERVAS, "ab");
    if(archi != NULL){
        fwrite(&aux,sizeof(Reservas),1,archi);
    }else{
        fclose(archi);
        crearArchivoReservas(aux);
    }
    fclose(archi);
}

///ENDREGION Cargar archivos



///REGION MENU

//TO DO Crear un menu utilizable

void mainMenu(){
    int selector=0;
    do{
        switch(){
            case 1:
                break;
            case 2:
                break;
            case 0:
                break;
        }
    }while(selector != 0);
}

void clienteMenu(){
    int selector=0;
    do{
        switch(){
            case 1:
                break;
            case 2:
                break;
            case 0:
                break;
        }
    }while(selector != 0);
}

void reservaMenu(){
    int selector=0;
    do{
        switch(){
            case 1:
                break;
            case 2:
                break;
            case 0:
                break;
        }
    }while(selector != 0);
}

void habitacionesMenu(){
    int selector=0;
    do{
        switch(){
            case 1:
                break;
            case 2:
                break;
            case 0:
                break;
        }
    }while(selector != 0);
}

///END REGION MENU

int main()
{

    return 0;
}
