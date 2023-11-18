// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cmath>
#include <limits>
#include <numbers>
#include <type_traits>

#include "Utils/Concepts.h"
#include "Types.h"

/*
*	Cmath.h contains a class providing a set of static math functions.
*
*	Most of these functions are the standard cmath functions written as
*   constexpr. It allows compile-time evaluation, although in runtime these
*   functions would subsequentally invoke the corresponding C functions.
* 
*   Based on: https://github.com/kthohr/gcem/tree/master
*/

// It is required 'cause such functions can be defined in std math library and break our code

#ifdef abs
#undef abs
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace math {
	// Cmath implements some of the standard C math functions as constexpr
    class Cmath final {
    public:
        // The minimal value after which a float cannot have digits after the point (i.e. it is no different from integrals)
        template<::utils::Arithmetic FloatTy>
        constexpr static FloatTy getMinValueWithoutPoint() noexcept {
            if constexpr (::std::is_same_v<FloatTy, float>) {
                return static_cast<FloatTy>(8388608.f);
            } else if constexpr (::std::is_same_v<FloatTy, double>) {
                return static_cast<FloatTy>(4503599627370496.0);
            } else if constexpr (::std::is_same_v<FloatTy, long double>) {
                return static_cast<FloatTy>(9223372036854775808.l);
            }

            return FloatTy(0);
        }

        template<::utils::Arithmetic T>
        constexpr static T abs(const T x) noexcept {
            if constexpr (::std::is_unsigned_v<T>) {
                return x;
            } else {
                return x < 0 ? -x : x;
            }
        }

        template<::utils::Arithmetic T>
        constexpr static T sgn(T x) noexcept {
            return x > T(0) ? T(1)
                : x < T(0) ? T(-1) : T(0);
        }

        template<::utils::Arithmetic A, ::utils::Arithmetic B>
        constexpr static auto min(const A a, const B b) noexcept {
            return a < b ? a : b;
        }

        template<::utils::Arithmetic A, ::utils::Arithmetic B>
        constexpr static auto max(const A a, const B b) noexcept {
            return a > b ? a : b;
        }

        template<::utils::Arithmetic T>
        constexpr static intmax_t wholeOf(const T x) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return intmax_t(x);
            } else {
                return abs(x - floor(x)) >= T(0.5)
                    ? static_cast<intmax_t>(floor(x) + sgn(x))
                    : static_cast<intmax_t>(floor(x));
            }
        }

        template<::utils::Arithmetic T>
        constexpr static T fractionOf(const T x) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return T(0);
            } else {
                return abs(x - floor(x)) >= T(0.5)
                    ? x - floor(x) - sgn(x)
                    : x - floor(x);
            }
        }

        template<::utils::Arithmetic T>
        constexpr static intmax_t exponentOf(const T x, const int32_t exponent) noexcept {
            return x < T(1e-03)
                    ? exponentOf(x * T(1e+04), exponent - intmax_t(4))
                : x < T(1e-01)
                    ? exponentOf(x * T(1e+02), exponent - intmax_t(2))
                : x < T(1)
                    ? exponentOf(x * T(10), exponent - intmax_t(1))
                : x > T(10)
                    ? exponentOf(x / T(10), exponent + intmax_t(1))
                : x > T(1e+02)
                    ? exponentOf(x / T(1e+02), exponent + intmax_t(2))
                : x > T(1e+04)
                    ? exponentOf(x / T(1e+04), exponent + intmax_t(4))
                    : exponent;
        }

        template<::utils::Arithmetic T>
        constexpr static bool isWhole(const T x) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return true;
            } else {
                return Cmath::floor(x) == x;
            }
        }

        template<::utils::Arithmetic T>
        constexpr static bool isOdd(const T x) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return (x & T(1)) != 0;
            } else { // T is floating point
                return isWhole(x) && isOdd(int64_t(x));
            }
        }

        template<::utils::Arithmetic T>
        constexpr static bool isEven(const T x) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return (x & T(1)) == 0;
            } else { // T is floating point
                return isWhole(x) && isEven(int64_t(x));
            }
        }

        template<::utils::Arithmetic T>
        constexpr static bool isNan(const T x) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return false;
            } else {
                return x != x;
            }
        }

        template<::utils::Arithmetic T>
        constexpr static bool isNegInf(const T x) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return false;
            } else {
                return x == -::std::numeric_limits<T>::infinity();
            }
        }

        template<::utils::Arithmetic T>
        constexpr static bool isPosInf(const T x) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return false;
            } else {
                return x == ::std::numeric_limits<T>::infinity();
            }
        }

        template<::utils::Arithmetic T>
        constexpr static bool isInf(const T x) noexcept {
            return isNegInf(x) || isPosInf(x);
        }

        template<::utils::Arithmetic T>
        constexpr static bool isFinite(const T x) noexcept {
            return !isNan(x) && !isInf(x);
        }

        template<::utils::Arithmetic T>
        constexpr static bool isIndistinguishableFrom(const T x, const T from) noexcept {
            if constexpr (std::is_integral_v<T>) {
                return x == from;
            } else {
                return std::numeric_limits<T>::min() > abs(x - from);
            }
        }
        
        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> floor(const T x) noexcept {
            using FloatTy = CorrespondingFloat<T>;

            if constexpr (::std::is_integral_v<T>) {
                return FloatTy(x);
            } else {
                if (::std::is_constant_evaluated()) {
                    return isNan(x) ? ::std::numeric_limits<FloatTy>::quiet_NaN()
                        : isInf(x) ? x
                        : ::std::numeric_limits<FloatTy>::min() > abs(x) ? x
                        : floor_internal<FloatTy>(x);
                }

                return ::std::floor(x);
            }
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> ceil(const T x) noexcept {
            using FloatTy = CorrespondingFloat<T>;

            if constexpr (::std::is_integral_v<T>) {
                return FloatTy(x);
            } else {
                if (::std::is_constant_evaluated()) {
                    return isNan(x) ? ::std::numeric_limits<FloatTy>::quiet_NaN()
                        : isInf(x) ? x
                        : ::std::numeric_limits<FloatTy>::min() > abs(x) ? x
                        : ceil_internal<FloatTy>(x);
                }

                return ::std::ceil(x);
            }
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> exp(const T x) noexcept {
            if (::std::is_constant_evaluated()) {
                return exp_internal(static_cast<CorrespondingFloat<T>>(x));
            } else {
                return ::std::exp(x);
            }
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> log(const T x) noexcept {
            if (::std::is_constant_evaluated()) {
                return log_internal(x);
            } else {
                return ::std::log(x);
            }
        }

        template<::utils::Arithmetic T>
        constexpr static T sqrt(const T x) noexcept {
            if (::std::is_constant_evaluated()) {
                if constexpr (std::is_floating_point_v<T>) {
                    return isNan(x) ? ::std::numeric_limits<T>::quiet_NaN()
                        : isInf(x) ? x
                        : static_cast<T>(sqrt(x, x, 0));
                } else {
                    return static_cast<T>(sqrt(x, x, 0));
                }
            }

            return ::std::sqrt(x);
        }

        template<::utils::Arithmetic T>
        constexpr static T pow(const T x, const int32_t degree) noexcept {
            if (::std::is_constant_evaluated()) {
                return pow_internal(x, degree);
            }

            return static_cast<T>(::std::pow(x, degree));
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> atan(const T x) noexcept {
            if (::std::is_constant_evaluated()) {
                return atan_internal(x);
            }

            return ::std::atan(x);
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> acos(const T x) noexcept {
            if (::std::is_constant_evaluated()) {
                return acos_internal(x);
            }

            return ::std::acos(x);
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> tan(const T x) noexcept {
            if (::std::is_constant_evaluated()) {
                return tan_internal(x);
            } else {
                return ::std::tan(x);
            }
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> cos(const T x) noexcept {
            using R = CorrespondingFloat<T>;

            if (::std::is_constant_evaluated()) {
                return cos_check(static_cast<R>(x));
            } else {
                return ::std::cos(x);
            }
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> sin(const T x) noexcept {
            using R = CorrespondingFloat<T>;

            if (::std::is_constant_evaluated()) {
                return sin_check(static_cast<R>(x));
            } else {
                return ::std::sin(x);
            }
        }

    private:


        ///  IMPLEMENTATIONS  ///

        // Floor

        template<::utils::FloatingPoint FloatTy>
        constexpr static int floor_residual(const FloatTy x, const FloatTy x_whole) noexcept {
            return((x < FloatTy(0)) && (x < x_whole));
        }

        template<::utils::FloatingPoint FloatTy>
        constexpr static FloatTy floor_int(const FloatTy x, const FloatTy x_whole) noexcept {
            return(x_whole - static_cast<FloatTy>(floor_residual(x, x_whole)));
        }

        template<::utils::FloatingPoint FloatTy>
        constexpr static FloatTy floor_internal(const FloatTy x) noexcept {
            if constexpr (::std::is_same_v<FloatTy, long double>) {
                return abs(x) >= getMinValueWithoutPoint<FloatTy>() ? x
                    : floor_int(x, FloatTy(static_cast<::std::uintmax_t>(abs(x))) * sgn(x));
            }

            return abs(x) >= getMinValueWithoutPoint<FloatTy>() ? x
                   : floor_int(x, FloatTy(static_cast<CorrespondingInteger<FloatTy>>(x)));
        }

        // Ceil

        template<::utils::FloatingPoint FloatTy>
        constexpr static int ceil_residual(const FloatTy x, const FloatTy x_whole) noexcept {
            return((x > FloatTy(0)) && (x > x_whole));
        }

        template<::utils::FloatingPoint FloatTy>
        constexpr static FloatTy ceil_int(const FloatTy x, const FloatTy x_whole) noexcept {
            return(x_whole + static_cast<FloatTy>(ceil_residual(x, x_whole)));
        }

        template<::utils::FloatingPoint FloatTy>
        constexpr static FloatTy ceil_internal(const FloatTy x) noexcept {
            if constexpr (::std::is_same_v<FloatTy, long double>) {
                return abs(x) >= getMinValueWithoutPoint<FloatTy>() ? x
                    : ceil_int(x, FloatTy(static_cast<::std::uintmax_t>(abs(x))) * sgn(x));
            }

            return abs(x) >= getMinValueWithoutPoint<FloatTy>() ? x
                : ceil_int(x, FloatTy(static_cast<CorrespondingInteger<FloatTy>>(x)));
        }

        // Exp

        template<::utils::Arithmetic T>
        constexpr static T exp_recur(const T x, const int32_t depth_end) noexcept {
            int32_t depth = 24;
            T result = T(1);

            while (depth > depth_end - 1) {
                result = T(1) + x / T(depth - 1) - x / depth / result; // Wow
                --depth;
            }

            return result;
        }

        template<::utils::Arithmetic T>
        constexpr static T exp_compute(const T x) noexcept {
            return T(1) / (T(1) - x / exp_recur(x, 2));
        }

        template<::utils::Arithmetic T>
        constexpr static T exp_split(const T x) noexcept {
            return static_cast<T>(pow_integral(static_cast<T>(std::numbers::e), wholeOf(x))) * exp_compute(fractionOf(x));
        }

        template<::utils::Arithmetic T>
        constexpr static T exp_internal(const T x) noexcept {
            return isNan(x)
                    ? std::numeric_limits<T>::quiet_NaN()
                : isNegInf(x)
                    ? T(0)
                : isPosInf(x)
                    ? std::numeric_limits<T>::infinity()
                : isIndistinguishableFrom(x, T(0))
                    ? T(1)
                : abs(x) < T(2)
                    ? exp_compute(x)
                    : exp_split(x);
        }

        // Log

        template<::utils::Arithmetic T>
        constexpr static T log_compute_main(const T xx, const int32_t depth_end) noexcept {
            int32_t depth = 24;
            T result = T(2 * (depth + 1) - 1);

            while (depth > depth_end - 1) {
                result = T(2 * depth - 1) - T(depth*depth) * xx / result;
                --depth;
            }

            return result;
        }

        template<::utils::Arithmetic T>
        constexpr static T log_compute_begin(const T x) noexcept {
            return T(2) * x / log_compute_main(x * x, 1);
        }

        template<::utils::Arithmetic T>
        constexpr static T log_main(const T x) noexcept {
            return log_compute_begin((x - T(1)) / (x + T(1)));
        }

        constexpr static long double log_mantissa_int(const int32_t x) noexcept {
            return x == 2 ? 0.6931471805599453094172321214581765680755l :
                x == 3 ? 1.0986122886681096913952452369225257046475l :
                x == 4 ? 1.3862943611198906188344642429163531361510l :
                x == 5 ? 1.6094379124341003746007593332261876395256l :
                x == 6 ? 1.7917594692280550008124773583807022727230l :
                x == 7 ? 1.9459101490553133051053527434431797296371l :
                x == 8 ? 2.0794415416798359282516963643745297042265l :
                x == 9 ? 2.1972245773362193827904904738450514092950l :
                x == 10 ? 2.3025850929940456840179914546843642076011l :
                0.0l;
        }

        template<::utils::Arithmetic T>
        constexpr static T log_mantissa(const T x) noexcept {
            return log_main(x / T(static_cast<int32_t>(x))) + T(log_mantissa_int(static_cast<int32_t>(x)));
        }

        template<::utils::Arithmetic T>
        constexpr static T mantissa(const T x) noexcept {
            return x < T(1)
                    ? mantissa(x * T(10))
                : x > T(10)
                    ? mantissa(x / T(10))
                    : x;
        }

        template<::utils::Arithmetic T>
        constexpr static T log_breakup(const T x) noexcept {
            return log_mantissa(mantissa(x)) + T(std::numbers::log10e) * T(exponentOf(x, 0));
        }

        template<::utils::Arithmetic T>
        constexpr static T log_check(const T x) noexcept {
            return (isNan(x) || x < T(0))
                    ? std::numeric_limits<T>::quiet_NaN()
                : isIndistinguishableFrom(x, T(0))
                    ? -std::numeric_limits<T>::infinity()
                : isIndistinguishableFrom(x, T(1))
                    ? T(0)
                : isPosInf(x)
                    ? std::numeric_limits<T>::infinity()
                : (x < T(0.5) || x > T(1.5))
                    ? log_breakup(x)
                    : log_main(x);
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> log_internal(const T x) noexcept {
            using R = CorrespondingFloat<T>;
            
            if constexpr (std::is_integral_v<T>) {
                return x == T(0)
                        ? -std::numeric_limits<R>::infinity()
                    : x > T(1)
                        ? log_check(static_cast<T>(x))
                        : R(0);
            } else {
                return log_check(static_cast<R>(x));
            }
        }

        // Sqrt
        
        constexpr static double sqrt(const double x, const double curr, const double prev) noexcept { // Newton-Raphson
            return curr == prev
                ? curr
                : sqrt(x, 0.5 * (curr + x / curr), curr);
        }

        // Pow

        template<::utils::Arithmetic T>
        constexpr static T pow_compute(const T base, const T exp_term) noexcept {
            return exp(exp_term * log(base));
        }

        template<::utils::Arithmetic T, ::utils::Arithmetic Degree>
        constexpr static auto pow_internal(const T x, const Degree degree) noexcept {
            if constexpr (std::is_integral_v<Degree>) {
                return pow_integral(x, degree);
            } else {
                if (isWhole(degree)) {
                    return pow_integral(x, intmax_t(degree));
                } else if (x < T(0)) {
                    return std::numeric_limits<T>::quiet_NaN();
                } else {
                    using Common = CommonType<T, Degree>;
                    return pow_compute(static_cast<Common>(x), static_cast<Common>(degree));
                }
            }
        }

        // Pow for integral degrees

        template<::utils::Arithmetic T, ::std::integral Degree>
        constexpr static T pow_integral_recur(const T base, const T val, const Degree exp_term) noexcept {
            if (exp_term > Degree(1)) {
                return isOdd(exp_term)
                    ? pow_integral_recur(base * base, val * base, exp_term / 2)
                    : pow_integral_recur(base * base, val, exp_term / 2);
            } else {
                return exp_term == Degree(1)
                    ? val * base
                    : val; // exp_term == 0
            }
        }

        template<::utils::Arithmetic T, ::std::integral Degree>
        constexpr static T pow_integral_sgn_check(const T base, const Degree exp_term) noexcept {
            if constexpr (std::is_signed_v<Degree>) {
                return exp_term < Degree(0)
                    ? T(1) / pow_integral(base, -exp_term)
                    : pow_integral_recur(base, T(1), exp_term);
            } else {
                return pow_integral_recur(base, T(1), exp_term);
            }
        }

        template<::utils::Arithmetic T, ::std::integral Degree>
        constexpr static T pow_integral(const T base, const Degree exp_term) noexcept {
            if (exp_term == Degree(2)) {
                return base * base;
            } else if (exp_term == Degree(3)) {
                return base * base * base;
            } else if (exp_term == Degree(1)) {
                return base;
            } else if (exp_term == Degree(0)) {
                return T(1);
            } else if (exp_term == std::numeric_limits<Degree>::min()) {
                return T(0);
            } else if (exp_term == std::numeric_limits<Degree>::max()) {
                return std::numeric_limits<T>::infinity();
            } else {
                return pow_integral_sgn_check(base, exp_term);
            }
        }

        // Atan

        template<::utils::Arithmetic T>
        constexpr static T atan_series_order_calc(const T xx, const T x_pow, const uint32_t order) noexcept {
            return T(1) / (T((order - 1) * 4 - 1) * x_pow) - T(1) / (T((order - 1) * 4 + 1) * x_pow * xx); // ???
        }

        template<::utils::Arithmetic T>
        constexpr static T atan_series_order(const T x, const T x_pow, const uint32_t order_begin, const uint32_t max_order) noexcept {
            if (max_order == 1) {
                return (T(std::numbers::pi) / 2) - T(1) / x_pow;
            }

            T xx = x * x;
            T res = atan_series_order_calc(xx, pow(x, 4 * max_order - 5), max_order);

            uint32_t depth = max_order - 1;
            while (depth > order_begin) {
                res += atan_series_order_calc(xx, pow(x, 4 * depth - 5), depth);

                --depth;
            }

            res += (T(std::numbers::pi) / 2) - T(1) / x;

            return res;
        }

        template<::utils::Arithmetic T>
        constexpr static T atan_series_main(const T x) noexcept {
            return x < T(3) ? atan_series_order(x, x, 1U, 10U) : // Not that I understand what's going on...
                   x < T(4) ? atan_series_order(x, x, 1U, 9U) :
                   x < T(5) ? atan_series_order(x, x, 1U, 8U) :
                   x < T(7) ? atan_series_order(x, x, 1U, 7U) :
                   x < T(11) ? atan_series_order(x, x, 1U, 6U) :
                   x < T(25) ? atan_series_order(x, x, 1U, 5U) :
                   x < T(100) ? atan_series_order(x, x, 1U, 4U) :
                   x < T(1000) ? atan_series_order(x, x, 1U, 3U) :
                   atan_series_order(x, x, 1U, 2U);
        }

        template<::utils::Arithmetic T>
        constexpr static T atan_cf_recur(const T xx, const uint32_t depth_begin, const uint32_t max_depth) noexcept {
            uint32_t depth = max_depth - 1;
            T res = T(2 * (depth + 1) - 1);

            while (depth > depth_begin - 1) {
                res = T(2 * depth - 1) + T(depth * depth) * xx / res;

                --depth;
            }

            return res;
        }

        template<::utils::Arithmetic T>
        constexpr static T atan_cf_main(const T x) noexcept {
            return x < T(0.5) ? x / atan_cf_recur(x * x, 1U, 15U) :
                   x < T(1) ? x / atan_cf_recur(x * x, 1U, 25U) :
                   x < T(1.5) ? x / atan_cf_recur(x * x, 1U, 35U) :
                   x < T(2) ? x / atan_cf_recur(x * x, 1U, 45U) :
                   x / atan_cf_recur(x * x, 1U, 52U);
        }

        template<::utils::Arithmetic T>
        constexpr static T atan_begin(const T x) noexcept {
            return x > T(2.5) ? atan_series_main(x) : atan_cf_main(x);
        }

        template<::utils::Arithmetic T>
        constexpr static T atan_internal(const T x) noexcept {
            return isNan(x) 
                    ? ::std::numeric_limits<T>::quiet_NaN()
                : isIndistinguishableFrom(x, T(0))
                    ? T(0)
                : x < T(0) 
                    ? -atan_begin(-x)
                    : atan_begin(x);
        }

        // Acos

        template<::utils::Arithmetic T>
        constexpr static T acos_compute(const T x) noexcept {
            return abs(x) > T(1) 
                    ? ::std::numeric_limits<T>::quiet_NaN()
                : isIndistinguishableFrom(x, T(1))
                    ? T(0)
                : isIndistinguishableFrom(x, T(0))
                    ? T(::std::numbers::pi / 2)
                    : atan(sqrt(T(1) - x * x) / x);
        }

        template<::utils::Arithmetic T>
        constexpr static T acos_internal(const T x) noexcept {
            return isNan(x) 
                    ? ::std::numeric_limits<T>::quiet_NaN()
                : x > T(0) 
                    ? acos_compute(x)
                    : T(::std::numbers::pi) - acos_compute(-x);
        }

        // Tan

        template<::utils::Arithmetic T>
        constexpr static T tan_series_exp_long(const T x) noexcept {
            return -1 / x + x / 3 + pow_integral(x, 3) / 45 + 2 * pow_integral(x, 5) / 945 + pow_integral(x, 7) / 4725;
        }

        template<::utils::Arithmetic T>
        constexpr static T tan_series_exp(const T x) noexcept {
            return std::numeric_limits<T>::min() > abs(x - T(std::numbers::pi / 2))
                ? T(1.633124e+16)
                : tan_series_exp_long(x - T(std::numbers::pi / 2));
        }

        template<::utils::Arithmetic T>
        constexpr static T tan_compute_recur(const T xx, const int32_t depth, const int32_t max_depth) noexcept {
            return depth < max_depth
                ? T(2 * depth - 1) - xx / tan_compute_recur(xx, depth + 1, max_depth)
                : T(2 * depth - 1);
        }

        template<::utils::Arithmetic T>
        constexpr static T tan_compute_main(const T x) noexcept {
            return x > T(1.55) && x < T(1.6)
                    ? tan_series_exp(x)
                : x > T(1.4)
                    ? x / tan_compute_recur(x * x, 1, 45)
                : x > T(1)
                    ? x / tan_compute_recur(x * x, 1, 35)
                    : x / tan_compute_recur(x * x, 1, 25);
        }

        template<::utils::Arithmetic T>
        constexpr static T tan_begin(const T x, const int32_t count = 0) noexcept {
            return x > T(std::numbers::pi_v<T>)
                ? count > 1
                    ? std::numeric_limits<T>::quiet_NaN()
                    : tan_begin(x - T(std::numbers::pi_v<T>) * floor(x / T(std::numbers::pi_v<T>)), count + 1)
                : tan_compute_main(x);
        }

        template<::utils::Arithmetic T>
        constexpr static T tan_check(const T x) noexcept {
            return isNan(x)
                    ? std::numeric_limits<T>::quiet_NaN()
                : isIndistinguishableFrom(x, T(0))
                    ? T(0)
                : x < T(0)
                    ? -tan_begin(-x)
                    : tan_begin(x);
        }

        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> tan_internal(const T x) noexcept {
            return tan_check(static_cast<CorrespondingFloat<T>>(x));
        }

        // Cos

        template<::utils::Arithmetic T>
        constexpr static T cos_compute(const T x) noexcept {
            const T xx = x * x;
            return (T(1) - xx) / (T(1) + xx);
        }

        template<::utils::Arithmetic T>
        constexpr static T cos_check(const T x) noexcept {
            return isNan(x)
                    ? std::numeric_limits<T>::quiet_NaN()
                : isIndistinguishableFrom(x, T(0))
                    ? T(1)
                : (isIndistinguishableFrom(x, T(std::numbers::pi_v<T> / 2))
                   || isIndistinguishableFrom(x, T(-std::numbers::pi_v<T> / 2)))
                    ? T(0)
                : (isIndistinguishableFrom(x, T(std::numbers::pi_v<T>))
                   || isIndistinguishableFrom(x, T(-std::numbers::pi_v<T>)))
                    ? T(-1)
                    : cos_compute(tan(x / T(2)));
        }

        // Sin

        template<::utils::Arithmetic T>
        constexpr static T sin_compute(const T x) noexcept {
            return T(2) * x / (T(1) + x*x);
        }

        template<::utils::Arithmetic T>
        constexpr static T sin_check(const T x) noexcept {
            return isNan(x)
                    ? std::numeric_limits<T>::quiet_NaN()
                : isIndistinguishableFrom(x, T(0))
                    ? T(0)
                : isIndistinguishableFrom(x, T(std::numbers::pi_v<T> / 2))
                    ? T(1)
                : isIndistinguishableFrom(x, T(-std::numbers::pi_v<T> / 2))
                    ? -T(1)
                : isIndistinguishableFrom(x, T(std::numbers::pi_v<T>))
                    ? T(0)
                : isIndistinguishableFrom(x, T(-std::numbers::pi_v<T>))
                    ? -T(0)
                    : sin_compute(tan(x / T(2)));
        }
    };
}
