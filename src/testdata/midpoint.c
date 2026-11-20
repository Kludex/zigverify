#define ZIG_TARGET_MAX_INT_ALIGNMENT 16
#include "zig.h"
struct slice_u8_51 { /* [:0]const u8 */
 uint8_t const *ptr;
 size_t len;
};
typedef uint8_t enum__builtin_OutputMode_147; /* builtin.OutputMode */
struct arr_16_u8_179 { uint8_t array[16] zig_nonstring; }; /* [16]u8 */
zig_static_assert(sizeof (struct arr_16_u8_179) == 16, "incorrect size");
zig_static_assert(_Alignof (struct arr_16_u8_179) == 1, "incorrect alignment");
struct slice_u8_189 { /* []u8 */
 uint8_t *ptr zig_nonstring;
 size_t len;
};
struct tuple_2_u8_u1_805306368 { /* struct { u8, u1 } */
 uint8_t f0;
 uint8_t f1;
};
zig_static_assert(sizeof (struct tuple_2_u8_u1_805306368) == 2, "incorrect size");
zig_static_assert(_Alignof (struct tuple_2_u8_u1_805306368) == 1, "incorrect alignment");
struct arr_5_usize_621 { uintptr_t array[5]; }; /* [5]usize */
zig_static_assert(sizeof (struct arr_5_usize_621) == 40, "incorrect size");
zig_static_assert(_Alignof (struct arr_5_usize_621) == 8, "incorrect alignment");
struct Target_Cpu_Feature_Set_608 { /* Target.Cpu.Feature.Set */
 struct arr_5_usize_621 ints;
};
zig_static_assert(sizeof (struct Target_Cpu_Feature_Set_608) == 40, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_Feature_Set_608) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Cpu_Arch_601; /* Target.Cpu.Arch */
struct Target_Cpu_Model_603;
struct Target_Cpu_591 { /* Target.Cpu */
 struct Target_Cpu_Model_603 const *model;
 struct Target_Cpu_Feature_Set_608 features;
 enum__Target_Cpu_Arch_601 arch;
};
zig_static_assert(sizeof (struct Target_Cpu_591) == 56, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_591) == 8, "incorrect alignment");
struct slice_u8_50 { /* []const u8 */
 uint8_t const *ptr zig_nonstring;
 size_t len;
};
struct Target_Cpu_Model_603 { /* Target.Cpu.Model */
 struct slice_u8_50 name;
 struct slice_u8_51 llvm_name;
 struct Target_Cpu_Feature_Set_608 features;
};
zig_static_assert(sizeof (struct Target_Cpu_Model_603) == 72, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_Model_603) == 8, "incorrect alignment");
struct SemanticVersion_628 { /* SemanticVersion */
 uintptr_t major;
 uintptr_t minor;
 uintptr_t patch;
 struct slice_u8_50 pre;
 struct slice_u8_50 build;
};
zig_static_assert(sizeof (struct SemanticVersion_628) == 56, "incorrect size");
zig_static_assert(_Alignof (struct SemanticVersion_628) == 8, "incorrect alignment");
struct SemanticVersion_Range_630 { /* SemanticVersion.Range */
 struct SemanticVersion_628 zig_e_min;
 struct SemanticVersion_628 zig_e_max;
};
zig_static_assert(sizeof (struct SemanticVersion_Range_630) == 112, "incorrect size");
zig_static_assert(_Alignof (struct SemanticVersion_Range_630) == 8, "incorrect alignment");
struct Target_Os_HurdVersionRange_632 { /* Target.Os.HurdVersionRange */
 struct SemanticVersion_Range_630 range;
 struct SemanticVersion_628 glibc;
};
zig_static_assert(sizeof (struct Target_Os_HurdVersionRange_632) == 168, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_HurdVersionRange_632) == 8, "incorrect alignment");
struct Target_Os_LinuxVersionRange_634 { /* Target.Os.LinuxVersionRange */
 struct SemanticVersion_Range_630 range;
 struct SemanticVersion_628 glibc;
 uint32_t android;
};
zig_static_assert(sizeof (struct Target_Os_LinuxVersionRange_634) == 176, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_LinuxVersionRange_634) == 8, "incorrect alignment");
typedef uint32_t enum__Target_Os_WindowsVersion_636; /* Target.Os.WindowsVersion */
struct Target_Os_WindowsVersion_Range_638 { /* Target.Os.WindowsVersion.Range */
 enum__Target_Os_WindowsVersion_636 zig_e_min;
 enum__Target_Os_WindowsVersion_636 zig_e_max;
};
zig_static_assert(sizeof (struct Target_Os_WindowsVersion_Range_638) == 8, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_WindowsVersion_Range_638) == 4, "incorrect alignment");
typedef uint8_t enum___40typeInfo_28Target_Os_VersionRange_29__40_22union_22_tag_type__3f_626; /* @typeInfo(Target.Os.VersionRange).@"union".tag_type.? */
struct Target_Os_VersionRange_624 { /* Target.Os.VersionRange */
 union {
  struct SemanticVersion_Range_630 semver;
  struct Target_Os_HurdVersionRange_632 hurd;
  struct Target_Os_LinuxVersionRange_634 linux;
  struct Target_Os_WindowsVersion_Range_638 windows;
 } payload;
 enum___40typeInfo_28Target_Os_VersionRange_29__40_22union_22_tag_type__3f_626 tag;
};
zig_static_assert(sizeof (struct Target_Os_VersionRange_624) == 184, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_VersionRange_624) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Os_Tag_622; /* Target.Os.Tag */
struct Target_Os_593 { /* Target.Os */
 struct Target_Os_VersionRange_624 version_range;
 enum__Target_Os_Tag_622 tag;
};
zig_static_assert(sizeof (struct Target_Os_593) == 192, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_593) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Abi_595; /* Target.Abi */
typedef uint8_t enum__Target_ObjectFormat_597; /* Target.ObjectFormat */
struct arr_255_u8_695 { uint8_t array[255] zig_nonstring; }; /* [255]u8 */
zig_static_assert(sizeof (struct arr_255_u8_695) == 255, "incorrect size");
zig_static_assert(_Alignof (struct arr_255_u8_695) == 1, "incorrect alignment");
struct Target_DynamicLinker_599 { /* Target.DynamicLinker */
 struct arr_255_u8_695 buffer;
 uint8_t len;
};
zig_static_assert(sizeof (struct Target_DynamicLinker_599) == 256, "incorrect size");
zig_static_assert(_Alignof (struct Target_DynamicLinker_599) == 1, "incorrect alignment");
struct Target_589 { /* Target */
 struct Target_Cpu_591 cpu;
 struct Target_Os_593 os;
 enum__Target_Abi_595 abi;
 enum__Target_ObjectFormat_597 ofmt;
 struct Target_DynamicLinker_599 dynamic_linker;
};
zig_static_assert(sizeof (struct Target_589) == 512, "incorrect size");
zig_static_assert(_Alignof (struct Target_589) == 8, "incorrect alignment");
struct opt_u64_436 { /* ?u64 */
 uint64_t payload;
 bool is_null;
};
zig_static_assert(sizeof (struct opt_u64_436) == 16, "incorrect size");
zig_static_assert(_Alignof (struct opt_u64_436) == 8, "incorrect alignment");
struct builtin_CallingConvention_CommonOptions_420 { /* builtin.CallingConvention.CommonOptions */
 struct opt_u64_436 incoming_stack_alignment;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_CommonOptions_420) == 16, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_CommonOptions_420) == 8, "incorrect alignment");
