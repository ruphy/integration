
# array indexes:
# [0]: max sum n
# [1]: sum result
# [2]: delta sum da expected (pi^2/6 = 1.64493406685)

sommaCrescente = [[2, 1.25, -0.394934],[4, 1.42361, -0.221323],[8, 1.52742, -0.117512],[16, 1.58435, -0.0605875],[32, 1.61417, -0.0307666],[64, 1.62943, -0.0155034],[128, 1.63715, -0.00778199],[256, 1.64104, -0.00389827],[512, 1.64298, -0.00195135],[1024, 1.64396, -0.000976333],[2048, 1.64444, -0.000490555],[4096, 1.64473, -0.000208744],[8192, 1.64473, -0.000208744],[16384, 1.64473, -0.000208744],[32768, 1.64473, -0.000208744],[65536, 1.64473, -0.000208744],[131072, 1.64473, -0.000208744],[262144, 1.64473, -0.000208744],[524288, 1.64473, -0.000208744],[1048576, 1.64473, -0.000208744],[2097152, 1.64473, -0.000208744],[4194304, 1.64473, -0.000208744],[8388608, 1.64473, -0.000208744],[16777216, 1.64473, -0.000208744],[33554432, 1.64473, -0.000208744],[67108864, 1.64473, -0.000208744],[134217728, 1.64473, -0.000208744],[268435456, 1.64473, -0.000208744],[536870912, 1.64473, -0.000208744],[1073741824, 1.64473, -0.000208744]]

sommaDecrescente = [[2, 1.25, -0.394934],[4, 1.42361, -0.221323],[8, 1.52742, -0.117512],[16, 1.58435, -0.0605875],[32, 1.61417, -0.0307669],[64, 1.62943, -0.0155035],[128, 1.63715, -0.00778211],[256, 1.64104, -0.00389863],[512, 1.64298, -0.00195123],[1024, 1.64396, -0.000976094],[2048, 1.64445, -0.000488171],[4096, 1.64469, -0.000244149],[8192, 1.64481, -0.000122079],[16384, 1.64487, -6.10438e-05],[32768, 1.6449, -3.05262e-05],[65536, 1.64492, -1.52674e-05],[131072, 1.64493, -7.63806e-06],[262144, 1.64493, -3.82336e-06],[524288, 1.64493, -1.91601e-06],[1048576, 1.64493, -9.62335e-07],[2097152, 1.64493, -4.85498e-07],[4194304, 1.64493, -2.47079e-07],[8388608, 1.64493, -1.2787e-07],[16777216, 1.64493, -1.2787e-07],[33554432, 1.64493, -8.66061e-09],[67108864, 1.64493, -8.66061e-09],[134217728, 1.64493, -8.66061e-09],[268435456, 1.64493, -8.66061e-09],[536870912, 1.64493, -8.66061e-09],[1073741824, 1.64493, -8.66061e-09]]


# TODO: Make plot of this

import matplotlib.pyplot as plt

plt.clf()
plt.title(r"$\sum_{i=1}^{N} \frac{1}{n^2}$")
#for i in [1, 2]:
a = []
n = []
for el in sommaCrescente:
  a.append(abs(el[2]))
  n.append(el[0])
plt.plot(n, a)
for el in sommaDecrescente:
  a.append(abs(el[2]))
  n.append(el[0])
plt.plot(n, a)
plt.yscale('log')
plt.xscale('log')
  
plt.legend(('Metodo dei trapezi', 'Metodo di Simpson'),
           'upper center', shadow=True, fancybox=True)
plt.grid(True)
plt.savefig("serie.png")


