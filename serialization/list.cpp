#include "list.h"

#include <cstdio>
#include <random>
#include <unordered_map>
#include <vector>

List::List():
	head(nullptr),
	tail(nullptr),
	count(0) {
}

List::~List() {
	DeleteData();
}

List::List(List&& other):
	head(nullptr),
	tail(nullptr),
	count(0) {

	if (this == &other) {
		return;
	}
	MoveData(std::move(other));
}

List& List::operator=(List&& other) {
	if (this == &other) {
		return *this;
	}

	MoveData(std::move(other));
	return *this;
}

void List::Serialize(FILE* file) const {
	ListNode* node = head;
	size_t dataLength = 0;
	size_t ret = 0;

	while (node) {
		dataLength = node->data.length();
		ret = fwrite(&node, sizeof(ListNode*), 1, file);
		if (ret < 1) {
			return;
		}

		ret = fwrite(&(node->rand), sizeof(ListNode*), 1, file);
		if (ret < 1) {
			return;
		}

		ret = fwrite(&dataLength, sizeof(size_t), 1, file);
		if (ret < 1) {
			return;
		}

		ret = fwrite(node->data.c_str(), sizeof(char), dataLength, file);
		if (ret < dataLength) {
			return;
		}

		node = node->next;
	}
}

void List::Deserialize(FILE* file) {
	// key: an old address, value: a new address
	std::unordered_map<ListNode*, ListNode*> knownAddresses;
	// key: an old address, value: nodes that need to obtain the new address
	std::unordered_map<ListNode*, std::vector<ListNode*>> wantedList;

	size_t dataLength = 0;
	ListNode* node = nullptr;
	ListNode* oldAddress = nullptr;
	ListNode* randAddress = nullptr;
	size_t ret = 0;

	while(!feof(file)) {
		// Read data from the file
		ret = fread(&oldAddress, sizeof(ListNode*), 1, file);
		if (ret < 1) {
			return;
		}

		ret = fread(&randAddress, sizeof(ListNode*), 1, file);
		if (ret < 1) {
			return;
		}

		ret = fread(&dataLength, sizeof(size_t), 1, file);
		if (ret < 1) {
			return;
		}

		node = EmplaceBack();
		if (!node) {
			return;
		}

		node->data.resize(dataLength);

		ret = fread(const_cast<char*>(node->data.c_str()), sizeof(char), dataLength, file);
		if (ret < dataLength) {
			return;
		}

		// Register the new address
		knownAddresses[oldAddress] = node;

		// Try to find the new address of the random node
		auto randIt = knownAddresses.find(randAddress);
		if (randIt != knownAddresses.end()) {
			node->rand = (*randIt).second;
		} else {
			auto& incompleteNodes = wantedList[randAddress];
			incompleteNodes.push_back(node);
		}

		// Fix incomplete nodes
		auto incompleteIt = wantedList.find(oldAddress);
		if (incompleteIt == wantedList.end()) {
			continue;
		}

		auto& incompleteNodes = (*incompleteIt).second;
		for (auto& incompleteNode: incompleteNodes) {
			incompleteNode->rand = node;
		}

		wantedList.erase(incompleteIt);
	}
}

ListNode* List::EmplaceBack(const std::string& data) {
	ListNode* node = new ListNode;
	if (!node) {
		return node;
	}

	node->prev = nullptr;
	node->next = nullptr;
	node->rand = nullptr;
	node->data = data;

	if (tail) {
		node->prev = tail;
		tail->next = node;
		tail = node;
	} else {
		head = tail = node;
	}

	++count;
	return node;
}

void List::ConnectToRandomNode(ListNode* node) const {
	if (!node) {
		return;
	}

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> distr(-1, count - 1);
	int advance = distr(generator);

	node->rand = nullptr;
	if (advance < 0) {
		return;
	}

	node->rand = head;
	for (int i = 0; i < advance; ++i) {
		node->rand = node->rand->next;
	}
}

ListNode* List::First() const {
	return head;
}

ListNode* List::Last() const {
	return tail;
}

void List::DeleteData() {
	ListNode* node = nullptr;
	while (head) {
		node = head;
		head = head->next;
		delete node;
	}

	head = nullptr;
	tail = nullptr;
	count = 0;
}

void List::MoveData(List&& other) {
	DeleteData();

	head = other.head;
	tail = other.tail;
	count = other.count;

	other.head = nullptr;
	other.tail = nullptr;
	other.count = 0;
}
