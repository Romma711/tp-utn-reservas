#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#define CLIENTES "clientes.bin"
#define HABITACIONES "habitaciones.bin"
#define RESERVAS "reservas.bin"
#define EMPLEADOS "empleados.bin"

const int fil = 3;
const int col = 3;

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

typedef struct{
    char nombre[20];
    char apellido[20];
    char puesto[30]; ///Recepcionista, conserje, etc.
    int edad;
    int dni;
    int salario;
}Empleado; ///Esta struct nos puede ser de utilidad más adelante

//TO DO mostrar archivos y sus respectivos contenions de manera recursiva

//TO DO crear una funciones que modifique los registros implementando un arreglo dinamico(en lo posible cargarlo con una funcion void con doble puntero)

//TO DO crear funciones que eliminen los registros de los archivos con un arreglo estatico

///REGION Cuenta de registros

int cantRegistrosCliente(){
    FILE *archi = fopen(CLIENTES,"rb");
    int resultado;
    if(archi != NULL){
        fseek(archi,0,SEEK_END);
        resultado = ftell(archi)/sizeof(Cliente);
    }
    return resultado;
}

int cantRegistrosReserva(){
    FILE *archi = fopen(RESERVAS,"rb");
    int resultado;
    if(archi != NULL){
        fseek(archi,0,SEEK_END);
        resultado = ftell(archi)/sizeof(Reservas);
    }
    return resultado;
}

int cantRegistrosEmpleado(){
    FILE *archi = fopen(EMPLEADOS,"rb");
    int resultado;
    if(archi != NULL){
        fseek(archi,0,SEEK_END);
        resultado = ftell(archi)/sizeof(Empleado);
    }
    return resultado;
}

///ENDREGION Cuenta de registros

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

/// Eze: HELL NAW
void cargarReserva(Reservas *aux){

}

void cargarEmpleado(Empleado *aux){
    printf("Ingrese el nombre del empleado:\n");
    fflush(stdin);
    scanf("%s",aux->nombre);
    printf("\nIngrese el apellido del empleado:\n");
    fflush(stdin);
    scanf("%s",aux->apellido);
    printf("Ingrese el puesto del empleado:\n");
    fflush(stdin);
    scanf("%s",aux->puesto);
    printf("\nIngrese la edad del empleado:\n");
    fflush(stdin);
    scanf("%i",aux->edad);
    printf("\nIngrese el DNI del empleado:\n");
    fflush(stdin);
    scanf("%i",aux->dni);
    printf("\nIngrese el salario del empleado:\n");
    fflush(stdin);
    scanf("%i",aux->salario);
}

///ENDREGION Cargar registros

///REGION Crear archivos

void crearArchivoCliente(Cliente aux){
    FILE *archi = fopen(CLIENTES,"wb");
    if(archi == NULL){
        fwrite(&aux,sizeof(Cliente),1,archi);
        printf("Se creo el archivo y se almaceno el registro ingresado");
    }
    fclose(archi);
}

void crearArchivoHabitaciones(Habitaciones aux){
    FILE *archi = fopen(HABITACIONES,"wb");
    if(archi == NULL){
        fwrite(&aux,sizeof(Habitaciones),1,archi);
        printf("Se creo el archivo y se almaceno el registro ingresado");
    }
    fclose(archi);
}

void crearArchivoReservas(Reservas aux){
    FILE *archi = fopen(RESERVAS,"wb");
    if(archi == NULL){
        fwrite(&aux,sizeof(Reservas),1,archi);
        printf("Se creo el archivo y se almaceno el registro ingresado");
    }
    fclose(archi);
}

void crearArchivoEmpleado(Empleado aux){
    FILE *archi = fopen(EMPLEADOS,"wb");
    if(archi == NULL){
        fwrite(&aux,sizeof(Empleado),1,archi);
        printf("Se creo el archivo y se almaceno el registro ingresado");
    }
    fclose(archi);
}

///ENDREGION Crear archivos

///REGION Cargar archivos

//TO DO crear validaciones para las diferentes funciones, revisando el dato a cargar y los diferentes registros cargados coincidan

int validarFechas(Reservas aValidar,FILE *archi){
    Reservas aux;
    int flag=0;
    while(!feof(archi)){
        fread(&aux,sizeof(Cliente),1,archi);
        if(aValidar.habitacionReservada.numero==aux.habitacionReservada.numero){
            if(aValidar.checkIn[0]<=aux.checkOut[0] && aValidar.checkOut<aux.checkOut && aValidar.checkIn[1]==aux.checkIn[1]){
                flag=1;
            }
        }
    }
    return flag;
}

void cargarArchivoClientes(){
    Cliente aux,aux2;
    cargarCliente(&aux);
    FILE *archi = fopen(CLIENTES, "r+b");
    if(archi != NULL){
        int flag=0;
        fseek(archi,0,SEEK_SET);
        while(!feof(archi)){
            fread(&aux2,sizeof(Cliente),1,archi);
            if(strcmpi(aux.nombre,aux2.nombre) == 0 && strcmpi(aux.apellido,aux2.apellido) == 0 && aux.dni==aux2.dni){
                flag=1;
            }
        }
        if(flag==0){
            fwrite(&aux,sizeof(Cliente),1,archi);
        }else{
            printf("\nEste cliente ya esta cargado");
        }
    }else{
        fclose(archi);
        crearArchivoCliente(aux);
    }
    fclose(archi);
}

