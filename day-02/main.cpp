#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


struct IdRange
{
    size_t from, to;
};

std::vector<IdRange> parseFile(std::string const& name)
{
    std::ifstream file(name);

    std::string line;
    std::getline(file, line);

    std::vector<IdRange> results;

    std::istringstream iss(line);
    for (std::string range; std::getline(iss, range, ','); )
    {
        std::istringstream rangess(range);
        IdRange r;
        char dash;
        rangess >> r.from >> dash >> r.to;

        results.push_back(r);
    }

    return results;
}

bool isDoubled(size_t n)
{
    std::string s = std::to_string(n);

    if (s.length() % 2 == 1)
        return false;
    
    const int halfLength = s.length() / 2;
    for (int i = 0; i < halfLength; i++)
    {
        if (s[i] != s[i+halfLength])
            return false;
    }

    return true;
}

size_t sumOfDoubled(std::vector<IdRange> const& ranges)
{
    size_t sum = 0;
    for (auto const& r : ranges)
    {
        for (size_t n = r.from; n <= r.to; n++)
        {
            if (isDoubled(n))
                sum += n;
        }
    }
    return sum;
}

int main(int, char**)
{
    auto ranges = parseFile("../input.txt");
    size_t sum = sumOfDoubled(ranges);

    std::cout << sum << std::endl;
}
