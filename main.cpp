//
// Author: Adithya Jose, UIC, Spring 2021
// Assignment: Project 04
//
// g++ -g -Wall main.cpp -o main
// ./main
// valgrind ./main
//
// Project Description: My program is going to input 2 types of data: stations in the
// DIVVY system, and bike trips that riders have taken on a DIVVY bike.
// My program starts by prompting and inputting the name of the
// stations file from the keyboard, and then prompting and inputting the
// name of the bike trips file from the keyboard. If either file cannot be
// opened, your program should output an error message (including the
// filename) and stop. 
//
//

#include <iostream>
#include <string>
#include <cmath>    
#include <iomanip>   
#include <fstream>

using namespace std;

struct Stations
{
    string id;
    int capacity;
    double latitude;
    double longitude;
    string name;
    int trips = 0; // int object to be made use of for commands stations and finds
    int plcHldrInt = -1; // made use in find command for case-sensative searches, a conditional set
    int numStations; // int object keeping track of number of stations
};

struct bikeTrips
{
    string tripID;
    string bikeID;
    string startStationID;
    string endStationID;
    int tripDuration;
    string startTime; // conditional string object to be made use in trip command
    bool tripBool = false; // conditional bool object made use in trips command
    int numTrips; // int object keeping track of number of trips
};

//
// inputStations
//
// A function that opens the input file for DIVVY bike stations.
// Once opened it fills a Stations struct array with corresponding data and closes the file.
//
Stations* inputStations(string filename1, int& S)
{
    ifstream infile;        // declares an input file object
     
    infile.open(filename1);        // opens input file
    
    // mitigation to make sure input file is legitmate otherwise prints error message
    
    if (!infile.good())  // file is NOT good, i.e. could not be opened:
    {
        cout << "**Error: unable to open input file '" << filename1 << "'" << endl;
        S = 0;
        return nullptr;  // return now since we cannot continue without proper input file
    }
                    
    infile >> S;
    
    Stations* stations;
    stations = new Stations[S];
    
    for (int i = 0; i < S; ++i) // filling in array with data from file based on N
    {
        infile >> stations[i].id;
        infile >> stations[i].capacity;
        infile >> stations[i].latitude;
        infile >> stations[i].longitude;
        getline(infile, stations[i].name);
    }
    
    infile.close(); // closes input file
    
    return stations; // return stations array
}

//
// inputTrips
//
// A function that opens the input file for DIVVY bike trips.
// Once opened it fills a bikeTrips struct array with corresponding data and closes the file.
//
bikeTrips* inputTrips(string filename2, int& T)
{
    ifstream infile2;        // declares an input file object
     
    infile2.open(filename2);        // opens input file
    
    // mitigation to make sure input file is legitmate otherwise prints error message
    
    if (!infile2.good())  // file is NOT good, i.e. could not be opened:
    {
        cout << "**Error: unable to open input file '" << filename2 << "'" << endl;
        T = 0;
        return nullptr;  // return now since we cannot continue without proper input file
    }
                    
    infile2 >> T;
    
    bikeTrips* trips;
    trips = new bikeTrips[T];
    
    for (int i = 0; i < T; ++i) // filling in array with data from file based on N
    {
        infile2 >> trips[i].tripID;
        infile2 >> trips[i].bikeID;
        infile2 >> trips[i].startStationID;
        infile2 >> trips[i].endStationID;
        infile2 >> trips[i].tripDuration;
        infile2 >> trips[i].startTime;
    }
    
    infile2.close(); // closes input file
    
    return trips;
}

//
// stats
//
// A simple void function that calculates and outputs the total # of stations, the total # of trips, and the total capacity across all the stations.
//
void stats (Stations stations[], int& S, bikeTrips trips[], int& T)
{
    int x;
    x = 0;
    
    for (int i = 0; i < S; ++i)
    {
        x = x + stations[i].capacity;
    }
    
    cout << "stations: " << S << endl;
    cout << "trips: " << T << endl;
    cout << "total bike capacity: " << x << endl;
}

