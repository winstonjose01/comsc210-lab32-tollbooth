// COMSC-210 | Lab 32 | Winston
// IDE Used: Visual Studio Code
// Github link: https://github.com/winstonjose01/comsc210-lab32-tollbooth 

const int INIT_CARS = 2;
const int CAR_PAYING = 55;
const int CAR_LEAVING = 45;

#include "Car.h"            // Include Car class definition
#include <iostream>
#include <deque>
#include <cstdlib>
using namespace std;

// Function declaration to output the contents of the toll queue
void output_queue(deque<Car> &tollstat);

int main(){
    srand(time(0)); // Seed the random number generator with the current time
    deque<Car> toll; // Initialize a deque to simulate the toll booth queue
    int random_gen;  // Random generator variable

    // Populate the queue with the initial number of cars
    for (int i = 0; i < INIT_CARS; i++){
        Car new_car;
        toll.push_back(new_car);  // Add the new car to the back of the deque
    }
    cout << "Initial queue: " << endl;
      // Display the initial queue of cars
    for (auto cars: toll){
        cout << "\t";
        cars.print();   // Call the print method of the Car object
    }
    
    int simulation = 1;  // Counter to track simulation time steps
    while (true){
        cout << endl << "Time: " << simulation << " Operation: ";
        random_gen = rand() % 100;
        // Case: A car pays and leaves the front of the queue
        if (random_gen < CAR_PAYING){
            cout << "Car paid: ";
            toll.front().print(); // Print the car at the front of the queue
            toll.pop_front();  // Remove the car from the front
        }
        else{
            // Case: A new car arrives and joins the back of the queue
            Car car_arriving;
            cout << "Joined lane: ";
            car_arriving.print();  // Print the details of the arriving car
            toll.push_back(car_arriving);  // Add the car to the back
        }

        // Output the current queue status
        output_queue(toll);

        // Check if the queue is empty and terminate the simulation if so
        if (toll.size() == 0){
            cout << "\tEmpty" << endl;
            break;
        }
        simulation++; // Increment the simulation time step
    }

    return 0;
}
// Function to output the current state of the toll booth queue
// arguments: the deque container 'toll'
// return: no returns
void output_queue(deque<Car> &tollstat){

    cout << "Queue: " << endl;
    for (auto cars: tollstat){
        cout << "\t";
        cars.print();
    }

}