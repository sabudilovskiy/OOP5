//
// Created by MRV on 29.11.2021.
//

#ifndef OOP5_SUPPORT_H
#define OOP5_SUPPORT_H
#include <string>
template <class T>
T input(bool (*verifer)(T), T (*converter)(std::string), const std::string& input, const std::string& _error) {
    std::string temp;
    std::cout << input;
    std::cin >> temp;
    try {
        T answer = converter(temp);
        if (verifer(answer)) return answer;
        throw std::invalid_argument("");
    }
    catch (std::invalid_argument) {
        while (true) {
            std::cout << _error;
            std::cin >> temp;
            try {
                T answer = converter(temp);
                if (verifer(answer)) return answer;
            }
            catch (std::invalid_argument) {
            }
        }
    }
}
#endif //OOP5_SUPPORT_H
