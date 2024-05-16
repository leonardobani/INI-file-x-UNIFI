#include <map>
#include <fstream>
#include <sstream>

class IniFile {
    std::map<std::string, std::map<std::string, std::string>> data;

public:
    IniFile() = default;
    void Load(const std::string &filename);

    void SetString(const std::string &section, const std::string &key, const std::string &value) {
        data[section][key] = value;
    }
    std::string GetString(const std::string &section, const std::string &key) {
        return data[section][key];
    }

    void Save(const std::string &filename) {
        std::ofstream file(filename); // Open file
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file for writing: " + filename);
        }
        for (const auto &section : data) {
            file << "[" << section.first << "]\n";
            for (const auto &keyValue : section.second) {
                file << keyValue.first << "=" << keyValue.second << "\n";
            }
        }
    }
};

void IniFile::Load(const std::string &filename) {
    std::ifstream file(filename); // Open file
    std::string line; // Current line
    std::string currentSection; // Current section
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for reading: " + filename);
    }
    while (std::getline(file, line)) {
        if (line[0] == '[') { // New section
            currentSection = line.substr(1, line.find(']') - 1);//remove brackets from section name
            std::cout << "Section: " << currentSection << '\n';//print section name
        } else {//New line
            std::cout<< line << '\n';//print key-value pair
        }
    }
}
