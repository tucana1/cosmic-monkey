#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*

▗▞▀▘ ▄▄▄   ▄▄▄ ▄▄▄▄  ▄ ▗▞▀▘    ▄▄▄▄   ▄▄▄  ▄▄▄▄  █  ▄ ▗▞▀▚▖▄   ▄ 
▝▚▄▖█   █ ▀▄▄  █ █ █ ▄ ▝▚▄▖    █ █ █ █   █ █   █ █▄▀  ▐▛▀▀▘█   █ 
    ▀▄▄▄▀ ▄▄▄▀ █   █ █         █   █ ▀▄▄▄▀ █   █ █ ▀▄ ▝▚▄▄▖ ▀▀▀█ 
                     █                           █  █      ▄   █ 
                                                            ▀▀▀  
 * INSTRUCTIONS:
 * Note, you're going to need a C compiler to test your code. This is different
 * for each operating system, so feel free to ask a team member for help if
 * you're stuck.
 * ---------------------------------------------------------------------------
 * DISCLAIMER: This code is very UNIX/Linux specific. It abides by the
 * coding/safety standards expected on PVDXos, but it NOT a 1-to-1
 * correspondance with the code pushed to the satellite.
 */

/**
 * int32_t cosmic_monkey(void* data, size_t size)
 *
 * \brief Randomly selects a bit within `data` to flip, and flips the bit.
 *
 * The function should:
 *    - Randomly select a byte and a bit within that byte to flip (using rand()
 * seeded by srand()).
 *    - Print which byte and bit are being flipped (for debugging purposes).
 *    - Flip the selected bit using XOR.
 *
 * Prarametres:
 * \param data : The pointer to the data block to be mutated.
 * \param size : The size of the data block in bytes.
 *
 * Returns:
 * \return int32_t : 0 upon success
 */

int32_t cosmic_monkey(void *data, size_t size) {
    if (data == NULL || size == 0) {
        return -1;
    }
    // has to be casted to an integer
    uint8_t * bytes = (uint8_t *)data;

    size_t byte_index = (size_t)rand() % size;
    uint8_t bit_index = (uint8_t)(rand() % 8);

#ifdef DEBUG
    if (printf("Flipping bit %u of byte %zu\n", bit_index, byte_index) < 0) {
        perror("printf");
        return -1;
    }
#endif
    // where the actual flip happens, 
    bytes[byte_index] ^= (uint8_t)(1u << bit_index);

    return 0;
}

/**
 * int32_t print_bytes(void *data, size_t size);
 *
 * \brief Given a pointer to arbitrary data and a size, prints the data as a hex
 * array
 *
 * Parametres:
 * \param data : The pointer to the data block to be printed.
 * \param size : The size of the data block in bytes.
 *
 * Returns:
 * \return int32_t : a status code, int32_t to comply with status codes returned
 *                   by printf
 */

int32_t print_bytes(void *data, size_t size) {
    uint8_t * bytes = (uint8_t *)data;

    for (size_t i = 0; i < size; i++) {
        if (printf("%02X ", bytes[i]) < 0) {
            perror("printf");
            return -1;
        }
    }

    if (printf("\n") < 0) {
        perror("printf");
        return -1;
    }

    return 0;
}

/**
 * int main(void)
 *
 * \brief Program entry point; runs cosmic monkey program
 *
 * Parametres:
 * N/A
 *
 * Return:
 * \return int : 0 upon success, +ve status code otherwise.
 *
 * NOTE: the use of int here as a return type is only to comply with the current
 * Linux standard. Use of ambiguous/unsized `int` types is *strongly*
 * discouraged in PVDXos
 */
int main(void) {
    // Example data for testing the Cosmic Monkey
    unsigned char data[4] = {0xFF, 0x00, 0xAA, 0x55};

    // Print original data
    if (printf("Original data:\n") < 0 || print_bytes(data, sizeof(data)) < 0) {
        return 1;
    }

    // Seed random number generator
    time_t now = time(NULL);
    if (now == (time_t)-1) {
        perror("time");
        return 1;
    }
    srand((uint32_t)now);

    // Run the Cosmic Monkey to flip random bits
    if (cosmic_monkey(data, sizeof(data)) < 0) {
        return 1;
    }

    // Print mutated data
    if (printf("Mutated data:\n") < 0 || print_bytes(data, sizeof(data)) < 0) {
        return 1;
    }

    return 0;
}

/* 
⠀⠀⠀⠀⠀⠀⠀⣀⣴⣦⡄⠀⠀⠀⠀⠀⠀⠀
⠀⠀⢠⢺⡽⣦⣴⣾⡿⣟⣿⢿⣷⣤⣺⠿⡳⡀⠀
⠀⠀⠸⣿⣠⣿⡿⠛⠛⢿⡟⠛⠻⣿⣷⣠⡷⠁⠀
⠀⠀⠀⠀⠹⣿⠇⣠⡄⠀⠀⣠⡀⢹⣿⠉⣠⣤⣦    ⠀⠀⠀⢸⣦⡀⠀⠀⠀⠀⢀⡄
⠀⠀⠀⠀⠀⢿⡇⠀⠀⢂⠂⠀⠀⢿⡇⢸⣿⠋⠁    ⠀⠀⠀⢸⣏⠻⣶⣤⡶⢾⡿⠁⠀⢠⣄⡀⢀⣴
⠀⠀⠀⠀⠀⠘⣧⣈⠓⠚⠒⠋⣠⣞⠀⠘⢿⣷⡄    ⠀⠀⣀⣼⠷⠀⠀⠁⢀⣿⠃⠀⠀⢀⣿⣿⣿⣇
⠀⠀⠀⠀⠀⢸⣿⡿⣿⣿⣿⣿⢿⣿⡆⠀⢀⣿⡷    ⠴⣾⣯⣅⣀⠀⠀⠀⠈⢻⣦⡀⠒⠻⠿⣿⡿⠿⠓⢀
⠀⠀⠀⣴⣶⣿⡿⣽⠟⠉⠉⢻⣿⢾⣷⣶⣿⠟⠁    ⠀⠀⠀⠉⢻⡇⣤⣾⣿⣷⣿⣿⣤⠀⠀⣿⠁⠀
⠀⣴⠋⢻⣿⣿⣟⣿⡀⠀⠀⢸⣿⢿⣿⣟⡟⢶⣄    ⠀⠀⠀⠀⠸⣿⡿⠏⠀
⠈⢯⡀⠈⠻⢿⣿⡽⣇⠀⢀⡸⢿⣿⡿⠋⠀⣀⠝    ⠀⠀⠀⠀⠀⠟⠁⠀
⠀⠀⠙⠢⠴⠭⠤⠤⠬⠧⠼⠤⠤⠤⠽⠦⠖⠁⠀
*/
