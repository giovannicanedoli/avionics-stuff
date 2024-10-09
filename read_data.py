import csv
def main(nome_file):
    # apri il csv e printa i valori
    with open(nome_file) as file:
        reader = csv.reader(file)
        # leggo l'header
        header = next(reader)
        print(f"{header[0]} {header[1]} {header[2]}")
        #printa tutto        
        for row in reader:
            state, time, pressure = row
            print(f"{state} {time} {pressure}")

if __name__ == '__main__':
    main("output.csv")
