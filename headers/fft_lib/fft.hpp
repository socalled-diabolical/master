#pragma once

#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

namespace math {
namespace fft {

namespace {
template <std::ranges::range R> auto to_vector(R &&r) {
  std::vector<std::ranges::range_value_t<R>> v;

  // if we can get a size, reserve that much
  if constexpr (requires { std::ranges::size(r); }) {
    v.reserve(std::ranges::size(r));
  }

  // push all the elements
  for (auto &&e : r) {
    v.push_back(static_cast<decltype(e) &&>(e));
  }

  return v;
}
} // namespace

template <typename T>
std::complex<T> complex_exponent_to_sin_cos(const T &angle) {
  return std::complex<T>(std::cos(angle), std::sin(angle));
}

template <typename T> class FFTInternals {

public:
  T base_exp;

  FFTInternals(const auto &len) {
    base_exp = complex_exponent_to_sin_cos<double>(2 * std::numbers::pi / len);
  }

  std::vector<T> run(const std::vector<T> &seq, const T &base_exp) {

    if (seq.size() == 0) {
      throw std::logic_error("Trying to fft a vector of size = 0");
    }

    auto even_index = [index = 0](auto val) mutable {
      if (index % 2 == 0) {
        ++index;
        return true;
      }
      ++index;
      return false;
    };

    auto evens = seq | std::views::filter(even_index);
    auto odds = seq | std::views::drop(1) | std::views::filter(even_index);

    if (std::distance(evens.begin(), evens.end()) == 1) {
      return to_vector(evens);
    }

    auto evens_fft = run(to_vector(evens), base_exp * base_exp);
    auto odds_fft = run(to_vector(odds), base_exp * base_exp);

    std::vector<T> fft;

    auto iteven = evens_fft.begin();
    auto itodd = odds_fft.begin();
    auto itevene = evens_fft.end();
    auto itodde = odds_fft.end();
    auto exp = base_exp;

    for (; iteven != itevene; ++iteven, ++itodd) {
      auto val = *iteven + exp * (*itodd);

      exp *= base_exp;
      fft.push_back(val);
    }

    iteven = evens_fft.begin();
    itodd = odds_fft.begin();
    itevene = evens_fft.end();
    itodde = odds_fft.end();
    exp = base_exp;

    for (; iteven != itevene; ++iteven, ++itodd) {
      auto val = *iteven - exp * (*itodd);

      exp *= base_exp;
      fft.push_back(val);
    }

    return fft;
  }
};

namespace {
template <typename T> std::vector<T> conj(const std::vector<T> &seq) {
  std::vector<T> conj;

  for (auto &&x : seq) {
    conj.push_back(std::conj(x));
  }

  return conj;
}
} // namespace

template <typename T> std::vector<T> fft(const std::vector<T> &seq) {
  FFTInternals<T> _internals(std::distance(seq.begin(), seq.end()));
  auto val = _internals.run(seq, _internals.base_exp);

  return val;
}

template <typename T> std::vector<T> ifft(const std::vector<T> &seq) {

  FFTInternals<T> _internals(std::distance(seq.begin(), seq.end()));

  auto val = conj(_internals.run(conj(seq), _internals.base_exp));
  return val;
}

} // namespace fft
} // namespace math
