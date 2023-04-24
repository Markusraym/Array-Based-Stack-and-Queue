#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class ABQ
{
	//Variables here
	float scale_factor = 2.0f;
	int capacity; // Maximum capacity 
	int size; //Current size (how many slots are taken up)
	T* theData;

//Prototypes here
public:
	ABQ(); //Default constructor. Capacity set to 1, size set to 0

	ABQ(int capacity); //Constructor with a specified starting capacity

	ABQ(const ABQ& d); // Copy constructor

	ABQ &operator=(const ABQ& d); //Copy assignment operator

	~ABQ(); //Destructor

	void enqueue(T data); //Add a new item to the end of the que and resize if necessary

	T dequeue(); //Remove the item at front of queue, resize if necessary, return value removed. Throw runtime if empty

	T peek(); //Return the value of the item at the front of the que, without removing it. Throw runtime_error if empty

	unsigned int getSize(); //Return size

	unsigned int getMaxCapacity(); //Return capacity

	T* getData(); //Return the data

};
//Believe this is going to be like an array, except you start an take items out from the left side after placing

//Default constructor 
template <typename T>
ABQ<T>::ABQ()
{
	capacity = 1; //Starting out the capacity will just be one
	size = 0; //Starting out its just empty space, there is 0 items in the slots
	theData = new T[capacity]; //new pointer array
 
}

//Constructor with parameters
template <typename T>
ABQ<T>::ABQ(int capacity)
{
	this->capacity = capacity;
	size = 0; 
	theData = new T[capacity];
}

//Copy constructor
template <typename T>
ABQ<T>::ABQ(const ABQ& d)
{
	this->capacity = d.capacity;
	this->size = d.size;
	theData = new T[capacity]; // the deep copy of the array
	for (int i = 0; i < capacity; i++)
	{
		theData[i] = d.theData[i];
	}
	//Credit to professor Fox's example
}

//Assignment operator
template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ& d)
{
	delete[] theData;
	this->capacity = d.capacity;
	this->size = d.size;
	theData = new T[capacity]; // the deep copy of the array
	for (int i = 0; i < capacity; i++)
	{
		theData[i] = d.theData[i];
	}
	//Credit to professor Fox's example 
}

//Destructor
template <typename T>
ABQ<T>::~ABQ()
{
	delete[] theData;
}

//Add a new item to the end of the queue and resize if necessary
template <typename T>
void ABQ<T>::enqueue(T data)
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

//Remove the item at index size (front) of the queue, resize if necessary, and return the value removed. Throw runtime error if empty
template <typename T>
T ABQ<T>::dequeue()
{
	
	//Check if stack is empty, if so, throw a runtime error
	if (size == 0)
	{
		throw runtime_error("The queue is empty!");
	}
	//Save the first index as a variable before removing it
	T removedValue = theData[0];

	//Check if the array is half full, and if so, make a new array with half the size. 
	float percentFilled = (float)(size-1) / (float)capacity;
	if (percentFilled < (1 / scale_factor))
	{
		T* throwArray = new T[(int)capacity / (int)scale_factor]; //Make a new array half the size

		for (int i = 0; i < size-1; i++)
		{
			throwArray[i] = theData[i+1];
		}
		delete[] theData; //Delete the previous stuff
		theData = throwArray; // Point the pointer to the new memory location
		capacity = capacity / scale_factor; //Update the capacity
	}
	else {
		T* throwArray = new T[size-1]; //If not half full, make a new array with one digit smaller

		for (int i = 0; i < size-1; i++) //Copy over everything except the last digit
		{
			throwArray[i] = theData[i+1];
		}
		delete[] theData; //Delete the previous stuff
		theData = throwArray; // Point the pointer to the new memory location
	}
	size = size - 1; //decrement the size value after computing function
	return removedValue; //return the deleted value
}

//Return the value of the item at the front of the queue, without removing it
template <typename T>
T ABQ<T>::peek()
{
	if (size == 0)
	{
		throw runtime_error("Queue is empty!");
	}
	return theData[0]; //May be size - 1 and not 0!
}

//Returns the current number of its in the ABQ
template <typename T>
unsigned int ABQ<T>::getSize()
{
	return size;
}

//Return the current max capacity of the ABQ
template <typename T>
unsigned int ABQ<T>::getMaxCapacity()
{
	return capacity;
}

//Return the array representing the queue 
template <typename T>
T* ABQ<T>::getData()
{
	return theData;
}