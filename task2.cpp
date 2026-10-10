#include <iostream>
#include <string>
using namespace std;

struct RepairNode
{
    int requestID;
    string customerName;
    string device;
    int priority;
    RepairNode* next;
};

class PriorityQueue
{
private:
    RepairNode* front;
    RepairNode* rear;

public:
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    void Add(RepairNode* request)
    {
        request->next = nullptr;

        if (front == nullptr)
        {
            front = rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            RepairNode* current = front;

            while (current->next != nullptr &&
                   current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == nullptr)
                rear = request;
        }
    }

    RepairNode* Remove()
    {
        if (front == nullptr)
            return nullptr;

        RepairNode* request = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        request->next = nullptr;
        return request;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    void PrintQueue()
    {
        RepairNode* current = front;

        while (current != nullptr)
        {
            cout << "Request ID: " << current->requestID << endl;
            cout << "Customer: " << current->customerName << endl;
            cout << "Device: " << current->device << endl;
            cout << "Priority: " << current->priority << endl;
            cout << "------------------------" << endl;

            current = current->next;
        }
    }

    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            RepairNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }
};

int main()
{
    PriorityQueue repairs;
    int choice;

    do
    {
        cout << "\nService Centre Management System\n";
        cout << "1. Add Repair Request\n";
        cout << "2. Process Repair Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            RepairNode* request = new RepairNode;

            cout << "Enter Request ID: ";
            cin >> request->requestID;

            cin.ignore(10000, '\n');

            cout << "Enter Customer Name: ";
            getline(cin, request->customerName);

            cout << "Enter Device Name: ";
            getline(cin, request->device);

            cout << "Enter Priority (1-3): ";
            cin >> request->priority;

            if (request->priority < 1 || request->priority > 3)
            {
                cout << "Invalid priority.\n";
                delete request;
            }
            else
            {
                repairs.Add(request);
                cout << "Repair request added.\n";
            }
        }
        else if (choice == 2)
        {
            RepairNode* request = repairs.Remove();

            if (request == nullptr)
            {
                cout << "No repair requests available.\n";
            }
            else
            {
                cout << "Processing Repair Request\n";
                cout << "Customer: " << request->customerName << endl;
                cout << "Device: " << request->device << endl;
                cout << "Priority: " << request->priority << endl;

                delete request;
            }
        }
        else if (choice == 3)
        {
            if (repairs.IsEmpty())
                cout << "No pending requests.\n";
            else
                repairs.PrintQueue();
        }
        else if (choice == 4)
        {
            if (repairs.IsNotEmpty())
                cout << "Queue is not empty.\n";
            else
                cout << "Queue is empty.\n";
        }
        else if (choice == 5)
        {
            cout << "Program ended.\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}