struct builtin_CallingConvention_X86RegparmOptions_422 { /* builtin.CallingConvention.X86RegparmOptions */
 struct opt_u64_436 incoming_stack_alignment;
 uint8_t register_params;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_X86RegparmOptions_422) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_X86RegparmOptions_422) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ArmInterruptOptions_InterruptType_437; /* builtin.CallingConvention.ArmInterruptOptions.InterruptType */
struct builtin_CallingConvention_ArmInterruptOptions_424 { /* builtin.CallingConvention.ArmInterruptOptions */
 struct opt_u64_436 incoming_stack_alignment;
 enum__builtin_CallingConvention_ArmInterruptOptions_InterruptType_437 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ArmInterruptOptions_424) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ArmInterruptOptions_424) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_MipsInterruptOptions_InterruptMode_446; /* builtin.CallingConvention.MipsInterruptOptions.InterruptMode */
struct builtin_CallingConvention_MipsInterruptOptions_426 { /* builtin.CallingConvention.MipsInterruptOptions */
 struct opt_u64_436 incoming_stack_alignment;
 enum__builtin_CallingConvention_MipsInterruptOptions_InterruptMode_446 mode;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_MipsInterruptOptions_426) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_MipsInterruptOptions_426) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_RiscvInterruptOptions_PrivilegeMode_458; /* builtin.CallingConvention.RiscvInterruptOptions.PrivilegeMode */
