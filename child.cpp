#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    std::string str;
    std::ofstream file(argv[1]); // вызывает open() в режиме "w" (создать и записать) (если уже есть - перезаписать)
    if(!file.is_open()) return 1;
    while(getline(std::cin, str)) {
        std::stringstream ss(str);
        int first_num;
        if(!(ss >> first_num)) continue;
        int div;
        while(ss >> div) {
            if(div == 0) {
                file.close();
                return 1;
            }
            first_num /= div;
        }
        file << first_num << '\n';
    }
    file.close();
    return 0;
}