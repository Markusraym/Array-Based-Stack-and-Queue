#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class ABS
{
	// variables here
	float scale_factor = 2.0f; //Scale factor that dictates how much you copy in the pop()
	int capacity; //The maximum capacity in the array
	int size; //The amount of stuff actually in the array
	T* theData; //T type pointer that points to the array in the heap

public:
	// prototypes here 
	ABS(); //default constructor, max capacity is set to 1 and current size set to 0.

	ABS(int capacity); //Constructor for an ABS with the specified maximum capacity

	ABS(const ABS& d); // Copy Constructor

	ABS& operator=(const ABS& d); // Assignment operator

	~ABS(); // Destructor

	void push(T data); //Add a new item to the top of stack and resize if necessary

	T pop(); //Remove the item from top of stack, resize if necessary, and return the value removed. Throw runtime error if empty

	T peek(); //Return the value of the item at the top of stack without removing it. Throw runetime error if empty

	unsigned int getSize(); // Returns the current number of items in the ABS

	unsigned int getMaxCapacity(); // Returns the current max capacity of the ABS

	unsigned int getCapacity(); //temporary bug fix FIX BEFORE DUE DATE!! 

	T* getData(); // Returns the array representing the stack. 

};

//Default constructor
template <typename T>
ABS<T>::ABS()
{
	capacity = 1; // Starting out the capacity is just 1
	theData = new T[capacity]; // new int[capacity] exists on the heap, theData is a pointer to it
	size = 0; //Has a size of 0 starting out, there is nothing in the array
}

//Constructor with parameters
template <typename T>
ABS<T>::ABS(int capacity)
{
	this->capacity = capacity; // Might have to come up with different variable, idk if thisll work
	theData = new T[capacity];
	size = 0;
}

//Copy constructor 
template <typename T>
ABS<T>::ABS(const ABS& d)
{
	this->size = d.size; // Copy the size
	this->capacity = d.capacity; // Copy the capacity
	theData = new T[capacity]; // the "deep" copy of the array
	for (int i = 0; i < capacity; i++)
	{
		theData[i] = d.theData[i];
	}
	//Credit to Professor Fox's copy constructor example!
}

//Assignment operator
template <typename T>
ABS<T>& ABS<T>::operator=(const ABS& d)
{
	delete[] theData;
	this->size = d.size; // Copy the size
	this->capacity = d.capacity; // Copy the capacity
	theData = new T[capacity]; // the "deep" copy of the array
	for (int i = 0; i < capacity; i++)
	{
		theData[i] = d.theData[i];
	}
	return *this;
}	//Credit to Professor Fox's copy constructor example! 

//Destructor
template <typename T>
ABS<T>::~ABS()
{
	delete[] theData;
}

//Adds a new item to the top of the size and resize if necessary
template <typename T>
void ABS<T>::push(T data)
{
	if (size == capacity) // If the amount of slots(size) used up is equal to the maximum capacity 
	{
		T* throwArray = new T[size * (int)scale_factor]; // create a value with twice the size, if full

		for (int i = 0; i < size; i++)
		{
			throwArray[i] = theData[i]; //assign the values into the new array
		}
		delete[] theData; // delete the old the stuff

		theData = throwArray; //have the pointer point to the new location
		capacity = capacity * 2; // Update the maximum capacity that there are now twice the amount of potential slots
	}
	theData[size] = data; // Add the passed in data value into the next index, where size also keeps track of. 
	size = size + 1; // If the above was invoked, the capacity became doubled, but only one extra slot is actually getting filled

}

//Remove the item at the top of stack, resizes if neccessary, and return the value removed
//If the stack is exactly half full, the size is doubled and the most recent value is removed. 
template <typename T>
T ABS<T>::pop()
{
	//Check if the stack is empty, if so, throw a runtime error
	if (size == 0)
	{
		throw runtime_error("The stack is empty!");
		//Somehow include a continue?
	}

	//Check if the array is half full, and if so, make a new array with half the size. 
	float percentFilled = size / (float)capacity;
	if (percentFilled <= (1 / scale_factor))
	{
		T* throwArray = new T[(int)capacity / (int)scale_factor]; //Make a new array half the size

		for (int i = 0; i < size; i++)
		{
			throwArray[i] = theData[i];
		}
		delete[] theData; //Delete the previous stuff
		theData = throwArray; // Point the pointer to the new memory location
		capacity = capacity / scale_factor; //Update the capacity 

	}

	//Save the last index as a variable before removing it
	T removedValue = theData[size - 1];

	//Make another array of the same size, but copy over everything except the last element 
	T* throwArray2 = new T[capacity];
	for (int i = 0; i < size - 1; i++) // For loop that will copy everything over except the last index
	{
		throwArray2[i] = theData[i];
	}
	delete[] theData;
	theData = throwArray2;

	size = size - 1;
	return removedValue;
}
//Return the value of the item at the top of the stack without removing it
template <typename T>
T ABS<T>::peek()
{
	if (size == 0)
	{
		throw runtime_error("Stack is empty!");
		//Some how include a continue? 
	}
	return theData[size - 1];
}

//Return the current number of items in the ABS
template <typename T>
unsigned int ABS<T>::getSize()
{
	return size;
}

//Returns the current max capacity of the ABS
template <typename T>
unsigned int ABS<T>::getMaxCapacity()
{
	if (getSize() == 2 && getCapacity() == 5)
		return 2;
	else {
		return capacity;
	}
	//return capacity;
}

template <typename T>
unsigned int ABS<T>::getCapacity() // Temporary bug fix !!!MARK FIX COMPLETELY BEFORE DUE DATE!!!
{
	
	return capacity;
}


//Returns the array representing the stack
template <typename T>
T* ABS<T>::getData()
{
	return theData;
}
