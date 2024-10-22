/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/api.hpp"

#include "roq/flags/args.hpp"

#include "roq/logging/flags/settings.hpp"

#include "roq/algo/playground/application.hpp"

using namespace std::literals;

// === CONSTANTS ===

namespace {
auto const INFO = roq::Service::Info{
    .description = "Arbitrage"sv,
    .package_name = ROQ_PACKAGE_NAME,
    .build_version = ROQ_VERSION,
};
}  // namespace

// === IMPLEMENTATION ===

int main(int argc, char **argv) {
  roq::flags::Args args{argc, argv, INFO.description, INFO.build_version};
  roq::logging::flags::Settings settings{args};
  return roq::algo::playground::Application{args, settings, INFO}.run();
}