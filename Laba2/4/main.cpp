#include <iostream>
#include "Readers/Readers.h"

int main() {
    try {
        std::ifstream inFile = loadFile("test1.bin");
        std::vector<Purchase> purchases;
        while(inFile.peek() != EOF)
            purchases.push_back(read<Purchase>(inFile));
        inFile.close();
        printMostExpencivePurchase(purchases);
        printMostSpenders(purchases);
        printMostSpenderNames(purchases);
    } catch (std::exception &ex){
        std::cout << ex.what() << std::endl;
    }
    return 0;

}