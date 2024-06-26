#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"
#define CLIENTES "clientes.bin"
#define HABITACIONES "habitaciones.bin"
#define RESERVAS "reservas.bin"

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


///TO DO Una funcion que verifique la carga de los cliente (verificar que el dni sea diferente a los que estan cargados)

///TO DO Una funcion que verifique la carga de las fechas de los check ins y check outs (verificar que ninguna fecha se superponga a otra en la misma habitacion)

///TO DO Una funcion que modifique la reserva (que puedea modificar la habitacion, el coste total del hospedaje, entrada y salida) TOMAR DE REFERENCIA MODIFICAR CLIENTE

///TO DO Una funcion que elimine la reserva TOMAR DE REFERENCIA BORRAR CLIENTE

///TO DO Hacer la funcionalidad completa del menu

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

///REGION Modificacion y eliminacion de registros

///ENDREGION

void modificarCliente(Cliente *aux){
    int selector;
    printf("\nQue desea modificar?\n");
    printf("\n1. Nombre y apellido\n");
    printf("\n2. Edad\n");
    printf("\n3. DNI\n");
    printf("\n0. Volver\n");
    fflush(stdin);
    scanf("%i",&selector);
    switch(selector){
        case 1:
            printf("\nNombre: ");
            fflush(stdin);
            scanf("%s",aux->nombre);
            printf("\nApellido: ");
            fflush(stdin);
            scanf("%s",aux->apellido);
            break;
        case 2:
            printf("\nEdad: ");
            fflush(stdin);
            scanf("%i",&aux->edad);
            break;
        case 3:
            printf("\nDNI: ");
            fflush(stdin);
            scanf("%i",&aux->dni);
            break;
        default:
            break;
    }
}

void borrarCliente(int pos){
    int total=cantRegistrosCliente();
    Cliente *arr;
    Cliente aux;
    arr = (Cliente*) malloc(sizeof(Cliente)*total);
    int i = 0;
    int j=0;
    FILE *archi  = fopen(CLIENTES,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            if(i != (pos-1) && i<total){
            fread(&arr[j],sizeof(Cliente),1,archi);
                mostrarCliente(arr[j]);
                j++;
            }else{
                fread(&aux,sizeof(Cliente),1,archi);
            }
            i++;
        }
    }
    fclose(archi);
    system("pause");
    FILE *archi2=fopen(CLIENTES,"wb");
    j = 0;
    if(archi2 != NULL){
        while(j<(i-1)){
            fwrite(&arr[j],sizeof(Cliente),1,archi2);
            j++;
        }
    }
    fclose(archi);
}

void modificarReserva(Reservas *aux){
    int selector;
    int intAux;
    printf("\nQue desea modificar?\n");
    printf("\n1. Cliente\n");
    printf("\n2. Habitacion\n");
    printf("\n3. CheckIn\n");
    printf("\n4. CheckOut\n");
    printf("\n0. Volver\n");
    switch(selector){
        case 1:
            printf("\nCliente: ");
            fflush(stdin);
            scanf("%i",intAux);
            break;
        case 2:
            printf("\nHabitacion: ");
            fflush(stdin);
            scanf("%i",intAux);
            break;
        case 3:
            printf("\nDia: ");
            fflush(stdin);
            scanf("%i",&aux->checkIn[0]);
            printf("\nMes: ");
            fflush(stdin);
            scanf("%i",&aux->checkIn[1]);
            break;
        case 4:
            printf("\nDia: ");
            fflush(stdin);
            scanf("%i",&aux->checkOut[0]);
            printf("\nMes: ");
            fflush(stdin);
            scanf("%i",&aux->checkOut[1]);
            break;
        default:
            break;
    }
}

///REGION Modificacion y eliminacion de registros

///ENDREGION

///REGION Posicion en el archivo

void recuperarCliente(int pos){
    Cliente aux;
    FILE *archi=fopen(CLIENTES,"r+b");
    if(archi != NULL){
        fseek(archi,sizeof(Cliente)*pos,SEEK_CUR);
        fread(&aux,sizeof(Cliente),1,archi);
        mostrarCliente(aux);
        modificarCliente(&aux);
        fseek(archi,sizeof(Cliente)*pos,SEEK_SET);
        fwrite(&aux,sizeof(Cliente),1,archi);
    }
    fclose(archi);
}

