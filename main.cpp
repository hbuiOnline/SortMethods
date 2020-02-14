//Han Bui
//ID#: 1858671
//COSC 2430 Data Structure
//Professor: Nouhad Rizk
//Homework 3

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "ArgumentManager.h"
#define MAX 100000


using namespace std;

struct list{
    int data;
    list * next;
    
};

class Sorting{
private:
    list *head, *tail;
    int indexNum = 0;
    int numbersFromFile[MAX];
    
    
public:
    int count = 0;
    
    Sorting(){
        head = NULL;
        tail = NULL;
    }
    
    void swap(int * a, int * b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    
    
    void insertEnd(int value){
        
        list *temp = new list;          //Create new node
        temp->data = value;
        temp->next = NULL;
        
        if (head == NULL)
        {
            head = temp;
            tail = temp;
            temp = NULL;
        }
        else {
            tail->next = temp;
            tail = temp;
        }
    }
    
    
    void parsing(string inputFile)
    {
        int num;
        fstream inFile;
        inFile.open(inputFile);
        if(!inFile.is_open()){cout << "Cannot open the file.\n";}
        
        while(inFile >> num)
        {
            insertEnd(num);
            numbersFromFile[count] = num;
            count++;
        }
        
        
    }
    
    
    void command(string inputFile, ofstream &output)
    {
        string line, firstw, secondw, thirdw, index;
        
        fstream inFile;
        inFile.open(inputFile);
        if (!inFile.is_open()){ cout << "Cannot open the file.\n";}
        
        stringstream ss;
        getline(inFile, line);
        
        ss << line;
        
        getline(ss, firstw, ' ');
        getline(ss, secondw, ' ');
        getline(ss, thirdw, ' ');
        
        
        //Calling Quick Sort functions
        if((firstw == "quick") && (secondw == "sort"))
        {
            if (thirdw == "descending")
                quickSortD(numbersFromFile, 0, count-1);
            else
                quickSortA(numbersFromFile, 0,count-1);
        }
        
        //Calling Merge Sort functions
        else if((firstw == "merge") && (secondw == "sort"))
        {
            if(thirdw == "descending")
            {
                recMergeSortD(head);
                for (int i = 0; i < count; i++){
                    numbersFromFile[i] = head->data;
                    head = head->next;
                }
            }
            else
            {
                recMergeSortA(head);
                for (int i = 0; i < count; i++){
                    numbersFromFile[i] = head->data;
                    head = head->next;
                }
            }
           
        }
        
        //Calling Shell Sort functions
        else if((firstw == "shell") && (secondw == "sort"))
        {
            if(thirdw == "descending")
                shellSortD(numbersFromFile, count);
            else
                shellSortA(numbersFromFile, count);
        }
        
        //Reset cursor to the front of the string
        ss.clear();
        ss.seekg(0, ios::beg);
        
        string temp;
        
        //Write output into output file
        while(!ss.eof())
        {
            ss >> temp;
            if(stringstream(temp) >> indexNum){
                if (indexNum >= count)
                { continue; }
                output << numbersFromFile[indexNum] << ' ' ;
            }
        }
        
    }
    
    int partitionA(int *arr, int left, int right) {
        int i, j;
        
        i = left;
        for (j = left + 1; j <= right; ++j) {
            if (arr[j] < arr[left]) {
                ++i;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[left], &arr[i]);
        
        return i;
    }
    
    int partitionD(int *arr, int left, int right) {
        int i, j;
        
        i = left;
        for (j = left + 1; j <= right; ++j) {
            if (arr[j] > arr[left]) {
                ++i;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[left], &arr[i]);
        
        return i;
    }
    
    void quickSortA(int *arr, int left, int right) {
        int r;
        
        if (right > left) {
            r = partitionA(arr, left, right);
            quickSortA(arr, left, r - 1);
            quickSortA(arr, r + 1, right);
        }
    }
    
    void quickSortD(int *arr, int left, int right) {
        int r;
        
        if (right > left) {
            r = partitionD(arr, left, right);
            quickSortD(arr, left, r - 1);
            quickSortD(arr, r + 1, right);
        }
    }
    
    
    void divideList(list * first1, list* &first2)
    {
        list* middle;
        list* current;
        if (first1 == NULL) //list is empty
            first2 = NULL;
        else if (first1->next == NULL) //list has only one node
            first2 = NULL;
        else
        {
            middle = first1;
            current = first1->next;
            
            if (current != NULL) //list has more than two nodes
                current = current->next;
            while (current != NULL)
            {
                middle = middle->next;
                current = current->next;
                if (current != NULL)
                    current = current->next;
            } //end while
            first2 = middle->next;      //first2 points to the first
            //node of the second sublist
            middle->next = NULL;        //set the link of the last node
            //of the first sublist to NULL
        } //end else
        
    } //end divideList
    
    void recMergeSortA(list*  &head)
    {
        list * otherHead;
        if(head != NULL)
            if (head->next != NULL)
            {
                divideList(head,otherHead);
                recMergeSortA(head);
                recMergeSortA(otherHead);
                head = mergeListA(head, otherHead);
            }
    }
    
    void recMergeSortD(list*  &head)
    {
        list * otherHead;
        if(head != NULL)
            if (head->next != NULL)
            {
                divideList(head,otherHead);
                recMergeSortD(head);
                recMergeSortD(otherHead);
                head = mergeListD(head, otherHead);
            }
    }
    
    list* mergeListA(list * first1, list * first2)
    {
        list * lastSmall;
        list * newHead;
        
        if(first1 == NULL)
            return first2;
        else if (first2 == NULL)
            return first1;
        
        else
        {
            if(first1->data < first2->data)   //Change for desending.
            {
                newHead = first1;
                first1 = first1->next;
                lastSmall = newHead;
            }
            else
            {
                newHead = first2;
                first2 = first2->next;
                lastSmall = newHead;
            }
            
            while(first1 != NULL && first2 != NULL)
            {
                if(first1->data < first2->data) //Change for desending.
                {
                    lastSmall->next = first1;
                    lastSmall = lastSmall->next;
                    first1 = first1->next;
                }
                else
                {
                    lastSmall->next = first2;
                    lastSmall = lastSmall->next;
                    first2 = first2->next;
                }
                
            }//End while
            
            if(first1 == NULL)//first sublist is exhausted first
                lastSmall->next = first2;
            else
                lastSmall->next = first1;
            
            return newHead;
        }
        
    }//End mergeList
    
    list* mergeListD(list * first1, list * first2)
    {
        list * lastSmall;
        list * newHead;
        
        if(first1 == NULL)
            return first2;
        else if (first2 == NULL)
            return first1;
        
        else
        {
            if(first1->data > first2->data)   //Change for desending.
            {
                newHead = first1;
                first1 = first1->next;
                lastSmall = newHead;
            }
            else
            {
                newHead = first2;
                first2 = first2->next;
                lastSmall = newHead;
            }
            
            while(first1 != NULL && first2 != NULL)
            {
                if(first1->data > first2->data) //Change for desending.
                {
                    lastSmall->next = first1;
                    lastSmall = lastSmall->next;
                    first1 = first1->next;
                }
                else
                {
                    lastSmall->next = first2;
                    lastSmall = lastSmall->next;
                    first2 = first2->next;
                }
            }//End while
            
            if(first1 == NULL)//first sublist is exhausted first
                lastSmall->next = first2;
            else
                lastSmall->next = first1;
            
            return newHead;
            
            
        }
        
    }//End mergeList
    
    /* function to sort arr using shellSort */
    void shellSortA(int arr[], int n)
    {
        
        // Start with a big gap, then reduce the gap
        for (int gap = n/2; gap > 0; gap /= 2)
        {
            // Do a gapped insertion sort for this gap size.
            // The first gap elements a[0..gap-1] are already in gapped order
            // keep adding one more element until the entire array is
            // gap sorted
            for (int i = gap; i < n; i += 1)
            {
                // add a[i] to the elements that have been gap sorted
                // save a[i] in temp and make a hole at position i
                int temp = arr[i];
                
                // shift earlier gap-sorted elements up until the correct
                // location for a[i] is found
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];
                
                //  put temp (the original a[i]) in its correct location
                arr[j] = temp;
            }
        }
        
    }
    
    void shellSortD(int arr[], int n)
    {
        
        // Start with a big gap, then reduce the gap
        for (int gap = n/2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                int temp = arr[i];
                
                int j;
                for (j = i; j >= gap && arr[j - gap] < temp; j -= gap)
                    arr[j] = arr[j - gap];
                
                arr[j] = temp;
            }
        }
    }
    
};


int main(int argc, char * argv[]) {
    
    ArgumentManager am(argc, argv);
    const string inputFileName = am.get("input");
    const string commandLine = am.get("command");
    const string outputFileName = am.get("output");

    //string outputFileName = "output33.txt";
    Sorting obj;
    ofstream output(outputFileName);

    obj.parsing(inputFileName);
    obj.command(commandLine, output);

//        ArgumentManager am(argc, argv);
//        const string inputFileName = am.get("input");
//        const string commandLine = am.get("command");
//        //const string outputFileName = am.get("output");
//
//        string outputFileName = "output39.txt";
//        Sorting obj;
//        ofstream output(outputFileName);
//
//        obj.parsing("input39.txt");
//        obj.command("command39.txt", output);
    
    
    return 0;
}


//Read how many number inside the input file
//Create dyanamic array based on the number of int in the input
//Read input file again, this time, store int into the new dynamic array

//*Note each input file is contained 10000 numbers

//Case1 interver [0.00558, 0.01034]
//Case2 interval [0.00711, 0.01319]
//Case3 interval [0.0061, 0.0111]

