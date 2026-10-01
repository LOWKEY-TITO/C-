#include <iostream>
#include <stdexcept>

struct Node {
    int data;
    Node* next;

    explicit Node(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;

    Node* tail() const {
        if (!head) {
            return nullptr;
        }

        Node* current = head;
        while (current->next != head) {
            current = current->next;
        }
        return current;
    }

public:
    CircularLinkedList() : head(nullptr) {}

    CircularLinkedList(const CircularLinkedList&) = delete;
    CircularLinkedList& operator=(const CircularLinkedList&) = delete;

    ~CircularLinkedList() {
        if (!head) {
            return;
        }

        Node* current = head->next;
        while (current != head) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        delete head;
        head = nullptr;
    }

    void insertEnd(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            head->next = head;
            return;
        }

        Node* last = tail();
        newNode->next = head;
        last->next = newNode;
    }

    void insertBegin(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            head->next = head;
            return;
        }

        Node* last = tail();
        newNode->next = head;
        last->next = newNode;
        head = newNode;
    }

    void insertSorted(int value) {
        if (!head || value <= head->data) {
            insertBegin(value);
            return;
        }

        Node* current = head;
        while (current->next != head && current->next->data < value) {
            current = current->next;
        }

        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
    }

    void deleteNode(int value) {
        if (!head) {
            throw std::runtime_error("List is empty. Cannot delete.");
        }

        if (head->data == value) {
            if (head->next == head) {
                delete head;
                head = nullptr;
                return;
            }

            Node* last = tail();
            Node* oldHead = head;
            head = head->next;
            last->next = head;
            delete oldHead;
            return;
        }

        Node* previous = head;
        Node* current = head->next;
        while (current != head) {
            if (current->data == value) {
                previous->next = current->next;
                delete current;
                return;
            }

            previous = current;
            current = current->next;
        }

        throw std::runtime_error("Value not found in the list.");
    }

    bool search(int value) const {
        if (!head) {
            return false;
        }

        Node* current = head;
        do {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        } while (current != head);

        return false;
    }

    void reverse() {
        if (!head || head->next == head) {
            return;
        }

        Node* oldHead = head;
        Node* previous = head;
        Node* current = head->next;

        while (current != oldHead) {
            Node* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }

        oldHead->next = previous;
        head = previous;
    }

    void display() const {
        if (!head) {
            std::cout << "List is empty.\n";
            return;
        }

        Node* current = head;
        do {
            std::cout << current->data << " -> ";
            current = current->next;
        } while (current != head);

        std::cout << "(back to head)\n";
    }
};

int main() {
    CircularLinkedList list;

    try {
        list.insertBegin(20);
        list.insertEnd(30);
        list.insertSorted(10);
        list.insertSorted(25);

        std::cout << "List after insertions: ";
        list.display();

        std::cout << "Searching for 25: "
                  << (list.search(25) ? "Found" : "Not found") << '\n';
        std::cout << "Searching for 40: "
                  << (list.search(40) ? "Found" : "Not found") << '\n';

        list.reverse();
        std::cout << "List after reversing: ";
        list.display();

        list.deleteNode(20);
        std::cout << "List after deleting 20: ";
        list.display();
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}