void clienteMB(int pos){
    printf("\nQue desea hacer?\n");
    printf("\n1. Modificar\n");
    printf("\n2. Eliminar\n");
    printf("\n0. Volver\n");
    int selector;
    fflush(stdin);
    scanf("%i",&selector);
    switch(selector){
        case 1:
            recuperarCliente(pos);
            break;
        case 2:
            borrarCliente(pos);
            break;
        default:
            break;
    }
}

int buscarPorDNI(){
    int dni,pos,i = 0, flag = 0;
    Cliente aux;
    printf("\nIngrese el DNI del cliente\n");
    fflush(stdin);
    scanf("%i",&dni);
    FILE *archi=fopen(CLIENTES,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            fread(&aux,sizeof(Cliente),1,archi);
            if(aux.dni==dni){
                pos=i;
                flag=1;
                mostrarCliente(aux);
                system("pause");
            }
            i++;
        }
    }
    fclose(archi);
    if(flag==1){
        return pos;
    }else{
        printf("\nNo se encontro al cliente\n");
        system("pause");
        return -1;
    }
}

void posicionCliente(){
    int pos = buscarPorDNI();
    if(pos >= 0){
        clienteMB(pos);
    }else{
        printf("\nNo se encontro al cliente\n");
    }
}

void modificarHabitacion(int pos){

    char control;
    int nuevoCoste;

    printf("\nDesea modificar el coste por noche de la habitacion? s/n\n");
    fflush(stdin);
    scanf("%c", &control);

    Habitaciones aux;
    if(control == 's'){
        FILE* archi = fopen(HABITACIONES, "r+b");

        if(archi != NULL){
            fseek(archi,sizeof(Habitaciones)*pos,SEEK_CUR);
            fread(&aux,sizeof(Habitaciones),1,archi);
            printf("\nIngrese el nuevo coste de la habitacion:\n");
            fflush(stdin);
            scanf("%i", &nuevoCoste);
            aux.costeNoche = nuevoCoste;
            fseek(archi,sizeof(Habitaciones)*pos,SEEK_SET);
            fwrite(&aux,sizeof(Habitaciones),1,archi);
            fclose(archi);
    }
    }else{
        printf("\n");
        system("pause");
    }

}

int buscarHabitacion(){
    int num, pos, i = 0, flag = 0;

    mostrarMatrizHabitaciones();

    printf("\nIngrese el numero de la habitacion:\n");
    fflush(stdin);
    scanf("%i", &num);

    Habitaciones aux;

    FILE* archi = fopen(HABITACIONES, "rb");

    if(archi != NULL){
        while(!feof(archi)){
            fread(&aux,sizeof(Habitaciones),1,archi);
            if(aux.numero == num){
                flag = 1;
                pos = i;
                mostrarHabitacion(aux);
            }
            i++;
        }
        fclose(archi);
    }

    if(flag == 1){
        return pos;
    }else{
        return -1;
    }
}

void posicionHabitacion(){
    int pos = buscarHabitacion();
    if(pos >= 0){
        modificarHabitacion(pos);
    }else{
        printf("\nHabitacion inexistente\n");
        system("pause");
    }
}

void clienteReservar(Cliente *aCargar){
    int posicion=buscarPorDNI();
    FILE *archi= fopen (CLIENTES,"rb");
    if(archi != NULL){
        if(posicion>=0){
            fseek(archi,0,SEEK_SET);
            fseek(archi,sizeof(Cliente)*(posicion-1),SEEK_CUR);
            fread(aCargar,sizeof(Cliente),1,archi);
        }
    }
    fclose(archi);
}

void habitacionReservar(Habitaciones *aCargar){
    int numero;
    printf("\nElegi el numero de la habitacion:\n");
    fflush(stdin);
    scanf("%i",&numero);
    Habitaciones aux;
    FILE *archi= fopen (HABITACIONES,"rb");
    if(archi != NULL){
        fseek(archi,0,SEEK_SET);
        while(!feof(archi)){
            fread(&aux,sizeof(Habitaciones),1,archi);
            if(aux.numero == numero){
                aCargar->numero = aux.numero;
                aCargar->ambientes = aux.ambientes;
                aCargar->costeNoche = aux.costeNoche;
                mostrarHabitacion(aux);
            }
        }
    }
    fclose(archi);
}


///ENDREGION Posicion en el archivo

///REGION Cargar registros

