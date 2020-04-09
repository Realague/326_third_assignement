#include <string>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <wait.h>
#include "Child.h"


class Parent
{
private:
	void mainLoop();
	bool isNumber(std::string);
	void createChild(int, char);
public:
	Parent();
};

Parent::Parent() {
	mainLoop();
}

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

void Parent::createChild(int arraySizeNb, char character) {
	pid_t pid = fork();
	int status;
	if (pid == -1) {
		std::cout << "Error cannot fork" << std::endl;
		exit(84);
	} else if (pid == 0) {
		Child(arraySizeNb, character);
	} else {
		waitpid(pid, &status, 0);
	}
}

bool Parent::isNumber(std::string number) {
	return !number.empty() && std::find_if(number.begin(), number.end(), [](
		unsigned char c) { return !std::isdigit(c); }) == number.end();
}