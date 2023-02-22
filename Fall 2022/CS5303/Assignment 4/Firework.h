#ifndef FIREWORK_H
#define FIREWORK_H

#include <string>

using namespace std;

class Firework {
    protected:
        string color;
    public:
        virtual void Explode();
};

class Rocket : public Firework {
    public:
        Rocket();
        Rocket(string color);
        void Explode();
};

class Flower : public Firework {
    public:
        Flower();
        Flower(string color);
        void Explode();
};

#endif
