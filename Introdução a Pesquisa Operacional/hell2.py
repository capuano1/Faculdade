import math

def read_ttp_instance(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    tsp_data = []
    kp_data = []
    tsp_section = False
    kp_section = False

    for line in lines:
        if line.startswith("NODE_COORD_SECTION"):
            tsp_section = True
            kp_section = False
            continue
        elif line.startswith("ITEMS SECTION"):
            tsp_section = False
            kp_section = True
            continue

        if tsp_section:
            tsp_data.append(line.strip())
        elif kp_section:
            kp_data.append(line.strip())

    return tsp_data, kp_data

def calculate_distances(tsp_data):
    num_cities = len(tsp_data)
    distances = [[0] * num_cities for _ in range(num_cities)]

    cities = []
    for line in tsp_data:
        index, x, y = map(int, line.split())
        cities.append((index, x, y))

    for i in range(num_cities):
        for j in range(num_cities):
            if i != j:
                dist = math.ceil(math.sqrt((cities[j][1] - cities[i][1]) ** 2 + (cities[j][2] - cities[i][2]) ** 2))
                distances[i][j] = dist
                distances[j][i] = dist

    return distances

def write_ampl_file(file_path, data, header, footer):
    with open(file_path, 'w') as file:
        file.write(header + '\n')
        for line in data:
            file.write(line + '\n')
        file.write(footer + '\n')

def main():
    input_file = '.\Inst\instancia.ttp'
    tsp_output_file = 'tsp_data.dat'
    kp_output_file = 'kp_data.dat'

    tsp_data, kp_data = read_ttp_instance(input_file)
    distances = calculate_distances(tsp_data)

    tsp_header = "set N := 1..51;\n"
    tsp_footer = ";\nparam n := 51;\nend;"
    kp_header = "set ITEMS := 1..50;\nparam profit :=\n"
    kp_footer = ";\nparam capacity := 4029;\nend;"

    tsp_data_ampl = []
    for i in range(len(distances)):
        for j in range(len(distances)):
            tsp_data_ampl.append(f"param c[{i}, {j}] = {distances[i][j]};")
        

    kp_data_ampl = []
    for line in kp_data:
        index, profit, weight, node = line.split()
        kp_data_ampl.append(f"{index} {profit} {weight}")

    write_ampl_file(tsp_output_file, tsp_data_ampl, tsp_header, tsp_footer)
    write_ampl_file(kp_output_file, kp_data_ampl, kp_header, kp_footer)

if __name__ == "__main__":
    main()
