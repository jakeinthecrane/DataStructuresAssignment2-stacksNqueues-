#include "stacksNqueue.h"
using namespace std;

Browser::Browser() : head(nullptr), tail(nullptr) // Constructor initializes the head and tail to nullptr to indicate an empty linked list at the start.  
{}

Browser::~Browser() // browser deconstructor
{
    clearList(); // this function is invoked before switching between stack and queue.  This function clears all data everytime a new function is called so that there are no leaks or dangling pointers
}

// Stack behavior: Push a message (LIFO), clear list function is called before this function to ensure that the there isn't any leaks or dangling pointers
void Browser::pushMessage(const string& message) // each message argument passed here will begin fresh with a new node then each additional node will be added and update the newNode to head. 
{
    auto newNode = make_shared<Node>(message);
    if (!head)
    {
        head = tail = newNode;
    }
    else
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
} // return; delimiters are not needed here since void functions dont have a return value.. the function ends at the closing brace because the compiler understands that the function has completed its job..

// Stack behavior: Pop a message (LIFO)
string Browser::popMessage()
{
    if (!head)
    {
        cout << "Stack is empty.\n";
        return "";
    }
    string message = head->message;  // head node is retrieved and assigned to local variable message here.  head node points to it
    head = head->next; // head is popped/ disconnected and head now points to the next node
    if (head) head->prev = nullptr; // if statement checking if head is not null. prev pointer of head is now updated to nullptr
    else tail = nullptr; // Resets tail if(when...in this case at least) list becomes empty ensuring both head and tail reflect an empty list.
    return message; // returns the message from the popped node to the caller and will iterate until the list is empty..
}

// Queue behavior: Enqueue a message add function with FIFO input entry..
void Browser::enqueueMessage(const string& message) 
{
    auto newNode = make_shared<Node>(message); // Create a new node here..
    if (!tail) // same as above start a new node
    {
        head = tail = newNode;
    }
    else // here we add the node to the end of the queue where tail points to the new node.. the list is added in the opposite manner as the push function.
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode; // the tail points to newNode if its not empty..
    }
}

// Queue behavior: Dequeue a message (FIFO)
string Browser::dequeueMessage() 
{
    if (!head) // if no list is available then output message from the block executes..
    {
        cout << "Queue is empty.\n";
        return "";
    }
    string message = head->message; // we dequeue with the same algorithm as pop.  It works fifo becuase of how we first assigned the list 
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr; // Reset tail if list becomes empty
    return message;
}

// Clear the linked list to prevent memory leaks.  I noticed letters were overlapping so I added this function.
void Browser::clearList() 
{
    while (head) // while head is not null... 
    {
        head = head->next; // starts at the head and works its way down until nullptr
    }
    tail = nullptr; // Reset tail
}

// Displays the predefined list of messages
void Browser::displayList(const vector<string>& messages) const
{
    cout << "List of Messages:\n";
    for (const auto& msg : messages) 
    {
        cout << msg << endl;
    }
}

// Play messages using either stack or queue. We are function chaining these 2 functions...indirect recursion..
void Browser::playMessages(bool useStack) 
{
    if (useStack) // these 2 conditional statements will be guided by a boolean operator depending on the users selection
    { 
        cout << "Playing messages using Stack (LIFO):\n";
        while (head) 
        {
            cout << popMessage() << endl; // if true pop message gets called (option 1)
        }
    }
    else
    {
        cout << "Playing messages using Queue (FIFO):\n";
        while (head)
 {
            cout << dequeueMessage() << endl; // if false fifo gets called (option 2)
        }
    }
}

// Menu for user interaction
void Browser::menu()
{
    vector<string> messages = // our string vector where we have assigned our conversation to be stored..
    {
        "Person 1: Hey, where should we go for dinner?",  // the messages from our conversation. They start in this order and organized accordingly..
        "Person 2: How about Italian?",
        "Person 1: Great! Luigi's downtown?",
        "Person 2: Perfect. What time?",
        "Person 1: 7 PM works for me.",
        "Person 2: Got it. See you there!",
        "Person 1: Don't forget to try the tiramisu.",
        "Person 2: Sounds amazing. Thanks!",
        "Person 1: It'll be great to catch up.",
        "Person 2: Definitely. See you soon!",
        "Person 1: Have you decided on drinks?",
        "Person 2: Maybe their house wine?",
        "Person 1: That’s a great choice!",
        "Person 2: Have you tried their pasta?",
        "Person 1: Yes, it's fantastic!",
        "Person 2: I can’t wait!",
        "Person 1: Me too. It'll be fun!",
        "Person 2: Absolutely. Let’s meet there.",
        "Person 1: Sounds like a plan!",
        "Person 2: See you at 7!"
    };

    bool running = true; // control flag for the while loop so we have a proper exit.. no infinite loops...
    int choice;
    while (running) 
    {
        cout << "\nMenu:\n";  // user menu options..
        cout << "1. Display the conversation messages \n";
        cout << "2. Display playback choices\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))  // users input line to select from the above choices
        {
            cin.clear(); // resets error flags... and below assists with input buffers.... followed by an output to the user...
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // used for robust input handling...  let's keep our ram tip top. 
        switch (choice)  // switch statement that performs depending on the users choice
        {
        case 1: // calls the conversation so that we can make a 1st observation. 
        {
            displayList(messages); 
            break;
        }
        case 2:  // calls a menu to give the user a choice to retieve the messages between the 2 LIFO or FIFO methods.
        {
            int playbackChoice;
            cout << "Choose playback method:\n";
            cout << "1. Stack (LIFO)\n";
            cout << "2. Queue (FIFO)\n";
            cout << "Enter your choice: ";
            cin >> playbackChoice;

            if (playbackChoice == 1) // #1 clears the linked list to prevent any leaks, then calls pushMessage followed by playMessages(true) which executes popMessages
            {
                clearList();
                for (const auto& msg : messages)
                {
                    pushMessage(msg); 
                }
                playMessages(true);
            }
            else if (playbackChoice == 2) // #2 same idea as #1 we clear the list then call the enqueueMessage function followed by a playMessages(false)
            {
                clearList();
                for (const auto& msg : messages)
                {
                    enqueueMessage(msg);
                }
                playMessages(false);
            }
            else // error message for an incorect choice 
            {
                cout << "Invalid playback choice.\n";
            }
            break;
        }
        case 3:
            cout << "Exiting program.\n";
            running = false; // exits the program and sets the boolean to false
            break;
        default: // default for the switch construct
            cout << "Invalid choice. Try again.\n";
        }
    }
}
/* the conversation doesn't make sense when we use the stack method since it is populating the stream with the messages from the 
   head rather than from the tail as the queue method does. I created a couple of options to sample both variances  */