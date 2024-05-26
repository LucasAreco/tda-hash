#include "pa2m.h"
#include "src/hash.h"
#include <string.h>
#include <stdlib.h>

#define CAPACIDAD_VALIDA 8
#define CANTIDAD_CLAVES 1000


bool imprimir_valor_par(const char *clave, void *valor, void *aux) {
    int numero = *(int*)valor;
    if (numero % 2 == 0) {
        printf("Clave: %s, Valor: %d\n", clave, numero);
        return true;

    } 

    return false;
    
}


bool imprimir_valor(const char *clave, void *valor, void *aux) {
    int numero = *(int*)valor;
    printf("Clave: %s, Valor: %d\n", clave, numero);
    return true;
}

bool sumar_a_valores(const char *clave, void *valor, void *aux) {
    int *numero = (int*)valor;
    int suma = *(int*)aux;
    *numero += suma;
    return true;
}


void creacion_de_hash() 
{
	hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	pa2m_afirmar(nuevo_hash != NULL, "Un hash con capacidad mayor a 3 se crea correctamente");
	pa2m_afirmar(hash_cantidad(nuevo_hash) == 0, "Un hash vacío no tiene elementos.");

	hash_destruir(nuevo_hash);

	hash_t* otro_hash = hash_crear(0);
	pa2m_afirmar(otro_hash != NULL, "Al pasar capacidad 0, el hash se crea correctemente.");

	hash_destruir(otro_hash);


	hash_t* hash_diferente = hash_crear(2);
	pa2m_afirmar(hash_diferente != NULL, "Al pasar capacidad menor a 3, el hash se crea correctemente.");



	hash_destruir(hash_diferente);
}

void insertar_elementos_en_el_hash()
{
    hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);
    const char* clave_1 = "hola";
    char* valor_1 = "hello";

    const char* clave_2 = "hola";
    char* valor_2 = "bonjour";
    char* valor_anterior_clave_1 = NULL; 

    const char* clave_3 = "gato";
    char* valor_3 = "cat";

    // const char* clave_4 = "hacer";
    // char* valor_4 = "do";

    const char* clave_5 = "auto";
    char* valor_5 = "car";

    const char* clave_6 = "sol";
    char* valor_6 = "sun";

    const char* clave_7 = "take";
    char* valor_7 = "tomar";

    const char* clave_8 = "name";
    char* valor_8 = "nombre";

    // const char* clave_9 = "casa";
    // char* valor_9 = "house";

    // const char* clave_10 = "bird";
    // char* valor_10 = "pájaro";

    // const char* clave_11 = "moon";
    // char* valor_11 = "luna";

    // const char* clave_12 = "tree";
    // char* valor_12 = "árbol";

    // const char* clave_13 = "water";
    // char* valor_13 = "agua";

    // const char* clave_14 = "mountain";
    // char* valor_14 = "montaña";

    pa2m_afirmar(hash_insertar(NULL, clave_8, valor_8, NULL) == NULL, "Inserta en un hash inválido, devuelve NULL");
    pa2m_afirmar(hash_insertar(nuevo_hash, NULL, valor_2, NULL) == NULL, "Inserta con clave inválida, devuelve NULL");
    pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, NULL, NULL) != NULL, "Se puede insertar un valor NULL correctamente.");

    hash_insertar(nuevo_hash, clave_1, valor_1, NULL); 
    pa2m_afirmar(hash_obtener(nuevo_hash, clave_1) == valor_1, "Inserta correctamente en un hash vacío.");
    pa2m_afirmar(hash_obtener(nuevo_hash, clave_1) == valor_1, "Se encuentra valor el insertado (valor 1).");

    hash_insertar(nuevo_hash, clave_2, valor_2, (void**)&valor_anterior_clave_1);

    pa2m_afirmar(strcmp(valor_anterior_clave_1, valor_1) == 0, "Obtenemos el anterior correctamente al insertar con clave repetida.");

    pa2m_afirmar(hash_cantidad(nuevo_hash) == 1, "Se mantiene la cantidad de pares al insertar con clave repetida.");

    hash_insertar(nuevo_hash, clave_3, valor_3, NULL);
    pa2m_afirmar(hash_obtener(nuevo_hash, clave_3) == valor_3, "Se encuentra el valor insertado (valor 3).");

    hash_insertar(nuevo_hash, clave_5, valor_5, NULL);
    hash_insertar(nuevo_hash, clave_6, valor_6, NULL);
    hash_insertar(nuevo_hash, clave_7, valor_7, NULL);

    pa2m_afirmar(hash_insertar(nuevo_hash, clave_8, valor_8, NULL) != NULL, "Inserta correctamente un nuevo valor, luego de insertar varios elementos.");
    pa2m_afirmar(hash_obtener(nuevo_hash, clave_8) == valor_8, "Se encuentra el valor insertado (clave 8).");

    hash_destruir(nuevo_hash);
}


