//File: App.cpp

//Name:Islam Osama Nwsihy
//ID#:900170200
//Assignment 1 - Part (2)

#include <iostream>
#include "DEQ.h"
#include "DEQ.cpp"
#include <time.h>
using namespace std;

//a global class that holds information about the plane
class Plane {
public:
	int ArrivalTime;
	int JobNum;
};

//JobNum is the number of jobs arriving
//MaxSize is the number of possible planes in the Queue
//Tservice is the average service Time (T_Landing)
//Parrive, is the probability of a plane to join the Queue
int JobNum, MaxSize=0, Tservice;
float Parrive;

//Prototype
void Start();
void Arrival(DEQ<Plane>& Q, DEQ<Plane>& compare, int T_arrival);
void Service(DEQ<Plane>& Q, int T_served, int& T_Remaining, int& WaitTotal, int& JobCount, bool DoLog, int random);
void ExitLine(DEQ<Plane>& Q, int T_served, int& WaitTotal, int& JobCount, bool DoLog);
float Rand(float LO, float HI, bool canFloat);
bool QisFull(DEQ<Plane>& Q);
void Log(Plane plane, int time, int waitTime);
float AverageWait(int waitTime, int jobCount);

void main() {
	//Restart returns true only if the user enters Y or y when asked
	//choice is made to take the users input for the answer if they want to restart the program or not
	bool Restart = false;
	char choice;

	do {
		Start();
		cout << endl << endl << "Do you want to Restart?" << endl << "Y or N ?" << endl;
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
			Restart = true;
		else
			Restart = false;
		
	} while (Restart);
	

}



//The Entry Point to the Program
void Start() {
	//Declaring the variables
	//random is for the random service time (Bonus)
	int random;
	//Tremaining1 and 2 are for the time remaining to service 
	int Tremaining1, Tremaining2;
	//t is the time passed, Tmax is the simulation time, TaveArrival is the average time between 2 planes (Delta T)
	int t, Tmax, TaveArrival;
	//WaitTotal is the total wait time for planes in the simulation, jobcount is the number of jobs served
	int WaitTotal, JobCount;
	//these are the variables for the 1 runway situation (Bonus)
	int compareTremaining, compareWaitTotal, compareJobCount;
	//Q is the the Queue for the 2 runway, compare is the Q for the 1 runway (Bonus)
	DEQ<Plane>Q, compare;
	
	//Instantiating the Variables
	JobNum = 0;
	compareTremaining = 0; compareWaitTotal = 0; compareJobCount = 0;
	Tremaining1 = 0; Tremaining2 = 0; t = 0; WaitTotal = 0; JobCount = 0;
	cout << "Enter Simulation Time (in Minutes)" << endl;
	cin >> Tmax;
	cout << "Enter Average Service Time for a plane that landed" << endl;
	cin >> Tservice;
	cout << "Enter the Average Arrival Time between 2 planes (Delta T)" << endl;
	cin >> TaveArrival;
	Parrive = (1.0 / float(TaveArrival));
	cout << "Enter the Maximum Number of Elements in the Queue" << endl;
	cin >> MaxSize;
	

	srand((unsigned)time(NULL));
	while (t < Tmax) {
		//Arrival
		Arrival(Q,compare, t);

		//Service1 for both the 2 runway case and the 1 runway (Bonus) case
		random = Rand(Tservice - 3, Tservice + 3, false);
		Service(Q, t, Tremaining1, WaitTotal, JobCount, true,random);
		Service(compare, t, compareTremaining, compareWaitTotal, compareJobCount,false,random);

		//Service2 for runway 2
		random = Rand(Tservice - 3, Tservice + 3, false);
		Service(Q, t, Tremaining2, WaitTotal, JobCount, true,random);

		//Decrementing remaining time for service
		if (Tremaining1 > 0)Tremaining1--;
		if (Tremaining2 > 0)Tremaining2--;
		if (compareTremaining > 0)compareTremaining--;

		//Incrementing Time
		t++;
	}

	//Outputing the values for the 2 Runway case and the 1 Runway case
	cout << "Avarege Wait Time for 2 Runways is " << AverageWait(WaitTotal, JobCount) << " Minutes" << endl;
	cout << "Avarege Wait Time for 1 Runway is " << AverageWait(compareWaitTotal, compareJobCount) << " Minutes" << endl;

}

