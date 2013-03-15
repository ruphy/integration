import math
import matplotlib.pyplot as plt
import numpy as np

def f(x):
  return (np.exp(x)+1+x**9-8*x**8+np.sinh(5*x))*np.exp(-1*(x**2))

plt.clf()
xin = np.arange(0, 10, 0.05)
yin = f(xin)
plt.plot(xin, yin)
plt.grid(True)
plt.title(r"Grafico di $(e^x+1+x^9-8x^8+\sinh(5x))e^{-x^2}$ tra 0 e 10")
plt.savefig("funzione-integranda.png")

plt.clf()
xin = np.arange(0, 10, 0.05)
yin = f(xin)
plt.plot(xin, yin)
plt.yscale('log')
plt.grid(True)
plt.title(r"Grafico di $(e^x+1+x^9-8x^8+\sinh(5x))e^{-x^2}$ tra 0 e 10")
plt.savefig("funzione-integranda-log.png")