void hash_contiene_verifica_que_este_el_valor_por_su_clave() 
{

    hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);
    const char* clave_1 = "Juan";
    int valor_1 = 20;

    const char* clave_2 = "Gonzalo";
    int valor_2 = 30;

    const char* clave_3 = "Camila";
    int valor_3 = 25;

    const char* clave_4 = "Pepe";
    int valor_4 = 100;

    const char* clave_5 = "Tomas";
    int valor_5 = 10;

    const char* clave_6 = "Javier";
    int valor_6 = 80;

    const char* clave_7 = "Jorge";
    int valor_7 = 20;

    const char* clave_8 = "Julian";
    int valor_8 = 21;

    const char* clave_9 = "Melissa";
    int valor_9 = 43;

    hash_insertar(nuevo_hash, clave_1, &valor_1, NULL); 
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_1) == true, "Al contener una clave recien insertada, devuelve TRUE.");
    hash_insertar(nuevo_hash, clave_2, &valor_2, NULL);
    hash_insertar(nuevo_hash, clave_3, &valor_3, NULL);
    hash_insertar(nuevo_hash, clave_4, &valor_4, NULL);
    hash_insertar(nuevo_hash, clave_5, &valor_5, NULL);
    hash_insertar(nuevo_hash, clave_6, &valor_6, NULL);
    hash_insertar(nuevo_hash, clave_7, &valor_7, NULL);
    hash_insertar(nuevo_hash, clave_8, &valor_8, NULL);
    hash_insertar(nuevo_hash, clave_9, &valor_9, NULL);
    
    pa2m_afirmar(hash_contiene(NULL, clave_1) == false, "Un hash no válido no contiene clave.");
    pa2m_afirmar(hash_contiene(nuevo_hash, NULL) == false, "Buscar con clave inválida, devuelve FALSE.");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_2) == true, "Al contener la clave buscada, devuelve TRUE.");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_3) == true, "Al contener la clave buscada, devuelve TRUE.");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_4) == true, "Al contener la clave buscada, devuelve TRUE.");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_6) == true, "Al contener la clave buscada, devuelve TRUE.");

    pa2m_afirmar(hash_contiene(nuevo_hash, "Leticia") == false, "Al no contener la clave buscada, devuelve FALSE.");
    pa2m_afirmar(hash_contiene(nuevo_hash, "Pamela") == false, "Al no contener la clave buscada, devuelve FALSE.");

    hash_quitar(nuevo_hash, clave_3);
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_3) == false, "Al no contener clave recien quitada, devuelve FALSE.");

    hash_destruir(nuevo_hash);
}





