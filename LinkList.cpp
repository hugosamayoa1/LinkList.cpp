#include <iostream>
#include <cassert>


using namespace std;

class Iterator;
class List;
class Link;

class Iterator {
        public:
                Iterator();
                void operator++();
                int & operator*();

        private:
                Link* position;
                List* container;
                friend class List;
};

class List {
        public: List();
                ~List() { }
                bool empty() const;
                void push_back(int x);
                void push_front(int x);
                int size();
                void pop_back();
                void pop_front();
                Iterator begin();
                Iterator end();
                Iterator erase(Iterator Iter);
                void insert(Iterator Iter, int x);
        private:
                Link* first;
};

class Link {
        public:
                Link (int n);
        private:
                int data;
                Link* next;
                friend class Iterator;
                friend class List;
};


Iterator::Iterator() {
        position = 0;
        container = 0;
}

Iterator List::begin(){
        Iterator iter;
        iter.position = first;
        iter.container = this;
        return iter;
}

void Iterator::operator++(){
        assert(position != NULL);
        position = position->next;
}

int & Iterator::operator*(){
        assert(position != NULL);
        return position->data;
}

Iterator List::erase(Iterator iter){
        Link* remove = iter.position;
        Link* after = remove->next;

        if(remove == first)
                first = after;
        delete remove;
        Iterator r;
        r.position = after;
        r.container = this;
        return r;
}

Link::Link(int n) {
        data = n;
        next = NULL;
}

List::List(){
        first = NULL;
}

bool List::empty() const {
        if(first == NULL)
                return true;
        else
                return false;
}


void List::push_back(int x) { // pushes number into last part of list
        if (first == nullptr){
                first = new Link(x);
        }
        else {
                Link * link = first;
                while (link->next != nullptr){
                        link = link->next;
                }

                link->next = new Link(x);
        }
}

void List::push_front(int x) { // pushes a number into the last part of list

        if (first == nullptr){
                first = new Link(x);
        }

         else {
         Link* new_Link = new Link(x);
                Link * link = first;
                new_Link->next = first;
                first = new_Link;
        }
}

void List::pop_back() { //removes the 1st prt of List
        Link * link = first;
        while(link->next != nullptr) {
                link = link->next;
        }
        delete link->next;
}
void List::pop_front(){ //removes first part of list

        first = first->next;
}

void List::insert(Iterator iter, int x){//pushes number into specific part list

        if(iter.position == NULL){//skips unneed steps if list empty
                push_back(x);
                return;
        }

        Link* after = iter.position;
        Link* new_Link = new Link(x);
        new_Link->next = after;

}

int List::size(){       //return size of last
        Link * link = first;
        int count = 0;
        while (link != nullptr) {
                ++count;
                link = link->next;
        }
        return count;
}

void test1() { //test push_back
        
                List a;
        a.push_back(5);
        a.push_back(10);
        Iterator it;
        it = a.begin();
        a.erase(it);
        assert(*it = 5);
        ++it;
        assert(*it = 10);
}

void test2() { //test push_front

        List b;
        b.push_front(15);
        b.push_back(20);
        Iterator it;
        it = b.begin();
        b.erase(it);
        assert(*it = 15);
         ++it;
        assert(*it = 20);
}

void test3() { //deletes a middle number

        List c;
        c.push_front(25);
        c.push_front(30);
        c.push_front(35);
        Iterator it;
        it = c.begin();
        ++it;
        c.erase(it);
        assert(*it = 25);
        ++it;
        assert(*it = 35);
        }

void test4() { //test size

        List d;
        assert(d.size() == 0);
        d.push_front(40);
        assert(d.size() == 1);
        d.push_front(45);
        assert(d.size() == 2);
        d.push_front(50);
        assert(d.size() == 3);
}
int main(){

        test1();
        test2();
        test3();
        test4();
        
        cout << "Awesome! All Test Passed!" << endl;

        return 0;
}
