
#include <stdio.h>
#include <stdlib.h>

typedef struct Gauss {
	float value;
	char generaloIsmeretlen;
} Gauss;

typedef struct Pos {
	int row;
	int column;
} Pos;

Gauss** gauss(int m, int n, float matrix[][n]) {
	Gauss** matr = malloc(sizeof(float*) * m);

	for (int i = 0; i < m; i++) {
		matr[i] = malloc(sizeof(float*) * n);

		for (int j = 0; j < n; j++) {
			matr[i][j].generaloIsmeretlen = 0;
			matr[i][j].value = matrix[i][j];
		}
	}

	return matr;
}

char checkRow(Gauss** matrix, int m, int n, int row) { // 1: hasznalhato, 0: van mar megjelolt elem
	for (int i = 0; i < n-1; i++) {
		if (matrix[row][i].generaloIsmeretlen == 1) {
			return 0;
		}
	}

	return 1;
}

char checkColumn(Gauss** matrix, int m, int n, int column) { // 1: hasznalhato, 0: van mar megjelolt elem
	for (int i = 0; i < m; i++) {
		if (matrix[i][column].generaloIsmeretlen == 1) {
			return 0;
		}
	}

	return 1;
}

Pos* findGeneraloIsmeretlen(Gauss** matrix, int m, int n) { // elso lepes
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n - 1; j++) {
			if ((matrix[i][j].value != 0) && (checkColumn(matrix, m, n, j)) && (checkRow(matrix, m, n, i))) {
				Pos* pos = malloc(sizeof(Pos));
				pos->row = i;
				pos->column = j;
				return pos;
			}
		}
	}
	return NULL;
}

void matrixSorOsztas(Gauss** matrix, int m, int n, int row, float value) { // masodik lepes
	for (int i = 0; i < n; i++) {
		matrix[row][i].value /= value;
	}
}

void matrixSorKivonas(Gauss** matrix, int m, int n, int row, int genRow, float kivonasSzorzo) {
	for (int i = 0; i < n; i++) {
		matrix[row][i].value -= matrix[genRow][i].value * kivonasSzorzo;
	}
}

void generaloOszlopNullazasa(Gauss** matrix, int m, int n, int row, int column, float oldValue) {
	for (int i = 0; i < m; i++) {
		if (i != row) {
			float kivonasSzorzo = matrix[i][column].value / oldValue;
			matrixSorKivonas(matrix, m, n, i, row, kivonasSzorzo);
		}
	}
}

void printMatrix(Gauss** matrix, int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n-1; j++) {
			if (matrix[i][j].generaloIsmeretlen) {
				printf("[%f] ", matrix[i][j].value);
			} else {
				printf(" %f  ", matrix[i][j].value);
			}
		}
		printf("| %f\n", matrix[i][n-1].value);
	}
}

void JordanEliminate(Gauss** matrix, int m, int n) {
	// 1. lepes
	Pos* generaloIsmeretlen = findGeneraloIsmeretlen(matrix, m, n);

	if (generaloIsmeretlen == NULL) {
		printMatrix(matrix, m, n);
	} else {
		int genRow = generaloIsmeretlen->row;
		int genColumn = generaloIsmeretlen->column;
		free(generaloIsmeretlen);
		float oldValue = matrix[genRow][genColumn].value;

		// 3. lepes
		generaloOszlopNullazasa(matrix, m, n, genRow, genColumn, oldValue);
		// 2. lepes
		matrixSorOsztas(matrix, m, n, genRow, oldValue);
		matrix[genRow][genColumn].generaloIsmeretlen = 1;

		printMatrix(matrix, m, n);
		printf("\n\n");
		JordanEliminate(matrix, m, n);
	}
}

int main() {
	float matrix[3][5] = {
		{2,3,-1,2,-1},
		{1,4,-4,3,2},
		{4,1,5,0,1}
	};

	Gauss** matr = gauss(3, 5, matrix);
	JordanEliminate(matr, 3, 5);

	return 0;
}