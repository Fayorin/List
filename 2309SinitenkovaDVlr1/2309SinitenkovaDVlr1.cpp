// 1lab_aisd.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
using namespace std;
class Node
{
public:
    int data;
    Node* prev, * next;
    Node(int data)
    {
        this->data = data;
        this->prev = this->next = NULL;
    }
};
class List
{

public:
    Node* head, * tail;
    List();
    void printList();
    void push_back(int data);
    void push_front(int data);
    void deleteLastNode();
    void deleteFirstNode();
    void insertBefore(int index, int value);
    Node* getNode(int index);
    void DeleteNode(int index);
    int getListSize();
    void deleteList();
    void replaceElementByIndex(int index, int newValue);
    bool isListEmpty();
    void reverseList();
    void swapByIndexes(int index1, int index2);
};
List::List()
{
    head = tail = NULL;
}
void List::printList() {
    if (head) {
        for (Node* c = head; c; c = c->next) {
            printf("%i", c->data);
            if (c->next) printf("->");
        }
    }
    else {
        printf("There are no nodes in this list.");
    }
    printf("\n");
}
void List::push_back(int data)
{
    Node* temp = new Node(data);

    if (head != NULL)
    {
        temp->prev = tail;
        if (tail != NULL) {
            tail->next = temp;
        }
        tail = temp;
    }
    else
    {
        temp->prev = NULL;
        head = tail = temp;
    }
}
void List::push_front(int data) {
    Node* ptr = new Node(data);

    ptr->next = head;
    if (head != NULL)
    {
        head->prev = ptr;
        head = ptr;
    }
    else
    {
        head = tail = ptr;
    }
}

void List::deleteLastNode() {
    if (head == nullptr) { // если список пустой
        return;
    }

    if (head->next == nullptr) { // если в списке только один элемент
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }

    Node* temp = tail;
    tail = tail->prev;
    tail->next = nullptr;
    delete temp;
}


void List::deleteFirstNode() {
    // Проверяем, что список не пустой
    if (head == nullptr) {
        return;
    }
    Node* temp = head;

    head = head->next;
    if (head != nullptr) {
        (head)->prev = nullptr;
    }
    // Удаляем первый элемент
    delete temp;
}

