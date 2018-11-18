//
// Created by ptaxom on 14.10.2018.
//



#include <fstream>
#include "Menu.h"


void exitScreen(int type){
    system("cls");
    if (type == 0)
        std::cout << "Goodbye!" << std::endl;
    else {
        //int rCat = rand() % 2;
        int rCat = 0;
        std::ifstream screen(std::to_string(rCat) + ".txt");
        while (screen.peek() != EOF) {
            std::string line;
            getline(screen, line);
            std::cout << line << std::endl;
        }
    }
    getch();
}


int Menu::keyAction(){
    char z = getch();
    if (z == -32 || z == 224)
        z = -getch();
    return z;
}



int endlessInputLoop(const std::function<void (int)> &printer,const std::function<int (int, int)> &posChanger, int pos){
    printer(pos);
    while (true){
        int key = Menu::keyAction();
        if (key == 27) {
            system("cls");
            throw std::runtime_error("User canceled choosing");
        }
        if (key == 13) {
            system("cls");
            return pos;
        }
        pos = posChanger(key, pos);
        system("cls");
        printer(pos);
    }
}



 int Menu::getPositionFromParagraphs(const std::vector<std::string> &paragraphs, int pos) {
    int maxLength = -1;
    for (int i = 1; i < paragraphs.size(); i++)
        maxLength = std::max((int) paragraphs[i].size(), maxLength);
    maxLength++;

    auto printer = [&paragraphs, &maxLength](int pos) -> int {
        for (int i = 0; i < paragraphs.size(); i++)
            std::cout << std::setw(maxLength) << std::left << paragraphs[i] << (i == pos ? "<-----" : "") << std::endl;
    };
    int max_size = paragraphs.size(),  min_pos = 1;
    auto posChanger = [min_pos, max_size](int key, int pos){
        if (key == -72)
            return pos <= min_pos ? min_pos : pos-1;
        if (key == -80)
            return pos >= max_size-1 ? max_size-1 : pos+1;
        return pos;
    };

    return endlessInputLoop(printer, posChanger ,pos);

}

Menu::Menu() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ccInfo;
    ccInfo.bVisible = 0;
    ccInfo.dwSize = 20;
    SetConsoleCursorInfo(hStdOut, &ccInfo);
}



int Menu::getInt(const std::string &invitation, int min, int max) {
    auto printer = [invitation](int pos){
        std::cout<<invitation<<" "<<pos;
    };
    auto posChanger = [min, max](int key, int pos) -> int {
        if (key == -80)
            return pos <= min ? min : pos-1;
        if (key == -72)
            return pos >= max ? max : pos+1;
        return pos;
    };
    return endlessInputLoop(printer, posChanger, min);
}




bool Menu::isCorrectString(const std::string &st){
    int spacesCount = std::count(st.begin(), st.end(), ' ');
    return (!st.empty() && st.size() != spacesCount);
}


void Menu::printCatsList() {
    system("cls");
    if (this->catsList.empty())
        std::cout<<"No cats in list!"<<std::endl<<std::endl;
    else
        for(Cat cat : this->catsList)
            std::cout<<cat<<std::endl<<std::endl;
    getch();
    system("cls");
}

void Menu::addCat() {
    try{
        Cat cat = Menu::readCat();
        this->catsList.push_back(cat);
        std::cout<<"Successfully added!"<<std::endl;
    }
    catch (std::runtime_error &ex){
        system("cls");
        std::cout<<"You have cancelled input!"<<std::endl;
    }
    getch();
    system("cls");
}

void Menu::handling() {                     // 0                1           2                3           4
    std::vector<std::string> paragraphs = {"Select action: ", "Add cat", "Remove cat", "Clear list", "Sort list by primary field",
                                           "Sort list by primary and secondary field", "Print cats list", "Exit"};
                                        //   5                                            6                  7
    while (true){
        try{
            int action = Menu::getPositionFromParagraphs(paragraphs);
            switch(action){
                case 1: this->addCat(); break;
                case 2: this->deleteCat(); break;
                case 3: this->clearList(); break;
                case 4: this->sortListByOneField();  break;
                case 5: this->sortListByTwoFields(); break;
                case 6: this->printCatsList(); break;
                case 7: throw std::runtime_error("");
            }

        }
        catch (std::runtime_error& ex){
            break;
        }
    }
    exitScreen(1);
}

void Menu::clearList() {
    this->catsList.clear();
    std::cout<<"Successfully cleared!"<<std::endl;
    getch();
    system("cls");

}

void Menu::deleteCat() {
    if (!this->catsList.empty()) {
        std::vector<std::string> paragraphs = {"Choose selector for deleting:", "Delete by preview", "Delete by field"};
        try {
            int type = Menu::getPositionFromParagraphs(paragraphs);
            if (type == 1)
                this->deleteCatByNum();
            else this->deleteCatByField();
        }
        catch (std::runtime_error &ex) {
            system("cls");
            std::cout << "You have cancelled deleting!" << std::endl;
        }
    }
    else std::cout<<"Nothing to delete!"<<std::endl;
    getch();
    system("cls");

}