void hash_quitar_quita_valor_y_clave_del_hash() 
{
    hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);
    const char* clave_1 = "Juan";
    int valor_1 = 20;

    const char* clave_2 = "Gonzalo";
    int valor_2 = 30;

    const char* clave_3 = "Camila";
    int valor_3 = 25;

    const char* clave_4 = "Pepe";
    int valor_4 = 100;

    const char* clave_5 = "Tomas";
    int valor_5 = 10;

    const char* clave_6 = "Javier";
    int valor_6 = 80;

    const char* clave_7 = "Jorge";
    int valor_7 = 20;

    const char* clave_8 = "Julian";
    int valor_8 = 21;

    const char* clave_9 = "Melissa";
    int valor_9 = 43;

    hash_insertar(nuevo_hash, clave_1, &valor_1, NULL); 



    pa2m_afirmar(hash_quitar(NULL, clave_1) == NULL, "Eliminar valor de un hash inválido, devuelve NULL.");
    pa2m_afirmar(hash_quitar(nuevo_hash, NULL) == NULL, "Eliminar valor con clave inválida, devuelve NULL.");


    pa2m_afirmar(hash_quitar(nuevo_hash, clave_1) == &valor_1, "Elimina correctamente el único valor del hash (valor 1).");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_1) == false, "El hash ya no contiene el valor eliminado (valor 1).");
    pa2m_afirmar(hash_cantidad(nuevo_hash) == 0, "Al eliminar todos los elementos, el hash queda vacío.");



    hash_insertar(nuevo_hash, clave_2, &valor_2, NULL);
    hash_insertar(nuevo_hash, clave_3, &valor_3, NULL);
    hash_insertar(nuevo_hash, clave_4, &valor_4, NULL);
    hash_insertar(nuevo_hash, clave_5, &valor_5, NULL);
    hash_insertar(nuevo_hash, clave_6, &valor_6, NULL);
    hash_insertar(nuevo_hash, clave_7, &valor_7, NULL);
    hash_insertar(nuevo_hash, clave_8, &valor_8, NULL);
    hash_insertar(nuevo_hash, clave_9, &valor_9, NULL);


    pa2m_afirmar(hash_quitar(nuevo_hash, clave_2) == &valor_2, "Elimina correctame un valor del hash (valor 2).");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_2) == false, "El hash ya no contiene el valor eliminado (valor 2).");

    pa2m_afirmar(hash_quitar(nuevo_hash, clave_3) == &valor_3, "Elimina correctamente un valor del hash (valor 3).");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_3) == false, "El hash ya no contiene el valor eliminado (valor 3).");

    pa2m_afirmar(hash_quitar(nuevo_hash, clave_4) == &valor_4, "Elimina correctamente un valor del hash (valor 4).");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_4) == false, "El hash ya no contiene el valor eliminado (valor 4).");

    pa2m_afirmar(hash_quitar(nuevo_hash, clave_5) == &valor_5, "Elimina correctamente un valor del hash (valor 5).");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_5) == false, "El hash ya no contiene el valor eliminado (valor 5).");

    pa2m_afirmar(hash_quitar(nuevo_hash, clave_8) == &valor_8, "Elimina correctamente un valor del hash (valor 8).");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_8) == false, "El hash ya no contiene el valor eliminado (valor 8).");

    pa2m_afirmar(hash_cantidad(nuevo_hash) == 3, "La cantidad de elementos en el hash es correcta después de eliminar varios elementos.");

    pa2m_afirmar(hash_quitar(nuevo_hash, "Lucas") == NULL, "Eliminar con clave inexistente, devuelve NULL.");
    
    hash_quitar(nuevo_hash, clave_6);
        hash_quitar(nuevo_hash, clave_7);
    hash_quitar(nuevo_hash, clave_9);

    pa2m_afirmar(hash_cantidad(nuevo_hash) == 0, "Al eliminar todos los elementos, el hash queda vacío.");

    hash_destruir(nuevo_hash);    
}




void hash_inserta_y_elimina_muchos_elementos() 
{
    hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

    char claves[CANTIDAD_CLAVES][20]; 
    int elementos[CANTIDAD_CLAVES];
    for (int i = 0; i < CANTIDAD_CLAVES; i++) {
        snprintf(claves[i], sizeof(claves[i]), "clave%d", i);
        elementos[i] = i;
    }

    bool exito = true;
    for (int i = 0; i < CANTIDAD_CLAVES; i++) {
        if (hash_insertar(nuevo_hash, claves[i], &elementos[i], NULL) == NULL) {
            exito = false;
        }
    }

    pa2m_afirmar(exito, "Inserta correctamente las claves y elementos en el hash.");

    bool contiene_todos = true;
    for (int i = 0; i < CANTIDAD_CLAVES; i++) {
        if (hash_obtener(nuevo_hash, claves[i]) != &elementos[i]) {
            contiene_todos = false;
            break;
        }
    }

    pa2m_afirmar(contiene_todos, "El hash contiene correctamente todos los elementos insertados.");

    pa2m_afirmar(hash_cantidad(nuevo_hash) == CANTIDAD_CLAVES, "El hash tiene la cantidad correcta de elementos.");

    bool eliminado_correctamente = true;
    for (int i = 0; i < CANTIDAD_CLAVES; i++) {
        if (hash_quitar(nuevo_hash, claves[i]) != &elementos[i]) {
            eliminado_correctamente = false;
            break;
        }
    }

    pa2m_afirmar(eliminado_correctamente, "Elimina correctamente todos los elementos del hash.");

    bool contiene_alguno = false;
    for (int i = 0; i < CANTIDAD_CLAVES; i++) {
        if (hash_obtener(nuevo_hash, claves[i]) != NULL) {
            contiene_alguno = true;
            break;
        }
    }

    pa2m_afirmar(!contiene_alguno, "El hash no contiene ningún valor después de eliminar todos los elementos.");
    pa2m_afirmar(hash_cantidad(nuevo_hash) == 0, "Al eliminar todos los elementos, el hash queda vacío.");

    hash_destruir(nuevo_hash);
}


