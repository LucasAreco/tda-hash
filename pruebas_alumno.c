#include "pa2m.h"
#include "src/hash.h"
#include <string.h>
#include <stdlib.h>

#define CAPACIDAD_VALIDA 8
#define CANTIDAD_CLAVES 1000

bool imprimir_valor_par(const char *clave, void *valor, void *aux)
{
	int numero = *(int *)valor;
	printf("\n");
	if (numero % 2 == 0) {
		printf("Clave: %s, Valor: %d\n", clave, numero);
		return true;
	}

	printf("\n");

	return false;
}

bool imprimir_valor(const char *clave, void *valor, void *aux)
{
	printf("\n");
	int numero = *(int *)valor;
	printf("Clave: %s, Valor: %d\n", clave, numero);
	return true;
}

bool sumar_a_valores(const char *clave, void *valor, void *aux)
{
	int *numero = (int *)valor;
	int suma = *(int *)aux;
	*numero += suma;
	return true;
}

typedef struct {
	char *nombre;
	int edad;
} persona_t;

persona_t *crear_persona(const char *nombre, int edad)
{
	persona_t *persona = malloc(sizeof(persona_t));
	if (!persona) {
		return NULL;
	}
	persona->nombre = malloc(strlen(nombre) + 1);
	if (!persona->nombre) {
		free(persona);
		return NULL;
	}
	strcpy(persona->nombre, nombre);
	persona->edad = edad;
	return persona;
}

void destructor(void *dato)
{
	if (!dato) {
		return;
	}
	persona_t *persona = (persona_t *)dato;

	free(persona->nombre);

	free(persona);
}

void cuando_se_crea_un_hash_con_capacidad_mayor_al_minimo_devuelve_un_hash_válido()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	pa2m_afirmar(nuevo_hash != NULL,
		     "Un hash con capacidad mayor a 3 se crea correctamente.");

	hash_destruir(nuevo_hash);
}

void cuando_se_crea_un_hash_con_capcidad_menor_al_minimo_devuelve_un_hash_valido()
{
	hash_t *otro_hash = hash_crear(0);
	pa2m_afirmar(otro_hash != NULL,
		     "Al pasar capacidad 0, el hash se crea correctemente.");

	hash_destruir(otro_hash);

	hash_t *hash_diferente = hash_crear(2);
	pa2m_afirmar(
		hash_diferente != NULL,
		"Al pasar capacidad menor a 3, el hash se crea correctemente.");

	hash_destruir(hash_diferente);
}

void cuando_se_intenta_insertar_con_algun_parametro_invalido_devuelve_null()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_8 = "name";
	char *valor_8 = "nombre";

	char *valor_2 = "bonjour";

	pa2m_afirmar(hash_insertar(NULL, clave_8, valor_8, NULL) == NULL,
		     "Inserta en un hash inválido, devuelve NULL.");
	pa2m_afirmar(hash_insertar(nuevo_hash, NULL, valor_2, NULL) == NULL,
		     "Inserta con clave inválida, devuelve NULL.");

	hash_destruir(nuevo_hash);
}

void cuando_se_insertan_pares_se_espera_que_el_elemento_este_en_el_hash()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "hola";

	const char *clave_3 = "gato";
	char *valor_3 = "cat";

	const char *clave_4 = "silla";
	char *valor_4 = "chair";

	const char *clave_5 = "auto";
	char *valor_5 = "car";

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, NULL, NULL) != NULL,
		     "Se puede insertar un valor NULL correctamente.");

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_4, valor_4, NULL) != NULL,
		     "Se inserta correctamente el valor 4.");
	pa2m_afirmar(hash_obtener(nuevo_hash, clave_4) == valor_4,
		     "Se encuentra valor el insertado (valor 4).");

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_3, valor_3, NULL) != NULL,
		     "Se inserta correctamente el valor 3");
	pa2m_afirmar(hash_obtener(nuevo_hash, clave_3) == valor_3,
		     "Se encuentra el valor insertado (valor 3).");

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_5, valor_5, NULL) != NULL,
		     "Se inserta correctamente el valor 5");
	pa2m_afirmar(hash_obtener(nuevo_hash, clave_5) == valor_5,
		     "Se encuentra el valor insertado (valor 5).");

	hash_destruir(nuevo_hash);
}

