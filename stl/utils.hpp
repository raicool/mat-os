#pragma once

#include "stl.hpp"
#include "types.hpp"

namespace STL_NS {

namespace concepts {

namespace STL_NS_IMPL {

template <class T> inline constexpr bool is_integral = false;
template <> inline constexpr bool is_integral<u8> = true;
template <> inline constexpr bool is_integral<i8> = true;
template <> inline constexpr bool is_integral<u16> = true;
template <> inline constexpr bool is_integral<i16> = true;
template <> inline constexpr bool is_integral<u32> = true;
template <> inline constexpr bool is_integral<i32> = true;
template <> inline constexpr bool is_integral<u64> = true;
template <> inline constexpr bool is_integral<i64> = true;

}

template <class T>
concept integral = STL_NS_IMPL::is_integral<T>;

}

namespace types {

namespace STL_NS_IMPL {

template <class T> struct remove_cv { using type = T; };
template <class T> struct remove_cv<const T> { using type = T; };
template <class T> struct remove_cv<volatile T> { using type = T; };
template <class T> struct remove_cv<const volatile T> { using type = T; };

template <class T> struct remove_ref { using type = T; };
template <class T> struct remove_ref<T&> { using type = T; };
template <class T> struct remove_ref<T&&> { using type = T; };

template <class T> struct remove_ptr { using type = T; };
template <class T> struct remove_ptr<T*> { using type = T; };

template <class T> struct remove_array { using type = T; };
template <class T, usize N> struct remove_array<T[N]> { using type = T*; };
template <class T, usize N> struct remove_array<T(&)[N]> { using type = T*; };

template <class T> struct to_signed { using type = T; };
template <> struct to_signed<u8>  { using type = i8; };
template <> struct to_signed<u16> { using type = i16; };
template <> struct to_signed<u32> { using type = i32; };
template <> struct to_signed<u64> { using type = i64; };

template <class T> struct to_unsigned { using type = T; };
template <> struct to_unsigned<i8>  { using type = u8; };
template <> struct to_unsigned<i16> { using type = u16; };
template <> struct to_unsigned<i32> { using type = u32; };
template <> struct to_unsigned<i64> { using type = u64; };

}

template <class T>
using remove_cv = typename STL_NS_IMPL::remove_cv<T>::type;

template <class T>
using remove_ref = typename STL_NS_IMPL::remove_ref<T>::type;

template <class T>
using remove_cv_ref = remove_cv<remove_ref<T>>;

template <class T>
using remove_ptr = typename STL_NS_IMPL::remove_ptr<T>::type;

template <class T>
using decay = remove_cv_ref<typename STL_NS_IMPL::remove_array<T>::type>;

template <class T, class V>
static constexpr bool is_same = false;

template <class T>
static constexpr bool is_same<T, T> = true;

template <class T, class... Others>
static constexpr bool is_one_of = (is_same<T, Others> || ...);

template <class T>
static constexpr bool is_pointer = false;

template <class T>
static constexpr bool is_pointer<T*> = true;

template <concepts::integral Int>
static constexpr bool is_signed = is_same<Int, typename STL_NS_IMPL::to_signed<Int>::type>;

template <concepts::integral Int>
static constexpr bool is_unsigned = !is_signed<Int>;

template <concepts::integral Int>
using to_signed = typename STL_NS_IMPL::to_signed<Int>::type;

template <concepts::integral Int>
using to_unsigned = typename STL_NS_IMPL::to_unsigned<Int>::type;

}

template <class First, class Second>
struct Pair {
	First first;
	Second second;
};

}