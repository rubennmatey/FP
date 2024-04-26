#include <iostream>
using namespace std;

const int N = 6;
const int M = 3;

int A[N] = { 1,2,3,4,5,6 };



int resto(const int a) {

	int resto = a;

	while (resto >= 2) {
		resto = resto - 2;

	}
	
	return resto;
}

void dividir(int A[], int B[], int C[]) {
	int restos = 0;
	int j = 0;
	int cont1 = 0;
	int cont2 = 0;
	while (cont1 < M && cont2 < M) {
		for (int i = 0; i < N; i++) {
			restos = resto(A[i]);
			if (restos == 0) {
				B[cont1] = A[i];
				cont1++;
			}
			else {
				C[cont2] = A[i];
				cont2++;
			}
		}
	}
}

int mul(int a, int b) {
	int mul = 0;
	while (b > 0) {
		mul += a;
		b--;
	}
	return mul;
}

int productoEscalar(int A[], int B[], int n) {
	int res = 0;
	for (int i = 0; i < n; i++) {
		res += mul(A[i], B[i]);
	}
	return res;
}
int  main() {
	int C[N];
	int B[N];
	int res = 0;

	dividir(A, B, C);

	for (int i = 0; i < M; i++) {
		cout << B[i] << " ";
	}
	cout << endl;
	for (int j = 0; j < M; j++) {
		cout << C[j] << " ";
	}
	cout << endl;


	cout << productoEscalar(B, C, M);

	return 0;
}