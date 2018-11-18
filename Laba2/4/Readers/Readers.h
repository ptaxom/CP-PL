//
// Created by ptaxom on 22.10.2018.
//

#ifndef INC_4_READERS_H
#define INC_4_READERS_H
#include <iostream>
#include <fstream>
#include <vector>


struct Purchase{
    std::string buyerName;
    std::string purchaseName;
    int cost;
};


std::ifstream loadFile(std::string path);

template<class T>
T read(std::ifstream &file);

template <>
std::string read<std::string>(std::ifstream &file);


template<>
Purchase read<Purchase>(std::ifstream &file);

std::ostream& operator<<(std::ostream& s,const Purchase &p);

void printMostExpencivePurchase(const std::vector<Purchase> &purchases);

void printMostSpenders(const std::vector<Purchase> &purchases);

void printMostSpenderNames(const std::vector<Purchase> &purchases);


#endif //INC_4_READERS_H
