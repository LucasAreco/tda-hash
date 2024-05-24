#include "pa2m.h"
#include "src/hash.h"

#define CAPACIDAD_VALIDA 5

void creacion_de_hash() 
{
	hash_t* nuevo_hash = hash_crear(CAPACIDAD_VALIDA);

	pa2m_afirmar(nuevo_hash != NULL, "Un hash válido se crea correctamente");
	pa2m_afirmar(hash_cantidad(nuevo_hash) == 0, "Un hash vacío no tiene elementos.");

	hash_destruir(nuevo_hash);

	hash_t* otro_hash = hash_crear(0);
	pa2m_afirmar(otro_hash != NULL, "Al pasar capacidad 0, el hash se crea correctemente.");


	hash_destruir(otro_hash);
}

int main()
{
	pa2m_nuevo_grupo("\n======================== Creación de hash ========================");
	creacion_de_hash();

	return pa2m_mostrar_reporte();
}
