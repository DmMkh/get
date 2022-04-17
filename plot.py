import matplotlib.pyplot as plt
data = [1, 2, 3, 5, 6, 7, 3]

plt.plot(data)
plt.show()


data_str = [str(item) for item in data]
with open("data.txt", "w") as outfile:
    outfile.write("\n".join(data_str))
