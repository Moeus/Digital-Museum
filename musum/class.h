#pragma once
#include <iostream>
#include <vector>
#include <fstream>   // 用于文件操作
#include <sstream>   // 用于字符串流处理
#include <string>
#include <algorithm> // 用于 std::find_if
#include <cstdlib>   // 用于调用 system 函数打开图片

const int CONSOLE_WIDTH = 80;

std::string centerText(const std::string& text) {
    int padding = (CONSOLE_WIDTH - text.length()) / 2;
    if (padding > 0) {
        return std::string(padding, ' ') + text;
    }
    return text;
}

// 展品类
class Exhibit {
private:
    std::string name;       // 展品名称
    std::string category;   // 展品类别
    std::string description;// 展品描述
    std::string imagePath;  // 展品图片路径
    int id;                 // 展品编号

public:
    // 构造函数
    Exhibit(int id, const std::string& name, const std::string& category, const std::string& description, const std::string& imagePath)
        : id(id), name(name), category(category), description(description), imagePath(imagePath) {}

    // 展示展品信息
    void display() const {
        std::cout << centerText("Exhibit ID: " + std::to_string(id)) << "\n"
            << centerText("Name: " + name) << "\n"
            << centerText("Category: " + category) << "\n"
            << centerText("Description: " + description) << "\n";

        if (!imagePath.empty()) {
            std::cout << centerText("Image Path: " + imagePath) << "\n";
            // 调用系统命令打开图片
            std::cout << centerText("Displaying the exhibit image...") << "\n";
            openImage();
        }
        else {
            std::cout << centerText("No image available for this exhibit.") << "\n";
        }
    }

    // 获取展品ID
    int getId() const {
        return id;
    }

    // 获取展品名称
    std::string getName() const {
        return name;
    }

    // 获取展品类别
    std::string getCategory() const {
        return category;
    }
    std::string getDescription() const {
        return description;
    }
    // 获取展品图片路径
    std::string getImagePath() const {
        return imagePath;
    }

    // 打开图片
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
    std::vector<Exhibit> exhibits; // 展品列表
public:
    std::vector<int> ID_pramery;
    // 添加展品
    void addExhibit(const Exhibit& exhibit) {
        exhibits.push_back(exhibit);
        ID_pramery.push_back(exhibit.getId());
    }

    // 删除展品
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

    // 根据ID查询展品
    Exhibit* findExhibitById(int id) {
        for (auto& exhibit : exhibits) {
            if (exhibit.getId() == id) {
                return &exhibit;
            }
        }
        std::cout << centerText("Exhibit with ID " + std::to_string(id) + " not found.") << "\n";
        return nullptr;
    }

    // 根据名称查询展品
    Exhibit* findExhibitByName(const std::string& name) {
        for (auto& exhibit : exhibits) {
            if (exhibit.getName() == name) {
                return &exhibit;
            }
        }
        std::cout << centerText("Exhibit with name " + name + " not found.") << "\n";
        return nullptr;
    }

    // 显示所有展品信息
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

    // 保存展品信息到文件
    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename); // 打开文件

        if (!file) {
            std::cerr << centerText("Error opening file for writing.") << "\n";
            return;
        }

        // 遍历所有展品，并将展品信息保存到文件
        for (const auto& exhibit : exhibits) {
            file << exhibit.getId() << "|"
                << exhibit.getName() << "|"
                << exhibit.getCategory() << "|"
                << exhibit.getDescription() << "|"
                << exhibit.getImagePath() << "\n";
        }

        file.close(); // 关闭文件
        std::cout << centerText("Exhibits saved to file successfully!") << "\n";
    }

    // 从文件加载展品信息
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename); // 打开文件

        if (!file) {
            std::cerr << centerText("Error opening file for reading.") << "\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, name, category, description, imagePath;

            // 读取每个展品的属性值
            std::getline(ss, idStr, '|');
            std::getline(ss, name, '|');
            std::getline(ss, category, '|');
            std::getline(ss, description, '|');
            std::getline(ss, imagePath);

            int id = std::stoi(idStr); // 将ID字符串转换为整数

            // 创建展品对象并添加到展品列表
            Exhibit exhibit(id, name, category, description, imagePath);
            exhibits.push_back(exhibit);

        }
        for (auto& exhibit : exhibits)
        {
            ID_pramery.push_back(exhibit.getId());
        }
        file.close(); // 关闭文件
        std::cout << centerText("Exhibits loaded from file successfully!") << "\n";
    }
};