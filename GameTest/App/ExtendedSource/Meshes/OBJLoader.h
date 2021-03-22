
#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include "..\Helpers\SimpleMath.h"
#include "Mesh.h"
#include <vector>
#include <assert.h>

class OBJLoader
{
public:

    static std::vector<Vec2> LoadLineOBJ(const char* filePath)
    {
        long fileLength = 0;
        char* fileContents = LoadFile(filePath, &fileLength);

        assert(fileLength != 0 && fileContents != 0); // There was no such file as the one requested, or the file was empty.

        std::vector<Vec2> readVerts;
        std::vector<Vec2> meshVerts;

        char* nextSymbol = 0;
        char* line = strtok_s(fileContents, "\n", &nextSymbol);

        while (line)
        {
            if (line[0] == 'v')
            {
                Vec2 value;
                float unused;
                sscanf_s(line, "v %f %f %f", &value.x, &unused, &value.y);

                // Blender's Y axis is the other way from this OBJ loader.
                // Normally, I'd go back and re-export things differently but
                // this will work just fine for the purposes of this exercise.

                value.y = -value.y;

                readVerts.push_back(value);
            }
            if (line[0] == 'l')
            {
                int val1, val2 = 0;
                sscanf_s(line, "l %d %d", &val1, &val2);
                meshVerts.push_back(readVerts[--val1]);
                meshVerts.push_back(readVerts[--val2]);
            }

            line = strtok_s(0, "\n", &nextSymbol);
        }

        delete[] fileContents;
        return meshVerts;
    };

private:

    static char* LoadFile(const char* filePath, long* fileLength)
    {
        FILE* file;
        char* fileBuffer = 0;;

        errno_t error = fopen_s(&file, filePath, "rb");

        if (file)
        {
            fseek(file, 0, SEEK_END);
            long size = ftell(file);
            rewind(file);

            fileBuffer = new char[size + 1];
            fread(fileBuffer, size, 1, file);
            fileBuffer[size] = 0;

            if (fileLength)
            {
                *fileLength = size;
            }

            fclose(file);
        }

        return fileBuffer;
    }
};

#endif