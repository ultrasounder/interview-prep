#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* findMiddle(struct ListNode* head) {
    // Function implementation goes here
    struct ListNode *slow = head;
    struct ListNode *fast = head;

    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int main() {
    // Your main function code here
}