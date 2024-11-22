#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <unistd.h> // For sleep()

using namespace std;

// Function to simulate sending a frame
bool sendFrame(int frame) {
    cout << "Sender: Sending frame " << frame << endl;
    return true;
}

// Function to simulate receiving acknowledgment
bool receiveACK(int frame) {
    // Simulate random packet loss by generating a random number
    int randNum = rand() % 10;

    if (randNum < 8) { // 80% chance that the acknowledgment is received successfully
        cout << "Receiver: ACK for frame " << frame << " received." << endl;
        return true;
    } else {
        cout << "Receiver: ACK for frame " << frame << " lost." << endl;
        return false;
    }
}

int main() {
    srand(time(0)); // Initialize random seed

    int totalFrames = 5; // Total number of frames to send

    for (int i = 1; i <= totalFrames; ++i) {
        bool frameSent = sendFrame(i);

        if (frameSent) {
            // Wait for the acknowledgment
            bool ackReceived = receiveACK(i);

            while (!ackReceived) {
                // If ACK is not received, resend the frame
                cout << "Sender: Resending frame " << i << endl;
                frameSent = sendFrame(i);
                ackReceived = receiveACK(i);
            }
        }

        // Simulate network delay before sending the next frame
        sleep(1);
    }

    cout << "All frames sent and acknowledged successfully." << endl;
    return 0;
}
