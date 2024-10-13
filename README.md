Singleton Pattern in C (Avoiding Global Variables)
This project demonstrates a simple implementation of the Singleton pattern in C while avoiding the use of global variables. It includes signal handling to showcase how to interact with the Singleton instance during runtime by sending a SIGINT (Ctrl+C) signal.

How It Works
The Singleton pattern is implemented using a static pointer inside the get_instance() function. This pattern ensures that there is only one instance of a particular class (in this case, SingletonClass), and it can be accessed from anywhere in the program without the need for global variables.

Key Features:
Static Singleton Pointer: A static pointer inside the get_instance() function is used to maintain the Singleton instance across function calls.
Signal Handling: The program handles SIGINT (Ctrl+C) using signal() to print the current Singleton instance details when the signal is received.
Interactive Input: The user is prompted to enter the name of the Singleton instance at runtime.
Program Flow:
The program starts by asking the user to enter the name of the Singleton instance.
The user provides an ID as a command-line argument.
Once the instance is set, the program waits for a SIGINT signal (Ctrl+C).
When the signal is received, the current state of the Singleton instance is printed to the console.
Compilation and Running
Prerequisites:
GCC (or another C compiler) installed on your machine.
Compilation:
To compile the program, run the following command in your terminal:

Copy code
gcc singleton.c -o singleton
Running the Program:
Once compiled, you can run the program like this:

bash
Copy code
./singleton <id_number>
<id_number>: This is an integer that represents the ID for the Singleton instance.
Example Usage:
Run the program with an ID:
bash
Copy code
./singleton 123
Enter the name when prompted:
perl
Copy code
Please enter name for instance: Arc Naboo
ok please send sigint with ctrl+c to print instance info
Send a SIGINT signal by pressing Ctrl+C:
yaml
Copy code
instance name: Arc Naboo
id: 123
Code Breakdown
SingletonClass Structure:
c
Copy code
typedef struct {
    int id;
    char name[100];
} SingletonClass;
This structure holds the data for our Singleton instance, with an id and a name.

Singleton Getter Function:
c
Copy code
SingletonClass *get_instance(SingletonClass *sc) {
    static SingletonClass *out = NULL;
    
    if (sc != NULL) {
        out = sc;
    }
    return out;
}
The get_instance() function manages a static pointer that stores the Singleton instance. The first call to this function initializes the instance, and subsequent calls return the same instance.

Signal Handler:
c
Copy code
void sigint_handler(int sig) {
    SingletonClass *instance = get_instance(NULL);
    if (instance) {
        printf("instance name: %s\nid: %d\n", instance->name, instance->id);
    } else {
        printf("No instance set.\n");
    }
    exit(15);
}
This function handles SIGINT (Ctrl+C). It retrieves the Singleton instance and prints its data to the console before exiting.

Use Case for Singleton Pattern
Avoiding Global Variables: The Singleton pattern is particularly useful when you need to ensure only one instance of a structure or class exists, while still maintaining access to it from multiple points in the program.
Shared Resource Management: In more advanced use cases, singletons can be used to manage shared resources such as configuration settings, logging services, or database connections.
License
This project is licensed under the MIT License. You are free to use, modify, and distribute the code. See the LICENSE file for more details.

Author
Prepared by Arc Naboo for educational purposes.
