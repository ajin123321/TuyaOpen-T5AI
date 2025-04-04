// Copyright 2020-2021 Beken
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <driver/mailbox_types.h>

void  mailbox_interrupt_enable(mailbox_endpoint_t src);
void  mailbox_interrupt_disable(mailbox_endpoint_t src);
#if CONFIG_SOC_BK7239_SMP_TEMP
void core_mbox_interrupt_enable(uint32 core_id, mailbox_endpoint_t src);
void core_mbox_interrupt_disable(uint32 core_id, mailbox_endpoint_t src);
#endif

