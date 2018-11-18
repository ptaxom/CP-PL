//
// Created by ptaxom on 22.10.2018.
//

#include <algorithm>
#include <map>
#include "Readers.h"


std::ifstream loadFile(std::string path) {
    std::ifstream inFile(path, std::ios::binary);
    if (!inFile)
        throw std::runtime_error("Can't open file " + path);
    return inFile;
}

template<class T>
T read(std::ifstream &file) {
    T readedValue = 0;
    file.read(reinterpret_cast<char *>(&readedValue), sizeof(T));
    if (file.gcount() != sizeof(readedValue))
        throw std::runtime_error("Read error when reading T!");
    return readedValue;
}

template <>
std::string read<std::string>(std::ifstream &file) {
    std::uint64_t size = read<std::uint64_t>(file);

    std::string readedString;
    try {
        readedString.resize(size);
    }
    catch (std::bad_alloc &ex) {
        throw std::runtime_error("Read error when reading string!");
    }

    file.read(reinterpret_cast<char*>(&readedString[0]), sizeof(char) * size);
    if (file.gcount() != sizeof(char)*size)
        throw std::runtime_error("Read error when reading string!");
    return readedString;
}


template<>
Purchase read<Purchase>(std::ifstream &file) {
    Purchase purchase;
    try {
        purchase.buyerName = read<std::string>(file);
        purchase.purchaseName = read<std::string>(file);
        purchase.cost = read<int>(file);
    }
    catch (std::runtime_error &ex) {
        throw std::runtime_error("Read error when reading struct Purchase!");
    }
    return purchase;
}

std::ostream& operator<<(std::ostream& s,const Purchase &p){
    s << "Buyer name: "<<p.buyerName<<std::endl<<"Purchase: "<<p.purchaseName<<std::endl<<"Cost: "<<p.cost;
    return s;
}

void printMostExpencivePurchase(const std::vector<Purchase> &purchases){
    Purchase it = *std::max_element(purchases.begin(), purchases.end(), [](Purchase a, Purchase b){
        return a.cost < b.cost;
    });
    std::cout << "The most expensive purchase is "<< it.purchaseName <<" : "<< it.cost << "" << std::endl;
}

void printMostSpenders(const std::vector<Purchase> &purchases){
    std::map<std::string, std::pair<int, int>> purchaseMap;
    for(const auto &p : purchases){
        purchaseMap[p.purchaseName].first++;
        purchaseMap[p.purchaseName].second+=p.cost;
    }
    auto mostPopular = *std::max_element(purchaseMap.begin(), purchaseMap.end(), [](std::pair<std::string, std::pair<int, int>> a, std::pair<std::string, std::pair<int, int>> b){
        return a.second.first < b.second.first;
    });
    std::cout << "The most popular purchase is "<< mostPopular.first <<" : " <<mostPopular.second.first << " times"<<std::endl;

    auto mostCostly = *std::max_element(purchaseMap.begin(), purchaseMap.end(), [](std::pair<std::string, std::pair<int, int>> a, std::pair<std::string, std::pair<int, int>> b){
        return a.second.second < b.second.second;
    });

    std::cout << "Most costly category is " << mostCostly.first << " : " << mostCostly.second.second << std::endl;
}

void printMostSpenderNames(const std::vector<Purchase> &purchases){
    std::map<std::string, std::pair<int, int>> spends;
    for(const auto &p : purchases){
        spends[p.buyerName].first++;
        spends[p.buyerName].second+=p.cost;
    }
    auto mostSpender = *std::max_element(spends.begin(), spends.end(), [](std::pair<std::string, std::pair<int, int>> a, std::pair<std::string, std::pair<int, int>> b){
        return a.second.first < b.second.first;
    });

    std::cout << (mostSpender.second.first > 10 ? "All made a lot of purchases" : "Very sparingly")<<std::endl;
    auto mostCostly = *std::max_element(spends.begin(), spends.end(), [](std::pair<std::string, std::pair<int, int>> a, std::pair<std::string, std::pair<int, int>> b){
        return a.second.second < b.second.second;
    });
    std::string ans("Spenders: ");
    for(const auto &p : spends){
        if (p.second.second == mostCostly.second.second)
            ans+= p.first+" : " + std::to_string(p.second.second)+", ";
    }
    std::cout << ans.substr(0, ans.length()-2);



}