void cargarCliente(Cliente *aux){
    printf("\nIngrese el nombre del cliente:\n");
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
    printf("\nIngrese el numero de la habitacion:\n");
    fflush(stdin);
    scanf("%i",&aux->numero);
    printf("\nIngrese la cantidad de ambientes que tiene la habitacion:\n");
    fflush(stdin);
    scanf("%i",&aux->ambientes);
    printf("\nIngrese el coste por noche de la habitacion:\n");
    fflush(stdin);
    scanf("%i",&aux->costeNoche);
}

void cargarReserva(Reservas *aux){
    clienteReservar(&aux->reservadoPor);
    mostrarMatrizHabitaciones();
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
    system("pause");
}



///ENDREGION Cargar registros

///REGION Crear archivos

void crearArchivoCliente(){
    FILE *archi = fopen(CLIENTES,"wb");
    if(archi == NULL){
        printf("\nSe creo el archivo\n");
        fclose(archi);
    }else{
        printf("\nEl archivo ya esta creado\n");
        fclose(archi);
    }
    system("pause");
}

void crearArchivoHabitaciones(){
    FILE *archi = fopen(HABITACIONES,"wb");
    if(archi == NULL){
        printf("\nSe creo el archivo\n");
        fclose(archi);
    }else{
        printf("\nEl archivo ya esta creado\n");
        fclose(archi);
    }
    system("pause");
}

void crearArchivoReservas(){
    FILE *archi = fopen(RESERVAS,"wb");
    if(archi == NULL){
        printf("\nSe creo el archivo\n");
        fclose(archi);
    }else{
        printf("\nEl archivo ya esta creado\n");
        fclose(archi);
    }
    system("pause");
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
    Cliente aux;
    cargarCliente(&aux);
    FILE *archi=fopen(CLIENTES,"ab");
    if(archi != NULL){
       fwrite(&aux,sizeof(Cliente),1,archi);
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
        crearArchivoHabitaciones(aux);
    }
    fclose(archi);
}

