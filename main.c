// includes
#include <stdio.h>
#include <math.h>
#include "./meal.c"
#include "./hotelExpenses.c"
#include "./transportationExpenses.c"

// ui globals
int uiState;        // current state of ui state machine
int exitUI;         // change to 1 to exit state machine
char input[100];    // most recent user input

// calculator globals
int tripDays;           // number of days spent on trip, inclusive
int arrivalTime;        // hour of arrival at beginning of trip
int departureTime;      // hour of departure at end of trip

int breakfasts;         // number of breakfasts allotted based on trip length
int lunches;            // number of lunches allotted based on trip length
int dinners;            // number of dinners allotted based on trip length

float mealFares;        // amount spent on breakfasts
float airfare;          // amount of airfare
float rentalFare;       // amount of car rentals
int milesDriven;        // number of miles driven
float vehicleExpenses;  // private vehicle use expenses
float parkingFees;      // parking fees
float taxiFees;         // taxi fees
float conferenceFees;   // conference or seminar fees
float hotelExpenses;    // hotel expenses


float mealCovered;      // amount allotted for meals
float hotelCovered;     // amount allotted for lodging
float taxiCovered;      // amount allotted for lodging
float parkingCovered;   // amount allotted for lodging


float totalExpenses;    // total amount of expenses for the trip
float totalAllowances;  // total amount of allowances for expenses on the trip
float totalDifferences; // total amount saved/excess that must be reimbursed

int excess;            // 0 if employee saved money (or stayed perfectly on budget), 1 if there was an excess spent


int main(int argc, char(*argv[])) {
    /*
        Basic UI for user input of all required information, and display of final values
    */
    while(!exitUI) {
        // Prompt and recioeve information from user.
        printf("CS 2600 Project 2:\n");
        printf("Business Travel Expense Calculator\n\n");

        printf("Press enter to continue.\n");
        gets(input); // take any input

        printf("_________________________________________________\n");
        printf("Enter the total number of days spent on the trip:\n");
        printf("This includes day of departure and day of return\n");
        scanf("%d", &tripDays);
        printf("Enter the hour of departure on the first day of the trip:\n");
        printf("Please use 24 hour time. For example, if you depart at 2pm, enter '14'\n");
        scanf("%d", &arrivalTime);
        printf("Enter the hour of arrival back home on the last day of the trip:\n");
        printf("Please use 24 hour time. For example, if you arrive at 2pm, enter '14'\n");
        scanf("%d", &departureTime);
        // calculate alotted meals based on trip arrival, departure, and length
        breakfasts = breakfastAllowed(departureTime, arrivalTime, tripDays);
        lunches = lunchAllowed(departureTime, arrivalTime, tripDays);
        dinners = dinnerAllowed(departureTime, arrivalTime, tripDays);
        printf("You were allotted %d breakfasts, %d lunches, and %d dinners for this trip.\n", breakfasts, lunches, dinners);
        printf("Enter the total amount spent on meals during your trip: \n");
        scanf("%f", &mealFares);
        printf("Enter the total amount spent on Round-Trip Airfare during your trip: \n");
        scanf("%f", &airfare);
        printf("Enter the total amount spent on Car Rentals during your trip: \n");
        scanf("%f", &rentalFare);
        printf("Enter the total amount of Miles Driven on a personal vehicle on your trip: \n");
        printf("If only a rental car was used, enter '0'. \n");
        scanf("%d", &milesDriven);
        printf("Enter the total amount spent on Parking Fees during your trip: \n");
        scanf("%f", &parkingFees);
        printf("Enter the total amount spent on Taxi Fees during your trip: \n");
        scanf("%f", &taxiFees);
        printf("Enter the total amount spent on Conference or Seminar Registration Fees during your trip: \n");
        scanf("%f", &conferenceFees);
        printf("Enter the total amount spent on Hotel Expenses during your trip: \n");
        scanf("%f", &hotelExpenses);

        // use recieved values to calculate covered expenses
        mealCovered = costAllotedMeals(departureTime, arrivalTime, tripDays);
        taxiCovered = 0;
        parkingCovered = 0;
        vehicleExpenses = 0;
        hotelCovered = costAllotedHotels(tripDays);
        taxiCovered = costAllotedTaxis(tripDays);
        parkingCovered = costAllotedParking(tripDays);
        vehicleExpenses = costAllotedMiles(milesDriven);
        printf("\n");
        printf("Airfare Expenses: %.2f Airfare Allowances: %.2f\n", airfare, airfare);
        printf("Meal Expenses: %.2f Meal Allowances: %.2f\n", mealFares, mealCovered);
        printf("Rental Vehicle Expenses: %.2f Rental Vehicle Allowances: %.2jf\n", rentalFare, rentalFare);
        printf("Private Vehicle Expenses: %.2f Private Vehicle Allowances: %.2f\n", vehicleExpenses, vehicleExpenses);
        printf("Taxi Expenses: %.2f Taxi Allowances: %.2f\n", taxiFees, taxiCovered);
        printf("Parking Expenses: %.2f Parking Allowances: %.2f\n", parkingFees, parkingCovered);
        printf("Conference/Seminar Expenses: %.2f Conference/Seminar Allowances: %.2f\n", conferenceFees, conferenceFees);
        printf("Hotel Expenses: %.2f Hotel Allowances: %.2f\n", hotelExpenses, hotelCovered);

        printf("\n");
        // calculate expenses and allowances, then get the difference
        totalExpenses   = mealFares   + airfare + rentalFare + vehicleExpenses + taxiFees    + conferenceFees + hotelExpenses + parkingFees;
        totalAllowances = mealCovered + airfare + rentalFare + vehicleExpenses + taxiCovered + conferenceFees + hotelCovered  + parkingCovered;
        totalDifferences = totalExpenses - totalAllowances;

        if(totalDifferences < 0) excess = 1;                // if more was spent than allowed (difference is negative), we have an excess
        totalDifferences = (float) fabs(totalDifferences);  // get absolute value of difference for future display
 
        // print final values
        printf("Total Travel Expenses: %.2f\nTotal Travel Allowances: %.2f\n", totalExpenses, totalAllowances);
        // change last print based on if we detected and excess or not.
        if(!excess) {
            printf("Excess to be reimbursed by businessperson: %.2f\n", totalDifferences);
        } else {
            printf("Amount saved by businessperson: %.2f", totalDifferences);
        }


        exitUI = 1;
    }
    return 0;   
}