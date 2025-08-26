#include "contador.h"

int main(void) {
	contador_init();

	while (1) {
		contador_incrementar();
		contador_mostrar();
	}
}
