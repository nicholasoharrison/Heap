#include <iostream>
#include <fstream>
#include <sstream>

#include "ArrayHeap.h"
#include "PriorityQueue.h"

using namespace std;



int main() {


    string inputFileName, actionFileName, outputFileName;

    // Output file
    cout << "\nEnter the name of the output file: ";
    cin >> outputFileName;
    ofstream outputFile(outputFileName);

    if (!outputFile) {
        cout << "\nError opening output file!" << endl;
        return 1;
    }

    // Initial heap size
    cout << "\nEnter initial size of the heap (or 0 to use the default size): ";
    int initialSize;
    cin >> initialSize;
    if (cin.fail()) {
        outputFile << "\nInvalid input capacity.";
        return 1;
    }



    ArrayHeap aHeap(initialSize);
    PriorityQueue pQueue(initialSize);



    // Input file
    cout << "\nEnter the name of the input file: ";
    cin >> inputFileName;
    ifstream inputFile(inputFileName);

    if (!inputFile) {
        outputFile << "\nError opening input file!" << endl;
        outputFile.close();
        return 1;
    }

    cout << "\n\n\n";

    // Input file reading
    string line;
    priorityData insertData;
    while (inputFile >> insertData.priorityValue >> insertData.dataValue) { // Checks formatting of file and inputs the file data into correct variables in one step
        outputFile << "\nValue inserted to the heap: " << insertData.priorityValue << " - " << insertData.dataValue;
        outputFile << "\n\tCurrent size: " << pQueue.getCurrentSize() << ", capacity: " << pQueue.getCapacity();
        pQueue.addInitialValues(insertData);
    }


    pQueue.initialize(); // Heapifies the arrayHeap



    outputFile << "\n\nCreation of heap complete.";
    outputFile << "\n\n\n" << pQueue.toString();
    outputFile << "\n\n\n";



    // Ask user for action mode
    char actionMode;
    cout << "\nEnter 'U' for user entered actions only, 'F' for action file only, or 'B' for both: ";
    cin >> actionMode;
    while (actionMode != 'U' && actionMode != 'u' && actionMode != 'f' && actionMode != 'F' && actionMode != 'B' && actionMode != 'b') {
        cout << "\nEnter a valid character (U, F, B): ";
        cin >> actionMode;
    }



    // Input name of action file if needed
    if (actionMode == 'F' || actionMode == 'B' || actionMode == 'f' || actionMode == 'b') {
        cout << "\nEnter the name of the action file: ";
        cin >> actionFileName;
    }



    // Read actions from file if chosen
    if (actionMode == 'F' || actionMode == 'B' || actionMode == 'f' || actionMode == 'b') {
        ifstream actionFile(actionFileName);
        if (!actionFile) {
            outputFile << "\nError opening action file!" << endl;
        }
        else {
            ifstream operationFile(actionFileName);
            if (operationFile.peek() == ifstream::traits_type::eof()) {
                outputFile << "\nEmpty Actions File - No Operations Performed" << endl;
            }
            else {
                while (getline(operationFile, line)) {
                    char actionCode;
                    int priorityValue;
                    string strData;
                    priorityData insertedVal;

                    istringstream iss(line);
                    // Checks if each line is in the correct format then proceeds with the operations
                    if (iss >> actionCode) {
                        switch (actionCode) {
                        case 'I':
                            iss >> strData >> priorityValue;
                            insertedVal.dataValue = strData;
                            insertedVal.priorityValue = priorityValue;
                            pQueue.insert(insertedVal);
                            cout << "\nValue inserted to the heap: " << insertedVal.priorityValue << " - " << insertedVal.dataValue;
                            outputFile << "\nValue inserted to the heap: " << insertedVal.priorityValue << " - " << insertedVal.dataValue;
                            outputFile << "\n\tCurrent size: " << pQueue.getCurrentSize() << ", capacity: " << pQueue.getCapacity();
                            cout << pQueue.toString();
                            outputFile << pQueue.toString();
                            break;

                        case 'R':
                            if (pQueue.getCurrentSize() != 0) {
                                cout << "\nValue removed from the top of the heap: " << pQueue.returnMin().priorityValue << " - " << pQueue.returnMin().dataValue;
                                outputFile << "\nValue removed from the top of the heap: " << pQueue.returnMin().priorityValue << " - " << pQueue.returnMin().dataValue;
                                outputFile << "\n\tCurrent size: " << pQueue.getCurrentSize() << ", capacity: " << pQueue.getCapacity();
                                pQueue.remove();
                                cout << pQueue.toString();
                                outputFile << pQueue.toString();
                            }
                            else {
                                cout << "\nAttempt to remove element from empty heap";
                                outputFile << "\nAttempt to remove element from empty heap";
                            }
                            break;

                        case 'S':
                            if (pQueue.getCurrentSize() != 0) {
                                cout << "\nValue at the top of the heap: " << pQueue.returnMin().priorityValue << " - " << pQueue.returnMin().dataValue;
                                outputFile << "\nValue at the top of the heap: " << pQueue.returnMin().priorityValue << " - " << pQueue.returnMin().dataValue;
                                pQueue.counters[4]++; // Requested return minimum value (from actions file or user)
                            }
                            else {
                                cout << "\nAttempt to remove element from empty heap";
                                outputFile << "\nAttempt to remove element from empty heap";
                            }
                            break;

                        case 'A':
                            cout << pQueue.toString();
                            outputFile << pQueue.toString();
                            pQueue.counters[5]++; // Requested print all values
                            break;

                        default:
                            cout << "\nError: Invalid Action Code - skipping line: " << line << endl;
                            break;
                        }
                    }
                    else {
                        cout << "\nError: Invalid format for operation - skipping line: " << line << endl;
                    }
                }

            }
        }
    }


    // Get user input in cases where it was requested
    if (actionMode == 'U' || actionMode == 'B' || actionMode == 'u' || actionMode == 'b') {
        char choice = 'y';
        priorityData insertedVal;
        while (choice == 'y' || choice == 'Y') {
            cout << "\nEnter action code ('I' for insert, 'R' for remove, 'S' for see top element, 'A' for print all values): ";
            char actionCode;
            cin >> actionCode;

            switch (actionCode) {
            case 'I': {
                int priorityValue;
                string strData;
                cout << "\nEnter priority value: ";
                cin >> priorityValue;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter an integer value: ";
                    cin >> priorityValue;
                }
                cout << "\nEnter data string: ";
                cin.ignore();
                getline(cin, strData);
                insertedVal.dataValue = strData;
                insertedVal.priorityValue = priorityValue;
                pQueue.insert(insertedVal);
                cout << "\nValue inserted to the heap: " << insertedVal.priorityValue << " - " << insertedVal.dataValue;
                outputFile << "\nValue inserted to the heap: " << insertedVal.priorityValue << " - " << insertedVal.dataValue;
                cout << pQueue.toString();
                outputFile << pQueue.toString();
                break;
            }
            case 'R':
                if (pQueue.getCurrentSize() != 0) {
                    cout << "\nValue removed from the top of the heap: " << pQueue.returnMin().priorityValue << " - " << pQueue.returnMin().dataValue;
                    outputFile << "\nValue removed from the top of the heap: " << pQueue.returnMin().priorityValue << " - " << pQueue.returnMin().dataValue;
                    pQueue.remove();
                    cout << pQueue.toString();
                    outputFile << pQueue.toString();
                }
                else {
                    cout << "\nAttempt to remove element from empty heap";
                    outputFile << "\nAttempt to remove element from empty heap";
                }
                break;
            case 'S':
                if (pQueue.getCurrentSize() != 0) {
                    cout << "\nValue at the top of the heap: " << pQueue.returnMin().priorityValue << " - " << pQueue.returnMin().dataValue;
                    outputFile << "\nValue at the top of the heap: " << pQueue.returnMin().priorityValue << " - " << pQueue.returnMin().dataValue;
                    pQueue.counters[4]++; // Requested return minimum value (from actions file or user)
                }
                else {
                    cout << "\nAttempt to remove element from empty heap";
                    outputFile << "\nAttempt to remove element from empty heap";
                }
                break;
            case 'A':
                cout << pQueue.toString();
                outputFile << pQueue.toString();
                pQueue.counters[5]++; // Requested print all values
                break;
            default:
                cout << "\nInvalid action code." << endl;
            }

            cout << "\nDo you want to perform more actions? (y/n): ";
            cin >> choice;
            while (choice != 'y' && choice != 'N' && choice != 'Y' && choice != 'n') {
                cout << "\nEnter a valid character (y/n): ";
                cin >> choice;
            }
        }
    }

    outputFile << "\n\n\n\n";
    outputFile<<"\nTotal number of Inserts - Initialization                                 " << pQueue.counters[0];
    outputFile<<"\nTotal number of heap - down actions - Initialization                     " << pQueue.counters[1];
    outputFile<<"\nTotal number of user requested Inserts                                   " << pQueue.counters[2];
    outputFile<<"\nTotal number of user requested Removes                                   " << pQueue.counters[3];
    outputFile<<"\nTotal number of user requested Return top                                " << pQueue.counters[4];
    outputFile<<"\nTotal number of user requested Print                                     " << pQueue.counters[5];
    outputFile<<"\nTotal number of heap actions for user actions                            " << pQueue.counters[7] + pQueue.counters[8];
    outputFile<<"\n\tTotal number of heap - up actions                                " << pQueue.counters[7];
    outputFile<<"\n\tTotal number of heap - down actions                              " << pQueue.counters[8];



    // Close output file
    outputFile.close();

    return 0;
}