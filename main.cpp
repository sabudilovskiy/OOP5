#include <iostream>
#include "Planer.h"
#include "Support.h"
#include <vector>
int main() {
    double finish = input<double>([](double x){return x>0;},
                           [](std::string inp){return std::stod(inp);},
                           "������� ���������� �� ������: ",
                           "�������� ������, ��������� ����: ");
    int n = input<int>([](int x){return x>=0;},
                       [](std::string inp){return std::stoi(inp);},
                       "������� ���������� ��������, ����������� � �����: ",
                       "�������� ������, ��������� ����: ");
    int sec = input<int>([](int x){return x>=0;},
                         [](std::string inp){return std::stoi(inp);},
                         "������� �����, ����� ������� ����� ���������� ���������� ��������, ����������� � �����: ",
                         "�������� ������, ��������� ����: ");
    std::vector<Planer> planers;
    std::cout << "���� ����������: \n1) ���������� �������� : 500, ���������� 1450, ������ �������: 1000 * e^(0.5-1450/speed)\n";
    std::cout << "2) ���������� �������� : 500, ���������� 2000, ������ �������: 100 * e^(1-ln(1-speed/2000)\n";
    std::cout << "3) ���������� �������� : 500, ���������� 2000, ������ �������: 1000 * e^(1-arctan(1-speed/2000))\n";
    std::cout << "���� ��������� ������: \n1) ����������� : 10000, ����� �� ����������: ���������� �����������/������� ���������� ������� * 20\n";
    std::cout << "2) ����������� : 5000, ����� �� ����������: ����������(���������� �����������/������� ���������� �������) * 15\n";
    std::cout << "3) ����������� : 8000, ����� �� ����������: �������������(���������� �����������/������� ���������� �������) * 30. �������������� �����: ������ ������� �������� �� 40%\n";
    for (int i = 0; i < n; i++){
        int num_engine = input<int>([](int x){return 3>=x && x>=0;},
                                    [](std::string inp){return std::stoi(inp);},
                                    "������� ����� ���������, ������� ����� � �������: ",
                                    "�������� ������, ��������� ����: ");;
        int num_cargo = input<int>([](int x){return 3>=x && x>=0;},
                                    [](std::string inp){return std::stoi(inp);},
                                    "������� ����� ��������� �������, ������� ����� � �������: ",
                                    "�������� ������, ��������� ����: ");
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
                                     "������� �������� � ������� ����� ������ ������: ",
                                     "�������� ������, ��������� ����: ");
        bool error = true;
        try {
            engine->sec(speed);
            error = false;
        }
        catch (std::invalid_argument){
            while (error) {
                double speed = input<double>([](double x){return x>0;},
                                             [](std::string inp){return std::stod(inp);},
                                             "�������� ������, ��������� ����: ",
                                             "�������� ������, ��������� ����: ");
                try {
                    engine->sec(speed);
                    error = false;
                }
                catch (std::invalid_argument) {}
            }
        }
        int autorefuel = input<int>([](int x){return 80>=x && x>=0;},
                                    [](std::string inp){return std::stoi(inp);},
                                    "������� % �������, ��� ������� ����� ������ �����������: ",
                                    "�������� ������, ��������� ����: ");;
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
                            std::cout << "������ " << std::to_string(i + 1) << " ��������� �� ���������� ��� "<< std::to_string(planers[i].get_refuel_remain()) << "� � ����� �� ��������� 200 � ��� ������� �� ������ " << std::to_string(
                                    (int) (finish - planers[i].get_coord())) << '\n';
                        }
                        else std::cout << "������ " << std::to_string(i + 1) << " ����� �� ����������� ��������� � ��� ������� �� ������ " << std::to_string(
                                    (int) (finish - planers[i].get_coord())) << '\n';
                        all_finished = false;
                    }
                    else {
                        std::cout << "������ "  << std::to_string(i + 1) << " ������ ������. \n";
                        finished[i] = k;
                        if (!was_finish) was_finish = true;
                    }
                }
            }
        }
        if (was_finish) k++;
    }
    for (int i = 0; i < n; i++){
        std::cout << "������ "  << std::to_string(i + 1) << " ������ ������ " << std::to_string(finished[i]) << " �� �����\n";
    }
    return 0;
}
