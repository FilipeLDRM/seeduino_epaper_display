#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 10000 // Tamanho máximo do array
#define MAX_FILES 100


void clearImageDataFile(const char *filename) {
    FILE *file_ptr = fopen(filename, "w");
    if (file_ptr == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }

    fprintf(file_ptr, "/* Conteúdo removido */");

    fclose(file_ptr);
}

void addHeaderToImageDataFile(const char *filename, const char *header) {
    FILE *file_ptr = fopen(filename, "r");
    if (file_ptr == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }

    // Lê o conteúdo existente do arquivo
    char *buffer = (char *)malloc(MAX_LENGTH * sizeof(char));
    size_t length = 0;
    char c;

    while ((c = fgetc(file_ptr)) != EOF && length < MAX_LENGTH) {
        buffer[length++] = c;
    }
    buffer[length] = '\0';

    fclose(file_ptr);

    // Cria um arquivo temporário para escrever o conteúdo atualizado
    FILE *temp_file_ptr = fopen("tempfile.tmp", "w");
    if (temp_file_ptr == NULL) {
        printf("Erro ao criar o arquivo temporário\n");
        exit(1);
    }

    // Escreve o cabeçalho fornecido no novo arquivo temporário
    fprintf(temp_file_ptr, "%s\n\n%s", header, buffer);

    fclose(temp_file_ptr);

    // Remove o arquivo original e renomeia o arquivo temporário para o nome original
    remove(filename);
    rename("tempfile.tmp", filename);

    free(buffer);
}

int main() {
    // Limpa o conteúdo existente no arquivo C:\\Users\\anton\\Desktop\\Seeeduino_EBP\\Codigos\\epd2in13_V4\\imagedata.cpp
    clearImageDataFile("C:\\Users\\anton\\Desktop\\Seeeduino_EBP\\Codigos\\epd2in13_V4\\imagedata.cpp");

    // Cabeçalho a ser adicionado
    const char *header = "/*  Copyright (C) Waveshare     September 5 2017\n"
                         " *\n"
                         " * Permission is hereby granted, free of charge, to any person obtaining a copy\n"
                         " * of this software and associated documnetation files (the \"Software\"), to deal\n"
                         " * in the Software without restriction, including without limitation the rights\n"
                         " * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
                         " * copies of the Software, and to permit persons to  whom the Software is\n"
                         " * furished to do so, subject to the following conditions:\n"
                         " *\n"
                         " * The above copyright notice and this permission notice shall be included in\n"
                         " * all copies or substantial portions of the Software.\n"
                         " *\n"
                         " * THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
                         " * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
                         " * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
                         " * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
                         " * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
                         " * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\n"
                         " * THE SOFTWARE.\n"
                         " */\n\n"
                         "#include \"imagedata.h\"\n"
                         "#include <avr/pgmspace.h>\n";

    // Adiciona o cabeçalho ao arquivo C:\\Users\\anton\\Desktop\\Seeeduino_EBP\\Codigos\\epd2in13_V4\\imagedata.cpp
    addHeaderToImageDataFile("C:\\Users\\anton\\Desktop\\Seeeduino_EBP\\Codigos\\epd2in13_V4\\imagedata.cpp", header);

    // Nomes dos arquivos .c a serem processados
    char *fileNames[MAX_FILES]; // Adicione mais nomes conforme necessário

    for (int i = 0; i < MAX_FILES; i++) {
        // Aloca espaço suficiente para o nome do arquivo, incluindo o caractere nulo '\0'
        fileNames[i] = (char *)malloc(5 * sizeof(char)); // "x.c" tem 4 caracteres + 1 do '\0'
        sprintf(fileNames[i], "%d.c", i + 1); // Cria o nome do arquivo baseado no número
    }

    FILE *file_cpp_ptr;
    FILE *file_c_ptr;

    file_cpp_ptr = fopen("C:\\Users\\anton\\Desktop\\Seeeduino_EBP\\Codigos\\epd2in13_V4\\imagedata.cpp", "a"); // Abre o arquivo .cpp no modo de anexação

    if (file_cpp_ptr == NULL) {
        printf("Erro ao abrir o arquivo C:\\Users\\anton\\Desktop\\Seeeduino_EBP\\Codigos\\epd2in13_V4\\imagedata.cpp\n");
        return 1;
    }

    // Itera através dos arquivos .c
    for (int i = 0; i < sizeof(fileNames) / sizeof(fileNames[0]); i++) {
        file_c_ptr = fopen(fileNames[i], "r"); // Abre o arquivo .c para leitura

        if (file_c_ptr == NULL) {
            printf("Erro ao abrir o arquivo %s\n", fileNames[i]);
            break;
        }

        // Lê o conteúdo do arquivo .c
        fseek(file_c_ptr, 0, SEEK_END);
        long file_size = ftell(file_c_ptr);
        fseek(file_c_ptr, 0, SEEK_SET);

        char *buffer = (char *)malloc(file_size * sizeof(char));
        fread(buffer, sizeof(char), file_size, file_c_ptr);

        // Procura pelo início e fim do conteúdo hexadecimal do array
        char *start = strstr(buffer, "{");
        char *end = strstr(buffer, "};");

        if (start != NULL && end != NULL) {
            start++; // Avança além do '{'

            // Escreve no arquivo .cpp, mantendo a formatação desejada
            fprintf(file_cpp_ptr, "\n\nconst unsigned char IMAGE_DATA%d[] PROGMEM = {", i + 1);
            fwrite(start, sizeof(char), end - start, file_cpp_ptr); // Remove 1 byte do tamanho (vírgula extra)
            fprintf(file_cpp_ptr, "};");
        }

        // Libera a memória alocada e fecha o arquivo .c
        free(buffer);
        fclose(file_c_ptr);
    }
    // Liberar a memória alocada
    for (int i = 0; i < MAX_FILES; i++) {
        free(fileNames[i]);
    }
    fclose(file_cpp_ptr);

    return 0;
}
