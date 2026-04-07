// Only <vector> is allowed besides built-in headers per problem statement.
// Do not include anything else and do not use using namespace std.

#include <vector>

template <typename T>
class Expect {
private:
    T value;
    bool ok;
    bool negate;

    template <typename Pred>
    Expect& apply(Pred p) {
        bool res = p(value);
        if (negate) res = !res;
        ok = ok && res;
        return *this;
    }

public:
    explicit Expect(const T& v) : value(v), ok(true), negate(false) {}

    // toBe: value == y
    template <typename U>
    Expect& toBe(const U& y) {
        return apply([&](const T& x){ return x == y; });
    }

    // toBeOneOf: exists z in vec such that value == z
    Expect& toBeOneOf(const std::vector<T>& vec) {
        return apply([&](const T& x){
            for (const T& z : vec) {
                if (x == z) return true;
            }
            return false;
        });
    }

    // Comparisons
    template <typename U>
    Expect& le(const U& y) { // x <= y
        return apply([&](const T& x){ return !(y < x); });
    }

    template <typename U>
    Expect& ge(const U& y) { // x >= y
        return apply([&](const T& x){ return !(x < y); });
    }

    template <typename U>
    Expect& lt(const U& y) { // x < y
        return apply([&](const T& x){ return x < y; });
    }

    template <typename U>
    Expect& gt(const U& y) { // x > y
        return apply([&](const T& x){ return y < x; });
    }

    // Not: negate subsequent conditions
    Expect& Not() {
        negate = !negate;
        return *this;
    }

    // Conversion to bool for if conditions
    operator bool() const {
        return ok;
    }
};

template <typename T>
Expect<T> expect(const T& v) {
    return Expect<T>(v);
}
