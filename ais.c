#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

FILE* inpF;
Coordinate* targets;
int count;

void getInput(FILE* f, char* fileName);
void printCord(Coordinate* crdAr);
float calculateFitness(Indv* indv);
float euclidianDistance(Coordinate c1, Coordinate c2);

int main(int arg, char** argv ){
	printf("Flight started...\n");
	getInput(inpF, "inp.txt");
	printCord(targets);
	Indv indv;
	int idx;
	indv.sequence = (int *) malloc(sizeof(int) * count);
	for (idx=0; idx<count; idx++){
		indv.sequence[idx] = idx;
	}
	calculateFitness(&indv);
	printf("fitness: %f\n", indv.fitness);
	//~ count = 1;
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
		targets[i] = tmp;
	}
	count = i;
}

void printCord(Coordinate* crdAr){
	printf("Number of coordinates: %d", count);
	int i;
	for(i=0; i<count; i++){
		printf("Coordinate %d, X: %f, Y: %f, Z: %f\n", i, targets[i]._X, targets[i]._Y, targets[i]._Z);
	}
}


float calculateFitness(Indv* indv){
	int i;
	double fitness = 0.0;
	for(i=0; i<count; i++){
		fitness += (double) euclidianDistance(targets[i], targets[(i+1)%count]);
	}
	indv->fitness = fitness;
	return fitness;
}

float euclidianDistance(Coordinate c1, Coordinate c2){
	return sqrt(pow((sqrt(pow((c1._X-c2._X), 2) + pow((c1._Y-c2._Y), 2))), 2) + pow((c1._Z-c2._Z), 2));
}


