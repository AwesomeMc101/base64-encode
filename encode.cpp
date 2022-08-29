// encode.cpp
// Written by AwesomeMc101 for LunarGuard LLC / Lunar Guard Technologies
// Licensed under MIT

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>


std::map<int, char> base64mapping = { {0, 'A'},{1, 'B'},{2, 'C'},{3, 'D'},{4, 'E'},{5, 'F'},
{6, 'G'},{7, 'H'},{8, 'I'},{9, 'J'},{10, 'K'},{11, 'L'},{12, 'M'},{13, 'N'},{14, 'O'},{15, 'P'},
{16, 'Q'},{17, 'R'},{18, 'S'},{19, 'T'},{20, 'U'},{21, 'V'},{22, 'W'},{23, 'X'},{24, 'Y'},{25, 'Z'},
{26, 'a'},{27, 'b'},{28, 'c'},{29, 'd'},{30, 'e'},{31, 'f'},{32, 'g'},{33, 'h'},{34, 'i'},{35, 'j'},
{36, 'k'},{37, 'l'},{38, 'm'},{39, 'n'},{40, 'o'},{41, 'p'},{42, 'q'},{43, 'r'},{44, 's'},{45, 't'},
{46, 'u'},{47, 'v'},{48, 'w'},{49, 'x'},{50, 'y'},{51, 'z'},{52, '0'},{53, '1'},{54, '2'},{55, '3'},
{56, '4'},{57, '5'},{58, '6'},{59, '7'},{60, '8'},{61, '9'},{62, '+'},{63, '/'},
};

namespace Binary 
{
    std::vector<std::string> stringToBinary(std::string convert)
    {
        std::vector<std::string> binary;
        int len = convert.length();
        for (int i = 0; i < len; i++)
        {
            int val = int(convert[i]);
            char character = convert[i];
            int z;
            int m[8];
            for (z = 0; z < 8; z++)
            {
                m[z] = character % 2;
                character = character / 2;
            }
            int top, bottom;
            std::string flex = "";
            for (bottom = 0, top = 7; bottom < 8; bottom++, top--)
            {
                flex += std::to_string(m[top]);
            }
            binary.push_back(flex);
        }
        return binary;
    }
    std::vector<std::string> sixBitBinaryConversion(std::vector<std::string> vec)
    {
        std::string overflow = "";
        std::vector<std::string> trueBinary;
        for (int i = 0; i < vec.size(); i++)
        {
            std::string flex = "";
            if (overflow.length() > 0)
            {
                if (overflow.length() > 6)
                {
                    flex = overflow.substr(0, 6);
                    overflow = overflow.substr(6);
                }
                else
                {
                    flex = overflow;
                    overflow.clear();
                }
            }
            int toLoop = 6 - flex.size();

            for (int x = 0; x < toLoop; x++)
            {
                std::string convert(1, vec[i].at(x));
                flex += convert;
            }
            trueBinary.push_back(flex);

            if (vec[i][toLoop] != std::string::npos) {
                overflow += vec[i].substr(toLoop);
            }
        }

        if (overflow.length() > 6)
        {
            while (overflow.length() > 6)
            {
                trueBinary.push_back(overflow.substr(0, 6));
                overflow = overflow.substr(6);
            }
        }
        if (overflow.length() > 0)
        {
            while (overflow.length() < 6)
            {
                overflow += "0";
            }
            trueBinary.push_back(overflow);
        }
        return trueBinary;
    }
}

void encrypt(std::string tec)
{
    std::vector<std::string> binaries = Binary::sixBitBinaryConversion(Binary::stringToBinary(tec));

    std::string finalEncrypt = "";

    for (std::string set : binaries)
    {
        int sumTotal = 0;
        int multiplier = -1;
        for (int i = set.size(); i >= 0; i--)
        {
            if (set[i] == '1')
            {
                sumTotal += (pow((1 * 2), multiplier));
            }
            else
            {
                sumTotal += 0; //lol
            }
            multiplier++;
        }
        finalEncrypt += base64mapping[sumTotal];
    }
    if ((finalEncrypt.length() % 4) != 0)
    {
        while ((finalEncrypt.length() % 4) != 0)
        {
            finalEncrypt += '=';
        }
    }
    std::cout << "Encrypted String: " << finalEncrypt;
}

int main()
{
    encrypt("Are you down?!");
}
