#include <iostream>
#include "math.h"

int numeros[2][100];
int bits;

void convertirNumero(int num, int pos, int bits) {
	int multiplo = 2;
	bool noSobrecarga = true;
	if (num >= 0) {
		numeros[pos][0] = 0;
		if (num >= pow(multiplo, bits - 1)) {
			std::cout << "Hay sobrecarga ingrese de nuevo\n";
			noSobrecarga = false;
		}
	}
	else if (num < 0) {
		numeros[pos][0] = 1;
		int msb = pow(multiplo, bits - 1);
		num = msb + num;
		if (num < 0) {
			std::cout << "Hay sobrecarga, ingrese de nuevo\n";
			noSobrecarga = false;
		}
	}

	if (noSobrecarga) {
		for (int i = 1; i < bits; i++) {
			int j = bits - (i + 1);
			int value = pow(multiplo, j);
			if (num >= value) {
				num -= value;
				numeros[pos][i] = 1;
			}
			else {
				numeros[pos][i] = 0;
			}
			if (num == 0) {
				break;
			}
		}
	}
}


int convertirBinarios(int* A, int* Q) {
	int tam = bits * 2;
	int MSB = -1*(A[0] * pow(2,tam-1));
	int sum = 0;
	int result = 0;

	for (int i = 1; i < bits; i++) {
		sum += A[i] * (pow(2, tam - 1 - i));
	}
	for (int i = 0; i < bits; i++) {
		sum += Q[i] * (pow(2, bits - 1 - i));
	}
	result = MSB + sum;


	return result;
}

void suma(int* A, int *M, int bits) {
	int carry = 0;
	int sum=0;
	for (int i = 0; i < bits; i++) {
		sum = A[bits - 1 - i] + M[bits - 1 - i]+carry;
		if (sum == 1) {
			A[bits - 1 - i] = 1;
			carry = 0;
		}
		else if (sum == 2) {
			A[bits - 1 - i] = 0;
			carry = 1;
		}
		else if (sum == 3) {
			A[bits - 1 - i] = 1;
			carry = 1;
		}
		else {
			A[bits - 1 - i] = 0;
			carry = 0;
		}
	}

}
void resta(int* A, int* M, int bits) {
	//Voltear 
	int carry = 1;
	int Minversa[100];
	for (int i = 0; i < bits; i++) {
		if (M[i] == 0) {
			Minversa[i] = 1;
		}
		else {
			Minversa[i] = 0;
		}
	}

	for (int i = 0; i < bits; i++) {
		int sum = Minversa[bits-1-i] + carry;
		if (sum == 1) {
			Minversa[bits - 1 - i] = 1;
			carry = 0;
		}
		else if (sum == 0) {
			Minversa[bits - 1 - i] = 0;
			carry = 0;
		}
		else {
			Minversa[bits - 1 - i] = 0;
			carry = 1;
		}
	}
	suma(A, Minversa, bits);
}

void shift(int *A, int *Q, int &q, int bits) {
	int cambio = A[bits-1];
	q = Q[bits - 1];
	for (int i = 0; i < bits-1; i++) {
		A[bits-1-i] = A[bits-2-i];
		Q[bits-1-i] = Q[bits-2-i];	
	}
	Q[0] = cambio;
}

void imprimir2(int *A, int *Q, int *M,int q, int bits) {
	for (int i = 0; i < bits; i++) {
		std::cout << A[i] << " ";
	}
	std::cout << " ";
	for (int i = 0; i < bits; i++) {
		std::cout << Q[i] << " ";
	}
	std::cout << " " << q << "  ";

	for (int i = 0; i < bits; i++) {
		std::cout << M[i] << " ";
	}
	
}
void multiplicación(int bits) {
	int A[100];
	int Q[100];
	int M[100];
	int q=0;
	int veces = bits;
	for (int i = 0; i < bits; i++) {
		A[i] = 0;
		Q[i] = numeros[0][i];
		M[i] = numeros[1][i];
	}

	imprimir2(A, Q, M, q, bits);
	std::cout << std::endl << std::endl;

	while (veces > 0) {
		if (Q[bits - 1] == 1 && q == 0) {
			resta(A, M, bits);
			imprimir2(A, Q, M, q, bits);
			std::cout << "A-M (Resta)" << std::endl;
		}
		else if (Q[bits - 1] == 0 && q == 1) {
			suma(A, M, bits);
			imprimir2(A, Q, M, q, bits);
			std::cout << "A+M (suma)" << std::endl;
		}
		shift(A, Q, q, bits);
		imprimir2(A, Q, M, q, bits);
		std::cout << "shift\n" << std::endl;
		veces--;
	}
	
	//Imprimir Resultado
	std::cout << "Resultado: ";
	for (int i = 0; i < bits; i++) {
		std::cout << A[i] << " ";
	}
	for (int i = 0; i < bits; i++) {
		std::cout << Q[i] << " ";
	}
	std::cout << "= " << convertirBinarios(A, Q);
}

void imprimir(int bits) {
	std::cout << "\nMultiplicando(Q): ";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < bits ; j++) {
			std::cout << numeros[i][j] << " ";
		}
		std::cout << std::endl;
		if(i==0) std::cout << "Multiplicador(M): ";
	}
	std::cout << std::endl;
}

void pedirNumeros() {
	int a, b;
	std::cout << "\nIngrese la cantidad de bits: ";
	std::cin >> bits;
	std::cout << "\nIngrese el primer numero: ";
	std::cin >> a;
	std::cout << "\nIngrese el segundo numero: ";
	std::cin >> b;

	convertirNumero(a,0, bits);
	convertirNumero(b,1, bits);
	imprimir(bits);
	multiplicación(bits);
}

int main() {
	pedirNumeros();
	return 0;
}