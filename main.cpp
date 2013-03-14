
#include <iostream>

#include "serie.h"
#include "esbase.h"

class Esercizi {
public:
    enum Esercizio {
        EsSerie,
        IntDeterm,
        IntMontecarlo,
        AgoBuffon
    };

    void run(Esercizio tipo);
};

void Esercizi::run(Esercizi::Esercizio tipo)
{
    EsBase *es;
    switch (tipo) {
        case EsSerie:
            es = new Serie;
            return;
        default:
            std::cout << "Esercizio non ancora implementato";
    }
    
    delete es;
}

int main(int argc, char **argv)
{
    Esercizi es;
    es.run(Esercizi::EsSerie);
    return 0;
}
