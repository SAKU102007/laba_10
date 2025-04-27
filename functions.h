#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char date[11];
    int days;
} TourDate;

typedef struct {
    float price;
    char* name;
    TourDate start;
} ExcursionTour;

void inputTour(ExcursionTour* tour);
void printTour(const ExcursionTour* tour);
void freeTour(ExcursionTour* tour);
ExcursionTour* addTour(ExcursionTour* tours, int* count);
void findToursByPrice(const ExcursionTour* tours, int count, float maxPrice);
int removeToursByName(ExcursionTour* tours, int* count, const char* nameToRemove);
void printAllTours(const ExcursionTour* tours, int count);

#endif
