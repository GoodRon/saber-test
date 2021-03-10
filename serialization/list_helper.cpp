#include "list_helper.h"

#include <iostream>

void printList(const List& list) {
	auto node = list.First();
	while (node) {
		std::cout << "Node data: " << node->data << std::endl;

		if (node->rand) {
			std::cout << "Random data: " << node->rand->data << std::endl;
		} else {
			std::cout << "Random data: empty" << std::endl;
		}
		std::cout << "-----" << std::endl;

		node = node->next;
	}
}
