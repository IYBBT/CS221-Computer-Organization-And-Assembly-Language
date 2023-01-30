
#include <iostream>

#define YEAR_BITS 0x0003
#define CREDIT_BITS 0x001F
#define DECLARED_BITS 0x0001
#define GPA_BITS 0x003F

#define CREDIT_SHIFT 0x0002
#define DECLARED_SHIFT 0x0007
#define GPA_SHIFT 0x0008

// data members as int:   each student is 16 bytes
// data members as int:   each student is 8 bytes
// data members as char:  each student is 4 bytes

typedef struct student {
    int get_year() const {
        return (information & YEAR_BITS) + 1;
    }

    void set_year(int year) {
        --year;

        information &= ~YEAR_BITS;
        information |= year;
    }

    int get_credits() const {
        return ((information & (CREDIT_BITS << CREDIT_SHIFT)) >> CREDIT_SHIFT) + 1;
    }

    void set_credits(int credits) {
        --credits;

        information &= ~(CREDIT_BITS << CREDIT_SHIFT);
        information |= (credits << CREDIT_SHIFT);
    }

    int get_declared() const {
        return (information & (DECLARED_BITS << DECLARED_SHIFT)) >> DECLARED_SHIFT;
    }

    void set_declared(int declared) {
        information &= ~(DECLARED_BITS << DECLARED_SHIFT);
        information |= (declared << DECLARED_SHIFT);
    }

    int get_gpa() const {
        return (information & (GPA_BITS << GPA_SHIFT)) >> GPA_SHIFT;
    }

    void set_gpa(int gpa) {
        information &= ~(GPA_BITS << GPA_SHIFT);
        information |= (gpa << GPA_SHIFT);
    }

private:
    // char year = 0;           // 1, 2, 3, 4
    // char credits = 0;        // 1 - 32
    // char declared = 0;       // false or true
    // char gpa = 0;            // 0 - 43
    short information = 0;      // Holds all the information of the student within 14 bits
                                // **00000000000000
                                // 2        6       1           5           2
                                // **       000000  0           00000       00
                                // Empty    GPA     Declared    CREDITS     year
                                // -----    char    bool        char        char

private:
    friend std::ostream& operator<<(std::ostream& os, const student& sd) {
        os << "Year: " << sd.get_year() << '\n';
        os << "Credits: " << sd.get_credits() << '\n';
        os << (sd.get_declared() ? "Declared" : "Undeclared") << '\n';
        os << "GPA: " << sd.get_gpa();
        return os;
    }
} student_t;

int main(int argc, char** argv) {
    student_t s;
    s.set_year(4);
    s.set_credits(32);
    s.set_declared(1);
    s.set_gpa(43);
    std::cout << s << std::endl;
}
