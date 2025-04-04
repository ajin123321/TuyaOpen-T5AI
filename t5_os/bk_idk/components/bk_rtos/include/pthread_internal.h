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
#if !defined PTHREAD_INTERNAL_H
#define PTHREAD_INTERNAL_H
#if (CONFIG_SOC_BK7256XX)
	typedef unsigned int pthread_key_t;
#endif
typedef void (*pthread_destructor_t)(void*);

int pthread_setspecific(pthread_key_t key, const void *value);
void *pthread_getspecific(pthread_key_t key);
#endif /*PTHREAD_INTERNAL_H*/