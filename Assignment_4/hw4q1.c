#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXIMAL_AIRLINES 10
#define DEST 6
#define DIM 2
#define ERROR_AIRLINE_RETURN -1
#define FIRST_ARRAY_ROW	 0
#define BEST_AIRLINE_NUM 0
#define BEST_AIRLINE_RATE 1


char* destinations[] = { "Miami", "Rio", "Moscow", "Shanghai", "Barcelona", "Melbourne" };

int fillPricesTable(double flightsPrices[][DEST], int n, double* dollarRate);

double get_dollar_rate();

void compute(double flightsPrices[][DEST], int length,
	double* max, double* min, int* bestAirLine);

void bestPrice(double flightsPrices[][DEST], int length,
	double bestPrices[DEST][DIM], double dollarRate);

void printBestPrices(double bestPrices[DEST][DIM]);

void printMinMaxAvg(double max, double min, int bestAirLine);

void errorPrice(int row);

void errorDollar();

//this function starts the program and calls all the other functions
//11 lines
int main()
{
	int num_of_airlines = 0, bestAirLine = 0;
	double prices[MAXIMAL_AIRLINES][DEST];
	double max = 0, min = 0, dollarRate = 0;
	double bestPrices[DEST][DIM];

	num_of_airlines = fillPricesTable(prices, MAXIMAL_AIRLINES, &dollarRate);
	if (num_of_airlines > 0) {
		compute(prices, num_of_airlines, &max, &min, &bestAirLine);
		printMinMaxAvg(max, min, bestAirLine);
		bestPrice(prices, num_of_airlines, bestPrices, dollarRate);
		printBestPrices(bestPrices);
	}

	return 0;
}

//This functions gets all the airline ticket prices for all the airlines
//13 lines
int fillPricesTable(double flightsPrices[][DEST], int n, double* dollarRate) {
	*dollarRate = get_dollar_rate();
	double ticketPrice;
	int continuePriceEnter = 0;

	for (int airlineCounter = 0; airlineCounter < n; airlineCounter++) {
		for (int destCounter = 0; destCounter < DEST; destCounter++) {
			continuePriceEnter = scanf("%lf", &ticketPrice);
			if (continuePriceEnter != 1)
				return airlineCounter;
			if (ticketPrice <= 0) {
				errorPrice(airlineCounter);
				return ERROR_AIRLINE_RETURN;
			}
			flightsPrices[airlineCounter][destCounter] = ticketPrice;

		}
		
	}
	return n;
}

//Gets the dollar/shekel exchange rate
//6 lines
double get_dollar_rate() {
	double dollar = 0;
	scanf("%lf", &dollar);
	while (dollar <= 0) {
		errorDollar();
		scanf("%lf", &dollar);
	}
	return dollar;
}
//Calculates the minimum, maximum, and best average airline
//22 lines
void compute(double flightsPrices[][DEST], int length, double* max, double* min, int* bestAirLine) {
	double tempMax = 0, tempMin=0;
	double sum = 0, tempAvg = 0;
	for (int h = 0; h < DEST; h++) {
		sum += flightsPrices[FIRST_ARRAY_ROW][h];
	}
	tempAvg = sum / DEST; //gets the first sum
	sum = 0;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < DEST; j++) {
			if (flightsPrices[i][j] > tempMax) // if the price is bigger then the current max
				tempMax = flightsPrices[i][j];
			sum += flightsPrices[i][j];
		}
		if ((sum / DEST) < tempAvg) {
			tempAvg = sum / DEST;
			*bestAirLine = i;
		}
		sum = 0;
	}
	tempMin = tempMax;
	
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < DEST; j++) {
			if (flightsPrices[i][j] < tempMin)
				tempMin = flightsPrices[i][j];
		}
	}
	*max = tempMax;
	*min = tempMin;
}

//shows which airline has the best price for each destination and then converts from dollar to shekels
//11 lines
void bestPrice(double flightsPrices[][DEST], int length, double bestPrices[DEST][DIM], double dollarRate){
	double tempBest = 0;
	double tempBestAirline = 0;
	for (int i = 0; i < DEST; i++) {
		tempBest = flightsPrices[FIRST_ARRAY_ROW][i];
		tempBestAirline = 0;
		for (int j = 0; j < length; j++) {
			if (flightsPrices[j][i] < tempBest) {
				tempBest = flightsPrices[j][i];
				tempBestAirline = j;
			}
		}
		bestPrices[i][BEST_AIRLINE_NUM] = tempBestAirline; // inserts the values into the array
		bestPrices[i][BEST_AIRLINE_RATE] = tempBest * dollarRate;
	}
}

void printBestPrices(double bestPrices[DEST][DIM]) {
	for (int i = 0; i < DEST; i++) {
		printf("Best offer for %s is ", destinations[i]);
		printf("Airline # %d price: %.2f shekels\n", (int)(bestPrices[i][0]), bestPrices[i][1]);
	}
}

void printMinMaxAvg(double max, double min, int bestAirLine) {
	printf("Maximal price: %.2f\nMinimal price: %.2f\nBest Airline: %d\n", max, min, bestAirLine);

}

void errorPrice(int row) {
	printf("ERROR: invalid price in airline # %d\n", row);
}

void errorDollar() {
	printf("ERROR: invalid dollar rate, try again!\n");
}