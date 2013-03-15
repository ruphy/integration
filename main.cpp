
#include <iostream>

#include "serie.h"
#include "esbase.h"
#include "integrali/integralemc.h"
#include "integrali/integraledeterministico.h"

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
            es = new IntegraleDeterministico(1, 10);
            return;
        case IntMontecarlo:
            es = new IntegraleMC(1, 10);
            return;
        case AgoBuffon:
            es;
            return;
        default:
            std::cout << "Esercizio non ancora implementato" << std::endl;
    }

    delete es;
}

int main(int argc, char **argv)
{
    Esercizi es;
    es.run(Esercizi::IntMontecarlo);

    return 0;
}
