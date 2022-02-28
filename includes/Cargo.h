//
// Created by MRV on 29.11.2021.
//

#ifndef OOP5_CARGO_H
#define OOP5_CARGO_H
#include <cmath>
class Cargo{
protected:
    double current_fuel;
    double max_fuel;
public:
    virtual int get_time_refueling() = 0;
    void refuel(){
        current_fuel = max_fuel;
    };
    virtual bool get_fuel(double fuel) = 0;
    int get_percent(){
        return floor(current_fuel / max_fuel * 100);
    };
};

class First_Cargo : public Cargo{
public:
    First_Cargo(){
        max_fuel = 10000;
        current_fuel = max_fuel;
    }
    int get_time_refueling() override{
        return ceil(log(max_fuel/current_fuel)*20);
    }
    bool get_fuel(double fuel) override{
        if (current_fuel > fuel){
            current_fuel -= fuel;
            return true;
        }
        else return false;
    }
};
class Second_Cargo : public Cargo{
public:
    Second_Cargo(){
        max_fuel = 5000;
        current_fuel = max_fuel;
    }
    int get_time_refueling() override{
        return ceil(atan(max_fuel/current_fuel) * 15);
    }
    bool get_fuel(double fuel) override{
        if (current_fuel > fuel){
            current_fuel -= fuel;
            return true;
        }
        else return false;
    }
};
class Thirst_Cargo : public Cargo{
public:
    Thirst_Cargo(){
        max_fuel = 8000;
        current_fuel = max_fuel;
    }
    int get_time_refueling() override{
        return ceil(asinh(max_fuel/current_fuel) * 30);
    }
    bool get_fuel(double fuel) override{
        if (current_fuel > fuel*0.6){
            current_fuel -= fuel*0.6;
            return true;
        }
        else return false;
    }
};

#endif //OOP5_CARGO_H
