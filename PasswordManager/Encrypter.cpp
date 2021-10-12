#include "Encrypter.h"

int Encrypter::collatz(int input) {
	return collatz(input, 0);
}

int Encrypter::collatz(int input, int count) {
	if (input == 1) {
		return count;
	}
	else {
		count++;
		input % 2 == 0 ? collatz(input / 2, count) : collatz((input * 3) + 1, count);
	}
}

string Encrypter::encrypt_string(string input) {
	string encrypted = "";
	int previousNumber = 0;

	for (int i = 0; i < input.size(); ++i) {
		int number_of_turns = 0;
		number_of_turns = collatz(int(input[i]) + previousNumber);
		encrypted += to_string(number_of_turns);
		previousNumber = number_of_turns;
	}

	return encrypted;
}