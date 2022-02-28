//
// Created by MRV on 29.11.2021.
//

#ifndef OOP5_PLANER_H
#define OOP5_PLANER_H
#include "Cargo.h"
#include "Engine.h"
class Planer{
    int refuel_remain, auto_refuel;
    double speed, coord;
    Cargo* cargo;
    Engine* engine;
public:
    Planer(){}
    Planer(Cargo *cargo, Engine *engine, double speed, int auto_refuel) : cargo(cargo), engine(engine), speed(speed), refuel_remain(0), coord(0), auto_refuel(auto_refuel) {}
    void sec(){
        if (refuel_remain == 0){
            int cur_percent = cargo->get_percent();
            if (cur_percent < auto_refuel || !cargo->get_fuel(engine->sec(speed))){
                refuel_remain = cargo->get_time_refueling() - 1;
                cargo->refuel();
                coord+=200;
            }
            else coord+=speed;
        }
        else {
            refuel_remain--;
            coord+=200;
        }
    }
    double get_coord() const {
        return coord;
    }
    int get_refuel_remain() const {
        return refuel_remain;
    }
};
#endif //OOP5_PLANER_H
