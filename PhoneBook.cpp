﻿#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Contact {
    std::string firstName;
    std::string lastName;
    std::string separator;
    std::string phoneNumber;
};

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

int countNumbersInString(const std::string& str) {
    int count = 0;
    bool inNumber = false;

    for (char c : str) {
        if (isDigit(c)) {
            if (!inNumber) {
                inNumber = true;
                count++;
            }
        }
        else {
            inNumber = false;
        }
    }

    return count;
}

bool compareContacts(const Contact& a, const Contact& b, std::string criteria, bool descending) {
    bool result;
    if (criteria == "Name") {
        result = a.firstName < b.firstName;
    }
    else if (criteria == "Surname") {
        result = a.lastName < b.lastName;
    }
    else if (criteria == "PhoneNumberCode") {
        int aCode = std::stoi(a.phoneNumber.substr(0, 3));
        int bCode = std::stoi(b.phoneNumber.substr(0, 3));
        result = aCode < bCode || (aCode == bCode && a.phoneNumber < b.phoneNumber);
    }
    else {
        result = false;
    }

    return descending ? result : !result;
}

void bubbleSort(Contact contacts[], int size, std::string criteria, bool descending) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (compareContacts(contacts[j], contacts[j + 1], criteria, descending)) {
                std::swap(contacts[j], contacts[j + 1]);
            }
        }
    }
}


void validateContacts(Contact contacts[], int size) {
    bool hasValidationErrors = false;

    for (int i = 0; i < size; i++) {
        std::cout << contacts[i].firstName << " " << contacts[i].lastName << contacts[i].separator << contacts[i].phoneNumber << std::endl;
    }
    std::cout << "\nValidation" << std::endl;

    for (int i = 0; i < size; i++) {
        bool hasValidationErrorForContact = false;
        std::string validationMessage = "line " + std::to_string(i + 1) + ": ";

        if (contacts[i].phoneNumber.size() != 9) {
            hasValidationErrorForContact = true;
            validationMessage += "phone number should be with 9 digits";
        }

        if (contacts[i].separator != ":" && contacts[i].separator != "-") {
            if (hasValidationErrorForContact) {
                validationMessage += ", ";
            }
            validationMessage += "the separator should be : or -";
        }

        if (hasValidationErrorForContact) {
            std::cout << validationMessage << "." << std::endl;
            hasValidationErrors = true;
        }
    }

    if (!hasValidationErrors) {
        std::cout << "No validation errors found." << std::endl;
    }
}


int main() {
    const int maxSize = 100;
    Contact contacts[maxSize];
    int size = 0;
    std::string criteria;
    bool descending = false;

    std::ifstream inputFile("C:/Users/ACER/Desktop/Arman crag/myFile.txt");

    if (!inputFile) {
        std::cerr << "Failed to open the input file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        Contact contact;

        if (ss >> contact.firstName >> contact.lastName >> contact.separator >> contact.phoneNumber) {
            contacts[size] = contact;
            size++;
        }
    }

    inputFile.close();

    std::cout << "Do you want to validate contacts? (yes or no): ";
    std::string validateInput;
    std::cin >> validateInput;

    if (validateInput == "yes") {
        validateContacts(contacts, size);
    }

    std::cout << "\nDo you want to sort contacts? (yes or no): ";
    std::string sortInput;
    std::cin >> sortInput;

    if (sortInput == "yes") {
        std::cout << "Please choose sorting criteria: Name, Surname, or PhoneNumberCode: ";
        std::cin >> criteria;

        std::string descendingInput;
        std::cout << "Sort in ascending or descending order? ";
        std::cin >> descendingInput;

        if (descendingInput == "descending" || descendingInput == "Descending" || descendingInput == "1") {
            descending = true;
        }
        else {
            descending = false;
        }

        bubbleSort(contacts, size, criteria, descending);

        std::cout << "Sorted entries:" << std::endl;

        for (int i = 0; i < size; i++) {
            std::cout << contacts[i].firstName << " " << contacts[i].lastName << contacts[i].separator << contacts[i].phoneNumber << std::endl;
        }
    }

    return 0;
}
