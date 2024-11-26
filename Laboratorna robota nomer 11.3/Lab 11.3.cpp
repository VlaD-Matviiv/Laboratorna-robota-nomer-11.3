// Lab 11.3

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <Windows.h>

struct Student 
{
    std::string surname;
    int grade1, grade2, grade3;
};

// Функція для зчитування списку студентів із файлу
std::vector<Student> readStudentsFromFile(const std::string& filename) 
{
    std::vector<Student> students;
    std::ifstream file(filename);
    if (!file) 
    {
        std::cerr << "Помилка: не вдалося відкрити файл " << filename << std::endl;
        return students;
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        std::istringstream iss(line);
        Student student;
        if (iss >> student.surname >> student.grade1 >> student.grade2 >> student.grade3) 
        {
            students.push_back(student);
        }
    }

    file.close();
    return students;
}

// Функція для запису списку студентів у файл
void writeStudentsToFile(const std::string& filename, const std::vector<Student>& students) 
{
    std::ofstream file(filename, std::ios::trunc);
    if (!file) 
    {
        std::cerr << "Помилка: не вдалося відкрити файл " << filename << std::endl;
        return;
    }

    for (const auto& student : students) 
    {
        file << student.surname << " " << student.grade1 << " " << student.grade2 << " " << student.grade3 << std::endl;
    }

    file.close();
}

// Функція для перегляду списку студентів
void viewStudents(const std::vector<Student>& students) 
{
    if (students.empty()) 
    {
        std::cout << "Список студентів порожній." << std::endl;
        return;
    }

    std::cout << "Список студентів:" << std::endl;
    for (const auto& student : students) 
    {
        std::cout << student.surname << ": " << student.grade1 << ", " << student.grade2 << ", " << student.grade3 << std::endl;
    }
}

// Функція для додавання нового студента
void addStudent(std::vector<Student>& students) 
{
    Student student;
    std::cout << "Введіть прізвище студента: ";
    std::cin >> student.surname;
    std::cout << "Введіть три екзаменаційні оцінки: ";
    std::cin >> student.grade1 >> student.grade2 >> student.grade3;

    students.push_back(student);
    std::cout << "Студента додано!" << std::endl;
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const std::string filename = "students.txt";
    std::vector<Student> students = readStudentsFromFile(filename);

    int choice;
    do 
    {
        std::cout << "\nМеню:\n";
        std::cout << "1. Переглянути список студентів\n";
        std::cout << "2. Додати нового студента\n";
        std::cout << "3. Вийти\n";
        std::cout << "Ваш вибір: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
            viewStudents(students);
            break;
        case 2:
            addStudent(students);
            writeStudentsToFile(filename, students);
            break;
        case 3:
            std::cout << "Вихід із програми." << std::endl;
            break;
        default:
            std::cout << "Неправильний вибір. Спробуйте ще раз." << std::endl;
        }
    } while (choice != 3);

    return 0;
}
