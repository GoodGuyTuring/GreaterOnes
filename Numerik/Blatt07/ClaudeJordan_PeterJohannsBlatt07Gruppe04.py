#ClaudeJordan_PeterJohanns Blatt07 Gruppe04

import numpy as np
from numpy import linalg as la


def sign(x):
    if x >= 0:
        return 1
    return -1


def Householder(A):
    """Computes a QR-decomposition of the given matrix using the Householder 
       algorithm.
      return A pair (NormalList,R) where NormalList is a list of Householder
              normal vectors and R is an upper triangular matrix shaped like A.
      sa ComputeQ """

    B = np.copy(A)
    NormalList = []

    for k in range(B.shape[1]):

        x = np.copy(B[k:, [k]]) #k-te spalte
        e1 = np.zeros((x.size, 1))
        e1[0, 0] = 1

        vk = sign(x[0,0]) * np.linalg.norm(x) * e1 + x
        vk /= np.linalg.norm(vk)
        NormalList.append(np.copy(vk))

        B[k:, k:] -= 2*vk @ vk.conjugate().transpose() @ B[k:, k:]

    return NormalList, B


def ComputeQ(NormalList):
    """Given a normal list such as the one returned by householder() this 
       function computes the corresponding orthogonal matrix."""
    Qbase = np.identity(NormalList[0].shape[0])
    for index, vk in enumerate(NormalList):
        Qk = np.identity(NormalList[0].shape[0])
        Hk = np.identity(vk.shape[0])
        Hk -= 2 * (vk @ vk.conjugate().transpose()) / np.inner(vk.transpose(), vk.transpose())
        Qk[index:, index:] = np.copy(Hk)
        Qbase = Qk @ Qbase

    return Qbase.transpose()

if __name__=="__main__":
    A=np.random.rand(4,3);
    NormalList,R=Householder(A);
    Q=ComputeQ(NormalList);#
    print("The following matrix should be upper triangular:");
    print(R);
    print("If the solution consitutes a decomposition, the following is near zero:");
    print(la.norm(A-Q@ R));
    print("If Q is unitary, the following is near zero:");
    print(la.norm(np.dot(Q.T,Q)-np.eye(Q.shape[0])));

    ##A = np.array([[-2.,-2.,-2.],[-2,-1,-1], [1,0,-1]])
    ##NormalList, R = Householder(A)
    ##print("R",R)
    ##Q = ComputeQ(NormalList)
    ##print("Q", Q)
    ##print("QR", Q@R)
