import math

if __name__=="__main__":
    x,y=[],[]
    x.append(9)
    y.append(2)
    for i in range(1,20):
        k_1,k_2=x[0]*x[i-1]+20*y[0]*y[i-1],x[0]*y[i-1]+y[0]*x[i-1]
        x.append(k_1)
        y.append(k_2)
    #print x
    #print y
 
    p1,q1,p2,q2,p3,q3=[14],[1],[16],[2],[26],[5]
    p1.append
    for i in range(20):
        k_1,k_2,k_3,k_4=p1[0]*x[i]+20*q1[0]*y[i],p1[0]*y[i]+q1[0]*x[i],p1[0]*x[i]-20*q1[0]*y[i],p1[0]*y[i]-q1[0]*x[i]
        p1.append(k_1)
        p1.append(k_3)
        q1.append(k_2)
        q1.append(k_4)
        k_1,k_2,k_3,k_4=p2[0]*x[i]+20*q2[0]*y[i],p2[0]*y[i]+q2[0]*x[i],p2[0]*x[i]-20*q2[0]*y[i],p2[0]*y[i]-q2[0]*x[i]
        p2.append(k_1)
        p2.append(k_3)
        q2.append(k_2)
        q2.append(k_4)
        k_1,k_2,k_3,k_4=p3[0]*x[i]+20*q3[0]*y[i],p3[0]*y[i]+q3[0]*x[i],p3[0]*x[i]-20*q3[0]*y[i],p3[0]*y[i]-q3[0]*x[i]
        p3.append(k_1)
        p3.append(k_3)
        q3.append(k_2)
        q3.append(k_4)
 
    T=p1
    T[len(T):]=p2
    T[len(T):]=p3
    T.sort();
    #print T
    ret,sum,cnt=0,0,0
    while(True and ret<len(T)):
        if((T[ret]-14)%10==0):
            cnt+=1
            print cnt,' ',(T[ret]-14)/10;
            sum+=((T[ret]-14)/10)
        if(cnt==31):
            print sum;
            break;
        ret+=1