void cuando_se_inserta_valor_nulo_devuelve_el_hash_correctamente()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "hola";

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, NULL, NULL) != NULL,
		     "Se puede insertar un valor NULL correctamente.");

	hash_destruir(nuevo_hash);
}

void cuando_se_inserta_elemento_con_clave_repetida_devuelve_el_hash_correctamente()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "hola";
	char *valor_1 = "hello";

	const char *clave_2 = "hola";
	char *valor_2 = "bonjour";

	char *valor_anterior_clave_1 = NULL;

	hash_insertar(nuevo_hash, clave_1, valor_1, NULL);

	hash_insertar(nuevo_hash, clave_2, valor_2,
		      (void **)&valor_anterior_clave_1);

	pa2m_afirmar(
		strcmp(valor_anterior_clave_1, valor_1) == 0,
		"Obtenemos el anterior correctamente al insertar con clave repetida.");
	pa2m_afirmar(
		hash_cantidad(nuevo_hash) == 1,
		"Se mantiene la cantidad de pares al insertar con clave repetida.");

	hash_destruir(nuevo_hash);
}

void cuando_se_inserta_un_par_luego_de_insertar_varios_se_espera_que_el_par_este_en_el_hash()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "hola";
	char *valor_1 = "hello";

	const char *clave_5 = "auto";
	char *valor_5 = "car";

	const char *clave_6 = "sol";
	char *valor_6 = "sun";

	const char *clave_7 = "take";
	char *valor_7 = "tomar";

	const char *clave_8 = "name";
	char *valor_8 = NULL;

	const char *clave_9 = "casa";
	char *valor_9 = "house";

	const char *clave_10 = "bird";
	char *valor_10 = "pájaro";

	const char *clave_11 = "moon";
	char *valor_11 = "luna";

	const char *clave_12 = "tree";
	char *valor_12 = "árbol";

	const char *clave_13 = "water";
	char *valor_13 = "agua";

	const char *clave_14 = "mountain";
	char *valor_14 = "montaña";

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, valor_1, NULL) != NULL,
		     "Se inserta correctamente el valor 1");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_5, valor_5, NULL) != NULL,
		     "Se inserta correctamente el valor 5");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_6, valor_6, NULL) != NULL,
		     "Se inserta correctamente el valor 6");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_7, valor_7, NULL) != NULL,
		     "Se inserta correctamente el valor 7");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_9, valor_9, NULL) != NULL,
		     "Se inserta correctamente el valor 9");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_10, valor_10, NULL) !=
			     NULL,
		     "Se inserta correctamente el valor 10");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_11, valor_11, NULL) !=
			     NULL,
		     "Se inserta correctamente el valor 11");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_12, valor_12, NULL) !=
			     NULL,
		     "Se inserta correctamente el valor 12");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_13, valor_13, NULL) !=
			     NULL,
		     "Se inserta correctamente el valor 13");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_14, valor_14, NULL) !=
			     NULL,
		     "Se inserta correctamente el valor 14");

	pa2m_afirmar(
		hash_insertar(nuevo_hash, clave_8, valor_8, NULL) != NULL,
		"Inserta correctamente un nuevo valor, luego de insertar varios elementos.");
	pa2m_afirmar(hash_obtener(nuevo_hash, clave_8) == valor_8,
		     "Se encuentra el valor insertado (valor 8).");

	hash_destruir(nuevo_hash);
}

void cuando_se_insertan_elementos_con_valores_nulos_se_insertan_correctamente()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "hola";

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, NULL, NULL) != NULL,
		     "Se inserta correctamente la clave con valor NULL");

	pa2m_afirmar(hash_obtener(nuevo_hash, clave_1) == NULL,
		     "Se encuentra correctamente el valor NULL para la clave");

	hash_destruir(nuevo_hash);
}

void cuando_se_verifica_que_un_hash_no_valido_contenga_un_valor_devuelve_false()
{
	pa2m_afirmar(hash_contiene(NULL, "hola") == false,
		     "Buscar en un hash no válido devuelve FALSE.");
}

void cuando_se_verifica_que_un_hash_contenga_un_valor_por_una_clave_invalida_devuelve_false()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	pa2m_afirmar(hash_contiene(nuevo_hash, NULL) == false,
		     "Buscar con clave inválida, devuelve FALSE.");

	hash_destruir(nuevo_hash);
}

