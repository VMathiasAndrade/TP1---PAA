import random
import os

def gerar_arquivo_mapa(
    altura: int,
    largura: int,
    num_pecas: int,
    durabilidade_base: tuple = (30, 60),
    decremento_base: tuple = (3, 7),
    acrescimo_base: tuple = (10, 25),
    nome_arquivo: str = "mapa_gerado.txt"
):
    """
    Gera um arquivo de mapa de acordo com a especificação do trabalho,
    garantindo que o mapa tenha um caminho conectando todos os pontos.
    """
    if altura % 2 == 0: altura += 1
    if largura % 2 == 0: largura += 1

    # 1. Geração do Labirinto (Randomized DFS)
    grid = [['.' for _ in range(largura)] for _ in range(altura)]
    stack = [(1, 1)]
    grid[1][1] = ' ' # Caminho temporário
    
    while stack:
        (cx, cy) = stack[-1]
        vizinhos = []
        for dx, dy in [(0, 2), (0, -2), (2, 0), (-2, 0)]:
            nx, ny = cx + dx, cy + dy
            if 0 < nx < altura and 0 < ny < largura and grid[nx][ny] == '.':
                vizinhos.append((nx, ny))
        
        if vizinhos:
            nx, ny = random.choice(vizinhos)
            # Remove a parede entre a célula atual e a vizinha
            grid[cx + (nx - cx) // 2][cy + (ny - cy) // 2] = ' '
            grid[nx][ny] = ' '
            stack.append((nx, ny))
        else:
            stack.pop()

    # 2. Definir tipos de caminho ('-', '|', '+') e coletar posições válidas
    posicoes_caminho = []
    for r in range(altura):
        for c in range(largura):
            if grid[r][c] == ' ':
                posicoes_caminho.append((r, c))
                
                con_n = r > 0 and grid[r - 1][c] == ' '
                con_s = r < altura - 1 and grid[r + 1][c] == ' '
                con_w = c > 0 and grid[r][c - 1] == ' '
                con_e = c < largura - 1 and grid[r][c + 1] == ' '
                
                vertical = con_n or con_s
                horizontal = con_w or con_e
                
                if vertical and horizontal:
                    grid[r][c] = '+'
                elif vertical:
                    grid[r][c] = '|'
                else: # Horizontal ou beco sem saída
                    grid[r][c] = '-'
    
    # 3. Posicionar 'X', 'F' e 'P's
    if len(posicoes_caminho) < num_pecas + 2:
        raise ValueError("Mapa muito pequeno para o número de peças especificado.")
        
    random.shuffle(posicoes_caminho)
    
    # Posição Inicial 'X'
    x_r, x_c = posicoes_caminho.pop()
    grid[x_r][x_c] = 'X'
    
    # Destino Final 'F'
    f_r, f_c = posicoes_caminho.pop()
    grid[f_r][f_c] = 'F'
    
    # Peças 'P'
    for _ in range(num_pecas):
        p_r, p_c = posicoes_caminho.pop()
        grid[p_r][p_c] = 'P'
        
    # 4. Escrever no arquivo
    try:
        with open(nome_arquivo, 'w') as f:
            # Linha 1: D, D', A
            D = random.randint(*durabilidade_base)
            D_prime = random.randint(*decremento_base)
            A = random.randint(*acrescimo_base)
            f.write(f"{D} {D_prime} {A}\n")
            
            # Linha 2: Altura e Largura
            f.write(f"{altura} {largura}\n")
            
            # Grid
            for row in grid:
                f.write("".join(row) + "\n")
        
        print(f"Arquivo '{nome_arquivo}' gerado com sucesso!")
        print(f"Dimensões: {altura}x{largura}, Peças: {num_pecas}")
        print(f"Parâmetros: D={D}, D'={D_prime}, A={A}")

    except IOError as e:
        print(f"Erro ao escrever o arquivo: {e}")


# --- Exemplo de Uso ---
if __name__ == "__main__":
    print("Gerando um mapa de exemplo...")
    gerar_arquivo_mapa(
        altura=9,
        largura=15,
        num_pecas=5,
        nome_arquivo="mapa1.txt"
    )
    
    print("\nGerando um mapa maior e mais difícil...")
    gerar_arquivo_mapa(
        altura=15,
        largura=31,
        num_pecas=8,
        durabilidade_base=(40, 50), # Mais apertado
        decremento_base=(5, 5),     # Consistente
        acrescimo_base=(10, 15),    # Menos recompensador
        nome_arquivo="mapa_dificil.txt"
    )