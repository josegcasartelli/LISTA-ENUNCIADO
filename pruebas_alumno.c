#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

void prueba_lista_crear()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "La lista se creo correctamente");
	pa2m_afirmar(lista_vacia(lista) == true, "La lista esta vacia");
	pa2m_afirmar(lista_cantidad(lista) == 0, "La lista tiene 0 elementos");

	lista_destruir(lista);
}

void pruebas_lista_agregar_y_buscar()
{
	lista_t *lista = lista_crear();
	int a = 10, b = 20;
	pa2m_afirmar(lista_agregar(lista, &a) == true,
		     "Se agrego un elemento a la lista");
	lista_agregar(lista, &b);
	pa2m_afirmar(!lista_vacia(lista), "La lista no esta vacia");
	pa2m_afirmar(lista_cantidad(lista) == 2, "La lista tiene 2 elementos");

	pa2m_afirmar(lista_buscar_elemento(lista, 0) == &a,
		     "El primer elemento es correcto");
	pa2m_afirmar(lista_buscar_elemento(lista, 1) == &b,
		     "El segundo elemento es correcto");

	lista_destruir(lista);
}

void pruebas_lista_agregar_y_eliminar()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2, c = 3;

	lista_agregar(lista, &a);
	lista_agregar(lista, &c);
	lista_insertar(lista, &b, 1);

	pa2m_afirmar(*(int *)lista_buscar_elemento(lista, 1) == 2,
		     "Se inserto bien el elemento");

	void *eliminado = lista_eliminar_elemento(lista, 1);
	pa2m_afirmar(eliminado == &b, "Se elimino el elemento correcto");

	lista_destruir(lista);
}

void pruebas_lista_insertar_en_lista_vacia()
{
	lista_t *lista = lista_crear();
	int a = 1;

	bool insertado = lista_insertar(lista, &a, 0);
	pa2m_afirmar(!insertado, "No se puede insertar en una lista vacia");
	pa2m_afirmar(lista_cantidad(lista) == 0, "la lista esta vacia");
	pa2m_afirmar(lista_buscar_elemento(lista, 0) == NULL,
		     "No hay ningun elemento en la posicion 0");

	lista_destruir(lista);
}

void pruebas_lista_insertar_al_final()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;

	pa2m_afirmar(lista_agregar(lista, &a),
		     "agrego primer elemento con agregar");
	pa2m_afirmar(lista_insertar(lista, &b, 1), "Inserto al final");

	pa2m_afirmar(lista_cantidad(lista) == 2, "la lista tiene 2 elementos");
	pa2m_afirmar(lista_buscar_elemento(lista, 1) == &b,
		     "el elemento esta insertado correcctamente");

	lista_destruir(lista);
}

void pruebas_lista_insertar_al_principio()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2;
	lista_agregar(lista, &a);
	lista_insertar(lista, &b, 0);

	pa2m_afirmar(lista_cantidad(lista) == 2, "la lista tiene 2 elementos");
	pa2m_afirmar(lista_buscar_elemento(lista, 0) == &b,
		     "el nuevo primer elemento es correcto");
	pa2m_afirmar(lista_buscar_elemento(lista, 1) == &a,
		     "el viejo primer elemento ahora es el segundo");

	lista_destruir(lista);
}

void pruebas_orden_correcto_despues_de_varios_insertar()
{
	lista_t *lista = lista_crear();
	int a = 1, b = 2, c = 3, d = 4;

	lista_agregar(lista, &a);
	lista_insertar(lista, &b, 1);
	lista_insertar(lista, &c, 2);
	lista_insertar(lista, &d, 1);

	pa2m_afirmar(lista_cantidad(lista) == 4, "la lista tiene 4 elementos");
	pa2m_afirmar(lista_buscar_elemento(lista, 0) == &a,
		     "el nuevo primer elemento es correcto");
	pa2m_afirmar(lista_buscar_elemento(lista, 1) == &d,
		     "el nuevo segundo elemento es correcto");
	pa2m_afirmar(lista_buscar_elemento(lista, 2) == &b,
		     "el viejo segundo elemento ahora es el tercero");
	pa2m_afirmar(lista_buscar_elemento(lista, 3) == &c,
		     "el viejo tercer elemento ahora es el cuarto");

	lista_destruir(lista);
}

