--listas

tam :: [t] -> Int
tam [] = 0
tam (a:as) = 1 + tam as

--casamento de padroes
somarLista :: [Int] -> Int
somarLista [] = 0
somarLista (a:as) = a + somarLista as

dobrarLista :: [Int] -> [Int]
dobrarLista [] = []
dobrarLista (a:as) = 2*a : dobrarLista as

member :: [Int] -> Int -> Bool
member [] n = False
member (a:as) n | a == n = True
                | otherwise = member as n  

digits :: String -> String
-- dica: use a funcao member
digits [] = []
digits (a:as) | a >= '0' && a <= '9' = a : digits as
              | otherwise = digits as
-- digits (a:as) | member ['0'..'9'] a = a : digits

sumPairs :: [Int] -> [Int] -> [Int]
sumPairs [] [] = []
sumPairs (a:as) (b:bs) = a + b : sumPairs as bs

somarPares :: [(Int,Int)] -> [Int]
-- exemplo: somarPares [(1,2),(2,4)] ---> [3,6]
somarPares [] = []
somarPares ((x,y):pares) = x+y : somarPares pares

maiorLista :: [Int] -> Int
maiorLista [] = minBound :: Int
maiorLista [x] = x
maiorLista (x:xs) | x > maiorLista xs = x
                  | otherwise = maiorLista xs