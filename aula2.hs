--definicoes locais

sumSquare :: Int -> Int -> Int
sumSquare x y = sqrX + sqrY + quadradoSoma x y
    where sqrX = x * x
          sqrY = y * y
          quadradoSoma a b = (a+b)*(a+b) 