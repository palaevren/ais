#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define POPULATION 10
#define	OFFSPRING 3



int points = 0;

typedef struct Location{
	float _X;
	float _Y;
	float _Z;
} Coordinate;

typedef struct Individual{
	double fitness;
	int* sequence;
	
}Indv;

typedef struct Rectangle{
	float min_x;
	float max_x;
	float min_y;
	float max_y;
	float min_z;
	float max_z;
}Obstacle;

FILE* inpF;
Coordinate* targets;
int COUNT;

void getInput(FILE* f, char* fileName);
void printCord(Coordinate* crdAr);
double calculateFitness(Indv* indv);
float euclidianDistance(Coordinate c1, Coordinate c2);
void randPerm(int *i, int n);
void printArr(int *arr, int len);
void swap(int *arr, int idx_a, int idx_b);
void shuffle(int *arr, int len, int times);
void quickSort(Indv *, int, int);
int partition(Indv *, int, int);
void printIndvFits(Indv *indv, int size);
void generateIndv(Indv *ind);

int main(int arg, char** argv ){
	int i;
	printf("Flight started...\n");
	getInput(inpF, "inp.txt");
	printCord(targets);
	Indv* indv = (Indv *) malloc(sizeof(Indv)*POPULATION);
	
	for(i=0; i<POPULATION; i++){
		//~ generateIndv(indv+i);
		(indv+i)->sequence = (int *) malloc(sizeof(int)*COUNT);
		randPerm((indv+i)->sequence, COUNT);
		(indv+i)->fitness = calculateFitness(indv+i);
	}
	printIndvFits(indv, POPULATION);
	//~ int idx;
	//~ indv.sequence = (int *) malloc(sizeof(int) * COUNT);
	//~ for (idx=0; idx<COUNT; idx++){
		//~ indv.sequence[idx] = idx;
	//~ }
	
	//indv->sequence = randPerm(COUNT);
	//calculateFitness(indv);
	//~ printf("fitness: %f\n", indv->fitness);
	
	//~ COUNT = 1;
	//~ Coordinate a = {0.4f, -0.2f, 0.5f};
	//~ Coordinate b = {0.7f, -0.6f, -0.7f};
	//~ printCord(&a);
	//~ printCord(&b);
	//~ printf("Distance: %f\n", euclidianDistance(a,b) );
	return 0;
}


void getInput(FILE* f, char* fileName){
	targets = (Coordinate*) malloc(sizeof(Coordinate));
	f = fopen(fileName, "r");
	Coordinate tmp;
	int i;
	for(i=0; fscanf(f, "%f", &(tmp._X)) != EOF; i++){
		fscanf(f, "%f", &(tmp._Y));
		fscanf(f, "%f", &(tmp._Z));
		targets = (Coordinate*) realloc(targets, (i+1)*sizeof(Coordinate));
		*(targets+i) = tmp;
	}
	COUNT = i;
	return;
}

void printCord(Coordinate *crdAr){
	printf("Number of coordinates: %d", COUNT);
	int i;
	for(i=0; i<COUNT; i++){
		printf("Coordinate %d, X: %f, Y: %f, Z: %f\n", i, targets[i]._X, targets[i]._Y, targets[i]._Z);
	}
}


double calculateFitness(Indv *indv){
	int i;
	double fitness = 0.0;
	int* seq = indv->sequence;
	for(i=0; i<COUNT; i++){
		fitness += (double) euclidianDistance(targets[seq[i]], targets[seq[(i+1)%COUNT]]);
	}
	//~ indv->fitness = fitness;
	return fitness;
}

float euclidianDistance(Coordinate c1, Coordinate c2){
	return sqrt(pow((sqrt(pow((c1._X-c2._X), 2) + pow((c1._Y-c2._Y), 2))), 2) + pow((c1._Z-c2._Z), 2));
}

void randPerm(int *r, int n) 
{	
	int i,j;
    //~ r = malloc(n * sizeof(int));
    for(j=0; j<n; j++){
		*(r+j) = j;
	}
	shuffle(r, n, n);
	printArr (r, n);
	return;
}

void printArr(int *arr, int len){
	int i;
	for(i=0; i< len; i++){
		printf("%d, ", arr[i]);
	}
	printf("\n");
	return;
}

void swap(int *arr, int idx_a, int idx_b){
	//~ printf("%dth element (%d) is to be swapped with %dth element (%d)\n", idx_a, *(arr+idx_a), idx_b, *(arr+idx_b));
	int tmp = *(arr+idx_a);
	*(arr+idx_a) = *(arr+idx_b);
	*(arr+idx_b) = tmp;
	
	//printf("%dth element (%d) is swapped with %dth element (%d)\n", idx_a, *(arr+idx_a), idx_b, *(arr+idx_b));
	return;
}

void shuffle(int *arr, int len, int times){
	int i;
	for(i=0; i<times; i++){
		srand(time(NULL));
		int index_1 = rand() % len;
		srand(time(NULL));
		int index_2 = rand() % len;
		while(index_2 == index_1){
			srand(time(NULL));
			index_2 = rand() % len;
		}
		 
		//printf("generated random pair : %d-%d\n", index_1, index_2);
		swap(arr, index_1, index_2);
	}
}

void quickSort( Indv *a, int l, int r)
{
   int j;

   if( l < r ) 
   {
   	// divide and conquer
		j = partition( a, l, r);
		quickSort( a, l, j-1);
		quickSort( a, j+1, r);
   }
	
}



int partition( Indv *a, int l, int r) {
	float pivot;
	int i, j;
	//~ int* t = (int*) malloc(sizeof(int));
	Indv* t = (Indv *) malloc(sizeof(Indv));
	pivot = (a+l)->fitness;
	i = l;
	j = r+1;
	
	while( 1){
		do ++i; while( (a+i)->fitness<= pivot && i <= r );
		do --j; while( (a+j)->fitness > pivot );
		if( i >= j ) break;
		*t = *(a+i);
		*(a+i) = *(a+j);
		*(a+j) = *t;
		
	}
	*t = *(a+l);
	*(a+l) = *(a+j);
	*(a+j) = *t;
	return j;
}

void generateIndv(Indv *ind){
	 randPerm(ind->sequence, COUNT);
	calculateFitness(ind);
} 

void printIndvFits(Indv *indv, int size){
	int i;
	for(i=0; i<size; i++){
		printf("addr=%p and fitness=%lf, permutation=", indv+i, (indv+i)->fitness);
		printArr((indv+i)->sequence, COUNT);
	}
}
