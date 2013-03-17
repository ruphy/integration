
import matplotlib.pyplot as plt
import numpy as np

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

execfile('data/mc-stat-10-8.py')
x = []
y = []
errors = []

for i in dati:
    x.append(i[0])
    y.append(abs(i[1]-417.8077704440582))
    errors.append(i[2])

# Mantieni gli errori positivi (log plot)
y = np.array(y)
errors = np.array(errors)
#ylower = np.maximum(1e-4, y - errors)
#yerr_lower = y - ylower
ylower = np.zeros_like(y)
yerr_lower = ylower

plt.clf()
plt.errorbar(x, y, xerr=0, yerr=[yerr_lower, 2*errors], fmt='.') #xerr=errors, fmt='.')
plt.yscale('log')
plt.grid(True)
plt.xscale('log')
plt.xlabel('Numero di campionamenti')
plt.ylabel('Errore medio (modulo)')
plt.title(r"Metodo Montecarlo $\int_1^{10} (e^x+1+x^9-8x^8+\sinh(5x))e^{-x^2}dx$")

plt.savefig('images/montecarlo-con-stat.png')
