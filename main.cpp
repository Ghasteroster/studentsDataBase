#include <iostream>
#include <vector>
#include <string>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

// Функция для добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin >> student.name;
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin >> student.major;
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const std::vector<Student>& database) {
    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

// Функция для вывода студентов из базы данных по специальности
void displayStudentsByMajor(const std::vector<Student>& database, const std::string& major) {
    bool found = false;
    std::cout << "Список студентов по специальности:\n";
    for (const Student& student : database) {
        if (student.major == major) {
            std::cout << "Имя: " << student.name << "\n";
            std::cout << "Возраст: " << student.age << "\n";
            std::cout << "Специальность: " << student.major << "\n";
            std::cout << "Средний балл: " << student.gpa << "\n\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Студенты со специальностью \"" << major << "\" не найдены.\n";
    }
}

int main() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                int choice1;
                std::cout << "1. Вывести список студентов по специальности\n";
                std::cout << "2. Вывести список всех студентов\n";
                std::cin >> choice1;
               
                switch (choice1) {
                    case 1: { 
                        std::string major;
                        std::cout << "Введите название специальности: ";
                        std::cin >> major;
                        displayStudentsByMajor(database, major);
                    }
                    case 2:
                        displayStudents(database);
                    default:
                        std::cout << "Неверный выбор.\n";
                }
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
