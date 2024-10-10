import csv
import matplotlib.pyplot as plt
import numpy as np
from typing import List

def cleanup(namefile: str) -> None:
    # Leggo i dati dal CSV
    with open(namefile) as f:
        reader = csv.reader(f)
        data = list(reader)

    # Converti i dati in formato numerico (supponendo che i dati siano in formato stringa)
    data = [[float(x), float(y)] for x, y in data]
    data = np.array(data)
    print(data)

    len_data = len(data)
    results: List[str] = []  # Lista per memorizzare i risultati

    for i in range(1, len_data):
        # Controlla la differenza di esattamente ±7000 Pascal
        if (data[i][1] - data[i-1][1]) not in range(-5000, 5000):
            data[i][1] = data[i-1][1]

        delta: float = data[i][0]
        pressure: float = data[i][1]
        result: str = stateTick(delta, pressure)
        results.append(result)  # Memorizza il risultato per uso o analisi futura

        # Paracadute
        pression: float = pressure
        initial: float = 81192
        # Calcolo la quota (considero g = 10 e la densità dell'aria 1)
        # Utilizzo la legge di Stevino
        quota: int = int((pression - initial) / 10)
        if quota == 400:
            print("secondo paracadute")

        # Scrivo in output per far funzionare gnuplot
        print(f"{data[i][0]} {data[i][1]}")

    x_vals = [row[0] for row in data]
    y_vals = [row[1] for row in data]

    plt.plot(x_vals, y_vals)
    plt.xlabel('Delta (Valori X)')
    plt.ylabel('Pressione (Valori Y)')
    plt.title('Grafico')
    plt.grid(True)
    plt.show()

def stateTick(delta: int, pressure: float) -> str:
    # Differenzia gli stati in base agli intervalli specificati
    if 46478 <= delta < 252413:
        return "Su rampa"
    elif 252413 <= delta < 262424:
        return "Lancio"
    elif 262424 <= delta < 273865:
        return "Apogeo"
    elif 378262 <= delta < 800000:
        return "A terra"
    else:
        # Non è specificato il nome dell'evento in questo caso
        return ""

    # Azione specifica all'apogeo
    if delta == 268159:
        return "Paracadute azionato"

# Funzione principale per eseguire il processo di pulizia e test
if __name__ == '__main__':
    cleanup('data.csv')
