--definicoes locais

sumSquare :: Int -> Int -> Int
sumSquare x y = sqrX + sqrY + quadradoSoma x y
    where sqrX = x * x
          sqrY = y * y
          quadradoSoma a b = (a+b)*(a+b) 


addEspacos :: Int -> String
addEspacos 0 = ""
addEspacos n = " "++addEspacos(n-1)

paraDireita :: Int -> String -> String
paraDireita n str = addEspacos n ++ str



imprimeTabela :: Int -> IO()
imprimeTabela n = putStr (cabecalho 
                           ++ imprimeSemanas n
                           ++ imprimeTotal n ++ "\n"
                           ++ imprimeMedia n ++ "\n" )

cabecalho :: String 
cabecalho = "Semana  Venda\n"

imprimeSemanas :: Int -> String
imprimeSemanas 0 = imprimeSemana 0
imprimeSemanas x = imprimeSemanas (x-1) ++ imprimeSemana x

imprimeSemana :: Int -> String
imprimeSemana n = paraDireita 2 (show n) ++
                  paraDireita (8-ajuste) (show (vendas n)) ++
                  "\n"
    where
      ajuste = length (show (vendas n))

imprimeTotal :: Int -> String
imprimeTotal n = "Total   " ++ show (totalVendas n)



vendas :: Int -> Int
vendas 0 = 30
vendas 1 = 40
vendas 2 = 90
vendas 3 = 110
vendas 4 = 30
vendas 5 = 99
vendas other = 0

vendasNulas :: Int -> Bool
vendasNulas n = (vendas n == 0)

totalVendas :: Int -> Int
totalVendas n | n == 0 = vendas 0
              | otherwise = totalVendas (n-1) + vendas n

imprimeMedia :: Int -> String
imprimeMedia n = "media " ++ show(fromIntegral(totalVendas n) / fromIntegral(n))