void hash_cantidad_devuelve_cantidad_de_elementos() {
    hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);
    const char* clave_1 = "hola";
    char* valor_1 = "hello";

    const char* clave_2 = "chau";
    char* valor_2 = "bye";

    const char* clave_3 = "gato";
    char* valor_3 = "cat";

    pa2m_afirmar(hash_cantidad(nuevo_hash) == 0, "La cantidad de elementos en un hash sin inserciones es 0.");

    hash_insertar(nuevo_hash, clave_1, &valor_1, NULL); 
    pa2m_afirmar(hash_cantidad(nuevo_hash) == 1, "Al insertar un elemento en hash vacío, la cantidad de elementos es 1.");

    hash_insertar(nuevo_hash, clave_2, &valor_2, NULL);
    hash_insertar(nuevo_hash, clave_3, &valor_3, NULL);

    pa2m_afirmar(hash_cantidad(nuevo_hash) == 3, "Al insertar mas elemento en hash vacío, la cantidad de elementos es correcta.");

    hash_quitar(nuevo_hash, clave_1);
    hash_quitar(nuevo_hash, clave_2);

    pa2m_afirmar(hash_cantidad(nuevo_hash) == 1, "Al eliminar mas de un elemento de un hash con varios elementos, la cantidad de elementos es correcta.");
    hash_quitar(nuevo_hash, clave_3);

    pa2m_afirmar(hash_cantidad(nuevo_hash) == 0, "Al eliminar el único elemento, la cantidad de elementos es 0.");



    hash_quitar(nuevo_hash, clave_3);


    hash_destruir(nuevo_hash);

}

void hash_obtener_devuelve_elemento_correcto() {

    hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);
    const char* clave_1 = "Juan";
    int valor_1 = 20;

    const char* clave_2 = "Gonzalo";
    int valor_2 = 30;

    const char* clave_3 = "Camila";
    int valor_3 = 25;

    const char* clave_4 = "Pepe";
    int valor_4 = 100;

    const char* clave_5 = "Tomas";
    int valor_5 = 10;

    hash_insertar(nuevo_hash, clave_1, &valor_1, NULL); 
    hash_insertar(nuevo_hash, clave_2, &valor_2, NULL);
    hash_insertar(nuevo_hash, clave_3, &valor_3, NULL);
    hash_insertar(nuevo_hash, clave_4, &valor_4, NULL);
    hash_insertar(nuevo_hash, clave_5, &valor_5, NULL);

    pa2m_afirmar(hash_obtener(nuevo_hash, clave_1) == &valor_1, "Obtiene el elemento correcto con la clave existente.");
    pa2m_afirmar(hash_obtener(nuevo_hash, clave_2) == &valor_2, "Obtiene el elemento correcto con la clave existente.");
    pa2m_afirmar(hash_obtener(nuevo_hash, clave_3) == &valor_3, "Obtiene el elemento correcto con la clave existente.");
    pa2m_afirmar(hash_obtener(nuevo_hash, clave_4) == &valor_4, "Obtiene el elemento correcto con la clave existente.");
    pa2m_afirmar(hash_obtener(nuevo_hash, clave_5) == &valor_5, "Obtiene el elemento correcto con la clave existente.");

    pa2m_afirmar(hash_obtener(nuevo_hash, "Leticia") == NULL, "Devuelve NULL al intentar obtener un elemento inexistente.");
    pa2m_afirmar(hash_obtener(nuevo_hash, "Pamela") == NULL, "Devuelve NULL al intentar obtener un elemento inexistente.");

    pa2m_afirmar(hash_obtener(NULL, clave_1) == NULL, "Devuelve NULL al intentar obtener un elemento con hash nulo.");
    
    hash_destruir(nuevo_hash);
}