void cuando_se_verifica_que_un_hash_contenga_un_valor_devuelve_true_sino_false()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);
	const char *clave_1 = "Juan";
	int valor_1 = 20;

	const char *clave_2 = "Gonzalo";
	int valor_2 = 30;

	const char *clave_3 = "Camila";
	int valor_3 = 25;

	const char *clave_4 = "Pepe";
	int valor_4 = 100;

	const char *clave_5 = "Tomas";
	int valor_5 = 10;

	const char *clave_6 = "Javier";
	int valor_6 = 80;

	const char *clave_7 = "Jorge";
	int valor_7 = 20;

	const char *clave_8 = "Julian";
	int valor_8 = 21;

	const char *clave_9 = "Melissa";
	int valor_9 = 43;

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, &valor_1, NULL) != NULL,
		     "Se inserta correctamente el valor 1");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_1) == true,
		     "Al contener una clave recien insertada, devuelve TRUE.");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_2, &valor_2, NULL) != NULL,
		     "Se inserta correctamente el valor 2");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_3, &valor_3, NULL) != NULL,
		     "Se inserta correctamente el valor 3");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_4, &valor_4, NULL) != NULL,
		     "Se inserta correctamente el valor 4");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_5, &valor_5, NULL) != NULL,
		     "Se inserta correctamente el valor 5");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_6, &valor_6, NULL) != NULL,
		     "Se inserta correctamente el valor 6");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_7, &valor_7, NULL) != NULL,
		     "Se inserta correctamente el valor 7");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_8, &valor_8, NULL) != NULL,
		     "Se inserta correctamente el valor 8");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_9, &valor_9, NULL) != NULL,
		     "Se inserta correctamente el valor 9");

	pa2m_afirmar(hash_contiene(nuevo_hash, clave_2) == true,
		     "Al contener la clave buscada, devuelve TRUE.");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_3) == true,
		     "Al contener la clave buscada, devuelve TRUE.");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_4) == true,
		     "Al contener la clave buscada, devuelve TRUE.");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_6) == true,
		     "Al contener la clave buscada, devuelve TRUE.");

	pa2m_afirmar(hash_contiene(nuevo_hash, "Leticia") == false,
		     "Al no contener la clave buscada, devuelve FALSE.");
	pa2m_afirmar(hash_contiene(nuevo_hash, "Pamela") == false,
		     "Al no contener la clave buscada, devuelve FALSE.");

	pa2m_afirmar(hash_quitar(nuevo_hash, clave_3) != NULL,
		     "Se quita el valor 3 correctamente");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_3) == false,
		     "Al no contener clave recien quitada, devuelve FALSE.");

	hash_destruir(nuevo_hash);
}

void cuando_se_intenta_quitar_de_un_hash_no_válido_devuelve_null()
{
	pa2m_afirmar(hash_quitar(NULL, "clave") == NULL,
		     "Eliminar valor de un hash inválido, devuelve NULL.");
}

void cuando_se_intenta_quitar_de_un_hash_con_clave_nula_devuelve_null()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "Sol";
	int valor_1 = 220;

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, &valor_1, NULL) != NULL,
		     "Se inserta correctamente el valor 1");

	pa2m_afirmar(hash_quitar(nuevo_hash, NULL) == NULL,
		     "Eliminar valor con clave inválida, devuelve NULL.");

	hash_destruir(nuevo_hash);
}

