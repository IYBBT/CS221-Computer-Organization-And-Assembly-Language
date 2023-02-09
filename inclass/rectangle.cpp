
#include <iostream>

template<typename T>
struct rectangle {

    rectangle() : width(1), height(1) {}

    rectangle(T width, T height) : width(width), height(height) {}

    ~rectangle() {
        width = height = 0;
    }

    T get_width() const { return width; }
    T get_height() const { return height; }

    void set_width(T width) {
        this->width = width;
    }

    void set_height(T height) {
        this->height = height;
    }

private:
    T width, height;

private:
    friend rectangle operator+(const rectangle& ls, const rectangle& rs) {
        return rectangle(ls.width + rs.width, ls.height + rs.height);
    }

    friend rectangle& operator+=(rectangle& ls, const rectangle& rs) {
        ls = (ls + rs);
        return ls;
    }

    friend rectangle operator-(const rectangle& ls, const rectangle& rs) {
        return rectangle(ls.width - rs.width, ls.height - rs.height);
    }

    friend rectangle operator*(const int ls, const rectangle& rs) {
        return rectangle(ls * rs.width, ls * rs.height);
    }

    friend rectangle operator*(const rectangle& ls, const int rs) {
        return rs * ls;
    }

    friend std::ostream& operator<<(std::ostream& os, const rectangle& r) {
        os << "[" << r.width << ", " << r.height << "]";
        return os;
    }
};

int main(int argc, char** argv) {
    rectangle<float> r1 = { 0.1, 0.2 };
    rectangle<float> r2 = { 0.5, 0.3 };

    std::cout << r1 + r2 << std::endl;
    std::cout << r1 - r2 << std::endl;
    // std::cout << r1 * 2 << std::endl;
    // std::cout << 2 * r1 << std::endl;
    std::cout << (r1 += r2) << std::endl;
    std::cout << r1 << std::endl;
    std::cout << &r1 << std::endl;
    std::cout << &r2 << std::endl;

    return 0;
}
