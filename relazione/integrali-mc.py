
import matplotlib.pyplot as plt

execfile('data/deltamc-10-10.py')

x = []
y = []

for i in dati:
    x.append(i[0])
    y.append(abs(i[1]))

plt.clf()
plt.plot(x, y, 'o')
plt.yscale('log')
plt.grid(True)
plt.xscale('log')
plt.xlabel('Numero di campionamenti')
plt.ylabel('Errore (modulo)')
plt.title(r"Metodo Montecarlo $\int_1^{10} (e^x+1+x^9-8x^8+\sinh(5x))e^{-x^2}dx$")

plt.savefig('images/montecarlo-err.png')