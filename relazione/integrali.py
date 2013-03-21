
# Risultati di integrazione tra 1 e 10

## Legenda:
# [0]: n intervalli
# [1]: trapezi
# [2]: simpson
# [3]: quadrature gaussiane

### Funzione 1
### (exp(x)+1+pow(x,9)-8*pow(x,8)+sinh(5*x))*exp(-pow(x,2));
execfile('valorevero.py')

import matplotlib.pyplot as plt

def disegna1(legendt='lower left'):
  plt.clf()
  plt.title(r"$\int_1^{10} (e^x+1+x^9-8x^8+\sinh(5x))e^{-x^2}dx$")
  for i in [1, 3, 2]:
    a = []
    n = []
    for el in funzione1:
      a.append(abs(el[i]-funz1vero))
      n.append(el[0])
    plt.plot(n, a, '.-')
    plt.yscale('log')
    plt.xscale('log')
    
  plt.xlabel('Numero di intervalli')
  plt.ylabel('Errore (modulo)')
  plt.legend(('Metodo dei trapezi', 'Quadrature gaussiane', 'Metodo di Simpson'),
	    legendt, shadow=True, fancybox=True)
  plt.grid(True)

def disegna2(legendt='lower right'):
  plt.clf()
  plt.title(r"$\int_1^{10} (e^x+1+x^9-8x^8+\sinh(5x))e^{-x^2}dx$")
  for i in [1, 3, 2]:
    a = []
    n = []
    for el in funzione1:
      a.append(abs(el[i]-funz1vero))
      n.append(1./(10*el[0]))
    plt.plot(n, a, '.-')
    plt.yscale('log')
    plt.xscale('log')
    
  plt.xlabel('Larghezza dell\'intervallo')
  plt.ylabel('Errore (modulo)')
  plt.legend(('Metodo dei trapezi', 'Quadrature gaussiane', 'Metodo di Simpson'),
	    legendt, shadow=True, fancybox=True)
  plt.grid(True)
  
  
execfile('data/dati-det-sommaimprecisa.py')
disegna1()
plt.savefig("images/integrali.png")
disegna2()
plt.savefig("images/integrali-intervalli.png")


execfile('data/dati-det-sommagiusta.py')
disegna1()
plt.savefig("images/integrali-sommaprecisa.png")
disegna2()
plt.savefig("images/integrali-sommaprecisa-intervalli.png")


execfile('data/dati-det-sommagiusta-big.py')
disegna1(legendt='upper right')
plt.savefig("images/integrali-sommaprecisa-big.png")
disegna2(legendt='upper left')
plt.savefig("images/integrali-sommaprecisa-intervalli-big.png")


