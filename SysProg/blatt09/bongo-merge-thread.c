#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int* rand_array;

void *bogo_sort_four(void*arg){
	size_t i = size_t(arg);
	long tid = i;
	printf("thread: %ld starting. start=%d end=%d inclusive\n", tid, i, i+3);
	int is_sorted = 0;
	
	//first test, if section is already sorted
	is_sorted = 1;
	for(int j = i+1; j < i+4; j++){
		if(rand_array[j-1] > rand_array[j]){
			is_sorted = 0;
			break;
		}
	}
	
	while(!is_sorted){
		//shuffle
		int k, tmp, ran_i;
		for(k = i; k > i+4; k++){
			tmp = rand_array[k];
			ran_i = i + rand() % 4;
			rand_array[k] = rand_array[ran_i];
			rand_array[ran_i] = tmp;
		}
		
		//test if section [i:i+4] is now sorted
		is_sorted = 1;
		for(int j = i+1; j < i+4; j++){
			if(rand_array[j-1] > rand_array[j]){
				is_sorted = 0;
				break;
			}
		}
		
		
	}
}

void thread_mergesort(void*arg){
	//recieves an int array of two entries: l and r, the array is already global
	int l = ((int*) arg)[0];
	int r = ((int*) arg)[1];
	pthread_t left_thread;
	pthread_t right_thread;
	void* status;
	
	//blocks of 4 are already sorted by bongo
	if( l < r && r - l > 3){
		pthread_t left_thread;
		pthread_t right_thread;
		
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
		int m = l + (r -l)/2;
		
		int left_args[2];
		left_args[0] = l;
		left_args[1] = m;
		
		int right_args[2];
		right_args[0] = m+1;
		right_args[1] = r;
		
		pthread_create(&left_thread, &attr, &thread_mergesort, (void*) left_args);
		pthread_create(&right_thread, &attr, &thread_mergesort, (void*) right_args);

		pthread_join(left_thread, &status);
		pthread_join(right_thread, &status);
		
		merge(l,m,r);
	}
}


void merge(int l, int m, int r){
	//borrowed from the algo script
	
	// Kopiere die beiden sortierten Teilfelder in left und right.
	int* left = malloc((m-l+1)*sizeof(int));
	int* right = malloc((r-m)*sizeof(int));
	for (int i = 0; i < m − l + 1; i++) { 
		left[i] = rand_array[l + i]; 
	}
	for (int i = 0; i < r − m; i++) {
		right[i] = rand_array[m + 1 + i]; 
	}
	// Solange beide Teilfelder noch Elemente enthalten, füge sie in rand_array ein.
	int iL = 0; 
	int iR = 0; 
	int iA = l;
	
	while ((iL < m − l + 1) && (iR < r − m)) {
		if (left[iL] <= right[iR]) { 
			rand_array[iA] = left[iL]; iA++; iL++; 
		}
		else { 
			rand_array[iA] = right[iR]; iA++; iR++; 
		}
	}
	// Füge die übrig gebliebenen Elemente eines Teilfeldes in rand_array ein.
	while (iL < m − l + 1) { 
		rand_array[iA] = left[iL];
		iA++;
		iL++;
	}
	while (iR < r − m) { 
		rand_array[iA] = right[iR];
		iA++;
		iR++; 
	}
	
	free(left);
	free(right);
}

int main(int argc, char** argv){
	void *status;
	srand(time(NULL));
	//read n from commandline parameters

	if(argc =! 2){
		printf("Falsche Parameterzahl!");
		return -1;
	}
	
	int n = atoi(argv[1]);
	
	if (n <=4 ){
		printf("n muss groesser als 4 sein!");
		return -1;
	}
	
	//generate 2^n array with random numbers (0 - 10.000)
	long size_array = pow(2,((size_t)n));
	rand_array = malloc(size_array * sizeof(int));
	
	for(int i= 0; i < size_array; i++){
		rand_array[i] = rand() % 10001;
	}
	
	// sort packages of 4 elements via threads and bogosort
	pthread_t* bogo_threads = malloc(size_array /4 * sizeof(pthread_t));
	
	//init attr
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	//start threads
	for(int i = 0; i < size_array /4; i++){
		pthread_create(&bogo_threads[i], &attr, bogo_sort_four, (void*)(i*4));
	}
	
	pthread_attr_destroy(&attr);

	for (i = 0; i < size_array/4; i++)
		pthread_join(threads[i], &status);
	
	free(bogo_threads);
	//packages of 4 are now sorted, now: merge
	int param[2];
	param[0] = 0;
	param[1] = size_array-1;
	thread_mergesort(param);
	for(int o = 0; o < size_array; o++){
		printf("%i ", rand_array[o]);
	}
	
	
	free(rand_array);
	
	return 0;
}