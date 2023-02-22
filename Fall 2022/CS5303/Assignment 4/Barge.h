#ifndef BARGE_H
#define BARGE_H

#include <vector>
#include "Firework.h"

class Barge {
    private:
        vector<Firework *> fireworks;
        string name;

    public:
        Barge(string barge_name);
        void LoadFirework(Firework * new_firework);
        void Ignite();

};

#endif
