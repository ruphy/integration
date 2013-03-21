execfile('valorevero.py')
execfile("integralibackend.py")

def plot(titolo='', legenda1='lower left', legenda2='lower right'):
  i = IntegraliBackend(titolo)

# Risultati di integrazione tra 1 e 10

## Legenda:
# [0]: n intervalli
# [1]: trapezi
# [2]: simpson
# [3]: quadrature gaussiane


execfile('data/det-sommaimprecisa.py')
plot('sommaimprecisa')

execfile('data/dati-det-sommagiusta.py')
plot('sommaprecisa')

execfile('data/dati-det-sommagiusta-big.py')
plot('sommaprecisa-big', 'upper-right', 'upper-left')