void cuando_se_van_quitando_varios_pares_en_el_hash_se_espera_que_no_se_encuentren_los_valores_en_el_hash()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "Sol";
	int valor_1 = 220;

	const char *clave_2 = "Gonzalo";
	int valor_2 = 30;

	const char *clave_3 = "Camila";
	int valor_3 = 25;

	const char *clave_4 = "Pepe";
	int valor_4 = 100;

	const char *clave_5 = "Tomas";
	int valor_5 = 10;

	const char *clave_6 = "Javier";
	int valor_6 = 80;

	const char *clave_7 = "Jorge";
	int valor_7 = 20;

	const char *clave_8 = "Julian";
	int valor_8 = 21;

	const char *clave_9 = "Melissa";
	int valor_9 = 43;

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, &valor_1, NULL) != NULL,
		     "Se inserta correctamente el valor 1");

	pa2m_afirmar(
		hash_quitar(nuevo_hash, clave_1) == &valor_1,
		"Elimina correctamente el único valor del hash (valor 1).");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_1) == false,
		     "El hash ya no contiene el valor eliminado (valor 1).");
	pa2m_afirmar(hash_cantidad(nuevo_hash) == 0,
		     "Al eliminar todos los elementos, el hash queda vacío.");

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_2, &valor_2, NULL) != NULL,
		     "Se inserta correctamente el valor 2");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_3, &valor_3, NULL) != NULL,
		     "Se inserta correctamente el valor 3");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_4, &valor_4, NULL) != NULL,
		     "Se inserta correctamente el valor 4");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_5, &valor_5, NULL) != NULL,
		     "Se inserta correctamente el valor 5");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_6, &valor_6, NULL) != NULL,
		     "Se inserta correctamente el valor 6");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_7, &valor_7, NULL) != NULL,
		     "Se inserta correctamente el valor 7");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_8, &valor_8, NULL) != NULL,
		     "Se inserta correctamente el valor 8");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_9, &valor_9, NULL) != NULL,
		     "Se inserta correctamente el valor 9");

	pa2m_afirmar(hash_quitar(nuevo_hash, clave_2) == &valor_2,
		     "Elimina correctame un valor del hash (valor 2).");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_2) == false,
		     "El hash ya no contiene el valor eliminado (valor 2).");

	pa2m_afirmar(hash_quitar(nuevo_hash, clave_3) == &valor_3,
		     "Elimina correctamente un valor del hash (valor 3).");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_3) == false,
		     "El hash ya no contiene el valor eliminado (valor 3).");

	pa2m_afirmar(hash_quitar(nuevo_hash, clave_4) == &valor_4,
		     "Elimina correctamente un valor del hash (valor 4).");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_4) == false,
		     "El hash ya no contiene el valor eliminado (valor 4).");

	pa2m_afirmar(hash_quitar(nuevo_hash, clave_5) == &valor_5,
		     "Elimina correctamente un valor del hash (valor 5).");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_5) == false,
		     "El hash ya no contiene el valor eliminado (valor 5).");

	pa2m_afirmar(hash_quitar(nuevo_hash, clave_8) == &valor_8,
		     "Elimina correctamente un valor del hash (valor 8).");
	pa2m_afirmar(hash_contiene(nuevo_hash, clave_8) == false,
		     "El hash ya no contiene el valor eliminado (valor 8).");

	pa2m_afirmar(
		hash_cantidad(nuevo_hash) == 3,
		"La cantidad de elementos en el hash es correcta después de eliminar varios elementos.");

	pa2m_afirmar(hash_quitar(nuevo_hash, "Lucas") == NULL,
		     "Eliminar con clave inexistente, devuelve NULL.");

	pa2m_afirmar(hash_quitar(nuevo_hash, clave_6) != NULL,
		     "Se elimina correctamente el valor asociado a la clave 6");
	pa2m_afirmar(hash_quitar(nuevo_hash, clave_7) != NULL,
		     "Se elimina correctamente el valor asociado a la clave 7");
	pa2m_afirmar(hash_quitar(nuevo_hash, clave_9) != NULL,
		     "Se elimina correctamente el valor asociado a la clave 9");

	pa2m_afirmar(hash_cantidad(nuevo_hash) == 0,
		     "Al eliminar todos los elementos, el hash queda vacío.");

	hash_destruir(nuevo_hash);
}

