//
// Created by ptaxom on 15.10.2018.
//

#ifndef INC_1_CAT_H
#define INC_1_CAT_H

#include <string>
#include <iostream>


class Cat {
    bool male;
    std::string name;
    int age;
    int weight;

public:

    Cat(bool male, const std::string &name, int age, int weight);

    std::string toString();

    bool isMale() const;

    const std::string &getName() const;

    int getAge() const;

    int getWeight() const;

    void setMale(bool male);

    void setName(const std::string &name);

    void setAge(int age);

    void setWeight(int weight);

    friend std::ostream &operator<<(std::ostream &os, const Cat &cat);

    Cat();
};


#endif //INC_1_CAT_H
