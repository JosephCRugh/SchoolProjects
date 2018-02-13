// By Joseph Rugh
#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <map>
#include <tuple>
#include <stack>
#include <string>

using namespace std;

void factory(map<int, queue<int>>& queues, int& lastIndex, int& num);
void receiver(map<int, queue<int>>& queues, stack<int>& myStack);
void displayQueues(map<int, queue<int>> queues);
void displayStack(stack<int> myStack);

int main()
{
    srand(time(NULL));
    map<int, queue<int>> queues;
    stack<int> myStack;
    queue<int> q1, q2, q3, q4;
    queues.insert(pair<int, queue<int>>(0, q1));
    queues.insert(pair<int, queue<int>>(1, q1));
    queues.insert(pair<int, queue<int>>(2, q1));
    queues.insert(pair<int, queue<int>>(3, q1));

    // Requesting user input to know if they want to run the program around
    string input = "";
    string testInput = "";
    do {
        testInput = "";

        // Generating values and placing them in queues and the stack
        int lastIndex = 0, num = 1;
        for (int i = 0; i < 5; i++)
        {
            factory(queues, lastIndex, num);
            displayQueues(queues);
            receiver(queues, myStack);
            displayQueues(queues);
            displayStack(myStack);
            cout << "\n";
        }

        while (true)
        {
            cout << endl;
            cout << "Run the program around? (y/n):";
            cin >> input;
            for (string::size_type i = 0; i < input.length(); i++) testInput += tolower(input[i]);

            // Invalid input
            if (!(testInput == "n" || testInput == "no" || testInput == "yes" || testInput == "y"))
            {
                cout << "\n\nInvalid input.\n\n";
                testInput = "";
                continue;
            }
            break;
        }

    } while (testInput != "n" && testInput != "no");

    return 0;
}

void factory(map<int, queue<int>>& queues, int& lastIndex, int& num)
{
    int numDeals = (rand() % 5) + 1;
    cout << "Factory generates: ";
    for (int i = 0; i < numDeals; i++)
    {
        cout << num << ((i+1) == numDeals ? "" : ", ");
        // restart at q1
        if (lastIndex > 3)
        {
            lastIndex = 0;
            (queues.find(lastIndex)->second).push(num);
        }
        else
        {
            (queues.find(lastIndex)->second).push(num);
            lastIndex++;
        }
        num++;
    }
    cout << "\n";
}

void receiver(map<int, queue<int>>& queues, stack<int>& myStack)
{
    while (true)
    {
        int queuePicked = (rand() % 4) + 0;
        queue<int>* removeQueue = &(queues.find(queuePicked)->second);
        if (removeQueue->empty()) continue;
        cout << "Receiver choice: " << queuePicked << "\n";
        myStack.push(removeQueue->front());
        removeQueue->pop();
        break;
    }
}

void displayQueues(map<int, queue<int>> queues)
{
    map<int, queue<int>>::iterator mapItr = queues.begin();
    int i = 0;
    while (mapItr != queues.end())
    {
        cout << "Q" << i << ": ";
        queue<int> tqueue = mapItr->second;
        if (tqueue.empty()) cout << "empty";
        while (!tqueue.empty())
        {
            int value = tqueue.front();
            cout << value << " ";
            tqueue.pop();
        }
        cout << "  ";
        mapItr++;
        i++;
    }
    cout << "\n";
}

void displayStack(stack<int> myStack)
{
    cout << "Stack: ";
    while (!myStack.empty())
    {
        int value = myStack.top();
        cout << value << " ";
        myStack.pop();
    }
    cout << "\n";
}
