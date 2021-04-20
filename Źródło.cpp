#include <iostream>
#include <list>
#include <string>
using namespace std;

#define COMMAND_ARR_SIZE 13

struct Node
{
	int value;
	int inQueue = 0;
	Node* next;
	Node* previous;
};

void ADD_BEG(Node** head, Node** tail, int value, int& size)
{
	//creating new
	Node* newNode = new Node;
	newNode->value = value;
	newNode->previous = NULL;
	newNode->next = NULL;
	if (*tail == NULL) *tail = newNode;
	//updating last
	if (*head != NULL)
	{
		(*head)->previous = newNode;
		newNode->next = *head;
	}
	*head = newNode;
	size++;
}

void ADD_END(Node** head, Node** tail, int value, int& size)
{
	//creating new
	Node* newNode = new Node;
	newNode->value = value;
	newNode->next = NULL;
	newNode->previous = NULL;
	if (*head == NULL) *head = newNode;
	//updating last
	if (*tail != NULL)
	{
		(*tail)->next = newNode;
		newNode->previous = *tail;
	}
	*tail = newNode;
	size++;
}

void DEL_BEG(Node** head, Node** tail, Node** front, Node** rear, int& size, int& count)
{
	if (*head == NULL) return;
	//queue management
	if ((*head)->inQueue == 1) count--;
	if (*front == *head || *rear == *head)
	{
		//when there is only one element
		if (count == 1)
		{
			*rear = NULL;
			*front = NULL;
		}
		else if (*head == *front)
		{
			*front = *tail;
		}
		else if (*head == *rear)
		{
			*rear = (*rear)->next;
		}
	}
	//deletion
	if (*head == *tail)
	{
		Node* old = *head;
		*head = nullptr;
		*tail = nullptr;
		delete old;
	}
	else
	{
		Node* old = *head;
		*head = (*head)->next;
		(*head)->previous = NULL;
		delete old;
	}
	size--;
}

void DEL_END(Node** head, Node** tail, Node** front, Node** rear, int& size, int& count)
{
	if (*tail == NULL) return;
	//queue management
	if ((*tail)->inQueue == 1) count--;
	if (*front == *tail || *rear == *tail)
	{
		//when there is only one element
		if (count == 1)
		{
			*rear = NULL;
			*front = NULL;
		}
		else if (*tail == *front)
		{
			*front = (*front)->previous;
		}
		else if (*tail == *rear)
		{
			*rear = *head;
		}
	}
	//deletion
	if (*head == *tail)
	{
		Node* old = *head;
		*head = nullptr;
		*tail = nullptr;
		delete old;
	}
	else
	{
		Node* old = *tail;
		*tail = (*tail)->previous;
		(*tail)->next = NULL;
		delete old;
	}
	size--;
}

void SIZE(int size)
{
	cout << size << endl;
}

void COUNT(int count)
{
	cout << count << endl;
}

void GARBAGE_SOFT(Node** head)
{
	if (*head == NULL) return;
	Node* curr = *head;
	Node* next;
	while (curr != NULL)
	{
		if (curr->inQueue == 0) curr->value = 0;
		next = curr->next;
		curr = next;
	}
}

void GARBAGE_HARD(Node** head, Node** tail, int& size)
{
	if (*head == NULL) return;
	Node* curr = *head;
	Node* next;
	while (curr != NULL)
	{
		if (curr->inQueue == 0)
		{
			//one element
			if (*head == *tail)
			{
				Node* old = *head;
				*head = nullptr;
				*tail = nullptr;
				delete old;
				size--;
				return;
			}
			//at the beginning
			else if (curr == *head)
			{
				Node* old = *head;
				*head = (*head)->next;
				(*head)->previous = NULL;
				delete old;
				next = *head;
				size--;
			}
			else if (curr == *tail)
			{
				Node* old = *tail;
				*tail = (*tail)->previous;
				(*tail)->next = NULL;
				delete old;
				size--;
				return;
			}
			else
			{
				Node* old = curr;
				curr->next->previous = curr->previous;
				curr->previous->next = curr->next;
				next = curr->next;
				delete old;
				size--;
			}
		}
		else next = curr->next;
		curr = next;
	}
}

void PRINT_FORWARD(Node* head)
{
	if (head == NULL)
	{
		cout << "NULL" << endl;
		return;
	}
	Node* curr = head;
	Node* next;
	while (curr != NULL)
	{
		cout << curr->value << " ";
		next = curr->next;
		curr = next;
	}
	cout << endl;
}

