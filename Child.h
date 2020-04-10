//Julien Delane William Murray
//main.cpp Parent.h Child.h
//Child class declaration and logic
#include<string>
#include <iostream>

/*********************************************************************************************
 * Child
 * Child process. Allocates and constructs random character array of the constructor param.
 * Searches for number of param character occurences in the constructed character array.
*********************************************************************************************/
class Child
{
private:
	int size;
	char *array;
	char character;
	void findCharacter();
public:
	Child(int size, char c);
    ~Child();
};

//Constructor
//param: size -- size of the array to be created
//		 c    -- character to be searched for
Child::Child(int size, char c):
size(size), character(c) {
	srand(time(NULL));
	array = (char *)malloc(sizeof(char) * size);
	for (int i = 0; i != size; i++) {
		array[i] = std::rand() % 26 + 'A';
	}
	findCharacter();
}

Child::~Child() {
	//deallocate memory
	free(array);
}

void Child::findCharacter() {
	int occurrence = 0;
	//Injected bug. Program will lock if character cannot be found, but process can be terminated with kill command
	while (occurrence == 0) {
		for (int i = 0; i != size; i++) {
			if (array[i] == character) {
				occurrence++;
			}
		}
	}
	std::cout << occurrence << " found in the array" << std::endl;
}