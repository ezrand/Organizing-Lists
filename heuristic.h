#pragma once

#include "SelfOrderedListADT.h"
#include "llist.h"
#include "link.h"

template <typename E>
class heuristic : public SelfOrderedListADT<E> {
	LList <E>* list;
	int comparisons;
	int position; 
	int heur;

public:
	//Default constructor/destructor
	heuristic() {
		list = new LList <E>();
	}
	~heuristic() { list->clear();  }

	//Look for 'it'.  If found return true and execute the self-ordering
	//heuristic used for ordering the list: count, move-to-front, or transpose.
	//Increments the compare instance variable every time it compares 'it' to
	//other members of the list. Returns true if 'it' is found.
	bool find(const E& it)
	{
		bool found{ false };
		//if list is empty, add "it" to the list, setfrequency to 0, setting the position does not really matter because their is nothing to reorder yet
		//however it needs to be set for the function to work
		if (size() == 0)
		{
			add(it);
			list->setFrequency(0);
			position = (size() - 1);
			found = false;
			return found;
		}
		//move to start to check every variable
		list->moveToStart();
		//if found, increments the frequency
		//for loop to check entire list
		for (int i = 0; i < size(); i++)
		{
			//increment comparisons for every loop done
			comparisons++;
			//if the value in the list matches "it", it means that "it" already exists, so we increment the frequency up by 1, set found to true, and break the loop to stop it
			if (list->getValue() == it)
			{
				position = i;
				list->incrementFrequency();
				found = true;
				break;
			}
			else //if the value does not match it, move to the next value to check
			{
				list->next();
			}
		}
		//if not found, add(it) and then increment the frequency, which to start will be 0
		if (found == false)
		{
			add(it);
			list->setFrequency(0);
			position = (size() - 1);
		}
		//swtich statement to call the correct heuristic, whichever heuristic were demonstrating is set in main, and called here
		switch (heur)
		{
		case 1:
			mtfOrder(position);
			break;
		case 2:
			cOrder(position);
			break;
		case 3:
			tOrder(position, found);
			break;
		}
		return found;
	}

	//Called by find if 'it' is not in the list. Adds the new 'it' to the list
	//Can also be called independently when initially loading the list with
	//unique values and when you want to load the list in the order 'it' is 
	//read without your re-order method being called (or the number of compares
	//being incremented.
	void add(const E& it)
	{
		list->append(it);
	}
	//return the number of comparisons for main to show
	int getCompares() const
	{
		return comparisons; 
	}
	//size of list return statement used in functinos'.p
	int size() const
	{
		return list->length(); 
	}

	//Print the list
	//In order print of the list.  printlist() prints the entire list
	//whereas printlist(n) prints n nodes.
	void printlist()
	{
		//string to display the correct heuristic used
		string heurOut;
		switch (getHeur())
		{
		case 1:
			heurOut = "Move to Front ";
			break;
		case 2:
			heurOut = "Count ";
			break;
		case 3:
			heurOut = "Transpose ";
			break;
		} //Display the correct size of list as well as the number of comparisons made
		cout << heurOut << "heuristic: Size of list : " << size() << endl; 
		cout << "Number of comparisons: " << getCompares() << endl; 
		//move to the strat of the list so that the list can be outputted along with its frequency
		list->moveToStart();
		for (int i = 0; i < size(); i++)
		{
			//list the letter or word stored, along with the frequency, then move to the next variable
			cout << list->getValue() << "--" << list->getFrequency() << "  ";
			list->next();
		}
		cout << endl << endl;
		//after printing the list clear it out so that the next set of letters or words can be read in
		list->clear();
	}
	//this is the same exact logic as the previous printList, however, the n variable read in is used to only display the first 10 variables
	void printlist(int n)
	{
		string heurOut;
		switch (getHeur())
		{
		case 1:
			heurOut = "Move to Front ";
			break;
		case 2:
			heurOut = "Count ";
			break;
		case 3:
			heurOut = "Transpose ";
			break;
		}
		cout << heurOut << "heuristic: Size of list : " << size() << endl;
		cout << "Number of comparisons: " << getCompares() << endl;
		list->moveToStart();
		for (int i = 0; i < n; i++)
		{
			cout << list->getValue() << "--" << list->getFrequency() << "  ";
			list->next();
		}
		cout << endl << endl;
		list->clear();
	}	
	//set and get function for which heuristic is being deomstrated
	void setHeur(int h)
	{
		heur = h;
	}

	int getHeur()
	{
		return heur;
	}
	void mtfOrder(int pos)
	{
		//create a temporary variable and int to transfer data
		E temp;
		int tempF;
		//move to the position that the accessed variable was at
		list->moveToPos(pos);
		//read the data from the position into the temporary variable
		tempF = list->getFrequency();
		temp = list->remove();
		//move to the start of the list
		list->moveToStart();
		//insert the temporary variable and set the frequency
		list->insert(temp); 
		list->setFrequency(tempF);
	}

	void cOrder(int pos)
	{
		//create a temporary variable and int to transfer data
		E temp;
		int tempF;
		//move to the position that the accessed variable was at
		list->moveToPos(pos);
		//for loop increment through the list
		for (int i = 0; i < pos; i++)
		{
			//helper compare function
			if (list->compare(list->currPos()))
			{
				//read the data from the position into the temporary variable
				tempF = list->getFrequency();
				temp = list->remove();
				//because of the nature of compare, move to the previous variable to insert the data, this way the highest frequency is moved to the front
				list->prev();
				list->insert(temp);
				list->setFrequency(tempF);
			}
		}

	}

	void tOrder(int pos, bool f)
	{
		//create a temporary variable and int to transfer data
		E temp;
		int tempF;
		//move to the position that the accessed variable was at
		list->moveToPos(pos);
		//by using the bool from find, i can determine if the variable was found, and thus needs to be transposed
		//however the variables that were added to the end of the list do not get moved and stay at the end
		if (f)
		{
			//same logic copied from count\
			//because the variable is flipped with the one before it, all you need to do is set the temporary variable, move to the previous node, and insert it
			tempF = list->getFrequency();
			temp = list->remove();
			list->prev();
			list->insert(temp);
			list->setFrequency(tempF);
		}
	}
};