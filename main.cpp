
#include <iostream>

#include "src/serie.h"
#include "src/esbase.h"
#include "src/integrali/integralemc.h"
#include "src/integrali/integraledeterministico.h"
#include "src/agobuffon.h"
#include "src/pathint/pathint.h"

class Esercizi {
public:
    enum Esercizio {
        EsSerie,
        IntDeterm,
        IntMontecarlo,
        AgoBuffonTipo,
        PathIntegral

    };

    void run(Esercizio tipo);
};

void Esercizi::run(Esercizi::Esercizio tipo)
{
    EsBase *es;
    switch (tipo) {
        case EsSerie:
            es = new Serie;
            break;
        case IntDeterm:
            es = new IntegraleDeterministico(1, 10);
            break;
        case IntMontecarlo:
            es = new IntegraleMC(1, 10);
            break;
        case AgoBuffonTipo:
            es = new AgoBuffon;
            break;
        case PathIntegral:
            es = new PathInt;
            break;
        default:
            std::cout << "Esercizio non ancora implementato" << std::endl;
    }

    es->statRun();
    delete es;
}

int main(int argc, char **argv)
{
    Esercizi es;
    es.run(Esercizi::PathIntegral);

    return 0;
}