void cuando_se_insertan_y_eliminan_muchos_valores_del_hash_se_espera_una_correcta_insercion_y_eliminacion()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	char claves[CANTIDAD_CLAVES][20];
	int elementos[CANTIDAD_CLAVES];
	for (int i = 0; i < CANTIDAD_CLAVES; i++) {
		snprintf(claves[i], sizeof(claves[i]), "clave%d", i);
		elementos[i] = i;
	}

	bool exito = true;
	for (int i = 0; i < CANTIDAD_CLAVES; i++) {
		if (hash_insertar(nuevo_hash, claves[i], &elementos[i], NULL) ==
		    NULL) {
			exito = false;
		}
	}

	pa2m_afirmar(
		exito,
		"Inserta correctamente las claves y elementos en el hash.");

	bool contiene_todos = true;
	for (int i = 0; i < CANTIDAD_CLAVES; i++) {
		if (hash_obtener(nuevo_hash, claves[i]) != &elementos[i]) {
			contiene_todos = false;
			break;
		}
	}

	pa2m_afirmar(
		contiene_todos,
		"El hash contiene correctamente todos los elementos insertados.");

	pa2m_afirmar(hash_cantidad(nuevo_hash) == CANTIDAD_CLAVES,
		     "El hash tiene la cantidad correcta de elementos.");

	bool eliminado_correctamente = true;
	for (int i = 0; i < CANTIDAD_CLAVES; i++) {
		if (hash_quitar(nuevo_hash, claves[i]) != &elementos[i]) {
			eliminado_correctamente = false;
			break;
		}
	}

	pa2m_afirmar(eliminado_correctamente,
		     "Elimina correctamente todos los elementos del hash.");

	bool contiene_alguno = false;
	for (int i = 0; i < CANTIDAD_CLAVES; i++) {
		if (hash_obtener(nuevo_hash, claves[i]) != NULL) {
			contiene_alguno = true;
			break;
		}
	}

	pa2m_afirmar(
		!contiene_alguno,
		"El hash no contiene ningún valor después de eliminar todos los elementos.");
	pa2m_afirmar(hash_cantidad(nuevo_hash) == 0,
		     "Al eliminar todos los elementos, el hash queda vacío.");

	hash_destruir(nuevo_hash);
}

void cuando_se_solicita_la_cantidad_de_pares_de_hash_inválido_devuelve_cero()
{
	pa2m_afirmar(hash_cantidad(NULL) == 0,
		     "Un hash nulo no tiene elementos, devuelve 0.");
}

void cuando_se_solicita_la_cantidad_de_pares_en_hash_vacio_devuelve_cero()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	pa2m_afirmar(hash_cantidad(nuevo_hash) == 0,
		     "Un hash vacío no tiene elementos.");

	hash_destruir(nuevo_hash);
}

void cuando_se_solicita_la_cantiadad_de_pares_con_inserciones_y_eliminaciones_pares_devuelve_la_cantidad_correcta()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "hola";
	char *valor_1 = "hello";

	const char *clave_2 = "chau";
	char *valor_2 = "bye";

	const char *clave_3 = "gato";
	char *valor_3 = "cat";

	pa2m_afirmar(
		hash_cantidad(nuevo_hash) == 0,
		"La cantidad de elementos en un hash sin inserciones es 0.");

	hash_insertar(nuevo_hash, clave_1, &valor_1, NULL);
	pa2m_afirmar(
		hash_cantidad(nuevo_hash) == 1,
		"Al insertar un elemento en hash vacío, la cantidad de elementos es 1.");

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_2, valor_2, NULL) != NULL,
		     "Se inserta correctamente el valor 2.");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_3, valor_3, NULL) != NULL,
		     "Se inserta correctamente el valor 3.");

	pa2m_afirmar(
		hash_cantidad(nuevo_hash) == 3,
		"Al insertar mas elemento en hash vacío, la cantidad de elementos es correcta.");

	pa2m_afirmar(hash_quitar(nuevo_hash, clave_1) != NULL,
		     "Se elimina correctamente el valor asociado a la clave 1");
	pa2m_afirmar(hash_quitar(nuevo_hash, clave_2) != NULL,
		     "Se elimina correctamente el valor asociado a la clave 2");

	pa2m_afirmar(
		hash_cantidad(nuevo_hash) == 1,
		"Al eliminar más de un elemento de un hash con varios elementos, la cantidad de elementos es correcta.");

	pa2m_afirmar(hash_quitar(nuevo_hash, clave_3) != NULL,
		     "Se elimina correctamente el valor asociado a la clave 3");

	hash_destruir(nuevo_hash);
}

void cuando_se_intenta_obtener_valor_en_hash_nulo_devuelve_null()
{
	pa2m_afirmar(
		hash_obtener(NULL, "juan") == NULL,
		"Devuelve NULL al intentar obtener un elemento con hash nulo.");
}

void cuando_se_intentan_obtener_valores_que_no_estan_en_el_hash_devuelve_null()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	pa2m_afirmar(
		hash_obtener(nuevo_hash, "Leticia") == NULL,
		"Devuelve NULL al intentar obtener un elemento inexistente.");
	pa2m_afirmar(
		hash_obtener(nuevo_hash, "Pamela") == NULL,
		"Devuelve NULL al intentar obtener un elemento inexistente.");

	hash_destruir(nuevo_hash);
}

