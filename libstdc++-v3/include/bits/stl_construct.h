// nonstandard construct and destroy functions -*- C++ -*-

// Please review $(srcdir/SPL-README) for GNU licencing info.

/** @file bits/stl_construct.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{memory}
 */

#ifndef _STL_CONSTRUCT_H
#define _STL_CONSTRUCT_H 1

#include <new>
#include <bits/move.h>
#include <bits/stl_iterator_base_types.h> // for iterator_traits
#include <bits/stl_iterator_base_funcs.h> // for advance

/* This file provides the C++17 functions std::destroy_at, std::destroy, and
 * std::destroy_n, and the C++20 function std::construct_at.
 * It also provides std::_Construct, std::_Destroy,and std::_Destroy_n functions
 * which are defined in all standard modes and so can be used in C++98-14 code.
 * The _Destroy functions will dispatch to destroy_at during constant
 * evaluation, because calls to that function are intercepted by the compiler
 * to allow use in constant expressions.
 */

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

#if __cplusplus >= 201703L
  template <typename _Tp>
    _GLIBCXX20_CONSTEXPR inline void
    destroy_at(_Tp* __location)
    {
      if constexpr (__cplusplus > 201703L && is_array_v<_Tp>)
	{
	  for (auto& __x : *__location)
	    std::destroy_at(std::__addressof(__x));
	}
      else
	__location->~_Tp();
    }

#if __cplusplus >= 202002L
  template<typename _Tp, typename... _Args>
    constexpr auto
    construct_at(_Tp* __location, _Args&&... __args)
    noexcept(noexcept(::new((void*)0) _Tp(std::declval<_Args>()...)))
    -> decltype(::new((void*)0) _Tp(std::declval<_Args>()...))
    { return ::new((void*)__location) _Tp(std::forward<_Args>(__args)...); }
#endif // C++20
#endif// C++17

  /**
   * Constructs an object in existing memory by invoking an allocated
   * object's constructor with an initializer.
   */
#if __cplusplus >= 201103L
  template<typename _Tp, typename... _Args>
    _GLIBCXX20_CONSTEXPR
    inline void
    _Construct(_Tp* __p, _Args&&... __args)
    {
#if __cplusplus >= 202002L
      if (std::__is_constant_evaluated())
	{
	  // Allow std::_Construct to be used in constant expressions.
	  std::construct_at(__p, std::forward<_Args>(__args)...);
	  return;
	}
#endif
      ::new((void*)__p) _Tp(std::forward<_Args>(__args)...);
    }
#else
  template<typename _T1, typename _T2>
    inline void
    _Construct(_T1* __p, const _T2& __value)
    {
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 402. wrong new expression in [some_]allocator::construct
      ::new(static_cast<void*>(__p)) _T1(__value);
    }
#endif

  template<typename _T1>
    inline void
    _Construct_novalue(_T1* __p)
    { ::new((void*)__p) _T1; }

  template<typename _ForwardIterator>
    _GLIBCXX20_CONSTEXPR void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last);

  /**
   * Destroy the object pointed to by a pointer type.
   */
  template<typename _Tp>
    _GLIBCXX14_CONSTEXPR inline void
    _Destroy(_Tp* __pointer)
    {
#if __cplusplus > 201703L
      std::destroy_at(__pointer);
#else
      __pointer->~_Tp();
#endif
    }

  template<bool>
    struct _Destroy_aux
    {
      template<typename _ForwardIterator>
	static _GLIBCXX20_CONSTEXPR void
	__destroy(_ForwardIterator __first, _ForwardIterator __last)
	{
	  for (; __first != __last; ++__first)
	    std::_Destroy(std::__addressof(*__first));
	}
    };

  template<>
    struct _Destroy_aux<true>
    {
      template<typename _ForwardIterator>
        static void
        __destroy(_ForwardIterator, _ForwardIterator) { }
    };

  /**
   * Destroy a range of objects.  If the value_type of the object has
   * a trivial destructor, the compiler should optimize all of this
   * away, otherwise the objects' destructors must be invoked.
   */
  template<typename _ForwardIterator>
    _GLIBCXX20_CONSTEXPR inline void
    _Destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
                       _Value_type;
#if __cplusplus >= 201103L
      // A deleted destructor is trivial, this ensures we reject such types:
      static_assert(is_destructible<_Value_type>::value,
		    "value type is destructible");
#endif
#if __cplusplus >= 202002L
      if (std::__is_constant_evaluated())
	return _Destroy_aux<false>::__destroy(__first, __last);
#endif
      std::_Destroy_aux<__has_trivial_destructor(_Value_type)>::
	__destroy(__first, __last);
    }

  template<bool>
    struct _Destroy_n_aux
    {
      template<typename _ForwardIterator, typename _Size>
	static _GLIBCXX20_CONSTEXPR _ForwardIterator
	__destroy_n(_ForwardIterator __first, _Size __count)
	{
	  for (; __count > 0; (void)++__first, --__count)
	    std::_Destroy(std::__addressof(*__first));
	  return __first;
	}
    };

  template<>
    struct _Destroy_n_aux<true>
    {
      template<typename _ForwardIterator, typename _Size>
        static _ForwardIterator
        __destroy_n(_ForwardIterator __first, _Size __count)
	{
	  std::advance(__first, __count);
	  return __first;
	}
    };

  /**
   * Destroy a range of objects.  If the value_type of the object has
   * a trivial destructor, the compiler should optimize all of this
   * away, otherwise the objects' destructors must be invoked.
   */
  template<typename _ForwardIterator, typename _Size>
    _GLIBCXX20_CONSTEXPR inline _ForwardIterator
    _Destroy_n(_ForwardIterator __first, _Size __count)
    {
      typedef typename iterator_traits<_ForwardIterator>::value_type
                       _Value_type;
#if __cplusplus >= 201103L
      // A deleted destructor is trivial, this ensures we reject such types:
      static_assert(is_destructible<_Value_type>::value,
		    "value type is destructible");
#endif
#if __cplusplus >= 202002L
      if (std::__is_constant_evaluated())
	return _Destroy_n_aux<false>::__destroy_n(__first, __count);
#endif
      return std::_Destroy_n_aux<__has_trivial_destructor(_Value_type)>::
	__destroy_n(__first, __count);
    }

#if __cplusplus >= 201703L
  template <typename _ForwardIterator>
    _GLIBCXX20_CONSTEXPR inline void
    destroy(_ForwardIterator __first, _ForwardIterator __last)
    {
      std::_Destroy(__first, __last);
    }

  template <typename _ForwardIterator, typename _Size>
    _GLIBCXX20_CONSTEXPR inline _ForwardIterator
    destroy_n(_ForwardIterator __first, _Size __count)
    {
      return std::_Destroy_n(__first, __count);
    }
#endif // C++17

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace std

#endif /* _STL_CONSTRUCT_H */
