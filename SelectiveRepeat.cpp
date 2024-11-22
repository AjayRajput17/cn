#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <unistd.h> // For sleep()

using namespace std;

const int WINDOW_SIZE = 4;   // Window size for Selective Repeat ARQ
const int TOTAL_FRAMES = 10; // Total number of frames to send

// Function to simulate sending a frame
void sendFrame(int frame) {
    cout << "Sender: Sending frame " << frame << endl;
}

// Function to simulate receiving a frame (with random chance of error)
bool receiveFrame(int frame) {
    // Simulate a random error with a 20% chance
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

    bool ack[TOTAL_FRAMES + 1] = {false}; // Acknowledgment array to track received frames
    int send_base = 1;                    // The base of the sender's window
    int next_frame = 1;                   // The next frame to send

    // Loop until all frames are acknowledged
    while (send_base <= TOTAL_FRAMES) {
        // Send frames within the window size
        while (next_frame < send_base + WINDOW_SIZE && next_frame <= TOTAL_FRAMES) {
            sendFrame(next_frame);
            next_frame++;
        }

        // Simulate receiving frames and their acknowledgments
        for (int i = send_base; i < next_frame; ++i) {
            if (!ack[i]) { // Only process frames that haven't been acknowledged
                bool received = receiveFrame(i);
                if (received) {
                    ack[i] = true; // Mark the frame as acknowledged
                    cout << "Receiver: ACK for frame " << i << " sent.\n";
                } else {
                    cout << "Sender: Retransmitting frame " << i << " due to error.\n";
                    sendFrame(i); // Retransmit only the erroneous frame

                    // Retransmit once, continue loop to simulate receiver retry
                    if (receiveFrame(i)) {
                        ack[i] = true; // Acknowledge after successful retransmission
                        cout << "Receiver: ACK for frame " << i << " sent.\n";
                    }
                }
            }
        }

        // Slide the sender's window if frames are acknowledged
        while (ack[send_base] && send_base <= TOTAL_FRAMES) {
            send_base++; // Move the window forward
        }

        sleep(1); // Simulate delay between transmissions
    }

    cout << "All frames sent and acknowledged successfully." << endl;
    return 0;
}
