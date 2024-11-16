// COMSC-210 | Lab 32/33 | Winston
// IDE Used: Visual Studio Code
// Github link: https://github.com/winstonjose01/comsc210-lab32-tollbooth 

const int INIT_CARS = 2;            // Initial number of cars per lane
const int CAR_PAYING = 46;          // Probability % of a car paying and leaving
const int CAR_LEAVING = 39;         // Probability % of a car leaving the rear
const int CAR_SWITCHING = 15;       // Probability % of a car switching to another lane
const int SIMULATION = 20;          // No of simulation steps

#include "Car.h"            // Include Car class definition
#include <iostream>
#include <deque>
#include <map>
#include <array>
#include <cstdlib>          // For random generation
using namespace std;

// Function declaration to output the contents of the toll queue
void output_queue(array<deque<Car>,4>);

int main(){
    srand(time(0)); // Seed the random number generator with the current time
    array<deque<Car>,4> lanes {}; // Use map to create 4 lane tool
    deque<Car> toll; // Initialize a deque to simulate the toll booth queue
    int random_gen;  // Random generator variable

    // Populate the queue with the initial number of cars
    for (int k = 0; k < lanes.size(); k++)
        for (int i = 0; i < INIT_CARS; i++){
            Car new_car;
            //toll.push_back(new_car);  // Add the new car to the back of the deque
            lanes[k].push_back(new_car);
        }
    cout << "Initial queue: " << endl;
      // Display the initial queue of cars

    int m =1;
    for (auto& lane : lanes){
        cout << "Lane " << m << endl;
        for (auto& cars: lane){
            cout << "\t";
            cars.print();   // Call the print method of the Car object
        }
        m++;
    }
    
    int time_ctr = 1;  // Counter to track simulation time steps
    for (int sim = 0; sim < SIMULATION; sim++){
        int lanectr = 1;
        cout << endl << "Time: " << time_ctr << endl;
        for (int i = 0; i < lanes.size(); i++){
            random_gen = rand() % 100;
            // Case: A car pays and leaves the front of the queue
            if (random_gen < CAR_PAYING){
                if (!lanes[i].empty()){
                    cout << "Lane " << i + 1 << " Paid: ";
                    lanes[i].front().print(); // Print the car at the front of the queue
                    lanes[i].pop_front();  // Remove the car from the front
                }
                else{
                    cout << "Lane " << i + 1 << " is empty, no car to pay." << endl;
                }
            }
            else if (random_gen < CAR_LEAVING + CAR_PAYING) 
            {
                // Case: A new car arrives and joins the back of the queue
                Car car_arriving;
                cout << "Lane " << i + 1 << " Joined lane: ";
                car_arriving.print();  // Print the details of the arriving car
                lanes[i].push_back(car_arriving);  // Add the car to the back
            }
            else
            {
                if (!lanes[i].empty()){
                    cout << "Lane " << i+1 << " Switched: ";
                    lanes[i].back().print();  // Print the car at the back of the lane
                    // Generate a random lane index, ensuring it's not the current lane
                    int random_switch;
                    do{
                        random_switch =  rand() % 4;
                    } while (random_switch == i);

                    cout << "--> Moved to lane " << random_switch+1 << endl;
                    lanes[random_switch].push_back(lanes[i].back());  // Move car to the new lane
                    lanes[i].pop_back();  // Remove the car from the current lane
                }else {
                    cout << "Lane " << i + 1 << "is empty, no car to switch." << endl;
                }
            }
            
        }
        // Output the current state of all lanes
        output_queue(lanes);
        time_ctr++; // Increment the simulation time step
        cout << "-------------------------------------------------------------";
    }
    return 0;
}
// Function to output the current state of the toll booth queue
// arguments: the deque container 'toll'
// return: no returns
void output_queue(array<deque<Car>,4> toll){
    
    int lane_ctr = 1;
    for (auto lane: toll){
        cout << "Lane " << lane_ctr << " Queue: ";
        if (lane.empty()){
            cout << "\tEmpty\n";
            lane_ctr++;
            continue;
        }
        cout << endl;
        for (auto cars : lane){
            cout << "\t";
            cars.print();
            }
        lane_ctr++;
        }
    }
