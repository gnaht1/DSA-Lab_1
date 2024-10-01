// STT: ?
// Full Name: Nguyen Phan Huynh Thang
// Session 01 - Exercise 01
// Notes or Remarks:

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm> // for std::find
using namespace std;

// Cấu trúc node
struct Node
{
    int data;
    Node *next;
    Node(int x) : data(x), next(nullptr) {}
};

// Lớp LinkedList
class LinkedList
{
private:
    Node *head;

public:
    LinkedList() : head(nullptr) {}

    // Hàm tạo danh sách liên kết từ mảng đầu vào
    void createLinkedList(int arr[], int n)
    {
        head = nullptr;
        Node *tail = nullptr;

        for (int i = 0; i < n; ++i)
        {
            Node *newNode = new Node(arr[i]);

            if (!head)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    // Hàm tìm node ở giữa danh sách liên kết
    Node *findMiddle()
    {
        if (!head)
            return nullptr;

        Node *slow = head;
        Node *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow; // Trả về node ở giữa
    }

    // Hàm phát hiện chu trình khi node cuối trỏ về node đầu
    bool detectCycle()
    {
        if (!head)
            return false;

        Node *slow = head;
        Node *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
            {
                return true; // Chu trình được phát hiện
            }
        }
        return false; // Không có chu trình
    }

    // Hàm in danh sách liên kết
    void printList()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Hàm trả về con trỏ đến đầu danh sách
    Node *getHead()
    {
        return head;
    }

    // Hàm hợp nhất hai danh sách đã sắp xếp
    void combineSortedLists(LinkedList &otherList)
    {
        Node *head1 = this->head;
        Node *head2 = otherList.getHead();
        Node *mergedHead = nullptr;
        Node *mergedTail = nullptr;

        while (head1 && head2)
        {
            Node *temp = nullptr;

            if (head1->data <= head2->data)
            {
                temp = head1;
                head1 = head1->next;
            }
            else
            {
                temp = head2;
                head2 = head2->next;
            }

            if (!mergedHead)
            {
                mergedHead = temp;
                mergedTail = temp;
            }
            else
            {
                mergedTail->next = temp;
                mergedTail = temp;
            }
        }

        if (head1)
        {
            mergedTail->next = head1;
        }
        else if (head2)
        {
            mergedTail->next = head2;
        }

        this->head = mergedHead;
    }

    // Hàm tìm tất cả giá trị giao nhau của hai danh sách liên kết
    vector<int> getIntersectionValues(LinkedList &otherList)
    {
        unordered_map<int, bool> values;
        vector<int> intersectionValues;
        Node *head1 = this->head;

        // Lưu trữ các giá trị trong danh sách đầu tiên
        while (head1)
        {
            values[head1->data] = true;
            head1 = head1->next;
        }

        Node *head2 = otherList.getHead();
        // Tìm các giá trị giao nhau trong danh sách thứ hai
        while (head2)
        {
            if (values.find(head2->data) != values.end())
            {
                // Kiểm tra nếu giá trị đã được thêm
                if (find(intersectionValues.begin(), intersectionValues.end(), head2->data) == intersectionValues.end())
                {
                    intersectionValues.push_back(head2->data); // Thêm giá trị giao nhau vào danh sách
                }
            }
            head2 = head2->next;
        }

        return intersectionValues; // Trả về danh sách các giá trị giao nhau
    }

    // Hàm đảo ngược danh sách liên kết
    void reverse()
    {
        Node *prev = nullptr;
        Node *current = head;
        Node *next = nullptr;

        while (current)
        {
            next = current->next; // Lưu trữ con trỏ tiếp theo
            current->next = prev; // Đảo ngược con trỏ
            prev = current;       // Di chuyển prev lên
            current = next;       // Di chuyển current lên
        }
        head = prev; // Đặt head mới
    }

    // Hàm loại bỏ các giá trị trùng lặp từ danh sách liên kết đã sắp xếp
    void eliminateDuplicates()
    {
        Node *current = head;
        while (current && current->next)
        {
            if (current->data == current->next->data)
            {
                Node *temp = current->next;          // Lưu trữ con trỏ đến node trùng lặp
                current->next = current->next->next; // Bỏ qua node trùng lặp
                delete temp;                         // Giải phóng bộ nhớ
            }
            else
            {
                current = current->next; // Di chuyển đến node tiếp theo
            }
        }
    }

    bool isPalindrome()
    {
        if (!head || !head->next)
            return true; // Nếu danh sách trống hoặc có một phần tử thì là palindrome

        // Tìm node ở giữa
        Node *slow = head;
        Node *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Đảo ngược nửa sau danh sách
        Node *prev = nullptr;
        Node *current = slow;
        Node *next = nullptr;
        while (current)
        {
            next = current->next; // Lưu trữ con trỏ tiếp theo
            current->next = prev; // Đảo ngược con trỏ
            prev = current;       // Di chuyển prev lên
            current = next;       // Di chuyển current lên
        }

        // So sánh cả hai nửa
        Node *left = head;
        Node *right = prev; // prev là đầu của nửa sau đã đảo ngược
        while (right)       // Chỉ cần so sánh đến khi hết nửa sau
        {
            if (left->data != right->data)
                return false; // Không phải là palindrome
            left = left->next;
            right = right->next;
        }

        return true; // Là palindrome
    }

    vector<Node *> searchForValue(int X)
    {
        vector<Node *> result;
        Node *temp = head;

        while (temp)
        {
            if (temp->data == X)
            {
                result.push_back(temp); // Thêm địa chỉ của node có giá trị X vào vector
            }
            temp = temp->next;
        }

        if (result.empty())
        {
            return {}; // Không tìm thấy, trả về danh sách trống
        }
        return result; // Trả về danh sách các địa chỉ của node có giá trị X
    }
};

int main()
{
    LinkedList list1, list2; // Tạo hai đối tượng của lớp LinkedList
    int choice;
    do
    {
        cout << "\n----- Menu -----\n";
        cout << "1. Phát hiện chu trình trong danh sách liên kết\n";
        cout << "2. Tìm node ở giữa của danh sách liên kết\n";
        cout << "3. Hợp nhất hai danh sách liên kết đã sắp xếp\n";
        cout << "4. Tìm tất cả giá trị giao nhau của hai danh sách liên kết\n";
        cout << "5. Đảo ngược danh sách liên kết\n";                                   // Mục mới
        cout << "6. Loại bỏ các giá trị trùng lặp từ danh sách liên kết đã sắp xếp\n"; // Mục mới
        cout << "7. Check Palindrome\n";
        cout << "8. Tìm node có giá trị X\n";
        cout << "0. Thoát\n";
        cout << "Chọn lựa chọn của bạn: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int n;
            cout << "Nhập số lượng phần tử trong danh sách liên kết 1: ";
            cin >> n;

            int arr[n];
            cout << "Nhập các phần tử: ";
            for (int i = 0; i < n; ++i)
            {
                cin >> arr[i];
            }

            list1.createLinkedList(arr, n);
            if (list1.detectCycle())
            {
                cout << "Chu trình được phát hiện trong danh sách liên kết.\n";
            }
            else
            {
                cout << "Không có chu trình trong danh sách liên kết.\n";
            }
            break;
        }
        case 2:
        {
            int n;
            cout << "Nhập số lượng phần tử trong danh sách liên kết 1: ";
            cin >> n;

            int arr[n];
            cout << "Nhập các phần tử: ";
            for (int i = 0; i < n; ++i)
            {
                cin >> arr[i];
            }

            list1.createLinkedList(arr, n);
            Node *middle = list1.findMiddle();
            if (middle)
            {
                cout << "Node ở giữa có giá trị: " << middle->data << endl;
            }
            else
            {
                cout << "Danh sách liên kết trống.\n";
            }
            break;
        }
        case 3:
        {
            int n1, n2;
            cout << "Nhập số lượng phần tử trong danh sách liên kết 1: ";
            cin >> n1;
            int arr1[n1];
            cout << "Nhập các phần tử cho danh sách liên kết 1: ";
            for (int i = 0; i < n1; ++i)
            {
                cin >> arr1[i];
            }
            list1.createLinkedList(arr1, n1);

            cout << "Nhập số lượng phần tử trong danh sách liên kết 2: ";
            cin >> n2;
            int arr2[n2];
            cout << "Nhập các phần tử cho danh sách liên kết 2: ";
            for (int i = 0; i < n2; ++i)
            {
                cin >> arr2[i];
            }
            list2.createLinkedList(arr2, n2);

            list1.combineSortedLists(list2);
            cout << "Danh sách liên kết đã hợp nhất: ";
            list1.printList();
            break;
        }
        case 4:
        {
            int n1, n2;
            cout << "Nhập số lượng phần tử trong danh sách liên kết 1: ";
            cin >> n1;
            int arr1[n1];
            cout << "Nhập các phần tử cho danh sách liên kết 1: ";
            for (int i = 0; i < n1; ++i)
            {
                cin >> arr1[i];
            }
            list1.createLinkedList(arr1, n1);

            cout << "Nhập số lượng phần tử trong danh sách liên kết 2: ";
            cin >> n2;
            int arr2[n2];
            cout << "Nhập các phần tử cho danh sách liên kết 2: ";
            for (int i = 0; i < n2; ++i)
            {
                cin >> arr2[i];
            }
            list2.createLinkedList(arr2, n2);

            vector<int> intersectionValues = list1.getIntersectionValues(list2);
            if (!intersectionValues.empty())
            {
                cout << "Các điểm giao nhau có giá trị: ";
                for (int val : intersectionValues)
                {
                    cout << val << " ";
                }
                cout << endl;
            }
            else
            {
                cout << "Không có điểm giao nhau.\n";
            }
            break;
        }
        case 5: // Đảo ngược danh sách liên kết
        {
            int n;
            cout << "Nhập số lượng phần tử trong danh sách liên kết 1: ";
            cin >> n;

            int arr[n];
            cout << "Nhập các phần tử: ";
            for (int i = 0; i < n; ++i)
            {
                cin >> arr[i];
            }

            list1.createLinkedList(arr, n);
            cout << "Danh sách liên kết trước khi đảo ngược: ";
            list1.printList();

            list1.reverse(); // Gọi hàm đảo ngược
            cout << "Danh sách liên kết sau khi đảo ngược: ";
            list1.printList();
            break;
        }
        case 6: // Loại bỏ các giá trị trùng lặp
        {
            int n;
            cout << "Nhập số lượng phần tử trong danh sách liên kết 1: ";
            cin >> n;

            int arr[n];
            cout << "Nhập các phần tử: ";
            for (int i = 0; i < n; ++i)
            {
                cin >> arr[i];
            }

            list1.createLinkedList(arr, n);
            cout << "Danh sách liên kết trước khi loại bỏ trùng lặp: ";
            list1.printList();

            list1.eliminateDuplicates(); // Gọi hàm loại bỏ trùng lặp
            cout << "Danh sách liên kết sau khi loại bỏ trùng lặp: ";
            list1.printList();
            break;
        }

        case 7: // Kiểm tra xem danh sách liên kết có phải là palindrome không
        {
            int n;
            cout << "Nhập số lượng phần tử trong danh sách liên kết 1: ";
            cin >> n;

            int arr[n];
            cout << "Nhập các phần tử: ";
            for (int i = 0; i < n; ++i)
            {
                cin >> arr[i];
            }

            list1.createLinkedList(arr, n);
            if (list1.isPalindrome())
            {
                cout << "Danh sách liên kết là palindrome.\n";
            }
            else
            {
                cout << "Danh sách liên kết không phải là palindrome.\n";
            }
            break;
        }

        case 8: // Tìm kiếm node có giá trị X
        {
            int n, X;
            cout << "Nhập số lượng phần tử trong danh sách liên kết 1: ";
            cin >> n;

            int arr[n];
            cout << "Nhập các phần tử: ";
            for (int i = 0; i < n; ++i)
            {
                cin >> arr[i];
            }

            list1.createLinkedList(arr, n);

            cout << "Nhập giá trị X cần tìm: ";
            cin >> X;

            vector<Node *> nodesWithValue = list1.searchForValue(X);
            if (!nodesWithValue.empty())
            {
                cout << "Tìm thấy " << nodesWithValue.size() << " node có giá trị " << X << " ở địa chỉ: ";
                for (Node *node : nodesWithValue)
                {
                    cout << node << " ";
                }
                cout << endl;
            }
            else
            {
                cout << "Không tìm thấy giá trị " << X << " trong danh sách.\n";
            }
            break;
        }
        case 0:
            cout << "Thoát chương trình.\n";
            break;
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
        }
    } while (choice != 0);

    return 0;
}
