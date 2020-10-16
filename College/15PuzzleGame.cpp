#include <iostream>

void tabla(int(*numeros)[4], int tam) {				//Función: Dibuja la tabla
	std::cout << "\n\t  15 PUZZLE\n\t_____________" << std::endl;
	for (int(*p)[4] = numeros; p < numeros + tam; p++) {
		std::cout << "\t|";
		for (int *q = *p; q < (*p) + tam; q++) {
			if (*q == 0) {
				std::cout << "  |";			//El cero será el hueco movible
			}
			else if (*q < 10) {
				std::cout << " " << *q << "|";		//Para dar simetría a la tabla
			}
			else {
				std::cout << *q << "|";
			}
		}
		std::cout << std::endl;
	}

	return;
}

void movimiento(int (*numeros)[4],int movimiento) {
	//swap
	int tmp;
	for (int(*p)[4] = numeros; p < numeros + 4; p++) {
		for (int* q = *p; q < (*p) + 4; q++) {
			if (*q == 0) {	//Verifica donde está el hueco y lo mueve
				tmp = *q;
				*q = *(q + movimiento);
				*(q + movimiento) = tmp;
				p = numeros + 4; //break for de p
				break;	//break for de q
			}
		}

	}
}

int* posicionCero(int(*numeros)[4], int tam) {	//Halla la posicion del hueco para limitar movimientos
	int* posicion=nullptr;
	for (int(*p)[4] = numeros; p < numeros + tam; p++) {
		for (int* q = *p; q < (*p) + tam; q++) {
			if (*q == 0) {
				posicion = q;
				p = numeros + tam; //break del for de p 
				break;	//break de for de q

			}
		}
	}
	return posicion;
}

bool endGame(int(*numeros)[4], int tam) {	//Verifica si ya ganó
	bool play = true;
	int valorCorrecto=1; //Numero que debe estar en la casilla observada
	for (int (*p)[4] = numeros; p < numeros + tam; p++) {
		for (int *q = *p; q < (*p)+tam; q++) {
			if (*q == valorCorrecto) {
				play = false;
				valorCorrecto += 1;
				if (valorCorrecto == 16) {
					break;
				}
			} 
			else {		//Se encontró un número en posición errónea (No gana el juego)
				play = true;
				p = numeros + tam; //break
				break;
			}
			
		}

	}
	return play;
}
void game(int (*numeros)[4], int tam) { //Funcion donde se basa el juego
	char tecla; //Movimiento ingresado
	bool play = true;
	while (play) {
		tabla(numeros, tam); //Imprime tabla
		std::cout << "Move: ";
		std::cin >> tecla;

		int* cero = posicionCero(numeros, 4); //Ayuda establecer los límites de los movimientos

		//Opciones 
		if (tecla == 'a' && cero!=*numeros && cero!= *(numeros+1) && cero != *(numeros+2) && cero != *(numeros+3)){
			movimiento(numeros, -1);
		}
		else if (tecla == 'w' && cero >= *(numeros + 1)) {
			movimiento(numeros, -4);
		}
		else if (tecla == 'd' && cero != *numeros+3 && cero != *numeros + 7 && cero != *numeros + 11 && cero != *numeros +15) {
			movimiento(numeros, 1);
		}
		else if (tecla == 's' && cero < *(numeros + 3)) {
			movimiento(numeros, 4);
		}
		system("CLS");
		play=endGame(numeros, 4); //Verifica si ya ganó
	}
	
	tabla(numeros, tam);
	std::cout << "\n\t  GANASTE";
	return;
}

int main() {
	/*int numeros[4][4] = { {3,4,7,8},{0,9,1,2},{15,10,5,11},{6,13,12,14} }; //Mas dificil*/
	int numeros[4][4] = { {1,2,3,4},{5,6,0,8},{10,13,7,12},{9,14,11,15} };
	game(numeros, 4);
	return 0;
}