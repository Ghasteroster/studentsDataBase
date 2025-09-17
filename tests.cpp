#include <vector>
#include <string>
#include "gtest/gtest.h"

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

void addStudent(std::vector<Student>& database, const Student& student) {
    database.push_back(student);
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
    std::streambuf* old_сout = std::cout.rdbuf(buffer.rdbuf());

    displayStudentsByMajor(db, "Математика");

    std::cout.rdbuf(old_cout);

    std::string output = buffer.str();
    EXPECT_NE(output.find("Иван"), std::string::npos);
    EXPECT_NE(output.find("Петр"), std::string::npos);
    EXPECT_EQ(output.find("Анна"), std::string::npos);
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
