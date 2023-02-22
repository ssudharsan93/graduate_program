#include <iostream>
#include "Firework.h"

using namespace std;

void Firework::Explode() {
    cout << "The firework goes off with a bang!" << endl;
}

Rocket::Rocket() {
    this->color = "red";
}

Rocket::Rocket(string color) {
    this->color = color;
}

void Rocket::Explode() {
    cout << "The sky is split by a column of "
        << this->color
        << " fire that then detonates!!"
        << endl;
}

Flower::Flower() {
    this->color = "yellow";
}

Flower::Flower(string color) {
    this->color = color;
}

void Flower::Explode() {
    cout << "The sky is lit up by a bright "
        << this->color
        << " flower of sparkles!"
        << endl;
}
