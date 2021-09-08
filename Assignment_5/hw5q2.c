
#include <stdio.h>
#include <stdbool.h>

#define N 4
#define EMPTY_CELL -1

void PrintWelcomeMessage();
void PrintSourceCityMessage();
void PrintDestinationCityMessage();
void PrintSpace();
void PrintNumber(int num);

void Delete_From_Array(int array[], int n, int iteration);
void Array_Duplicate(int source[], int destArr[], int n);
bool Is_Exist(int beenThere[], int arrlen, int num);
int ShortestPath(int array[N][N], int source, int destination, int beenThere[N], int iteration, int path[N]);
void Clean_New_Array (int array[]);

//the main part of the program that initiates everything.
int main(){
    int array[N][N] = { {0} };
    for (int i = 0; i<N; i++){
        for (int j=0;j<N;j++){
            array[i][j]=0;
        }
    }
    int source = 0, destination = 0;
    PrintWelcomeMessage();
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            scanf("%d", &array[i][j]);
        }
    }
    PrintSourceCityMessage();
    scanf("%d", &source);
    PrintDestinationCityMessage();
    scanf("%d", &destination);
    printf("The shortest path is:\n");

    int beenThere[N] = { 0 };
    int path[N] = { 0 };

    Delete_From_Array(beenThere, N, 0);
    Delete_From_Array(path, N, 0);

    ShortestPath(array, source, destination, beenThere, 0, path);

    for (int i = 0; i < N; i++){
        if (path[i] != -1){
            PrintNumber(path[i]);
            PrintSpace();
        }
    }

    return 0;
}

//clears the array to -1 (which is defined in the define)
void Delete_From_Array(int array[], int n, int iteration){
    for (int i = iteration + 1; i < n; i++){
        array[i] = EMPTY_CELL;
    }
}

//"cleans" a new array
void Clean_New_Array (int array[]){
    for (int i=0; i<N;i++){
        array[i]=0;
    }
}

//duplicates the array to a new array
void Array_Duplicate(int source[], int destArr[], int n){
    for (int i = 0; i < n; i++){
        destArr[i] = source[i];
    }
}

//checks if the cited city has already been visited
bool Is_Exist(int beenThere[], int arrlen, int num){
    for (int i = 0; i < arrlen; i++){
        if (beenThere[i] == num)
            return true;
    }

    return false;
}

//a backtracking function to find the shortest path that calls all the other paths
int ShortestPath(int array[N][N], int source, int destination, int beenThere[N], int iteration, int path[N]){
    beenThere[iteration] = source;
    path[iteration] = source;

    if (source == destination)
        return 0;

    int directPath = array[source][destination];
    int newLeastPath;
    int next_city;

    for (int i = 1; i < N; i++){
        next_city = (source + i) % N;
        if (Is_Exist(beenThere, N, next_city)==false){
            int traceNewPath[N]; // testing new path
            Clean_New_Array(traceNewPath);
            Delete_From_Array(traceNewPath, N, 0);
            Array_Duplicate(path, traceNewPath, iteration+1);
            newLeastPath = array[source][next_city] + ShortestPath(array, next_city, destination, beenThere, iteration+1, traceNewPath);

            if (newLeastPath <= directPath){
                directPath = newLeastPath;
                Array_Duplicate(traceNewPath, path, N);
            }
            Delete_From_Array(beenThere, N, iteration);
        }
    }

    return directPath;
}

void PrintWelcomeMessage()
{
    printf("Please enter road matrix:\n");
}

void PrintSourceCityMessage()
{
    printf("Please enter source city:\n");
}

void PrintDestinationCityMessage()
{
    printf("Please enter destination city:\n");
}

void PrintSpace()
{
    printf(" ");
}

void PrintNumber(int num)
{
    printf("%d", num);
}
