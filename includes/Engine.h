//
// Created by MRV on 29.11.2021.
//

#ifndef OOP5_ENGINE_H
#define OOP5_ENGINE_H
#include <cmath>
#include <stdexcept>
class Engine{
protected:
    double min_speed, max_speed;
public:
    virtual double sec(double cur_speed) = 0;
};
class First_Engine : public Engine{
public:
    First_Engine(){
        min_speed = 500;
        max_speed = 1450;
    }
    double sec(double cur_speed) override{
        if (cur_speed >= 500 && cur_speed <= 1450) {
            double answer = 0.5 - 1451/cur_speed;
            answer = exp (answer);
            answer = 1000*answer;
            return answer ;
        }
        else throw std::invalid_argument("");
    }
};
class Second_Engine : public Engine{
public:
    Second_Engine(){
        min_speed = 500;
        max_speed = 2000;
    }
    double sec(double cur_speed) override{
        if (cur_speed >= 500 && cur_speed <= 2000) {
            double answer = 100 * exp(1 - log(1 - cur_speed / 2100));
            return answer;
        }
        else throw std::invalid_argument("");
    }
};
class Thirst_Engine : public Engine{
public:
    Thirst_Engine(){
        min_speed = 500;
        max_speed = 2000;
    }
    double sec(double cur_speed) override{
        if (cur_speed >= 500 && cur_speed <= 2000) {
            double answer = 1000 * exp(1 - atan(1 - cur_speed / 2000));
            return answer;
        }
        else throw std::invalid_argument("");
    }
};
#endif //OOP5_ENGINE_H
