#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "hash.h"

#define FACTOR_CARGA_MAXIMA 0.7
#define CAPACIDAD_MIN 3

struct par {
	char* clave;
	void* valor;
};

struct hash {
	size_t capacidad;
	struct par* pares;
	size_t cantidad_elementos;
};


size_t djb2(void *data) {
	const unsigned char *str = data;
	size_t hash = 5381;
	int c;

	while ((c = *(str++))) {
		hash = ((hash << 5) + hash) + (size_t)c;
	}

	return hash;
	
}

struct par* obtener_par(hash_t* hash, const char *clave) {
    size_t posicion = djb2((void*)clave) % hash->capacidad;
    int posiciones_visitadas = 0;

    while (hash->pares[posicion].clave != NULL && posiciones_visitadas < hash->capacidad) {
        if (strcmp(hash->pares[posicion].clave, clave) == 0) {
            return &(hash->pares[posicion]);
        }
        posicion = (posicion + 1) % hash->capacidad;
        posiciones_visitadas++;
    }

    return NULL;
}



//revisar nombres
char* copiar_clave(const char* clave) {
    size_t len = strlen(clave) + 1; 
    char *copy = malloc(len);  
    if (copy == NULL) {
        return NULL;           
    }
    memcpy(copy, clave, len);        
    return copy;
}






hash_t *hash_crear(size_t capacidad)
{    
	hash_t* hash = calloc(1, sizeof(hash_t));
	if (!hash) {
		return NULL;
	}

	if (capacidad < CAPACIDAD_MIN) {
		hash->capacidad = CAPACIDAD_MIN;
	}

	hash->capacidad = capacidad;
	hash->cantidad_elementos = 0;

	hash->pares = calloc(hash->capacidad, sizeof(struct par));
	if (!hash->pares) {
		free(hash);
		return NULL;
	}	

	return hash;
}





hash_t* rehash(hash_t* hash) {
    size_t capacidad_anterior = hash->capacidad;
    size_t nueva_capacidad = capacidad_anterior * 2;

    struct par* nuevos_pares = calloc(nueva_capacidad, sizeof(struct par));
    if (!nuevos_pares) {
        return NULL;
    }

    hash_t hash_aux = {
        .capacidad = nueva_capacidad,
        .pares = nuevos_pares,
        .cantidad_elementos = 0,
    };

    for (size_t i = 0; i < capacidad_anterior; i++) {
        if (hash->pares[i].clave != NULL) {
            hash_insertar(&hash_aux, hash->pares[i].clave, hash->pares[i].valor, NULL);
            free((void*)hash->pares[i].clave); 
        }
    } 

    free(hash->pares);

    hash->capacidad = nueva_capacidad;
    hash->pares = nuevos_pares;
    hash->cantidad_elementos = hash_aux.cantidad_elementos;

    return hash;
}



hash_t* hash_insertar(hash_t *hash, const char *clave, void *elemento, void **anterior) {   
    if (!hash || !clave) {
        return NULL;
    }


    float factor_de_carga = (float)hash->cantidad_elementos / (float)hash->capacidad; 
    if (factor_de_carga >= FACTOR_CARGA_MAXIMA) {
        if (!rehash(hash)) {
            return NULL;
        }

    }

    struct par* par = obtener_par(hash, clave);
    if (par) {
        if (anterior) {
            *anterior = par->valor;
        } 
        par->valor = elemento;
        return hash;
    }


    size_t posicion = djb2((void*)clave) % hash->capacidad;

    while (hash->pares[posicion].clave != NULL) {
        posicion = (posicion + 1) % hash->capacidad;
    }

    hash->pares[posicion].clave = copiar_clave(clave);
    if (hash->pares[posicion].clave == NULL) {
        return NULL; 
    }
    hash->pares[posicion].valor = elemento;

    hash->cantidad_elementos++;

    if (anterior) {
        *anterior = NULL;
    }


    return hash;
}

