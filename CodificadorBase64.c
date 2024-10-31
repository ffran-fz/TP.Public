#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tabla Base64
static const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Función para codificar en Base64
char* codificar_base64(const unsigned char* input, int len) {
    int i = 0, j = 0;
    int en_len = 4 * ((len + 2) / 3);  // Tamaño de la salida codificada
    char* output = (char*)malloc(en_len + 1);  // Asignar memoria para la cadena resultante
    unsigned char arr_3[3], arr_4[4];

    while (len--) {
        arr_3[i++] = *(input++);
        if (i == 3) {
            arr_4[0] = (arr_3[0] & 0xfc) >> 2;
            arr_4[1] = ((arr_3[0] & 0x03) << 4) + ((arr_3[1] & 0xf0) >> 4);
            arr_4[2] = ((arr_3[1] & 0x0f) << 2) + ((arr_3[2] & 0xc0) >> 6);
            arr_4[3] = arr_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                output[j++] = base64_chars[arr_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (int k = i; k < 3; k++)
            arr_3[k] = '\0';

        arr_4[0] = (arr_3[0] & 0xfc) >> 2;
        arr_4[1] = ((arr_3[0] & 0x03) << 4) + ((arr_3[1] & 0xf0) >> 4);
        arr_4[2] = ((arr_3[1] & 0x0f) << 2) + ((arr_3[2] & 0xc0) >> 6);
        arr_4[3] = arr_3[2] & 0x3f;

        for (int k = 0; k < i + 1; k++)
            output[j++] = base64_chars[arr_4[k]];

        while (i++ < 3)
            output[j++] = '=';
    }

    output[j] = '\0';  // Terminar la cadena codificada
    return output;
}

int main() {
    char texto[1000];

    // Pedir el texto a codificar
    printf("Introduce el texto a codificar en Base64: ");
    fgets(texto, sizeof(texto), stdin);
    texto[strcspn(texto, "\n")] = '\0';  // Eliminar el salto de línea del input

    // Codificar
    char* texto_codificado = codificar_base64((unsigned char*)texto, strlen(texto));
    printf("Texto codificado en Base64: %s\n", texto_codificado);

    // Liberar memoria
    free(texto_codificado);

    return 0;
}
