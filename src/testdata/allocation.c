#define ZIG_TARGET_MAX_INT_ALIGNMENT 16
#include "zig.h"
struct slice_u8_51 { /* [:0]const u8 */
 uint8_t const *ptr;
 size_t len;
};
typedef uint8_t enum__builtin_OutputMode_147; /* builtin.OutputMode */
struct mem_Allocator_VTable_206;
struct mem_Allocator_203 { /* mem.Allocator */
 void *ptr;
 struct mem_Allocator_VTable_206 const *vtable;
};
zig_static_assert(sizeof (struct mem_Allocator_203) == 16, "incorrect size");
zig_static_assert(_Alignof (struct mem_Allocator_203) == 8, "incorrect alignment");
struct slice_u8_50 { /* []const u8 */
 uint8_t const *ptr zig_nonstring;
 size_t len;
};
struct slice_u8_216 { /* []u8 */
 uint8_t *ptr zig_nonstring;
 size_t len;
};
struct allocation_Pair_214 { /* allocation.Pair */
 struct slice_u8_216 first;
 struct slice_u8_216 second;
};
zig_static_assert(sizeof (struct allocation_Pair_214) == 32, "incorrect size");
zig_static_assert(_Alignof (struct allocation_Pair_214) == 8, "incorrect alignment");
struct arr_32_u8_189 { uint8_t array[32] zig_nonstring; }; /* [32]u8 */
zig_static_assert(sizeof (struct arr_32_u8_189) == 32, "incorrect size");
zig_static_assert(_Alignof (struct arr_32_u8_189) == 1, "incorrect alignment");
struct arr_2_opt_ptr_u8_193 { uint8_t *array[2]; }; /* [2]?[*]u8 */
zig_static_assert(sizeof (struct arr_2_opt_ptr_u8_193) == 16, "incorrect size");
zig_static_assert(_Alignof (struct arr_2_opt_ptr_u8_193) == 8, "incorrect alignment");
struct verifier_FailingAllocator_2832_2c2_29_187 { /* verifier.FailingAllocator(32,2) */
 zig_align(16) struct arr_32_u8_189 buffer;
 uintptr_t used;
 struct arr_2_opt_ptr_u8_193 live;
};
zig_static_assert(sizeof (struct verifier_FailingAllocator_2832_2c2_29_187) == 64, "incorrect size");
zig_static_assert(_Alignof (struct verifier_FailingAllocator_2832_2c2_29_187) == 16, "incorrect alignment");
struct arr_2s116_u8_223 { uint8_t array[3]; }; /* [2:0]u8 */
zig_static_assert(sizeof (struct arr_2s116_u8_223) == 3, "incorrect size");
zig_static_assert(_Alignof (struct arr_2s116_u8_223) == 1, "incorrect alignment");
typedef uint8_t enum__mem_Alignment_261; /* mem.Alignment */
typedef uint8_t *fn__Pptr_anyopaque_Pusize_Pmem_Alignment_Pusize_Ropt_ptr_u8_264(void *, uintptr_t, enum__mem_Alignment_261, uintptr_t); /* fn (*anyopaque, usize, mem.Alignment, usize) ?[*]u8 */
typedef bool fn__Pptr_anyopaque_Pslice_u8_Pmem_Alignment_Pusize_Pusize_Rbool_266(void *, struct slice_u8_216, enum__mem_Alignment_261, uintptr_t, uintptr_t); /* fn (*anyopaque, []u8, mem.Alignment, usize, usize) bool */
typedef uint8_t *fn__Pptr_anyopaque_Pslice_u8_Pmem_Alignment_Pusize_Pusize_Ropt_ptr_u8_268(void *, struct slice_u8_216, enum__mem_Alignment_261, uintptr_t, uintptr_t); /* fn (*anyopaque, []u8, mem.Alignment, usize, usize) ?[*]u8 */
typedef void fn__Pptr_anyopaque_Pslice_u8_Pmem_Alignment_Pusize_Rvoid_270(void *, struct slice_u8_216, enum__mem_Alignment_261, uintptr_t); /* fn (*anyopaque, []u8, mem.Alignment, usize) void */
struct mem_Allocator_VTable_206 { /* mem.Allocator.VTable */
 fn__Pptr_anyopaque_Pusize_Pmem_Alignment_Pusize_Ropt_ptr_u8_264 *alloc;
 fn__Pptr_anyopaque_Pslice_u8_Pmem_Alignment_Pusize_Pusize_Rbool_266 *resize;
 fn__Pptr_anyopaque_Pslice_u8_Pmem_Alignment_Pusize_Pusize_Ropt_ptr_u8_268 *remap;
 fn__Pptr_anyopaque_Pslice_u8_Pmem_Alignment_Pusize_Rvoid_270 *free;
};
zig_static_assert(sizeof (struct mem_Allocator_VTable_206) == 32, "incorrect size");
zig_static_assert(_Alignof (struct mem_Allocator_VTable_206) == 8, "incorrect alignment");
struct arr_5_usize_748 { uintptr_t array[5]; }; /* [5]usize */
zig_static_assert(sizeof (struct arr_5_usize_748) == 40, "incorrect size");
zig_static_assert(_Alignof (struct arr_5_usize_748) == 8, "incorrect alignment");
struct Target_Cpu_Feature_Set_737 { /* Target.Cpu.Feature.Set */
 struct arr_5_usize_748 ints;
};
zig_static_assert(sizeof (struct Target_Cpu_Feature_Set_737) == 40, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_Feature_Set_737) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Cpu_Arch_730; /* Target.Cpu.Arch */
struct Target_Cpu_Model_732;
struct Target_Cpu_720 { /* Target.Cpu */
 struct Target_Cpu_Model_732 const *model;
 struct Target_Cpu_Feature_Set_737 features;
 enum__Target_Cpu_Arch_730 arch;
};
zig_static_assert(sizeof (struct Target_Cpu_720) == 56, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_720) == 8, "incorrect alignment");
struct Target_Cpu_Model_732 { /* Target.Cpu.Model */
 struct slice_u8_50 name;
 struct slice_u8_51 llvm_name;
 struct Target_Cpu_Feature_Set_737 features;
};
zig_static_assert(sizeof (struct Target_Cpu_Model_732) == 72, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_Model_732) == 8, "incorrect alignment");
struct SemanticVersion_755 { /* SemanticVersion */
 uintptr_t major;
 uintptr_t minor;
 uintptr_t patch;
 struct slice_u8_50 pre;
 struct slice_u8_50 build;
};
zig_static_assert(sizeof (struct SemanticVersion_755) == 56, "incorrect size");
zig_static_assert(_Alignof (struct SemanticVersion_755) == 8, "incorrect alignment");
struct SemanticVersion_Range_757 { /* SemanticVersion.Range */
 struct SemanticVersion_755 zig_e_min;
 struct SemanticVersion_755 zig_e_max;
};
zig_static_assert(sizeof (struct SemanticVersion_Range_757) == 112, "incorrect size");
zig_static_assert(_Alignof (struct SemanticVersion_Range_757) == 8, "incorrect alignment");
struct Target_Os_HurdVersionRange_759 { /* Target.Os.HurdVersionRange */
 struct SemanticVersion_Range_757 range;
 struct SemanticVersion_755 glibc;
};
zig_static_assert(sizeof (struct Target_Os_HurdVersionRange_759) == 168, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_HurdVersionRange_759) == 8, "incorrect alignment");
struct Target_Os_LinuxVersionRange_761 { /* Target.Os.LinuxVersionRange */
 struct SemanticVersion_Range_757 range;
 struct SemanticVersion_755 glibc;
 uint32_t android;
};
zig_static_assert(sizeof (struct Target_Os_LinuxVersionRange_761) == 176, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_LinuxVersionRange_761) == 8, "incorrect alignment");
typedef uint32_t enum__Target_Os_WindowsVersion_763; /* Target.Os.WindowsVersion */
struct Target_Os_WindowsVersion_Range_765 { /* Target.Os.WindowsVersion.Range */
 enum__Target_Os_WindowsVersion_763 zig_e_min;
 enum__Target_Os_WindowsVersion_763 zig_e_max;
};
zig_static_assert(sizeof (struct Target_Os_WindowsVersion_Range_765) == 8, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_WindowsVersion_Range_765) == 4, "incorrect alignment");
typedef uint8_t enum___40typeInfo_28Target_Os_VersionRange_29__40_22union_22_tag_type__3f_753; /* @typeInfo(Target.Os.VersionRange).@"union".tag_type.? */
struct Target_Os_VersionRange_751 { /* Target.Os.VersionRange */
 union {
  struct SemanticVersion_Range_757 semver;
  struct Target_Os_HurdVersionRange_759 hurd;
  struct Target_Os_LinuxVersionRange_761 linux;
  struct Target_Os_WindowsVersion_Range_765 windows;
 } payload;
 enum___40typeInfo_28Target_Os_VersionRange_29__40_22union_22_tag_type__3f_753 tag;
};
zig_static_assert(sizeof (struct Target_Os_VersionRange_751) == 184, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_VersionRange_751) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Os_Tag_749; /* Target.Os.Tag */
struct Target_Os_722 { /* Target.Os */
 struct Target_Os_VersionRange_751 version_range;
 enum__Target_Os_Tag_749 tag;
};
zig_static_assert(sizeof (struct Target_Os_722) == 192, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_722) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Abi_724; /* Target.Abi */
typedef uint8_t enum__Target_ObjectFormat_726; /* Target.ObjectFormat */
struct arr_255_u8_822 { uint8_t array[255] zig_nonstring; }; /* [255]u8 */
zig_static_assert(sizeof (struct arr_255_u8_822) == 255, "incorrect size");
zig_static_assert(_Alignof (struct arr_255_u8_822) == 1, "incorrect alignment");
struct Target_DynamicLinker_728 { /* Target.DynamicLinker */
 struct arr_255_u8_822 buffer;
 uint8_t len;
};
zig_static_assert(sizeof (struct Target_DynamicLinker_728) == 256, "incorrect size");
zig_static_assert(_Alignof (struct Target_DynamicLinker_728) == 1, "incorrect alignment");
struct Target_718 { /* Target */
 struct Target_Cpu_720 cpu;
 struct Target_Os_722 os;
 enum__Target_Abi_724 abi;
 enum__Target_ObjectFormat_726 ofmt;
 struct Target_DynamicLinker_728 dynamic_linker;
};
zig_static_assert(sizeof (struct Target_718) == 512, "incorrect size");
zig_static_assert(_Alignof (struct Target_718) == 8, "incorrect alignment");
struct opt_u64_427 { /* ?u64 */
 uint64_t payload;
 bool is_null;
};
zig_static_assert(sizeof (struct opt_u64_427) == 16, "incorrect size");
zig_static_assert(_Alignof (struct opt_u64_427) == 8, "incorrect alignment");
struct builtin_CallingConvention_CommonOptions_411 { /* builtin.CallingConvention.CommonOptions */
 struct opt_u64_427 incoming_stack_alignment;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_CommonOptions_411) == 16, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_CommonOptions_411) == 8, "incorrect alignment");
struct builtin_CallingConvention_X86RegparmOptions_413 { /* builtin.CallingConvention.X86RegparmOptions */
 struct opt_u64_427 incoming_stack_alignment;
 uint8_t register_params;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_X86RegparmOptions_413) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_X86RegparmOptions_413) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ArmInterruptOptions_InterruptType_428; /* builtin.CallingConvention.ArmInterruptOptions.InterruptType */
