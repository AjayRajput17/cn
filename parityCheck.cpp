#include <iostream>
#include <vector>
#include <string>
using namespace std;



// Parity Check Functions
string parityCheck(string data) {
    int count = 0;
    for (char c : data) {
        if (c == '1') count++;
    }
    return (count % 2 == 0) ? "0" : "1";
}

void parityDetectAndCorrect(string dataWithParity) {
    string data = dataWithParity.substr(0, dataWithParity.size() - 1);
    string receivedParity = dataWithParity.substr(dataWithParity.size() - 1);
    string calculatedParity = parityCheck(data);

    if (calculatedParity == receivedParity) {
        cout << "No error detected. Data: " << data << endl;
    } else {
        cout << "Error detected! Data received: " << dataWithParity << ", Parity mismatch.\n";
    }
}




// Cyclic Redundancy Check (CRC) Functions
string xorStrings(string a, string b) {
    string result = "";
    for (size_t i = 1; i < b.size(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string crcGenerate(string data, string divisor) {
    string paddedData = data + string(divisor.size() - 1, '0');
    string remainder = paddedData.substr(0, divisor.size());

    for (size_t i = 0; i <= paddedData.size() - divisor.size(); i++) {
        if (remainder[0] == '1') {
            remainder = xorStrings(remainder, divisor) + paddedData[divisor.size() + i];
        } else {
            remainder = remainder.substr(1) + paddedData[divisor.size() + i];
        }
    }
    return remainder.substr(1);
}

void crcDetect(string dataWithCRC, string divisor) {
    string remainder = crcGenerate(dataWithCRC.substr(0, dataWithCRC.size() - divisor.size() + 1), divisor);
    if (remainder == string(divisor.size() - 1, '0')) {
        cout << "No error detected.\n";
    } else {
        cout << "Error detected! Remainder: " << remainder << endl;
    }
}




// Hamming Code Functions
string hammingEncode(string data) {
    int m = data.size();
    int r = 0;

    // Calculate the number of parity bits needed
    while ((1 << r) < (m + r + 1)) r++;

    vector<char> hammingData(m + r, '0');

    // Insert data bits into hammingData
    int j = 0;
    for (int i = 1; i <= hammingData.size(); i++) {
        if ((i & (i - 1)) != 0) { // If i is not a power of 2
            hammingData[i - 1] = data[j++];
        }
    }

    // Calculate parity bits
    for (int i = 0; i < r; i++) {
        int parityPos = (1 << i) - 1;
        int parity = 0;

        for (int j = parityPos; j < hammingData.size(); j += (parityPos + 1) * 2) {
            for (int k = j; k < j + parityPos + 1 && k < hammingData.size(); k++) {
                parity ^= (hammingData[k] - '0');
            }
        }
        hammingData[parityPos] = parity + '0';
    }
    return string(hammingData.begin(), hammingData.end());
}

void hammingDetectAndCorrect(string hammingData) {
    int n = hammingData.size();
    int r = 0;

    // Calculate the number of parity bits
    while ((1 << r) < n + 1) r++;

    int errorPos = 0;

    // Detect error position
    for (int i = 0; i < r; i++) {
        int parityPos = (1 << i) - 1;
        int parity = 0;

        for (int j = parityPos; j < hammingData.size(); j += (parityPos + 1) * 2) {
            for (int k = j; k < j + parityPos + 1 && k < hammingData.size(); k++) {
                parity ^= (hammingData[k] - '0');
            }
        }

        if (parity) errorPos += parityPos + 1;
    }

    if (errorPos) {
        cout << "Error detected at position: " << errorPos << endl;
        hammingData[errorPos - 1] = (hammingData[errorPos - 1] == '0') ? '1' : '0';
        cout << "Corrected Data: " << hammingData << endl;
    } else {
        cout << "No error detected. Data is correct: " << hammingData << endl;
    }
}

// Main Function
int main() {
    cout << "1. Parity Check\n";
    string data = "1101";  // Example data for parity check
    string parityBit = parityCheck(data);
    string dataWithParity = data + parityBit;
    cout << "Sent Data with Parity: " << dataWithParity << endl;
    parityDetectAndCorrect(dataWithParity);
    parityDetectAndCorrect("11010"); // Test with error



    cout << "\n2. Cyclic Redundancy Check (CRC)\n";
    string divisor = "1011"; // CRC Divisor
    string crcRemainder = crcGenerate(data, divisor);
    string dataWithCRC = data + crcRemainder;
    cout << "Sent Data with CRC: " << dataWithCRC << endl;
    crcDetect(dataWithCRC, divisor);
    crcDetect("11011010", divisor); // Test with error


    cout << "\n3. Hamming Code\n";
    string hammingData = hammingEncode(data);
    cout << "Encoded Data: " << hammingData << endl;
    hammingDetectAndCorrect(hammingData);
    hammingDetectAndCorrect("0110101"); // Test with error

    return 0;
}

