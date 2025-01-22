def write_combinations_to_file(filename):
    with open(filename, 'w') as file:
        for i in range(1, 52):
            for j in range(1, 52):
                file.write(f'x[{i},{j}]\n')

# Use o nome do arquivo desejado
write_combinations_to_file('bounds.txt')
