import subprocess
import matplotlib.pyplot as plt
import numpy as np

def run_main_program(size):
    command = ['./main', str(size), str(max_threads), "-p"]
    output = subprocess.check_output(command).decode('utf-8')
    speedups = []
    for line in output.split('\n'):
        if 'Speedup' in line:
            speedups.append(float(line.split(':')[1].split('segundos')[0]))
    return speedups

def generate_graph():
    results = np.zeros((len(sizes), max_threads - 1))
    
    for i, size in enumerate(sizes):
        all_speedups = []
        for j in range(executions):
            speedups = run_main_program(size)
            all_speedups.append(speedups)
            print("size " + str(size) + " exec " + str(j))
        results[i] = np.mean(all_speedups, axis=0)
    
    plt.figure(figsize=(10, 6))
    colors = ['r', 'g', 'b']
    labels = ['Tamanho ' + size for size in sizes]
    
    for i, size in enumerate(sizes):
        plt.plot(range(2, max_threads + 1), results[i], marker='o', color=colors[i], label=labels[i])
    
    plt.xlabel('Número de Threads')
    plt.ylabel('Speedup')
    plt.legend()
    plt.grid(True)
    plt.show()

sizes = [1000, 2000, 4000]
executions = 3
max_threads = 8
generate_graph()
