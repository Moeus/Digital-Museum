#include "class.h"

//添加展品

void addExhibitToMuseum(Museum& museum) {
    int id;
    std::string name, category, description, imagePath;
    std::cout << centerText("Enter exhibit ID: ");
    std::cin >> id;
    std::cin.ignore(); // 忽略换行符
    if(!museum.ID_acceptable(id))//ID的主键约束，避免ID重复
    {
        std::cout << centerText("ID已存在\n");
        std::cin.ignore();
        return;
    }
    std::cout << centerText("Enter exhibit name: ");
    std::getline(std::cin, name);
    std::cout << centerText("Enter exhibit category: ");
    std::getline(std::cin, category);
    std::cout << centerText("Enter exhibit description: ");
    std::getline(std::cin, description);
    std::cout << centerText("Enter exhibit image path: ");
    std::getline(std::cin, imagePath);

    Exhibit exhibit(id, name, category, description, imagePath);
    museum.addExhibit(exhibit);
    std::cout << centerText("Exhibit added successfully!") << "\n";
    museum.saveToFile("exhibits.txt");
    std::cin.ignore();
}

// 查询展品
void searchExhibitInMuseum(Museum& museum) {
    int option;
    std::cout << centerText("Search by:") << "\n"
        << centerText("1. ID") << "\n"
        << centerText("2. Name") << "\n"
        << centerText("Choose an option: ");
    std::cin >> option;

    if (option == 1) {
        int id;
        std::cout << centerText("Enter exhibit ID: ");
        std::cin >> id;
        Exhibit* exhibit = museum.findExhibitById(id);
        if (exhibit) {
            exhibit->display();
        }
    }
    else if (option == 2) {
        std::string name;
        std::cout << centerText("Enter exhibit name: ");
        std::cin.ignore();
        std::getline(std::cin, name);
        Exhibit* exhibit = museum.findExhibitByName(name);
        if (exhibit) {
            exhibit->display();
        }
    }
    else {
        std::cout << centerText("Invalid option!") << "\n";
    }
    std::cin.ignore();
    std::cin.ignore();
}

// 删除展品
void deleteExhibitFromMuseum(Museum& museum) {
    int id;
    std::cout << centerText("Enter exhibit ID to remove: ");
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
        std::cout << centerText("1. Add Exhibit") << "\n"
            << centerText("2. Search Exhibit") << "\n"
            << centerText("3. Remove Exhibit") << "\n"
            << centerText("4. Display All Exhibits") << "\n"
            << centerText("5. Exit") << "\n"
            << centerText("Enter your choice: ");
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
            std::cout << centerText("Invalid choice!") << "\n";
        }
        flush();
    } while (choice != 5);

    return 0;
}
