//
// Created by ptaxom on 15.10.2018.
//

#include "Cat.h"

std::string Cat::toString() {
    int maxLen = 10;
    return "(name = "+(this->name.length() > maxLen ? this->name.substr(0,maxLen-3)+"..." : this->name)
           +"; sex = "+(this->male ? "male" : "female") +";weight = "+std::to_string(this->weight)
           +";age = "+std::to_string(this->age)+")";
}

bool Cat::isMale() const {
    return male;
}

const std::string &Cat::getName() const {
    return name;
}

int Cat::getAge() const {
    return age;
}

int Cat::getWeight() const {
    return weight;
}


void Cat::setMale(bool male) {
    Cat::male = male;
}

void Cat::setName(const std::string &name) {
    Cat::name = name;
}

void Cat::setAge(int age) {
    Cat::age = age;
}

void Cat::setWeight(int weight) {
    Cat::weight = weight;
}

std::ostream &operator<<(std::ostream &s, const Cat &cat) {
    auto format = s.flags();
    s << "Cat's name: "   <<  cat.getName()                        <<std::endl;
    s << "Cat's sex: "    << (cat.isMale() ? "Male" : "Female")    <<std::endl;
    s << "Cat's age: "    <<  cat.getAge()         <<" years"      <<std::endl;
    s << "Cat's weight: " <<  cat.getWeight()      <<" kilograms";
    s.setf(format);
    return s;
}

Cat::Cat(bool male, const std::string &name, int age, int weight) : male(male), name(name), age(age), weight(weight) {}

Cat::Cat() {
    this->male = false;
    this->name = "";
    this->age = 0;
    this->weight = 0;
}