//
// durations
//
// A simple void function that analyzes the bike trips, then categorizes and outputs the trips into 1 of 5 categories based on the duration.
//
void durations (bikeTrips trips[], int& T)
{
    // int objects based on duration categories
    int ltThirty = 0;
    int thirtyToSixty = 0; 
    int oneToTwo = 0; 
    int twoToFive = 0; 
    int gtFive = 0; 
    
    for (int i = 0; i < T; ++i)
    {
        if (trips[i].tripDuration <= 1800)
        {
            ltThirty += 1;
        }
        
        if ((trips[i].tripDuration > 1800) && (trips[i].tripDuration <= 3600))
        {
            thirtyToSixty += 1;
        }
        
        if ((trips[i].tripDuration > 3600) && (trips[i].tripDuration <= 7200))
        {
            oneToTwo += 1;
        }
        
        if ((trips[i].tripDuration > 7200) && (trips[i].tripDuration <= 18000))
        {
            twoToFive += 1;
        }
        
        if (trips[i].tripDuration > 18000)
        {
            gtFive += 1;
        }
    }
    
    cout << "trips <= 30 mins: " << ltThirty << endl;
    cout << "trips 30..60 mins: " << thirtyToSixty << endl;
    cout << "trips 1-2 hrs: " << oneToTwo << endl;
    cout << "trips 2-5 hrs: " << twoToFive << endl;
    cout << "trips > 5 hrs: " << gtFive << endl;    
}

//
// starting
//
// A simple void function that analyzes the bike trips, and then categorizes the trips into 1 of 24 categories based on the starting hour. The total number of trips falling into each category is displayed; if there are no trips, output the category with a 0.
//
void starting(bikeTrips trips[], int& T)
{
   int* a;
   a = new int[24];
    
   for (int i = 0; i < 24; ++i)
   {
       a[i] = 0;
   }
   
   for (int i = 0; i < T; ++i)
   {
       string s = trips[i].startTime.substr(0, 2);
       int x = stoi(s);
       
       a[x] += 1;  
   }
    
   for (int i = 0; i < 24; ++i)
   {
       cout << i << ": " << a[i] << endl;
   }
   
   delete[] a;
}

//
// distBetween2Points
//
// Returns the distance in miles between 2 points (lat1, long1) and 
// (lat2, long2).  Latitudes are positive above the equator and 
// negative below; longitudes are positive heading east of Greenwich 
// and negative heading west.  Example: Chicago is (41.88, -87.63).
//
// NOTE: you may get slightly different results depending on which 
// (lat, long) pair is passed as the first parameter.
// 
// Originally written by: Prof. Hummel, U. of Illinois, Chicago, Spring 2021
// Reference: http://www8.nau.edu/cvm/latlon_formula.html
//
double distBetween2Points(double lat1, double long1, double lat2, double long2)
{
  double PI = 3.14159265;
  double earth_rad = 3963.1;  // statue miles:

  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;

  double dist = earth_rad * acos(
    (cos(lat1_rad) * cos(long1_rad) * cos(lat2_rad) * cos(long2_rad))
    +
    (cos(lat1_rad) * sin(long1_rad) * cos(lat2_rad) * sin(long2_rad))
    +
    (sin(lat1_rad) * sin(lat2_rad))
  );

  return dist;
}

//
// sortByDistance
//
// A simple void function that sorts an inputted stations array by distance or ascending order.
//
void sortByDistance(Stations stations[], int& S, double userLat, double userLong, double D)
{
    for (int i = 0; i < S-1; i++)
       {
          int minIndex = i;

          for (int j = i+1; j < S; j++)
          {
             if (distBetween2Points(userLat, userLong, stations[j].latitude, stations[j].longitude) < distBetween2Points(userLat, userLong, stations[minIndex].latitude, stations[minIndex].longitude))
             {
                minIndex = j;
             }
          }

          Stations temp = stations[i];
          stations[i] = stations[minIndex];
          stations[minIndex] = temp;
       }
}

