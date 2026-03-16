import numpy as np
import matplotlib.pyplot as plt
data = np.loadtxt("company_sales_data.csv",delimiter=",", skiprows=1)

test = np.transpose(data)
x = test[0]
y = test[len(data[1])-1]
plt.plot(x,y)
plt.title("Company profit per month")
plt.xlabel("Month number")
plt.ylabel("Sales units in number")
plt.savefig("pic1.png")
plt.close()
plt.plot(x,y,color="red", linestyle="--", linewidth=3, marker="o", markerfacecolor="black")
plt.title("Company profit per month")
plt.xlabel("Month number")
plt.ylabel("Sales units in number")
plt.legend(["Profit data of the year"], loc="lower right")
plt.savefig("pic2.png")
plt.close()
