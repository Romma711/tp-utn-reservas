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

//TO DO crear una funcion que modifique los registros implementando un arreglo dinamico(en lo posible cargarlo con una funcion void con doble puntero)

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

///ENDREGION Cuenta de registros

///REGION Posicion en el archivo

int clientePosicion(FILE *archi){
    Cliente arr[50];
    int i = 0;
    int control;
    while(!feof(archi)){
        fread(&arr[i],sizeof(Cliente),1,archi);
        i++;
    }
    for(int j=0; j<i;j++){
        printf("\n%i.",j);
        mostrarCliente(arr[i]);
    }
    printf("\nElegi al cliente:\n");
    fflush(stdin);
    scanf("%i",&control);
    control - 1;
    return control;
}

int habitacionPosicion(FILE *archi){
    Habitaciones matriz[fil][col];
    int i = 0;
    int control;
    for(int j=0;j<fil;j++){
        for(int k=0;k<col;k++){
            fread(&matriz[i],sizeof(Cliente),1,archi);
        }
    }
    for(int j=0; j<fil;j++){
        for(int k=0;k<col;k++){
            mostrarHabitacion(matriz[j][k]);
        }
        printf("\n");
    }
    printf("\nElegi el numero de la habitacion:\n");
    fflush(stdin);
    scanf("%i",&control);
    control;
    return control;
}

void clienteReservar(Cliente *aCargar){
    int posicion;
    FILE *archi= fopen (CLIENTES,"rb");
    if(archi != NULL){
        posicion = clientePosicion(&archi);
        fseek(archi,0,SEEK_SET);
        fseek(archi,sizeof(Cliente)*posicion,SEEK_CUR);
        fread(aCargar,sizeof(Cliente),1,archi);
    }
    fclose(archi);
}

void habitacionReservar(Habitaciones *aCargar){
    int numero;
    Habitaciones aux;
    FILE *archi= fopen (HABITACIONES,"rb");
    if(archi != NULL){
        numero = habitacionPosicion(&archi);
        fseek(archi,0,SEEK_SET);
        while(!feof(archi)){
            fread(&aux,sizeof(Habitaciones),1,archi);
            if(aux.numero == numero){
                aCargar->numero = aux.numero;
                aCargar->ambientes = aux.ambientes;
                aCargar->costeNoche = aux.costeNoche;
            }
        }
    }
    fclose(archi);
}

///ENDREGION Posicion en el archivo

///REGION Cargar registros

void cargarCliente(Cliente *aux){
    printf("Ingrese el nombre del cliente:\n");
    fflush(stdin);
    scanf("%s",&aux->nombre);
    printf("\nIngrese el apellido del cliente:\n");
    fflush(stdin);
    scanf("%s",&aux->apellido);
    printf("\nIngrese la edad del cliente:\n");
    fflush(stdin);
    scanf("%i",&aux->edad);
    printf("\nIngrese el DNI del cliente:\n");
    fflush(stdin);
    scanf("%i",&aux->dni);
}

void cargarHabitacion(Habitaciones *aux){
    printf("Ingrese el numero de la habitacion:\n");
    fflush(stdin);
    scanf("%s",&aux->numero);
    printf("\nIngrese la cantidad de ambientes que tiene la habitacion:\n");
    fflush(stdin);
    scanf("%s",&aux->ambientes);
    printf("\nIngrese el coste por noche de la habitacion:\n");
    fflush(stdin);
    scanf("%i",&aux->costeNoche);
}

void cargarReserva(Reservas *aux){
    clienteReservar(&aux->reservadoPor);
    habitacionReservar(&aux->habitacionReservada);
    printf("\nDe cuantos dias es la reserva?: \n");
    fflush(stdin);
    scanf("%i",&aux->cantDias);
    printf("\nDia de entrada: \n");
    fflush(stdin);
    scanf("%i",&aux->checkIn[0]);
    printf("\nMes de entrada: \n");
    fflush(stdin);
    scanf("%i",&aux->checkIn[1]);
    printf("\nDia de salida: \n");
    fflush(stdin);
    scanf("%i",&aux->checkOut[0]);
    printf("\nMes de salida: \n");
    fflush(stdin);
    scanf("%i",&aux->checkOut[1]);
    aux->costeTotal = aux->cantDias * aux->habitacionReservada.costeNoche;
    printf("\nEl coste total seria de: %i \n",aux->costeTotal);
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
    Cliente aux, aux2;
    cargarCliente(&aux);
    FILE *archi = fopen(CLIENTES, "r+b");
    if(archi != NULL){
        int flag=0;
        fseek(archi,0,SEEK_SET);
        while(!feof(archi)){
            fread(&aux2,sizeof(Cliente),1,archi);
            if(strcmpi(aux.nombre,aux2.nombre) == 0 && strcmpi(aux.apellido,aux2.apellido) == 0 && aux.dni == aux2.dni){
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

///ENDREGION Cargar archivos

///REGION Mostrar contenido del archivo

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

void mostrarRecursivoHabitacion(FILE *archi, int i){
    Habitaciones aux;
    if(!feof(archi)){
        fread(&aux,sizeof(Habitaciones),1,archi);
        printf("\Habitacion %i:\n",i+1);
        mostrarHabitacion(aux);
        mostrarRecursivoHabitacion(&archi,i+1);
    }
}

void mostrarMatrizHabitaciones(){

    Habitaciones aux;
    int matriz[fil][col];
    FILE* archi = fopen(HABITACIONES, "rb");

    if(archi != NULL){
        for(int i = 0; i < fil; i++){
            for(int j = 0; j < col; j++){
                fread(&aux, sizeof(Habitaciones), 1, archi);
                if(!feof(archi)){
                    matriz[i][j] = aux.numero;
                }
            }
        }
        fclose(archi);
    }

    for(int i = 0; i < fil; i++){
        printf("\nPlanta %i:\n", i);
        for(int j = 0; j < col; j++){
            printf("| %i |", matriz[i][j]);
        }
    }

}

void copiarReservasEnArreglo(int cant, Reservas **arr){

    Reservas aux;
    *arr = (int*) calloc(cant, sizeof(Reservas));
    int i = 0;
    FILE* archi = fopen(RESERVAS, "rb");

    if(archi != NULL){
        while(!feof(archi) && i < cant){
            fread(&aux, sizeof(Reservas), 1, archi);
            if(!feof(archi)){
                (*arr)[i] = aux;
                i++;
            }
        }
        fclose(archi);
    }

}

void abrirArchivoCliente(){
    int i = 0;
    FILE *archi = fopen(CLIENTES,"rb");
    if(archi != NULL){
        mostrarRecursivoCliente(&archi,i);
    }
    fclose(archi);
}

void abrirArchivoHabitacion(){
    int i = 0;
    Habitaciones aux;
    FILE *archi = fopen(HABITACIONES,"rb");
    if(archi != NULL){
        mostrarMatrizHabitaciones();
        mostrarRecursivoHabitacion(&archi, i);
    }
    fclose(archi);
}

void abrirArchivoReservas(){
    int i = 0;
    FILE *archi = fopen(RESERVAS,"rb");
    if(archi != NULL){
        mostrarRecursivoReserva(archi, i);
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

void empleadosMenu(){
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
