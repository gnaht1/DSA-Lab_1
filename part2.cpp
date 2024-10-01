// STT: ?
// Full Name: Nguyen Phan Huynh Thang
// Session 01 - Exercise 01
// Notes or Remarks:
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
using namespace std;

class Node
{
public:
    int data;     // Digit value
    Node *next;   // Pointer to the next node
    Node *random; // Pointer for random reference

    Node(int value) : data(value), next(nullptr), random(nullptr) {}
};

class LinkedList
{
public:
    Node *head;

    LinkedList() : head(nullptr) {}

    // Function to insert a new node at the end of the linked list
    void insert(int value)
    {
        Node *newNode = new Node(value);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Function to display the linked list
    void display()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data;
            temp = temp->next;
            if (temp)
                cout << " -> ";
        }
        cout << endl;
    }

    // Function to add two linked lists
    LinkedList add(LinkedList &other)
    {
        LinkedList result;
        Node *p1 = this->head;
        Node *p2 = other.head;
        int carry = 0;

        // Loop until both linked lists and carry are processed
        while (p1 != nullptr || p2 != nullptr || carry)
        {
            int sum = carry; // Start with carry

            // Add value from the first list if available
            if (p1 != nullptr)
            {
                sum += p1->data;
                p1 = p1->next;
            }

            // Add value from the second list if available
            if (p2 != nullptr)
            {
                sum += p2->data;
                p2 = p2->next;
            }

            carry = sum / 10;        // Calculate carry for the next digit
            result.insert(sum % 10); // Insert unit digit into the result
        }

        return result; // Return the resulting linked list
    }

    // Function to automatically insert random values into the linked list
    void insertRandomValues()
    {
        // Seed random number generator
        srand(static_cast<unsigned int>(time(0)));

        // Generate a random number of entries in the range [39, 59]
        int numEntries = rand() % 21 + 39; // (0-20) + 39 = [39, 59]

        for (int i = 0; i < numEntries; i++)
        {
            // Generate a random value in the range [-99, 99]
            int randomValue = rand() % 199 - 99; // (0-198) - 99 = [-99, 99]
            insert(randomValue);
        }
    }

    // Function to swap nodes by their values
    void swapNodes(int value1, int value2)
    {
        if (value1 == value2)
        {
            cout << "Values are the same, no need to swap.\n";
            return;
        }

        Node *prev1 = nullptr, *prev2 = nullptr;
        Node *node1 = head, *node2 = head;

        // Find the first node and its previous node
        while (node1 && node1->data != value1)
        {
            prev1 = node1;
            node1 = node1->next;
        }

        // Find the second node and its previous node
        while (node2 && node2->data != value2)
        {
            prev2 = node2;
            node2 = node2->next;
        }

        // If either value is not found, return
        if (!node1 || !node2)
        {
            cout << "One or both values not found in the list.\n";
            return;
        }

        // If node1 is not the head node
        if (prev1)
        {
            prev1->next = node2; // Connect prev1 to node2
        }
        else
        {
            head = node2; // Update head if node1 is the head
        }

        // If node2 is not the head node
        if (prev2)
        {
            prev2->next = node1; // Connect prev2 to node1
        }
        else
        {
            head = node1; // Update head if node2 is the head
        }

        // Swap the next pointers
        Node *temp = node1->next;  // Store next of node1
        node1->next = node2->next; // Node1 points to Node2's next
        node2->next = temp;        // Node2 points to Node1's next
    }

    // Function to remove the N-th node from the end of the list
    void removeNthFromEnd(int n)
    {
        Node *first = head;
        Node *second = head;

        // Move first pointer n steps ahead
        for (int i = 0; i < n; i++)
        {
            if (first == nullptr)
            {
                cout << "N is larger than the list length. No node removed.\n";
                return;
            }
            first = first->next;
        }

        // Move first to the end, maintaining the gap
        Node *prev = nullptr; // To keep track of the previous node for deletion
        while (first)
        {
            prev = second;         // Keep track of the previous node
            second = second->next; // Move second pointer
            first = first->next;   // Move first pointer
        }

        // Remove the N-th node from the end
        if (second == head)
        {
            // If the node to be removed is the head
            head = head->next;
        }
        else if (prev)
        {
            prev->next = second->next; // Bypass the second node
        }

        delete second; // Free the memory
    }

    // Function to separate odd and even nodes in the list
    void separateOddEven(LinkedList &oddList, LinkedList &evenList)
    {
        Node *temp = head;

        while (temp)
        {
            if (temp->data % 2 == 0)
            {
                evenList.insert(temp->data); // Insert into even list
            }
            else
            {
                oddList.insert(temp->data); // Insert into odd list
            }
            temp = temp->next;
        }
    }

    // Function to divide the linked list into k parts
    vector<LinkedList> divideIntoParts(int k)
    {
        vector<LinkedList> parts(k); // Vector to hold k parts
        Node *temp = head;
        int length = 0;

        // Calculate the length of the list
        while (temp)
        {
            length++;
            temp = temp->next;
        }

        // Determine the size of each part
        int partSize = length / k;
        int extraNodes = length % k; // Nodes to distribute

        temp = head; // Reset temp to head
        for (int i = 0; i < k; i++)
        {
            parts[i].head = temp; // Set head of the current part

            // Calculate the size of the current part
            int currentPartSize = partSize + (i < extraNodes ? 1 : 0);
            Node *prev = nullptr;

            // Move to the end of the current part
            for (int j = 0; j < currentPartSize; j++)
            {
                prev = temp;
                temp = temp ? temp->next : nullptr;
            }

            // Break the link to the next part if prev is not null
            if (prev)
            {
                prev->next = nullptr;
            }
        }

        return parts; // Return the vector of parts
    }

    // Function to remove zero-sum consecutive nodes from the linked list
    void removeZeroSumConsecutiveNodes()
    {
        unordered_map<int, Node *> sumMap;
        Node *dummy = new Node(0); // Dummy node to simplify head removal
        dummy->next = head;
        Node *current = dummy;
        int cumulativeSum = 0;

        while (current)
        {
            cumulativeSum += current->data; // Update cumulative sum

            // If cumulative sum is found in map, we have a zero-sum sublist
            if (sumMap.find(cumulativeSum) != sumMap.end())
            {
                Node *nodeToRemove = sumMap[cumulativeSum]->next;
                int sumToRemove = cumulativeSum;

                // Remove nodes until we reach the end of the zero-sum sublist
                while (nodeToRemove != current)
                {
                    sumToRemove += nodeToRemove->data;
                    sumMap.erase(sumToRemove); // Remove sums from the map
                    nodeToRemove = nodeToRemove->next;
                }

                // Bypass the nodes to remove them
                sumMap[cumulativeSum]->next = current->next;
            }
            else
            {
                sumMap[cumulativeSum] = current; // Store the current node
            }

            current = current->next; // Move to the next node
        }

        head = dummy->next; // Update head
        delete dummy;       // Free memory
    }

    LinkedList copyWithRandomPointers()
    {
        unordered_map<Node *, Node *> nodeMap; // Map to hold original and copied nodes
        Node *current = head;

        // First pass: Copy nodes and store in map
        while (current)
        {
            nodeMap[current] = new Node(current->data);
            current = current->next;
        }

        // Second pass: Set next and random pointers
        current = head;
        while (current)
        {
            if (current->next)
            {
                nodeMap[current]->next = nodeMap[current->next]; // Set next pointer
            }
            if (current->random)
            {
                nodeMap[current]->random = nodeMap[current->random]; // Set random pointer
            }
            current = current->next;
        }

        LinkedList copiedList;
        copiedList.head = nodeMap[head]; // Set head of the copied list
        return copiedList;
    }
};

