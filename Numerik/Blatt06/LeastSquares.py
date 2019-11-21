import numpy as np


def QR(A):
    """Given a matrix A with full column rank this function uses the classical 
       Gram-Schmidt algorithm to compute a QR decomposition. It returns a tuple 
       (Q,R) of np.matrix objects with Q having shape identical to A and Q*R=A."""
    A = np.asarray(A)
    Q = np.zeros(A.shape)
    qi = np.array(0)
    for i in range(A.shape[1]):
        if i == 0:
            qi = np.copy(A[:, 0])
            qi /= np.linalg.norm(qi)
            Q[:, 0] = np.copy(qi)
            continue

        qi = np.copy(A[:, i])
        for j in range(i):
            qi -= np.dot(A[:, i], Q[:, j]) * Q[:, j]

        qi /= np.linalg.norm(qi)
        Q[:, i] = np.copy(qi)

    R = Q.transpose() @ A
    R = np.around(R,decimals=14)

    return Q, R
    

def BackSubstitution(R,y):
    """Given a square upper triangular matrix R and a vector y of same size this 
       function solves R*x=y using backward substitution and returns x."""
    R = np.asarray(R)
    y = np.asarray(y)
    n = y.size
    x = np.zeros((1, n))
    for i in range(n-1, -1,-1):
        x[0,i] = np.copy(y[i])
        tmp_sum = 0
        for j in range(i+1, n):
            tmp_sum += R[i, j] * x[0,j]
        x[0,i] -= tmp_sum
        x[0,i] /= R[i, i]

    a = np.linalg.solve(R, y)
    res = x.transpose()
    return res
    

def LeastSquares(A,b):
    """Given a matrix A and a vector b this function solves the least squares 
       problem of minimizing |A*x-b| and returns the optimal x."""
    Q, R = QR(A)
    b = np.asarray(b)
    #T = np.abs((Q@R)-A)
    y = Q.transpose().conjugate() @ b
    res = BackSubstitution(R, y)
    return res
    

if(__name__=="__main__"):
    # Try the QR decomposition
    A=np.matrix([
        [1.0,1.0,1.0],
        [1.0,2.0,3.0],
        [1.0,4.0,9.0],
        [1.0,8.0,27.0]
    ]);
    Q,R=QR(A);
    print("If the following numbers are nearly zero, QR seems to be working.");
    print(np.linalg.norm(Q@R-A));
    print(np.linalg.norm(Q.transpose().conjugate()@Q-np.eye(3)));
    # Try solving a least squares system
    b=np.matrix([1.0,2.0,3.0,4.0]).T;
    x=LeastSquares(A,b);
    print("If the following number is nearly zero, least squares solving seems to be working.");
    print(np.linalg.norm(x-np.linalg.lstsq(A,b)[0]));
