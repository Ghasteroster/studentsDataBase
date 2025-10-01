#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "gtest/gtest.h"

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

void createReport(const std::vector<Student>& database) {
	std::ofstream report;
	std::string reportFolder = "report/";
	system("mkdir report");
	report.open(reportFolder + "report.typ");
	report << "#set page(paper: \"a4\", margin: 2cm)\n"
	<< "#set text(font: (\"Times New Roman\", \"Libertinus Serif\"), size: 12pt)\n"
	<< "#set par(leading: 1.5em, justify: true)\n\n"
	<< "#align(center)[\n"
		<< "\t#text(weight: \"bold\", size: 16pt)[ОТЧЁТ]\n"
		<< "\t#linebreak()\n"
		<< "\t#text(style: \"italic\", size: 10pt)[Дата: #datetime.today().display(\"[day].[month].[year]\")]\n"
	<< "]\n";

    for (const Student& student : database) {
		report << "#block(fill: rgb(\"#f0f0f0\"), inset: 8pt, radius: 4pt, stroke: (left: 2pt + blue))[\n"
			<< "\t#text(weight: \"bold\")[Студент:] " << student.name << "\\\n"
			<< "\t#text(weight: \"bold\")[Возраст:] " << student.age << "\\\n"
			<< "\t#text(weight: \"bold\")[Специальность:] " << student.major << "\\\n"
		<< "]\n";
	}

	report.close();
}

// Тестовые функции
double calculateAverageGPA(const std::vector<Student>& database) {
    if (database.empty()) return 0.0;

    double total = 0.0;
    for (const Student& student : database) {
        total += student.gpa;
    }
    return total / database.size();
}

bool isValidGPA(double gpa) {
    return gpa >= 0.0 && gpa <= 5.0;
}

bool isValidAge(int age) {
    return age >= 16 && age <= 100;
}

// Тесты GoogleTest
TEST(StudentTest, CalculateAverageGPA) {
    std::vector<Student> testDatabase;

    Student s1{"Иван", 20, "Информатика", 4.5};
    Student s2{"Мария", 21, "Математика", 3.8};
    Student s3{"Петр", 22, "Физика", 4.2};

    testDatabase.push_back(s1);
    testDatabase.push_back(s2);
    testDatabase.push_back(s3);

    EXPECT_NEAR(calculateAverageGPA(testDatabase), (4.5 + 3.8 + 4.2) / 3, 0.001);
}

TEST(StudentTest, CalculateAverageGPAEmpty) {
    std::vector<Student> emptyDatabase;
    EXPECT_DOUBLE_EQ(calculateAverageGPA(emptyDatabase), 0.0);
}

TEST(StudentTest, ValidateGPA) {
    EXPECT_TRUE(isValidGPA(3.5));
    EXPECT_TRUE(isValidGPA(0.0));
    EXPECT_TRUE(isValidGPA(5.0));
    EXPECT_FALSE(isValidGPA(-1.0));
    EXPECT_FALSE(isValidGPA(5.1));
}

TEST(StudentTest, ValidateAge) {
    EXPECT_TRUE(isValidAge(18));
    EXPECT_TRUE(isValidAge(25));
    EXPECT_FALSE(isValidAge(15));
    EXPECT_FALSE(isValidAge(101));
}

TEST(ReportTest, CreateReportFileExists) {
    std::vector<Student> testDatabase;

    Student s1{"Анна", 20, "Информатика", 4.5};
    Student s2{"Дмитрий", 21, "Математика", 3.8};

    testDatabase.push_back(s1);
    testDatabase.push_back(s2);

    createReport(testDatabase);

    std::ifstream file("report/report.typ");
    EXPECT_TRUE(file.good());

    if (file.good()) {
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        EXPECT_FALSE(content.empty());

        EXPECT_TRUE(content.find("Анна") != std::string::npos);
        EXPECT_TRUE(content.find("Дмитрий") != std::string::npos);
        EXPECT_TRUE(content.find("Информатика") != std::string::npos);
        EXPECT_TRUE(content.find("Математика") != std::string::npos);
    }

    file.close();
}

int runTests(int argc, char **argv) {
    std::cout << "Запуск тестов...\n";
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

void runMainWork() { 
    std::vector<Student> database;
    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
		std::cout << "3. Создать отчёт\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;

            case 2:
                displayStudents(database);
                break;

            case 3:
                createReport(database);
                break;

            case 0:
                std::cout << "Выход из программы.\n";
                break;

            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        runMainWork();
        return 0;
    }

}
