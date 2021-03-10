#include <iostream>
#include <string>

void removeDuplicates(char* str) {
	if (!str) {
		return;
	}

	char* out = str;

	for (const char* in = str; *in != 0; ++in) {
		if (*in == *out) {
			continue;
		}
		*(++out) = *in;
	}

	*(++out) = 0;
}

int main() {
	std::cout << "Enter a string: " << std::endl;

	std::string data;
	std::getline(std::cin, data);

	removeDuplicates(const_cast<char*>(data.c_str()));

	std::cout << std::endl << "The string without duplicated characters is: " << std::endl;
	std::cout << data.c_str() << std::endl;

	return 0;
}
