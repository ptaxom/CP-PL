#include <iostream>

int main() {
    while (true)
    try{
        std::string input_string;
        getline(std::cin, input_string);
        if (input_string == "stop")
            break;
        double value = std::stod(input_string);
        std::cout << "Value is " << std::scientific << value << std::endl;
    }
    catch (std::exception &ex){
        std::cout << "Invalid argument" << std::endl;
    }
}