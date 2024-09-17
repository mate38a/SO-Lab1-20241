#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <cstring>

/*Luis Mateo Ochoa Agudelo
Juan Sebastian Ortiz Tangarife*/

// Función para verificar si dos archivos son el mismo (hardlinked)
bool are_files_same(const std::string& file1, const std::string& file2) {
    struct stat stat1, stat2;

    // Obtener información del primer archivo
    if (stat(file1.c_str(), &stat1) != 0) {
        std::cerr << "Error al obtener información del archivo " << file1 << std::endl;
        exit(1);
    }

    // Obtener información del segundo archivo
    if (stat(file2.c_str(), &stat2) != 0) {
        std::cerr << "Error al obtener información del archivo " << file2 << std::endl;
        exit(1);
    }

    // Comparar el número de dispositivo e inodo
    return (stat1.st_dev == stat2.st_dev && stat1.st_ino == stat2.st_ino);
}

int main(int argc, char *argv[]) {
    std::istream* input_stream = &std::cin;
    std::ostream* output_stream = &std::cout;
    std::vector<std::string> lines;
    std::string line;
    std::ifstream input_file;
    std::ofstream output_file;

    // Manejo de argumentos
    if (argc > 3) {
        std::cerr << "usage: reverse <input> <output>" << std::endl;
        exit(1);
    }

    if (argc >= 2) {
        input_file.open(argv[1]);
        if (!input_file.is_open()) {
            std::cerr << "reverse: cannot open file '" << argv[1] << "'" << std::endl;
            exit(1);
        }
        input_stream = &input_file;
    }

    if (argc == 3) {
        output_file.open(argv[2]);
        if (!output_file.is_open()) {
            std::cerr << "reverse: cannot open file '" << argv[2] << "'" << std::endl;
            exit(1);
        }
        output_stream = &output_file;

        if (std::string(argv[1]) == std::string(argv[2]) || are_files_same(argv[1], argv[2])) {
            std::cerr << "reverse: input and output file must differ" << std::endl;
            exit(1);
        }
    }

    // Leer el archivo de entrada línea por línea y agregar al vector
    while (std::getline(*input_stream, line)) {
        lines.push_back(line);
    }

    // Imprimir las líneas en orden inverso
    for (auto it = lines.rbegin(); it != lines.rend(); ++it) {
        *output_stream << *it << std::endl;
    }

    // Los streams se cerrarán automáticamente al salir del scope

    return 0;
}

