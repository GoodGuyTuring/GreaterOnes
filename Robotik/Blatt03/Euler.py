import numpy as np

R = np.array([[1/np.sqrt(2),0,1/np.sqrt(2)],[-1/2,1/np.sqrt(2),1/2],[-1/2,-1/np.sqrt(2),1/2]])
print(R)
T1 = -1/np.sin(R[2,0])
T2 = np.pi - T1
print(T1)
