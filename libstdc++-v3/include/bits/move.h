// Move, forward and identity for C++11 + swap -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/move.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{utility}
 */

#ifndef _MOVE_H
#define _MOVE_H 1

#include <bits/c++config.h>
#if __cplusplus < 201103L
# include <bits/concept_check.h>
#endif

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  // Used, in C++03 mode too, by allocators, etc.
  /**
   *  @brief Same as C++11 std::addressof
   *  @ingroup utilities
   */
  template<typename _Tp>
    inline _GLIBCXX_CONSTEXPR _Tp*
    __addressof(_Tp& __r) _GLIBCXX_NOEXCEPT
    { return __builtin_addressof(__r); }

#if __cplusplus >= 201103L

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

#include <type_traits> // Brings in std::declval too.

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

  /**
   *  @addtogroup utilities
   *  @{
   */

  /**
   *  @brief  Forward an lvalue.
   *  @return The parameter cast to the specified type.
   *
   *  This function is used to implement "perfect forwarding".
   */
  template<typename _Tp>
    _GLIBCXX_NODISCARD
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type& __t) noexcept
    { return static_cast<_Tp&&>(__t); }

  /**
   *  @brief  Forward an rvalue.
   *  @return The parameter cast to the specified type.
   *
   *  This function is used to implement "perfect forwarding".
   */
  template<typename _Tp>
    _GLIBCXX_NODISCARD
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type&& __t) noexcept
    {
      static_assert(!std::is_lvalue_reference<_Tp>::value,
	  "std::forward must not be used to convert an rvalue to an lvalue");
      return static_cast<_Tp&&>(__t);
    }

  /**
   *  @brief  Convert a value to an rvalue.
   *  @param  __t  A thing of arbitrary type.
   *  @return The parameter cast to an rvalue-reference to allow moving it.
  */
  template<typename _Tp>
    _GLIBCXX_NODISCARD
    constexpr typename std::remove_reference<_Tp>::type&&
    move(_Tp&& __t) noexcept
    { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }


  template<typename _Tp>
    struct __move_if_noexcept_cond
    : public __and_<__not_<is_nothrow_move_constructible<_Tp>>,
                    is_copy_constructible<_Tp>>::type { };

  /**
   *  @brief  Conditionally convert a value to an rvalue.
   *  @param  __x  A thing of arbitrary type.
   *  @return The parameter, possibly cast to an rvalue-reference.
   *
   *  Same as std::move unless the type's move constructor could throw and the
   *  type is copyable, in which case an lvalue-reference is returned instead.
   */
  template<typename _Tp>
    _GLIBCXX_NODISCARD
    constexpr
    __conditional_t<__move_if_noexcept_cond<_Tp>::value, const _Tp&, _Tp&&>
    move_if_noexcept(_Tp& __x) noexcept
    { return std::move(__x); }

  // declval, from type_traits.

#if __cplusplus > 201402L
  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 2296. std::addressof should be constexpr
# define __cpp_lib_addressof_constexpr 201603L
#endif
  /**
   *  @brief Returns the actual address of the object or function
   *         referenced by r, even in the presence of an overloaded
   *         operator&.
   *  @param  __r  Reference to an object or function.
   *  @return   The actual address.
  */
  template<typename _Tp>
    _GLIBCXX_NODISCARD
    inline _GLIBCXX17_CONSTEXPR _Tp*
    addressof(_Tp& __r) noexcept
    { return std::__addressof(__r); }

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 2598. addressof works on temporaries
  template<typename _Tp>
    const _Tp* addressof(const _Tp&&) = delete;

  // C++11 version of std::exchange for internal use.
  template <typename _Tp, typename _Up = _Tp>
    _GLIBCXX20_CONSTEXPR
    inline _Tp
    __exchange(_Tp& __obj, _Up&& __new_val)
    {
      _Tp __old_val = std::move(__obj);
      __obj = std::forward<_Up>(__new_val);
      return __old_val;
    }

  /// @} group utilities

#define _GLIBCXX_FWDREF(_Tp) _Tp&&
#define _GLIBCXX_MOVE(__val) std::move(__val)
#define _GLIBCXX_FORWARD(_Tp, __val) std::forward<_Tp>(__val)
#else
#define _GLIBCXX_FWDREF(_Tp) const _Tp&
#define _GLIBCXX_MOVE(__val) (__val)
#define _GLIBCXX_FORWARD(_Tp, __val) (__val)
#endif

  /**
   *  @addtogroup utilities
   *  @{
   */

  /**
   *  @brief Swaps two values.
   *  @param  __a  A thing of arbitrary type.
   *  @param  __b  Another thing of arbitrary type.
   *  @return   Nothing.
  */
  template<typename _Tp>
    _GLIBCXX20_CONSTEXPR
    inline
#if __cplusplus >= 201103L
    typename enable_if<__and_<__not_<__is_tuple_like<_Tp>>,
			      is_move_constructible<_Tp>,
			      is_move_assignable<_Tp>>::value>::type
#else
    void
#endif
    swap(_Tp& __a, _Tp& __b)
    _GLIBCXX_NOEXCEPT_IF(__and_<is_nothrow_move_constructible<_Tp>,
				is_nothrow_move_assignable<_Tp>>::value)
    {
#if __cplusplus < 201103L
      // concept requirements
      __glibcxx_function_requires(_SGIAssignableConcept<_Tp>)
#endif
      _Tp __tmp = _GLIBCXX_MOVE(__a);
      __a = _GLIBCXX_MOVE(__b);
      __b = _GLIBCXX_MOVE(__tmp);
    }

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // DR 809. std::swap should be overloaded for array types.
  /// Swap the contents of two arrays.
  template<typename _Tp, size_t _Nm>
    _GLIBCXX20_CONSTEXPR
    inline
#if __cplusplus >= 201103L
    typename enable_if<__is_swappable<_Tp>::value>::type
#else
    void
#endif
    swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm])
    _GLIBCXX_NOEXCEPT_IF(__is_nothrow_swappable<_Tp>::value)
    {
      for (size_t __n = 0; __n < _Nm; ++__n)
	swap(__a[__n], __b[__n]);
    }

  /// @} group utilities
_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

#endif /* _MOVE_H */
