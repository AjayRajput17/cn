#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <unistd.h> // For sleep()

using namespace std;

const int WINDOW_SIZE = 4; // Window size for Go-Back-N ARQ

// Function to simulate sending a frame
void sendFrame(int frame) {
    cout << "Sender: Sending frame " << frame << endl;
}

// Function to simulate receiving a frame
bool receiveFrame(int frame) {
    // Simulate random errors with a 20% chance
    int randNum = rand() % 10;
    if (randNum < 8) {
        cout << "Receiver: Frame " << frame << " received successfully." << endl;
        return true;
    } else {
        cout << "Receiver: Error in frame " << frame << "." << endl;
        return false;
    }
}

int main() {
    srand(time(0)); // Initialize random seed

    int totalFrames = 10; // Total frames to be sent
    int frame = 1;        // Start from frame 1

    while (frame <= totalFrames) {
        // Send frames within the window size
        for (int i = 0; i < WINDOW_SIZE && frame <= totalFrames; ++i) {
            sendFrame(frame);
            frame++;
        }

        // Simulate acknowledgment and error detection
        for (int i = frame - WINDOW_SIZE; i < frame; ++i) {
            if (receiveFrame(i)) {
                // Frame successfully received, acknowledgment simulated
                cout << "Receiver: ACK for frame " << i << " sent." << endl;
            } else {
                // If there's an error, retransmit from the erroneous frame
                cout << "Sender: Error detected. Resending from frame " << i << "." << endl;
                frame = i; // Go back to the erroneous frame
                break;
            }
        }

        // Simulate delay before next window of frames
        sleep(1);
    }

    cout << "All frames sent and acknowledged successfully." << endl;
    return 0;
}