struct builtin_CallingConvention_RiscvInterruptOptions_428 { /* builtin.CallingConvention.RiscvInterruptOptions */
 struct opt_u64_436 incoming_stack_alignment;
 enum__builtin_CallingConvention_RiscvInterruptOptions_PrivilegeMode_458 mode;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_RiscvInterruptOptions_428) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_RiscvInterruptOptions_428) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ArcInterruptOptions_InterruptType_460; /* builtin.CallingConvention.ArcInterruptOptions.InterruptType */
struct builtin_CallingConvention_ArcInterruptOptions_430 { /* builtin.CallingConvention.ArcInterruptOptions */
 struct opt_u64_436 incoming_stack_alignment;
 enum__builtin_CallingConvention_ArcInterruptOptions_InterruptType_460 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ArcInterruptOptions_430) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ArcInterruptOptions_430) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_MicroblazeInterruptOptions_InterruptType_463; /* builtin.CallingConvention.MicroblazeInterruptOptions.InterruptType */
struct builtin_CallingConvention_MicroblazeInterruptOptions_432 { /* builtin.CallingConvention.MicroblazeInterruptOptions */
 struct opt_u64_436 incoming_stack_alignment;
 enum__builtin_CallingConvention_MicroblazeInterruptOptions_InterruptType_463 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_MicroblazeInterruptOptions_432) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_MicroblazeInterruptOptions_432) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ShInterruptOptions_SaveBehavior_465; /* builtin.CallingConvention.ShInterruptOptions.SaveBehavior */
struct builtin_CallingConvention_ShInterruptOptions_434 { /* builtin.CallingConvention.ShInterruptOptions */
 struct opt_u64_436 incoming_stack_alignment;
 enum__builtin_CallingConvention_ShInterruptOptions_SaveBehavior_465 save;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ShInterruptOptions_434) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ShInterruptOptions_434) == 8, "incorrect alignment");
