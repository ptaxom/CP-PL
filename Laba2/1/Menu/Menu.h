//
// Created by ptaxom on 14.10.2018.
//

#ifndef INC_1_MENU_H
#define INC_1_MENU_H

#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <deque>
#include "../Cat/Cat.h"


//TODO 2 fields sort

//TODO selecting by field


class Menu {



    std::deque<Cat> catsList;

    static bool isCorrectString(const std::string &st);

    void printCatsList();

    void addCat();

    void clearList();

    void deleteCat();

    void deleteCatByNum();

    void deleteCatByField();

    void sortListByOneField();

    void sortListByTwoFields();

    std::function<bool(Cat, Cat)> createPairComparator(const std::pair<int, int> &keys);

    int chooseComparator(std::string invitation, std::string action);

public:

    std::vector<std::function<bool(Cat, Cat)>> comparators = { [](Cat a, Cat b) { return a.getWeight() < b.getWeight(); },
                                                               [](Cat a, Cat b) { return a.getAge() < b.getAge(); },
                                                               [](Cat a, Cat b) { return a.getName() < b.getName(); },
                                                               [](Cat a, Cat b) { return a.isMale(); } };

    std::vector<std::function<bool(Cat, Cat)>> equalityComparators =
            { [](Cat a, Cat b) { return a.getWeight() == b.getWeight(); },
              [](Cat a, Cat b) { return a.getAge() == b.getAge(); },
              [](Cat a, Cat b) { return a.getName() == b.getName(); },
              [](Cat a, Cat b) { return a.isMale() == b.isMale(); } };

    Menu();

    static int getPositionFromParagraphs(const std::vector<std::string> &paragraphs, int pos = 1);

    static int getInt(const std::string &invitation, int min, int max);

    static Cat readCat();

    void handling();

    static std::string readString(const std::string &invitation);

    static int keyAction();
};


#endif //INC_1_MENU_H
