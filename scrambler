#GERADOR DE SCRAMBLE 3X3 RUBIKS CUBE
import random
#criando o vetor de strings que vai conter os movimentos possiveismovimentos = ["R ", "R'", "R2","L ", "L'", "L2","U ", "U'", "U2","B ", "B'", "B2","F ", "F'", "F2","D ", "D'", "D2"]
def verificador_mov(lista_movimentos,atual, anterior):
    i = 0;    while(i == 0):
        if(lista_movimentos[atual] == lista_movimentos[anterior]):            lista_movimentos[atual] = random.choice(movimentos)
                    break
    






lista_movimentos = []lista_movimentos.append(random.choice(movimentos))
#escolhe um movimento aleatorio entre os possiveis e printa ele na tela.
for i in range(1,20):    lista_movimentos.append(random.choice(movimentos))
    if(i == 1):         verificador_mov(lista_movimentos,i, i-1)
    else:        if(lista_movimentos[i] == "R " or lista_movimentos[i] == "R2" or lista_movimentos[i] == "R'"):
            if(lista_movimentos[i-1] == "L " or lista_movimentos[i-1] == "L2" or lista_movimentos[i-1] == "L'"):                verificador_mov(lista_movimentos,i, i-2)
            else:                verificador_mov(lista_movimentos,i, i-1)
                        elif(lista_movimentos[i] == "L " or lista_movimentos[i] == "L2" or lista_movimentos[i] == "L'"):
            if(lista_movimentos[i-1] == "R " or lista_movimentos[i-1] == "R2" or lista_movimentos[i-1] == "R'"):                verificador_mov(lista_movimentos,i, i-2)
            else:                verificador_mov(lista_movimentos,i, i-1)
                        elif(lista_movimentos[i] == "U " or lista_movimentos[i] == "U2" or lista_movimentos[i] == "U'"):
            if(lista_movimentos[i-1] == "D " or lista_movimentos[i-1] == "D2" or lista_movimentos[i-1] == "D'"):                verificador_mov(lista_movimentos,i, i-2)
            else:                verificador_mov(lista_movimentos,i, i-1)
                        elif(lista_movimentos[i] == "D " or lista_movimentos[i] == "D2" or lista_movimentos[i] == "D'"):
            if(lista_movimentos[i-1] == "U " or lista_movimentos[i-1] == "U2" or lista_movimentos[i-1] == "U'"):                verificador_mov(lista_movimentos, i, i-2)
            else:                verificador_mov(lista_movimentos,i, i-1)
                        elif(lista_movimentos[i] == "F " or lista_movimentos[i] == "F2" or lista_movimentos[i] == "F'"):
            if(lista_movimentos[i-1] == "B " or lista_movimentos[i-1] == "B2" or lista_movimentos[i-1] == "B'"):                verificador_mov(lista_movimentos,i, i-2)
            else:                verificador_mov(lista_movimentos,i, i-1)
                        elif(lista_movimentos[i] == "B " or lista_movimentos[i] == "B2" or lista_movimentos[i] == "B'"):
            if(lista_movimentos[i-1] == "F " or lista_movimentos[i-1] == "F2" or lista_movimentos[i-1] == "F'"):                verificador_mov(lista_movimentos,i, i-2)
            else:                verificador_mov(lista_movimentos,i, i-1)
    for i in range(20):
    print(lista_movimentos[i], end = " ")
