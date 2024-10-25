#pragma once
#include <iostream>
#include <vector>
#include <fstream>   // �����ļ�����
#include <sstream>   // �����ַ���������
#include <string>
#include <algorithm> // ���� std::find_if
#include <cstdlib>   // ���ڵ��� system ������ͼƬ

const int CONSOLE_WIDTH = 80;

std::string centerText(const std::string& text) {
    int padding = (CONSOLE_WIDTH - text.length()) / 2;
    if (padding > 0) {
        return std::string(padding, ' ') + text;
    }
    return text;
}

// չƷ��
class Exhibit {
private:
    std::string name;       // չƷ����
    std::string category;   // չƷ���
    std::string description;// չƷ����
    std::string imagePath;  // չƷͼƬ·��
    int id;                 // չƷ���

public:
    // ���캯��
    Exhibit(int id, const std::string& name, const std::string& category, const std::string& description, const std::string& imagePath)
        : id(id), name(name), category(category), description(description), imagePath(imagePath) {}

    // չʾչƷ��Ϣ
    void display() const {
        std::cout << centerText("Exhibit ID: " + std::to_string(id)) << "\n"
            << centerText("Name: " + name) << "\n"
            << centerText("Category: " + category) << "\n"
            << centerText("Description: " + description) << "\n";

        if (!imagePath.empty()) {
            std::cout << centerText("Image Path: " + imagePath) << "\n";
            // ����ϵͳ�����ͼƬ
            std::cout << centerText("Displaying the exhibit image...") << "\n";
            openImage();
        }
        else {
            std::cout << centerText("No image available for this exhibit.") << "\n";
        }
    }

    // ��ȡչƷID
    int getId() const {
        return id;
    }

    // ��ȡչƷ����
    std::string getName() const {
        return name;
    }

    // ��ȡչƷ���
    std::string getCategory() const {
        return category;
    }
    std::string getDescription() const {
        return description;
    }
    // ��ȡչƷͼƬ·��
    std::string getImagePath() const {
        return imagePath;
    }

    // ��ͼƬ
    void openImage() const {
#ifdef _WIN32
        std::string command = "start " + imagePath;
#elif __APPLE__
        std::string command = "open " + imagePath;
#elif __linux__
        std::string command = "xdg-open " + imagePath;
#else
        std::cerr << centerText("Image display not supported on this OS.") << "\n";
        return;
#endif
        std::system(command.c_str());
        std::system("pause");
    }
};

class Museum {
private:
    std::vector<Exhibit> exhibits; // չƷ�б�
public:
    std::vector<int> ID_pramery;
    // ���չƷ
    void addExhibit(const Exhibit& exhibit) {
        exhibits.push_back(exhibit);
        ID_pramery.push_back(exhibit.getId());
    }

    // ɾ��չƷ
    void removeExhibit(int id) {
        auto it = std::find_if(exhibits.begin(), exhibits.end(),
            [id](const Exhibit& e) { return e.getId() == id; });
        if (it != exhibits.end()) {
            exhibits.erase(it);
            ID_pramery.erase(std::find(ID_pramery.begin(), ID_pramery.end(), id));
            std::cout << centerText("Exhibit with ID " + std::to_string(id) + " removed.") << "\n";
        }
        else {
            std::cout << centerText("Exhibit with ID " + std::to_string(id) + " not found.") << "\n";
        }
        
    }

    // ����ID��ѯչƷ
    Exhibit* findExhibitById(int id) {
        for (auto& exhibit : exhibits) {
            if (exhibit.getId() == id) {
                return &exhibit;
            }
        }
        std::cout << centerText("Exhibit with ID " + std::to_string(id) + " not found.") << "\n";
        return nullptr;
    }

    // �������Ʋ�ѯչƷ
    Exhibit* findExhibitByName(const std::string& name) {
        for (auto& exhibit : exhibits) {
            if (exhibit.getName() == name) {
                return &exhibit;
            }
        }
        std::cout << centerText("Exhibit with name " + name + " not found.") << "\n";
        return nullptr;
    }

    // ��ʾ����չƷ��Ϣ
    void displayAll() const {
        if (exhibits.empty()) {
            std::cout << centerText("No exhibits found.") << "\n";
            return;
        }
        for (const auto& exhibit : exhibits) {
            exhibit.display();
            std::cout << centerText("-----------------------------") << "\n";
        }
    }

    // ����չƷ��Ϣ���ļ�
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename); // ���ļ�

        if (!file) {
            std::cerr << centerText("Error opening file for writing.") << "\n";
            return;
        }

        // ��������չƷ������չƷ��Ϣ���浽�ļ�
        for (const auto& exhibit : exhibits) {
            file << exhibit.getId() << "|"
                << exhibit.getName() << "|"
                << exhibit.getCategory() << "|"
                << exhibit.getDescription() << "|"
                << exhibit.getImagePath() << "\n";
        }

        file.close(); // �ر��ļ�
        std::cout << centerText("Exhibits saved to file successfully!") << "\n";
    }

    // ���ļ�����չƷ��Ϣ
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename); // ���ļ�

        if (!file) {
            std::cerr << centerText("Error opening file for reading.") << "\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, name, category, description, imagePath;

            // ��ȡÿ��չƷ������ֵ
            std::getline(ss, idStr, '|');
            std::getline(ss, name, '|');
            std::getline(ss, category, '|');
            std::getline(ss, description, '|');
            std::getline(ss, imagePath);

            int id = std::stoi(idStr); // ��ID�ַ���ת��Ϊ����

            // ����չƷ������ӵ�չƷ�б�
            Exhibit exhibit(id, name, category, description, imagePath);
            exhibits.push_back(exhibit);

        }
        for (auto& exhibit : exhibits)
        {
            ID_pramery.push_back(exhibit.getId());
        }
        file.close(); // �ر��ļ�
        std::cout << centerText("Exhibits loaded from file successfully!") << "\n";
    }
};