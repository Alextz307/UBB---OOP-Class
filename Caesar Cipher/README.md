
# Caesar Cipher Tool

This program is a simple implementation of the Caesar Cipher encryption and decryption tool in C. The tool allows you to encrypt plain English text using the Caesar Cipher technique and decrypt text that was encrypted with the same method.

## Features

- Encrypt text with a given shift
- Decrypt text based on the normal distribution of English letter frequencies
- Interactive menu to choose between encryption, decryption, and exiting the program

## Prerequisites

- A C compiler such as `gcc` or `clang`
- Make sure you have a `distribution.txt` file containing the normal distribution of English letters

## Usage

1. Compile the program with your C compiler. For example, using `gcc`:
   ```sh
   gcc main.c -o caesar_cipher
   ```
2. Run the compiled program:
   ```sh
   ./caesar_cipher
   ```
3. Follow the on-screen menu to select encryption or decryption.

## Menu Options

1. **Encrypt an English text using Caesar Cipher:** You will be prompted to enter the text you wish to encrypt and the shift value.
2. **Decrypt a text (which was encrypted using Caesar Cipher):** You will be prompted to enter the encrypted text, and the program will attempt to decrypt it.
3. **Stop:** Exits the program.

## File Structure

- `main.c`: Contains the source code.
- `distribution.txt`: Should contain the distribution of letter frequencies in English (required for decryption).

## Notes

- The `distribution.txt` file must contain 26 floating-point values representing the normal distribution of English letters from 'a' to 'z'.
- Decryption assumes that the text was encrypted using the Caesar Cipher method without additional obfuscation.

## Contributing

Feel free to fork the repository, make changes, and submit pull requests. Please update the tests as appropriate.

## License

This project is open-source and available under the [MIT License](LICENSE).

## Acknowledgments

- This program uses a standard frequency distribution of English letters for decryption. Make sure your `distribution.txt` is accurate for effective decryption.
- The encryption and decryption are case-insensitive and handle only alphabetic characters.

## Disclaimer

This tool is for educational purposes only. The author is not responsible for any misuse of this tool.
