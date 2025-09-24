#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"
#include "src/tp1.h"
#include <stdio.h>
#include "src/aux.h"

int main(int argc, char *argv[])
{
	if (argc != 5) {
		fprintf(stderr, "uso incorrecto");
		return 1;
	}

	const char *archivo = argv[1];
	const char *comando = argv[2];
	const char *tipo = argv[3];
	const char *valor = argv[4];

	if (strcmp(comando, "buscar") != 0) {
		fprintf(stderr, "comando incorrecto");
		return 1;
	}

	tp1_t *tp = tp1_leer_archivo(archivo);
	if (!tp) {
		fprintf(stderr, "error al leer el archivo");
		return 1;
	}

	lista_t *lista = lista_crear();
	if (!lista) {
		fprintf(stderr, "error al crear lista");
		tp1_destruir(tp);
		return 1;
	}

	tp1_con_cada_pokemon(tp, agregar_a_lista, lista);

	if (strcmp(tipo, "nombre") == 0) {
		size_t recorridos = lista_con_cada_elemento(
			lista, buscar_nombre, (void *)valor);
		if (recorridos == lista_cantidad(lista))
			printf("No se encontro el pokemon con nombre %s\n",
			       valor);
	} else if (strcmp(tipo, "id") == 0) {
		int id = atoi(valor);
		size_t recorridos =
			lista_con_cada_elemento(lista, buscar_id, &id);
		if (recorridos == lista_cantidad(lista))
			printf("No se encontro el pokemon con id %d\n", id);
	} else {
		fprintf(stderr, "tipo de busqueda incorrecta, use nombre o id");
	}

	lista_destruir(lista);
	tp1_destruir(tp);

	return 0;
}