// 
// nearMe
//
// A simple void function that calculates distances of all stations from an inputted longitude and latitude. Outputs trips in miles.
// Makes use of distBetween2Points function to calculate distance between starting station and ending station.
//
void nearMe(Stations stations[], int& S, double userLat, double userLong, double D)
{
    cout << "The following stations are within " << D << " miles of (" << userLat << ", " << userLong << "):" << endl;
    
    int count = 0;
    for (int i = 0; i < S; ++i)
    {
        double x = distBetween2Points(userLat, userLong, stations[i].latitude, stations[i].longitude);
//         cout << i + 1 << ").: " << x << endl;
         
        if (x <= D)
        {
            count += 1;
        }     
    }
    
    if (count == 0)
    {
        cout << " none found" << endl;
    }
    
    int j = 0;
    Stations* a = new Stations[count];
    
    for (int i = 0; i < S; ++i)
    {
        double x = distBetween2Points(userLat, userLong, stations[i].latitude, stations[i].longitude);
//         cout << i + 1 << ").: " << x << endl;
         
        if (x <= D)
        {
            a[j] = stations[i];
            j += 1;
        }     
    }
    
    sortByDistance(a, count, userLat, userLong, D);
    
    for (int i = 0; i < count; ++i)
    {
//         cout << std::fixed;
        cout << std::setprecision(6); // sets digits to six after decimal point
        
        
        cout << "station " << a[i].id << " (" << a[i].name << " ): " << distBetween2Points(userLat, userLong, a[i].latitude, a[i].longitude) << " miles" << endl;
    }
    
    delete[] a;
}

//
// sortByName
//
// A simple void function that sorts an inputted stations array by name or alphabetical order.
//
void sortByName(Stations stations[], int& S)
{
   for (int i = 0; i < S-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < S; j++)
      {
         if (stations[j].name < stations[minIndex].name)
         {
            minIndex = j;
         }
      }
      
      Stations temp = stations[i];
      stations[i] = stations[minIndex];
      stations[minIndex] = temp;
   }
}

//
// searchStationID
//
// int function to search for a perticular id in a stations.id array
// if not found returns -1
//
int searchStationID(Stations stations[], int& S, string id)
{
   for (int i = 0; i < S; ++i)
   {
      if (stations[i].id == id)
         return i; 
   }

   return -1;
}

//
// addTripsToStations
//
// A simple void function that literally reads in data from a inputted trips array and adds it to the .trip object in the struct Stations.
//
void addTripsToStations(Stations stations[], int& S, bikeTrips trips[], int& T)
{
    int temp = -1;
    string x;
    // loops through trips array to assign the number of trips, starting or ending stations, to the stations[].trips object 
    for (int i = 0; i < T; ++i)
    {
        // loops through the starting stations first and then the ending stations 
        // checks if starting station and ending station is the same 
        // adds 1 if above condition is true for ending stations or adds 1 if it's just starting station
        x = trips[i].startStationID;
        int index = searchStationID(stations, S, x);
        
        if (index != -1)
        {
            stations[index].trips = stations[index].trips + 1;
            temp = index;
        }
        
        x = trips[i].endStationID;
        index = searchStationID(stations, S, x);
        
        if ((index != -1) && (temp != index))
        {
            stations[index].trips += 1;
        }
    }
}

//
// listStations
//
// A simple void function that sorts the stations array and ouputs stations data in a certain order
//
void listStations(Stations stations[], int& S)
{
    sortByName(stations, S); // sorts alphabetically
    
    for (int i = 0; i < S; ++i)
    {
        cout << stations[i].name << " (" << stations[i].id << ") @ (" << stations[i].latitude << ", " << stations[i].longitude << "), " << stations[i].capacity << " capacity, " << stations[i].trips << " trips" << endl;  
    }
}

