#ifndef CP_LIBRARY_FASTIO_H
#define CP_LIBRARY_FASTIO_H

#include <type_traits>
#include <limits>
#include <string>

namespace FastIO {
    inline void print_char(const char& c) {
        putchar_unlocked(c);
    }
    inline void print_str(const char* str) {
        while (*str) {
            putchar_unlocked(*str++);
        }
    }
    template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
    inline void print_int(T n) {
        if (n == 0) {
            putchar_unlocked('0');
            return;
        }
        if (n < 0) {
            putchar_unlocked('-');
            n = -n;
        }
        char buffer[std::numeric_limits<T>::digits10 + 2];
        int i = 0;
        while (n) {
            buffer[i++] = n % 10 + '0';
            n /= 10;
        }
        while (i) {
            putchar_unlocked(buffer[--i]);
        }
    }
    inline void print_string(const std::string& str) {
        for (const char& c: str) {
            putchar_unlocked(c);
        }
    }
	inline void print_longint(__int128_t n) {
        if (n == 0) {
            putchar_unlocked('0');
            return;
        }
        if (n < 0) {
            putchar_unlocked('-');
            n = -n;
        }
        char buffer[40];
        int i = 0;
        while (n) {
            buffer[i++] = n % 10 + '0';
            n /= 10;
        }
        while (i) {
            putchar_unlocked(buffer[--i]);
        }
	}
    template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    inline void print_float(T n, const int& precision = 10) {
        long long int_part = static_cast<long long>(n);
        print_int(int_part);
        n -= int_part;
        int i = 0;
        putchar_unlocked('.');
        while(i < precision) {
            n *= 10;
            int digit = static_cast<int>(n);
            putchar_unlocked(digit + '0');
            n -= digit;
            i++;
        }
    }
    inline char scan_char() {
        char c;
        while (c = getchar_unlocked(), c == ' ' || c == '\n') {
            continue;
        }
        return c;
    }
    inline std::string scan_string() {
        std::string str;
        char c;
        while (c = scan_char(), c != '\n' && c != ' ') {
            str.push_back(c);
        }
        return str;
    }
    inline long long scan_int() {
        long long n = 0;
        bool is_negative = false;
        char c = scan_char();
        if (c == '-') {
            is_negative = true;
            c = scan_char();
        }
        do {
            n = n * 10 + c - '0';
			c = getchar_unlocked();
        } while (c != ' ' && c != '\n');
        return is_negative ? -n : n;
    }
	inline __int128_t scan_longint() {
		__int128_t n = 0;
        bool is_negative = false;
        char c = scan_char();
        if (c == '-') {
            is_negative = true;
            c = scan_char();
        }
        do {
            n = n * 10 + c - '0';
			c = getchar_unlocked();
        } while (c != ' ' && c != '\n');
        return is_negative ? -n : n;
	}
    inline long double scan_float() {
        long double n = 0;
        bool is_negative = false;
        char c = scan_char();
        if (c == '-') {
            is_negative = true;
            c = scan_char();
        }
        do {
            n = n * 10 + c - '0';
        } while (c = getchar_unlocked(), c != ' ' && c != '\n' && c != '.');
        if (c == '.') {
            long double k = 1;
            while (c = getchar_unlocked(), c != ' ' && c != '\n') {
                k /= 10;
                n += k * (c - '0');
            }
        }
        return is_negative ? -n : n;
    }
    class instream {
    public:
        template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
        instream& operator>>(T& n) {
            n = FastIO::scan_int();
            return *this;
        }
        instream& operator>>(__int128_t& n) {
            n = FastIO::scan_longint();
            return *this;
        }
        instream& operator>>(std::string& str) {
            str = FastIO::scan_string();
            return *this;
        }
        instream& operator>>(char& c) {
            c = FastIO::scan_char();
            return *this;
        }
        template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        instream& operator>>(long double& n) {
            n = FastIO::scan_float();
            return *this;
        }
    };
    class outstream {
        int precision = 0;
    public:
        template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
        outstream& operator<<(T n) {
            FastIO::print_int(n);
            return *this;
        }
        outstream& operator<<(__int128_t n) {
            FastIO::print_longint(n);
            return *this;
        }
        template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
        outstream& operator<<(T n) {
            FastIO::print_float(n, precision);
            return *this;
        }
        outstream& operator<<(const std::string& str) {
            FastIO::print_string(str);
            return *this;
        }
        outstream& operator<<(const char* str) {
            FastIO::print_str(str);
            return *this;
        }
        outstream& operator<<(const char& c) {
            FastIO::print_char(c);
            return *this;
        }
        void setprecision(int precision) {
            this->precision = precision;
        }
    };
};

#endif //CP_LIBRARY_FASTIO_H