int comparar_enteros(const void *a, const void *b)
{
	int x = *(const int *)a;
	int y = *(const int *)b;

	if (x == y)
		return 0;
	return 1;
}

void pruebas_lista_buscar_posicion()
{
	lista_t *lista = lista_crear();
	int a = 10, b = 20, c = 30;
	lista_agregar(lista, &a);
	lista_agregar(lista, &b);
	lista_agregar(lista, &c);

	int posicion = lista_buscar_posicion(lista, &b, comparar_enteros);
	pa2m_afirmar(posicion == 1, "Se encontro la posicion del elemento");

	lista_destruir(lista);
}

bool sumar(void *elemento, void *extra)
{
	*(int *)extra += *(int *)elemento;
	return true;
}

void pruebas_lista_con_cada_elemento()
{
	lista_t *lista = lista_crear();
	int a = 10, b = 20, c = 30;
	int suma = 0;

	lista_agregar(lista, &a);
	lista_agregar(lista, &b);
	lista_agregar(lista, &c);

	lista_con_cada_elemento(lista, sumar, &suma);
	pa2m_afirmar(suma == 60, "Se aplico la funcion a cada elemento");

	lista_destruir(lista);
}

void pruebas_iterador_externo()
{
	lista_t *lista = lista_crear();
	int a = 10, b = 20, c = 30;

	lista_agregar(lista, &a);
	lista_agregar(lista, &b);
	lista_agregar(lista, &c);

	lista_iterador_t *it = lista_iterador_crear(lista);
	size_t contador = 0;

	while (lista_iterador_hay_mas_elementos(it)) {
		void *actual = lista_iterador_obtener_actual(it);
		if (actual)
			contador++;
		lista_iterador_siguiente(it);
	}

	pa2m_afirmar(contador == 3,
		     "Iterador externo recorre todos los elementos");

	lista_iterador_destruir(it);
	lista_destruir(lista);
}

void pruebas_de_pila()
{
	pila_t *pila = pila_crear();
	int a = 10, b = 20;

	pila_apilar(pila, &a);
	pila_apilar(pila, &b);

	pa2m_afirmar(pila_cantidad(pila) == 2, "La pila tiene 2 elementos");
	pa2m_afirmar(pila_ver_primero(pila) == &b,
		     "El tope de la pila es correcto");

	void *desapilado = pila_desapilar(pila);
	pa2m_afirmar(desapilado == &b, "Se desapilo correctamente el tope");
	pa2m_afirmar(pila_ver_primero(pila) == &a, "El nuevo tope es correcto");

	pila_destruir(pila);
}

void pruebas_de_cola()
{
	cola_t *cola = cola_crear();
	int a = 10, b = 20;

	cola_encolar(cola, &a);
	cola_encolar(cola, &b);

	pa2m_afirmar(cola_cantidad(cola) == 2, "La cola tiene 2 elementos");
	pa2m_afirmar(cola_ver_primero(cola) == &a,
		     "El primer elemento de la cola es correcto");

	void *desencolado = cola_desencolar(cola);
	pa2m_afirmar(desencolado == &a,
		     "Se desencolo correctamente el primer elemento");
	pa2m_afirmar(cola_ver_primero(cola) == &b,
		     "El nuevo primer elemento es correcto");

	cola_destruir(cola);
}

int main()
{
	pa2m_nuevo_grupo("============== LISTA ===============");
	prueba_lista_crear();
	pruebas_lista_agregar_y_buscar();
	pruebas_lista_agregar_y_eliminar();
	pruebas_lista_insertar_en_lista_vacia();
	pruebas_lista_insertar_al_principio();
	pruebas_lista_insertar_al_final();
	pruebas_orden_correcto_despues_de_varios_insertar();
	pruebas_lista_buscar_posicion();
	pruebas_lista_con_cada_elemento();
	pruebas_iterador_externo();

	pa2m_nuevo_grupo("============== PILA ===============");
	pruebas_de_pila();

	pa2m_nuevo_grupo("============== COLA ===============");
	pruebas_de_cola();

	return pa2m_mostrar_reporte();
}