void PRINT_BACKWARD(Node* tail)
{
	if (tail == NULL)
	{
		cout << "NULL" << endl;
		return;
	}
	Node* curr = tail;
	Node* prev;
	while (curr != NULL)
	{
		cout << curr->value << " ";
		prev = curr->previous;
		curr = prev;
	}
	cout << endl;
}

void PUSH(Node** head, Node** tail, Node** front, Node** rear, int value, int& size, int& count)
{
	//when the list is empty
	if (size == NULL)
	{
		ADD_END(head, tail, value, size);
		*front = *head;
		*rear = *tail;
		(*tail)->inQueue = 1;
	}
	//when the queue is full
	else if (size == count)
	{
		//when pointers don't cross
		if ((*front == *tail) && (*rear == *head))
		{
			ADD_BEG(head, tail, value, size);
			*rear = *head;
			(*head)->inQueue = 1;
		}
		//when they cross
		else
		{
			Node* newNode = new Node;
			newNode->inQueue = 1;
			newNode->value = value;
			newNode->next = *rear;
			newNode->previous = *front;
			(*rear)->previous = newNode;
			(*front)->next = newNode;
			size++;
		}
	}
	//when there is space
	else
	{
		//empty queue
		if (count == 0)
		{
			*rear = *tail;
			*front = *tail;
			(*rear)->value = value;
			(*rear)->inQueue = 1;
		}
		else
		{
			if (*rear == *head)
			{
				*rear = *tail;
				(*rear)->value = value;
				(*rear)->inQueue = 1;
			}
			else
			{
				*rear = (*rear)->previous;
				(*rear)->value = value;
				(*rear)->inQueue = 1;
			}
		}
	}
	count++;
}

void POP(Node** head, Node** tail, Node** front, Node** rear, int& count)
{
	//when the queue is empty
	if (count == 0)
	{
		cout << "NULL" << endl;
		return;
	}
	//when there is only one element
	if (count == 1)
	{
		cout << (*front)->value << endl;
		*rear = NULL;
		*front = NULL;
	}
	//when front is at the beginning 
	else if (*front == *head)
	{
		cout << (*front)->value << endl;
		*front = *tail;
	}
	else
	{
		cout << (*front)->value << endl;
		*front = (*front)->previous;
	}
	count--;
}

void PRINT_QUEUE(Node* head, Node* tail, Node* front, Node* rear)
{
	if (front == NULL || rear == NULL)
	{
		cout << "NULL" << endl;
		return;
	}
	Node* curr = front;
	Node* previous;
	while (curr != rear->previous || curr != NULL)
	{
		cout << curr->value << " ";
		if (curr == rear || rear == front)
		{
			cout << endl;
			return;
		}
		if (curr == head) previous = tail;
		else previous = curr->previous;
		curr = previous;
	}
	cout << endl;
}

int Choice(const string command)
{
	string arr[13] = { "ADD_BEG", "ADD_END", "DEL_BEG", "DEL_END", "PRINT_FORWARD",
	"PRINT_BACKWARD", "SIZE", "PUSH", "POP", "PRINT_QUEUE", "COUNT", "GARBAGE_SOFT",
	"GARBAGE_HARD" };

	for (int i = 0; i < COMMAND_ARR_SIZE; i++)
	{
		if (command == arr[i]) return i;
	}
	return -1;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string command;
	Node* head = NULL;
	Node* tail = NULL;
	Node* front = NULL;
	Node* rear = NULL;
	int value;
	int count = 0;
	int size = 0;

	while (cin >> command)
	{
		switch (Choice(command))
		{
		case 0:
			cin >> value;
			ADD_BEG(&head, &tail, value, size);
			break;
		case 1:
			cin >> value;
			ADD_END(&head, &tail, value, size);
			break;
		case 2:
			DEL_BEG(&head, &tail, &front, &rear, size, count);
			break;
		case 3:
			DEL_END(&head, &tail, &front, &rear, size, count);
			break;
		case 4:
			PRINT_FORWARD(head);
			break;
		case 5:
			PRINT_BACKWARD(tail);
			break;
		case 6:
			SIZE(size);
			break;
		case 7:
			cin >> value;
			PUSH(&head, &tail, &front, &rear, value, size, count);
			break;
		case 8:
			POP(&head, &tail, &front, &rear, count);
			break;
		case 9:
			PRINT_QUEUE(head, tail, front, rear);
			break;
		case 10:
			COUNT(count);
			break;
		case 11:
			GARBAGE_SOFT(&head);
			break;
		case 12:
			GARBAGE_HARD(&head, &tail, size);
			break;
		case -1:
			cout << "Wrong command" << endl;
			break;
		}
	}
}

//proper memory dealloc