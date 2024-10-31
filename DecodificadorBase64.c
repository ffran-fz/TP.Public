#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tabla Base64
static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Función para verificar si un carácter es válido en Base64
int es_base64(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '+' || c == '/';
}

// Función para decodificar Base64
unsigned char* decodificar_base64(const char* input, int len, int* out_len) {
    int i = 0, j = 0, en = 0;
    unsigned char arr_3[3], arr_4[4];
    unsigned char* output = (unsigned char*)malloc(len * 3 / 4);  // Asignar memoria

    while (len-- && (input[en] != '=') && es_base64(input[en])) {
        arr_4[i++] = input[en++];
        if (i == 4) {
            for (i = 0; i < 4; i++)
                arr_4[i] = strchr(base64_chars, arr_4[i]) - base64_chars;

            arr_3[0] = (arr_4[0] << 2) + ((arr_4[1] & 0x30) >> 4);
            arr_3[1] = ((arr_4[1] & 0xf) << 4) + ((arr_4[2] & 0x3c) >> 2);
            arr_3[2] = ((arr_4[2] & 0x3) << 6) + arr_4[3];

            for (i = 0; i < 3; i++)
                output[j++] = arr_3[i];
            i = 0;
        }
    }

    if (i) {
        for (int k = i; k < 4; k++)
            arr_4[k] = 0;

        for (int k = 0; k < 4; k++)
            arr_4[k] = strchr(base64_chars, arr_4[k]) - base64_chars;

        arr_3[0] = (arr_4[0] << 2) + ((arr_4[1] & 0x30) >> 4);
        arr_3[1] = ((arr_4[1] & 0xf) << 4) + ((arr_4[2] & 0x3c) >> 2);

        for (int k = 0; k < i - 1; k++)
            output[j++] = arr_3[k];
    }

    *out_len = j;  // Longitud de la salida
    return output;
}

int main() {
    char texto_codificado[1000];
    int longitud_decodificada;

    // Pedir el texto codificado en Base64
    printf("Introduce el texto codificado en Base64: ");
    fgets(texto_codificado, sizeof(texto_codificado), stdin);
    texto_codificado[strcspn(texto_codificado, "\n")] = '\0';  // Eliminar el salto de línea del input

    // Decodificar
    unsigned char* texto_decodificado = decodificar_base64(texto_codificado, strlen(texto_codificado), &longitud_decodificada);
    texto_decodificado[longitud_decodificada] = '\0';  // Terminar la cadena decodificada

    // Mostrar el texto decodificado
    printf("Texto decodificado: %s\n", texto_decodificado);

    // Liberar memoria
    free(texto_decodificado);

    return 0;
}
