//Julien Delane William Murray
//main.cpp Parent.h Child.h
//Parent class declaration and logic
#include <string>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <wait.h>
#include "Child.h"

/*********************************************************************************************
 * Parent
 * Parent process of the application, handles user input and child process creation
*********************************************************************************************/
class Parent
{
private:
	void mainLoop();
	bool isNumber(std::string);
	void createChild(int, char);
public:
	Parent();
};

//Intialize
Parent::Parent() {
	mainLoop();
}

//Event handler
void Parent::mainLoop() {
	std::cout << "You can exit the programme by typing: QUIT" << std::endl;
	while (true) {
		std::string  arraySize;
		std::string  character;
		int arraySizeNb;
		
		do {
			std::cout << "Choose a size for the array of character: " << std::endl;
			std::cin >> arraySize;
			if (arraySize == "QUIT") {
				return;
			}
		} while (!isNumber(arraySize));
		do {
			std::cout << "Choose a character to find: " << std::endl;
			std::cin >> character;
			if (character == "QUIT") {
				return;
			}
		} while (character.size() != 1 || !std::isupper(character.at(0)));
		arraySizeNb = std::stoi(arraySize);
		createChild(arraySizeNb, character.at(0));
	}
}

//helper method to fork child processes
void Parent::createChild(int arraySizeNb, char character) {
	pid_t pid = fork();
	int status;
	if (pid == -1) {
		std::cout << "Error cannot fork" << std::endl;
		exit(84);
	} else if (pid == 0) {
		//if no problems forking, create the child process
		Child(arraySizeNb, character);
	} else {
		//wait for bad process to die
		waitpid(pid, &status, 0);
	}
}

//helper method for converting string to a digit
bool Parent::isNumber(std::string number) {
	//will return true if the stirng is not empty, and if each character of number is a digit
	return !number.empty() && std::find_if(number.begin(), number.end(), [](
		unsigned char c) { return !std::isdigit(c); }) == number.end();
}