import matplotlib.pyplot as plt
import sys
import json

header = sys.argv[1]

with open('data.json') as file:
    data = json.load(file)

plt.plot(data[0], data[1])

plt.xlabel('Time')
plt.ylabel('Iterations')
plt.title(header)
plt.grid(True)

plt.show()