void cuando_se_obtienen_los_valores_que_estan_en_el_hash_se_devuelven_los_valores()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);
	const char *clave_1 = "Juan";
	int valor_1 = 20;

	const char *clave_2 = "Gonzalo";
	int valor_2 = 30;

	const char *clave_3 = "Camila";
	int valor_3 = 25;

	const char *clave_4 = "Pepe";
	int valor_4 = 100;

	const char *clave_5 = "Tomas";
	int valor_5 = 10;

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, &valor_1, NULL) != NULL,
		     "Se inserta correctamente el valor asociado a la clave 1");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_2, &valor_2, NULL) != NULL,
		     "Se inserta correctamente el valor asociado a la clave 2");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_3, &valor_3, NULL) != NULL,
		     "Se inserta correctamente el valor asociado a la clave 3");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_4, &valor_4, NULL) != NULL,
		     "Se inserta correctamente el valor asociado a la clave 4");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_5, &valor_5, NULL) != NULL,
		     "Se inserta correctamente el valor asociado a la clave 5");

	pa2m_afirmar(hash_obtener(nuevo_hash, clave_1) == &valor_1,
		     "Obtiene el elemento correcto con la clave existente.");
	pa2m_afirmar(hash_obtener(nuevo_hash, clave_2) == &valor_2,
		     "Obtiene el elemento correcto con la clave existente.");
	pa2m_afirmar(hash_obtener(nuevo_hash, clave_3) == &valor_3,
		     "Obtiene el elemento correcto con la clave existente.");
	pa2m_afirmar(hash_obtener(nuevo_hash, clave_4) == &valor_4,
		     "Obtiene el elemento correcto con la clave existente.");
	pa2m_afirmar(hash_obtener(nuevo_hash, clave_5) == &valor_5,
		     "Obtiene el elemento correcto con la clave existente.");

	hash_destruir(nuevo_hash);
}

void cuando_se_itera_sobre_un_hash_vacio_nulo_o_funcion_nula_devuelve_cero_iteraciones()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	pa2m_afirmar(hash_con_cada_clave(nuevo_hash, imprimir_valor_par,
					 NULL) == 0,
		     "Iterar un hash vacío, devuelve 0 invocaciones.");
	pa2m_afirmar(hash_con_cada_clave(NULL, imprimir_valor_par, NULL) == 0,
		     "Iterar un hash no válido, devuelve 0 invocaciones.");
	pa2m_afirmar(
		hash_con_cada_clave(nuevo_hash, NULL, NULL) == 0,
		"Iterar un hash con función no válida, devuelve 0 invocaciones.");

	hash_destruir(nuevo_hash);
}

void cuando_se_itera_sobre_un_hash_con_una_funcion_sin_contexto_se_devuelve_la_cantidad_de_iteraciones()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "Juan";
	int valor_1 = 20;

	const char *clave_2 = "Gonzalo";
	int valor_2 = 30;

	const char *clave_3 = "Camila";
	int valor_3 = 12;

	const char *clave_4 = "Pepe";
	int valor_4 = 100;

	const char *clave_5 = "Tomas";
	int valor_5 = 10;

	const char *clave_6 = "Javier";
	int valor_6 = 80;

	const char *clave_7 = "Jorge";
	int valor_7 = 21;

	const char *clave_8 = "Julian";
	int valor_8 = 21;

	const char *clave_9 = "Melissa";
	int valor_9 = 43;

	hash_insertar(nuevo_hash, clave_1, &valor_1, NULL);
	hash_insertar(nuevo_hash, clave_2, &valor_2, NULL);
	hash_insertar(nuevo_hash, clave_3, &valor_3, NULL);
	hash_insertar(nuevo_hash, clave_4, &valor_4, NULL);
	hash_insertar(nuevo_hash, clave_5, &valor_5, NULL);
	hash_insertar(nuevo_hash, clave_6, &valor_6, NULL);
	hash_insertar(nuevo_hash, clave_7, &valor_7, NULL);
	hash_insertar(nuevo_hash, clave_8, &valor_8, NULL);
	hash_insertar(nuevo_hash, clave_9, &valor_9, NULL);
	pa2m_afirmar(true, "Imprime los pares hasta encontrar un valor impar:");
	pa2m_afirmar(
		hash_con_cada_clave(nuevo_hash, imprimir_valor_par, NULL) > 0,
		"Iterador no recorre todo el hash y aplica correctamente la función en cada iteración.");

	hash_destruir(nuevo_hash);
}

