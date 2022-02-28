#include <iostream>
#include "Planer.h"
#include "Support.h"
#include <vector>
int main() {
    double finish = input<double>([](double x){return x>0;},
                           [](std::string inp){return std::stod(inp);},
                           "Введите расстояние до финиша: ",
                           "Допущена ошибка, повторите ввод: ");
    int n = input<int>([](int x){return x>=0;},
                       [](std::string inp){return std::stoi(inp);},
                       "Введите количество самолётов, участвующих в гонке: ",
                       "Допущена ошибка, повторите ввод: ");
    int sec = input<int>([](int x){return x>=0;},
                         [](std::string inp){return std::stoi(inp);},
                         "Введите время, через которое будет выводиться координаты самолётов, участвующих в гонке: ",
                         "Допущена ошибка, повторите ввод: ");
    std::vector<Planer> planers;
    std::cout << "Виды двигателей: \n1) наименьшая скорость : 500, наибольшая 1450, расход топлива: 1000 * e^(0.5-1450/speed)\n";
    std::cout << "2) наименьшая скорость : 500, наибольшая 2000, расход топлива: 100 * e^(1-ln(1-speed/2000)\n";
    std::cout << "3) наименьшая скорость : 500, наибольшая 2000, расход топлива: 1000 * e^(1-arctan(1-speed/2000))\n";
    std::cout << "Виды топливных систем: \n1) вместимость : 10000, время на дозаправку: наибольшая вместимость/текущее количество топлива * 20\n";
    std::cout << "2) вместимость : 5000, время на дозаправку: арктангенс(наибольшая вместимость/текущее количество топлива) * 15\n";
    std::cout << "3) вместимость : 8000, время на дозаправку: аркгиперсинус(наибольшая вместимость/текущее количество топлива) * 30. Дополнительный бонус: расход топлива уменьшен на 40%\n";
    for (int i = 0; i < n; i++){
        int num_engine = input<int>([](int x){return 3>=x && x>=0;},
                                    [](std::string inp){return std::stoi(inp);},
                                    "Введите номер двигателя, который будет в самолёте: ",
                                    "Допущена ошибка, повторите ввод: ");;
        int num_cargo = input<int>([](int x){return 3>=x && x>=0;},
                                    [](std::string inp){return std::stoi(inp);},
                                    "Введите номер топливной системы, который будет в самолёте: ",
                                    "Допущена ошибка, повторите ввод: ");
        Cargo* cargo = nullptr;
        switch(num_cargo){
            case 1:
                cargo = new First_Cargo();
                break;
            case 2:
                cargo = new Second_Cargo();
                break;
            case 3:
                cargo = new Thirst_Cargo();
                break;
        }
        Engine* engine = nullptr;
        switch(num_engine){
            case 1:
                engine = new First_Engine();
                break;
            case 2:
                engine = new Second_Engine();
                break;
            case 3:
                engine = new Thirst_Engine();
                break;
        }
        double speed = input<double>([](double x){return x>0;},
                                     [](std::string inp){return std::stod(inp);},
                                     "Введите скорость с которой будет лететь самолёт: ",
                                     "Допущена ошибка, повторите ввод: ");
        bool error = true;
        try {
            engine->sec(speed);
            error = false;
        }
        catch (std::invalid_argument){
            while (error) {
                double speed = input<double>([](double x){return x>0;},
                                             [](std::string inp){return std::stod(inp);},
                                             "Допущена ошибка, повторите ввод: ",
                                             "Допущена ошибка, повторите ввод: ");
                try {
                    engine->sec(speed);
                    error = false;
                }
                catch (std::invalid_argument) {}
            }
        }
        int autorefuel = input<int>([](int x){return 80>=x && x>=0;},
                                    [](std::string inp){return std::stoi(inp);},
                                    "Введите % топлива, при котором будет вызван дозаправщик: ",
                                    "Допущена ошибка, повторите ввод: ");;
        planers.emplace_back(cargo, engine, speed, autorefuel);
    }
    bool all_finished = false;
    int* finished = new int[n];
    for (int i = 0; i < n; i++) finished[i] = -1;
    int j = 0;
    int k = 1;
    while (!all_finished){
        all_finished = true;
        bool was_finish = false;
        for (int i = 0; i < n; i++){
            if (finished[i] == -1){
                planers[i].sec();
                if (j % sec == 0) {
                    if (finish - planers[i].get_coord() > 0) {
                        if (planers[i].get_refuel_remain() > 0){
                            std::cout << "Самолёт " << std::to_string(i + 1) << " находится на дозаправке ещё "<< std::to_string(planers[i].get_refuel_remain()) << "с и летит со скоростью 200 и ему остаётся до финиша " << std::to_string(
                                    (int) (finish - planers[i].get_coord())) << '\n';
                        }
                        else std::cout << "Самолёт " << std::to_string(i + 1) << " летит со стандартной скоростью и ему остаётся до финиша " << std::to_string(
                                    (int) (finish - planers[i].get_coord())) << '\n';
                        all_finished = false;
                    }
                    else {
                        std::cout << "Самолёт "  << std::to_string(i + 1) << " достиг финиша. \n";
                        finished[i] = k;
                        if (!was_finish) was_finish = true;
                    }
                }
            }
        }
        if (was_finish) k++;
    }
    for (int i = 0; i < n; i++){
        std::cout << "Самолёт "  << std::to_string(i + 1) << " достиг финиша " << std::to_string(finished[i]) << " по счёту\n";
    }
    return 0;
}
