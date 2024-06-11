import serial
import csv
import time

# Configurar a porta serial
ser = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # Aguarda a inicialização do Arduino

# Nome do arquivo CSV
csv_file = 'Arduino_to_Excel.csv'

# Cria ou abre o arquivo CSV e adiciona o cabeçalho
with open(csv_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow([ "Data1", "Data2"])

try:
    while True:
        # Ler dados da porta serial
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').rstrip()
            if data:
                # Processar os dados (supondo que sejam separados por vírgula)
                data_split = data.split(',')
                row = data_split

                # Escrever dados no arquivo CSV
                with open(csv_file, mode='a', newline='') as file:
                    writer = csv.writer(file)
                    writer.writerow(row)

                print(f"Dados recebidos: {data}")

except KeyboardInterrupt:
    # Fechar a porta serial ao finalizar o programa
    print("Programa finalizado.")
    ser.close()

except Exception as e:
    print(f"Ocorreu um erro: {e}")
    ser.close()
