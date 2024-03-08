#pragma once
#include <cmath>
#include <complex>
#include <vector>

#define PRECISION 1e-10

namespace math {
namespace fft {

template <typename T>
std::complex<T> complex_exponent_to_sin_cos(const T &angle) {
  return std::complex<T>(std::cos(angle), -std::sin(angle));
}

template <typename T> class FFTInternals {

public:
  T base_exp;

  FFTInternals(const auto &points) {
    base_exp =
        complex_exponent_to_sin_cos<double>(2 * std::numbers::pi / points);
  }

  std::vector<T> run(const std::vector<T> &seq, const T &base_exp) {
    if (seq.size() == 0) {
      throw std::logic_error("Trying to fft a vector of size = 0");
    } else if (seq.size() == 1) {
      return seq;
    }

    std::vector<T> evens;
    std::vector<T> odds;

    size_t i = 0;
    for (; i < seq.size(); ++i) {
      if (i % 2 == 0) {
        evens.push_back(seq[i]);
      } else {
        odds.push_back(seq[i]);
      }
    }

    auto evens_fft = run(evens, base_exp * base_exp);
    auto odds_fft = run(odds, base_exp * base_exp);

    std::vector<T> fft;

    auto iteven = evens_fft.begin();
    auto itodd = odds_fft.begin();
    auto itevene = evens_fft.end();
    auto itodde = odds_fft.end();
    auto exp = T(1);

    for (; iteven != itevene; ++iteven, ++itodd) {
      auto val = *iteven + exp * (*itodd);
      exp *= base_exp;
      fft.push_back(val);
    }

    iteven = evens_fft.begin();
    itodd = odds_fft.begin();
    itevene = evens_fft.end();
    itodde = odds_fft.end();
    exp = T(1);

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
  FFTInternals<T> _internals(seq.size());
  auto val = _internals.run(seq, _internals.base_exp);

  return val;
}

template <typename T> std::vector<T> ifft(const std::vector<T> &seq) {
  FFTInternals<T> _internals(seq.size());
  auto val = conj(_internals.run(conj(seq), _internals.base_exp));

  for (size_t i = 0; i < seq.size(); ++i) {
    if (val[i].real() > PRECISION && val[i].imag() > PRECISION)
      val[i] = T(val[i] / T(seq.size()));
    else if (val[i].real() > PRECISION) {
      val[i] = T(val[i].real() / T(seq.size()));
    } else if (val[i].imag() > PRECISION) {
      val[i] = T(val[i].imag() / T(seq.size()));
    } else
      val[i] = 0;
  }

  return val;
}

} // namespace fft
} // namespace math
