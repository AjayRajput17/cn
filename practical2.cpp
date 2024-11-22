#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Function prototypes
void parityCheck();
void crcCheck();
void hammingCode();

// Menu-driven program
int main()
{
  int choice;

  do
  {
    cout << "\nError Detection and Correction Menu" << endl;
    cout << "1. Parity Check" << endl;
    cout << "2. Cyclic Redundancy Check (CRC)" << endl;
    cout << "3. Hamming Code" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      parityCheck();
      break;
    case 2:
      crcCheck();
      break;
    case 3:
      hammingCode();
      break;
    case 4:
      cout << "Exiting the program." << endl;
      break;
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  } while (choice != 4);

  return 0;
}

// Function for Parity Check
void parityCheck()
{
  string data;
  cout << "Enter the binary data: ";
  cin >> data;

  // Count the number of 1s
  int count = 0;
  for (char bit : data)
  {
    if (bit == '1')
    {
      count++;
    }
  }

  // Check parity
  if (count % 2 == 0)
  {
    cout << "No error detected (Even Parity)." << endl;
  }
  else
  {
    cout << "Error detected (Odd Parity)." << endl;
  }
}

// Function for CRC
void crcCheck()
{
  string data, generator;
  cout << "Enter the binary data: ";
  cin >> data;
  cout << "Enter the generator polynomial: ";
  cin >> generator;

  string augmented_data = data + string(generator.length() - 1, '0');
  string remainder = augmented_data;

  for (size_t i = 0; i <= data.length(); ++i)
  {
    if (remainder[i] == '1')
    {
      for (size_t j = 0; j < generator.length(); ++j)
      {
        remainder[i + j] = (remainder[i + j] == generator[j]) ? '0' : '1';
      }
    }
  }

  remainder = remainder.substr(data.length());
  cout << "CRC Remainder: " << remainder << endl;

  if (stoi(remainder) == 0)
  {
    cout << "No error detected." << endl;
  }
  else
  {
    cout << "Error detected." << endl;
  }
}

// Function for Hamming Code
void hammingCode()
{
  int m;
  cout << "Enter the number of data bits: ";
  cin >> m;

  vector<int> data(m);
  cout << "Enter the data bits one by one: \n";
  for (int i = 0; i < m; ++i)
  {
    cin >> data[i];
  }

  int r = 0;
  while ((1 << r) < (m + r + 1))
  {
    ++r;
  }

  vector<int> hamming_code(m + r, 0);
  int j = 0;
  for (int i = 1; i <= m + r; ++i)
  {
    if ((i & (i - 1)) == 0)
    {
      continue;
    }
    hamming_code[i - 1] = data[j++];
  }

  for (int i = 0; i < r; ++i)
  {
    int parity_position = (1 << i);
    int parity = 0;
    for (int j = 1; j <= m + r; ++j)
    {
      if (j & parity_position)
      {
        parity ^= hamming_code[j - 1];
      }
    }
    hamming_code[parity_position - 1] = parity;
  }

  cout << "Hamming Code: ";
  for (int bit : hamming_code)
  {
    cout << bit << " ";
  }
  cout << endl;

  int error_position = 0;
  cout << "Enter the received Hamming code: \n";
  for (int i = 0; i < m + r; ++i)
  {
    cin >> hamming_code[i];
  }

  for (int i = 0; i < r; ++i)
  {
    int parity_position = (1 << i);
    int parity = 0;
    for (int j = 1; j <= m + r; ++j)
    {
      if (j & parity_position)
      {
        parity ^= hamming_code[j - 1];
      }
    }
    if (parity != 0)
    {
      error_position += parity_position;
    }
  }

  if (error_position == 0)
  {
    cout << "No error detected." << endl;
  }
  else
  {
    cout << "Error detected at position: " << error_position << endl;
    hamming_code[error_position - 1] ^= 1;
    cout << "Corrected Hamming Code: ";
    for (int bit : hamming_code)
    {
      cout << bit << " ";
    }
    cout << endl;
  }
}

// Parity Check
// Input Example:
// plaintext
// Copy code
// Enter the binary data: 1010101

// Cyclic Redundancy Check (CRC)
// Input Example:
// plaintext
// Copy code
// Enter the binary data: 110101
// Enter the generator polynomial: 1011

// Hamming Code
// Generating Hamming Code:
// Input Example:
// plaintext
// Copy code
// Enter the number of data bits: 4
// Enter the data bits one by one:
// 1
// 0
// 1
// 1