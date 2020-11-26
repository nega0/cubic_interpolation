#include <cstdlib>
#include <iostream>
#include <memory>

#include "BicubicSplines.h"
#include "CubicSplines.h"
#include "Utility.h"

float func1dim(float x) { return x * x + x; }
float func2dim(float x, float y) { return x * x + y * y; }

int main() {
  auto def1d = CubicSplines::Definition();
  def1d.f = func1dim;
  def1d.axis = std::make_unique<LinAxis>(-2.f, 2.f, (size_t)10);
  auto inter1d = Interpolant<CubicSplines>(std::move(def1d), "", "");
  auto function_value = 1.f;
  auto guess = 0.5f;

  auto x = FindParameter(inter1d, function_value, guess);
  std::cout << "f(x) = " << function_value << " -> x = " << x << std::endl;

  auto def2d = BicubicSplines::Definition();
  def2d.f = func2dim;
  def2d.axis[0] = std::make_unique<LinAxis>(1.e-5f, 1.e1f, (size_t)10);
  def2d.axis[1] = std::make_unique<LinAxis>(1.e-5f, 1.e1f, (size_t)10);
  auto inter2d = Interpolant<BicubicSplines>(std::move(def2d), "", "");

  function_value = 42.f;
  auto x_val = 0.5f;
  auto y_guess = 3.f;
  auto searched_param = 1;
  auto y = FindParameter(inter2d, function_value,
                    std::array<float, 2>{x_val, y_guess}, searched_param);
  std::cout << "f(x="<< x_val <<",y) = " << function_value << " -> y = " << y << std::endl;
  return 0;
}
