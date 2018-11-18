#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <cstring>
#include <algorithm>

std::ifstream openInputFile(std::string path){
    std::ifstream inputFile(path);
    if (!inputFile)
        throw std::runtime_error("Can't open file " +path);
    return inputFile;
}

std::ofstream openOutputFile(std::string path){
    std::ofstream outputFile(path, std::ios::binary);
    if (!outputFile)
        throw std::runtime_error("Can't create file " +path);
    return outputFile;
}


std::vector<std::string> commandReader(){
    std::string command;
    getline(std::cin,command);
    std::vector<std::string> args;
    std::istringstream arg(command);
    while (!arg.eof()){
        std::string word;
        arg>>word;
        args.push_back(word);
    }
    return args;
}


std::map<std::string, std::string> loadConfiguration(std::ifstream &inputFile){
    std::map<std::string, std::string> configuration;
    while (!inputFile.eof()){
        std::string bufferString;
        getline(inputFile, bufferString);
        if (!bufferString.empty() && bufferString!="\r") {
            int spacePosition = bufferString.find(' ');
            if (spacePosition != -1){
                configuration[bufferString.substr(0,spacePosition)] = bufferString.substr(spacePosition+1);
            }
            else configuration[bufferString] = "";
        }
    }
    return configuration;
}

bool isValidType(const std::string &type){
    const std::set<std::string> validTypes = {"int", "double", "bool", "string"};
    return (bool) (validTypes.count(type));
}

bool convertToBool(const std::string &key){
    if (key == "False" || key == "false")
        return false;
    if (key == "True"  || key == "true")
        return true;
    try{
        int val = std::stoi(key);
        return (bool)val;

    }
    catch (...){
        throw std::runtime_error("Bool cast exception");
    }
}

bool isCorrectString(const std::string &key){
    if (key.length() > 1 && key[0] == '"' && key[key.length()-1] == '"')
        return true;
}

template <typename T>
std::string castToString(T val){
    std::string str;
    str.resize(sizeof(T));
    memcpy(&str[0], &val, sizeof(T));
    return str;
}

void updateBuffer(std::stringstream &buffer,const std::string &type,const std::string &key,const std::map<std::string,std::string> &configuration){
    if (!isValidType(type))
        throw std::runtime_error("Invalid type "+type);
    if (!configuration.count(key))
        throw std::runtime_error("Invalid key "+key);
    try{
        if (type == "int")
            buffer << castToString<int>(std::stoi(configuration.at(key)));
        if (type == "double")
            buffer << castToString<double>(std::stod(configuration.at(key)));
        if (type == "string")
            if (isCorrectString(configuration.at(key)))
                buffer << castToString<int>(configuration.at(key).length()-2) << configuration.at(key).substr(1,configuration.at(key).length()-2);
            else throw std::runtime_error("");
        if (type == "bool")
            buffer << castToString<bool>(convertToBool(configuration.at(key)));
        }
    catch (...){
            throw std::runtime_error("Invalid "+type+" value "+configuration.at(key)+" for "+key);
    }
}

void menuHandler(std::ofstream &output,const std::map<std::string, std::string> &configuration){
    while(true){
        std::vector<std::string> args = commandReader();
        if (args[0] == "EXIT")
            break;
        else if (args[0] == "PACK"){
            try{
                if (args.size() % 2 == 1 && args.size() > 1) {
                    std::stringstream buffer("");
                    for (int i = 1; i < args.size(); i += 2)
                        updateBuffer(buffer, args[i], args[i + 1], configuration);
                    output << buffer.str();
                }
                else throw std::runtime_error("Invalid command syntax");
            }
            catch(std::runtime_error &ex){
                std::cout<<ex.what()<<std::endl;
            }
            catch (...){
                std::cout << "Unhandled exception!" << std::endl;
                break;
            }
        }
    }
    output.close();
}



int main(int argc, char **argv) {
    if (argc == 3){
        try{
            std::ifstream input = openInputFile(argv[1]);
            std::ofstream output = openOutputFile(argv[2]);
            std::map<std::string, std::string> configuration = loadConfiguration(input);
            input.close();
            menuHandler(output, configuration);

        }
        catch (std::runtime_error &ex){
            std::cout<<ex.what()<<std::endl;
        }
    }
    else std::cout<<"Invalid command arguments"<<std::endl;
    return 0;
}