import Graphics.Win32 (bST_CHECKED)
import System.Directory.Internal.Prelude (permissionErrorType)
--compreensao de listas
--[x*x | x <- [1..10]]

-- filtar elementos 
--[x | x <- [1..100], x `mod` 7 == 0]

-- simulacao do sistema de emprestimos de livros
type Pessoa = String
type Livro = String
type BancoDados = [(Pessoa, Livro)]

baseExemplo :: BancoDados
baseExemplo = [("marcos","trihexa"), ("wanderson", "spfc"), ("marcos","trihexa2008")]

livros :: BancoDados -> Pessoa -> [Livro]
livros bd p = [l | (pp,l) <- bd, pp == p ]

emprestimos :: BancoDados -> Livro -> [Pessoa]
emprestimos bd l = [p | (p, ll) <- bd, ll == l]

emprestado :: BancoDados -> Livro -> Bool
emprestado bd l = emprestimos bd l /= []

qtdEmprestimos :: BancoDados -> Pessoa -> Int
qtdEmprestimos bd p = length(livros bd p)

emprestar :: BancoDados -> Pessoa -> Livro -> BancoDados
-- par nao encontrado
emprestar [] pessoa livro = [(pessoa, livro)]
emprestar ((p,l):as) pessoa livro
    | p == pessoa && l == livro = (p,l):as 
    | otherwise = (p,l):emprestar as pessoa livro 

--devolver :: BancoDados -> Pessoa -> Livro -> BancoDados
