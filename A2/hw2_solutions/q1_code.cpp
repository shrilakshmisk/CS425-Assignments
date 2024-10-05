#include <iostream>
#include <cstdlib>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Initialize random seed

    int frameSize = 15, messageSize = 10;
    string message, polynomial, crc, sequence;

    // User input loop for frame and message sizes
    while (true) {
        cout << "Enter frame size (n): ";
        cin >> frameSize;
        cout << "Enter message size (k): ";
        cin >> messageSize;
        
        if (frameSize - messageSize + 1 <= 0) {
            cout << "Frame size (n) must be greater than or equal to message size (k).\n";
            continue;
        } else {
            // Exit the loop if valid sizes are provided
            break;
        }
    }

    // Loop for two examples
    for (int example = 1; example <= 2; ++example) {
        cout << "\nExample " << example << ":\n";

        // Generate random bit string for message
        message = "";
        for (int i = 0; i < messageSize; ++i) {
            message += ((rand() & 1) ? '1' : '0');
        }

        // Generate random bit string for polynomial, ensuring the first bit is '1'
        do {
            polynomial = "";
            for (int i = 0; i < frameSize - messageSize + 1; ++i) {
                polynomial += ((rand() & 1) ? '1' : '0');
            }
        } while (polynomial[0] != '1');

        // Append zeroes to message for CRC calculation
        sequence = message;
        for (size_t i = 0; i < polynomial.size() - 1; ++i) {
            sequence += '0';
        }

        // Perform XOR for CRC calculation
        for (size_t i = 0; i < sequence.size(); ++i) {
            if (i + polynomial.size() <= sequence.size()) {
                if (sequence[i] == '1') {
                    for (size_t j = 0; j < polynomial.size(); ++j) {
                        sequence[i + j] = ((sequence[i + j] != polynomial[j]) ? '1' : '0');
                    }
                }
            }
        }

        // Extract CRC from modified sequence
        crc = sequence.substr(sequence.size() - polynomial.size() + 1);

        cout << "Message: " << message << "\nPolynomial: " << polynomial << '\n' << "CRC: " << crc << "\nFull Sequence: " << message + crc << '\n';

        // Verify the message with appended CRC
        sequence = message + crc; // Reconstruct the sequence with CRC for verification
        string remainder = "";
        for (size_t i = 0; i < sequence.size(); ++i) {
            if (i + polynomial.size() <= sequence.size()) {
                if (sequence[i] == '1') {
                    for (size_t j = 0; j < polynomial.size(); ++j) {
                        sequence[i + j] = ((sequence[i + j] != polynomial[j]) ? '1' : '0');
                    }
                }
            } else {
                remainder += sequence[i];
            }
        }

        // Check if the remainder is zero
        bool isValid = true;
        for (const auto &bit : remainder) {
            if (bit == '1') {
                isValid = false;
                break;
            }
        }

        cout << "Verification: " << (isValid ? "Valid" : "Invalid") << ". The sequence " << (isValid ? "should" : "should not") << " be accepted.\n";
    }

    return 0;
}
