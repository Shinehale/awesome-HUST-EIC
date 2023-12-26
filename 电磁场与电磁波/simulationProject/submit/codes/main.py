import numpy as np
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib import axes
from matplotlib.font_manager import FontProperties
font = FontProperties(fname='/Library/Fonts/Songti.ttc')

# define the basic variables
m = 27.5 / np.sqrt(2) + 2
pi = 3.1415926
s0, s1 = [0, -m, m], [0, m, m]
alpha0, alpha1 = 3 / 4 * pi, 1 / 4 * pi
startHelix = 10
radiusChange = 2.5
turns = 5
mu = 4*np.pi * 1e-7
I = 1


def calculateB(x, y, z):
    tar = np.array([x, y, z])
    sumB = np.array([0.0, 0.0, 0.0])
    pre = None
    # calculate r_prime for all the cases
    r_prime_values = [calculateRPrime(x_val) for x_val in np.arange(0, 10 * np.pi, 0.01)]

    for s in [s0, s1]:
        pre = None
        for x_val, rPrime in zip(np.arange(0, 10 * np.pi, 0.1), r_prime_values):
            # calculate the position of new point
            x_new = s[0] + rPrime * np.sin(x_val)
            y_new = s[1] + rPrime * np.cos(x_val) * np.sin(alpha0 if s == s0 else alpha1)
            z_new = s[2] + rPrime * np.cos(x_val) * np.cos(alpha0 if s == s0 else alpha1)

            if pre is not None:
                cur = np.array([x_new, y_new, z_new])
                # calculate the vector dl
                dl = pre - cur

                # calculate the vector r and |r|^3
                r = cur - tar
                r_norm = np.linalg.norm(r) ** 3

                # calculate dl x r and sum them altogether
                demo_B = np.cross(dl, r)
                sumB += demo_B / r_norm

            pre = np.array([x_new, y_new, z_new])
    # return back
    return mu * I * np.linalg.norm(sumB) / (4 * np.pi)


def calculateRPrime(x):
    return startHelix + x * radiusChange / (2 * np.pi)



def simulateXY():
    x_values, y_values= np.arange(-20, 20, 0.5), np.arange(-20, 20, 0.5)
    B_values = []
    for x in x_values:
        temp = []
        for y in y_values:
            temp.append(calculateB(x, y, 0))
        B_values.append(temp)
        print(x)
    fig = plt.figure()
    ax = fig.add_subplot(111)

    fig, ax = plt.subplots()
    im = ax.imshow(B_values, cmap=plt.cm.hot_r)

    # 设置 xy 轴方向的刻度和标签
    x_ticks = np.arange(0, len(x_values), 10)
    y_ticks = np.arange(0, len(y_values), 10)

    ax.set_xticks(x_ticks)
    ax.set_xticklabels(x_values[x_ticks])
    ax.set_yticks(y_ticks)
    ax.set_yticklabels(y_values[y_ticks])

    # 显示颜色条
    cbar = plt.colorbar(im)
    cbar.set_label('Magnetic Field Strength')

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_title('Heatmap of Magnetic Field Strength in XY Plane')

    plt.show()


def simulateXZ():
    x_values, z_values= np.arange(-20, 20, 0.5), np.arange(-20, 20, 0.5)
    B_values = []
    for x in x_values:
        temp = []
        for z in z_values:
            temp.append(calculateB(x, 0, z))
        B_values.append(temp)
        print(x)
    fig = plt.figure()
    ax = fig.add_subplot(111)

    fig, ax = plt.subplots()
    im = ax.imshow(B_values, cmap=plt.cm.hot_r)

    # 设置 xy 轴方向的刻度和标签
    x_ticks = np.arange(0, len(x_values), 10)
    y_ticks = np.arange(0, len(z_values), 10)

    ax.set_xticks(x_ticks)
    ax.set_xticklabels(x_values[x_ticks])
    ax.set_yticks(y_ticks)
    ax.set_yticklabels(z_values[y_ticks])

    # 显示颜色条
    cbar = plt.colorbar(im)
    cbar.set_label('Magnetic Field Strength')

    ax.set_xlabel('X')
    ax.set_ylabel('Z')
    ax.set_title('Heatmap of Magnetic Field Strength in XZ Plane')

    plt.show()


def simulateYZ():
    y_values, z_values= np.arange(-20, 20, 0.5), np.arange(-20, 20, 0.5)
    B_values = []
    for y in y_values:
        temp = []
        for z in z_values:
            temp.append(calculateB(0, y, z))
        B_values.append(temp)
        print(y)
    fig = plt.figure()
    ax = fig.add_subplot(111)

    fig, ax = plt.subplots()
    im = ax.imshow(B_values, cmap=plt.cm.hot_r)

    # 设置 xy 轴方向的刻度和标签
    x_ticks = np.arange(0, len(y_values), 10)
    y_ticks = np.arange(0, len(z_values), 10)

    ax.set_xticks(x_ticks)
    ax.set_xticklabels(y_values[x_ticks])
    ax.set_yticks(y_ticks)
    ax.set_yticklabels(z_values[y_ticks])

    # 显示颜色条
    cbar = plt.colorbar(im)
    cbar.set_label('Magnetic Field Strength')

    ax.set_xlabel('Y')
    ax.set_ylabel('Z')
    ax.set_title('Heatmap of Magnetic Field Strength in YZ Plane')

    plt.show()



if __name__ == "__main__":
    simulateXY()
    simulateXZ()
    simulateYZ()