typedef uint8_t enum___40typeInfo_28builtin_CallingConvention_29__40_22union_22_tag_type__3f_324; /* @typeInfo(builtin.CallingConvention).@"union".tag_type.? */
struct builtin_CallingConvention_322 { /* builtin.CallingConvention */
 union {
  struct builtin_CallingConvention_CommonOptions_420 x86_64_sysv;
  struct builtin_CallingConvention_CommonOptions_420 x86_64_x32;
  struct builtin_CallingConvention_CommonOptions_420 x86_64_win;
  struct builtin_CallingConvention_CommonOptions_420 x86_64_regcall_v3_sysv;
  struct builtin_CallingConvention_CommonOptions_420 x86_64_regcall_v4_win;
  struct builtin_CallingConvention_CommonOptions_420 x86_64_vectorcall;
  struct builtin_CallingConvention_CommonOptions_420 x86_64_interrupt;
  struct builtin_CallingConvention_X86RegparmOptions_422 x86_sysv;
  struct builtin_CallingConvention_X86RegparmOptions_422 x86_win;
  struct builtin_CallingConvention_X86RegparmOptions_422 x86_stdcall;
  struct builtin_CallingConvention_CommonOptions_420 x86_fastcall;
  struct builtin_CallingConvention_CommonOptions_420 x86_thiscall;
  struct builtin_CallingConvention_CommonOptions_420 x86_thiscall_mingw;
  struct builtin_CallingConvention_CommonOptions_420 x86_regcall_v3;
  struct builtin_CallingConvention_CommonOptions_420 x86_regcall_v4_win;
  struct builtin_CallingConvention_CommonOptions_420 x86_vectorcall;
  struct builtin_CallingConvention_CommonOptions_420 x86_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 x86_16_cdecl;
  struct builtin_CallingConvention_CommonOptions_420 x86_16_stdcall;
  struct builtin_CallingConvention_CommonOptions_420 x86_16_regparmcall;
  struct builtin_CallingConvention_CommonOptions_420 x86_16_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 aarch64_aapcs;
  struct builtin_CallingConvention_CommonOptions_420 aarch64_aapcs_darwin;
  struct builtin_CallingConvention_CommonOptions_420 aarch64_aapcs_win;
  struct builtin_CallingConvention_CommonOptions_420 aarch64_vfabi;
  struct builtin_CallingConvention_CommonOptions_420 aarch64_vfabi_sve;
  struct builtin_CallingConvention_CommonOptions_420 alpha_osf;
  struct builtin_CallingConvention_CommonOptions_420 arm_aapcs;
  struct builtin_CallingConvention_CommonOptions_420 arm_aapcs_vfp;
  struct builtin_CallingConvention_ArmInterruptOptions_424 arm_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 mips64_n64;
  struct builtin_CallingConvention_CommonOptions_420 mips64_n32;
  struct builtin_CallingConvention_MipsInterruptOptions_426 mips64_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 mips_o32;
  struct builtin_CallingConvention_MipsInterruptOptions_426 mips_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 riscv64_lp64;
  struct builtin_CallingConvention_CommonOptions_420 riscv64_lp64_v;
  struct builtin_CallingConvention_RiscvInterruptOptions_428 riscv64_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 riscv32_ilp32;
  struct builtin_CallingConvention_CommonOptions_420 riscv32_ilp32_v;
  struct builtin_CallingConvention_RiscvInterruptOptions_428 riscv32_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 sparc64_sysv;
  struct builtin_CallingConvention_CommonOptions_420 sparc_sysv;
  struct builtin_CallingConvention_CommonOptions_420 powerpc64_elf;
  struct builtin_CallingConvention_CommonOptions_420 powerpc64_elf_altivec;
  struct builtin_CallingConvention_CommonOptions_420 powerpc64_elf_v2;
  struct builtin_CallingConvention_CommonOptions_420 powerpc_sysv;
  struct builtin_CallingConvention_CommonOptions_420 powerpc_sysv_altivec;
  struct builtin_CallingConvention_CommonOptions_420 powerpc_aix;
  struct builtin_CallingConvention_CommonOptions_420 powerpc_aix_altivec;
  struct builtin_CallingConvention_CommonOptions_420 wasm_mvp;
  struct builtin_CallingConvention_CommonOptions_420 arc_sysv;
  struct builtin_CallingConvention_ArcInterruptOptions_430 arc_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 bpf_std;
  struct builtin_CallingConvention_CommonOptions_420 csky_sysv;
  struct builtin_CallingConvention_CommonOptions_420 csky_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 hexagon_sysv;
  struct builtin_CallingConvention_CommonOptions_420 hexagon_sysv_hvx;
  struct builtin_CallingConvention_CommonOptions_420 hppa_elf;
  struct builtin_CallingConvention_CommonOptions_420 hppa64_elf;
  struct builtin_CallingConvention_CommonOptions_420 kvx_lp64;
  struct builtin_CallingConvention_CommonOptions_420 kvx_ilp32;
  struct builtin_CallingConvention_CommonOptions_420 lanai_sysv;
  struct builtin_CallingConvention_CommonOptions_420 loongarch64_lp64;
  struct builtin_CallingConvention_CommonOptions_420 loongarch32_ilp32;
  struct builtin_CallingConvention_CommonOptions_420 m68k_sysv;
  struct builtin_CallingConvention_CommonOptions_420 m68k_gnu;
  struct builtin_CallingConvention_CommonOptions_420 m68k_rtd;
  struct builtin_CallingConvention_CommonOptions_420 m68k_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 microblaze_std;
  struct builtin_CallingConvention_MicroblazeInterruptOptions_432 microblaze_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 msp430_eabi;
  struct builtin_CallingConvention_CommonOptions_420 msp430_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 or1k_sysv;
  struct builtin_CallingConvention_CommonOptions_420 propeller_sysv;
  struct builtin_CallingConvention_CommonOptions_420 s390x_sysv;
  struct builtin_CallingConvention_CommonOptions_420 s390x_sysv_vx;
  struct builtin_CallingConvention_CommonOptions_420 sh_gnu;
  struct builtin_CallingConvention_CommonOptions_420 sh_renesas;
  struct builtin_CallingConvention_ShInterruptOptions_434 sh_interrupt;
  struct builtin_CallingConvention_CommonOptions_420 ve_sysv;
  struct builtin_CallingConvention_CommonOptions_420 xcore_xs1;
  struct builtin_CallingConvention_CommonOptions_420 xcore_xs2;
  struct builtin_CallingConvention_CommonOptions_420 xtensa_call0;
  struct builtin_CallingConvention_CommonOptions_420 xtensa_windowed;
  struct builtin_CallingConvention_CommonOptions_420 amdgcn_device;
  struct builtin_CallingConvention_CommonOptions_420 amdgcn_cs;
 } payload;
 enum___40typeInfo_28builtin_CallingConvention_29__40_22union_22_tag_type__3f_324 tag;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_322) == 32, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_322) == 8, "incorrect alignment");