//
// find
//
// A void function that performs a case-sensitive search of the stations whose name includes the word input by the user;
// assume it’s one word, and not a string of words. The matching stations are output in alphabetical order by
// name. For each station, the output includes the name, station ID, position (latitude, longitude), capacity, and
// the total # of bike trips where this station was the starting station or the ending station.
// 
void find(Stations stations[], int& S, string keyword)
{
    int index = -1; 
    int count = 0;
    string x;
    // loops through stations to perform a case-sensitive search of the string keyword
    // adds count by one
    for (int i = 0; i < S; ++i)
    {
        x = stations[i].name;
        index = x.find(keyword);
        
        if (index != -1)
        {
                stations[i].plcHldrInt = 1;
                count += 1;
        }
        else
        {
            stations[i].plcHldrInt = -1;
        }
    }
    // if found, mark the keyword and cout relevant data.
    // count is used to to cout relevant stations
    sortByName(stations, S);
    
    if (count != 0)
    {
        for(int i = 0; i < S; ++i)
        {
            if (stations[i].plcHldrInt == 1)
            {
                cout << stations[i].name << " (" << stations[i].id << ") @ (" << stations[i].latitude << ", " << stations[i].longitude << "), " << stations[i].capacity << " capacity, " << stations[i].trips << " trips" << endl ;  
            }
        }
    }
    else if (count == 0)
    {
        cout << " none found" << endl;
    }
}

//
// searchArray
//
// int function to search for a perticular string in a string array
// if not found returns -1
//
int searchArray(string A[], int N, string element)
{

   for (int i = 0; i < N; ++i)
   {
       
      if (A[i] == element)
         return i;
       
   }

   return -1;
}

//
// sortArray
//
// A simple void function thats sorts an inputted string array alphabetically only made use in the trips command.
//
void sortArray(string A[], int N)
{
 
   for (int i = 0; i < N - 1; i++)
   {
      int minIndex;
      minIndex = i;
      
      for (int j = i+1; j < N; j++)
      {
         if (A[j] < A[minIndex])
         {
            minIndex = j;
         }
      }
      
      string temp = A[i];
      A[i] = A[minIndex];
      A[minIndex] = temp;
   }
}

//
// coutFindTripArray
//
// A simple void function that couts a certain string array (meant for trips)
// really made because running out of lines to code on
//
void coutFindTripArray(string A[], int N)
{ 
    for (int i = 0; i < N; ++i)
    {
        if(i == N - 1)
        {
            cout << A[i] << endl;
        }
        else
        {
            cout << A[i] << ", ";
        }
    }
}

//
// Trips
//
// A void function that searches the bike trips for all trips with a start time that falls within the given timespan.
// If no such trips are found, “none found” is output. Otherwise, the number of trips is output along with the average duration of those trips, in minutes. 
//
void Trips(bikeTrips trips[], int& T, Stations stations[], int& S, string startTime, string endTime)
{
    int x, z, j = 0, count = 0, avg = 0, minIndex, minStartTime, minEndTime;
    string a;
    bool tempBool = false;
    
    if (startTime.size() == 5)
    {
        x = stoi(startTime.substr(0,2)); z = stoi(startTime.substr(3,2));
    }
    else
    {
        x = stoi(startTime.substr(0,1)); z = stoi(startTime.substr(2,2));
    }
    
    minStartTime = (x * 60) + z;
    
    if (endTime.size() == 5)
    {
        x = stoi(endTime.substr(0,2)); z = stoi(endTime.substr(3,2));
    }
    else
    {
        x = stoi(endTime.substr(0,1)); z = stoi(endTime.substr(2,2));
    }
    
    minEndTime = (x * 60) + z;
    
    if (minStartTime >= minEndTime)
    {
        tempBool = true;
    }
    
    for (int i = 0; i < T; ++i)
    {
        a = trips[i].startTime;
        
        if (a.size() == 5)
        {
            x = stoi(a.substr(0,2)); z = stoi(a.substr(3,2));
        }
        else
        {
            x = stoi(a.substr(0,1)); z = stoi(a.substr(2,2));
        }
        
        minIndex = (x * 60) + z;
        
        if (tempBool == false)
        {
            if((minIndex <= minEndTime) && (minIndex >= minStartTime))
            {
                trips[i].tripBool = true;
                avg += trips[i].tripDuration;
                count += 1;
            }
            else
            {
                trips[i].tripBool = false;
            }
        }
        else
        {
            if (((minIndex <= 1439) && (minIndex >= minStartTime)) || ((minIndex >= 0) && (minIndex <= minEndTime)))
            {
                trips[i].tripBool = true;
                count += 1;
                avg += trips[i].tripDuration;
            }
            else
            {
                trips[i].tripBool = false;
            }
        }
    }
    
    sortByName(stations, S);
    
    if (count != 0)
    {
        string tempArray[count];
        avg = (avg / 60) / count;
        cout << count << " trips found" << endl << "avg duration: " << avg << " minutes" << endl << "stations where trip started: ";
        
        for (int i = 0; i < T; ++i)
        {
            if (trips[i].tripBool == true)
            {
                int index = searchStationID(stations, S, trips[i].startStationID);
                int tempIndex = searchArray(tempArray, count, stations[index].name);
                
                if ((index != -1) && (tempIndex == -1))
                {
                    tempArray[j] = stations[index].name;
                    j += 1;
                }
            }
        }
        
        string tempArray2[j];
        
        for (int i = 0; i < j; ++i)
        {
            tempArray2[i] = tempArray[i];
        }
        sortArray(tempArray2, j);
        coutFindTripArray(tempArray2, j);
    } 
    else 
    {
        cout << " none found" << endl;
    }
}

