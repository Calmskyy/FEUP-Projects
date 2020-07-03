#include "Utilities.h"

unsigned int readInputNumber() { // used to input a number, not restricted by menu options

	int numberInput;

	while (1) {
		std::cin >> numberInput;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(200, '\n');
			std::cout << "Please input a valid number: ";
			continue;
		}
		if (numberInput < 0) {
			std::cin.clear();
			std::cin.ignore(200, '\n');
			std::cout << "Please input a positive number: ";
			continue;
		}
		break;
	}

	return (unsigned int)numberInput;
}

double readDoubleInputNumber(double lowNumber, double highNumber) { // used to input a number (double), restricted by menu options

	double numberInput;

	while (1) {
		std::cin >> numberInput;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(200, '\n');
			std::cout << "Please input a valid number: ";
			continue;
		}
		if (numberInput < lowNumber || numberInput > highNumber) {
			std::cout << "Please input a single number between " << lowNumber << " and " << highNumber << " (inclusive): ";
			std::cin.clear();
			std::cin.ignore(200, '\n');
			continue;
		}
		break;
	}
	return numberInput;
}


int readInputNumber(int lowNumber, int highNumber) { // used to input a number, restricted by menu options

	int numberInput;

	while (1) {
		std::cin >> numberInput;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(200, '\n');
			std::cout << "Please input a valid number: ";
			continue;
		}
		if (numberInput < lowNumber || numberInput > highNumber) {
			std::cout << "Please input a single number between " << lowNumber << " and " << highNumber << " (inclusive): ";
			std::cin.clear();
			std::cin.ignore(200, '\n');
			continue;
		}
		break;
	}
	return numberInput;
}
