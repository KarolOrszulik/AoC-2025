#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

using Instructions = std::vector<int>;
constexpr int WHEEL_SIZE = 100;


Instructions parseFile(std::string const& name)
{
    std::ifstream file(name);

    Instructions results;

    for (std::string line; std::getline(file, line); )
    {
        std::istringstream oss(line);
        char dir;
        int distance;
        oss >> dir >> distance;

        if (dir == 'L')
            distance *= -1;
        
        results.push_back(distance);
    }

    return results;
}


int modulo(int input, int moduland)
{
    if (input < 0)
    {
        input += (input / (-moduland) + 1) * moduland;
    }

    return input % moduland;
}


int countZerosFromPosition(int position, Instructions const& instructions)
{
    int numZeros = 0;

    for (auto instr : instructions)
    {
        position += instr;
        position = modulo(position, WHEEL_SIZE);
        
        numZeros += position == 0;
    }

    return numZeros;
}

int countAllZerosFromPosition(int position, Instructions const& instructions)
{
    int numZeros = 0;

    for (auto instr : instructions)
    {
        int dir = instr > 0 ? 1 : -1;
        for (int i = 0; i < std::abs(instr); i++)
        {
            position += dir;
            if (position >= WHEEL_SIZE)
                position = 0;
            if (position < 0)
                position = WHEEL_SIZE - 1;
            
            numZeros += position == 0;
        }
    }

    return numZeros;
}

int main()
{
    constexpr int STARTING_POSITION = 50;

    Instructions instructions = parseFile("../input.txt");
    int zeros = countZerosFromPosition(STARTING_POSITION, instructions);
    int allZeroes = countAllZerosFromPosition(STARTING_POSITION, instructions);

    std::cout << zeros << "\n" << allZeroes << std::endl;
}
