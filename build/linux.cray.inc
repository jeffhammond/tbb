# Copyright (c) 2005-2017 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
#
#

COMPILE_ONLY = -c -MMD
PREPROC_ONLY = -E -x c++
INCLUDE_KEY = -I
DEFINE_KEY = -D
OUTPUT_KEY = -o #
OUTPUTOBJ_KEY = -o #
PIC_KEY = -h PIC -fPIC
WARNING_AS_ERROR_KEY = -h error_on_warning
WARNING_KEY =
DYLIB_KEY = -shared -DCRAYPE_LINK_TYPE=shared
EXPORT_KEY = -Wl,--version-script,
NOINTRINSIC_KEY = -h nointrinsics
LIBDL = -ldl

CPLUS = CC
CONLY = cc

ITT_NOTIFY = -DDO_ITT_NOTIFY
ifeq (release,$(cfg))
CPLUS_FLAGS = $(ITT_NOTIFY) -O2 -g -DUSE_PTHREAD
else
CPLUS_FLAGS = $(ITT_NOTIFY) -O0 -g -DUSE_PTHREAD -DTBB_USE_DEBUG
endif

LIB_LINK_FLAGS = -shared -Wl,-soname=$(BUILDING_LIBRARY) -z relro -z now
LIBS += -lpthread -lrt
LINK_FLAGS = -rdynamic
C_FLAGS = $(CPLUS_FLAGS)

OPENMP_FLAG = -h omp

ifeq (intel64,$(arch))
    ITT_NOTIFY = -DDO_ITT_NOTIFY
    CPLUS_FLAGS += -m64
    LIB_LINK_FLAGS += -m64
endif

TBB_ASM.OBJ=
MALLOC_ASM.OBJ=

#------------------------------------------------------------------------------
# Setting assembler data.
#------------------------------------------------------------------------------
ASM = as
ifeq (intel64,$(arch))
    ASM_FLAGS += --64
endif
ifeq (ia32,$(arch))
    ASM_FLAGS += --32
endif
ifeq ($(cfg),debug)
    ASM_FLAGS += -g
endif

ASSEMBLY_SOURCE=$(arch)-gas
ifeq (ia64,$(arch))
    ASM_FLAGS += -xexplicit
    TBB_ASM.OBJ += atomic_support.o lock_byte.o log2.o pause.o ia64_misc.o
    MALLOC_ASM.OBJ += atomic_support.o lock_byte.o pause.o log2.o
endif
#------------------------------------------------------------------------------
# End of setting assembler data.
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# Setting tbbmalloc data.
#------------------------------------------------------------------------------

M_CPLUS_FLAGS = $(CPLUS_FLAGS) -fno-rtti -fno-exceptions

#------------------------------------------------------------------------------
# End of setting tbbmalloc data.
#------------------------------------------------------------------------------

