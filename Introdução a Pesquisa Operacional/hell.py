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
                dist = round(math.sqrt((cities[j][1] - cities[i][1]) ** 2 + (cities[j][2] - cities[i][2]) ** 2), 0)
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
    input_file = r".\Inst\instancia.ttp"
    tsp_output_file = 'tsp_data.dat'
    kp_output_file = 'kp_data.dat'

    tsp_data, kp_data = read_ttp_instance(input_file)
    distances = calculate_distances(tsp_data)

    tsp_header = ""
    tsp_footer = ";end;"
    kp_header = ""
    kp_footer = "end;"

    tsp_data_ampl = []
    line = "param c: "
    for i in range(len(distances)):
        line = line + str(i+1) + " "
    line = line + ":="
    tsp_data_ampl.append(line)
    line = ""
    for i in range(len(distances)):
        line = line + str(i+1) + " "
        for j in range(len(distances)):
            if (i == j): line = line + str(10000000.0) + " "
            else: line = line + str(distances[i][j]) + " "
        tsp_data_ampl.append(line)
        line = ""

    kp_data_ampl = []
    kp_data_ampl.append("param: profit := ")
    for line in kp_data:
        index, profit, weight, node = line.split()
        kp_data_ampl.append(f"{index} {profit}")
    kp_data_ampl.append(";")
    kp_data_ampl.append("param: weight := ")
    for line in kp_data:
        index, profit, weight, node = line.split()
        kp_data_ampl.append(f"{index} {weight}")
    kp_data_ampl.append(";")

    write_ampl_file(tsp_output_file, tsp_data_ampl, tsp_header, tsp_footer)
    write_ampl_file(kp_output_file, kp_data_ampl, kp_header, kp_footer)

if __name__ == "__main__":
    main()