void reemplazar_al_quitar(hash_t *hash, size_t posicion) {
    size_t actual = (posicion + 1) % hash->capacidad;
    int posiciones_visitadas = 0;

    while (hash->pares[actual].clave != NULL && posiciones_visitadas < hash->capacidad) {
        size_t nueva_posicion = djb2(hash->pares[actual].clave) % hash->capacidad;
        if (nueva_posicion <= posicion) {
            hash->pares[posicion].clave = copiar_clave(hash->pares[actual].clave);
            if (hash->pares[posicion].clave == NULL) {
                return;
            }
            hash->pares[posicion].valor = hash->pares[actual].valor;

            free((void *)hash->pares[actual].clave);
            hash->pares[actual].clave = NULL;
            hash->pares[actual].valor = NULL;

            posicion = actual;
        }

        actual = (actual + 1) % hash->capacidad;
        posiciones_visitadas++;
    }
}


void *hash_quitar(hash_t *hash, const char *clave) {   
    if (!hash || !clave) {
        return NULL;
    }

    size_t posicion_quitar = djb2((void*)clave) % hash->capacidad;

    while (hash->pares[posicion_quitar].clave != NULL) {
        if (strcmp(hash->pares[posicion_quitar].clave, clave) == 0) {
            void *valor_eliminado = hash->pares[posicion_quitar].valor;
            
            char *clave_eliminada = hash->pares[posicion_quitar].clave;

            hash->pares[posicion_quitar].clave = NULL;
            hash->pares[posicion_quitar].valor = NULL;

            reemplazar_al_quitar(hash, posicion_quitar);

            hash->cantidad_elementos--;

            free(clave_eliminada);

            return valor_eliminado;
        }
        posicion_quitar = (posicion_quitar + 1) % hash->capacidad;
    }

    return NULL;
}



void* hash_obtener(hash_t* hash, const char* clave) {
    if (!hash || !clave) {
        return NULL;
    }

    size_t posicion = djb2((void*)clave) % hash->capacidad;
    int posiciones_visitadas = 0;

    while (hash->pares[posicion].clave != NULL && posiciones_visitadas < hash->capacidad) {
        if (strcmp(hash->pares[posicion].clave, clave) == 0) {
            return hash->pares[posicion].valor;
        }
        posicion = (posicion + 1) % hash->capacidad;
        posiciones_visitadas++;
    }

    return NULL;
}



bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave) {
		return false;
	}

	if (hash_obtener(hash, clave)) {
		return true;
	}

	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash) {
		return 0;
	}
	return hash->cantidad_elementos;
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *)) {
    if (!hash) {
        return;
    }
	for (size_t i = 0; i < hash->capacidad; i++) {
		if (hash->pares[i].clave != NULL) {
			free(hash->pares[i].clave);
			if (destructor) {
				destructor(hash->pares[i].valor);
			}
		}
	}
    free(hash->pares);
    free(hash);
}



void hash_destruir(hash_t *hash)
{   
//  for (size_t i = 0; i < hash->capacidad; i++) {
//         if (hash->pares[i].clave != NULL) {
//             // char* valor = (char *)(hash->pares[i].valor);
//             // printf("Posición: %zu, Clave: %s, Valor: %s\n", i, hash->pares[i].clave, valor);
//             int valor = *(int*)(hash->pares[i].valor);
//             printf("Posición: %zu, Clave: %s, Valor: %d\n", i, hash->pares[i].clave, valor);
//         }
//     }
	hash_destruir_todo(hash, NULL);
}

size_t hash_con_cada_clave(hash_t *hash, bool (*f)(const char *clave, void *valor, void *aux), void *aux)
{

    if (!hash || !f) {
        return 0;
    } 


    size_t iteraciones = 0;

    for (size_t i = 0; i < hash->capacidad; i++) {
        if (hash->pares[i].clave) {
            bool funcion = f(hash->pares[i].clave, hash->pares[i].valor, aux);
            iteraciones++;


            if (!funcion) {
                return iteraciones;
            }

        }
    }

	return iteraciones;
}
