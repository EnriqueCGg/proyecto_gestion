#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Estructura
struct Encuestado {
    char nombre[50];
    int edad;
    char genero; // 'M', 'F' u 'O'
    int calificacion_servicio; // de 1 a 10
    char comentarios[200];
};

const char* nombres[] = {
    "Jhair", "Marco", "Josue", "Mariana", "Karina",
    "Ana", "Luis", "Pedro", "Lucia", "Carlos", 
    "Maria", "Jorge", "Sofia", "Miguel", "Elena"
};

// Se divide los comentarios para que coincida con la calificacion
const char* comentarios_bajos[] = {
    "No me gusto", "Mala experiencia", "Nada especial"
};

const char* comentarios_medios[] = {
    "Regular", "Podria mejorar", "Facil de usar"
};

const char* comentarios_altos[] = {
    "Muy buen servicio", "Excelente", "Recomiendo el producto", "Volveria a usarlo"
};

//genera datos aleatorios
void encuestadosRandom(struct Encuestado datos[], int cantidad) {
    srand(time(NULL));
    for (int i = 0; i < cantidad; i++) {
        strcpy(datos[i].nombre, nombres[rand() % 15]); //accede a uno de los 15 nombres
        datos[i].edad = 18 + rand() % 50;    // indica una edad de 18 a 67 años
        char generos[] = {'M', 'F', 'O'};
        datos[i].genero = generos[rand() % 3]; //selecciona aleatoriamente una de esas 3 opciones 
        datos[i].calificacion_servicio = 1 + rand() % 10; //calificacion del 1 al 10

        // Elegir comentario segun la calificacion
        if (datos[i].calificacion_servicio <= 4) {
            strcpy(datos[i].comentarios, comentarios_bajos[rand() % 3]);
        } else if (datos[i].calificacion_servicio <= 7) {
            strcpy(datos[i].comentarios, comentarios_medios[rand() % 3]);
        } else {
            strcpy(datos[i].comentarios, comentarios_altos[rand() % 4]);
        }
    }
}

//Funcion para agrega un nuevo review a la lista
void agregar(struct Encuestado encuestados[], int index) {
    char nombre[50];
    int edad;
    char genero;
    int calificacion_servicio;
    char comentarios[100];

    printf("Nombre: ");
    scanf("%s", nombre);
    printf("Edad: ");
    scanf("%d", &edad);
    printf("Genero (M/F/O): ");
    scanf(" %c", &genero);
    printf("Calificacion del servicio (1-10): ");
    scanf("%d", &calificacion_servicio);
    printf("Comentarios: ");
    getchar(); // consumir newline pendiente
    fgets(comentarios, sizeof(comentarios), stdin);
    comentarios[strcspn(comentarios, "\n")] = '\0'; // eliminar newline

    //Guarda los datos a la lista de reviews
    strcpy(encuestados[index].nombre, nombre);
    encuestados[index].edad = edad;
    encuestados[index].genero = genero;
    encuestados[index].calificacion_servicio = calificacion_servicio;
    strcpy(encuestados[index].comentarios, comentarios);
}

// Visualiza los reviews en forma de tabla
void verEncuestados(struct Encuestado encuestados[], int cantidad_personas){
    printf("\n%-3s %-15s %-5s %-7s %-17s %-s\n", "#", "Nombre", "Edad", "Genero", "Calif. Servicio", "Comentarios");
    for (int i = 0; i < cantidad_personas; i++) {
        printf("%-3d %-15s %-5d %-7c %-17d %-s\n", //Los numeros hacen referencia a los saltos de caractreres
            i + 1,
            encuestados[i].nombre, 
            encuestados[i].edad, 
            encuestados[i].genero, 
            encuestados[i].calificacion_servicio, 
            encuestados[i].comentarios);
    }
}

//Evalua las estidisticas
void mostrarEstadisticas(struct Encuestado encuestados[], int cantidad) {
    int suma_calificaciones = 0;
    int rango_1 = 0, rango_2 = 0, rango_3 = 0, rango_4 = 0;
    int conteo_M = 0, conteo_F = 0, conteo_O = 0;

    for (int i = 0; i < cantidad; i++) {
        // Promedio
        suma_calificaciones += encuestados[i].calificacion_servicio;

        // Rango de edades
        if (encuestados[i].edad <= 20) rango_1++;
        else if (encuestados[i].edad <= 30) rango_2++;
        else if (encuestados[i].edad <= 40) rango_3++;
        else rango_4++;

        // Genero
        if (encuestados[i].genero == 'M') conteo_M++;
        else if (encuestados[i].genero == 'F') conteo_F++;
        else conteo_O++;
    }

    float promedio = (float)suma_calificaciones / cantidad;
    float porc_M = 100.0 * conteo_M / cantidad;
    float porc_F = 100.0 * conteo_F / cantidad;
    float porc_O = 100.0 * conteo_O / cantidad;

    printf("\n--- Estadisticas Generales ---\n");
    printf("Promedio de calificacion: %.2f\n", promedio);
    printf("Rango de edades:\n");
    printf("  <=20: %d personas\n", rango_1);
    printf("  21-30: %d personas\n", rango_2);
    printf("  31-40: %d personas\n", rango_3);
    printf("  >40: %d personas\n", rango_4);
    printf("Porcentaje por genero:\n");
    printf("  Masculino (M): %.2f%%\n", porc_M);
    printf("  Femenino (F): %.2f%%\n", porc_F);
    printf("  Otro (O): %.2f%%\n", porc_O);
}

//funcion para buscar por nombres
void buscarPorNombre(struct Encuestado encuestados[], int cantidad) {
    char nombre[50];
    printf("Ingrese el nombre a buscar: ");
    scanf("%s", nombre);

    int encontrado = 0;

    printf("\n%-3s %-15s %-5s %-7s %-17s %-s\n", "#", "Nombre", "Edad", "Genero", "Calif. Servicio", "Comentarios");

    for (int i = 0; i < cantidad; i++) {
        if (strcmp(encuestados[i].nombre, nombre) == 0) {
            printf("%-3d %-15s %-5d %-7c %-17d %-s\n",
                i + 1,
                encuestados[i].nombre,
                encuestados[i].edad,
                encuestados[i].genero,
                encuestados[i].calificacion_servicio,
                encuestados[i].comentarios);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontro ninguna persona con ese nombre.\n");
    }
}

int main() {
    struct Encuestado encuestados[100]; //100 es el numero maximo de reviews
    int cantidad_personas = 80; //80 datos generados aleatoriamente
    int opcion;

    encuestadosRandom(encuestados, cantidad_personas);

    do {
        printf("\n-------------------------------\n");
        printf("1. Agregar nuevo encuestado\n");
        printf("2. Ver todos los encuestados\n");
        printf("3. Ver estadisticas generales\n");
        printf("4. Buscar por nombre\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (cantidad_personas < 100) {
                    agregar(encuestados, cantidad_personas);
                    cantidad_personas++; // se suma uno para agregar otro reviews
                } else {
                    printf("Limite alcanzado.\n");
                }
                break;
            case 2:
                verEncuestados(encuestados, cantidad_personas);
                break;
            case 3:
                mostrarEstadisticas(encuestados, cantidad_personas);
                break;
            case 4:
                buscarPorNombre(encuestados, cantidad_personas);
                break;
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 5);

    return 0;
}