#include "list.h"
#include "list_helper.h"

#include <cstdio>
#include <iostream>

int main() {

	List list;
	list.EmplaceBack("One");
	list.EmplaceBack("Two");
	list.EmplaceBack("Three");
	list.EmplaceBack("Four");
	list.EmplaceBack("Five");
	list.EmplaceBack("The Last One");

	auto node = list.First();
	while (node) {
		list.ConnectToRandomNode(node);
		node = node->next;
	}

	FILE* file = fopen("serialized_data", "wb");
	if (!file) {
		std::cout << "Can't open file!" << std::endl;
		return -1;
	}

	list.Serialize(file);

	fclose(file);

	printList(list);

	return 0;
}