void List::insertBefore(int index, int value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        // Если список пуст, добавляем новый элемент в начало
        head = newNode;
        return;
    }

    if (index == 0) {
        // Если индекс равен 0, добавляем новый элемент в начало
        newNode->next = head;
        (head)->prev = newNode;
        head = newNode;
        return;
    }
    Node* current = head;
    int currentIndex = 0;

    while (current != nullptr && currentIndex < index) {
        // Продвигаемся по списку до нужного индекса
        current = current->next;
        currentIndex++;
    }

    if (current == nullptr) {
        // Если достигли конца списка, добавляем новый элемент в конец
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    else {
        // Вставляем новый элемент перед текущим элементом
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
}

Node* List::getNode(int index) {
    Node* ptr = head;
    int n = 0;

    while (n != index) {
        if (ptr == NULL)
            return ptr;
        ptr = ptr->next;
        n++;
    }

    return ptr;
}
void List::DeleteNode(int index)
{
    Node* ptr = head;
    Node* left = ptr->prev;
    Node* right = ptr->next;
    int n = 0;

    while (n != index) {
        if (ptr == NULL)
            return;
        ptr = ptr->next;
        left = ptr->prev;
        right = ptr->next;
        n++;
    }
    left->next = right;
    right->prev = left;

    delete ptr;
}

int List::getListSize() {
    int size = 0;
    Node* current = head;

    while (current != nullptr) {
        size++;
        current = current->next;
    }

    return size;
}

void List::deleteList() {
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
}

void List::replaceElementByIndex(int index, int newValue) {

    Node* current = head;

    current = head;
    for (int i = 0; i < index; i++)
    {
        if (current->next == nullptr)
        {
            std::cout << "Индекс выходит за пределы списка." << std::endl; return;
        }
        current = current->next;
    }
    current->data = newValue;
}

bool List::isListEmpty() {
    return (head == nullptr && tail == nullptr);
}

void List::reverseList() {
    Node* current = head;
    Node* temp = nullptr;

    // Перебираем список, меняя указатели prev и next для каждого узла
    while (current != nullptr) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
}

void insertList(Node* list1Head, Node* list1Tail, Node* list2Head, Node* list2Tail, int index) {
    if (index < 0) {
        std::cout << "Invalid index" << std::endl;
        return;
    }

    if (list1Head == nullptr) {
        list1Head = list2Head;
        list1Tail = list2Tail;
        return;
    }

    Node* current = list1Head;
    int count = 0;

    while (current != nullptr && count < index) {
        current = current->next;
        count++;
    }

    if (current == nullptr) {
        std::cout << "Invalid index" << std::endl;
        return;
    }

    Node* list1Next = current->next;

    current->next = list2Head;
    list2Head->prev = current;

    if (list1Next != nullptr) {
        list1Next->prev = list2Tail;
    }

    list2Tail->next = list1Next;

}

void insertListAtEnd(List* list1, List* list2) {
    if (list2->head == nullptr) {
        return; // Если второй список пуст, ничего не делаем
    }

    if (list1->head == nullptr) {
        // Если первый список пуст, просто присваиваем ему значения второго списка
        list1->head = list2->head;
        list1->tail = list2->tail;
    }
    else {
        // Иначе, добавляем элементы второго списка в конец первого списка
        list1->tail->next = list2->head;
        list2->head->prev = list1->tail;
        list1->tail = list2->tail;
    }

    // Обнуляем указатели второго списка
    list2->head = nullptr;
    list2->tail = nullptr;
}
void insertListAtStart(List* List1, List* List2) {
    // Если второй список пустой, то ничего не делаем
    if (List2->head == nullptr) {
        return;
    }

    // Если первый список пустой, то просто присваиваем ему указатели второго списка
    if (List1->head == nullptr) {
        List1->head = List2->head;
        List1->tail = List2->tail;
    }
    else {
        // Если оба списка не пустые, то вставляем второй список в начало первого
        List2->tail->next = List1->head;
        List1->head->prev = List2->tail;
        List1->head = List2->head;
    }

    // Обнуляем указатели второго списка
    List2->head = nullptr;
    List2->tail = nullptr;
}

bool containsList(List* list, List* sublist) {
    if (sublist->head == nullptr) {
        return true; // пустой список содержится в любом другом списке
    }
    if (list->head == nullptr) {
        return false; // пустой список не может содержать непустой список
    }

    Node* current = list->head;
    Node* subCurrent = sublist->head;

    while (current != nullptr) {
        if (current->data == subCurrent->data) {
            Node* temp = current;
            while (temp != nullptr && subCurrent != nullptr && temp->data == subCurrent->data) {
                temp = temp->next;
                subCurrent = subCurrent->next;
            }
            if (subCurrent == nullptr) {
                return true; // весь sublist найден в list
            }
            subCurrent = sublist->head; // сбрасываем subCurrent для продолжения поиска
        }
        current = current->next;
    }

    return false; // sublist не найден в list
}

int findSublist(List* DL1, List* DL2) {
    Node* curr1 = DL1->head;
    while (curr1 != nullptr) {
        Node* curr2 = DL2->head;
        Node* temp = curr1;
        while (curr2 != nullptr && temp != nullptr && curr2->data == temp->data) {
            curr2 = curr2->next;
            temp = temp->next;
        }
        if (curr2 == nullptr) {
            // Второй список полностью найден в первом списке
            int index = 0;
            Node* curr = DL1->head;
            while (curr != curr1) {
                curr = curr->next;
                index++;
            }
            return index;
        }
        curr1 = curr1->next;
    }
    return -1; // Второй список не найден в первом списке
}
int findLastOccurrence(List* list1, List* list2) {
    if (list1 == nullptr || list2 == nullptr) {
        return -1;
    }

    Node* curr1 = list1->tail;
    Node* curr2 = list2->tail;

    int index1 = 0;
    int index2 = 0;

    while (curr1 != nullptr) {
        if (curr1->data == curr2->data) {
            Node* temp1 = curr1;
            Node* temp2 = curr2;

            while (temp1 != nullptr && temp2 != nullptr && temp1->data == temp2->data) {
                temp1 = temp1->prev;
                temp2 = temp2->prev;
                index1--;
                index2--;
            }

            if (temp2 == nullptr) {
                return list1->getListSize() + index1;
            }
        }

        curr1 = curr1->prev;
        index1--;
    }

    return -1;
}

void List::swapByIndexes(int index1, int index2) {
    if (index1 < 0 || index2 < 0) {
        std::cout << "Invalid indexes" << std::endl;
        return;
    }

    Node* node1 = getNode(index1);
    Node* node2 = getNode(index2);

    if (node1 == nullptr || node2 == nullptr) {
        std::cout << "Invalid indexes" << std::endl;
        return;
    }

    if (node1 == node2) {
        std::cout << "Indexes are the same" << std::endl;
        return;
    }

    // Обмен указателями prev
    Node* tempPrev = node1->prev;
    node1->prev = node2->prev;
    node2->prev = tempPrev;

    if (node1->prev == nullptr) {
        head = node1;
    }
    else if (node2->prev == nullptr) {
        head = node2;
    }

    // Обмен указателями next
    Node* tempNext = node1->next;
    node1->next = node2->next;
    node2->next = tempNext;

    if (node1->next == nullptr) {
        tail = node1;
    }
    else if (node2->next == nullptr) {
        tail = node2;
    }

    // Обновление указателей соседних элементов
    if (node1->prev != nullptr) {
        node1->prev->next = node1;
    }
    if (node1->next != nullptr) {
        node1->next->prev = node1;
    }
    if (node2->prev != nullptr) {
        node2->prev->next = node2;
    }
    if (node2->next != nullptr) {
        node2->next->prev = node2;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    List DL1, DL2;
    int n;
    for (int i = 0; i < 10000; i++)
        DL1.push_back(3);
    //DL1.printList();
    for (int i = 0; i < 1; i++)
        DL2.push_back(4);
    // DL2.printList();
    do {
        cout << "Выберите функцию"<<endl<<"1. добавление в конец списка\n2. добавление в начало списка\n3. удаление последнего элемента" << endl <<
            "4. удаление первого элемента" << endl <<
            "5. добавление элемента по индексу(вставка перед элементом, который был ранее доступен по этому индексу)" << endl <<
            "6. получение элемента по индексу" << endl <<
            "7. удаление элемента по индексу" << endl <<
            "8. получение размера списка" << endl <<
            "9. удаление всех элементов списка" << endl <<
            "10. замена элемента по индексу на передаваемый элемент" << endl <<
            "11. проверка на пустоту списка" << endl <<
            "12. меняет порядок элементов в списке на обратный" << endl <<
            "13. вставка другого списка в список, начиная с индекса" << endl <<
            "14. вставка другого списка в конец" << endl <<
            "15. вставка другого списка в начало" << endl <<
            "16. проверка на содержание другого списка в списке" << endl <<
            "17. поиск первого вхождения другого списка в список"
            << endl << "18. поиск последнего вхождения другого списка в список" << endl << "19. обмен двух элементов списка по индексам" << endl;
        cin >> n;
        void printList();
        int data;
        int value, index;
        double start_time;
        double end_time;
        double search_time;

        switch (n) {
        case 1:
            cout << "Введите число, которое хотите вставить в конец списка" << endl;
            cin >> data;
            start_time = clock();
            DL1.push_back(data);
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            //DL1.printList();
            cout << endl;
            break;
        case 2:
            cout << "Введите число, которое хотите вставить в начало списка" << endl;
            cin >> data;
            start_time = clock();
            DL1.push_front(data);
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            DL1.printList();
            cout << endl;
            break;
        case 3:
            start_time = clock();
            DL1.deleteLastNode();
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            //DL1.printList();
            cout << endl;
            break;
        case 4:
            DL1.deleteFirstNode();
            DL1.printList();
            cout << endl;
            break;
        case 5:
            cout << "Введите число, которое хотите вставить, и индекс" << endl;

            cin >> value;
            cin >> index;
            start_time = clock();
            DL1.insertBefore(index, value);
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            //DL1.printList();
            cout << endl;
            break;
        case 6:
            cout << "Введите индекс" << endl;
            cin >> index;
            start_time = clock();
            cout << DL1.getNode(index);
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            break;
        case 7:
            cout << "Введите индекс" << endl;
            cin >> index;
            start_time = clock();
            DL1.DeleteNode(index);
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            break;
        case 8:
            start_time = clock();
            DL1.getListSize();
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            break;
        case 9:
            start_time = clock();
            DL1.deleteList();
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            break;
        case 10:
            cout << "Введите число, на которое хотите заменить, и индекс" << endl;

            cin >> value;
            cin >> index;
            start_time = clock();
            DL1.replaceElementByIndex(index, value);
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            break;
        case 11:
            if (DL1.isListEmpty()) cout << "Список пуст" << endl; else cout << "Cписок не пуст";
            break;
        case 12:
            //cout << "Список до:" << endl;
            //DL1.printList();
            start_time = clock();
            DL1.reverseList();
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            cout << "Список после" << endl;
            //DL1.printList();
            break;
        case 13:
            cout << "Первый список" << endl;
            // DL1.printList();
            cout << "Второй список" << endl;
            // DL2.printList();
            cout << "Введите индекс" << endl;
            cin >> index;
            start_time = clock();
            insertList(DL1.head, DL1.tail, DL2.head, DL2.tail, index);
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            //DL1.printList();
            break;
        case 14:
            cout << "Первый список" << endl;
            DL1.printList();
            cout << "Второй список" << endl;
            DL2.printList();
            insertListAtEnd(&DL1, &DL2);
            DL1.printList();
            break;
        case 15:
            cout << "Первый список" << endl;
            DL1.printList();
            cout << "Второй список" << endl;
            DL2.printList();
            insertListAtStart(&DL1, &DL2);
            DL1.printList();
            break;
        case 16:
            //cout << "Первый список" << endl;
            //DL1.printList();
            //cout << "Второй список" << endl;
           // DL2.printList();
            bool q;
            start_time = clock();
            q = containsList(&DL1, &DL2);
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            if (q) cout << "Первый список содержит второй список" << endl; else cout << "Первый список не содержит второй список" << endl;;
            break;
        case 17:
            cout << "Первый список" << endl;
            //DL1.printList();
            cout << "Второй список" << endl;
            // DL2.printList();
            start_time = clock();
            cout << "Первое вхождение - индекс " << findSublist(&DL1, &DL2) << endl;
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            break;
        case 18: cout << "Первый список" << endl;
            DL1.printList();
            cout << "Второй список" << endl;
            DL2.printList();
            cout << "Последнее вхождение - индекс " << findLastOccurrence(&DL1, &DL2) << endl;
            break;

        case 19:
            //DL1.printList();
            cout << "Введите индексы" << endl;
            int index1, index2;
            cin >> index1;
            cin >> index2;
            start_time = clock();
            DL1.swapByIndexes(index1, index2); cout << endl;
            end_time = clock();
            search_time = end_time - start_time;
            cout << "Time: " << search_time;
            //DL1.printList();
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            break;
        }
    } while (n != 20);
}

