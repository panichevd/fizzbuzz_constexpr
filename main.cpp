#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>

template <typename T, typename U>
constexpr void copy(
    T first,
    T last,
    U dst)
{
    while (first < last) {
        *dst++ = *first++;
    }
}

template <std::size_t size1, std::size_t size2>
constexpr std::array<char, size1 + size2> concat(
    const std::array<char, size1> & a1,
    const std::array<char, size2> & a2)
{
    std::array<char, size1 + size2> result{};
    ::copy(a1.begin(), a1.end(), result.begin());
    ::copy(a2.begin(), a2.end(), result.begin() + size1);
    return result;
}

template<unsigned N, std::size_t Size = 8>
constexpr std::array<char, Size> to_array()
{
    std::array<char, Size> result{};

    unsigned n = N;

    int i = Size;
    for (; i > 0; --i) {
        result[i - 1] = '0' + n % 10;
        n /= 10;
        if (n == 0) {
            --i;
            break;
        }
    }

    int j = 0;
    for (; i + j < Size; ++j) {
        result[j] = result[i + j];
    }

    for (; j < Size; ++j) {
        result[j] = ' ';
    }

    return result;
}

// All return paths need to return array of same length
template <unsigned N>
constexpr auto fizzBuzz()
{
    constexpr std::array<char, 1> comma = { ',' };
    constexpr std::array<char, 8> fizz     = { 'f', 'i', 'z', 'z', ' ', ' ', ' ', ' ' };
    constexpr std::array<char, 8> buzz     = { 'b', 'u', 'z', 'z', ' ', ' ', ' ', ' ' };
    constexpr std::array<char, 8> fizzbuzz = { 'f', 'i', 'z', 'z', 'b', 'u', 'z', 'z' };

    if constexpr (N % 15 == 0) {
        return concat(concat(fizzBuzz<N - 1>(), comma), fizzbuzz);
    }
    
    if constexpr (N % 3 == 0) {
        return concat(concat(fizzBuzz<N - 1>(), comma), fizz);
    }

    if constexpr (N % 5 == 0) {
        return concat(concat(fizzBuzz<N - 1>(), comma), buzz);
    }

    return concat(concat(fizzBuzz<N - 1>(), comma), to_array<N>());
}

template <>
constexpr auto fizzBuzz<1>()
{
    return to_array<1>();
}

template <std::size_t Size>
constexpr auto remove_spaces(const std::array<char, Size> & str)
{
    std::array<char, Size> result { 0 };

    for (std::size_t i = 0, j = 0; i < Size; ++i) {
        if (str[i] != ' ') {
            result[j++] = str[i];
        }
    }

    return result;
}

int main()
{
    constexpr auto fizz_buzz = fizzBuzz<20>();
    constexpr auto result = remove_spaces(fizz_buzz);

    for (const auto & c : result) {
        std::cout << c;
    }

    return 0;
}