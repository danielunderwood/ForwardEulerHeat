import numpy as np
import matplotlib.pyplot as plot

# Read In data File
data = np.genfromtxt("../data.dat", delimiter="\t")

x = np.linspace(0.0, 1.0, num=data[1,:].size)

# Plot Daya
p1 = plot.plot(x, data[1,:], linewidth=1)
p2 = plot.plot(x, data[10, :], linewidth=2)
p3 = plot.plot(x, data[100, :], linewidth=3)
p4 = plot.plot(x, data[1000, :], linewidth=4)
p5 = plot.plot(x, data[10000, :], linewidth=5)
plot.ylabel("Temperature (u)")
plot.xlabel("Position")
plot.title("Heat Equation Solution")
plot.show()
