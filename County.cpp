/************************************************************
 *  CSC1310 001 Program 2 - Doubly Linked Lists
 *  Author:     Riley Grimaud
 *  Date:       02/28/2023
 *  File Name:  County.cpp
 *  Purpose:	not original code; this file is provided by the instructor.
 * 				Creats class type county with attributes index, name, state,
 * 				and population. 
 * 
 * 
 ************************************************************/


#include "County.h"

using namespace std;

County::County(int i, string n, string s, int p)
{
	index = i;
	name = n;
	state = s;
	population = p;
}

int County::getIndex()
{
	return index;
}

void County::setIndex(int i)
{
	index = i;
}

int County::getPopulation()
{
	return population;
}

bool County::operator <(const County& c)				//when using operators >, or <, need to compare populations
{
	if(population < c.population)
		return true;
	else
		return false;
}

bool County::operator >(const County& c)
{
	if(population > c.population)
		return true;
	else
		return false;
}
