
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ListNode
{
    int val;
    struct ListNode* next;
};

struct ListNode* insertNode(struct ListNode* head, int val)
{
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    
    newNode->val = val;
    newNode->next = NULL;
    
    if (head == NULL)
	{
        return newNode;
    }
    
    struct ListNode* temp = head;
    
    while (temp->next != NULL)
	{
        temp = temp->next;
    }
    temp->next = newNode;
    
    return head;
}

struct ListNode* getMiddle(struct ListNode* head)
{
    if (head == NULL) return head;
    
    struct ListNode* slow = head;
    struct ListNode* fast = head->next;
    
    while (fast != NULL && fast->next != NULL)
	{
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

struct ListNode* sortedMerge(struct ListNode* a, struct ListNode* b)
{
    if (a == NULL)
		return b;
		
    if (b == NULL)
		return a;
    
    struct ListNode* result = NULL;
    
    if (a->val <= b->val)
	{
        result = a;
        result->next = sortedMerge(a->next, b);
    }
	else
	{
        result = b;
        result->next = sortedMerge(a->next, b);
    }
    
    return result;
}

struct ListNode* mergeSort(struct ListNode* head)
{
    if (head == NULL || head->next == NULL)
	{
        return head;
    }
    
    struct ListNode* middle = getMiddle(head);
    struct ListNode* nextOfMiddle = middle->next;
    
    middle->next = NULL;
    
    struct ListNode* left = mergeSort(head);
    struct ListNode* right = mergeSort(nextOfMiddle);
    
    struct ListNode* sortedList = sortedMerge(left, right);
    
    return sortedList;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize)
{
    struct ListNode* mergedHead = NULL;
    int i;
    
    for (i = 0; i < listsSize; i++)
	{
        struct ListNode* temp = lists[i];
        
        while (temp != NULL)
		{
            mergedHead = insertNode(mergedHead, temp->val);
            temp = temp->next;
        }
    }
    
    return mergedHead;
}

struct ListNode* generateRandomList(int size, int minValue, int maxValue)
{
    struct ListNode* head = NULL;
    int prevValue = minValue;
    int randomValue;
    int i;
    
    for (i = 0; i < size; i++)
	{
        randomValue = prevValue + rand() % (maxValue - prevValue + 1);
        head = insertNode(head, randomValue);
        prevValue = randomValue;
    }
    
    return head;
}

void printList(struct ListNode* head)
{
    while (head != NULL)
	{
        printf(" %d", head->val);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));
    
    int k = rand() % 10001;
    int totalNodes = 0;
    int maxTotalNodes = 10000;
    int listSize;
    int i;
    
    struct ListNode* lists[k];
    
    for (i = 0; i < k && totalNodes < maxTotalNodes; i++)
	{
        listSize = rand() % 501;
        
        if (totalNodes + listSize > maxTotalNodes)
		{
            listSize = maxTotalNodes - totalNodes;
        }
        totalNodes += listSize;
        
        lists[i] = generateRandomList(listSize, -10000, 10000);
    }
    
    struct ListNode* mergedList = mergeKLists(lists, k);
    
    struct ListNode* sortedList = mergeSort(mergedList);
    
    printList(sortedList);
    
    return 0;
}