//Takes the the 2 Queues and the arrival time and adds a plane in the Queue for that time
void Arrival(DEQ<Plane>& Q, DEQ<Plane>& compare , int T_arrival) {
	//Temporary Plane variable
	Plane temp;
	//if the probability is aproppriate add the Plane
	if (Rand(0.0, 1.0, true) < Parrive) {
		//if the Q is full don't add the plane and Report that
		if (QisFull(Q)) cout << "Queue is Full! The Plane Will not be Added!" << endl;
		else {
			//increment the job number
			JobNum++;
			//assign the appropriate values to the temporary Plane
			temp.ArrivalTime = T_arrival; temp.JobNum = JobNum;
			//Add the plane to the end of the Queue
			Q.Add_Rear(temp);
			//Log what happened
			Log(temp, -1, -1);
		}
		//Add the same plane to the compare Queue for the comparison at the end (Bonus)
		//Do not log the changes in this case
		if (!QisFull(compare)) {
			compare.Add_Rear(temp);
		}
	}
}

//Takes the Queue, the time of serving, and the random value of the next serving delay.
//if the previous serving is done, serve the next plane and take it out of the queue
//The rest are for the ExitLine Function
void Service(DEQ<Plane>& Q, int T_served, int& T_Remaining, int& WaitTotal, int& JobCount, bool DoLog, int random) {
	//if the runway is empty and there is planes waiting serve the next one
	if (T_Remaining == 0 && !Q.DEQisEmpty()) {
		//Serve the next plane in Queue
		ExitLine(Q, T_served, WaitTotal, JobCount,DoLog);
		//close the runway while the plane docks
		T_Remaining = random;
	}
}


//it takes the Queue to remove the top plane, the time inwhich the plane landed
//wait total and job count to be incremented for the final results
//DoLog is a boolean that is true when the user wants to log in the changes
void ExitLine(DEQ<Plane>& Q, int T_served, int& WaitTotal, int& JobCount,bool DoLog) {
	//Temporary variable to hold the wait time
	int T_wait;
	T_wait = T_served - (Q.View_Front().ArrivalTime);
	if (DoLog) Log(Q.Remove_Front(), T_served, T_wait);
	WaitTotal += T_wait;
	JobCount++;
}

//Returns a random float or int between 2 values
//CanFloat is true when the user wants to allow the function to return a float value
float Rand(float LO, float HI,bool canFloat) {
	if (canFloat)
		return  (rand() / float(RAND_MAX*HI) + LO);//random float between HI and LO
	else
		return rand() % (int(HI) - int(LO) + 1) + int(LO);// random Int between HI and LO
}


//returns true if the Queue is full
bool QisFull(DEQ<Plane>& Q) {
	return (Q.DEQ_Lenght() >= MaxSize);
}

//Logs in the Changes
//Takes the plane to log in or out
//the time and wait time are required for the service log
//the wait time must be less than 0 if the user wants to log an arrival
void Log(Plane plane, int time, int waitTime) {
	if (waitTime < 0)
		cout << "Arrival# " << plane.JobNum << " at the min: " << plane.ArrivalTime << endl;
	else
		cout << "Job# " << plane.JobNum << " Service Started at the min: " << time << " Wait = " << waitTime << " Minutes" << endl;
}

//Calculates the Average wait time during the simulation
float AverageWait(int waitTime, int jobCount) {
	if (jobCount == 0) return 0;

	else return(waitTime / float(jobCount));
}