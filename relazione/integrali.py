execfile('valorevero.py')
execfile("integralibackend.py")

def plot(titolo='', legenda1='lower left', legenda2='lower right', giaerrore=False, minx=1, maxx=10):
  i = IntegraliBackend(titolo, legenda1, legenda2, giaerrore, minx, maxx)
  #i.findfit(minx, maxx)

# Risultati di integrazione tra 1 e 10

## Legenda:
# [0]: n intervalli
# [1]: trapezi
# [2]: simpson
# [3]: quadrature gaussiane


#execfile('data/det-sommaimprecisa.py')
#plot('sommaimprecisa', minx=10, maxx=15)

execfile('data/dati-det-sommagiusta.py')
plot('sommaprecisa', minx=20, maxx=25)

#execfile('data/dati-det-sommagiusta-big.py')
#plot('sommaprecisa-big', 'upper right', 'upper left', minx=10, maxx=20)

execfile('data/det-bigprecision.py')
plot('bigprecision', 'upper right', 'upper left', True, 10, 60)