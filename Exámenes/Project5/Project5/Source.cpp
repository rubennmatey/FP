#include <iostream>
using namespace std;
# define N 8
# define INT_MAX 65536
int V[N] = { 7 ,3 , 9 ,8 ,15 ,16 ,0 ,3 };
int W[N];


int main() {
	int max, index;
	for (int j = 0; j < N; j++) {
		max = 0;
		for (int i = 0; i < N; i++) {
			if (V[i] > max) {
				max = V[i];
				index = i;
			}
		}
		W[j] = V[index];
		V[index] = 0;
	}
	for (int z = 0; z < N; z++) {
		cout << W[z] << " " << endl;
	}
}