void cargarArchivoHabitaciones(){
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

void cargarArchivoReservas(){
    Reservas aux;
    cargarReservas(&aux);
    FILE *archi = fopen(RESERVAS, "r+b");
    int flag = validarFechas(aux,&archi);
    if(archi != NULL){
        if(flag==0){
            fwrite(&aux,sizeof(Reservas),1,archi);
        }
    }else{
        fclose(archi);
        crearArchivoReservas(aux);
    }
    fclose(archi);
}

void cargarArchivoEmpleado(){
    Empleado aux,aux2;
    cargarEmpleado(&aux);
    FILE *archi = fopen(EMPLEADOS, "r+b");
    if(archi != NULL){
        int flag=0;
        fseek(archi,0,SEEK_SET);
        while(!feof(archi)){
            fread(&aux2,sizeof(Empleado),1,archi);
            if(strcmpi(aux.nombre,aux2.nombre) == 0 && strcmpi(aux.apellido,aux2.apellido) == 0 && aux.dni==aux2.dni){
                flag=1;
            }
        }
        if(flag==0){
            fwrite(&aux,sizeof(Empleado),1,archi);
        }else{
            printf("\nEste empleado ya esta cargado");
        }
    }else{
        fclose(archi);
        crearArchivoEmpleado(aux);
    }
    fclose(archi);
}

///ENDREGION Cargar archivos

///REGION mostrar contenido del archivo

void mostrarCliente(Cliente aux){
    printf("\n-------------------------");
    printf("\nNombre: %s\n",aux.nombre);
    printf("\nApellido: %s\n",aux.apellido);
    printf("\nEdad: %i\n",aux.edad);
    printf("\nDNI: %i\n",aux.dni);
    printf("-------------------------");
}

void mostrarHabitacion(Habitaciones aux){
    printf("\n-------------------------");
    printf("\nNumero de Habitacion: %i\n",aux.numero);
    printf("\nCantidad de ambientes: %s\n",aux.numero);
    printf("\nCoste por noche: %i\n",aux.costeNoche);
    printf("-------------------------");
}

void mostrarReserva(Reservas aux){
    printf("\n---------------------------------");
    printf("\nLa habitacion reservada es: \n\n");
    mostrarHabitacion(aux.habitacionReservada);
    printf("\nEsta reservada por: \n\n");
    mostrarCliente(aux.reservadoPor);
    printf("\nUn total de %i dias\n",aux.cantDias);
    printf("\nEntran el dia %i del %i\n",aux.checkIn[0], aux.checkIn[1]);
    printf("\nSalen el dia %i del %i\n",aux.checkOut[0], aux.checkOut[1]);
    printf("\nEl coste total de la reserva es de: %i\n",aux.costeTotal);
    printf("---------------------------------");
}

void mostrarEmpleado(Empleado aux){
    printf("\n--------------------------------");
    printf("\nNombre: %s\n", aux.nombre);
    printf("\nApellido: %s\n", aux.apellido);
    printf("\nPuesto: %s\n", aux.puesto);
    printf("\nEdad: %i\n", aux.edad);
    printf("\nDNI: %i\n", aux.dni);
    printf("\nSalario: %i\n", aux.salario);
    printf("--------------------------------");
}

void mostrarRecursivoCliente(FILE *archi, int i){
    Cliente aux;
    if(!feof(archi)){
        fread(&aux,sizeof(Cliente),1,archi);
        printf("\nCliente %i:\n",i+1);
        mostrarCliente(aux);
        mostrarRecursivoCliente(&archi,i+1);
    }
}

void mostrarRecursivoReserva(FILE *archi, int i){
    Reservas aux;
    if(!feof(archi)){
        fread(&aux,sizeof(Reservas),1,archi);
        printf("\nReserva %i:\n",i+1);
        mostrarReserva(aux);
        mostrarRecursivoReserva(&archi,i+1);
    }
}

void mostrarRecursivoEmpleado(FILE *archi, int i){
    Empleado aux;
    if(!feof(archi)){
        fread(&aux,sizeof(Empleado),1,archi);
        printf("\nEmpleado %i:\n",i+1);
        mostrarEmpleado(aux);
        mostrarRecursivoEmpleado(&archi,i+1);
    }
}

//Funcion que muestre las habitaciones como una matriz

//Funcion que recorra el archivo de reservas y almacene los registros del archivo en un arreglo dinamico

void abrirArchivoCliente(){
    int i = 0;
    FILE *archi = fopen(CLIENTES,"rb");
    if(archi != NULL){
        mostrarRecursivoCliente(&archi,i);
    }
    fclose(archi);
}

void abrirArchivoHabitacion(){
    FILE *archi = fopen(HABITACIONES,"rb");
    if(archi != NULL){
        Habitaciones aux[fil][col];
        for(int i=0;i<fil;i++){
            for(int j=0;j<col;j++){
                fread(&aux[i][j],sizeof(Habitaciones),1,archi);
            }
        }
        for(int i=0;i<fil;i++){
            for(int j=0;j<col;j++){
                mostrarHabitacion(aux[i][j]);
            }
        }
    }
    fclose(archi);
}

void abrirArchivoReservas(){
    FILE *archi = fopen(RESERVAS,"rb");
    if(archi != NULL){

    }
    fclose(archi);
}

void abrirArchivoEmpleado(){
    int i = 0;
    FILE *archi = fopen(EMPLEADOS,"rb");
    if(archi != NULL){
        mostrarRecursivoEmpleado(&archi,i);
    }
    fclose(archi);
}

///ENDREGION Mostrar contenido del archivo

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
