#include <iostream>
#include <thread>
#include <ConsoleReader.h>

using std::cout;
using std::endl;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;


int main() {
    ConsoleReader cr;

    cr.startSession();

    const milliseconds sleepTime{200};
    for (int i = 1; i <= 10; ++i) {
        sleep_for(sleepTime);
        cout << ".";
        cout.flush();

        if(cr.isInput())
            printf("Read: %c\n", cr.getInput());
    }

    cout << "stop" << endl;
    cr.stopSession();


    int i;
    std::cin >> i;
    cout << i;

    return 0;
}

