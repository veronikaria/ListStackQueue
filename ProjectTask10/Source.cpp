#include <iostream>
#include <string>
#include <fstream>
using namespace std;


struct node
{
    double data;
    node* next;
};

class list
{
protected:
    node* head, * tail;

public:
    list()
    {
        head = NULL;
        tail = NULL;
    }

    list(string file)
    {
        readfile(file);
    }

    void sethead(node* nod)
    {
        this->head = nod;
    }

    void settail(node* nod)
    {
        this->tail = nod;
    }

    node* gethead(node* nod)
    {
        return this->head;
    }

    node* gettail(node* nod)
    {
        return this->tail;
    }

    void createnode(double value)
    {
        node* temp = new node;
        temp->data = value;
        temp->next = NULL;
        if (head == NULL)
        {
            head = temp;
            tail = temp;
            temp = NULL;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
    }

    void readfile(string file)
    {
        head = NULL;
        tail = NULL;

        ifstream myfile(file);
        string line;
        string delimiter = " ";
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                int pos = 0;
                string token;
                while ((pos = line.find(delimiter)) != std::string::npos) {
                    token = line.substr(0, pos);
                    createnode(stod(token));
                    line.erase(0, pos + delimiter.length());
                }
                createnode(stod(line));
            }
            myfile.close();
            cout << "Файл успiшно зчитано!" << endl;
        }

