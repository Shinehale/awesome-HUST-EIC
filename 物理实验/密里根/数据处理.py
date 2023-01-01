import math

R = list(map(int,input().split()))
n = R[0]
R1 = list(map(float,input().split()))
R2 = list(map(float,input().split()))
for i in range(n):
    t = R1[i]
    U = R2[i]
    yita = 1.83*pow(10,-5)
    l = 1.5*pow(10,-3)
    v = l / t
    tho = 981
    g = 9.795
    pi = 3.1415926
    b = 6.17 * pow(10,-6)
    p = 76.0
    d = 5*pow(10,-3)
    a = math.sqrt( 9 * yita * v / ( 2 * tho * g ))
    q = 18*pi/math.sqrt(2*tho*g)*pow( ( yita*l / (t * (1 + b/(p*a))) ) , 1.5 )* d / U
    e = 1.60*pow(10,-19)
    print(round(q/e),q)


