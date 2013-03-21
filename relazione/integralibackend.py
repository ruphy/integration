
import matplotlib.pyplot as plt

class IntegraliBackend:
  
  def __init__(self, titolo, legenda1='lower left', legenda2='lower right'):
    self.disegna1(legenda1)
    plt.savefig("images/integrali/integrali"+titolo+".png")
    #self.disegna2(legenda2)
    #plt.savefig("images/integrali/integrali-intervalli"+titolo+".png")
  
  def disegna1(self, legendt='lower left'):
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

  def disegna2(self, legendt='lower right'):
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
    
