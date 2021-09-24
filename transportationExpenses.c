  /*
  Nick Hortua - CS2600
  • Miles driven, if a private vehicle was used. Calculate the vehicle expense as $0.27 per mile driven 
  • Parking fees (The company allows up to $6 per day. Anything more than this must be paid by the employee.) 
  • Taxi fees, if a taxi was used anytime during the trip (The company allows up to $10 per day, for each day a taxi was used. Anything more than this must be paid by the employee.) 
  */

 #include <stdio.h>
 #include "transportationExpenses.h"

// calculates the costs of taxi expenses covered by the company
 float costAllotedTaxis(int daysSpent)
 {
     float taxi_expenses = 0;
     taxi_expenses = daysSpent * 10.00;
     return taxi_expenses;
 }

// calculates the costs of parking covered by the company
 float costAllotedParking (int daysSpent)
 {
     float parking_covered = 0;
     parking_covered = daysSpent * 6.00;
     return parking_covered;
 }

// calculates the total costs of miles driven
 float costAllotedMiles(int totalMiles)
 {
     float vehicle_expenses = 0;
     vehicle_expenses = totalMiles * 0.27;
     return vehicle_expenses;
 }
