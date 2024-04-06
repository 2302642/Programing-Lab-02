/*!***************************************************************************************************************************************************************************************************************************************************************
\file       q.hpp
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
#ifndef Q_HPP
#define Q_HPP
// required since type Tsunami has data member of type std::string
#include <string> // don't remove

namespace hlp2 {
  
  struct Tsunami {
    // declare data members ...
    int month, day, year, fatalities;
    double wave_height;
    std::string location;
  };
  
  // declaration of interface functions ...
  Tsunami* read_tsunami_data(std::string const& file_name, int& max_cnt);
  void print_tsunami_data(Tsunami const *arr, int size, std::string const& file_name);
  
} // end namespace hlp2
#endif