struct builtin_CallingConvention_ArmInterruptOptions_415 { /* builtin.CallingConvention.ArmInterruptOptions */
 struct opt_u64_427 incoming_stack_alignment;
 enum__builtin_CallingConvention_ArmInterruptOptions_InterruptType_428 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ArmInterruptOptions_415) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ArmInterruptOptions_415) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_MipsInterruptOptions_InterruptMode_437; /* builtin.CallingConvention.MipsInterruptOptions.InterruptMode */
struct builtin_CallingConvention_MipsInterruptOptions_417 { /* builtin.CallingConvention.MipsInterruptOptions */
 struct opt_u64_427 incoming_stack_alignment;
 enum__builtin_CallingConvention_MipsInterruptOptions_InterruptMode_437 mode;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_MipsInterruptOptions_417) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_MipsInterruptOptions_417) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_RiscvInterruptOptions_PrivilegeMode_449; /* builtin.CallingConvention.RiscvInterruptOptions.PrivilegeMode */
struct builtin_CallingConvention_RiscvInterruptOptions_419 { /* builtin.CallingConvention.RiscvInterruptOptions */
 struct opt_u64_427 incoming_stack_alignment;
 enum__builtin_CallingConvention_RiscvInterruptOptions_PrivilegeMode_449 mode;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_RiscvInterruptOptions_419) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_RiscvInterruptOptions_419) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ArcInterruptOptions_InterruptType_451; /* builtin.CallingConvention.ArcInterruptOptions.InterruptType */
struct builtin_CallingConvention_ArcInterruptOptions_421 { /* builtin.CallingConvention.ArcInterruptOptions */
 struct opt_u64_427 incoming_stack_alignment;
 enum__builtin_CallingConvention_ArcInterruptOptions_InterruptType_451 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ArcInterruptOptions_421) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ArcInterruptOptions_421) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_MicroblazeInterruptOptions_InterruptType_454; /* builtin.CallingConvention.MicroblazeInterruptOptions.InterruptType */
struct builtin_CallingConvention_MicroblazeInterruptOptions_423 { /* builtin.CallingConvention.MicroblazeInterruptOptions */
 struct opt_u64_427 incoming_stack_alignment;
 enum__builtin_CallingConvention_MicroblazeInterruptOptions_InterruptType_454 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_MicroblazeInterruptOptions_423) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_MicroblazeInterruptOptions_423) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ShInterruptOptions_SaveBehavior_456; /* builtin.CallingConvention.ShInterruptOptions.SaveBehavior */
struct builtin_CallingConvention_ShInterruptOptions_425 { /* builtin.CallingConvention.ShInterruptOptions */
 struct opt_u64_427 incoming_stack_alignment;
 enum__builtin_CallingConvention_ShInterruptOptions_SaveBehavior_456 save;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ShInterruptOptions_425) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ShInterruptOptions_425) == 8, "incorrect alignment");
typedef uint8_t enum___40typeInfo_28builtin_CallingConvention_29__40_22union_22_tag_type__3f_312; /* @typeInfo(builtin.CallingConvention).@"union".tag_type.? */
struct builtin_CallingConvention_310 { /* builtin.CallingConvention */
 union {
  struct builtin_CallingConvention_CommonOptions_411 x86_64_sysv;
  struct builtin_CallingConvention_CommonOptions_411 x86_64_x32;
  struct builtin_CallingConvention_CommonOptions_411 x86_64_win;
  struct builtin_CallingConvention_CommonOptions_411 x86_64_regcall_v3_sysv;
  struct builtin_CallingConvention_CommonOptions_411 x86_64_regcall_v4_win;
  struct builtin_CallingConvention_CommonOptions_411 x86_64_vectorcall;
  struct builtin_CallingConvention_CommonOptions_411 x86_64_interrupt;
  struct builtin_CallingConvention_X86RegparmOptions_413 x86_sysv;
  struct builtin_CallingConvention_X86RegparmOptions_413 x86_win;
  struct builtin_CallingConvention_X86RegparmOptions_413 x86_stdcall;
  struct builtin_CallingConvention_CommonOptions_411 x86_fastcall;
  struct builtin_CallingConvention_CommonOptions_411 x86_thiscall;
  struct builtin_CallingConvention_CommonOptions_411 x86_thiscall_mingw;
  struct builtin_CallingConvention_CommonOptions_411 x86_regcall_v3;
  struct builtin_CallingConvention_CommonOptions_411 x86_regcall_v4_win;
  struct builtin_CallingConvention_CommonOptions_411 x86_vectorcall;
  struct builtin_CallingConvention_CommonOptions_411 x86_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 x86_16_cdecl;
  struct builtin_CallingConvention_CommonOptions_411 x86_16_stdcall;
  struct builtin_CallingConvention_CommonOptions_411 x86_16_regparmcall;
  struct builtin_CallingConvention_CommonOptions_411 x86_16_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 aarch64_aapcs;
  struct builtin_CallingConvention_CommonOptions_411 aarch64_aapcs_darwin;
  struct builtin_CallingConvention_CommonOptions_411 aarch64_aapcs_win;
  struct builtin_CallingConvention_CommonOptions_411 aarch64_vfabi;
  struct builtin_CallingConvention_CommonOptions_411 aarch64_vfabi_sve;
  struct builtin_CallingConvention_CommonOptions_411 alpha_osf;
  struct builtin_CallingConvention_CommonOptions_411 arm_aapcs;
  struct builtin_CallingConvention_CommonOptions_411 arm_aapcs_vfp;
  struct builtin_CallingConvention_ArmInterruptOptions_415 arm_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 mips64_n64;
  struct builtin_CallingConvention_CommonOptions_411 mips64_n32;
  struct builtin_CallingConvention_MipsInterruptOptions_417 mips64_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 mips_o32;
  struct builtin_CallingConvention_MipsInterruptOptions_417 mips_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 riscv64_lp64;
  struct builtin_CallingConvention_CommonOptions_411 riscv64_lp64_v;
  struct builtin_CallingConvention_RiscvInterruptOptions_419 riscv64_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 riscv32_ilp32;
  struct builtin_CallingConvention_CommonOptions_411 riscv32_ilp32_v;
  struct builtin_CallingConvention_RiscvInterruptOptions_419 riscv32_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 sparc64_sysv;
  struct builtin_CallingConvention_CommonOptions_411 sparc_sysv;
  struct builtin_CallingConvention_CommonOptions_411 powerpc64_elf;
  struct builtin_CallingConvention_CommonOptions_411 powerpc64_elf_altivec;
  struct builtin_CallingConvention_CommonOptions_411 powerpc64_elf_v2;
  struct builtin_CallingConvention_CommonOptions_411 powerpc_sysv;
  struct builtin_CallingConvention_CommonOptions_411 powerpc_sysv_altivec;
  struct builtin_CallingConvention_CommonOptions_411 powerpc_aix;
  struct builtin_CallingConvention_CommonOptions_411 powerpc_aix_altivec;
  struct builtin_CallingConvention_CommonOptions_411 wasm_mvp;
  struct builtin_CallingConvention_CommonOptions_411 arc_sysv;
  struct builtin_CallingConvention_ArcInterruptOptions_421 arc_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 bpf_std;
  struct builtin_CallingConvention_CommonOptions_411 csky_sysv;
  struct builtin_CallingConvention_CommonOptions_411 csky_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 hexagon_sysv;
  struct builtin_CallingConvention_CommonOptions_411 hexagon_sysv_hvx;
  struct builtin_CallingConvention_CommonOptions_411 hppa_elf;
  struct builtin_CallingConvention_CommonOptions_411 hppa64_elf;
  struct builtin_CallingConvention_CommonOptions_411 kvx_lp64;
  struct builtin_CallingConvention_CommonOptions_411 kvx_ilp32;
  struct builtin_CallingConvention_CommonOptions_411 lanai_sysv;
  struct builtin_CallingConvention_CommonOptions_411 loongarch64_lp64;
  struct builtin_CallingConvention_CommonOptions_411 loongarch32_ilp32;
  struct builtin_CallingConvention_CommonOptions_411 m68k_sysv;
  struct builtin_CallingConvention_CommonOptions_411 m68k_gnu;
  struct builtin_CallingConvention_CommonOptions_411 m68k_rtd;
  struct builtin_CallingConvention_CommonOptions_411 m68k_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 microblaze_std;
  struct builtin_CallingConvention_MicroblazeInterruptOptions_423 microblaze_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 msp430_eabi;
  struct builtin_CallingConvention_CommonOptions_411 msp430_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 or1k_sysv;
  struct builtin_CallingConvention_CommonOptions_411 propeller_sysv;
  struct builtin_CallingConvention_CommonOptions_411 s390x_sysv;
  struct builtin_CallingConvention_CommonOptions_411 s390x_sysv_vx;
  struct builtin_CallingConvention_CommonOptions_411 sh_gnu;
  struct builtin_CallingConvention_CommonOptions_411 sh_renesas;
  struct builtin_CallingConvention_ShInterruptOptions_425 sh_interrupt;
  struct builtin_CallingConvention_CommonOptions_411 ve_sysv;
  struct builtin_CallingConvention_CommonOptions_411 xcore_xs1;
  struct builtin_CallingConvention_CommonOptions_411 xcore_xs2;
  struct builtin_CallingConvention_CommonOptions_411 xtensa_call0;
  struct builtin_CallingConvention_CommonOptions_411 xtensa_windowed;
  struct builtin_CallingConvention_CommonOptions_411 amdgcn_device;
  struct builtin_CallingConvention_CommonOptions_411 amdgcn_cs;
 } payload;
 enum___40typeInfo_28builtin_CallingConvention_29__40_22union_22_tag_type__3f_312 tag;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_310) == 32, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_310) == 8, "incorrect alignment");
