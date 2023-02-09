
#include <iostream>

#define YEAR_BITS 0x0003
#define CREDIT_BITS 0x001F
#define DECLARED_BITS 0x0001
#define GPA_BITS 0x003F

#define CREDIT_SHIFT 0x0002
#define DECLARED_SHIFT 0x0007
#define GPA_SHIFT 0x0008

// data members as int:          each student is 16 bytes
// data members as short:        each student is 8 bytes
// data members as char:         each student is 4 bytes
// data members stored as bits:  all stored in 2 bytes

typedef struct student {
    student() : data(0) {}

    student(unsigned short data) : data(data) {}

    int get_year() const {
        return (data & YEAR_BITS) + 1;
    }

    void set_year(int year) {
        --year;

        data &= ~YEAR_BITS;
        data |= year;
    }

    int get_credits() const {
        return ((data & (CREDIT_BITS << CREDIT_SHIFT)) >> CREDIT_SHIFT) + 1;
    }

    void set_credits(int credits) {
        --credits;

        data &= ~(CREDIT_BITS << CREDIT_SHIFT);
        data |= (credits << CREDIT_SHIFT);
    }

    int get_declared() const {
        return (data & (DECLARED_BITS << DECLARED_SHIFT)) >> DECLARED_SHIFT;
    }

    void set_declared(int declared) {
        data &= ~(DECLARED_BITS << DECLARED_SHIFT);
        data |= (declared << DECLARED_SHIFT);
    }

    int get_gpa() const {
        return (data & (GPA_BITS << GPA_SHIFT)) >> GPA_SHIFT;
    }

    void set_gpa(int gpa) {
        data &= ~(GPA_BITS << GPA_SHIFT);
        data |= (gpa << GPA_SHIFT);
    }

private:
    // char year = 0;           // 1, 2, 3, 4
    // char credits = 0;        // 1 - 32
    // char declared = 0;       // false or true
    // char gpa = 0;            // 0 - 43
    unsigned short data = 0;    // Holds all the data of the student within 14 bits
                                // **00000000000000
                                // 2        6       1           5           2
                                // **       000000  0           00000       00
                                // Empty    GPA     Declared    CREDITS     year

private:
    friend std::ostream& operator<<(std::ostream& os, const student& sd) {
        os << "Year: " << sd.get_year() << '\n';
        os << "Credits: " << sd.get_credits() << '\n';
        os << (sd.get_declared() ? "Declared" : "Undeclared") << '\n';
        os << "GPA: " << sd.get_gpa();
        return os;
    }
} student_t;

student_t operator+(const student& ls, const student& rs) {
    int credits = (ls.get_credits() + rs.get_credits()) / 2;
    student s;
    s.set_credits(credits);
    return s;
}

int main(int argc, char** argv) {
    student_t s;
    s.set_year(4);
    s.set_credits(32);
    s.set_declared(0);
    s.set_gpa(43);
    std::cout << s << std::endl;
    std::cout << s + s << std::endl;
}