std::string Menu::readString(const std::string &invitation) {
    auto reader = [invitation]() -> std::string {
        std::string input;
        system("cls");
        std::cout<<invitation<<std::endl;
        std::getline(std::cin, input);
        return input;
    };
    std::string input = reader();
    while (!Menu::isCorrectString(input)){
        input = reader();
    }
    system("cls");
    return input;
}

Cat Menu::readCat() {
    Cat cat;
    cat.setName(Menu::readString("Enter name of a cat:"));
    std::vector<std::string> sexChoosing = {"Enter sex of a cat:", "Male", "Female"};
    cat.setMale(Menu::getPositionFromParagraphs(sexChoosing) == 1);
    cat.setAge(Menu::getInt("Enter age of a cat(years):", 0,30));
    cat.setWeight(Menu::getInt("Enter weight of a cat(KG's):", 0,30));
    return cat;
}

int Menu::chooseComparator(std::string invitation, std::string action) {
    std::vector<std::string> paragraphs = {invitation, action+" by weight", action+" by age", action+" by name", action+" by sex"};
    return Menu::getPositionFromParagraphs(paragraphs);
}

void Menu::sortListByOneField() {
    if (catsList.size() > 1)
        try{
            auto comparator = comparators[Menu::chooseComparator("Select primary field for sort","Sort")-1];
            std::sort(catsList.begin(), catsList.end(), comparator);
            std::cout<<"Successfully added!"<<std::endl;
        }
        catch (std::runtime_error &ex){
            system("cls");
            std::cout << "You have cancelled sorting!" << std::endl;
        }
    else std::cout<<"Nothing to sort!"<<std::endl;
    getch();
    system("cls");
}





std::function<bool(Cat, Cat)> Menu::createPairComparator(const std::pair<int, int> &keys) {
    auto C = this->comparators;
    auto EC = this->equalityComparators;
    return [EC, C, keys](Cat a, Cat b) -> bool{
        return (!EC[keys.first](a,b) & C[keys.first](a,b)
               ) || (EC[keys.first](a,b) & C[keys.second](a,b));
    };
}

void Menu::sortListByTwoFields() {
    if (catsList.size() > 1)
    try{
        auto keysPair = std::make_pair(Menu::chooseComparator("Select primary field for sort", "Sort")-1,
                                       Menu::chooseComparator("Select secondary field for sort", "Sort")-1);
        auto comparator = Menu::createPairComparator(keysPair);
        std::sort(catsList.begin(), catsList.end(), comparator);
        std::cout<<"Successfully sorted!"<<std::endl;
    }
    catch (std::runtime_error &ex){
        system("cls");
        std::cout << "You have cancelled sorting!" << std::endl;
    }
    else std::cout<<"Nothing to sort!"<<std::endl;
    getch();
    system("cls");

}

void Menu::deleteCatByNum() {
        std::vector<std::string> cats;
        cats.push_back("Select cat: ");
        for (int i = 0; i < this->catsList.size(); i++)
            cats.push_back("Cat[" + std::to_string(i + 1) + "]" + this->catsList[i].toString());
        try {
            int toDelete = getPositionFromParagraphs(cats);
            this->catsList.erase(this->catsList.begin() + toDelete - 1);
            std::cout << "Successfully deleted!" << std::endl;
        } catch (std::runtime_error &ex) {
            system("cls");
            std::cout << "You have cancelled deleting!" << std::endl;
        }
}

void Menu::deleteCatByField() {
    try{
        int type = Menu::chooseComparator("Select field for search", "Find")-1;
        Cat elepticalCatInVacuum;
        switch(type){
            case 0: elepticalCatInVacuum.setWeight(Menu::getInt("Enter weight of a cat(KG's):", 0,30)); break;
            case 1: elepticalCatInVacuum.setAge(Menu::getInt("Enter age of a cat(years):", 0,30));    break;
            case 2: elepticalCatInVacuum.setName(Menu::readString("Enter name of a cat:"));   break;
            case 3:
                std::vector<std::string> sexChoosing = {"Enter sex of a cat:", "Male", "Female"};
                elepticalCatInVacuum.setMale(Menu::getPositionFromParagraphs(sexChoosing) == 1);
                break;
        }

        auto comparator = std::bind(equalityComparators[type],std::placeholders::_1,elepticalCatInVacuum);
        int count = std::count_if(catsList.begin(), catsList.end(), comparator);
        switch(count){
            case 0: std::cout<<"No matches!"<<std::endl;
                break;
            case 1: catsList.erase(std::find_if(catsList.begin(), catsList.end(), comparator));
                std::cout << "Successfully deleted!" << std::endl;
                break;
            default: std::cout<<"Too much matches!"<<std::endl;
        }
    }
    catch (std::runtime_error &ex){
        system("cls");
        std::cout << "You have cancelled deleting!" << std::endl;
    }
}

