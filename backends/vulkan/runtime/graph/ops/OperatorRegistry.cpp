/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <executorch/backends/vulkan/runtime/graph/ops/OperatorRegistry.h>

#include <executorch/backends/vulkan/runtime/graph/ops/impl/Arithmetic.h>

namespace at {
namespace native {
namespace vulkan {

bool OperatorRegistry::has_op(const std::string& name) {
  return OperatorRegistry::kTable.count(name) > 0;
}

OperatorRegistry::OpFunction& OperatorRegistry::get_op_fn(
    const std::string& name) {
  return OperatorRegistry::kTable.find(name)->second;
}

// @lint-ignore-every CLANGTIDY modernize-avoid-bind
// clang-format off
#define OPERATOR_ENTRY(name, function) \
  { #name, std::bind(&function, std::placeholders::_1, std::placeholders::_2) }
// clang-format on

const OperatorRegistry::OpTable OperatorRegistry::kTable = {
    OPERATOR_ENTRY(aten.add.Tensor, add),
    OPERATOR_ENTRY(aten.sub.Tensor, sub),
    OPERATOR_ENTRY(aten.mul.Tensor, mul),
    OPERATOR_ENTRY(aten.div.Tensor, div),
    OPERATOR_ENTRY(aten.div.Tensor_mode, floor_div),
    OPERATOR_ENTRY(aten.pow.Tensor_Tensor, pow),
};

OperatorRegistry& operator_registry() {
  static OperatorRegistry registry;
  return registry;
}

} // namespace vulkan
} // namespace native
} // namespace at
