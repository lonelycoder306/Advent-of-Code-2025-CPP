#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int numLength(long long num)
{
    return static_cast<int>(std::to_string(num).length());
}

// Whether or not the number is a repeated
// sequence of digits.
bool isInvalidID(long long num)
{
    int len{};
    // Cannot be repeated if number of digits
    // is odd.
    if ((len = numLength(num)) % 2 != 0)
        return false;
    
    std::string numText = std::to_string(num);
    std::string firstPart = numText.substr(0, len/2);
    std::string secondPart = numText.substr(len/2, len/2);
    return (firstPart == secondPart);
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