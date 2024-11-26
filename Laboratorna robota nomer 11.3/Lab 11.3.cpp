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

// ������� ��� ���������� ������ �������� �� �����
std::vector<Student> readStudentsFromFile(const std::string& filename) 
{
    std::vector<Student> students;
    std::ifstream file(filename);
    if (!file) 
    {
        std::cerr << "�������: �� ������� ������� ���� " << filename << std::endl;
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

// ������� ��� ������ ������ �������� � ����
void writeStudentsToFile(const std::string& filename, const std::vector<Student>& students) 
{
    std::ofstream file(filename, std::ios::trunc);
    if (!file) 
    {
        std::cerr << "�������: �� ������� ������� ���� " << filename << std::endl;
        return;
    }

    for (const auto& student : students) 
    {
        file << student.surname << " " << student.grade1 << " " << student.grade2 << " " << student.grade3 << std::endl;
    }

    file.close();
}

// ������� ��� ��������� ������ ��������
void viewStudents(const std::vector<Student>& students) 
{
    if (students.empty()) 
    {
        std::cout << "������ �������� �������." << std::endl;
        return;
    }

    std::cout << "������ ��������:" << std::endl;
    for (const auto& student : students) 
    {
        std::cout << student.surname << ": " << student.grade1 << ", " << student.grade2 << ", " << student.grade3 << std::endl;
    }
}

// ������� ��� ��������� ������ ��������
void addStudent(std::vector<Student>& students) 
{
    Student student;
    std::cout << "������ ������� ��������: ";
    std::cin >> student.surname;
    std::cout << "������ ��� ������������ ������: ";
    std::cin >> student.grade1 >> student.grade2 >> student.grade3;

    students.push_back(student);
    std::cout << "�������� ������!" << std::endl;
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
        std::cout << "\n����:\n";
        std::cout << "1. ����������� ������ ��������\n";
        std::cout << "2. ������ ������ ��������\n";
        std::cout << "3. �����\n";
        std::cout << "��� ����: ";
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
            std::cout << "����� �� ��������." << std::endl;
            break;
        default:
            std::cout << "������������ ����. ��������� �� ���." << std::endl;
        }
    } while (choice != 3);

    return 0;
}
