#include <stdio.h>
# include <string>

int main(int argc, char** argv){
    FILE * file = fopen("../glTF-Sample-Models/2.0/TriangleWithoutIndices/glTF/TriangleWithoutIndices.gltf", "r+");
    if (!file) {
        printf("ERROR!");
        return 1;
    }

    fseek (file, 0, SEEK_END);
    unsigned int size = ftell(file);
    rewind(file);

    unsigned char * fileData = new unsigned char[size];
    fread(fileData, size, 1, file);
    fclose(file);
    printf("%s\n", fileData);

    bool withinQuote = false;

    // print all keys
    for (int i = 0; i < size; i++) {
        char c = fileData[i];

        if (c == '\"' && !withinQuote) {
            withinQuote = true;
        } else if (c == '\"' && withinQuote) {
            withinQuote = false;
            printf("\"\n");
        }

        if (withinQuote) {
            printf("%c", c);
        }
    }

    // print all headers
    withinQuote = false;
    std::string header = "";

    for (int i = 0; i < size; i++) {
        char c = fileData[i];

        if (c == '\"' && !withinQuote) {
            withinQuote = true;
        } else if (c == '\"' && withinQuote) {
            withinQuote = false;
            header += '\"';
            printf("%s\n", header);

            // BEGIN HERE: every time we find an open bracket add to numBracketPairs and every time we find a closing bracked subtract. When numBracketPairs is 0 again, we know we are at the en.
            int numBracketPairs = 0;
            while (numerBracketPairs != 0) {

            }

            i = j;
        }

        if (withinQuote) {
            header += c;
        }
    }

    delete[] fileData;
}