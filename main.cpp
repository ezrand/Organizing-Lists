#include <iostream>
#include <string> 
#include <fstream>
#include <istream> 
#include "heuristic.h"
#include "llist.h"

using namespace std;

int main()
{
	heuristic <char> moveToFront; //creating the char template
	moveToFront.setHeur(1); //setting the heuristic that the chars will be organized by
	//adding the letters from the instructions
	moveToFront.add('A');
	moveToFront.add('B');
	moveToFront.add('C');
	moveToFront.add('D');
	moveToFront.add('E');
	moveToFront.add('F');
	moveToFront.add('G');
	moveToFront.add('H');

	//finding if a specific letter is in the moveToFront
	moveToFront.find('F');
	moveToFront.find('D');
	moveToFront.find('F');
	moveToFront.find('G');
	moveToFront.find('E');
	moveToFront.find('G');
	moveToFront.find('F');
	moveToFront.find('A');
	moveToFront.find('D');
	moveToFront.find('F');
	moveToFront.find('G');
	moveToFront.find('E');
	moveToFront.find('H');
	moveToFront.find('I');

	//printing out the list 
	moveToFront.printlist(); 


	heuristic <char> count;
	//creating the char template
	count.setHeur(2); //setting the heuristic that the chars will be organized by
	//adding the letters from the instructions
	count.add('A');
	count.add('B');
	count.add('C');
	count.add('D');
	count.add('E');
	count.add('F');
	count.add('G');
	count.add('H');

	//finding if a specific letter is in the count
	count.find('F');
	count.find('D');
	count.find('F');
	count.find('G');
	count.find('E');
	count.find('G');
	count.find('F');
	count.find('A');
	count.find('D');
	count.find('F');
	count.find('G');
	count.find('E');
	count.find('H');
	count.find('I');

	count.printlist();


	heuristic <char> trans;
	//creating the char template
	trans.setHeur(3); //setting the heuristic that the chars will be organized by
	//adding the letters from the instructions
	trans.add('A');
	trans.add('B');
	trans.add('C');
	trans.add('D');
	trans.add('E');
	trans.add('F');
	trans.add('G');
	trans.add('H');

	//finding if a specific letter is in the trans
	trans.find('F');
	trans.find('D');
	trans.find('F');
	trans.find('G');
	trans.find('E');
	trans.find('G');
	trans.find('F');
	trans.find('A');
	trans.find('D');
	trans.find('F');
	trans.find('G');
	trans.find('E');
	trans.find('H');
	trans.find('I');
	//pritning the list
	trans.printlist();

	//using the heuristics on words from a file
	//variable implementation
	string word; 
	int n = 10;
	fstream infile;
	//opening the file
	infile.open("test.txt");
	//creating the string template
	heuristic <string> mtfString;
	//setting the heuristic to organize
	mtfString.setHeur(1);
	//while reading in from the file, any word read in, is put into the find function
	while (infile >> word)
	{
		mtfString.find(word);
	}
	//n is set to 10, the first ten nodes will be printed out
	mtfString.printlist(n);
	//clearing the string to be used in the next heuristic, and closing the file to reset
	word.clear();
	infile.close();


	//open the file, set the heuristic to be used, and creating the string template
	infile.open("test.txt");
	heuristic <string> cString;
	cString.setHeur(2);
	//while reading in from the file, any word read in, is put into the find function
	while (infile >> word)
	{
		cString.find(word);
	}
	//n is set to 10, the first ten nodes will be printed out
	cString.printlist(n);
	//clearing the string to be used in the next heuristic, and closing the file to reset
	word.clear();
	infile.close();

	//open the file, set the heuristic to be used, and creating the string template
	infile.open("test.txt");
	heuristic <string> tString;
	tString.setHeur(3);
	//while reading in from the file, any word read in, is put into the find function
	while (infile >> word)
	{
		tString.find(word);
	}
	//n is set to 10, the first ten nodes will be printed out
	tString.printlist(n);
	//clearing the string to be used in the next heuristic, and closing the file to reset
	word.clear();
	infile.close();


	system("pause");
	return 0;
}