void hash_con_cada_clave_itera_sobre_el_hash() {
    hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

    const char* clave_1 = "Juan";
    int valor_1 = 20;

    const char* clave_2 = "Gonzalo";
    int valor_2 = 30;

    const char* clave_3 = "Camila";
    int valor_3 = 12;

    const char* clave_4 = "Pepe";
    int valor_4 = 100;

    const char* clave_5 = "Tomas";
    int valor_5 = 10;

    const char* clave_6 = "Javier";
    int valor_6 = 80;

    const char* clave_7 = "Jorge";
    int valor_7 = 21;

    const char* clave_8 = "Julian";
    int valor_8 = 21;

    const char* clave_9 = "Melissa";
    int valor_9 = 43;

    int sumando = 100;

    pa2m_afirmar(hash_con_cada_clave(nuevo_hash, imprimir_valor_par, NULL) == 0, "Iterar un hash vacío, devuelve 0 invocaciones.");
    pa2m_afirmar(hash_con_cada_clave(NULL, imprimir_valor_par, NULL) == 0, "Iterar un hash no válido, devuelve 0 invocaciones.");

    hash_insertar(nuevo_hash, clave_1, &valor_1, NULL); 
    hash_insertar(nuevo_hash, clave_2, &valor_2, NULL);
    hash_insertar(nuevo_hash, clave_3, &valor_3, NULL);
    hash_insertar(nuevo_hash, clave_4, &valor_4, NULL);
    hash_insertar(nuevo_hash, clave_5, &valor_5, NULL);
    hash_insertar(nuevo_hash, clave_6, &valor_6, NULL);
    hash_insertar(nuevo_hash, clave_7, &valor_7, NULL);
    hash_insertar(nuevo_hash, clave_8, &valor_8, NULL);
    hash_insertar(nuevo_hash, clave_9, &valor_9, NULL);

    pa2m_afirmar(hash_con_cada_clave(nuevo_hash, NULL, NULL) == 0, "Iterar un hash con función no válida, devuelve 0 invocaciones.");

    pa2m_afirmar(hash_con_cada_clave(nuevo_hash, imprimir_valor_par, NULL) == 3, "Iterador no recorre todo el hash y devuelve cantidad correcta de invocaciones.");

    pa2m_afirmar(hash_con_cada_clave(nuevo_hash, sumar_a_valores, &sumando) == 9, "Iterador aplica la función con un auxiliar a todo el hash y devuelve cantidad correcta de invocaciones (9).");


    hash_con_cada_clave(nuevo_hash, imprimir_valor, NULL);
    hash_destruir(nuevo_hash);


}

typedef struct {
    char *nombre;
    int edad;
} persona_t;


void destructor(void *dato) {
    if (!dato) {
        return;
    }
    persona_t *persona = (persona_t *)dato;

    free(persona->nombre);

    free(persona);
}

// Función de prueba para hash_destruir_todo
void hash_destruir_todo_destruye_correctamente() {
    hash_t *hash = hash_crear(CAPACIDAD_VALIDA);

    persona_t *juan = malloc(sizeof(persona_t));
    juan->nombre = malloc(strlen("Juan") + 1);
    strcpy(juan->nombre, "Juan");
    juan->edad = 30;

    persona_t *maria = malloc(sizeof(persona_t));
    maria->nombre = malloc(strlen("Maria") + 1);
    strcpy(maria->nombre, "Maria");
    maria->edad = 25;

    hash_insertar(hash, "Juan", juan, NULL);
    hash_insertar(hash, "Maria", maria, NULL);

    hash_destruir_todo(hash, destructor);

    pa2m_afirmar(true, "Memoria liberada correctamente.");
}


int main()
{
	pa2m_nuevo_grupo("\n===Creación de hash===");
	creacion_de_hash();

	pa2m_nuevo_grupo("\n===Inserción de elementos ===");
	insertar_elementos_en_el_hash();    

    pa2m_nuevo_grupo("\n===Eliminación de elementos===");
    hash_quitar_quita_valor_y_clave_del_hash();

    pa2m_nuevo_grupo("\n===Inserción y eliminación de muchos elementos===");
    hash_inserta_y_elimina_muchos_elementos();

    pa2m_nuevo_grupo("\n===Contención de elementos===");
	hash_contiene_verifica_que_este_el_valor_por_su_clave();

    pa2m_nuevo_grupo("\n===Cantidad de elementos===");
    hash_cantidad_devuelve_cantidad_de_elementos();

    pa2m_nuevo_grupo("\n===Obtención de elementos===");
    hash_obtener_devuelve_elemento_correcto();


    pa2m_nuevo_grupo("\n===Iterar elementos===");
    hash_con_cada_clave_itera_sobre_el_hash();

    pa2m_nuevo_grupo("\n===Destrucción de elementos===");
    hash_destruir_todo_destruye_correctamente();


	return pa2m_mostrar_reporte();
}
