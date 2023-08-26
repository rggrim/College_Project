/***************************************************************************************************
 *  CSC1310 001 Program 2 - Using MergeSort on Doubly Linked Lists
 *  Author:     Riley Grimaud
 *  Date:       02/28/2023
 *  File Name:  List.h
 *  Purpose:    Recursively sorts a doubly linked list using the MergeSort approach. Given a linked list of nodes
 *              with T value, MergeSort will recursively split the list in halves until only one 
 *              node is left in the list, at which point the algorithm will begin to step its way back
 *              out of the recursion, comparing halves of the list against each other and putting them in 
 *              proper order as the recursion "unwinds".
 *****************************************************************************************************/

#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

template <typename T>                       //Using template with T data so that user can input any kind of data when 
                                            //using Mergesort.

    class List {                            //class "List" to create the doubly linked list of nodes of T values
        private:
            struct ListNode{                //Node with pointers to the nodes directly before and after it
                T value;                    //In this example, T value will be counties.
                ListNode * next;
                ListNode * prev;
            };
            ListNode * head;                //Establishing a head and tail to easily track where list begins and ends,
            ListNode * tail;                //which is one of the benefits of a doubly linked list! You can have a tail. 

            //functions:
            void Print(ListNode * startNode);
            ListNode * MergeSort(ListNode *, ListNode *);
            ListNode * Split(ListNode * front, ListNode * back);
            ListNode * Merge(ListNode *, ListNode*);

        public:
            
            List();
            ~List();
            void Print();
            void Append(T);
            void MergeSort();
           
    };

    /*************************************************************************************
     * Function:    Print
     * Purpose:     this version of print will print every value in the list after the 
     *              parameter node. This is useful for debugging your mergesort.
     *************************************************************************************/
    template <typename T>
        void List<T>::Print(ListNode * startNode){
            
            while(startNode != NULL) {                          //while loop will run until "startNode" reaches end of list                            
                cout << *(startNode->value) << endl;
                startNode = startNode->next;                    //set startNode to the next item in the list
            }
        }
    /*************************************************************************************
     * Function:    MergeSort
     * Purpose:     manages the recursive calls that mergesort needs to make
     *************************************************************************************/
    
    template <typename T>
        typename List<T>::ListNode* List<T>::MergeSort(ListNode * front, ListNode * back){
            ListNode * middleNode, * newEnd, * returnVal, * newStart;
            ListNode * left = front;
            ListNode * right = back;

            if((left == NULL) || (left->next == NULL)){     //MergeSort will call itself in newStart and newEnd (below) until the "left" node
                return left;                                //is the only node being passed through, and then it will start to step back
            }                                               //out of the recursion.
            
    
            middleNode = Split(left, right);                //split() will return the start of the right partition
            newStart = MergeSort(left, middleNode->prev);   //newStart is set to the front of the LEFT partition
            newEnd = MergeSort(middleNode, right);          //newEnd is set to the front of the RIGHT partition
            
            returnVal = Merge(newStart, newEnd);             //Merge will return the front of the newly sorted list, which will be
                                                             //the combination of newStart and newEnd's lists.
            return returnVal;
        }
    /*************************************************************************************
     * Function:    Split
     * Purpose:     subdivide a list partition into two more partitions until only one node is present.
     *************************************************************************************/
    template <typename T>
        typename List<T>::ListNode * List<T>::Split(ListNode * front, ListNode * back) {
            ListNode * left = front;
            ListNode * right = back;
            
            while(left != right->prev) {              //while loop will traverse through the list from both directions so that nodes "front"
                left = left->next;                    //and "back" meet in the middle

                if (left->next != right){             //move left element forward first; check to see if left and right are adjacent;           
                    right = right->prev;              //if left and right are not adjacent, move right node backward; check to see if adjacent; repeat loop.
                }  
            }

            (right->prev)->next = NULL;               //sever the left node from the following value so that left and right are now two separate lists

            return right;                             //return the start of the new right partition; the start of the new left partition is still "front", 
                                                      //so you don't need to return the left front back.
        }
    /*************************************************************************************
     * Function:    Merge
     * Purpose:     merge two list partitions together in order
     *************************************************************************************/
    template <typename T>
    typename List<T>::ListNode * List<T>::Merge(ListNode * left, ListNode* right) {
        ListNode * leftFront = left;
        ListNode * rightFront = right;

        if (leftFront == NULL) {                    //if either argument is NULL, no need to recursively call merge again.
            return rightFront;                      //Note: this may be superfluous since the program can not pass NULL values of 
        }                                           //"left" or "right" through to Merge() anyway.

        if(rightFront == NULL) {                                         
            return leftFront;                                         
        }

        if (leftFront->value->getPopulation() >= rightFront->value->getPopulation()) {    //case 1: leftFront > rightFront, so left should be head of new list
            if (leftFront->next == NULL){                                   //if leftFront is a single node, no need to recursively call Merge() anymore; rightFront
                leftFront->next = rightFront;                               //-can simply be appended to the end of leftFront
                (leftFront->next)->prev = leftFront;
            }
            else{
                leftFront->next = Merge(leftFront->next, rightFront);        //recursively call Merge() until single node partitions are being passed, and then string back together
                (leftFront->next)->prev = leftFront;                         //list in backwards order on the way out of the recursion.
            }

            return leftFront;                                                //return the new start of the newly sorted partition.
        }
        else {                                                                      //case 2: rightFront > leftFront. Same as case 1, except right and left are in opposite positions.
            if (rightFront->next == NULL){
                rightFront->next = leftFront;
                (rightFront->next)->prev = rightFront;
            }
            else {
                rightFront->next = Merge(leftFront, rightFront->next);
                (rightFront->next)->prev = rightFront;
            }
            return rightFront;
        }
    }
    /*************************************************************************************
     * Function:    List constructor
     * Purpose:     creates an empty list by setting head and tail to null
     *************************************************************************************/
    template <typename T>
    List<T>::List(){
        head = NULL;
        tail = NULL;
    }


    /*************************************************************************************
     * Function:    List destructor
     * Purpose:     called when the list is removed from memory
     *************************************************************************************/
    template <typename T>
    List<T>::~List(){
        ListNode * curNode = head;
        ListNode * nextNode = head;             //holder node so that you keep track of your place in the list after deleting curNode.

        while (nextNode != NULL)  {             //step through list until you reach the node before NULL (indicating you've reached the tail.)
            nextNode = nextNode->next;
            delete curNode;
            curNode = nextNode;
        }
    }

    
    /*************************************************************************************
     * Function:    Print
     * Purpose:     prints the value of every element in the list
     *************************************************************************************/
    template <typename T>
    void List<T>::Print(){
        Print(head);                           //call private print function
    }                                          //you can change "head" as needed for debugging


    /*************************************************************************************
     * Function:     Append
     * Purpose:     create a new node and add that node as the last element of the list
     *************************************************************************************/
    template <typename T>
    void List<T>::Append(T newValue) {
        ListNode * newNode = new ListNode;              //create a new node and store newValue in it
        newNode->value = newValue;

        if(head == NULL) {                              //set tail AND head  to newNode, since list is empty
            head = newNode;
            tail = newNode;
        }
        else {                                          //else attach newNode to the previous tail node
            tail->next = newNode;                       //and reset the tail value
            newNode->prev = tail;
            tail = newNode;
        }
    }
/*************************************************************************************
 * Function:     MergeSort
 * Purpose:      this is the public-facing function call to begin sorting the list in 
 *               descending order.
 *************************************************************************************/
template <typename T>
void List<T>::MergeSort(){

    Print(head);                                //USED FOR DEBUGGING
    head = MergeSort(head, tail);               //MergeSort will return the head of the newly sorted list
    ListNode * curNode = head;                  //Create new node to use during traversal of the list to find the tail
    
    while(curNode->next != NULL) {              //traverse newly sorted list until curNode = tail (since tail->next = NULL)
        curNode = curNode->next;
    }
    
    tail = curNode;                             //set tail to curNode
} 

#endif