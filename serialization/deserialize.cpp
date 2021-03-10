#include "list.h"
#include "list_helper.h"

#include <cstdio>
#include <iostream>

int main() {
	FILE* file = fopen("serialized_data", "rb");
	if (!file) {
		std::cout << "Can't open file!" << std::endl;
		return -1;
	}

	List list;
	list.Deserialize(file);

	fclose(file);

	printList(list);

	return 0;
}
