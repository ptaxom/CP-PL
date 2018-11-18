#pragma once

#include "DataStructs.h"

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>


class DataBase
{

	std::vector<Result> results;
	std::vector<Lesson> lessons;
	std::vector<Student> students;

	std::map<int, std::string> disciplines;
	std::map<std::string, std::set<std::string>> defaultMisses;
	std::map<int, std::set<int>> groupList;

	std::map<int, std::map<std::string, std::pair<std::set<std::string>, std::pair<int, int>>>> dataBase;

	void fillDataBase();

	std::ifstream loadFile(std::string path);

	template<class T> std::vector<T> loadVector(std::string path);

	void printStudents();

	void printDisciplines();

	void printGroups();

	double missesPercent(int studentID,const std::string &discipline);

	double getAvg(int studentID, const std::string &discipline);

	void misses(int studentsID);

	double groupMisses(int groupID, const std::string &discipline);

	bool isCorrectGroup(int groupID);

	bool isCorrectDiscipline(const std::string &discipline);

	bool isCorrectStudent(int studentID);


public:
	DataBase();
	DataBase(int argc, char **argv);

	
	void handle();

	~DataBase();
};




template<class T>
T read(std::ifstream &file);

template <>
std::string read<std::string>(std::ifstream &file);


template<>
Lesson read<Lesson>(std::ifstream &file);

template<>
Student read<Student>(std::ifstream &file);

template<>
Result read<Result>(std::ifstream &file);