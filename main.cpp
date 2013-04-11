
#include <iostream>

#include "serie.h"
#include "esbase.h"
#include "integrali/integralemc.h"
#include "integrali/integraledeterministico.h"
#include "agobuffon.h"

class Esercizi {
public:
    enum Esercizio {
        EsSerie,
        IntDeterm,
        IntMontecarlo,
        AgoBuffonTipo
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
        case AgoBuffonTipo:
            es = new AgoBuffon;
            return;
        default:
            std::cout << "Esercizio non ancora implementato" << std::endl;
    }

    delete es;
}

int main(int argc, char **argv)
{
    Esercizi es;
    es.run(Esercizi::AgoBuffonTipo);

    return 0;
}
