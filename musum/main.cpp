#include "class.h"

//添加展品

void addExhibitToMuseum(Museum& museum) {
    int id;
    std::string name, category, description, imagePath;
    std::cout << centerText("请输入展品ID: ");
    std::cin >> id;
    std::cin.ignore(); // 忽略换行符
    if(!museum.ID_acceptable(id))//ID的主键约束，避免ID重复
    {
        std::cout << centerText("ID已存在\n");
        std::cin.ignore();
        return;
    }
    std::cout << centerText("请输入展品名称: ");
    std::getline(std::cin, name);
    std::cout << centerText("请输入展品分类: ");
    std::getline(std::cin, category);
    std::cout << centerText("请输入展品描述: ");
    std::getline(std::cin, description);
    std::cout << centerText("请输入展品图片路径: ");
    std::getline(std::cin, imagePath);

    Exhibit exhibit(id, name, category, description, imagePath);
    museum.addExhibit(exhibit);
    std::cout << centerText("展品添加成功!") << "\n";
    museum.saveToFile("exhibits.txt");
    std::cin.ignore();
}

// 查询展品
void searchExhibitInMuseum(Museum& museum) {
    int option;
    std::cout << centerText("查询方式:") << "\n"
        << centerText("1. ID") << "\n"
        << centerText("2. Name") << "\n"
        << centerText("请选择: ");
    std::cin >> option;

    if (option == 1) {
        int id;
        std::cout << centerText("请输入展品ID: ");
        std::cin >> id;
        Exhibit* exhibit = museum.findExhibitById(id);
        if (exhibit) {
            exhibit->display();
        }
    }
    else if (option == 2) {
        std::string name;
        std::cout << centerText("请输入展品名称: ");
        std::cin.ignore();
        std::getline(std::cin, name);
        Exhibit* exhibit = museum.findExhibitByName(name);
        if (exhibit) {
            exhibit->display();
        }
    }
    else {
        std::cout << centerText("无效输入!") << "\n";
    }
    std::cin.ignore();
    std::cin.ignore();
}

// 删除展品
void deleteExhibitFromMuseum(Museum& museum) {
    int id;
    std::cout << centerText("请输入所要删除的展品的ID: ");
    std::cin >> id;
    museum.removeExhibit(id);
    std::cin.ignore();
    std::cin.ignore();
}

// 主程序
int main() {
    Museum museum;

    // 启动时从文件加载展品信息
    museum.loadFromFile("exhibits.txt");

    int choice;

    do {
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";
        std::cout << centerText("Digital-Museum Management System") << "\n";
        std::cout << centerText("1. 添加展品") << "\n"
            << centerText("2. 查找展品") << "\n"
            << centerText("3. 删除展品") << "\n"
            << centerText("4. 展示所有展品") << "\n"
            << centerText("5. 退出程序") << "\n"
            << centerText("输入所要进行的操作前的数字: ");
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            flush();
            addExhibitToMuseum(museum);
            break;
        case 2:
            flush();
            searchExhibitInMuseum(museum);
            break;
        case 3:
            flush();
            deleteExhibitFromMuseum(museum);
            break;
        case 4:
            flush();
            museum.displayAll();
            break;
        case 5:
            museum.saveToFile("exhibits.txt");
            std::cout << centerText("Goodbye!") << "\n";
            break;
        default:
            flush();
            std::cout << centerText("无效输入!") << "\n";
        }
        flush();
    } while (choice != 5);

    return 0;
}