        else
            cout << "Помилка! Неможливо відкрити даний файл!";
    }

    ~list()
    {
        node* current = head;
        while (current != NULL) {
            node* next = current->next;
            delete current;
            current = next;
        }
        head = NULL;
    }


    bool is_empty()
    {
        if (head == NULL)
            return true;
        return false;
    }


    void display()
    {
        node* temp = new node;
        temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    void swap_first_last()
    {
        if (is_empty())
        {
            cout << "Список порожній!" << endl;
            return;
        }
        else if (head == tail)
        {
            cout << "Список містить лише один елемент!" << endl;
            return;
        }

        node* temp = this->head;
        node* prev = NULL;

        node* last = tail;
        node* first = head;
        while (temp->next != NULL)
        {
            prev = temp;
            temp = temp->next;
        }

        if (head->next == tail)
        {
            first->next = NULL;
            last->next = first;

            head = last;
            tail = first;

            return;
        }
        temp = head->next;

        first->next = NULL;
        last->next = temp;

        head = last;

        first->next = NULL;
        prev->next = first;

        tail = first;

    }

    void insert_start(double value)
    {
        if (is_empty())
        {
            createnode(value);
            return;
        }
        node* temp = new node;
        temp->data = value;
        temp->next = head;
        head = temp;
    }

    void insert_last(double value)
    {
        if (is_empty())
        {
            createnode(value);
            return;
        }
        node* temp = new node;
        temp->data = value;
        temp->next = NULL;

        tail->next = temp;
        tail = temp;

    }

    bool delete_every(double e)
    {
        int index = 1;
        bool result = false;

        node* temp = new node;
        temp = head;
        while (temp != NULL)
        {
            if (temp->data == e)
            {
                if (temp->next != NULL)
                {
                    if (temp->next->data != e)
                    {
                        delete_position(index + 1);
                        result = true;
                    }
                }
            }
            index++;
            temp = temp->next;
        }
        return result;
    }


    void delete_first()
    {
        if (is_empty())
        {
            cout << "Список порожній!" << endl;
            return;
        }
        node* temp = new node;
        temp = head;
        head = head->next;
        delete temp;
    }

    void delete_last()
    {
        if (is_empty())
        {
            cout << "Список порожній!" << endl;
            return;
        }
        node* current = new node;
        node* previous = new node;
        current = head;
        while (current->next != NULL)
        {
            previous = current;
            current = current->next;
        }
        tail = previous;
        previous->next = NULL;
        delete current;
    }


    void delete_position(int pos)
    {
        node* current = new node;
        node* previous = new node;
        current = head;
        for (int i = 1; i < pos; i++)
        {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
    }

};


class stack:list
{
private:
    int size;
public:
    stack():list()
    {
        this->size = 0;
    }

    stack(string file) :list(file)
    {
        this->size = 0;
    }

    ~stack()
    {
        node* current = tail;
        while (size>0) {
            node* next = current->next;
            delete current;
            current = next;
            size--;
        }
        tail = NULL;
        head = NULL;
    }

    void push(double data)
    {
        node* temp;
        temp = (node*)new node[1];
        temp->data = data;
        temp->next = NULL;
        if (this->size == 0)
        {
            this->head = (node*)new node[1];
            this->tail = temp;
        }
        this->head->next = temp;
        this->head = temp;
        this->size++;
    }

    void pop()
    {
        if (this->size == 0)
        {
            cout << "Стек пустий!" << endl;
            return;
        }
        if (this->size == 1)
        {
            node* temp;
            temp = this->head;
            this->head = NULL;
            this->tail = NULL;
            this->size--;
            delete temp;
            return;
        }
        node* temp1, * temp2;
        temp1 = this->head;
        temp2 = this->tail;
        while (temp2->next != this->head)
        {
            temp2 = temp2->next;
        }
        this->head = temp2;
        this->size--;
        delete temp1;
    }

    void print()
    {
        if (this->size == 0)
        {
            cout << "Стек пустий!" << endl;
            return;
        }
        node* temp;
        temp = this->tail;
        while (temp != this->head)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << this->head->data << endl;
    }

};

class queue: public list
{
public:
    queue() : list() {}
    
    queue(string file) : list(file) {}

    void display()
    {
        node* temp = this->head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }


    void insert(double data)
    {
        node* temp;
        temp = new node;
        temp->data = data;
        temp->next = NULL;
        if (this->tail == NULL)
        {
            this->tail = temp;
            this->head = temp;
        }
        else
        {
            this->tail->next = temp;
            this->tail = temp;
        }
    }

    void drop()
    {
        if (this->head != NULL)
        {
            node* temp = this->head;
            this->head = this->head->next;
            delete temp;
            if (this->head == NULL)
                this->tail = NULL;
        }
        else
            cout << "Черга переповнена!" << endl;
    }
};



void do_task(string file, double a, double b)
{
    const int cnt = 3;
    queue queues[cnt];
    
    for (size_t i = 0; i < cnt; i++)
    {
        queues[i].sethead(NULL);
        queues[i].settail(NULL);
    }
    
    ifstream myfile(file);
    string line;
    string delimiter = " ";
    double num;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            int pos = 0;
            string token;
            while ((pos = line.find(delimiter)) != std::string::npos) 
            {
                token = line.substr(0, pos);
                num = stod(token);
                if (num < a)
                    queues[0].insert(num);
                else if (num>=a && num <=b)
                    queues[1].insert(num);
                else
                    queues[2].insert(num);

                line.erase(0, pos + delimiter.length());
            }
            num = stod(line);
            if (num < a)
                queues[0].insert(num);
            else if (num >= a && num <= b)
                queues[1].insert(num);
            else
                queues[2].insert(num);
        }
        myfile.close();
        cout << "Файл успiшно зчитано!" << endl;
        cout << endl;
        cout << "Числа, що меншi за " << a << ": ";
        queues[0].display();
        cout << "Числа, що в межах ["<< a << ", " << b << "]: ";
        queues[1].display();
        cout << "Iншi числа: ";
        queues[2].display();
    }

    else
        cout << "Помилка! Неможливо вiдкрити даний файл!";
}


int main()
{
    setlocale(LC_ALL, "UKR");
    double a, b;
    cout << "Введiть а: ";
    cin >> a;
    cout << "Введiть b: ";
    cin >> b;

    string file;
    cout << "Введiть назву файлу: ";
    cin >> file;

    do_task(file, a, b);


	return 0;
}


