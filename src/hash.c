#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "hash.h"

#define FACTOR_CARGA_MAXIMA 0.7
#define CAPACIDAD_MIN 3

typedef enum { VACIO, OCUPADO, ELIMINADO } estado;
struct par {
	char* clave;
	void* valor;
	int estado;
};

struct hash {
	size_t capacidad;
	struct par* pares;
	size_t cantidad_elementos;
};


hash_t *hash_crear(size_t capacidad)
{    
	hash_t* hash = malloc(sizeof(hash_t));
	if (!hash) {
		return NULL;
	}

	if (capacidad < CAPACIDAD_MIN) {
		hash->capacidad = CAPACIDAD_MIN;
	}

	hash->capacidad = capacidad;
	hash->cantidad_elementos = 0;

	hash->pares = malloc(sizeof(struct par) * hash->capacidad);
	if (!hash->pares) {
		free(hash);
		return NULL;
	}	

	return hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	return NULL;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	return hash->cantidad_elementos;
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *)) {
    if (!hash) {
        return;
    }
	//FALTA HACER FREE DE MAS COSAS
    free(hash->pares);
    free(hash);
}



void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	return 0;
}
