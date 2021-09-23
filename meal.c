#include <stdio.h>
#include "meal.h"
/* 
Jeremy Lesmana - CS2600
In this part, there are 4 different functions for the meal, 
finding out how many meals (breakfast, lunch, dinner)
the employee will get, and finding the total cost alloted by the company.
*/
int breakfastAllowed(int timeDept, int timeArrival, int numDays){

    //Here we start with breakfast = 0 to initialize the variable.
    int breakfast = 0;

    /*If the number of days > 2, meaning that the employee has spent that full day on the trip,
    that employee will for sure get a breakfast alloted, since they're there the full day. */
    if (numDays > 2)
        breakfast = breakfast + numDays - 2;
    
    //If the time of departure is before 7 AM, then the employee will get a breakfast covered
    if(timeDept < 7) 
        breakfast++;

    //If the time of arrival is after 8 AM then the employee will get a breakfast covered.
    if(timeArrival > 8) 
        breakfast++;

    return breakfast;
}

//The same concept of breakfast applies to lunch and dinner.
int lunchAllowed(int timeDept, int timeArrival, int numDays){
    int lunch = 0;
    if (numDays > 2)
        lunch = lunch + numDays - 2;
    if(timeDept < 12) 
        lunch++;
    if(timeArrival > 13) 
        lunch++;

    return lunch;
}

int dinnerAllowed(int timeDept, int timeArrival, int numDays){
    int dinner = 0;
    if (numDays > 2)
        dinner = dinner + numDays - 2;
    if(timeDept < 18) 
        dinner++;
    if(timeArrival > 19) 
        dinner++;

    return dinner;
}

/* Here we are just recalling the functions again
in order to get the allowed number of meals, and then we're going to
multiply it by their respective costs */
int costAlloted(int timeDept, int timeArrival, int numDays) {
    int breakfastCost = breakfastAllowed(timeDept, timeArrival, numDays) * 9;
    int lunchCost = lunchAllowed(timeDept, timeArrival, numDays) * 12;
    int dinnerCost = dinnerAllowed(timeDept, timeArrival, numDays) * 16;
    int sum = breakfastCost + lunchCost + dinnerCost;
    return sum;
}
