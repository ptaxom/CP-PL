#pragma once

#include <string>
#include <iomanip>


struct Student {
	int id;
	std::string name;
	int group;

	friend std::ostream& operator<<(std::ostream& s, Student st) {
		auto format = s.flags();
		s << std::left << std::setw(5) << st.id << " " << st.name << std::setw(5) << " " << st.group;
		s.setf(format);
		return s;
	}

};



struct Lesson {
	int id;
	std::string date;
	std::string discipline;

	friend std::ostream& operator<<(std::ostream& s, Lesson l) {
		auto format = s.flags();
		s << l.id << " " << l.date << " " << l.discipline;
		s.setf(format);
		return s;
	}

};

struct Result {
	int studentID;
	int lessonID;
	int grade;


	friend std::ostream& operator<<(std::ostream& s, Result r) {
		auto format = s.flags();
		s << r.studentID << " " << r.lessonID << " " << r.grade;
		s.setf(format);
		return s;
	}
};


