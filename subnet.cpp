#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Function to convert a string to an integer
int stringToInt(const string& str) {
    int num;
    stringstream ss(str);
    ss >> num;
    return num;
}

// Function to calculate subnet details
void calculateSubnet(const string& ipAddress, const string& subnetMask) {
    vector<int> ipParts;
    vector<int> maskParts;

    // Split IP address into parts
    istringstream ipStream(ipAddress);
    string ipPart;
    while (getline(ipStream, ipPart, '.')) {
        ipParts.push_back(stringToInt(ipPart));
    }

    // Split subnet mask into parts
    istringstream maskStream(subnetMask);
    string maskPart;
    while (getline(maskStream, maskPart, '.')) {
        maskParts.push_back(stringToInt(maskPart));
    }

    // Calculate the network address
    vector<int> networkAddress(4);
    for (int i = 0; i < 4; ++i) {
        networkAddress[i] = ipParts[i] & maskParts[i];
    }

    // Calculate the broadcast address
    vector<int> broadcastAddress(4);
    for (int i = 0; i < 4; ++i) {
        broadcastAddress[i] = ipParts[i] | (~maskParts[i] & 0xFF);
    }

    // Increment for usable IP range
    vector<int> firstUsableIP = networkAddress;
    firstUsableIP[3]++;
    
    vector<int> lastUsableIP = broadcastAddress;
    lastUsableIP[3]--;

    // Display subnet details
    cout << "\nSubnet Details:\n";

    cout << "Network Address: ";
    for (int i = 0; i < 4; ++i) {
        cout << networkAddress[i];
        if (i < 3) cout << ".";
    }
    cout << endl;

    cout << "Broadcast Address: ";
    for (int i = 0; i < 4; ++i) {
        cout << broadcastAddress[i];
        if (i < 3) cout << ".";
    }
    cout << endl;

    cout << "Usable IP Range: ";
    for (int i = 0; i < 4; ++i) {
        cout << firstUsableIP[i];
        if (i < 3) cout << ".";
    }
    cout << " - ";
    for (int i = 0; i < 4; ++i) {
        cout << lastUsableIP[i];
        if (i < 3) cout << ".";
    }
    cout << endl;
}

int main() {
    string ipAddress, subnetMask;
    cout << "Enter IP Address: ";
    cin >> ipAddress;
    cout << "Enter Subnet Mask: ";
    cin >> subnetMask;
    
    calculateSubnet(ipAddress, subnetMask);

    return 0;
}
