
#include <iostream>

#include "serie.h"
#include "esbase.h"
#include "integraledeterministico.h"

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
        case IntDeterm:
            es = new IntegraleDeterministico;
            return;
        default:
            std::cout << "Esercizio non ancora implementato" << std::endl;
    }

    delete es;
}

int main(int argc, char **argv)
{
    Esercizi es;
    es.run(Esercizi::IntDeterm);

    return 0;
}
