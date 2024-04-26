#include <iostream>

using namespace std;
const int  N = 4;
int A[N] = { 3 , 5, 1, 9 };
int B[N] = { 1 , 6, 2, 3 };
int dotprod(int V[], int W[], int n);
int mul(int a, int b);

int main() {


	int res = 0;
	int normA = dotprod(A, A, N);
	int normB = dotprod(B, B, N);
	cout << normA << endl;
	cout << normB << endl;

	if (normA > normB) {
		res = 0xa;
		
	}
	else {
		res = 0xb;
	}
	cout << res;
	return 0;
}
int dotprod(int V[], int W[], int n) {
	int acc = 0;
	for (int i = 0; i < n; i++) {
		acc += mul(V[i], W[i]);
	}
	return acc;
}
int mul(int a, int b) {
	int res = 0;
	while (b > 0) {
		res += a;
		b--;
	}
	return res;
}