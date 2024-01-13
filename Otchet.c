#define _CRT_SECURE_NO_DEPRECATE
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int* strct(int*, int);
int* sort_shell(int*, int);
void sort_haor(int*, int, int);
void merger(int*, int, int);
void sort_merger(int*, int);
int compare(const void*, const void*);
double time_get(double);
double sr_znach(double exp[]);



int main() {

	setlocale(LC_ALL, "RUS");

	int choice = 0;
	int size;
	double t;
	printf("Введите количество элементов массива:");
	scanf("%d", &size);
	int* ptrarray;
	ptrarray = (int*)malloc(sizeof(int) * size);
	double exp[30];

	do {

		printf("Выберите сортировку для сравнения:\n");
		printf("1. Сортировка Шелла\n");
		printf("2. Быстрая Хаора\n");
		printf("3. Сортировка слиянием\n");
		printf("4. Сортировка qsort\n");
		scanf("%d", &choice);

		switch (choice) {
		case 1: 
			
			for (int i = 0; i < 30; i++) {
				free(ptrarray);
				ptrarray = (int*)malloc(size * sizeof(int));
				strct(ptrarray, size);
				t = clock();
				ptrarray = sort_shell(ptrarray, size);
				exp[i] = time_get(t);
			}
			printf("Время: %lg секунд\n", sr_znach(exp));

			break;
		case 2:

			for (int i = 0; i < 30; i++) {
				free(ptrarray);
				ptrarray = (int*)malloc(size * sizeof(int));
				strct(ptrarray, size);
				t = clock();
				sort_haor(ptrarray, 0, size - 1);
				exp[i] = time_get(t);
			}
			printf("Время: %lg секунд\n", sr_znach(exp));
			break;
		case 3:
		
			for (int i = 0; i < 30; i++) {
				free(ptrarray);
				ptrarray = (int*)malloc(size * sizeof(int));
				strct(ptrarray, size);
				t = clock();
				sort_merger(ptrarray, size);
				exp[i] = time_get(t);
			}
			printf("Время: %lg секунд\n", sr_znach(exp));

			break;
		case 4:

			for (int i = 0; i < 30; i++) {
				free(ptrarray);
				ptrarray = (int*)malloc(size * sizeof(int));
				strct(ptrarray, size);
				t = clock();
				qsort(ptrarray, size, sizeof(int), compare);
				exp[i] = time_get(t);
			}
			printf("Время: %lg секунд\n", sr_znach(exp));
			break;

		default:
			break;
		}
		
	} while (choice !=5);

}

int* strct(int* ptrarr, int size) {

	srand(time(NULL));
	for (int i = 0; i < size; i++) {

		ptrarr[i] = rand() % 1000;
	}
	return ptrarr;
}

int* sort_shell(int* ptrarr, int n) {

	int j, temp;

	for (int h = n / 2; h > 0; h /= 2) {
		for (int k = 0; k < h; k++) {
			for (int i = 0; i < n / h; i++) {
				j = i;
				while ((j > 0) && (ptrarr[j * h + k] < ptrarr[(j - 1) * h + k]))
				{
					temp = ptrarr[j * h + k];
					ptrarr[j * h + k] = ptrarr[(j - 1) * h + k];
					ptrarr[(j - 1) * h + k] = temp;
					j = j - 1;
				}
			}
		}
	}
	return ptrarr;

}

void sort_haor(int* ptrarr, int start, int end) {

	int i = start, j = end, x = ptrarr[(start + end) / 2];

	do {
		while (ptrarr[i] < x) i++;
		while (ptrarr[j] > x) j--;

		if (i <= j) {
			if (ptrarr[i] > ptrarr[j]) {
				int temp = ptrarr[i];
				ptrarr[i] = ptrarr[j];
				ptrarr[j] = temp;
			}
			i++;
			j--;
		}
	} while (i <= j);

	if (i < end)
		sort_haor(ptrarr, i, end);
	if (start < j)
		sort_haor(ptrarr, start, j);

}

void merger(int* ptrarr, int n, int m) {

	int i = 0, j = m;
	int* x = (int*)malloc(n * sizeof(int));
	for (int k = 0; k < n; k++) {
		if (j == n) {
			x[k] = ptrarr[i++];
		}
		else if (i == m) {
			x[k] = ptrarr[j++];
		}
		else if (ptrarr[j] < ptrarr[i]) {
			x[k] = ptrarr[j++];
		}
		else {
			x[k] = ptrarr[i++];
		}
	}
	for (i = 0; i < n; i++) {
		ptrarr[i] = x[i];
	}
	free(x);

}

void sort_merger(int* ptrarr, int n) {

	if (n < 2) return;
	int m = n / 2;
	sort_merger(ptrarr, m);
	sort_merger(ptrarr + m, n - m);
	merger(ptrarr, n, m);

}

int compare(const void* a, const void* b)
{
	int data1 = *(int*)a, data2 = *(int*)b;
	if (data1 < data2)
		return -1;
	else if (data1 == data2)
		return 0;
	else
		return 1;
}

double time_get(double t) {
	double time = (clock() - t) * 1. / CLOCKS_PER_SEC;
	return time;
}

double sr_znach(double exp[]) {
	double sum = 0;
	for (int i = 0; i < 30; i++) {
		sum += exp[i];
	}
	return sum / 30.;
}