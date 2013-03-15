
import matplotlib.pyplot as plt

#execfile("mc-out.py")
#execfile('deltamc.py')
execfile('build/deltamc2.py')

x = []
y = []

for i in a:
    x.append(i[0])
    y.append(abs(i[1]))

plt.clf()
plt.plot(x, y, '.-')
plt.yscale('log')
plt.grid(True)
plt.xscale('log')
plt.xlabel('Numero di campionamenti')
plt.ylabel('Errore (modulo)')

plt.savefig('images/outmc.png')

