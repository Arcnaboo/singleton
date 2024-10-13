/**
 * @file singleton.c
 * @brief Singleton pattern implementation in C to avoid global variables.
 * 
 * This program demonstrates how to implement the Singleton pattern in C,
 * using a static pointer within a function to maintain a single instance
 * of a structure. It also includes signal handling for SIGINT to print the
 * Singleton instance information.
 * 
 * MIT License
 * 
 * Copyright (c) 2024 Arc Naboo
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @author Arc Naboo
 * @date 2024
 */

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Structure representing the Singleton instance.
 * 
 * The SingletonClass structure holds the instance data, which includes
 * an ID and a name. The Singleton pattern ensures that only one instance
 * of this structure exists at any time.
 */
typedef struct {
    int id;          /**< ID number of the singleton instance */
    char name[100];  /**< Name of the singleton instance */
} SingletonClass;

/**
 * @brief Get or set the Singleton instance.
 * 
 * This function maintains a static pointer to the Singleton instance. If
 * a non-NULL pointer is passed, it sets the static pointer to that value.
 * If NULL is passed, it returns the current Singleton instance.
 * 
 * @param sc Pointer to the SingletonClass instance to set. If NULL, the current
 * instance is returned.
 * @return Pointer to the SingletonClass instance.
 */
SingletonClass *get_instance(SingletonClass *sc) {
    static SingletonClass *out = NULL;  /**< Static pointer to store the singleton instance */
    
    if (sc != NULL) {
        out = sc;
    }
    return out;
}

/**
 * @brief Signal handler for SIGINT.
 * 
 * This function is triggered when the program receives a SIGINT signal (Ctrl+C).
 * It retrieves the Singleton instance and prints its name and ID, then exits the
 * program.
 * 
 * @param sig Signal number (expected to be SIGINT).
 */
void sigint_handler(int sig) {
    SingletonClass *instance = get_instance(NULL);
    if (instance) {
        printf("instance name: %s\nid: %d\n", instance->name, instance->id);
    } else {
        printf("No instance set.\n");
    }
    exit(15);
}

/**
 * @brief Main function of the program.
 * 
 * This function initializes the Singleton instance based on user input, sets up
 * the signal handler for SIGINT, and waits for the signal. When the signal is
 * received, the handler will print the instance information.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments (expects ID as the second argument).
 * @return int Exit status of the program.
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s idnum\n", argv[0]);
        return 1;
    }

    // Set up the signal handler for SIGINT
    signal(SIGINT, sigint_handler);
    
    SingletonClass sc;

    // Read the instance name
    printf("Please enter name for instance: ");
    if (!fgets(sc.name, sizeof(sc.name), stdin)) {
        puts("exiting");
        return 1;
    }

    // Remove the newline character from the name
    sc.name[strlen(sc.name) - 1] = '\0';

    // Read the ID from the command line argument
    sc.id = atoi(argv[1]);

    // Set the singleton instance
    get_instance(&sc);

    printf("ok please send sigint with ctrl+c to print instance info\n");

    // Wait indefinitely for the signal
    while (1);

    return 0;
}
