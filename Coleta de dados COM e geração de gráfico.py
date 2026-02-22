import serial
import time
import matplotlib.pyplot as plt
import pandas as pd

# 1. Coleta de dados da porta serial
try:
    ser = serial.Serial('COM5', 9600, timeout=1) 
    time.sleep(2) # Arduino reseta ao abrir a porta

    dados = []
    print("Iniciando coleta...")

    # Usar 'with' garante que o arquivo feche sozinho ao sair do bloco
    with open("walker1.txt", "w") as f:
        for i in range(200):
            linha = ser.readline().decode(errors="ignore").strip()
            if linha:
                f.write(linha + "\n")
                dados.append(float(linha)) # Guarda em lista para facilitar
                print(f"Passo {i}: {linha}")
    
    ser.close() # SEMPRE feche a porta serial
    print("Coleta finalizada e porta fechada.")

except Exception as e:
    print(f"Erro na serial: {e}")

# 2. Geração de Gráficos
# Verificamos se há dados antes de plotar
if dados:
    df1 = pd.DataFrame(dados, columns=["pos"])

    plt.style.use("bmh") # Um estilo mais moderno que o 'classic'
    plt.figure(figsize=(12, 6))

    plt.plot(df1["pos"], label="Walker 2", color="red", linewidth=2)

    plt.title("Random Walker 2 - 100 Passos ", fontsize=16, fontweight="bold")
    plt.xlabel("Passos", fontsize=12)
    plt.ylabel("Posição", fontsize=12)
    
    plt.grid(True, linestyle="--", alpha=0.6)
    plt.legend()
    plt.tight_layout()
    
    print("Gerando gráfico...")
    plt.show() # Esta janela deve abrir agora
else:
    print("Nenhum dado foi coletado para gerar o gráfico.")
