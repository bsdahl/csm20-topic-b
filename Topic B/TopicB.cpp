//
//  main.cpp
//  Topic B
//
//  Created by user on 9/23/15.
//  Copyright (c) 2015 Ben Dahl. All rights reserved.
//
// Status: Working with Extra Credit
// Note: TopicBin.txt has windows CRLF /r/n linebreaks. Getline removes /n, but not /r.
//       Therefore getline() includes the carriagereturn /r. When I run the program on
//       my Mac (UNIX) I get the extra linebreaks in the output.

#include <iostream>
#include <fstream>
#include <string>
#include "LinkedQueue.h"
#include "LinkedStack.h"

void readFileToQueue(const string&, LinkedQueue<string>&);
void displayQueue(LinkedQueue<string>&);
void displayStack(LinkedStack<char>&);
void stringToStack(const string&, LinkedStack<char>&);
void checkLine(const string&);

int main() {
    string filename;
    
    cout << "Create queue object lq" << endl << endl;
    LinkedQueue<string> lq;
    
    cout << "Get the file input" << endl << endl;
    cout << "Enter input file name: ";
    cin >> filename;
    readFileToQueue(filename,lq);
    
    cout << "After getting the file input,  test other functions*******" << endl;
    cout << "Create lq1, a copy of the queue" << endl << endl;
    LinkedQueue<string> lq1 = LinkedQueue<string>(lq);
    
    cout << "Display the contents of the copy queue lq1:" << endl << endl;
    displayQueue(lq1);
    
    cout << "Attempt to peek the now empty copy queue lq1:" << endl << endl;
    try {
        lq1.peekFront();
    }
    catch(PrecondViolatedExcep& error) {
        cerr << "ERROR: " << error.what() << endl;
    }
    
    cout << "Assign lq to lq1 and then display lq1:" << endl;
    lq1 = lq;
    displayQueue(lq1);
    
    cout << "Put the first string in lq into a stack of chars, ls1" << endl << endl;
    LinkedStack<char> ls1;
    stringToStack(lq.peekFront(), ls1);
    
    
    cout << "Create a copy, ls2, of the stack and display the copy:" << endl << endl;
    LinkedStack<char> ls2 = LinkedStack<char>(ls1);
    displayStack(ls2);
    
    cout << "Assign the first stack, ls1, to the second stack, ls2, and then display the second stack:" <<endl << endl;
    ls2 = ls1;
    displayStack(ls2);
    
    cout << "Do the expression checking:" << endl << endl;
    while (!lq.isEmpty()) {
        checkLine(lq.peekFront());
        lq.dequeue();
    }
    
    // Press enter to end
    cout << "Press Enter to end --> ";
    cin.ignore();cin.ignore(); //Once isnt enough?
    
    return 0;
}


void readFileToQueue(const string& filename, LinkedQueue<string>& queue) {
    string line;
    ifstream inFile;
    inFile.open(filename);

    if (inFile.good())
    {
        while (!inFile.eof() )
        {
            getline (inFile,line);
            queue.enqueue(line);
        }
    }
    inFile.close();
}

/* Originally I had plans for this to be a nondestructive display. It would loop the queue, and return the contents to the queue. However that didnt fit with the output of TopicB.exe */
void displayQueue(LinkedQueue<string>& aQueue) {
    string line;
    //LinkedQueue<string>* newqueue = new LinkedQueue<string>;
    
    while (!aQueue.isEmpty()) {
        line = aQueue.peekFront();
        cout << line << endl;
        aQueue.dequeue();
        //newqueue->enqueue(line);
    }
    
    //queue = *newqueue;
}

void displayStack(LinkedStack<char>& aStack) {
    char data;
    
    while (!aStack.isEmpty()) {
        data = aStack.peek();
        cout << data << " ";
        aStack.pop();
    }
    cout << endl;
}

void stringToStack(const string& line, LinkedStack<char>& aStack) {
    for (int i = 0; i < line.length(); i++) {
        aStack.push(line[i]);
    }
}

void checkLine(const string& line) {
    // Setup test characters. 0x22 = ", 0x27 = '
    char test[] = {'(',')','[',']','{','}', 0x22, 0x27};
    LinkedStack<char> aStack;
    bool balanced = true;
    int i = 0;
    
    cout << "The next string is:   " << line;
    
    while (balanced && i < line.length())
    {
        char ch = line[i];
        int j = 0;
        i++;
        
        // Check for escape char 0x5C = /
        if (ch == 0x5C) {
            i++;
            continue;
        }
        
        // Begin the expression check
        while (j < 5) {
            if(ch == test[j]) {
                aStack.push(test[j]);
                break;
            }
            else if (ch == test[j+1]) {
                if (!aStack.isEmpty() && aStack.peek() == test[j])
                    aStack.pop();
                else {
                    balanced = false;
                    break;
                }
            }
            j+= 2;
        }
        
        // Check for " and '
        if (ch == test[6] || ch == test[7]){
            if (!aStack.isEmpty() && aStack.peek() == ch)
                aStack.pop();
            else
                aStack.push(ch);
        }
    } // end while
    
    if (!aStack.isEmpty())
        balanced = false;
    
    cout << " is " << (balanced ? "":"NOT ") << "a correct expression" << endl;
    
}