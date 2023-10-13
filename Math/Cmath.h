// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once
#include <cmath>
#include <limits>
#include <numbers>
#include <type_traits>

#include "Utils/Concepts.h"
#include "Types.h"

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

        template<::utils::FloatingPoint FloatTy>
        constexpr static bool isNan(const FloatTy x) noexcept {
            return x != x;
        }

        template<::utils::FloatingPoint FloatTy>
        constexpr static bool isInf(const FloatTy x) noexcept {
            return x == ::std::numeric_limits<FloatTy>::infinity()
                || x == -::std::numeric_limits<FloatTy>::infinity();
        }

        template<::utils::FloatingPoint FloatTy>
        constexpr static bool isFinite(const FloatTy x) noexcept {
            return !isNan(x) && !isInf(x);
        }
        
        template<::utils::Arithmetic T>
        constexpr static CorrespondingFloat<T> floor(const T x) noexcept {
            using FloatTy = CorrespondingFloat<T>;

            if constexpr (::std::is_integral_v<T>) {
                return FloatTy(x);
            }

            if (::std::is_constant_evaluated()) {
                return isNan(x) ? ::std::numeric_limits<FloatTy>::quiet_NaN()
                    : isInf(x) ? x
                    : ::std::numeric_limits<FloatTy>::min() > abs(x) ? x
                    : floor_internal<FloatTy>(x);
            }

            return ::std::floor(x);
        }

        // Allows compile-time sqrt
        template<::utils::Arithmetic T>
        constexpr static T sqrt(const T x) noexcept {
            if (::std::is_constant_evaluated()) {
                return static_cast<T>(sqrt(x, x, 0));
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

    private:
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
        
        constexpr static double sqrt(const double x, const double curr, const double prev) noexcept { // Newton-Raphson
            return curr == prev
                ? curr
                : sqrt(x, 0.5 * (curr + x / curr), curr);
        }

        template<::utils::Arithmetic T>
        constexpr static T pow_internal(const T x, const int32_t degree) noexcept {
            if (degree == 0) {
                return static_cast<T>(1);
            }

            T tmp = pow(x, degree / 2);

            return tmp * tmp * (degree % 2 ? x : 1);
        }

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
            return isNan(x) ? ::std::numeric_limits<T>::quiet_NaN()
                   : ::std::numeric_limits<T>::min() > abs(x) ? T(0)
                   : x < T(0) ? -atan_begin(-x)
                   : atan_begin(x);
        }

        template<::utils::Arithmetic T>
        constexpr static T acos_compute(const T x) noexcept {
            return abs(x) > T(1) ? ::std::numeric_limits<T>::quiet_NaN()
                   : ::std::numeric_limits<T>::min() > abs(x - T(1)) ? T(0)
                   : ::std::numeric_limits<T>::min() > abs(x) ? T(::std::numbers::pi / 2)
                   : atan(sqrt(T(1) - x * x) / x);
        }

        template<::utils::Arithmetic T>
        constexpr static T acos_internal(const T x) noexcept {
            return isNan(x) ? ::std::numeric_limits<T>::quiet_NaN()
                   : x > T(0) ? acos_compute(x)
                   : T(::std::numbers::pi) - acos_compute(-x);
        }
    };
}
