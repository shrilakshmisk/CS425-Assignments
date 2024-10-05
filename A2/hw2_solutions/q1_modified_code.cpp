#include <iostream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Initialize random seed
    int frameSize = 15;
    int messageSize = 10;
    string message, polynomial = "110101", crc, transmittedFrame;

    // Generating bit string for the message
    message = "";
    for (int i = 0; i < messageSize; ++i) {
        message += ((rand() & 1) ? '1' : '0');
    }

    // Augment message with zeros for CRC calculation
    string augmentedMessage = message + string(polynomial.size() - 1, '0');

    // CRC calculation using XOR
    for (size_t i = 0; i + polynomial.size() <= augmentedMessage.size(); ++i) {
        if (augmentedMessage[i] == '1') {
            for (size_t j = 0; j < polynomial.size(); ++j) {
                augmentedMessage[i + j] = (augmentedMessage[i + j] != polynomial[j]) ? '1' : '0';
            }
        }
    }

    // Extract CRC and form the frame for transmission
    crc = augmentedMessage.substr(message.size());
    transmittedFrame = message + crc;

        cout << "Message: " << message << "\nPolynomial: " << polynomial
         << "\nCRC: " << crc << "\nTransmission Frame without errors: \t" << transmittedFrame;

    // Simulate transmission errors
    int errorProbability = 10;
    for (char &bit : transmittedFrame) {
        if (rand() % errorProbability == 0) bit = (bit == '1') ? '0' : '1';
    }

    // Validate transmission frame with polynomial
    string checkFrame = transmittedFrame + string(polynomial.size() - 1, '0');
    for (size_t i = 0; i + polynomial.size() <= checkFrame.size(); ++i) {
        if (checkFrame[i] == '1') {
            for (size_t j = 0; j < polynomial.size(); ++j) {
                checkFrame[i + j] = (checkFrame[i + j] != polynomial[j]) ? '1' : '0';
            }
        }
    }

    // Determine validity of the transmitted frame
    bool isValid = checkFrame.substr(transmittedFrame.size()).find('1') == string::npos;

    // Output results
    cout << "\nTransmission Frame after errors: \t" << transmittedFrame
         << "\nFrame Validity: " << (isValid ? "Valid" : "Invalid") << endl;

    return 0;
}
