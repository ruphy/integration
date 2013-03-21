
import matplotlib.pyplot as plt
import numpy as np

def func(P, x):
  return P[0]*pow(x,-1*P[1])   # Passiamo i parametri come array: P[0] = m; P[1] = q


class IntegraliBackend:
  
  def __init__(self, titolo, legenda1='lower left', legenda2='lower right', giaerrore=False, minx=1, maxx=10):
    if(giaerrore):
      self.disegna3(legenda1)
    else:
      self.disegna1(legenda1)
    param = self.findfit(minx, maxx)
    xin = np.arange(2, 100)
    yin = func(param, xin)
    plt.plot(xin, yin)
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
    
  def disegna3(self, legendt='lower left'):
    plt.clf()
    plt.title(r"$\int_1^{10} (e^x+1+x^9-8x^8+\sinh(5x))e^{-x^2}dx$")
    for i in [1, 3, 2]:
      a = []
      n = []
      for el in funzione1:
	a.append(abs(el[i]))
	n.append(el[0])
      plt.plot(n, a, '.-')
      plt.yscale('log')
      plt.xscale('log')
      
    plt.xlabel('Numero di intervalli')
    plt.ylabel('Errore (modulo)')
    plt.legend(('Metodo dei trapezi', 'Quadrature gaussiane', 'Metodo di Simpson'),
	      legendt, shadow=True, fancybox=True)
    plt.grid(True)

  def findfit(self, minx, maxx):
    from scipy import odr

    xdata = []
    ydata = []
    for i in [3]:
      for el in funzione1:
	if(el[0] > minx and el[0] < maxx):
	  ydata.append(el[i])
	  xdata.append(el[0])
    
    # A questo punto creiamo il "modello", la rappresentazione della funzione per ODR
    mymodel = odr.Model(func)
    
    # Creiamo un oggetto che contenga i dati
    mydata = odr.RealData(xdata, ydata)
    
    # In questa riga il parametro beta0 rappresenta le scelte iniziali;
    # maxit rappresenta le massime iterazioni - impostiamo 1000 di default
    myodr = odr.ODR(mydata, mymodel, beta0=[1.,3.],  maxit=10000)
    
    # Fa girare il fit
    myoutput = myodr.run()
    
    # Stampa i dati piu importanti
    myoutput.pprint()
    
    return myoutput.beta
    # Oppure accedo ai dati che mi interessano, direttamente:
    #print myouput.beta   # parametri
    #print myouput.delta  # errori stimati slle x
    # eccetera...