void cuando_se_itera_sobre_un_hash_con_una_funcion_con_contexto_se_devuelve_la_cantidad_de_iteraciones()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "Juan";
	int valor_1 = 20;

	const char *clave_2 = "Gonzalo";
	int valor_2 = 30;

	const char *clave_3 = "Camila";
	int valor_3 = 12;

	const char *clave_4 = "Pepe";
	int valor_4 = 100;

	const char *clave_5 = "Tomas";
	int valor_5 = 10;

	const char *clave_6 = "Javier";
	int valor_6 = 80;

	const char *clave_7 = "Jorge";
	int valor_7 = 21;

	const char *clave_8 = "Julian";
	int valor_8 = 21;

	const char *clave_9 = "Melissa";
	int valor_9 = 43;

	int sumando = 100;

	hash_insertar(nuevo_hash, clave_1, &valor_1, NULL);
	hash_insertar(nuevo_hash, clave_2, &valor_2, NULL);
	hash_insertar(nuevo_hash, clave_3, &valor_3, NULL);
	hash_insertar(nuevo_hash, clave_4, &valor_4, NULL);
	hash_insertar(nuevo_hash, clave_5, &valor_5, NULL);
	hash_insertar(nuevo_hash, clave_6, &valor_6, NULL);
	hash_insertar(nuevo_hash, clave_7, &valor_7, NULL);
	hash_insertar(nuevo_hash, clave_8, &valor_8, NULL);
	hash_insertar(nuevo_hash, clave_9, &valor_9, NULL);

	pa2m_afirmar(
		hash_con_cada_clave(nuevo_hash, sumar_a_valores, &sumando) > 0,
		"Iterador aplica la función con un auxiliar a todo el hash y devuelve cantidad acorde de invocaciones.");

	pa2m_afirmar(
		true,
		"Imprime los pares sumandole 100 a cada uno de sus valores:");
	hash_con_cada_clave(nuevo_hash, imprimir_valor, NULL);

	hash_destruir(nuevo_hash);
}

void cuando_se_invoca_hash_destruir_todo_sin_un_destructor_los_elementos_del_hash_son_destruidos_correctamente()
{
	hash_t *nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	const char *clave_1 = "Sol";
	int valor_1 = 220;

	const char *clave_2 = "Gonzalo";
	int valor_2 = 30;

	const char *clave_3 = "Camila";
	int valor_3 = 25;

	const char *clave_4 = "Pepe";
	int valor_4 = 100;

	const char *clave_5 = "Tomas";
	int valor_5 = 10;

	const char *clave_6 = "Javier";
	int valor_6 = 80;

	const char *clave_7 = "Jorge";
	int valor_7 = 20;

	const char *clave_8 = "Julian";
	int valor_8 = 21;

	const char *clave_9 = "Melissa";
	int valor_9 = 43;

	pa2m_afirmar(hash_insertar(nuevo_hash, clave_1, &valor_1, NULL) != NULL,
		     "Se inserta correctamente la clave 1");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_2, &valor_2, NULL) != NULL,
		     "Se inserta correctamente la clave 2");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_3, &valor_3, NULL) != NULL,
		     "Se inserta correctamente la clave 3");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_4, &valor_4, NULL) != NULL,
		     "Se inserta correctamente la clave 4");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_5, &valor_5, NULL) != NULL,
		     "Se inserta correctamente la clave 5");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_6, &valor_6, NULL) != NULL,
		     "Se inserta correctamente la clave 6");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_7, &valor_7, NULL) != NULL,
		     "Se inserta correctamente la clave 7");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_8, &valor_8, NULL) != NULL,
		     "Se inserta correctamente la clave 8");
	pa2m_afirmar(hash_insertar(nuevo_hash, clave_9, &valor_9, NULL) != NULL,
		     "Se inserta correctamente la clave 9");

	hash_destruir_todo(nuevo_hash, NULL);

	pa2m_afirmar(true,
		     "Hash y todos los pares fueron liberados correctamente.");
}

