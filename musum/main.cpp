#include "class.h"

//���չƷ

void addExhibitToMuseum(Museum& museum) {
    int id;
    std::string name, category, description, imagePath;
    std::cout << centerText("������չƷID: ");
    std::cin >> id;
    std::cin.ignore(); // ���Ի��з�
    if(!museum.ID_acceptable(id))//ID������Լ��������ID�ظ�
    {
        std::cout << centerText("ID�Ѵ���\n");
        std::cin.ignore();
        return;
    }
    std::cout << centerText("������չƷ����: ");
    std::getline(std::cin, name);
    std::cout << centerText("������չƷ����: ");
    std::getline(std::cin, category);
    std::cout << centerText("������չƷ����: ");
    std::getline(std::cin, description);
    std::cout << centerText("������չƷͼƬ·��: ");
    std::getline(std::cin, imagePath);

    Exhibit exhibit(id, name, category, description, imagePath);
    museum.addExhibit(exhibit);
    std::cout << centerText("չƷ��ӳɹ�!") << "\n";
    museum.saveToFile("exhibits.txt");
    std::cin.ignore();
}

// ��ѯչƷ
void searchExhibitInMuseum(Museum& museum) {
    int option;
    std::cout << centerText("��ѯ��ʽ:") << "\n"
        << centerText("1. ID") << "\n"
        << centerText("2. Name") << "\n"
        << centerText("��ѡ��: ");
    std::cin >> option;

    if (option == 1) {
        int id;
        std::cout << centerText("������չƷID: ");
        std::cin >> id;
        Exhibit* exhibit = museum.findExhibitById(id);
        if (exhibit) {
            exhibit->display();
        }
    }
    else if (option == 2) {
        std::string name;
        std::cout << centerText("������չƷ����: ");
        std::cin.ignore();
        std::getline(std::cin, name);
        Exhibit* exhibit = museum.findExhibitByName(name);
        if (exhibit) {
            exhibit->display();
        }
    }
    else {
        std::cout << centerText("��Ч����!") << "\n";
    }
    std::cin.ignore();
    std::cin.ignore();
}

// ɾ��չƷ
void deleteExhibitFromMuseum(Museum& museum) {
    int id;
    std::cout << centerText("��������Ҫɾ����չƷ��ID: ");
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
        std::cout << centerText("1. ���չƷ") << "\n"
            << centerText("2. ����չƷ") << "\n"
            << centerText("3. ɾ��չƷ") << "\n"
            << centerText("4. չʾ����չƷ") << "\n"
            << centerText("5. �˳�����") << "\n"
            << centerText("������Ҫ���еĲ���ǰ������: ");
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
            std::cout << centerText("��Ч����!") << "\n";
        }
        flush();
    } while (choice != 5);

    return 0;
}
