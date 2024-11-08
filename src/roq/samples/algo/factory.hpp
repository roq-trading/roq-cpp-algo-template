/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include "roq/client.hpp"

#include "roq/algo/market_data_source.hpp"

#include "roq/algo/matcher/type.hpp"

#include "roq/samples/algo/config.hpp"
#include "roq/samples/algo/settings.hpp"

namespace roq {
namespace samples {
namespace algo {

struct Factory final : public client::Simulator2::Factory {
  Factory(Settings const &, Config const &);

  std::unique_ptr<roq::algo::Strategy> create_strategy(
      roq::algo::Strategy::Dispatcher &, roq::algo::OrderCache &, roq::algo::strategy::Config const &) const override;

  std::unique_ptr<roq::algo::Reporter> create_reporter() const override;

  std::unique_ptr<roq::algo::Matcher> create_matcher(
      roq::algo::Matcher::Dispatcher &, roq::algo::OrderCache &, roq::algo::matcher::Config const &) const override;

 private:
  Settings const &settings_;
  Config const &config_;
  roq::algo::matcher::Type const matcher_type_;
  roq::algo::MarketDataSource const market_data_source_;
};

}  // namespace algo
}  // namespace samples
}  // namespace roq
