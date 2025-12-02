#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int numLength(long long num)
{
    return static_cast<int>(std::to_string(num).length());
}

bool seqRepeats(std::string numText, int numLen, int seqLen)
{
    if (numLen % seqLen != 0)
        return false;
    
    for (int i = 0; i < numLen - seqLen; i += seqLen)
    {
        std::string firstPart{numText.substr(i, seqLen)};
        std::string secondPart{numText.substr(i + seqLen, seqLen)};
        if (firstPart != secondPart)
            return false;
    }

    return true;
}

// Whether or not the number is a repeated
// sequence of digits.
bool isInvalidID(long long num)
{
    int len{numLength(num)};
    // Minimum number of repetitions = 2.
    // Maximum subsequence length = len/2.
    int maxLen{len/2};
    
    std::string numText = std::to_string(num);
    for (int i = 1; i <= maxLen; i++)
    {
        if (seqRepeats(numText, len, i))
            return true;
    }

    return false;
}

void splitRange(std::string_view text, long long& first, long long& second)
{
    int index{0};
    for (char c : text)
    {
        if (c == '-') break;
        index++;
    }

    first = std::stoll(std::string(text.substr(0, index)));
    second = std::stoll(std::string(text.substr(index + 1, 
        text.length() - index - 1)));
}

int main()
{
    std::ifstream file{"test.txt"};
    std::vector<std::string> ranges(1);
    int pos{0};

    while (!file.eof())
    {
        char c;
        if ((c = static_cast<char>(file.get())) != ',')
            ranges[pos].push_back(c);
        else
        {
            pos++;
            ranges.emplace_back("");
        }
    }

    long long first{};
    long long second{};
    long long total{0};

    for (std::string range : ranges)
    {
        splitRange(range, first, second);
        for (long long i = first; i <= second; i++)
        {
            if (isInvalidID(i))
                total += i;
        }
    }

    std::cout << "Invalid ID Total: " << total << '\n';

    return 0;
}