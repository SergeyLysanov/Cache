#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "deque.h"

#define TWICE(x) x x
#define ITERATORS 9999872
//#define ITERATORS 100000000

void shuffle2(int *array, size_t n) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int usec = tv.tv_usec;
    srand48(usec);


    if (n > 1) {
        size_t i;
        for (i = n - 1; i > 0; i--) {
            size_t j = (unsigned int) (drand48()*(i+1));
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int main(void) {

	struct timespec t1, t2;

	int nStep = 1;
	for (int nKb = 1; nKb <= 400; nKb += nStep)
	{
		SDeque* deq = create_deque();
		const int nBytesSize = nKb * 1024;//step(nKb * 1024);
		const int arr_size = nBytesSize / sizeof(void*);
		void** A = (void**)malloc(nBytesSize);

		int randoms[arr_size];

		for(int i=0; i < arr_size - 1; ++i){//[1..n]
			randoms[i] = i + 1;
		}
		shuffle2(randoms, arr_size - 1); //перемешиваем

		for(int i=0; i < arr_size - 1; ++i){
			push_front(deq, randoms[i]);
		}

		int next = pop_front(deq);
		A[0] = A + next;
		while(!isEmpty(deq))
		{
			int val = pop_front(deq);
			A[next] = A + val;
			//printf("%d to %d\n", next, val);
			next = val;
		}
		A[next] = A; //замыкаем

		void** c = A;
		clock_t t;
		clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &t1);
		t = clock();
		for(int j = 0; j < ITERATORS*8; j+=256) {
				TWICE(TWICE(TWICE(TWICE(TWICE(TWICE(TWICE(TWICE( c=(void**)*c; ))))))))
		}
		t = clock() - t;
		clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &t2);
		printf ("%f ",1000000000. * (((t2.tv_sec + t2.tv_nsec * 1.e-9) - (t1.tv_sec + t1.tv_nsec * 1.e-9))) / (ITERATORS*8));
		printf("Kb %d \n", nBytesSize/1024);
		//free(A);
		clear(deq);
		if(nKb > 64 && nStep == 1)
			nStep = 3;
		else if(nKb > 300 && nStep == 3)
			nStep = 50;
	}
	return EXIT_SUCCESS;
}