int main()
{
    string filename1, filename2;
    int S, T; 
    
    cout << "** Welcome to the Analyzing DIVVY Bike Data Program **" << endl;
    cout << "Enter set of DIVVY stations filename> " << endl;        // prompt to enter first input file
    cin >> filename1;
    
    Stations* stations = nullptr;
    S = 0;
    
    stations = inputStations(filename1, S);
    
//     for (int i = 0; i < S; ++i)
//     {
//         cout << i + 1 << "). " << stations[i].id << " " << stations[i].capacity << " " << stations[i].latitude << " " << stations[i].longitude << " " << stations[i].name << endl;
            
//     }
    
    cout << "Enter set of DIVVY bike trips filename> " << endl;        // prompt to enter second input file
    cin >> filename2;
    
    bikeTrips* trips = nullptr;
    T = 0;
    
    trips = inputTrips(filename2, T);
    
    addTripsToStations(stations, S, trips, T);
    
//     for (int i = 0; i < T; ++i)
//     {
//          cout << i + 1 << "). " << trips[i].tripID << " " << trips[i].bikeID << " " << trips[i].startStationID << " " << trips[i].endStationID << " " << trips[i].tripDuration << " " << trips[i].startTime << endl;
//     }
       
    string command;
   
    while (command != "#")
    {
        cout << "Enter command (# to stop)> ";
        cin >> command;
        
        if ((command != "stats") && (command != "durations") && (command != "starting") && (command != "nearme") && (command != "stations") && (command != "find") && (command != "trips") && (command != "#"))
        {
            cout << "** Invalid command, try again..." << endl;
        }

        if (command == "stats")
        {
            stats(stations, S, trips, T);
        }
       
        if (command == "durations")
        {
            durations(trips, T);
        }
       
        if (command == "starting")
        {
            starting(trips, T);
        }
        
        if (command == "nearme")
        {
            double userLat, userLong, D;
            cin >> userLat >> userLong >> D;
            nearMe(stations, S, userLat, userLong, D);
        }
        
        if (command == "stations")
        {
            listStations(stations, S);
        }
        
        if (command == "find")
        {
            string wordInput;
            cin >> wordInput;
            
            find(stations, S, wordInput);
        }
        
        else if (command == "trips")
        {
            string inputStartTime, inputEndTime;
            cin >> inputStartTime >> inputEndTime;
            
            Trips(trips, T, stations, S, inputStartTime, inputEndTime);
        }
    }
    
    cout << "** Done **" << endl;
   
    delete[] stations;
    delete[] trips;
    return 0;
}