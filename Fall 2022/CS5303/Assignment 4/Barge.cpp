#include <iostream>
#include "Barge.h"

using namespace std;

Barge::Barge(string barge_name) {
    this->name = barge_name;
}

void Barge::LoadFirework(Firework *new_firework) {
    this->fireworks.push_back(new_firework);
}

void Barge::Ignite() {
    cout << "Barge " << this->name << " sets off its display!" << endl;
    int number_of_fireworks = this->fireworks.size();
    for (int current_firework_num = 0; current_firework_num < number_of_fireworks; current_firework_num++){
        fireworks[current_firework_num]->Explode();
    }
}
