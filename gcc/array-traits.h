/* Descriptions of array-like objects.
   Please review: $(src-dir)/SPL-README for Licencing info. */

#ifndef GCC_ARRAY_TRAITS_H
#define GCC_ARRAY_TRAITS_H

/* Implementation for single integers (and similar types).  */
template<typename T, T zero = T (0)>
struct scalar_array_traits
{
  typedef T element_type;
  static const bool has_constant_size = true;
  static const size_t constant_size = 1;
  static const T *base (const T &x) { return &x; }
  static size_t size (const T &) { return 1; }
};

template<typename T>
struct array_traits : scalar_array_traits<T> {};

/* Implementation for arrays with a static size.  */
template<typename T, size_t N>
struct array_traits<T[N]>
{
  typedef T element_type;
  static const bool has_constant_size = true;
  static const size_t constant_size = N;
  static const T *base (const T (&x)[N]) { return x; }
  static size_t size (const T (&)[N]) { return N; }
};

#endif
