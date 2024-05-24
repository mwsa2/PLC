square :: Int -> Int 
square x = x * x


allEqual :: Int -> Int -> Int -> Bool
allEqual a b c = (a == b) && (b == c)

all4Equal :: Int -> Int -> Int -> Int -> Bool
all4Equal a b c d = allEqual a b c && d == a 

--EqualCount 

maxi :: Int -> Int -> Int
maxi a b | a >= b = a
         | otherwise = b  

vendas :: Int -> Int
vendas 0 = 10
vendas 1 = 20
vendas 2 = 30


totalVendas :: Int -> Int
totalVendas 0 = vendas 0
totalVendas n = vendas n + totalVendas (n-1)

fat :: Int -> Int
fat 1 = 1
fat a = a * fat (a-1)

imc :: Float -> Float -> Float
imc p a = p/(a*a) 
