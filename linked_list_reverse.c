#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseList(struct ListNode* head){
    //Initialize pointers
    struct ListNode *prev = NULL;
    struct ListNode *current = head;
    struct ListNode *next_node = NULL;

    //Iterate through the List
    while (current != NULL){
        //Store the next node
        next_node = current->next;
        //reverse the current node's pointer
        current->next = prev;
        //Move pointers one position ahead
        prev = current;
        current = next_node;
        


    }
}