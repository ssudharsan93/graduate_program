#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

bool TERMINATE = false;
bool PRINT = false;
char output_str[] = "Hey you just threaded! Nice!";

using namespace std;

void *prompt(void *arg) {

    int input;

    while (!TERMINATE) {

        cout << endl;
        cout << "Please enter either 1 or 0." << endl;
        cout << "1 for output that should be printed," << endl;
        cout << "and 0 for terminating the system. " << endl;
        cout << "Input> ";
        cout << endl;

        cin >> input;

        switch(input) {
            case 0:
                TERMINATE = true;
            case 1:
                PRINT = true;
        }

    }

    return arg;
}


int main() {

    pthread_t my_thread;
    int arg = 0;

    pthread_create(&my_thread, NULL, prompt, (void*) arg);

    while (!TERMINATE) {
        if ( PRINT ) {
            cout << output_str << endl;
            PRINT = false;
        }
    }

    pthread_join(my_thread, NULL);

    return 0;
}