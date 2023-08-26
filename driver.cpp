/************************************************************
 *  CSC1310 001 Program 2 - Doubly Linked Lists
 *  Author:     Riley Grimaud
 *  Date:       02/28/2023
 *  File Name:  driver.cpp
 *  Purpose:
 * 
 * 
 ************************************************************/

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include "County.h"
#include "List.h"


int main()
{
	ifstream file;
	stringstream temp;
	string line, county, state;
	int index, pop;
	//file.open("counties_list.csv", ios::in);
	file.open("counties_list.csv", ios::in);

	//create a new list of county pointers ------------------------------------------------------------------
	List<County *> countyList;

	County* newCounty;

	if(file.good()) {
	while(getline(file, line, ','))
	{
		temp.clear();
		temp.str(line);
		temp >> index;

		getline(file, line, ',');
		county = line;

		getline(file, line, ',');
		state = line;

		getline(file, line, '\n');
		temp.clear();
		temp.str(line);
		temp >> pop;

		newCounty = new County(index, county, state, pop);
		//append newCounty to your list-----------------------------------------------------------------------------------
		countyList.Append(newCounty);
	}}

	file.close();
	//call mergesort---------------------------------------------------------------------------------------------
	countyList.MergeSort();
	cout << "Flag" << endl;
	//print the list-----------------------------------------------------------------------------------------------------
	countyList.Print();

	return 0;
}