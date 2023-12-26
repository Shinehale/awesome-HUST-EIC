import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# define the basic variables
m = 27.5 / np.sqrt(2) + 2
pi = 3.1415926
s0, s1 = [0, -m, m], [0, m, m]
alpha0, alpha1 = 3 / 4 * pi, 1 / 4 * pi
startHelix = 10
radiusChange = 2.5
turns = 5

def calculateB(x, y, z, elev=None, azim=None):
    x_values, y_values, z_values = [], [], []
    for x_val in np.arange(0, 10 * np.pi, 0.001):
        rPrime = calculateRPrime(x_val)
        x_new = s0[0] + rPrime * np.sin(x_val)
        y_new = s0[1] + rPrime * np.cos(x_val) * np.sin(alpha0)
        z_new = s0[2] + rPrime * np.cos(x_val) * np.cos(alpha0)
        x_values.append(x_new)
        y_values.append(y_new)
        z_values.append(z_new)

    # Plot the values for verifying
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    if elev is not None and azim is not None:
        ax.view_init(elev=elev, azim=azim)

    ax.scatter(x_values, y_values, z_values, label='Points (x, y, z)')
    ax.set_xlabel('x values')
    ax.set_ylabel('y values')
    ax.set_zlabel('z values')
    ax.set_title('Plot of Points (x, y, z) along the helix')
    plt.legend()
    plt.show()


def calculateRPrime(x):
    return startHelix + x * radiusChange / (2 * np.pi)


if __name__ == "__main__":
    calculateB(5, 0, 0, elev=50, azim=40)  # Example: Point (x, r') at x=5
