f l = product $ zipWith (^) l [1..]
 
fmin n = floor $ f [ i*2/(n+1) | i<-[1..n]]
 
problem_190 = sum $ map fmin [2..15]
