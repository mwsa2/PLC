type Name = String
type Age = Int
type Person = (Name, Age)

pessoa :: Person 
pessoa = ("Marcos", 30)

name :: Person -> Name
name (n,a) = n


-- ax² + bx + c = 0
-- d = b² - 4ac
-- x = (-b +- sqrt(d))/2a


oneRoot :: Float -> Float -> Float -> Float
oneRoot a b c = (-b/2*a)

twoRoots :: Float -> Float -> Float -> (Float,Float)
twoRoots a b c = ((d - raiz), (d + raiz) )
                 where d = -b/(2.0*a) 
                       raiz = sqrt(b*b - 4.0*a*c)/(2.0*a)       

roots :: Float -> Float -> Float -> (Int,Float,Float)
roots a b c | delta < 0 = (0,0,0)
            | delta == 0 = (1, (oneRoot a b c), 0)
            | otherwise = (2, raiz1, raiz2)
             where delta = b*b - 4*a*c 
                   (raiz1, raiz2) = twoRoots a b c



