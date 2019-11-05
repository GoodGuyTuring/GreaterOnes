#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void arrayinit(int**pointer, int length, int modulo){
	
	int *new_array = malloc(length*sizeof(int));
	if(new_array == NULL){
		printf("Fehler beim Allokieren\n");
		return;
	}
	srand((unsigned)time(NULL));
	for(int i = 0;i<length;i++){
		new_array[i] = rand()%modulo;
	}
	
	(*pointer) = new_array;
}

void printArray(int *pointerArray,int length){
	if(pointerArray == NULL){
		printf("Array ist leer\n");
		return;
	}
	for(int i = 0;i<length;i++){
		printf("Wert %d: %d\n",i+1,*(pointerArray + i));
	}
	
}

void swap(int *pointerArray, int a, int b){
	int tmp = pointerArray[a];
	pointerArray[a] = pointerArray[b];
	pointerArray[b] = tmp;
}

int findminimum(int *array, int length, int pos){
	int min = pos;
	for(int i = pos;i<length;i++){
		if(array[i]<array[min]){
			min = i;
		}
	}
	return min;
}

void selectionSort(int *array, int length){
	
	clock_t start,end;
	start = clock();
	
	for(int i = 0;i<length;i++){
		int minimum = findminimum(array,length,i);
		swap(array,minimum,i);
	}
	
	end = clock();
	printf("\t%-40s%-10dms\t", "time needed for selectionSort:", (int)(1000.0f * (end-start)/CLOCKS_PER_SEC));
	printf("\n");
}

void insertionSort(int *array, int length){
	
	clock_t start,end;
	start = clock();
	
	int value = 0;
	for(int i = 1;i<length;i++){
		value = array[i];
		int j = 0;
		for(j = i;(j>0) && (array[j-1]>value);j--){
			array[j]=array[j-1];
		}
		array[j] = value;
	}
	
	end = clock();
	printf("\t%-40s%-10dms\t", "time needed for insertionSort:", (int)(1000.0f * (end-start)/CLOCKS_PER_SEC));
	printf("\n");
}

void bubbleSort(int *array, int length){
	
	clock_t start,end;
	start = clock();
	
	int i, tmp,marker = 0;
	while(length--){
		for(i = 0;i<length;i++){
			if(array[i]>array[i+1]){
				tmp = array[i];
				array[i] = array[i+1];
				array[i+1] = tmp;
				marker = 1;
			}
		}
		if(marker == 0){
			break;
		}
		marker = 0;
	}
	
	end = clock();
	printf("\t%-40s%-10dms\t", "time needed for bubbleSort:", (int)(1000.0f * (end-start)/CLOCKS_PER_SEC));
	printf("\n");
}

void quicksort(int *left, int *right){
	
	int pivot, tmp;
	pivot = *right;
	int *links = left;
	int *rechts = right;
	do{
		while(*left < pivot){
			left++;
		}
		while(*right > pivot){
			right--;
		}
		if(left > right){
			break;
		}
		tmp = *right;
		*right = *left;
		*left = tmp;
	}while(++left <= --right);
	if(links<right){
		quicksort(links,right);
	}
	if(left<rechts){
		quicksort(left,rechts);
	}
}

void mergeSort(int *array, int length){
	
	if(length > 1){
		int haelfte1[length/2];
		int haelfte2[(length+1)/2];
		int i;
		for(i = 0;i<length/2;i++){
			haelfte1[i] = array[i];
		}
		for(i=(length/2);i<length;i++){
			haelfte2[i-(length/2)] = array[i];
		}
		
		mergeSort(haelfte1,length/2);
		mergeSort(haelfte2,(length+1)/2);
		
		int *pos1 = &haelfte1[0];
		int *pos2 = &haelfte2[0];
		
		for(i = 0;i<length; i++){
			if(*pos1 <= *pos2){
				array[i] = *pos1;
				if(pos1 != &haelfte2[(length+1)/2-1]){
					if(pos1 == &haelfte1[length/2 -1]){
						pos1 = &haelfte2[(length+1)/2-1];
					}else{
						pos1++;
					}
				}
				
			}else{
				array[i] = *pos2;
				if(pos2 == &haelfte2[(length+1)/2-1]){
					pos2 = &haelfte1[(length/2 -1)];
				}else{
					pos2++;
				}
			}
		}
	}
}

int main(){
	
	
	int length[4] = {1000, 10000, 50000, 100000};
	
	for(int i = 0;i < 4;i++){
		printf("Größe des Arrays: %d\n",length[i]);
		int *parray;
		int *kopie = malloc(sizeof(int)*length[i]);
		arrayinit(&parray,length[i],1000000);
		
		memcpy(kopie, parray, length[i]*sizeof(int));
		selectionSort(kopie,length[i]);
		
		memcpy(kopie, parray, length[i]*sizeof(int));
		insertionSort(kopie,length[i]);
		
		memcpy(kopie, parray, length[i]*sizeof(int));
		bubbleSort(kopie, length[i]);
		
		memcpy(kopie, parray, length[i]*sizeof(int));
		clock_t start1, end1;
		start1=clock();
		quicksort(kopie,&kopie[length[i]-1]);
		
		end1 = clock();
		printf("\t%-40s%-10dms\t", "time needed for quickSort:", (int)(1000.0f * (end1-start1)/CLOCKS_PER_SEC));
		printf("\n");
		
		memcpy(kopie, parray, length[i]*sizeof(int));
		clock_t start,end;
		start = clock();
		mergeSort(kopie,length[i]);
		
		end = clock();
		printf("\t%-40s%-10dms\t", "time needed for mergeSort:", (int)(1000.0f * (end-start)/CLOCKS_PER_SEC));
		printf("\n");
		printf("\n");
		
		free(kopie);
		free(parray);
	}
	return 0;
}
