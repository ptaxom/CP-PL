#include "DataBase.h"



DataBase::DataBase()
{
}

DataBase::DataBase(int argc, char **argv) {
	if (argc == 4) {
		this->students = loadVector<Student>(argv[1]);
		this->lessons = loadVector<Lesson>(argv[2]);
		this->results = loadVector<Result>(argv[3]);
		this->fillDataBase();
	}
	else throw std::runtime_error("Bad command line args!");
}

DataBase::~DataBase()
{
}


std::ifstream DataBase::loadFile(std::string path) {
	std::ifstream inFile(path, std::ios::binary);
	if (!inFile)
		throw std::runtime_error("Can't open file " + path);
	return inFile;
}


template<class T>
std::vector<T> DataBase::loadVector(std::string path) {
	std::vector<T> data;
	std::ifstream input = loadFile(path);
	while (input.peek() != EOF) {
		data.push_back(read<T>(input));
	}
	input.close();
	return data;
}

void DataBase::fillDataBase() {
	std::set<int> studentIds;
	std::set<int> lessonsIds;

	std::map<int, std::string> lessonDate;

	for (Student &s : students) {
		studentIds.insert(s.id);
		groupList[s.group].insert(s.id);
	}
	for (Lesson &l : lessons) {
		lessonsIds.insert(l.id);
		defaultMisses[l.discipline].insert(l.date+"_" + std::to_string(l.id));
		disciplines[l.id] = l.discipline;
		lessonDate[l.id] = l.date+"_"+std::to_string(l.id);
	}

	for (int studentId : studentIds)                          //Предполагаем, что все студенты не ходили ни на какие пары
		for (std::pair<std::string, std::set<std::string>> p : defaultMisses) {
			std::set<std::string> bufSet(p.second);
			dataBase[studentId][p.first].first = bufSet;
		}
	for (Result r : results) {
		std::string discipline = disciplines[r.lessonID];
		dataBase[r.studentID][discipline].first.erase(lessonDate[r.lessonID]); //Убираем дату дисциплины из непосещенных, если пришел
		if (r.grade != 0) {                                                      //Если получаем отметку, добавляем её
			dataBase[r.studentID][discipline].second.first += r.grade;
			dataBase[r.studentID][discipline].second.second++;
		}
	}
}



bool DataBase::isCorrectGroup(int groupID) {
	return groupList.count(groupID) != 0;
}

bool DataBase::isCorrectDiscipline(const std::string &discipline) {
	return defaultMisses.count(discipline) != 0;
}

bool DataBase::isCorrectStudent(int studentID) {
	return (dataBase.count(studentID) != 0);
}


double avg(double sum, int times) {
	if (times == 0)
		throw std::runtime_error("Division by zero!");
	else return sum / (double)times;
}

double DataBase::missesPercent(int studentID, const std::string &discipline) {
	return 1.0 - (double)dataBase[studentID][discipline].first.size() / (double)defaultMisses[discipline].size();
}

double DataBase::getAvg(int studentID, const std::string &discipline) {
	if (!isCorrectStudent(studentID))
		throw std::runtime_error("No such student!");
	if (!isCorrectDiscipline(discipline))
		throw std::runtime_error("No such discipline!");
	double marks = dataBase[studentID][discipline].second.first;
	int times = dataBase[studentID][discipline].second.second;
	return avg(marks, times);
}

void DataBase::misses(int studentID) {
	if (!isCorrectStudent(studentID))
		throw std::runtime_error("No such student!");
	for (auto &p : dataBase[studentID])
		for (std::string date : p.second.first)
			std::cout << date.substr(0,date.find("_")) << " " << p.first << std::endl;
}

double DataBase::groupMisses(int groupID, const std::string &discipline) {
	if (!isCorrectGroup(groupID))
		throw std::runtime_error("No such group!");
	if (!isCorrectDiscipline(discipline))
		throw std::runtime_error("No such discipline!");
	double misses = 0;
	int times = 0;
	for (int studentID : groupList[groupID]) {
		misses += missesPercent(studentID, discipline);
		times++;
	}
	return avg(misses, times);
}




void DataBase::printStudents() {
	for (const auto &s : this->students)
		std::cout << s << std::endl;
}


void DataBase::printDisciplines() {
	for (const auto &pair : this->defaultMisses)
		std::cout << pair.first << std::endl;
}


void DataBase::printGroups() {
	for (const auto &pair : this->groupList)
		std::cout << pair.first << std::endl;
}


#include <sstream>

std::vector<std::string> splitInput() {
	std::string s;
	getline(std::cin, s);
	std::vector<std::string> args;
	std::istringstream arg(s);
	while (!arg.eof()) {
		std::string word;
		arg >> word;
		args.push_back(word);
	}
	return args;
}


void DataBase::handle() {
	while (true) {
		auto args = splitInput();
		if (args[0] == "show") {
			if (args[1] == "g") printGroups();
			if (args[1] == "s") printStudents();
			if (args[1] == "d") printDisciplines();
		}
		if (args[0] == "exit") break;
		try {
			if (args[0] == "%")
				if (args.size() == 3)
					std::cout << (groupMisses(stoi(args[1]), args[2]) * 100) << std::endl;
				else throw std::runtime_error("Invalid arguments amount");
			if (args[0] == "avg")
				if (args.size() == 3)
					std::cout << getAvg(stoi(args[1]), args[2]) << std::endl;
				else throw std::runtime_error("Invalid arguments amount");
			if (args[0] == "miss")
				if (args.size() == 2)
					misses(stoi(args[1]));
				else throw std::runtime_error("Invalid arguments amount");
		}
		catch (std::runtime_error &ex) {
			std::cout << ex.what() << std::endl;
		}
	}
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
Lesson read<Lesson>(std::ifstream &file) {
	Lesson lesson;
	try {
		lesson.id = read<int>(file);
		lesson.date = read<std::string>(file);
		lesson.discipline = read<std::string>(file);
	}
	catch (std::runtime_error &ex) {
		throw std::runtime_error("Read error when reading struct Lesson!");
	}
	return lesson;
}

template<> Student read<Student>(std::ifstream &file) {
	Student student;
	try {
		student.id = read<int>(file);
		student.name = read<std::string>(file);
		student.group = read<int>(file);
	}
	catch (std::runtime_error &ex) {
		throw std::runtime_error("Read error when reading struct Student!");
	}
	return student;
}

template<>
Result read<Result>(std::ifstream &file) {
	Result result;
	try {
		result.studentID = read<int>(file);
		result.lessonID = read<int>(file);
		result.grade = read<int>(file);
	}
	catch (std::runtime_error &ex) {
		throw std::runtime_error("Read error when reading struct Result!");
	}
	return result;
}
