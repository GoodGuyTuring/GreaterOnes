import numpy as np
from mpl_toolkits.mplot3d.axes3d import Axes3D
from matplotlib import pyplot


def ComputeTPSWeights(X, Y, Z):
    # erstellt die Matrix A mit der Dimension mxm

    A = np.zeros((len(X), len(X)))
    for i in range(len(X)):
        for j in range(len(X)):
            if i != j:
                r = np.sqrt((X[i] - X[j]) ** 2 + (Y[i] - Y[j]) ** 2)
                A[i][j] = r ** 2 + np.log(r)
    # gibt eine Lösung für das lineare Gleichungssystem zurück
    w = np.linalg.solve(A, Z)
    return w


def EvaluateTPSSpline(XNew, YNew, X, Y, Weights):

    # Falls XNew nur 1-dimensional ist:

    if len(XNew.shape) == 1:
        re_val = np.zeros((len(XNew)))

        # berechnet für jeden x bzw. y Wert das dazugehörige z

        for i in range(len(XNew)):
            xn = XNew.item(i)
            yn = YNew.item(i)
            new_val = 0

            # berechnet die Summe aus w*g(Norm((x,y)-(xj,yj))

            for j in range(len(X)):
                x = X.item(j)
                y = Y.item(j)
                R = np.sqrt(((xn - x) ** 2 + (yn - y) ** 2))
                if R != 0:
                    new_val = new_val + (R ** 2 + np.log(R)) * Weights.item(j)
            # Zuweisung zum Rückgabearray an der Stelle i
            re_val[i] = new_val

        return re_val

    # Wenn XNew 2-dimensional ist:

    re_val = np.zeros((len(XNew), len(XNew)))
    # Das Array besitzt n*m Einträge, wobei für jeden z berechnet werden muss
    for k in range(XNew.shape[1]):
        for i in range(len(XNew)):
            xn = XNew.item(k * len(XNew) + i)
            yn = YNew.item(k * len(XNew) + i)
            new_val = 0
            # berechnet für x und y Wert z
            for j in range(len(X)):
                x = X.item(j)
                y = Y.item(j)
                R = np.sqrt(((xn - x) ** 2 + (yn - y) ** 2))
                if R != 0:
                    new_val = new_val + (R ** 2 + np.log(R)) * Weights.item(j)

            re_val[k][i] = new_val

    return re_val


if __name__ == "__main__":
    # Produce random points which are to be interpolated by the thin plate spline
    nPoint = 20
    X = np.random.rand(nPoint)
    Y = np.random.rand(nPoint)
    Z = np.random.rand(nPoint)
    # Produce a regular grid for evaluation of the thin plate spline
    nGridCell = 41
    XNew = np.linspace(0.0, 1.0, nGridCell)
    YNew = np.linspace(0.0, 1.0, nGridCell)
    XNew, YNew = np.meshgrid(XNew, YNew)
    # Construct and evaluate the thin plate spline
    Weights = ComputeTPSWeights(X, Y, Z)
    ZNew = EvaluateTPSSpline(XNew, YNew, X, Y, Weights)

    # Check whether all points have been fitted correctly
    ZReconstructed = EvaluateTPSSpline(X, Y, X, Y, Weights)
    print("If the following number is nearly zero, the solution appears to be working fine.");
    print(np.linalg.norm(Z - ZReconstructed))

    # Plot the input points and the interpolated function
    Axes = pyplot.subplot(projection="3d")
    Axes.scatter3D(X, Y, Z, color="r")
    Axes.set_xlim(0.0, 1.0)
    Axes.set_ylim(0.0, 1.0)
    Axes.set_zlim(np.min(ZNew), np.max(ZNew))
    Axes.plot_wireframe(XNew, YNew, ZNew, rstride=1, cstride=1)
    pyplot.show()