typedef uint32_t enum__failure_Kind_1604; /* failure.Kind */
struct tuple_2_usize_u1_671088641 { /* struct { usize, u1 } */
 uintptr_t f0;
 uint8_t f1;
};
zig_static_assert(sizeof (struct tuple_2_usize_u1_671088641) == 16, "incorrect size");
zig_static_assert(_Alignof (struct tuple_2_usize_u1_671088641) == 8, "incorrect alignment");
struct slice_u8_1670 { /* []align(1) u8 */
 uint8_t *ptr zig_nonstring;
 size_t len;
};
struct arr_8_u8_1821 { uint8_t array[8] zig_nonstring; }; /* [8]u8 */
zig_static_assert(sizeof (struct arr_8_u8_1821) == 8, "incorrect size");
zig_static_assert(_Alignof (struct arr_8_u8_1821) == 1, "incorrect alignment");
struct arr_6s116_u8_1875 { uint8_t array[7]; }; /* [6:0]u8 */
zig_static_assert(sizeof (struct arr_6s116_u8_1875) == 7, "incorrect size");
zig_static_assert(_Alignof (struct arr_6s116_u8_1875) == 1, "incorrect alignment");
typedef uint64_t enum__builtin_CompilerBackend_2025; /* builtin.CompilerBackend */
struct errunion_allocation_Pair_214 { /* anyerror!allocation.Pair */
 struct allocation_Pair_214 payload;
 uint16_t error;
};
struct errunion_slice_u8_216 { /* anyerror![]u8 */
 struct slice_u8_216 payload;
 uint16_t error;
};
struct errunion_slice_u8_1670 { /* anyerror![]align(1) u8 */
 struct slice_u8_1670 payload;
 uint16_t error;
};
struct errunion_ptr_u8_1669 { /* anyerror![*]align(1) u8 */
 uint8_t *payload zig_nonstring;
 uint16_t error;
};
struct errunion_usize_16 { /* anyerror!usize */
 uintptr_t payload;
 uint16_t error;
};
#define allocation_free_twice_is_caught__220 free_twice_is_caught
zig_extern void free_twice_is_caught(void);
#define allocation_dupe_pair_without_errdefer_never_leaks__219 dupe_pair_without_errdefer_never_leaks
zig_extern void dupe_pair_without_errdefer_never_leaks(void);
#define allocation_dupe_pair_never_leaks__218 dupe_pair_never_leaks
zig_extern void dupe_pair_never_leaks(void);
static struct arr_2s116_u8_223 const __anon_224;
static struct arr_2s116_u8_223 const __anon_229;
static struct mem_Allocator_VTable_206 const __anon_624;
static struct arr_6s116_u8_1875 const __anon_1876;
static enum__builtin_OutputMode_147 const builtin_output_mode__225;
static struct errunion_allocation_Pair_214 allocation_dupePair__215(struct mem_Allocator_203 a0, struct slice_u8_50 a1, struct slice_u8_50 a2);
static struct mem_Allocator_203 verifier_FailingAllocator_2832_2c2_29_allocator__301(struct verifier_FailingAllocator_2832_2c2_29_187 *a0);
static void allocation_freeTwice__217(struct mem_Allocator_203 a0, struct allocation_Pair_214 a1);
static struct Target_Cpu_Feature_Set_737 const Target_Cpu_Feature_Set_empty__1161;
static struct Target_Cpu_720 const builtin_cpu__231;
static struct Target_Os_722 const builtin_os__232;
static enum__Target_Abi_724 const builtin_abi__230;
static enum__Target_ObjectFormat_726 const builtin_object_format__234;
static struct Target_718 const builtin_target__233;
static struct builtin_CallingConvention_310 const builtin_CallingConvention_c__849;
zig_extern void verifier_any(void *a0, uintptr_t a1);
static void verifier_FailingAllocator_2832_2c2_29_free__306(void *a0, struct slice_u8_216 a1, enum__mem_Alignment_261 a2, uintptr_t a3);
static uint8_t *verifier_FailingAllocator_2832_2c2_29_remap__305(void *a0, struct slice_u8_216 a1, enum__mem_Alignment_261 a2, uintptr_t a3, uintptr_t a4);
zig_extern zig_noreturn void verifier_fail(uint32_t a0, uintptr_t a1, uintptr_t a2);
static zig_cold zig_noreturn void panic_fail__974(enum__failure_Kind_1604 a0, uintptr_t a1, uintptr_t a2);
static zig_noreturn void panic_incorrectAlignment__985(void);
static zig_noreturn void panic_noreturnReturned__1000(void);
static bool verifier_FailingAllocator_2832_2c2_29_resize__304(void *a0, struct slice_u8_216 a1, enum__mem_Alignment_261 a2, uintptr_t a3, uintptr_t a4);
static uint8_t *verifier_FailingAllocator_2832_2c2_29_alloc__303(void *a0, uintptr_t a1, enum__mem_Alignment_261 a2, uintptr_t a3);
static void mem_Allocator_free__anon_253__638(struct mem_Allocator_203 a0, struct slice_u8_216 a1);
static zig_noreturn void panic_outOfBounds__978(uintptr_t a0, uintptr_t a1);
static enum__mem_Alignment_261 mem_Alignment_fromByteUnits__640(uintptr_t a0);
static struct slice_u8_216 mem_absorbSentinel__anon_1699__1327(struct slice_u8_216 a0);
static zig_noreturn void panic_invalidEnumValue__996(void);
static void debug_assert__160(bool a0);
static bool math_isPowerOfTwo__anon_1720__1328(uintptr_t a0);
static zig_noreturn void panic_reachedUnreachable__982(void);
static zig_noreturn void panic_integerOverflow__988(void);
static uintptr_t mem_Alignment_forward__647(enum__mem_Alignment_261 a0, uintptr_t a1);
static uintptr_t mem_Alignment_toByteUnits__639(enum__mem_Alignment_261 a0);
static bool verifier_any__anon_1655__1326(void);
static struct errunion_slice_u8_216 mem_Allocator_dupe__anon_244__637(struct mem_Allocator_203 a0, struct slice_u8_50 a1);
static uint8_t verifier_any__anon_1734__1329(void);
static zig_noreturn void panic_memcpyAlias__999(void);
static zig_noreturn void panic_copyLenMismatch__998(void);
static struct errunion_slice_u8_216 mem_Allocator_alloc__anon_1742__1330(struct mem_Allocator_203 a0, uintptr_t a1);
static struct errunion_ptr_u8_1669 mem_Allocator_allocWithSizeAndAlignment__anon_1776__1331(struct mem_Allocator_203 a0, uintptr_t a1, uintptr_t a2);
static struct errunion_usize_16 math_mul__anon_1786__1332(uintptr_t a0, uintptr_t a1);
static struct errunion_ptr_u8_1669 mem_Allocator_allocBytesWithAlignment__anon_1793__1333(struct mem_Allocator_203 a0, uintptr_t a1, uintptr_t a2);
static struct errunion_allocation_Pair_214 allocation_dupePairWithoutErrdefer__216(struct mem_Allocator_203 a0, struct slice_u8_50 a1, struct slice_u8_50 a2);
static struct slice_u8_216 verifier_prefix__anon_1828__1334(struct slice_u8_216 a0);
static void verifier_FailingAllocator_2832_2c2_29_assertNoLeaks__302(struct verifier_FailingAllocator_2832_2c2_29_187 const *a0);
zig_extern void verifier_assume(bool a0);
static void verifier_assume__295(bool a0);
static uintptr_t verifier_any__anon_1842__1335(void);
static struct Target_DynamicLinker_728 const Target_DynamicLinker_none__1108;
static struct Target_Cpu_Model_732 const Target_x86_cpu_znver4__1316;
static enum__builtin_CompilerBackend_2025 const builtin_zig_backend__224;
static bool const mem_use_vectors__333;
static bool const builtin_fuzz__241;
static bool const mem_use_vectors_for_comparison__334;
static bool mem_eql__anon_2015__1337(struct slice_u8_50 a0, struct slice_u8_50 a1);
zig_extern void verifier_check(bool a0);
static void verifier_assert__296(bool a0);
static zig_noreturn void panic_forLenMismatch__997(void);
enum {
 zig_error_OutOfMemory = 1u,
 zig_error_Overflow = 2u,
};
static uint8_t const zig_errorName_OutOfMemory[] = "OutOfMemory";
static uint8_t const zig_errorName_Overflow[] = "Overflow";
static struct slice_u8_51 const zig_errorName[2] = {
 {zig_errorName_OutOfMemory,11},
 {zig_errorName_Overflow,8},
};
static struct arr_2s116_u8_223 const __anon_224 = {"ab"};
static struct arr_2s116_u8_223 const __anon_229 = {"cd"};
static struct mem_Allocator_VTable_206 const __anon_624 = {(&verifier_FailingAllocator_2832_2c2_29_alloc__303),(&verifier_FailingAllocator_2832_2c2_29_resize__304),(&verifier_FailingAllocator_2832_2c2_29_remap__305),(&verifier_FailingAllocator_2832_2c2_29_free__306)};
static struct arr_6s116_u8_1875 const __anon_1876 = {"znver4"};
static enum__builtin_OutputMode_147 const builtin_output_mode__225 = UINT8_C(2);
static struct errunion_allocation_Pair_214 allocation_dupePair__215(struct mem_Allocator_203 const a0, struct slice_u8_50 const a1, struct slice_u8_50 const a2) {
 struct mem_Allocator_203 const *t1;
 struct mem_Allocator_203 t2;
 struct mem_Allocator_203 t0;
 struct errunion_slice_u8_216 t3;
 struct errunion_allocation_Pair_214 t6;
 struct errunion_allocation_Pair_214 t8;
 struct slice_u8_216 t7;
 struct allocation_Pair_214 *t9;
 struct slice_u8_216 *t10;
 uint16_t t4;
 uint16_t t5;
 t0 = a0;
 t1 = (struct mem_Allocator_203 const *)&t0;
 /* file:2:36 */
 t2 = (*t1);
 /* file:2:36 */
 t3 = mem_Allocator_dupe__anon_244__637(t2, a1);
 if (t3.error) {
  t4 = t3.error;
  /* file:2:24 */
  t5 = t4;
  t6.payload = (struct allocation_Pair_214){{((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul},{((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul}};
  t6.error = t5;
  return t6;
 }
 t7 = t3.payload;
 /* dbg_var_val:first_copy */
 /* file:4:5 */
 t8.error = UINT16_C(0);
 t9 = &t8.payload;
 t10 = (struct slice_u8_216 *)&t9->first;
 (*t10) = t7;
 t10 = (struct slice_u8_216 *)&t9->second;
 /* file:4:58 */
 t2 = (*t1);
 /* file:4:58 */
 t3 = mem_Allocator_dupe__anon_244__637(t2, a2);
 if (t3.error) {
  t4 = t3.error;
  /* file:3:22 */
  t2 = (*t1);
  /* file:3:22 */
  mem_Allocator_free__anon_253__638(t2, t7);
  /* file:4:46 */
  t5 = t4;
  t6.payload = (struct allocation_Pair_214){{((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul},{((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul}};
  t6.error = t5;
  return t6;
 }
 t7 = t3.payload;
 (*t10) = t7;
 /* file:4:5 */
 return t8;
}
void allocation_free_twice_is_caught__220(void) {
 struct verifier_FailingAllocator_2832_2c2_29_187 t0;
 struct mem_Allocator_203 t1;
 struct allocation_Pair_214 t2;
 struct allocation_Pair_214 t5;
 struct errunion_allocation_Pair_214 t3;
 bool t4;
 /* file:2:5 */
 t0 = (struct verifier_FailingAllocator_2832_2c2_29_187){{"\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},(uintptr_t)0ul,{{NULL,NULL}}};
 /* dbg_var_ptr:failing */
 /* file:3:34 */
 t1 = verifier_FailingAllocator_2832_2c2_29_allocator__301(&t0);
 /* dbg_var_val:gpa */
 /* file:4:5 */
 /* file:4:26 */
 t3 = allocation_dupePair__215(t1, (struct slice_u8_50){((uint8_t const *)((struct arr_2s116_u8_223 const *)&__anon_224)),(uintptr_t)2ul}, (struct slice_u8_50){((uint8_t const *)((struct arr_2s116_u8_223 const *)&__anon_229)),(uintptr_t)2ul});
 t4 = t3.error == UINT16_C(0);
 if (t4) {
  t5 = t3.payload;
  t2 = t5;
  goto zig_block_0;
 }
 /* file:4:50 */
 return;

zig_block_0:;
 /* dbg_var_val:pair */
 /* file:5:14 */
 allocation_freeTwice__217(t1, t2);
 return;
}
static struct mem_Allocator_203 verifier_FailingAllocator_2832_2c2_29_allocator__301(struct verifier_FailingAllocator_2832_2c2_29_187 *const a0) {
 void **t1;
 void *t2;
 struct mem_Allocator_VTable_206 const **t3;
 struct mem_Allocator_203 t0;
 /* file:2:13 */
 t1 = (void **)&t0.ptr;
 t2 = (void *)a0;
 (*t1) = t2;
 t3 = (struct mem_Allocator_VTable_206 const **)&t0.vtable;
 (*t3) = (((struct mem_Allocator_VTable_206 const *)&__anon_624));
 /* file:2:13 */
 return t0;
}
static void allocation_freeTwice__217(struct mem_Allocator_203 const a0, struct allocation_Pair_214 const a1) {
 struct mem_Allocator_203 const *t1;
 struct allocation_Pair_214 const *t3;
 struct mem_Allocator_203 t4;
 struct mem_Allocator_203 t0;
 struct slice_u8_216 const *t5;
 struct slice_u8_216 t6;
 struct allocation_Pair_214 t2;
 t0 = a0;
 t1 = (struct mem_Allocator_203 const *)&t0;
 t2 = a1;
 t3 = (struct allocation_Pair_214 const *)&t2;
 /* file:2:13 */
 t4 = (*t1);
 /* file:2:18 */
 t5 = (struct slice_u8_216 const *)&t3->first;
 t6 = (*t5);
 /* file:2:13 */
 mem_Allocator_free__anon_253__638(t4, t6);
 /* file:3:13 */
 t4 = (*t1);
 /* file:3:18 */
 t5 = (struct slice_u8_216 const *)&t3->second;
 t6 = (*t5);
 /* file:3:13 */
 mem_Allocator_free__anon_253__638(t4, t6);
 /* file:4:13 */
 t4 = (*t1);
 /* file:4:18 */
 t5 = (struct slice_u8_216 const *)&t3->first;
 t6 = (*t5);
 /* file:4:13 */
 mem_Allocator_free__anon_253__638(t4, t6);
 return;
}
static struct Target_Cpu_Feature_Set_737 const Target_Cpu_Feature_Set_empty__1161 = {{{0ul,0ul,0ul,0ul,0ul}}};
static struct Target_Cpu_720 const builtin_cpu__231 = {(((struct Target_Cpu_Model_732 const *)&Target_x86_cpu_znver4__1316)),{{{14373335171114205424ul,10664787974256315648ul,8073817237535973888ul,244ul,0ul}}},UINT8_C(54)};
static struct Target_Os_722 const builtin_os__232 = {{ .tag = UINT8_C(3), .payload = { .linux = {{{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}}},{2ul,43ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},UINT32_C(29)} } },UINT8_C(9)};
static enum__Target_Abi_724 const builtin_abi__230 = UINT8_C(1);
static enum__Target_ObjectFormat_726 const builtin_object_format__234 = UINT8_C(0);
static struct Target_718 const builtin_target__233 = {{(((struct Target_Cpu_Model_732 const *)&Target_x86_cpu_znver4__1316)),{{{14373335171114205424ul,10664787974256315648ul,8073817237535973888ul,244ul,0ul}}},UINT8_C(54)},{{ .tag = UINT8_C(3), .payload = { .linux = {{{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}}},{2ul,43ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},UINT32_C(29)} } },UINT8_C(9)},UINT8_C(1),UINT8_C(0),{{"/lib64/ld-linux-x86-64.so.2\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},UINT8_C(27)}};
static struct builtin_CallingConvention_310 const builtin_CallingConvention_c__849 = { .tag = UINT8_C(4), .payload = { .x86_64_sysv = {{ .is_null = true, .payload = UINT64_C(0xaaaaaaaaaaaaaaaa) }} } };
static void verifier_FailingAllocator_2832_2c2_29_free__306(void *const a0, struct slice_u8_216 const a1, enum__mem_Alignment_261 const a2, uintptr_t const a3) {
 struct slice_u8_216 const *t1;
 uintptr_t t2;
 struct verifier_FailingAllocator_2832_2c2_29_187 *t4;
 struct verifier_FailingAllocator_2832_2c2_29_187 *t5;
 struct verifier_FailingAllocator_2832_2c2_29_187 *const *t6;
 struct arr_2_opt_ptr_u8_193 *t7;
 uint8_t **t8;
 uint8_t *t9 zig_nonstring;
 uint8_t *t12 zig_nonstring;
 uint8_t *const *t10;
 uint8_t *t11 zig_nonstring;
 void *t13;
 uintptr_t const *t14;
 struct slice_u8_216 t0;
 bool t3;
 (void)a2;
 (void)a3;
 t0 = a1;
 t1 = (struct slice_u8_216 const *)&t0;
 /* file:2:33 */
 t2 = (uintptr_t)a0;
 t2 = t2 & (uintptr_t)15ul;
 t3 = t2 == (uintptr_t)0ul;
 if (t3) {
  goto zig_block_0;
 }
 panic_incorrectAlignment__985();
 zig_unreachable();

zig_block_0:;
 t4 = (struct verifier_FailingAllocator_2832_2c2_29_187 *)a0;
 t5 = t4;
 t6 = (struct verifier_FailingAllocator_2832_2c2_29_187 *const *)&t5;
 /* dbg_var_val:self */
 /* file:3:25 */
 /* dbg_var_val:slot */
 /* file:4:21 */
 /* file:4:25 */
 t4 = (*t6);
 t7 = (struct arr_2_opt_ptr_u8_193 *)&t4->live;
 /* file:4:30 */
 t8 = &t7->array[(uintptr_t)0ul];
 t9 = (*t8);
 /* file:4:46 */
 t10 = &t1->ptr;
 t11 = (*t10);
 t12 = (uint8_t *)t11;
 t3 = t9 == t12;
 if (t3) {
  /* file:5:25 */
  t4 = (*t6);
  t7 = (struct arr_2_opt_ptr_u8_193 *)&t4->live;
  /* file:5:30 */
  t8 = &t7->array[(uintptr_t)0ul];
  (*t8) = NULL;
  /* file:6:40 */
  t10 = &t1->ptr;
  t11 = (*t10);
  t13 = (void *)t11;
  /* file:6:52 */
  t14 = &t1->len;
  t2 = (*t14);
  /* file:6:33 */
  verifier_any(t13, t2);
  /* file:7:21 */
  return;
 }
 goto zig_block_2;

zig_block_2:;
 /* file:9:13 */
 (void)0;
 goto zig_block_1;

zig_block_1:;
 /* dbg_var_val:slot */
 /* file:4:21 */
 /* file:4:25 */
 t4 = (*t6);
 t7 = (struct arr_2_opt_ptr_u8_193 *)&t4->live;
 /* file:4:30 */
 t8 = &t7->array[(uintptr_t)1ul];
 t12 = (*t8);
 /* file:4:46 */
 t10 = &t1->ptr;
 t11 = (*t10);
 t9 = (uint8_t *)t11;
 t3 = t12 == t9;
 if (t3) {
  /* file:5:25 */
  t4 = (*t6);
  t7 = (struct arr_2_opt_ptr_u8_193 *)&t4->live;
  /* file:5:30 */
  t8 = &t7->array[(uintptr_t)1ul];
  (*t8) = NULL;
  /* file:6:40 */
  t10 = &t1->ptr;
  t11 = (*t10);
  t13 = (void *)t11;
  /* file:6:52 */
  t14 = &t1->len;
  t2 = (*t14);
  /* file:6:33 */
  verifier_any(t13, t2);
  /* file:7:21 */
  return;
 }
 goto zig_block_4;

zig_block_4:;
 /* file:9:13 */
 (void)0;
 goto zig_block_3;

zig_block_3:;
 /* file:10:23 */
 panic_fail__974(UINT32_C(27), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static uint8_t *verifier_FailingAllocator_2832_2c2_29_remap__305(void *const a0, struct slice_u8_216 const a1, enum__mem_Alignment_261 const a2, uintptr_t const a3, uintptr_t const a4) {
 (void)a0;
 (void)a1;
 (void)a2;
 (void)a3;
 (void)a4;
 /* file:2:13 */
 return NULL;
}
static zig_cold zig_noreturn void panic_fail__974(enum__failure_Kind_1604 const a0, uintptr_t const a1, uintptr_t const a2) {
 uint32_t t0;
 /* file:3:18 */
 t0 = a0;
 /* file:3:18 */
 verifier_fail(t0, a1, a2);
 panic_noreturnReturned__1000();
 zig_unreachable();
}
static zig_noreturn void panic_incorrectAlignment__985(void) {
 /* file:2:9 */
 panic_fail__974(UINT32_C(11), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static zig_noreturn void panic_noreturnReturned__1000(void) {
 /* file:2:9 */
 panic_fail__974(UINT32_C(26), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static bool verifier_FailingAllocator_2832_2c2_29_resize__304(void *const a0, struct slice_u8_216 const a1, enum__mem_Alignment_261 const a2, uintptr_t const a3, uintptr_t const a4) {
 (void)a0;
 (void)a1;
 (void)a2;
 (void)a3;
 (void)a4;
 /* file:2:13 */
 return false;
}
static uint8_t *verifier_FailingAllocator_2832_2c2_29_alloc__303(void *const a0, uintptr_t const a1, enum__mem_Alignment_261 const a2, uintptr_t const a3) {
 enum__mem_Alignment_261 const *t1;
 uintptr_t t2;
 uintptr_t t11;
 uintptr_t t14;
 struct verifier_FailingAllocator_2832_2c2_29_187 *t4;
 struct verifier_FailingAllocator_2832_2c2_29_187 *t5;
 struct verifier_FailingAllocator_2832_2c2_29_187 *const *t6;
 uint64_t t8;
 uint64_t t15;
 uintptr_t *t9;
 struct tuple_2_usize_u1_671088641 t12;
 struct arr_2_opt_ptr_u8_193 *t16;
 uint8_t **t17;
 uint8_t *t18 zig_nonstring;
 struct arr_32_u8_189 *t19;
 uint8_t *t20 zig_nonstring;
 uint8_t *t21 zig_nonstring;
 struct slice_u8_1670 t22;
 struct slice_u8_1670 t23;
 struct slice_u8_1670 t27;
 struct slice_u8_1670 const *t24;
 uint8_t *const *t25;
 void *t26;
 bool t3;
 bool t10;
 enum__mem_Alignment_261 t7;
 enum__mem_Alignment_261 t0;
 uint8_t t13;
 (void)a3;
 t0 = a2;
 t1 = (enum__mem_Alignment_261 const *)&t0;
 /* file:2:33 */
 t2 = (uintptr_t)a0;
 t2 = t2 & (uintptr_t)15ul;
 t3 = t2 == (uintptr_t)0ul;
 if (t3) {
  goto zig_block_0;
 }
 panic_incorrectAlignment__985();
 zig_unreachable();

zig_block_0:;
 t4 = (struct verifier_FailingAllocator_2832_2c2_29_187 *)a0;
 t5 = t4;
 t6 = (struct verifier_FailingAllocator_2832_2c2_29_187 *const *)&t5;
 /* dbg_var_val:self */
 /* file:3:17 */
 /* file:3:20 */
 t3 = verifier_any__anon_1655__1326();
 if (t3) {
  /* file:3:28 */
  return NULL;
 }
 goto zig_block_1;

zig_block_1:;
 /* file:4:17 */
 /* file:4:38 */
 t7 = (*t1);
 /* file:4:38 */
 t2 = mem_Alignment_toByteUnits__639(t7);
 t8 = t2;
 t3 = t8 > UINT64_C(16);
 if (t3) {
  /* file:4:47 */
  return NULL;
 }
 goto zig_block_2;

zig_block_2:;
 /* file:5:44 */
 t7 = (*t1);
 /* file:5:49 */
 t4 = (*t6);
 t9 = (uintptr_t *)&t4->used;
 t2 = (*t9);
 /* file:5:44 */
 t2 = mem_Alignment_forward__647(t7, t2);
 /* dbg_var_val:start */
 /* file:6:17 */
 t8 = t2;
 t3 = t8 > UINT64_C(32);
 if (t3) {
  t10 = true;
  goto zig_block_4;
 }
 /* file:6:52 */
 t12.f1 = zig_subo_u64(&t12.f0, (uintptr_t)32ul, t2, UINT8_C(64));
 t13 = t12.f1;
 t3 = t13 == UINT8_C(1);
 if (t3) {
  panic_integerOverflow__988();
  zig_unreachable();
 }
 t14 = t12.f0;
 t11 = t14;
 goto zig_block_5;

zig_block_5:;
 t8 = a1;
 t15 = t11;
 t3 = t8 > t15;
 t10 = t3;
 goto zig_block_4;

zig_block_4:;
 if (t10) {
  /* file:6:61 */
  return NULL;
 }
 goto zig_block_3;

zig_block_3:;
 /* file:7:25 */
 /* dbg_var_val:slot */
 /* file:8:21 */
 /* file:8:25 */
 t4 = (*t6);
 t16 = (struct arr_2_opt_ptr_u8_193 *)&t4->live;
 /* file:8:30 */
 t17 = &t16->array[(uintptr_t)0ul];
 t18 = (*t17);
 t10 = t18 == NULL;
 if (t10) {
  /* file:9:40 */
  t4 = (*t6);
  t19 = (struct arr_32_u8_189 *)&t4->buffer;
  /* file:9:56 */
  t20 = (uint8_t *)t19;
  t21 = (uint8_t *)(((uintptr_t)t20) + (t2*sizeof(uint8_t)));
  t14 = t2 + a1;
  t10 = t14 <= (uintptr_t)32ul;
  if (t10) {
   goto zig_block_8;
  }
  panic_outOfBounds__978(t14, (uintptr_t)32ul);
  zig_unreachable();

zig_block_8:;
  t22.ptr = t21;
  t22.len = a1;
  t23 = t22;
  t24 = (struct slice_u8_1670 const *)&t23;
  /* dbg_var_val:memory */
  /* file:10:40 */
  t25 = &t24->ptr;
  t21 = (*t25);
  t26 = (void *)t21;
  /* file:10:33 */
  verifier_any(t26, a1);
  /* file:11:25 */
  t4 = (*t6);
  t16 = (struct arr_2_opt_ptr_u8_193 *)&t4->live;
  /* file:11:30 */
  t17 = &t16->array[(uintptr_t)0ul];
  /* file:11:45 */
  t25 = &t24->ptr;
  t21 = (*t25);
  t18 = (uint8_t *)t21;
  (*t17) = t18;
  /* file:12:25 */
  t4 = (*t6);
  t9 = (uintptr_t *)&t4->used;
  /* file:12:39 */
  t12.f1 = zig_addo_u64(&t12.f0, t2, a1, UINT8_C(64));
  t13 = t12.f1;
  t10 = t13 == UINT8_C(1);
  if (t10) {
   panic_integerOverflow__988();
   zig_unreachable();
  }
  t2 = t12.f0;
  t14 = t2;
  goto zig_block_9;

zig_block_9:;
  (*t9) = t14;
  /* file:13:34 */
  t25 = &t24->ptr;
  t21 = (*t25);
  /* file:13:21 */
  t18 = (uint8_t *)t21;
  return t18;
 }
 goto zig_block_7;

zig_block_7:;
 /* file:15:13 */
 (void)0;
 goto zig_block_6;

zig_block_6:;
 /* dbg_var_val:slot */
 /* file:8:21 */
 /* file:8:25 */
 t4 = (*t6);
 t16 = (struct arr_2_opt_ptr_u8_193 *)&t4->live;
 /* file:8:30 */
 t17 = &t16->array[(uintptr_t)1ul];
 t18 = (*t17);
 t10 = t18 == NULL;
 if (t10) {
  /* file:9:40 */
  t4 = (*t6);
  t19 = (struct arr_32_u8_189 *)&t4->buffer;
  /* file:9:56 */
  t20 = (uint8_t *)t19;
  t21 = (uint8_t *)(((uintptr_t)t20) + (t2*sizeof(uint8_t)));
  t14 = t2 + a1;
  t10 = t14 <= (uintptr_t)32ul;
  if (t10) {
   goto zig_block_12;
  }
  panic_outOfBounds__978(t14, (uintptr_t)32ul);
  zig_unreachable();

zig_block_12:;
  t22.ptr = t21;
  t22.len = a1;
  t27 = t22;
  t24 = (struct slice_u8_1670 const *)&t27;
  /* dbg_var_val:memory */
  /* file:10:40 */
  t25 = &t24->ptr;
  t21 = (*t25);
  t26 = (void *)t21;
  /* file:10:33 */
  verifier_any(t26, a1);
  /* file:11:25 */
  t4 = (*t6);
  t16 = (struct arr_2_opt_ptr_u8_193 *)&t4->live;
  /* file:11:30 */
  t17 = &t16->array[(uintptr_t)1ul];
  /* file:11:45 */
  t25 = &t24->ptr;
  t21 = (*t25);
  t18 = (uint8_t *)t21;
  (*t17) = t18;
  /* file:12:25 */
  t4 = (*t6);
  t9 = (uintptr_t *)&t4->used;
  /* file:12:39 */
  t12.f1 = zig_addo_u64(&t12.f0, t2, a1, UINT8_C(64));
  t13 = t12.f1;
  t10 = t13 == UINT8_C(1);
  if (t10) {
   panic_integerOverflow__988();
   zig_unreachable();
  }
  t2 = t12.f0;
  t14 = t2;
  goto zig_block_13;

zig_block_13:;
  (*t9) = t14;
  /* file:13:34 */
  t25 = &t24->ptr;
  t21 = (*t25);
  /* file:13:21 */
  t18 = (uint8_t *)t21;
  return t18;
 }
 goto zig_block_11;

zig_block_11:;
 /* file:15:13 */
 (void)0;
 goto zig_block_10;

zig_block_10:;
 /* file:16:13 */
 return NULL;
}
static void mem_Allocator_free__anon_253__638(struct mem_Allocator_203 const a0, struct slice_u8_216 const a1) {
 struct mem_Allocator_203 const *t1;
 struct slice_u8_216 t2;
 struct slice_u8_216 t3;
 struct slice_u8_216 t4;
 struct slice_u8_216 const *t5;
 uintptr_t const *t6;
 uintptr_t t7;
 uint64_t t8;
 struct mem_Allocator_203 t10;
 struct mem_Allocator_203 t0;
 struct mem_Allocator_203 t12;
 struct mem_Allocator_VTable_206 const *const *t13;
 struct mem_Allocator_VTable_206 const *t14;
 fn__Pptr_anyopaque_Pslice_u8_Pmem_Alignment_Pusize_Rvoid_270 *const *t15;
 fn__Pptr_anyopaque_Pslice_u8_Pmem_Alignment_Pusize_Rvoid_270 *t16;
 void *const *t17;
 void *t18;
 bool t9;
 enum__mem_Alignment_261 t11;
 t0 = a0;
 t1 = (struct mem_Allocator_203 const *)&t0;
 /* file:4:63 */
 t2 = mem_absorbSentinel__anon_1699__1327(a1);
 /* file:4:25 */
 memcpy(&t3, &t2, 16);
 t4 = t3;
 t5 = (struct slice_u8_216 const *)&t4;
 /* dbg_var_val:bytes */
 /* file:5:9 */
 /* file:5:14 */
 t6 = &t5->len;
 t7 = (*t6);
 t8 = t7;
 t9 = t8 == UINT64_C(0);
 if (t9) {
  /* file:5:25 */
  return;
 }
 goto zig_block_0;

zig_block_0:;
 /* file:6:5 */
 memset(t3.ptr, 0xaa, t3.len * 1);
 /* file:7:17 */
 t10 = (*t1);
 /* file:7:39 */
 /* file:7:39 */
 t11 = mem_Alignment_fromByteUnits__640((uintptr_t)1ul);
 t7 = (uintptr_t)zig_return_address();
 /* file:7:17 */
 /* inline:mem.Allocator.rawFree */
 /* dbg_arg_inline:a */
 /* dbg_arg_inline:memory */
 /* dbg_arg_inline:alignment */
 /* dbg_arg_inline:ret_addr */
 t12 = t10;
 t1 = (struct mem_Allocator_203 const *)&t12;
 /* file:2:13 */
 t13 = (struct mem_Allocator_VTable_206 const *const *)&t1->vtable;
 /* file:2:25 */
 t14 = (*t13);
 t15 = (fn__Pptr_anyopaque_Pslice_u8_Pmem_Alignment_Pusize_Rvoid_270 *const *)&t14->free;
 t16 = (*t15);
 /* file:2:27 */
 t17 = (void *const *)&t1->ptr;
 t18 = (*t17);
 /* file:2:25 */
 t16(t18, t3, t11, t7);
 /* file:2:5 */
 goto zig_block_1;

zig_block_1:;
 return;
}
static zig_noreturn void panic_outOfBounds__978(uintptr_t const a0, uintptr_t const a1) {
 /* file:2:9 */
 panic_fail__974(UINT32_C(4), a0, a1);
 zig_unreachable();
}
static enum__mem_Alignment_261 mem_Alignment_fromByteUnits__640(uintptr_t const a0) {
 bool t0;
 uint8_t t1;
 enum__mem_Alignment_261 t2;
 enum__mem_Alignment_261 t3;
 /* file:2:37 */
 t0 = math_isPowerOfTwo__anon_1720__1328(a0);
 /* file:2:15 */
 debug_assert__160(t0);
 /* file:3:9 */
 t1 = zig_ctz_u64(a0, UINT8_C(64));
 /* file:3:16 */
 t0 = t1 > UINT8_C(63);
 if (t0) {
  panic_invalidEnumValue__996();
  zig_unreachable();
 }
 t3 = t1;
 t2 = t3;
 goto zig_block_0;

zig_block_0:;
 /* file:3:9 */
 return t2;
}
static struct slice_u8_216 mem_absorbSentinel__anon_1699__1327(struct slice_u8_216 const a0) {
 struct slice_u8_216 t0;
 t0 = a0;
 /* file:4:9 */
 /* file:5:9 */
 return a0;
}
static zig_noreturn void panic_invalidEnumValue__996(void) {
 /* file:2:9 */
 panic_fail__974(UINT32_C(22), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static void debug_assert__160(bool const a0) {
 bool t0;
 /* file:3:9 */
 t0 = !a0;
 if (t0) {
  /* file:3:14 */
  panic_reachedUnreachable__982();
  zig_unreachable();
 }
 goto zig_block_0;

zig_block_0:;
 return;
}
static bool math_isPowerOfTwo__anon_1720__1328(uintptr_t const a0) {
 uint64_t t0;
 uintptr_t t2;
 uintptr_t t5;
 struct tuple_2_usize_u1_671088641 t3;
 bool t1;
 uint8_t t4;
 /* file:2:11 */
 t0 = a0;
 t1 = t0 > UINT64_C(0);
 /* file:2:11 */
 debug_assert__160(t1);
 /* file:3:24 */
 t3.f1 = zig_subo_u64(&t3.f0, a0, (uintptr_t)1ul, UINT8_C(64));
 t4 = t3.f1;
 t1 = t4 == UINT8_C(1);
 if (t1) {
  panic_integerOverflow__988();
  zig_unreachable();
 }
 t5 = t3.f0;
 t2 = t5;
 goto zig_block_0;

zig_block_0:;
 t2 = a0 & t2;
 t0 = t2;
 t1 = t0 == UINT64_C(0);
 /* file:3:5 */
 return t1;
}
static zig_noreturn void panic_reachedUnreachable__982(void) {
 /* file:2:9 */
 panic_fail__974(UINT32_C(8), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static zig_noreturn void panic_integerOverflow__988(void) {
 /* file:2:9 */
 panic_fail__974(UINT32_C(14), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static uintptr_t mem_Alignment_forward__647(enum__mem_Alignment_261 const a0, uintptr_t const a1) {
 uintptr_t t1;
 uintptr_t t2;
 uintptr_t t6;
 struct tuple_2_usize_u1_671088641 t3;
 uint8_t t0;
 uint8_t t4;
 bool t5;
 /* file:2:9 */
 t0 = a0;
 /* file:2:34 */
 t1 = zig_shlw_u64((uintptr_t)1ul, t0, UINT8_C(64));
/* file:2:54 */
 t3.f1 = zig_subo_u64(&t3.f0, t1, (uintptr_t)1ul, UINT8_C(64));
 t4 = t3.f1;
 t5 = t4 == UINT8_C(1);
 if (t5) {
  panic_integerOverflow__988();
  zig_unreachable();
 }
 t1 = t3.f0;
 t2 = t1;
 goto zig_block_0;

zig_block_0:;
 /* dbg_var_val:x */
 /* file:3:25 */
 t3.f1 = zig_addo_u64(&t3.f0, a1, t2, UINT8_C(64));
 t4 = t3.f1;
 t5 = t4 == UINT8_C(1);
 if (t5) {
  panic_integerOverflow__988();
  zig_unreachable();
 }
 t6 = t3.f0;
 t1 = t6;
 goto zig_block_1;

zig_block_1:;
 t2 = zig_not_u64(t2, UINT8_C(64));
 t2 = t1 & t2;
 /* file:3:9 */
 return t2;
}
static uintptr_t mem_Alignment_toByteUnits__639(enum__mem_Alignment_261 const a0) {
 uintptr_t t1;
 uint8_t t0;
 /* file:2:9 */
 t0 = a0;
 /* file:2:30 */
 t1 = zig_shlw_u64((uintptr_t)1ul, t0, UINT8_C(64));
/* file:2:9 */
 return t1;
}
static bool verifier_any__anon_1655__1326(void) {
 uint8_t t0;
 bool t1;
 /* file:2:13 */
 /* file:4:28 */
 t0 = verifier_any__anon_1734__1329();
 t0 = t0 & UINT8_C(1);
 t1 = t0 == UINT8_C(1);
 /* file:4:18 */
 return t1;
}
static struct errunion_slice_u8_216 mem_Allocator_dupe__anon_244__637(struct mem_Allocator_203 const a0, struct slice_u8_50 const a1) {
 struct mem_Allocator_203 const *t1;
 struct slice_u8_50 const *t3;
 struct mem_Allocator_203 t4;
 struct mem_Allocator_203 t0;
 uintptr_t const *t5;
 uintptr_t t6;
 uintptr_t t10;
 struct errunion_slice_u8_216 t7;
 struct slice_u8_216 t9;
 uint8_t const *t12 zig_nonstring;
 uint8_t const *t14 zig_nonstring;
 uint8_t *t13 zig_nonstring;
 uint8_t *t15 zig_nonstring;
 struct slice_u8_50 t2;
 uint16_t t8;
 bool t11;
 bool t16;
 t0 = a0;
 t1 = (struct mem_Allocator_203 const *)&t0;
 t2 = a1;
 t3 = (struct slice_u8_50 const *)&t2;
 /* file:2:40 */
 t4 = (*t1);
 /* file:2:45 */
 t5 = &t3->len;
 t6 = (*t5);
 /* file:2:40 */
 t7 = mem_Allocator_alloc__anon_1742__1330(t4, t6);
 if (t7.error) {
  t8 = t7.error;
  /* file:2:21 */
  t7.payload = (struct slice_u8_216){((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul};
  t7.error = t8;
  return t7;
 }
 t9 = t7.payload;
 /* dbg_var_val:new_buf */
 /* file:3:5 */
 t6 = t9.len;
 t10 = a1.len;
 t11 = t6 == t10;
 if (t11) {
  goto zig_block_0;
 }
 panic_copyLenMismatch__998();
 zig_unreachable();

zig_block_0:;
 t12 = a1.ptr;
 t13 = t9.ptr;
 t14 = (uint8_t const *)(((uintptr_t)t12) + (t6*sizeof(uint8_t)));
 t15 = (uint8_t *)(((uintptr_t)t13) + (t6*sizeof(uint8_t)));
 t11 = t13 >= t14;
 t16 = t12 >= t15;
 t16 = t11 | t16;
 if (t16) {
  goto zig_block_1;
 }
 panic_memcpyAlias__999();
 zig_unreachable();

zig_block_1:;
 if (t9.len != 0) memcpy(t9.ptr, t12, t9.len * sizeof(uint8_t));
 /* file:4:5 */
 t7.payload = t9;
 t7.error = UINT16_C(0);
 return t7;
}
static uint8_t verifier_any__anon_1734__1329(void) {
 void *t1;
 uint8_t t2;
 uint8_t t0;
 /* file:2:13 */
 /* dbg_var_val:int */
 /* file:7:13 */
 memset(&t0, 0xaa, sizeof(uint8_t));
 /* dbg_var_ptr:backing */
 /* file:8:25 */
 t1 = (void *)&t0;
 /* file:8:25 */
 verifier_any(t1, (uintptr_t)1ul);
 /* file:10:13 */
 t2 = t0;
 /* file:10:43 */
 /* file:10:13 */
 return t2;
}
static zig_noreturn void panic_memcpyAlias__999(void) {
 /* file:2:9 */
 panic_fail__974(UINT32_C(25), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static zig_noreturn void panic_copyLenMismatch__998(void) {
 /* file:2:9 */
 panic_fail__974(UINT32_C(24), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static struct errunion_slice_u8_216 mem_Allocator_alloc__anon_1742__1330(struct mem_Allocator_203 const a0, uintptr_t const a1) {
 struct mem_Allocator_203 const *t1;
 struct mem_Allocator_203 t2;
 struct mem_Allocator_203 t0;
 struct mem_Allocator_203 t5;
 uintptr_t t3;
 struct errunion_slice_u8_1670 t4;
 struct errunion_slice_u8_1670 t8;
 struct errunion_ptr_u8_1669 t6;
 uint8_t *t9 zig_nonstring;
 uint8_t *t10 zig_nonstring;
 uint8_t *const *t11;
 struct slice_u8_1670 t12;
 struct errunion_slice_u8_216 t13;
 uint16_t t7;
 t0 = a0;
 t1 = (struct mem_Allocator_203 const *)&t0;
 /* file:2:41 */
 t2 = (*t1);
 t3 = (uintptr_t)zig_return_address();
 /* file:2:41 */
 /* inline:mem.Allocator.allocAdvancedWithRetAddr */
 /* dbg_arg_inline:self */
 /* dbg_arg_inline:alignment */
 /* dbg_arg_inline:n */
 /* dbg_arg_inline:return_address */
 t5 = t2;
 t1 = (struct mem_Allocator_203 const *)&t5;
 /* file:9:5 */
 /* dbg_var_val:a */
 /* file:10:89 */
 t2 = (*t1);
 /* file:10:89 */
 t6 = mem_Allocator_allocWithSizeAndAlignment__anon_1776__1331(t2, a1, t3);
 if (t6.error) {
  t7 = t6.error;
  /* file:10:55 */
  t8.payload = (struct slice_u8_1670){((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul};
  t8.error = t7;
  t4 = t8;
  goto zig_block_0;
 }
 t9 = t6.payload;
 /* file:10:46 */
 t10 = t9;
 t11 = (uint8_t *const *)&t10;
 /* dbg_var_val:ptr */
 /* file:11:15 */
 t9 = (*t11);
 t9 = (uint8_t *)(((uintptr_t)t9) + ((uintptr_t)0ul*sizeof(uint8_t)));
 t3 = a1 - (uintptr_t)0ul;
 t12.ptr = t9;
 t12.len = t3;
 /* file:11:5 */
 t8.payload = t12;
 t8.error = UINT16_C(0);
 t4 = t8;
 goto zig_block_0;

zig_block_0:;
 /* file:2:5 */
 memcpy(&t13, &t4, 24);
 return t13;
}
static struct errunion_ptr_u8_1669 mem_Allocator_allocWithSizeAndAlignment__anon_1776__1331(struct mem_Allocator_203 const a0, uintptr_t const a1, uintptr_t const a2) {
 struct mem_Allocator_203 const *t1;
 uintptr_t t2;
 uintptr_t t5;
 struct errunion_usize_16 t3;
 struct mem_Allocator_203 t6;
 struct mem_Allocator_203 t0;
 struct errunion_ptr_u8_1669 t7;
 bool t4;
 t0 = a0;
 t1 = (struct mem_Allocator_203 const *)&t0;
 /* file:8:5 */
 /* file:8:32 */
 t3 = math_mul__anon_1786__1332((uintptr_t)1ul, a1);
 t4 = t3.error == UINT16_C(0);
 if (t4) {
  t5 = t3.payload;
  t2 = t5;
  goto zig_block_0;
 }
 /* file:8:55 */
 return (struct errunion_ptr_u8_1669){ .error = zig_error_OutOfMemory, .payload = ((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul) };

zig_block_0:;
 /* dbg_var_val:byte_count */
 /* file:9:40 */
 t6 = (*t1);
 /* file:9:40 */
 t7 = mem_Allocator_allocBytesWithAlignment__anon_1793__1333(t6, t2, a2);
 /* file:9:5 */
 return t7;
}
static struct errunion_usize_16 math_mul__anon_1786__1332(uintptr_t const a0, uintptr_t const a1) {
 struct tuple_2_usize_u1_671088641 t0;
 struct tuple_2_usize_u1_671088641 t1;
 struct tuple_2_usize_u1_671088641 const *t2;
 uint8_t const *t3 zig_nonstring;
 uintptr_t const *t6;
 uintptr_t t7;
 struct errunion_usize_16 t8;
 uint8_t t4;
 bool t5;
 /* file:3:5 */
 t0.f1 = zig_mulo_u64(&t0.f0, a0, a1, UINT8_C(64));
 t1 = t0;
 t2 = (struct tuple_2_usize_u1_671088641 const *)&t1;
 /* dbg_var_val:ov */
 /* file:4:9 */
 /* file:4:11 */
 t3 = (uint8_t const *)&t2->f1;
 t4 = (*t3);
 t5 = t4 != UINT8_C(0);
 if (t5) {
  /* file:4:21 */
  return (struct errunion_usize_16){ .error = zig_error_Overflow, .payload = (uintptr_t)0xaaaaaaaaaaaaaaaaul };
 }
 goto zig_block_0;

zig_block_0:;
 /* file:5:14 */
 t6 = (uintptr_t const *)&t2->f0;
 t7 = (*t6);
 /* file:5:5 */
 t8.payload = t7;
 t8.error = UINT16_C(0);
 return t8;
}
static struct errunion_ptr_u8_1669 mem_Allocator_allocBytesWithAlignment__anon_1793__1333(struct mem_Allocator_203 const a0, uintptr_t const a1, uintptr_t const a2) {
 struct mem_Allocator_203 const *t1;
 uint64_t t2;
 uint8_t *t4 zig_nonstring;
 uint8_t *t15 zig_nonstring;
 uint8_t *t16 zig_nonstring;
 struct mem_Allocator_203 t5;
 struct mem_Allocator_203 t0;
 struct mem_Allocator_203 t7;
 uint8_t *t6 zig_nonstring;
 uint8_t *t14 zig_nonstring;
 struct mem_Allocator_VTable_206 const *const *t8;
 struct mem_Allocator_VTable_206 const *t9;
 fn__Pptr_anyopaque_Pusize_Pmem_Alignment_Pusize_Ropt_ptr_u8_264 *const *t10;
 fn__Pptr_anyopaque_Pusize_Pmem_Alignment_Pusize_Ropt_ptr_u8_264 *t11;
 void *const *t12;
 void *t13;
 uint8_t *const *t17;
 uintptr_t t18;
 struct slice_u8_216 t19;
 uint8_t *t20 zig_nonstring;
 struct errunion_ptr_u8_1669 t21;
 bool t3;
 t0 = a0;
 t1 = (struct mem_Allocator_203 const *)&t0;
 /* file:7:9 */
 t2 = a1;
 t3 = t2 == UINT64_C(0);
 if (t3) {
  /* file:8:9 */
  /* dbg_var_val:ptr */
  /* file:9:9 */
  return (struct errunion_ptr_u8_1669){ .error = 0, .payload = ((uint8_t *)UINTPTR_MAX) };
 }
 goto zig_block_0;

zig_block_0:;
 /* file:12:5 */
 /* file:12:35 */
 t5 = (*t1);
 /* file:12:35 */
 /* inline:mem.Allocator.rawAlloc */
 /* dbg_arg_inline:a */
 /* dbg_arg_inline:len */
 /* dbg_arg_inline:alignment */
 /* dbg_arg_inline:ret_addr */
 t7 = t5;
 t1 = (struct mem_Allocator_203 const *)&t7;
 /* file:2:13 */
 t8 = (struct mem_Allocator_VTable_206 const *const *)&t1->vtable;
 /* file:2:26 */
 t9 = (*t8);
 t10 = (fn__Pptr_anyopaque_Pusize_Pmem_Alignment_Pusize_Ropt_ptr_u8_264 *const *)&t9->alloc;
 t11 = (*t10);
 /* file:2:28 */
 t12 = (void *const *)&t1->ptr;
 t13 = (*t12);
 /* file:2:26 */
 t14 = t11(t13, a1, UINT8_C(0), a2);
 /* file:2:5 */
 t6 = t14;
 goto zig_block_2;

zig_block_2:;
 t3 = t6 != NULL;
 if (t3) {
  t15 = t6;
  t4 = t15;
  goto zig_block_1;
 }
 /* file:12:82 */
 return (struct errunion_ptr_u8_1669){ .error = zig_error_OutOfMemory, .payload = ((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul) };

zig_block_1:;
 t16 = t4;
 t17 = (uint8_t *const *)&t16;
 /* dbg_var_val:byte_ptr */
 /* file:13:21 */
 t15 = (*t17);
 t15 = (uint8_t *)(((uintptr_t)t15) + ((uintptr_t)0ul*sizeof(uint8_t)));
 t18 = a1 - (uintptr_t)0ul;
 t19.ptr = t15;
 t19.len = t18;
 memset(t19.ptr, 0xaa, t19.len * 1);
 /* file:14:12 */
 t20 = (uint8_t *)t4;
 /* file:14:5 */
 t21.payload = t20;
 t21.error = UINT16_C(0);
 return t21;
}
static struct errunion_allocation_Pair_214 allocation_dupePairWithoutErrdefer__216(struct mem_Allocator_203 const a0, struct slice_u8_50 const a1, struct slice_u8_50 const a2) {
 struct mem_Allocator_203 const *t1;
 struct mem_Allocator_203 t2;
 struct mem_Allocator_203 t0;
 struct errunion_slice_u8_216 t3;
 struct errunion_allocation_Pair_214 t6;
 struct errunion_allocation_Pair_214 t8;
 struct slice_u8_216 t7;
 struct allocation_Pair_214 *t9;
 struct slice_u8_216 *t10;
 uint16_t t4;
 uint16_t t5;
 t0 = a0;
 t1 = (struct mem_Allocator_203 const *)&t0;
 /* file:2:36 */
 t2 = (*t1);
 /* file:2:36 */
 t3 = mem_Allocator_dupe__anon_244__637(t2, a1);
 if (t3.error) {
  t4 = t3.error;
  /* file:2:24 */
  t5 = t4;
  t6.payload = (struct allocation_Pair_214){{((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul},{((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul}};
  t6.error = t5;
  return t6;
 }
 t7 = t3.payload;
 /* dbg_var_val:first_copy */
 /* file:3:5 */
 t8.error = UINT16_C(0);
 t9 = &t8.payload;
 t10 = (struct slice_u8_216 *)&t9->first;
 (*t10) = t7;
 t10 = (struct slice_u8_216 *)&t9->second;
 /* file:3:58 */
 t2 = (*t1);
 /* file:3:58 */
 t3 = mem_Allocator_dupe__anon_244__637(t2, a2);
 if (t3.error) {
  t4 = t3.error;
  /* file:3:46 */
  t5 = t4;
  t6.payload = (struct allocation_Pair_214){{((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul},{((uint8_t *)(uintptr_t)0xaaaaaaaaaaaaaaaaul),(uintptr_t)0xaaaaaaaaaaaaaaaaul}};
  t6.error = t5;
  return t6;
 }
 t7 = t3.payload;
 (*t10) = t7;
 /* file:3:5 */
 return t8;
}
void allocation_dupe_pair_without_errdefer_never_leaks__219(void) {
 struct verifier_FailingAllocator_2832_2c2_29_187 t0;
 struct mem_Allocator_203 t1;
 struct mem_Allocator_203 t2;
 struct mem_Allocator_203 const *t3;
 struct slice_u8_216 t6;
 struct slice_u8_216 t7;
 struct slice_u8_50 t8;
 struct slice_u8_50 t9;
 struct errunion_allocation_Pair_214 t10;
 struct allocation_Pair_214 t12;
 struct allocation_Pair_214 t13;
 struct allocation_Pair_214 const *t14;
 struct slice_u8_216 const *t15;
 struct verifier_FailingAllocator_2832_2c2_29_187 const *t16;
 bool t11;
 struct arr_8_u8_1821 t4;
 struct arr_8_u8_1821 t5;
 /* file:2:5 */
 t0 = (struct verifier_FailingAllocator_2832_2c2_29_187){{"\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},(uintptr_t)0ul,{{NULL,NULL}}};
 /* dbg_var_ptr:failing */
 /* file:3:34 */
 t1 = verifier_FailingAllocator_2832_2c2_29_allocator__301(&t0);
 t2 = t1;
 t3 = (struct mem_Allocator_203 const *)&t2;
 /* dbg_var_val:gpa */
 /* file:4:5 */
 memset(&t4, 0xaa, sizeof(struct arr_8_u8_1821));
 /* dbg_var_ptr:first_buffer */
 /* file:5:5 */
 memset(&t5, 0xaa, sizeof(struct arr_8_u8_1821));
 /* dbg_var_ptr:second_buffer */
 /* file:6:34 */
 t6.ptr = (uint8_t *)&t4;
 t6.len = (uintptr_t)8ul;
 /* file:6:34 */
 t6 = verifier_prefix__anon_1828__1334(t6);
 /* dbg_var_val:first */
 /* file:7:35 */
 t7.ptr = (uint8_t *)&t5;
 t7.len = (uintptr_t)8ul;
 /* file:7:35 */
 t7 = verifier_prefix__anon_1828__1334(t7);
 /* dbg_var_val:second */
 /* file:8:9 */
 /* file:8:32 */
 memcpy(&t8, &t6, 16);
 memcpy(&t9, &t7, 16);
 /* file:8:32 */
 t10 = allocation_dupePairWithoutErrdefer__216(t1, t8, t9);
 t11 = t10.error == UINT16_C(0);
 if (t11) {
  t12 = t10.payload;
  t13 = t12;
  t14 = (struct allocation_Pair_214 const *)&t13;
  /* dbg_var_val:pair */
  /* file:9:17 */
  t1 = (*t3);
  /* file:9:22 */
  t15 = (struct slice_u8_216 const *)&t14->first;
  t7 = (*t15);
  /* file:9:17 */
  mem_Allocator_free__anon_253__638(t1, t7);
  /* file:10:17 */
  t1 = (*t3);
  /* file:10:22 */
  t15 = (struct slice_u8_216 const *)&t14->second;
  t7 = (*t15);
  /* file:10:17 */
  mem_Allocator_free__anon_253__638(t1, t7);
  goto zig_block_0;
 }
 goto zig_block_0;

zig_block_0:;
 /* file:12:26 */
 t16 = (struct verifier_FailingAllocator_2832_2c2_29_187 const *)&t0;
 /* file:12:26 */
 verifier_FailingAllocator_2832_2c2_29_assertNoLeaks__302(t16);
 return;
}
static struct slice_u8_216 verifier_prefix__anon_1828__1334(struct slice_u8_216 const a0) {
 struct slice_u8_216 const *t1;
 uintptr_t t3;
 uintptr_t t4;
 uintptr_t t13;
 uintptr_t t2;
 uint64_t t5;
 uint64_t t6;
 uint8_t *t8 zig_nonstring;
 uintptr_t const *t10;
 struct slice_u8_216 t11;
 struct slice_u8_216 t0;
 uint8_t *t12 zig_nonstring;
 bool t7;
 uint8_t t9;
 t0 = a0;
 t1 = (struct slice_u8_216 const *)&t0;
 t2 = (uintptr_t)0ul;
 /* file:2:10 */
 t3 = a0.len;
 zig_loop_9:
 t4 = t2;
 t5 = t4;
 t6 = t3;
 t7 = t5 < t6;
 if (t7) {
  t8 = &a0.ptr[t4];
  /* dbg_var_val:item */
  /* file:2:38 */
  t9 = verifier_any__anon_1734__1329();
  (*t8) = t9;
  /* file:2:40 */
  (void)0;
  goto zig_block_1;
 }
 goto zig_block_0;

zig_block_1:;
 t4 = t4 + (uintptr_t)1ul;
 t2 = t4;
 goto zig_loop_9;

zig_block_0:;
 /* file:3:20 */
 t3 = verifier_any__anon_1842__1335();
 /* dbg_var_val:len */
 /* file:4:25 */
 t10 = &t1->len;
 t4 = (*t10);
 t6 = t3;
 t5 = t4;
 t7 = t6 <= t5;
 /* file:4:11 */
 verifier_assume__295(t7);
 /* file:5:18 */
 t11 = (*t1);
 t12 = t11.ptr;
 t12 = (uint8_t *)(((uintptr_t)t12) + ((uintptr_t)0ul*sizeof(uint8_t)));
 t4 = t3 - (uintptr_t)0ul;
 t13 = t11.len;
 t7 = t3 <= t13;
 if (t7) {
  goto zig_block_2;
 }
 panic_outOfBounds__978(t3, t13);
 zig_unreachable();

zig_block_2:;
 t11.ptr = t12;
 t11.len = t4;
 /* file:5:5 */
 return t11;
}
static void verifier_FailingAllocator_2832_2c2_29_assertNoLeaks__302(struct verifier_FailingAllocator_2832_2c2_29_187 const *const a0) {
 struct verifier_FailingAllocator_2832_2c2_29_187 const *const *t1;
 struct verifier_FailingAllocator_2832_2c2_29_187 const *t2;
 struct verifier_FailingAllocator_2832_2c2_29_187 const *t0;
 struct arr_2_opt_ptr_u8_193 const *t3;
 uint8_t *const *t4;
 uint8_t *t5 zig_nonstring;
 bool t6;
 t0 = a0;
 t1 = (struct verifier_FailingAllocator_2832_2c2_29_187 const *const *)&t0;
 /* file:3:25 */
 /* dbg_var_val:slot */
 /* file:4:21 */
 /* file:4:25 */
 t2 = (*t1);
 t3 = (struct arr_2_opt_ptr_u8_193 const *)&t2->live;
 /* file:4:30 */
 t4 = &t3->array[(uintptr_t)0ul];
 t5 = (*t4);
 t6 = t5 != NULL;
 if (t6) {
  /* file:4:56 */
  panic_fail__974(UINT32_C(28), (uintptr_t)0ul, (uintptr_t)0ul);
  zig_unreachable();
 }
 goto zig_block_1;

zig_block_1:;
 /* file:5:13 */
 (void)0;
 goto zig_block_0;

zig_block_0:;
 /* dbg_var_val:slot */
 /* file:4:21 */
 /* file:4:25 */
 t2 = (*t1);
 t3 = (struct arr_2_opt_ptr_u8_193 const *)&t2->live;
 /* file:4:30 */
 t4 = &t3->array[(uintptr_t)1ul];
 t5 = (*t4);
 t6 = t5 != NULL;
 if (t6) {
  /* file:4:56 */
  panic_fail__974(UINT32_C(28), (uintptr_t)0ul, (uintptr_t)0ul);
  zig_unreachable();
 }
 goto zig_block_3;

zig_block_3:;
 /* file:5:13 */
 (void)0;
 goto zig_block_2;

zig_block_2:;
 return;
}
static void verifier_assume__295(bool const a0) {
 /* file:2:20 */
 verifier_assume(a0);
 return;
}
static uintptr_t verifier_any__anon_1842__1335(void) {
 void *t1;
 uint64_t t2;
 uint64_t t0;
 uintptr_t t3;
 /* file:2:13 */
 /* dbg_var_val:int */
 /* file:7:13 */
 memset(&t0, 0xaa, sizeof(uint64_t));
 /* dbg_var_ptr:backing */
 /* file:8:25 */
 t1 = (void *)&t0;
 /* file:8:25 */
 verifier_any(t1, (uintptr_t)8ul);
 /* file:10:13 */
 t2 = t0;
 /* file:10:43 */
 t3 = t2;
 /* file:10:13 */
 return t3;
}
static struct Target_DynamicLinker_728 const Target_DynamicLinker_none__1108 = {{"\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},UINT8_C(0)};
static struct Target_Cpu_Model_732 const Target_x86_cpu_znver4__1316 = {{((uint8_t const *)((struct arr_6s116_u8_1875 const *)&__anon_1876)),6ul},{((uint8_t const *)((struct arr_6s116_u8_1875 const *)&__anon_1876)),6ul},{{{177989145354830000ul,14125804287856987392ul,8071020079954911744ul,229ul,0ul}}}};
void allocation_dupe_pair_never_leaks__218(void) {
 struct verifier_FailingAllocator_2832_2c2_29_187 t0;
 struct mem_Allocator_203 t1;
 struct mem_Allocator_203 t2;
 struct mem_Allocator_203 const *t3;
 struct slice_u8_216 t6;
 struct slice_u8_216 t7;
 struct slice_u8_216 t16;
 struct slice_u8_50 t8;
 struct slice_u8_50 t9;
 struct errunion_allocation_Pair_214 t10;
 struct allocation_Pair_214 t12;
 struct allocation_Pair_214 t13;
 struct allocation_Pair_214 const *t14;
 struct slice_u8_216 const *t15;
 struct verifier_FailingAllocator_2832_2c2_29_187 const *t17;
 bool t11;
 struct arr_8_u8_1821 t4;
 struct arr_8_u8_1821 t5;
 /* file:2:5 */
 t0 = (struct verifier_FailingAllocator_2832_2c2_29_187){{"\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},(uintptr_t)0ul,{{NULL,NULL}}};
 /* dbg_var_ptr:failing */
 /* file:3:34 */
 t1 = verifier_FailingAllocator_2832_2c2_29_allocator__301(&t0);
 t2 = t1;
 t3 = (struct mem_Allocator_203 const *)&t2;
 /* dbg_var_val:gpa */
 /* file:4:5 */
 memset(&t4, 0xaa, sizeof(struct arr_8_u8_1821));
 /* dbg_var_ptr:first_buffer */
 /* file:5:5 */
 memset(&t5, 0xaa, sizeof(struct arr_8_u8_1821));
 /* dbg_var_ptr:second_buffer */
 /* file:6:34 */
 t6.ptr = (uint8_t *)&t4;
 t6.len = (uintptr_t)8ul;
 /* file:6:34 */
 t6 = verifier_prefix__anon_1828__1334(t6);
 /* dbg_var_val:first */
 /* file:7:35 */
 t7.ptr = (uint8_t *)&t5;
 t7.len = (uintptr_t)8ul;
 /* file:7:35 */
 t7 = verifier_prefix__anon_1828__1334(t7);
 /* dbg_var_val:second */
 /* file:8:9 */
 /* file:8:17 */
 memcpy(&t8, &t6, 16);
 memcpy(&t9, &t7, 16);
 /* file:8:17 */
 t10 = allocation_dupePair__215(t1, t8, t9);
 t11 = t10.error == UINT16_C(0);
 if (t11) {
  t12 = t10.payload;
  t13 = t12;
  t14 = (struct allocation_Pair_214 const *)&t13;
  /* dbg_var_val:pair */
  /* file:9:45 */
  t15 = (struct slice_u8_216 const *)&t14->first;
  t16 = (*t15);
  memcpy(&t9, &t16, 16);
  memcpy(&t8, &t6, 16);
  /* file:9:36 */
  t11 = mem_eql__anon_2015__1337(t9, t8);
  /* file:9:24 */
  verifier_assert__296(t11);
  /* file:10:45 */
  t15 = (struct slice_u8_216 const *)&t14->second;
  t6 = (*t15);
  memcpy(&t8, &t6, 16);
  memcpy(&t9, &t7, 16);
  /* file:10:36 */
  t11 = mem_eql__anon_2015__1337(t8, t9);
  /* file:10:24 */
  verifier_assert__296(t11);
  /* file:11:17 */
  t1 = (*t3);
  /* file:11:22 */
  t15 = (struct slice_u8_216 const *)&t14->first;
  t7 = (*t15);
  /* file:11:17 */
  mem_Allocator_free__anon_253__638(t1, t7);
  /* file:12:17 */
  t1 = (*t3);
  /* file:12:22 */
  t15 = (struct slice_u8_216 const *)&t14->second;
  t7 = (*t15);
  /* file:12:17 */
  mem_Allocator_free__anon_253__638(t1, t7);
  goto zig_block_0;
 }
 goto zig_block_0;

zig_block_0:;
 /* file:14:26 */
 t17 = (struct verifier_FailingAllocator_2832_2c2_29_187 const *)&t0;
 /* file:14:26 */
 verifier_FailingAllocator_2832_2c2_29_assertNoLeaks__302(t17);
 return;
}
static enum__builtin_CompilerBackend_2025 const builtin_zig_backend__224 = UINT64_C(3);
static bool const mem_use_vectors__333 = true;
static bool const builtin_fuzz__241 = true;
static bool const mem_use_vectors_for_comparison__334 = false;
static bool mem_eql__anon_2015__1337(struct slice_u8_50 const a0, struct slice_u8_50 const a1) {
 struct slice_u8_50 const *t1;
 struct slice_u8_50 const *t3;
 uintptr_t const *t4;
 uintptr_t t5;
 uintptr_t t6;
 uintptr_t t14;
 uint64_t t7;
 uint64_t t8;
 uint8_t const *const *t11;
 uint8_t const *t12 zig_nonstring;
 uint8_t const *t13 zig_nonstring;
 struct slice_u8_50 t0;
 struct slice_u8_50 t2;
 bool t9;
 bool t10;
 uint8_t t15;
 uint8_t t16;
 t0 = a0;
 t1 = (struct slice_u8_50 const *)&t0;
 t2 = a1;
 t3 = (struct slice_u8_50 const *)&t2;
 /* file:2:9 */
 /* file:2:80 */
 /* inline:meta.hasUniqueRepresentation */
 /* file:2:20 */
 /* dbg_var_val:info */
 /* file:13:46 */
 goto zig_block_1;

zig_block_1:;
 /* file:2:5 */
 goto zig_block_0;

zig_block_0:;
 /* file:8:9 */
 /* file:8:10 */
 t4 = &t1->len;
 t5 = (*t4);
 /* file:8:19 */
 t4 = &t3->len;
 t6 = (*t4);
 t7 = t5;
 t8 = t6;
 t9 = t7 != t8;
 if (t9) {
  /* file:8:25 */
  return false;
 }
 goto zig_block_2;

zig_block_2:;
 /* file:9:9 */
 /* file:9:10 */
 t4 = &t1->len;
 t6 = (*t4);
 t8 = t6;
 t9 = t8 == UINT64_C(0);
 if (t9) {
  t10 = true;
  goto zig_block_4;
 }
 /* file:9:24 */
 t11 = &t1->ptr;
 t12 = (*t11);
 /* file:9:33 */
 t11 = &t3->ptr;
 t13 = (*t11);
 t9 = t12 == t13;
 t10 = t9;
 goto zig_block_4;

zig_block_4:;
 if (t10) {
  /* file:9:39 */
  return true;
 }
 goto zig_block_3;

zig_block_3:;
 t14 = (uintptr_t)0ul;
 /* file:11:13 */
 t6 = a0.len;
 t5 = a1.len;
 t10 = t6 == t5;
 if (t10) {
  goto zig_block_5;
 }
 panic_forLenMismatch__997();
 zig_unreachable();

zig_block_5:;
 zig_loop_69:
 t5 = t14;
 t8 = t5;
 t7 = t6;
 t10 = t8 < t7;
 if (t10) {
  t15 = a0.ptr[t5];
  /* dbg_var_val:a_elem */
  t16 = a1.ptr[t5];
  /* dbg_var_val:b_elem */
  /* file:12:13 */
  t10 = t15 != t16;
  if (t10) {
   /* file:12:31 */
   return false;
  }
  goto zig_block_8;

zig_block_8:;
  /* file:13:5 */
  (void)0;
  goto zig_block_7;
 }
 goto zig_block_6;

zig_block_7:;
 t5 = t5 + (uintptr_t)1ul;
 t14 = t5;
 goto zig_loop_69;

zig_block_6:;
 /* file:14:5 */
 return true;
}
static void verifier_assert__296(bool const a0) {
 /* file:2:19 */
 verifier_check(a0);
 return;
}
static zig_noreturn void panic_forLenMismatch__997(void) {
 /* file:2:9 */
 panic_fail__974(UINT32_C(23), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
