/* Copyright (c) 2017-2025, Hans Erik Thrane */

#include <pybind11/pybind11.h>

#include "roq/algo/reporter.hpp"

#include "roq/utils/common.hpp"

#include "roq/python/core/convert.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

using namespace std::literals;

namespace py = pybind11;

// === CONSTANTS ===

namespace {
auto const MODULE_DOC = R"pbdoc(
Pybind11 example plugin
-----------------------

.. currentmodule:: playground

.. autosummary::
:toctree: _generate

add
subtract
)pbdoc";

}  // namespace

// === HELPERS ===

namespace {
int add(int lhs, int rhs) {
  return lhs + rhs;
}

auto const ADD_DOC = R"pbdoc(
Add two numbers

Some other explanation about the add function.
                          )pbdoc";

std::unique_ptr<roq::algo::Reporter> create_my_reporter() {
  return {};
};
}  // namespace

// === IMPLEMENTATION ===

PYBIND11_MODULE(ROQ_PACKAGE_NAME, module) {
  module.doc() = MODULE_DOC;

  module.def("add", &add, ADD_DOC);

  module.def("create_my_reporter", &create_my_reporter);

  module.def("foo", [](roq::Side side) { return roq::utils::invert(side); });

#ifdef VERSION_INFO
  module.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  module.attr("__version__") = "dev";
#endif

  [[maybe_unused]] auto module_2 = py::module::import("roq");
}
