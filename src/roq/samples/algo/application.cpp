/* Copyright (c) 2017-2025, Hans Erik Thrane */

#include "roq/samples/algo/application.hpp"

#include "roq/utils/enum.hpp"

#include "roq/client/simulator.hpp"
#include "roq/client/trader.hpp"

using namespace std::literals;

namespace roq {
namespace samples {
namespace algo {

// === HELPERS ===

namespace {
void validate_params(auto &config, auto &params) {
  uint8_t max_source = {};
  for (auto &item : config.legs) {
    assert(item.source < SOURCE_MAX);
    max_source = std::max(max_source, item.source);
  }
  auto required = static_cast<size_t>(max_source) + 1;
  if (std::size(params) != required) {
    log::error("You must provide {} argument(s)! (got {})"sv, required, std::size(params));
    log::error("  For live trading: paths to unix sockets (the .sock files created by the gateways)"sv);
    log::error("  For simulation: paths to event-logs (the .roq files created by the gateways)"sv);
    log::fatal("Unexpected"sv);
  }
}
}  // namespace

// === IMPLEMENTATION ===

int Application::main(args::Parser const &args) {
  auto params = args.params();

  Settings settings{args};
  Config config{settings};

  validate_params(static_cast<roq::algo::strategy::Config const &>(config), params);

  Factory factory{settings, config};

  if (settings.simulate) {
    simulate(settings, factory, config, params);
  } else {
    trade(settings, factory, config, params);
  }

  return EXIT_SUCCESS;
}

void Application::simulate(Settings const &settings, Factory const &factory, Config const &config, std::span<std::string_view const> const &params) {
  auto output_type = utils::parse_enum<roq::algo::reporter::OutputType>(settings.simulation.reporter_output_type);
  auto reporter = client::Simulator::dispatch(settings, factory, config, config, params);
  (*reporter).print(output_type, settings.simulation.reporter_label);
}

void Application::trade(Settings const &settings, Factory const &factory, Config const &config, std::span<std::string_view const> const &params) {
  client::Trader2::dispatch(settings, factory, config, params);
}

}  // namespace algo
}  // namespace samples
}  // namespace roq
