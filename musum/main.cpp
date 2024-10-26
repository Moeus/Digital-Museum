#include "class.h"

//���չƷ

void addExhibitToMuseum(Museum& museum) {
    int id;
    std::string name, category, description, imagePath;
    std::cout << centerText("Enter exhibit ID: ");
    std::cin >> id;
    std::cin.ignore(); // ���Ի��з�
    if(!museum.ID_acceptable(id))//ID������Լ��������ID�ظ�
    {
        std::cout << centerText("ID�Ѵ���\n");
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

// ��ѯչƷ
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

// ɾ��չƷ
void deleteExhibitFromMuseum(Museum& museum) {
    int id;
    std::cout << centerText("Enter exhibit ID to remove: ");
    std::cin >> id;
    museum.removeExhibit(id);
    std::cin.ignore();
    std::cin.ignore();
}

// ������
int main() {
    Museum museum;

    // ����ʱ���ļ�����չƷ��Ϣ
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
