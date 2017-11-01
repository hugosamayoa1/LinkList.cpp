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

int main(){

        List a;
        assert(a.empty() == true);
        a.push_back(17);
        assert(a.empty() == false);
        a.push_front(3);
        a.push_back(10);
        assert(a.size() == 3);
        Iterator it = a.begin();
        assert(*it == 3);
        ++it;
        assert(*it == 17);
        ++it;
        assert(*it == 10);
        it = a.begin();
        assert(*it == 3);
        *it += 1;
        assert(*it == 4);
        ++it;
        a.insert(it, 29);
        it = a.begin();
        cout << *it << endl;
        ++it;
        cout << *it << endl;
        ++it;
        cout << *it << endl;
        ++it;
        cout << "All tests passed." << endl;
}


                
