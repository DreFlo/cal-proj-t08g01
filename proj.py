import matplotlib.pyplot as plt
import numpy as np
import math

m = 10

x = [i for i in range(1, m + 1)]
h_k = [math.pow(x, 2) * math.pow(2, x) for x in range(1, m + 1)]
fact = [math.factorial(x) for x in range(1, m + 1)]

brute = lambda x : math.factorial(x)

plt.plot(x, h_k)
plt.plot(x, fact)
plt.show()
