#include "aux.h"
#include "tp1.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "src/lista.h"

bool buscar_nombre(void *elemento, void *extra)
{
	struct pokemon *p = elemento;
	char *nombre_buscado = extra;

	if (strcmp(p->nombre, nombre_buscado) == 0) {
		printf("Pokemon encontrado por nombre: ID=%d, Nombre=%s, Tipo=%d, Ataque=%d, Defensa=%d, Velocidad=%d\n",
		       p->id, p->nombre, p->tipo, p->ataque, p->defensa,
		       p->velocidad);
		return false;
	}

	return true;
}

bool buscar_id(void *elemento, void *extra)
{
	struct pokemon *p = elemento;
	int *id_buscado = extra;

	if (p->id == *id_buscado) {
		printf("Pokemon encontrado por Id: ID=%d, Nombre=%s, Tipo=%d, Ataque=%d, Defensa=%d, Velocidad=%d\n",
		       p->id, p->nombre, p->tipo, p->ataque, p->defensa,
		       p->velocidad);
		return false;
	}

	return true;
}

bool agregar_a_lista(struct pokemon *p, void *extra)
{
	lista_t *lista = extra;
	return lista_agregar(lista, p);
}