#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <sstream>

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
            std::cout << "Средний балл: " << student.gpa << "\n\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Студенты со специальностью \"" << major << "\" не найдены.\n";
    }
}

// TESTS

// Тест для пустой базы данных
TEST(DisplayStudentsByMajorTest, HandlesEmptyDatabase) {
    std::vector<Student> empty_database;
    std::streambuf* old_cout = std::cout.rdbuf(output_buffer.rdbuf());
    
    displayStudentsByMajor(empty_database, "Информатика");
    
    std::cout.rdbuf(old_cout);
    
    std::string output = buffer.str();
    
    EXPECT_NE(output.find("не найдены"), std::string::npos);
}

// Проверяем, что выводятся студенты с заданной специальностью
TEST(DisplayStudentsByMajorTest, FoundStudents) {
    std::vector<Student> db = {
        {"Иван", 20, "Математика", 4.5},
        {"Анна", 22, "Физика", 4.2},
        {"Петр", 21, "Математика", 3.9}
    };

    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    displayStudentsByMajor(db, "Математика");

    std::cout.rdbuf(old_cout);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Иван"), std::string::npos);
    EXPECT_NE(output.find("Петр"), std::string::npos);
    EXPECT_EQ(output.find("Анна"), std::string::npos);
}


void runInteractiveMode() {
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
                        break;
                    }
                    case 2:
                        displayStudents(database);
                        break;
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

int main(int argc, char **argv) {
    // Если есть аргументы командной строки, запускает тесты
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        // Иначе запускает интерактивное меню
        runInteractiveMode();
        return 0;
    }
}
