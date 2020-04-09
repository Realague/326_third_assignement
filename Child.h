#include<string>
#include <iostream>

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
	free(array);
}

void Child::findCharacter() {
	int occurrence = 0;
	while (occurrence == 0) {
		for (int i = 0; i != size; i++) {
			if (array[i] == character) {
				occurrence++;
			}
		}
	}
	std::cout << occurrence << " found in the array" << std::endl;
}