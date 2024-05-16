#include <iostream>
#include <filesystem>
#include "IniFile.h"

int main() {
    std::filesystem::path project_path = std::filesystem::current_path().parent_path();
    char exit = 0;
    std::cout << "Project path is " << project_path << '\n';
    do {
        IniFile ini;
        std::string filename;
        std::cout << "Enter INI file name: ";
        std::cin >> filename;
        char editSameFile = 0;
        do {

        int select = 0;
        char choice = 0;

        std::cout << "(1) Read INI file\n(2) Create/Rebuild INI file\nEnter choice: ";
        std::cin >> select;

        std::string section, key, value;


        switch (select) {
            case 1: {
                try {
                    ini.Load((project_path / filename).string());
                } catch (const std::exception &e) {
                    std::cerr << "Error: " << e.what() << '\n';
                }
            }
                break;
            case 2: {
                do {
                    std::cout << "Enter section name: ";
                    std::cin >> section;
                    std::cout << "Enter key name: ";
                    std::cin >> key;
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    ini.SetString(section, key, value);
                    ini.Save((project_path / filename).string());
                    std::cout << "Do you want to add more values? (y/any key): ";
                    std::cin >> choice;
                } while (choice == 'y' || choice == 'Y');
            }
                break;
            case 3: {
                std::string section_name, key_name;
                std::cout << "Enter section name: ";
                std::cin >> section_name;
                std::cout << "Enter key name: ";
                std::cin >> key_name;
                std::cout << "Value is: " << ini.GetString(section_name, key_name) << '\n';
            }
                break;
            default:
                std::cerr << "Invalid choice\n";
        }
        std::cout << "Do you want to edit the same file? (y/any key): ";
        std::cin >> editSameFile;
    }while(editSameFile == 'y' || editSameFile == 'Y');
        std::cout << "Do you want to continue edit with this program? (E/any key): ";
        std::cin >> exit;
    } while (exit == 'e' || exit == 'E');
    return 0;
}


//meglio lo switch case