class NumberAdder
{
public:
    LinkedList num1; // First number
    LinkedList num2; // Second number

    void menu()
    {
        while (true)
        {
            cout << "Menu:\n";
            cout << "1. Add first number\n";
            cout << "2. Add second number\n";
            cout << "3. Display both numbers\n";
            cout << "4. Add the two numbers\n";
            cout << "5. Swap nodes in the first number list\n";
            cout << "6. Remove the N-th node from the end of the first number list\n";
            cout << "7. Separate odd and even nodes in the first number list\n";
            cout << "8. Divide the first number list into parts\n";
            cout << "9. Remove zero-sum consecutive nodes from the first number list\n";
            cout << "10. Insert random values into the first number list\n";
            cout << "11. Copy the first number list with random pointers\n";
            cout << "12. Exit\n";
            cout << "Choose an option: ";

            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                cout << "Enter digits for the first number (end with 0): ";
                int value;
                while (true)
                {
                    cin >> value;
                    if (value == 0)
                        break;
                    num1.insert(value);
                }
                break;
            }
            case 2:
            {
                cout << "Enter digits for the second number (end with -1): ";
                int value;
                while (true)
                {
                    cin >> value;
                    if (value == -1)
                        break;
                    num2.insert(value);
                }
                break;
            }
            case 3:
            {
                cout << "First number: ";
                num1.display();
                cout << "Second number: ";
                num2.display();
                break;
            }
            case 4:
            {
                LinkedList result = num1.add(num2);
                cout << "Sum: ";
                result.display();
                break;
            }
            case 5:
            {
                int value1, value2;
                cout << "Enter two values to swap in the first number list: ";
                cin >> value1 >> value2;
                num1.swapNodes(value1, value2);
                cout << "After swapping:\n";
                num1.display();
                break;
            }
            case 6:
            {
                int n;
                cout << "Enter N to remove the N-th node from the end: ";
                cin >> n;
                num1.removeNthFromEnd(n);
                cout << "After removal:\n";
                num1.display();
                break;
            }
            case 7:
            {
                LinkedList oddList, evenList;
                num1.separateOddEven(oddList, evenList);
                cout << "Odd nodes: ";
                oddList.display();
                cout << "Even nodes: ";
                evenList.display();
                break;
            }
            case 8:
            {
                int k;
                cout << "Enter the number of parts to divide into: ";
                cin >> k;
                vector<LinkedList> parts = num1.divideIntoParts(k);
                for (int i = 0; i < parts.size(); i++)
                {
                    cout << "Part " << i + 1 << ": ";
                    parts[i].display();
                }
                break;
            }
            case 9:
            {
                num1.removeZeroSumConsecutiveNodes();
                cout << "After removing zero-sum consecutive nodes:\n";
                num1.display();
                break;
            }
            case 10:
            {
                num1.insertRandomValues(); // Call the new function
                cout << "Random values inserted into the first number list:\n";
                num1.display();
                break;
            }
            case 11:
            { // New case for copying list with random pointers
                LinkedList copiedList = num1.copyWithRandomPointers();
                cout << "Copied list with random pointers:\n";
                copiedList.display();
                break;
            }
            case 12:
            {
                cout << "Exiting...\n";
                return;
            }
            default:
                cout << "Invalid option, please try again.\n";
            }
        }
    }
};

int main()
{
    NumberAdder adder; // Create an instance of NumberAdder
    adder.menu();
    return 0;
}
