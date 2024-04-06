/*!***************************************************************************************************************************************************************************************************************************************************************
\file       q.cpp
\par        Author:          Najih
\par        Email:           n.hajasheikallaudin
\par        Course:          RSE1202    
\par        Section:         RSE
\par        Tutorial:        Lab 2
\par        File created on: 18/01/2024
\brief      Recieve data of tsunami from file and format the print the data
 
\par        File information:
            This file is contains 2 function definitions to called by main in q-driver. \n \n
            Functions:
            - Tsunami* read_tsunami_data(std::string const& file_name, int& max_cnt);                                     // reading data from file in a certain way and storing them into structure tsunami
            - void print_tsunami_data(Tsunami const *arr, int size, std::string const& file_name)                         // printing data stored in structure tsunami
******************************************************************************************************************************************************************************************************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "q.hpp" // compiler needs definition of type Tsunami
using namespace std;
namespace { }
namespace hlp2 {
//#################################################################################################################################################################################################################################################################
  Tsunami* read_tsunami_data(std::string const& file_name, int& max_cnt){
//================================================================================================================================================================================================================================================================
//|                                                                              READ FILE SECTION                                                                                                                                                               |
//================================================================================================================================================================================================================================================================
    ifstream inputfile;                                                                                                   // setting file to be opened for reading data from the file
    inputfile.open(file_name);                                                                                            // opening the file
    if (!inputfile.is_open()) {                                                                                           // check if the file can be opened
        cout << "File " << file_name << " not found." << endl;                                                            // print error stream if file cannot be opend
        inputfile.close(); return 0;                                                                                      // closing the file if cannot be opened
    } 
//***************************************************************************************************************************************************************************************************************************************************************
    int size = 0; int STORAGE_SIZE = 10;
    Tsunami* arr = new Tsunami[STORAGE_SIZE];
//***************************************************************************************************************************************************************************************************************************************************************
    while (inputfile >> arr[size].month >> arr[size].day >> arr[size].year >>  arr[size].fatalities >> arr[size].wave_height) {
        
      getline(inputfile >> ws, arr[size].location);                                                                       // read the characters till '\n' is found and store into arr[size].location

      size_t lastNonSpace = arr[size].location.find_last_not_of(" \t\n\r");                                               // erase all characters found after the last non space character
      if (lastNonSpace != string::npos) { arr[size++].location.erase(lastNonSpace + 1); }

      if (size == STORAGE_SIZE) {                                                                                         // to dynamically resize the array when size == storage_size to hold more data. 
        STORAGE_SIZE *= 2;
        Tsunami* new_arr = new Tsunami[STORAGE_SIZE];                                                                     // allocating dynamic memory for new array
        for (int i = 0; i < size; ++i) { new_arr[i] = arr[i]; }                                                           // storing data from old array into new array
        delete[] arr;  arr = new_arr;                                                                                     // deallocate the old array and point to the new array
      }
    }
    inputfile.close();  max_cnt = size; return arr;
  }
//#################################################################################################################################################################################################################################################################
//################################################################################################################################################################################################################################################################# 
  void print_tsunami_data(Tsunami const *arr, int size, std::string const& file_name){
//================================================================================================================================================================================================================================================================
//|                                                                            WRITE FILE SECTION                                                                                                                                                                |
//================================================================================================================================================================================================================================================================
    std::ofstream outputfile;                                                                                             // setting file to be opened for writin
    outputfile.open(file_name);                                                                                           // opening the file
    if (!outputfile.is_open()) {                                                                                          // Check if the file can be opened
        std::cout << "Unable to create output file " << file_name << "." << std::endl;                                    // print to error stream if file cannot be opend
        outputfile.close(); return;                                                                                       // closing the file if cannot be opened
      } 
//***************************************************************************************************************************************************************************************************************************************************************
    outputfile<<"List of tsunamis:\n-----------------"<<endl;
    for (int i=0; i< size;i++){                                                                                           // printing month, day, year, fatalities, wave height and location, found in file
      outputfile<< right << setw(2) <<       setfill('0')       << arr[i].month       << " "      <<                       
                            setw(2) <<       setfill('0')       << arr[i].day         << " "      <<                      
                   left  << setw(5) <<       setfill(' ')       << arr[i].year                    <<                      
                   right << setw(6) <<       setfill(' ')       << arr[i].fatalities  << "      " <<                      
                            setw(5) << fixed << setprecision(2) << arr[i].wave_height << "     "  <<                      
                                                                   arr[i].location    << endl;                            
    }
//***************************************************************************************************************************************************************************************************************************************************************
    double max_height = 0.00, total_height = 0.00;
//***************************************************************************************************************************************************************************************************************************************************************
    outputfile<<"\nSummary information for tsunamis\n--------------------------------\n"<<endl;
    for(int i =0 ; i<size; i++){
        total_height += arr[i].wave_height;                                                                               // calculating total of all wave heights found in file
        if(arr[i].wave_height > max_height){ max_height = arr[i].wave_height; }                                           // identifing the heighest wave heigh out of all the heights found in file
    }
    outputfile<<"Maximum wave height (in meters): "<< setw(5) << max_height        << "\n" << endl;                       // printing the heighest wave heigh out of all the heights found in file
    outputfile<<"Average wave height (in meters): "<< setw(5) << total_height/size << "\n" << endl;                       // printing the average of all the heights found in file
    outputfile<<"Tsunamis with greater than average height "  << total_height/size  << ":" << endl;
    for(int i =0 ; i<size; i++){
      if(arr[i].wave_height > (total_height/size)){                                                                       // identifing the wave heighs that are higher then the average of all the heights found in file
        outputfile << fixed << setprecision(2) << arr[i].wave_height << "     " << arr[i].location<<endl;                 // printing the wave heighs that are higher then the average of all the heights found in file
      }
    }
  }
//#################################################################################################################################################################################################################################################################
}
