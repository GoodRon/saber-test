#ifndef LIST_H
#define LIST_H

#include <string>

struct ListNode {
	ListNode* prev;
	ListNode* next;
	ListNode* rand;
	std::string data;
};

class List {
public:
	List();
	~List();

	List(List&& other);
	List& operator=(List&& other);

	void Serialize(FILE* file) const;
	void Deserialize(FILE* file);

	ListNode* EmplaceBack(const std::string& data = std::string());
	void ConnectToRandomNode(ListNode* node) const;

	ListNode* First() const;
	ListNode* Last() const;

private:
	void DeleteData();
	void MoveData(List&& other);

private:
	ListNode* head;
	ListNode* tail;
	int count;
};

#endif // LIST_H