void cargarArchivoReservas(){
    Reservas aux;
    cargarReserva(&aux);
    FILE *archi = fopen(RESERVAS, "ab");
    if(archi != NULL){
        fwrite(&aux,sizeof(Reservas),1,archi);
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
    printf("\nCantidad de ambientes: %i\n",aux.ambientes);
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

void mostrarRecursivoCliente(Cliente arr[], int i, int val){
    if(i<val){
        printf("\n\n[%i].",i+1);
        mostrarCliente(arr[i]);
        mostrarRecursivoCliente(arr,i+1,val);
    }
}

void mostrarRecursivoReserva(Reservas arr[], int i, int val){
    if(i<val){
        mostrarReserva(arr[i]);
        mostrarRecursivoReserva(arr,i+1,val-1);
    }
}

void mostrarRecursivoHabitacion(Habitaciones arr[], int i, int val){
    if(i<val){
        printf("\n\n[%i].",i+1);
        mostrarHabitacion(arr[i]);
        mostrarRecursivoHabitacion(arr, i+1, val);
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
    system("cls");
    int val =0;
    Cliente aux[50];
    FILE *archi = fopen(CLIENTES,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            if(!feof(archi)){
                fread(&aux[val],sizeof(Cliente),1,archi);
                val++;
            }
        }
        int i=0;
        mostrarRecursivoCliente(aux,i,val-1);
    }
    fclose(archi);
}

void abrirArchivoHabitacion(){
    system("cls");
    int i = 0, val = 0;
    Habitaciones aux[10];
    FILE *archi = fopen(HABITACIONES,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            if(!feof(archi)){
                fread(&aux[val], sizeof(Habitaciones), 1, archi);
                val++;
            }
        }
        mostrarRecursivoHabitacion(aux, i, val-1);

    }
    fclose(archi);
}

void abrirArchivoReservas(){
    system("cls");
    int i = 0;
    int val =0;
    Reservas aux[50];
    FILE *archi = fopen(RESERVAS,"rb");
    if(archi != NULL){
        while(!feof(archi)){
            if(!feof(archi)){
                fread(&aux[val],sizeof(Reservas),1,archi);
                val++;
                printf("%i",val);

            }
        }
        mostrarRecursivoReserva(aux,i,val-1);
    }
    fclose(archi);
}
void listarReservas() {
    system("cls");
    int i = 0;
    int val = 0;
    Reservas aux[50];
    FILE *archi = fopen(RESERVAS, "rb");
    if (archi != NULL) {
        while (!feof(archi)) {
            if (!feof(archi)) {
                fread(&aux[val], sizeof(Reservas), 1, archi);
                val++;
            }
        }
        mostrarRecursivoReserva(aux, i, val - 1);
    } else {
        printf("No se pudo abrir el archivo de reservas.\n");
    }
    fclose(archi);
    system("pause");
}
int buscarReservaPorDNI() {
    int dni, pos = -1, i = 0;
    Reservas aux;

    printf("\nIngrese el DNI del cliente que realiz� la reserva:\n");
    fflush(stdin);
    scanf("%i", &dni);

    FILE *archi = fopen(RESERVAS, "rb");
    if (archi != NULL) {
        while (fread(&aux, sizeof(Reservas), 1, archi)) {
            if (aux.reservadoPor.dni == dni) {
                pos = i;
                mostrarReserva(aux);
                break;
            }
            i++;
        }
        fclose(archi);
    } else {
        printf("\nNo se pudo abrir el archivo de reservas.\n");
    }

    return pos;
}

void posicionReserva() {
    int pos = buscarReservaPorDNI();
    if (pos >= 0) {
    } else {
        printf("\nNo se encontr� la reserva.\n");
    }
    system("pause");
}

///ENDREGION Mostrar contenido del archivo

///REGION MENU

//TO DO Crear un menu utilizable

void mainMenu(){
    int selector;
    do{
        system("cls");
        printf("\nSelecciona una opcion:\n");
        printf("\n1. Clientes\n");
        printf("\n2. Reservas\n");
        printf("\n3. Habitaciones\n");
        printf("\n0. Cerrar programa\n");
        fflush(stdin);
        scanf("%i",&selector);
        switch(selector){
            case 1:
                clienteMenu();
                break;
            case 2:
                reservaMenu();
                break;
            case 3:
                habitacionesMenu();
                break;
            default:
                break;
        }
    }while(selector != 0);
}

void clienteMenu(){
    int selector;
    char control;
    int posicion;
    do{
        system("cls");
        printf("\nSelecciona una opcion:\n");
        printf("\n1. Listar clientes\n");
        printf("\n2. Buscar cliente\n");
        printf("\n3. Agregar cliente\n");
        printf("\n4. Crear archivo cliente\n");
        printf("\n0. Volver\n");
        fflush(stdin);
        scanf("%i",&selector);
        switch(selector){
            case 1:
                abrirArchivoCliente();
                printf("\n");
                system("pause");
                printf("\nDesea modificar algun cliente? s/n :");
                fflush(stdin);
                scanf("%c",&control);
                if(control=='s'){
                    printf("\nElija un cliente: ");
                    fflush(stdin);
                    scanf("%i",&posicion);
                    clienteMB(posicion);
                }
                break;
            case 2:
                posicionCliente();
                break;
            case 3:
                cargarArchivoClientes();
                break;
            case 4:
                crearArchivoCliente();
                break;
            case 0:
                break;
        }
    }while(selector != 0);
}

void reservaMenu(){
     int selector;
    do {
        system("cls");
        printf("\nSelecciona una opci�n:\n");
        printf("\n1. Listar reservas\n");
        printf("\n2. Buscar reserva\n");
        printf("\n3. Agregar reserva\n");
        printf("\n4. Crear archivo de reservas\n");
        printf("\n0. Volver\n");
        fflush(stdin);
        scanf("%i", &selector);
        switch (selector) {
            case 1:
                listarReservas();
                break;
            case 2:
                posicionReserva();
                break;
            case 3:
                cargarArchivoReservas();
                break;
            case 4:
                crearArchivoReservas();
                break;
            case 0:
                break;
        }
    } while (selector != 0);
}

void habitacionesMenu(){
    int selector;
    do{
        system("cls");
        printf("\nSelecciona una opcion:\n");
        printf("\n1. Listar habitaciones\n");
        printf("\n2. Buscar habitacion\n");
        printf("\n3. Agregar habitacion (son 9 habitaciones min y max)\n");
        printf("\n4. Crear archivo de habitaciones\n");
        printf("\n0. Volver\n");
        fflush(stdin);
        scanf("%i",&selector);
        switch(selector){
            case 1:
                abrirArchivoHabitacion();
                mostrarMatrizHabitaciones();
                printf("\n");
                system("pause");
                break;
            case 2:
                posicionHabitacion();
                break;
            case 3:
                cargarArchivoHabitaciones();
                break;
            case 4:
                crearArchivoHabitaciones();
                break;
            case 0:
                break;
        }
    }while(selector != 0);
}

///END REGION MENU

int main()
{
    mainMenu();
    return 0;
}
