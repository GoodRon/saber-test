#include <iostream>

void printBinary(long long value) {
	unsigned long long mask = 1;
	mask <<= (sizeof(mask) * 8 - 1);

	// Skip zeros for positive values (optional part)
	while (!(value & mask) && (mask > 1)) {
		mask >>= 1;
	}

	std::cout << "b";

	while (mask != 0) {
		if (value & mask) {
			std::cout << "1";
		} else {
			std::cout << "0";
		}

		mask >>= 1;
	}
	std::cout << std::endl;
}

int main() {
	long long value = 0;

	std::cout << "Enter signed integer value:" << std::endl;
	std::cin >> value;

	std::cout << std::endl << "The binary representation of " << value << " is: " << std::endl;
	printBinary(value);	

	return 0;
}
