#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <memory.h>
#include <time.h>

void bubble_sort(int *arr, size_t arr_size);
void qsort_optimized(int *arr, size_t arr_size);
void qsort(int* arr, int left, int right);
void swap(int *el1, int *el2);
int partition(int* arr, int left, int right);
void heapsort(int* arr, int l, int size);
void fixDown(int* arr, int k, int size);
void mergesort(int *arr, size_t arr_size);
void shellsort(int* arr, int arr_size);
void insertionsort(int* arr, int arr_size, int order);


int main(int argc, char ** argv) {
	srand((unsigned int)time(NULL));
	int ARR_SIZE;
	printf("Enter a size of array:\n");
	scanf("%i", &ARR_SIZE);
	int* somearray = (int*)malloc(sizeof(int)*ARR_SIZE);
	for (size_t i = 0; i < ARR_SIZE; i++) {
		somearray[i] = rand() % 100;
	}
	int* somearray2 = (int*)malloc(sizeof(int)*ARR_SIZE);
	int* somearray3 = (int*)malloc(sizeof(int)*ARR_SIZE);
	int* somearray4 = (int*)malloc(sizeof(int)*ARR_SIZE);
	int* somearray5 = (int*)malloc(sizeof(int)*ARR_SIZE);
	int* somearray6 = (int*)malloc(sizeof(int)*ARR_SIZE);

	memcpy(somearray2, somearray, sizeof(somearray));
	memcpy(somearray3, somearray, sizeof(somearray));
	memcpy(somearray4, somearray, sizeof(somearray));
	memcpy(somearray5, somearray, sizeof(somearray));
	memcpy(somearray6, somearray, sizeof(somearray));
	int left = 0;

	double start = clock();
	bubble_sort(somearray,ARR_SIZE);
	printf("\n");
	printf("Bubble Sort - %.4lf sec.\n", (clock() - start / CLOCKS_PER_SEC) / 1000000);

	double start2 = clock();
	qsort(somearray2, left , ARR_SIZE-1);
	printf("\n");
	printf("QSort - %.4lf sec.\n", (clock() - start2 / CLOCKS_PER_SEC) / 1000000);

	double start7 = clock();
	qsort_optimized(somearray3, ARR_SIZE);
	printf("\n");
	printf("QSort Optimized - %.4lf sec.\n", (clock() - start7 / CLOCKS_PER_SEC) / 1000000);

	double start3 = clock();
	heapsort(somearray4, left, ARR_SIZE);
	printf("\n");
	printf("HeapSort - %.4lf sec.\n", (clock() - start3 / CLOCKS_PER_SEC) / 1000000);

	double start4 = clock();
	mergesort(somearray5, ARR_SIZE);
	printf("\n");
	printf("Merge Sort - %.4lf sec.\n", (clock() - start4 / CLOCKS_PER_SEC) / 1000000);


	double start5 = clock();
	shellsort(somearray6, ARR_SIZE);
	printf("\n");
	printf("Shell Sort - %.4lf sec.\n", (clock() - start5 / CLOCKS_PER_SEC) / 1000000);

	printf("\n");
	return 0;
}

void swap(int *el1, int *el2) {
	*el2 ^= *el1;
	*el1 ^= *el2;
	*el2 ^= *el1;
}

void qsort(int* arr, int left, int right){
	if (right <= left)
		return;
	int leg = partition(arr, left, right);
	qsort(arr, left, leg - 1);
	qsort(arr, leg + 1, right);
}

int partition(int* arr, int left, int right){
	int i = left-1;
	int j = right;
	int elem = arr[right];
	for (;;)
	{
		while (arr[++i] < elem);
		while (arr[--j] > elem) { if (j == left) break; }
		if (i >= j) break;
		swap(&arr[i], &arr[j]);	
	}
	swap(&arr[i], &arr[right]);
	return i;
}

void heapsort(int* arr, int l, int size){
	int k;
	int N = size;// -1 + 1;
	int* pq = arr + l - 1;
	for (k = N/2; k >= 1 ; k--)
	{
		fixDown(pq, k, N);
	}
	while (N > 1)
	{
		swap(&pq[1], &pq[N]);
		fixDown(pq, 1, --N);
	}
}

void fixDown(int* arr, int k, int size){
	while (2*k <= size)
	{
		int j = 2 * k;
		if ((j < size) && (arr[j] < arr[j + 1])) j++;
		if (!(arr[k] < arr[j])) break;
		swap(&arr[k], &arr[j]);
		k = j;
	}
}

void mergesort(int *arr, int arr_size) {
				int odin = 1;
				if (arr_size == odin)
					return;
				else {
					mergesort(arr, arr_size / 2);
					mergesort(arr + arr_size / 2, (arr_size - arr_size / 2));
					
				}
				int *arr2 = arr + arr_size / 2;
				int *buf = (int*)malloc(arr_size * sizeof(arr[0]));
				int i = 0, j = 0;
				for (; i < arr_size / 2 && j < (arr_size - arr_size / 2);){
					if (arr[i]< arr2[j]) {
						buf[i + j] = arr[i];
						i++;
						
					}
					else {
						buf[i + j] = arr2[j];
						j++;
					}
				}
				while (i < arr_size / 2)
					buf[i + j] = arr[i], i++;
				while (j < (arr_size - arr_size / 2))
					buf[i + j] = arr2[j], j++;
				memcpy(arr, buf, arr_size * sizeof(arr[0]));
			}


int ds[] = { 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597 };
void insertionsort(int *arr, int arr_size, int order){
	if (arr_size < order * 2) return;
	for (int i = order; i < arr_size; i += order) {
		for (int j = i; (j > 0) && (arr[j] < arr[j - order]); j -= order)
			swap(arr + j, arr + (j - order));
	}
}

void shellsort(int *arr, int arr_size){
	for (int i = 15; i >= 0; i--){
		for (int j = 0; j < arr_size && j < ds[i]; j++){
			insertionsort(arr + j, arr_size - j, ds[i]);
		}
	}
}

void qsort_optimized(int*arr, size_t arr_size) {
	do {
		if (arr_size <= 1)
			return;
		int central = arr_size / 2;

		int i = 0, j = arr_size;
		for (; i < j ;) {
			while ((arr[i] <= arr[central]) && (i < central)) i++;
			while ((arr[j] >= arr[central]) && (j > central)) j--;
			if (i < j){
				if (i == central)
					central = j;
				else if (j == central)
					central = i;
				swap(arr + i, arr + j);
				if (i < central)
					i++;
				if (j > central)
					j--;
			}
		}
		if (j < arr_size - i){
			if (j > 0)
				qsort(arr,0, j);
			arr = arr + i;
			arr_size -= i;
		}
		else {
			if (i < arr_size)
				qsort(arr + i,0,  arr_size - i);
			arr_size = j;
		}
	} while (arr_size > 1);
}

void bubble_sort(int *arr, size_t arr_size) {
	for (unsigned int i = 0; i < arr_size; i++){
		for (unsigned int j = i; j < arr_size; j++){
			if (arr[i] > arr[j])
			{
				arr[j] ^= arr[i];
				arr[i] ^= arr[j];
				arr[j] ^= arr[i];
			}
		}
	}
}