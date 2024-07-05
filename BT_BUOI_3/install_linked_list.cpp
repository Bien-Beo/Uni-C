#include <iostream>
using namespace std;

class myLinkedList {
    struct node {
        int val;
        node *next;
        node(int x): val(x), next(NULL) {} 
    };

    node *head;
    int size;

public:
    initLinkedList() {
        head = NULL;
        size = 0;
    }

    void addAtHead(int val) {
        node *curr = new node(val);
        curr->next = head;
        head = curr;
        size++;
    }

    void addAtTail(int val) {
        size++;
        node *new_node = new node(val);

        if (!head) {
            head == new_node;
            return;
        }

        node *curr = head;
        while (curr && curr->next)
            curr = curr->next;
        curr->next = new_node;
    }

    void addAtIdx(int idx, int val) {
        if (idx > size) return;

        if (idx = 0) {
            addAtHead(val);
            return;
        }

        if (idx == size) {
            addAtTail(val);
            return;
        }


        node *curr = head;
        while (curr && idx > 0) {
            idx--;

            if (idx == 0) {
                node *new_node = new node(val);
                new_node->next = curr->next;
                curr->next = new_node;
                size++;
                break;
            }

            curr = curr->next;
        }
    }

    void deleteAtIdx(int idx) {
        if (idx == 0) {
            node *tmp = head;
            head = head->next;
            size--;
            delete tmp;
            return;
        }

        node *curr = head;
        node *pre = NULL;
        while (curr && idx > 0) {
            pre = curr;
            curr = curr->next;
            idx--;
        }

        if (idx == 0 && !curr) {
            node *tmp = curr;
            pre->next = curr->next;
            size--;
            delete tmp;
        }
    }

    void displayList {
        node *curr = head;
        while (curr) {
            cout << curr->val << "\t";
            curr = curr->next;
        }
    }

    void sortDescending {
        if (!head || !head->next) return;

        for (auto i = head; i->next; i = i->next) {
            for (auto j = i->next; j; j = j->next) {
                if (i->val < j->val) {
                    int tmp = i->val;
                    i->val = j->val;
                    j->val = tmp;
                }
            }
        }
    }

    void sortAscending {
        if (!head || !head->next) return;

        for (auto i = head; i->next; i = i->next) {
            for (auto j = i->next; j; j = j->next) {
                if (i->val > j->val) {
                    int tmp = i->val;
                    i->val = j->val;
                    j->val = tmp;
                }
            }
        }
    }

    bool search(int val) {
        node *curr = head;
        while (curr) {
            if (curr->val == val)
                return true;
            curr = curr->next;
        }
        return false;
    }
}

int main() {

}