typedef uint32_t enum__failure_Kind_1516; /* failure.Kind */
struct tuple_2_u32_u1_134217728 { /* struct { u32, u1 } */
 uint32_t f0;
 uint8_t f1;
};
zig_static_assert(sizeof (struct tuple_2_u32_u1_134217728) == 8, "incorrect size");
zig_static_assert(_Alignof (struct tuple_2_u32_u1_134217728) == 4, "incorrect alignment");
struct arr_6s116_u8_1620 { uint8_t array[7]; }; /* [6:0]u8 */
zig_static_assert(sizeof (struct arr_6s116_u8_1620) == 7, "incorrect size");
zig_static_assert(_Alignof (struct arr_6s116_u8_1620) == 1, "incorrect alignment");
#define midpoint_count_zeros_never_panics__218 count_zeros_never_panics
zig_extern void count_zeros_never_panics(void);
#define midpoint_midpoint_is_below_high__217 midpoint_is_below_high
zig_extern void midpoint_is_below_high(void);
#define midpoint_midpoint_is_between__216 midpoint_is_between
zig_extern void midpoint_is_between(void);
#define midpoint_naive_midpoint_never_panics__215 naive_midpoint_never_panics
zig_extern void naive_midpoint_never_panics(void);
static struct arr_6s116_u8_1620 const __anon_1621;
static enum__builtin_OutputMode_147 const builtin_output_mode__223;
static struct slice_u8_189 verifier_prefix__anon_191__298(struct slice_u8_189 a0);
static struct Target_Cpu_Feature_Set_608 const Target_Cpu_Feature_Set_empty__548;
static struct Target_Cpu_591 const builtin_cpu__229;
static struct Target_Os_593 const builtin_os__230;
static enum__Target_Abi_595 const builtin_abi__228;
static enum__Target_ObjectFormat_597 const builtin_object_format__232;
static struct Target_589 const builtin_target__231;
static struct builtin_CallingConvention_322 const builtin_CallingConvention_c__331;
zig_extern void verifier_check(bool a0);
static void verifier_assert__294(bool a0);
static zig_noreturn void panic_outOfBounds__305(uintptr_t a0, uintptr_t a1);
zig_extern void verifier_assume(bool a0);
static void verifier_assume__293(bool a0);
zig_extern zig_noreturn void verifier_fail(uint32_t a0, uintptr_t a1, uintptr_t a2);
static zig_cold zig_noreturn void panic_fail__301(enum__failure_Kind_1516 a0, uintptr_t a1, uintptr_t a2);
zig_extern void verifier_any(void *a0, uintptr_t a1);
static uintptr_t verifier_any__anon_288__329(void);
static zig_noreturn void panic_noreturnReturned__327(void);
static uint8_t verifier_any__anon_286__328(void);
static zig_noreturn void panic_integerOverflow__315(void);
static uint32_t verifier_any__anon_1586__979(void);
static uint32_t midpoint_midpoint__214(uint32_t a0, uint32_t a1);
static struct Target_DynamicLinker_599 const Target_DynamicLinker_none__495;
static struct Target_Cpu_Model_603 const Target_x86_cpu_znver4__703;
static uint32_t midpoint_midpointNaive__213(uint32_t a0, uint32_t a1);
static struct slice_u8_51 const zig_errorName[0] = {};
static struct arr_6s116_u8_1620 const __anon_1621 = {"znver4"};
static enum__builtin_OutputMode_147 const builtin_output_mode__223 = UINT8_C(2);
void midpoint_count_zeros_never_panics__218(void) {
 struct slice_u8_189 t3;
 uintptr_t t4;
 uintptr_t t5;
 uintptr_t t2;
 uint64_t t6;
 uint64_t t7;
 bool t8;
 uint8_t t9;
 uint8_t t10;
 uint8_t t1;
 struct tuple_2_u8_u1_805306368 t11;
 uint8_t t12;
 struct arr_16_u8_179 t0;
 /* file:2:5 */
 memset(&t0, 0xaa, sizeof(struct arr_16_u8_179));
 /* dbg_var_ptr:buffer */
 /* file:3:5 */
 t1 = UINT8_C(0);
 /* dbg_var_ptr:zeros */
 t2 = (uintptr_t)0ul;
 /* file:4:25 */
 t3.ptr = (uint8_t *)&t0;
 t3.len = (uintptr_t)16ul;
 /* file:4:25 */
 t3 = verifier_prefix__anon_191__298(t3);
 t4 = t3.len;
 zig_loop_17:
 t5 = t2;
 t6 = t5;
 t7 = t4;
 t8 = t6 < t7;
 if (t8) {
  t9 = t3.ptr[t5];
  /* dbg_var_val:byte */
  /* file:5:13 */
  t8 = t9 == UINT8_C(0);
  if (t8) {
   /* file:5:24 */
   t9 = t1;
   /* file:5:30 */
   t11.f1 = zig_addo_u8(&t11.f0, t9, UINT8_C(1), UINT8_C(8));
   t12 = t11.f1;
   t8 = t12 == UINT8_C(1);
   if (t8) {
    panic_integerOverflow__315();
    zig_unreachable();
   }
   t9 = t11.f0;
   t10 = t9;
   goto zig_block_3;

zig_block_3:;
   t1 = t10;
   goto zig_block_2;
  }
  goto zig_block_2;

zig_block_2:;
  /* file:6:5 */
  (void)0;
  goto zig_block_1;
 }
 goto zig_block_0;

zig_block_1:;
 t5 = t5 + (uintptr_t)1ul;
 t2 = t5;
 goto zig_loop_17;

zig_block_0:;
 /* file:7:20 */
 t10 = t1;
 t8 = t10 <= UINT8_C(16);
 /* file:7:20 */
 verifier_assert__294(t8);
 return;
}
static struct slice_u8_189 verifier_prefix__anon_191__298(struct slice_u8_189 const a0) {
 struct slice_u8_189 const *t1;
 uintptr_t t3;
 uintptr_t t4;
 uintptr_t t13;
 uintptr_t t2;
 uint64_t t5;
 uint64_t t6;
 uint8_t *t8 zig_nonstring;
 uintptr_t const *t10;
 struct slice_u8_189 t11;
 struct slice_u8_189 t0;
 uint8_t *t12 zig_nonstring;
 bool t7;
 uint8_t t9;
 t0 = a0;
 t1 = (struct slice_u8_189 const *)&t0;
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
  t9 = verifier_any__anon_286__328();
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
 t3 = verifier_any__anon_288__329();
 /* dbg_var_val:len */
 /* file:4:25 */
 t10 = &t1->len;
 t4 = (*t10);
 t6 = t3;
 t5 = t4;
 t7 = t6 <= t5;
 /* file:4:11 */
 verifier_assume__293(t7);
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
 panic_outOfBounds__305(t3, t13);
 zig_unreachable();

zig_block_2:;
 t11.ptr = t12;
 t11.len = t4;
 /* file:5:5 */
 return t11;
}
static struct Target_Cpu_Feature_Set_608 const Target_Cpu_Feature_Set_empty__548 = {{{0ul,0ul,0ul,0ul,0ul}}};
static struct Target_Cpu_591 const builtin_cpu__229 = {(((struct Target_Cpu_Model_603 const *)&Target_x86_cpu_znver4__703)),{{{14373335171114205424ul,10664787974256315648ul,8073817237535973888ul,244ul,0ul}}},UINT8_C(54)};
static struct Target_Os_593 const builtin_os__230 = {{ .tag = UINT8_C(3), .payload = { .linux = {{{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}}},{2ul,43ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},UINT32_C(29)} } },UINT8_C(9)};
static enum__Target_Abi_595 const builtin_abi__228 = UINT8_C(1);
static enum__Target_ObjectFormat_597 const builtin_object_format__232 = UINT8_C(0);
static struct Target_589 const builtin_target__231 = {{(((struct Target_Cpu_Model_603 const *)&Target_x86_cpu_znver4__703)),{{{14373335171114205424ul,10664787974256315648ul,8073817237535973888ul,244ul,0ul}}},UINT8_C(54)},{{ .tag = UINT8_C(3), .payload = { .linux = {{{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}}},{2ul,43ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},UINT32_C(29)} } },UINT8_C(9)},UINT8_C(1),UINT8_C(0),{{"/lib64/ld-linux-x86-64.so.2\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},UINT8_C(27)}};
static struct builtin_CallingConvention_322 const builtin_CallingConvention_c__331 = { .tag = UINT8_C(4), .payload = { .x86_64_sysv = {{ .is_null = true, .payload = UINT64_C(0xaaaaaaaaaaaaaaaa) }} } };
static void verifier_assert__294(bool const a0) {
 /* file:2:19 */
 verifier_check(a0);
 return;
}
static zig_noreturn void panic_outOfBounds__305(uintptr_t const a0, uintptr_t const a1) {
 /* file:2:9 */
 panic_fail__301(UINT32_C(4), a0, a1);
 zig_unreachable();
}
static void verifier_assume__293(bool const a0) {
 /* file:2:20 */
 verifier_assume(a0);
 return;
}
static zig_cold zig_noreturn void panic_fail__301(enum__failure_Kind_1516 const a0, uintptr_t const a1, uintptr_t const a2) {
 uint32_t t0;
 /* file:3:18 */
 t0 = a0;
 /* file:3:18 */
 verifier_fail(t0, a1, a2);
 panic_noreturnReturned__327();
 zig_unreachable();
}
static uintptr_t verifier_any__anon_288__329(void) {
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
static zig_noreturn void panic_noreturnReturned__327(void) {
 /* file:2:9 */
 panic_fail__301(UINT32_C(26), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static uint8_t verifier_any__anon_286__328(void) {
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
static zig_noreturn void panic_integerOverflow__315(void) {
 /* file:2:9 */
 panic_fail__301(UINT32_C(14), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
void midpoint_midpoint_is_below_high__217(void) {
 uint32_t t0;
 uint32_t t1;
 uint32_t t3;
 bool t2;
 /* file:2:29 */
 t0 = verifier_any__anon_1586__979();
 /* dbg_var_val:low */
 /* file:3:30 */
 t1 = verifier_any__anon_1586__979();
 /* dbg_var_val:high */
 /* file:4:20 */
 t2 = t0 <= t1;
 /* file:4:20 */
 verifier_assume__293(t2);
 /* file:5:36 */
 t3 = midpoint_midpoint__214(t0, t1);
 t2 = t0 <= t3;
 /* file:5:20 */
 verifier_assert__294(t2);
 /* file:6:29 */
 t0 = midpoint_midpoint__214(t0, t1);
 t2 = t0 < t1;
 /* file:6:20 */
 verifier_assert__294(t2);
 return;
}
static uint32_t verifier_any__anon_1586__979(void) {
 void *t1;
 uint32_t t2;
 uint32_t t0;
 /* file:2:13 */
 /* dbg_var_val:int */
 /* file:7:13 */
 memset(&t0, 0xaa, sizeof(uint32_t));
 /* dbg_var_ptr:backing */
 /* file:8:25 */
 t1 = (void *)&t0;
 /* file:8:25 */
 verifier_any(t1, (uintptr_t)4ul);
 /* file:10:13 */
 t2 = t0;
 /* file:10:43 */
 /* file:10:13 */
 return t2;
}
static uint32_t midpoint_midpoint__214(uint32_t const a0, uint32_t const a1) {
 uint32_t t0;
 uint32_t t4;
 struct tuple_2_u32_u1_134217728 t1;
 uint8_t t2;
 bool t3;
 /* file:2:24 */
 t1.f1 = zig_subo_u32(&t1.f0, a1, a0, UINT8_C(32));
 t2 = t1.f1;
 t3 = t2 == UINT8_C(1);
 if (t3) {
  panic_integerOverflow__315();
  zig_unreachable();
 }
 t4 = t1.f0;
 t0 = t4;
 goto zig_block_0;

zig_block_0:;
 /* file:2:31 */
 t0 = t0 / UINT32_C(2);
 /* file:2:16 */
 t1.f1 = zig_addo_u32(&t1.f0, a0, t0, UINT8_C(32));
 t2 = t1.f1;
 t3 = t2 == UINT8_C(1);
 if (t3) {
  panic_integerOverflow__315();
  zig_unreachable();
 }
 t0 = t1.f0;
 t4 = t0;
 goto zig_block_1;

zig_block_1:;
 /* file:2:5 */
 return t4;
}
static struct Target_DynamicLinker_599 const Target_DynamicLinker_none__495 = {{"\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},UINT8_C(0)};
static struct Target_Cpu_Model_603 const Target_x86_cpu_znver4__703 = {{((uint8_t const *)((struct arr_6s116_u8_1620 const *)&__anon_1621)),6ul},{((uint8_t const *)((struct arr_6s116_u8_1620 const *)&__anon_1621)),6ul},{{{177989145354830000ul,14125804287856987392ul,8071020079954911744ul,229ul,0ul}}}};
void midpoint_midpoint_is_between__216(void) {
 uint32_t t0;
 uint32_t t1;
 uint32_t t3;
 bool t2;
 /* file:2:29 */
 t0 = verifier_any__anon_1586__979();
 /* dbg_var_val:low */
 /* file:3:30 */
 t1 = verifier_any__anon_1586__979();
 /* dbg_var_val:high */
 /* file:4:20 */
 t2 = t0 <= t1;
 /* file:4:20 */
 verifier_assume__293(t2);
 /* file:5:25 */
 t3 = midpoint_midpoint__214(t0, t1);
 /* dbg_var_val:mid */
 /* file:6:20 */
 t2 = t0 <= t3;
 /* file:6:20 */
 verifier_assert__294(t2);
 /* file:7:20 */
 t2 = t3 <= t1;
 /* file:7:20 */
 verifier_assert__294(t2);
 return;
}
void midpoint_naive_midpoint_never_panics__215(void) {
 uint32_t t0;
 uint32_t t1;
 /* file:2:35 */
 t0 = verifier_any__anon_1586__979();
 /* file:2:54 */
 t1 = verifier_any__anon_1586__979();
 /* file:2:22 */
 (void)midpoint_midpointNaive__213(t0, t1);
 return;
}
static uint32_t midpoint_midpointNaive__213(uint32_t const a0, uint32_t const a1) {
 uint32_t t0;
 uint32_t t4;
 struct tuple_2_u32_u1_134217728 t1;
 uint8_t t2;
 bool t3;
 /* file:2:17 */
 t1.f1 = zig_addo_u32(&t1.f0, a0, a1, UINT8_C(32));
 t2 = t1.f1;
 t3 = t2 == UINT8_C(1);
 if (t3) {
  panic_integerOverflow__315();
  zig_unreachable();
 }
 t4 = t1.f0;
 t0 = t4;
 goto zig_block_0;

zig_block_0:;
 /* file:2:25 */
 t0 = t0 / UINT32_C(2);
 /* file:2:5 */
 return t0;
}
