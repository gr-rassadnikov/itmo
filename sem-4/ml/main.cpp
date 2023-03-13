#include <iostream>
#include <variant>

using namespace std;

// (a) A -> B -> A
template<class A, class B>
function<A(B)> f_a(A a) {
    return [a](B b) { return a; };
}

// (b) A&B -> A|B
template<class A, class B>
variant<A, B> f_b(pair<A, B> pair) {
    return pair.first;
}

// (c) (a & (b|c)) -> ((a&b) | (a&c))
// D = (a & (b|c))
template<class A, class B, class C>
variant<pair<A, B>, pair<A, C>> f_c(pair<A, variant<B, C>> D) {
    if (holds_alternative<B>(D.second)) {
        return variant<pair<A, B>, pair<A, C>>({D.first, get<B>(D.second)});
    } else {
        return variant<pair<A, B>, pair<A, C>>({D.first, get<B>(D.second)});
    }
}

// (d)
//bred, A = C = {}; B = {R}
// --> formula = {}
template<class A, class B, class C>
C f_d() {
    throw 3235;
}

// (e) (b|c -> a) -> (b -> a) & (c -> a)
template<class A, class B, class C>
pair<function<A(B)>, function<A(C)>> f_e(function<A(variant<B, C>)> in) {
    return {[in](B b) { return in(b); }, [in](C c) { return in(c); }};
}


#define imp(A, B) function<B(A)>

// (f) ((a -> b) -> c) -> (a -> (b -> c))
template<class A, class B, class C>
function<C(function<B(A)>)> f_f(function<function<C(B)>(A)> in) {
    return [=](A a) {
        return [=](B b) {
            return in([=](A a) { return (b); });
        };
    };
}


int main() {
    std::cout << "Hello, World!" << std::endl;

//    (a)
    auto a_t = f_a<bool, bool>(true)(true);
    cout << a_t;

    for (auto a: {false, true}) {
        for (auto b: {false, true}) {
            cout << f_a<bool, bool>(a)(b);
        }
    }
    return 0;
}
