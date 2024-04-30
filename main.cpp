#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

class PriorityQueue{
public:
    struct Node{
        int data;
        int priority;
        Node* next;
        Node(int value, int prio) : data(value), priority(prio), next(nullptr) {}
    };

    Node* head;
public:
    PriorityQueue() : head(nullptr) {}
    ~PriorityQueue(){
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool empty() const {
        return head == nullptr;
    }

    void enqueue(int value, int priority) {
        Node* newNode = new Node(value, priority);
        if (head == nullptr || priority > head->priority) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->priority >= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    int dequeue() {
        if(head == nullptr){
            cout<<"Kolejka jest pusta."<<endl;
            return -1; // lub inną wartość reprezentującą błąd
        }
        Node* temp = head;
        int value = temp->data;
        head = head->next;
        delete temp;
        return value;
    }

    int size() const {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    bool modifyPriority(int value, int newPriority) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                current->priority = newPriority;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int peek() const {
        if (head == nullptr) {
            cout << "Kolejka jest pusta." << endl;
            return -1; // lub inną wartość reprezentującą błąd
        }
        return head->data;
    }
};

int main() {
    int tab[] = {1000,10000,100000};
    for(int data : tab){
        PriorityQueue queue;
        int end = data;
        int mid = data/2;
        int first = 0;
        cout<<"-----------------------"<<data<<"-----------------------"<<endl;
        //Dodanie elementow do kolejki
        auto start = high_resolution_clock::now();
        for (int i = 0; i < data; i++) {
            queue.enqueue(i, i); // dla uproszczenia priorytet równy wartości
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cout << "Dodanie "<<data<<" elementów zajęło: " << duration.count() << " nanosekund."<<endl;

        //USUWANIE z najwyższym priorytetem
        auto start2 = high_resolution_clock::now();
        queue.dequeue();
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
        cout << "Usunięcie elementu o najwyższym priorytecie zajęło: " << duration2.count() << " nanosekund."<<endl;

        //ZWROT ROZMIARU
        auto start3 = high_resolution_clock::now();
        int size = queue.size();
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<nanoseconds>(stop3 - start3);
        cout << "Zwrot rozmiaru zajęło: " << duration3.count() << " nanosekund."<<endl;

        //MODYFIKACJA PRIORYTETU
        auto start4 = high_resolution_clock::now();
        queue.modifyPriority(first, end); // zmiana priorytetu pierwszego elementu na ostatnią wartość
        auto stop4 = high_resolution_clock::now();
        auto duration4 = duration_cast<nanoseconds>(stop4 - start4);
        cout << "Modyfikacja priorytetu zajęła: " << duration4.count() << " nanosekund."<<endl;

        //PEEK
        auto start5 = high_resolution_clock::now();
        int peekValue = queue.peek();
        auto stop5 = high_resolution_clock::now();
        auto duration5 = duration_cast<nanoseconds>(stop5 - start5);
        cout << "Podejrzenie elementu o najwyższym priorytecie zajęło: " << duration5.count() << " nanosekund."<<endl;

        cout<<endl<<endl;
    }
    return 0;
}