void cuando_se_invoca_hash_destruir_todo_con_un_destructor_los_elementos_son_destruidos_correctamente()
{
	hash_t *hash = hash_crear(CAPACIDAD_VALIDA);

	persona_t *juan = crear_persona("Juan", 30);
	if (!juan) {
		return;
	}

	persona_t *maria = crear_persona("Maria", 25);
	if (!maria) {
		free(juan);
		return;
	}

	pa2m_afirmar(
		hash_insertar(hash, "Juan", juan, NULL) != NULL,
		"Se inserta correctamente el valor asociado a la clave 'Juan'");
	pa2m_afirmar(
		hash_insertar(hash, "Maria", maria, NULL) != NULL,
		"Se inserta correctamente el valor asociado a la clave 'Maria'");

	hash_destruir_todo(hash, destructor);

	pa2m_afirmar(
		true,
		"Hash y todos los pares fueron liberados correctamente utilizando un destructor.");
}

int main()
{
	pa2m_nuevo_grupo("\n=== Creación de hash ===");
	cuando_se_crea_un_hash_con_capacidad_mayor_al_minimo_devuelve_un_hash_válido();
	cuando_se_crea_un_hash_con_capcidad_menor_al_minimo_devuelve_un_hash_valido();

	pa2m_nuevo_grupo("\n=== Inserción de elementos ===");
	cuando_se_intenta_insertar_con_algun_parametro_invalido_devuelve_null();
	cuando_se_insertan_pares_se_espera_que_el_elemento_este_en_el_hash();
	cuando_se_inserta_valor_nulo_devuelve_el_hash_correctamente();
	cuando_se_inserta_elemento_con_clave_repetida_devuelve_el_hash_correctamente();
	cuando_se_inserta_un_par_luego_de_insertar_varios_se_espera_que_el_par_este_en_el_hash();
	cuando_se_insertan_elementos_con_valores_nulos_se_insertan_correctamente();

	pa2m_nuevo_grupo("\n=== Eliminación de elementos ===");
	cuando_se_intenta_quitar_de_un_hash_no_válido_devuelve_null();
	cuando_se_intenta_quitar_de_un_hash_con_clave_nula_devuelve_null();
	cuando_se_van_quitando_varios_pares_en_el_hash_se_espera_que_no_se_encuentren_los_valores_en_el_hash();

	pa2m_nuevo_grupo(
		"\n=== Inserción y eliminación de muchos elementos ===");
	cuando_se_insertan_y_eliminan_muchos_valores_del_hash_se_espera_una_correcta_insercion_y_eliminacion();

	pa2m_nuevo_grupo("\n=== Contención de elementos ===");
	cuando_se_verifica_que_un_hash_no_valido_contenga_un_valor_devuelve_false();
	cuando_se_verifica_que_un_hash_contenga_un_valor_por_una_clave_invalida_devuelve_false();
	cuando_se_verifica_que_un_hash_contenga_un_valor_devuelve_true_sino_false();

	pa2m_nuevo_grupo("\n=== Cantidad de elementos ===");
	cuando_se_solicita_la_cantidad_de_pares_en_hash_vacio_devuelve_cero();
	cuando_se_solicita_la_cantidad_de_pares_de_hash_inválido_devuelve_cero();
	cuando_se_solicita_la_cantiadad_de_pares_con_inserciones_y_eliminaciones_pares_devuelve_la_cantidad_correcta();

	pa2m_nuevo_grupo("\n=== Obtención de elementos ===");
	cuando_se_intenta_obtener_valor_en_hash_nulo_devuelve_null();
	cuando_se_intentan_obtener_valores_que_no_estan_en_el_hash_devuelve_null();
	cuando_se_obtienen_los_valores_que_estan_en_el_hash_se_devuelven_los_valores();

	pa2m_nuevo_grupo("\n=== Iterar elementos ===");
	cuando_se_itera_sobre_un_hash_vacio_nulo_o_funcion_nula_devuelve_cero_iteraciones();
	cuando_se_itera_sobre_un_hash_con_una_funcion_sin_contexto_se_devuelve_la_cantidad_de_iteraciones();
	cuando_se_itera_sobre_un_hash_con_una_funcion_con_contexto_se_devuelve_la_cantidad_de_iteraciones();

	pa2m_nuevo_grupo("\n=== Destrucción de elementos ===");
	cuando_se_invoca_hash_destruir_todo_sin_un_destructor_los_elementos_del_hash_son_destruidos_correctamente();
	cuando_se_invoca_hash_destruir_todo_con_un_destructor_los_elementos_son_destruidos_correctamente();

	return pa2m_mostrar_reporte();
}
