#include "pa2m.h"
#include "src/hash.h"
#include <string.h>

#define CAPACIDAD_VALIDA 8



//printf("Valor de '%s': %s\n", clave_5, (char*)hash_obtener(nuevo_hash, clave_5));

void creacion_de_hash() 
{
	hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	pa2m_afirmar(nuevo_hash != NULL, "Un hash con capacidad válida se crea correctamente");
	pa2m_afirmar(hash_cantidad(nuevo_hash) == 0, "Un hash vacío no tiene elementos.");

	hash_destruir(nuevo_hash);

	hash_t* otro_hash = hash_crear(0);
	pa2m_afirmar(otro_hash != NULL, "Al pasar capacidad 0, igualmente el hash se crea correctemente.");



	hash_destruir(otro_hash);
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

    const char* clave_4 = "hacer";
    char* valor_4 = "do";

    const char* clave_5 = "auto";
    char* valor_5 = "car";

    const char* clave_6 = "sol";
    char* valor_6 = "sun";

    const char* clave_7 = "take";
    char* valor_7 = "tomar";

    const char* clave_8 = "name";
    char* valor_8 = "nombre";

    const char* clave_9 = "casa";
    char* valor_9 = "house";



    hash_insertar(nuevo_hash, clave_1, valor_1, NULL); 
    pa2m_afirmar(hash_obtener(nuevo_hash, clave_1) == valor_1, "Inserta correctamente en un hash vacío.");

    hash_insertar(nuevo_hash, clave_2, valor_2, (void**)&valor_anterior_clave_1);

    pa2m_afirmar(strcmp(valor_anterior_clave_1, valor_1) == 0, "Obtenemos el anterior correctamente al insertar con clave repetida.");

    pa2m_afirmar(hash_cantidad(nuevo_hash) == 1, "Se mantiene la cantidad de pares al insertar con clave repetida.");

    hash_insertar(nuevo_hash, clave_3, valor_3, NULL);
    pa2m_afirmar(hash_insertar(nuevo_hash, clave_4, valor_4, NULL) == nuevo_hash, "Al detectar colisión, la resuelve e inserta correctamente el par.");

    hash_insertar(nuevo_hash, clave_5, valor_5, NULL);
    hash_insertar(nuevo_hash, clave_6, valor_6, NULL);
    hash_insertar(nuevo_hash, clave_7, valor_7, NULL);

    pa2m_afirmar(hash_insertar(nuevo_hash, clave_8, valor_8, NULL) != NULL, "Inserta correctamente un nuevo par, luego de insertar varios pares.");

    //podria eliminar un par luego;

    pa2m_afirmar(hash_insertar(NULL, clave_8, valor_8, NULL) == NULL, "Inserta en un hash inválido, devuelve NULL");
    pa2m_afirmar(hash_insertar(nuevo_hash, NULL, valor_2, NULL) == NULL, "Inserta con clave inválida, devuelve NULL");
    //pa2m_afirmar(hash_insertar(nuevo_hash, clave_2, NULL, NULL) != NULL, "Se puede insertar un valor NULL correctamente.");


    hash_insertar(nuevo_hash, clave_9, valor_9, NULL);
    hash_destruir(nuevo_hash);
}


void hash_contiene_verifica_que_este_el_valor_por_su_clave() {

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
    hash_insertar(nuevo_hash, clave_2, &valor_2, NULL);
    hash_insertar(nuevo_hash, clave_3, &valor_3, NULL);
    hash_insertar(nuevo_hash, clave_4, &valor_4, NULL);
    hash_insertar(nuevo_hash, clave_5, &valor_5, NULL);
    hash_insertar(nuevo_hash, clave_6, &valor_6, NULL);
    hash_insertar(nuevo_hash, clave_7, &valor_7, NULL);
    hash_insertar(nuevo_hash, clave_8, &valor_8, NULL);
    hash_insertar(nuevo_hash, clave_9, &valor_9, NULL);

    pa2m_afirmar(hash_contiene(NULL, clave_1) == false, "Un hash no válido no contiene nada.");
    pa2m_afirmar(hash_contiene(nuevo_hash, NULL) == false, "Buscar con clave inválida, devuelve FALSE.");

    pa2m_afirmar(hash_contiene(nuevo_hash, clave_1) == true, "Al contener la clave buscada, devuelve TRUE.");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_2) == true, "Al contener la clave buscada, devuelve TRUE.");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_3) == true, "Al contener la clave buscada, devuelve TRUE.");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_4) == true, "Al contener la clave buscada, devuelve TRUE.");
    pa2m_afirmar(hash_contiene(nuevo_hash, clave_6) == true, "Al contener la clave buscada, devuelve TRUE.");

    pa2m_afirmar(hash_contiene(nuevo_hash, "auto") == false, "Al no contener la clave buscada, devuelve FALSE.");

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
    hash_insertar(nuevo_hash, clave_2, &valor_2, NULL);
    hash_insertar(nuevo_hash, clave_3, &valor_3, NULL);
    hash_insertar(nuevo_hash, clave_4, &valor_4, NULL);
    hash_insertar(nuevo_hash, clave_5, &valor_5, NULL);
    hash_insertar(nuevo_hash, clave_6, &valor_6, NULL);
    hash_insertar(nuevo_hash, clave_7, &valor_7, NULL);
    hash_insertar(nuevo_hash, clave_8, &valor_8, NULL);
    hash_insertar(nuevo_hash, clave_9, &valor_9, NULL);


    


    hash_quitar(nuevo_hash, clave_1);

    pa2m_afirmar(hash_contiene(nuevo_hash, clave_9) == true, "encuentra la que le seguia a la que elimine?");


    hash_destruir(nuevo_hash);    
}



int main()
{
	pa2m_nuevo_grupo("\n===Creación de hash===");
	creacion_de_hash();

	pa2m_nuevo_grupo("\n===Inserción en hash===");
	insertar_elementos_en_el_hash();


    pa2m_nuevo_grupo("\n===Contención de valores en hash===");
	hash_contiene_verifica_que_este_el_valor_por_su_clave();



    pa2m_nuevo_grupo("\n===Quitar valores del hash===");
    hash_quitar_quita_valor_y_clave_del_hash();

	return pa2m_mostrar_reporte();
}
