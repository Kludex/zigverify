#define ZIG_TARGET_MAX_INT_ALIGNMENT 16
#include "zig.h"
struct slice_u8_51 { /* [:0]const u8 */
 uint8_t const *ptr;
 size_t len;
};
typedef uint8_t enum__builtin_OutputMode_147; /* builtin.OutputMode */
struct arr_32_u8_179 { uint8_t array[32] zig_nonstring; }; /* [32]u8 */
zig_static_assert(sizeof (struct arr_32_u8_179) == 32, "incorrect size");
zig_static_assert(_Alignof (struct arr_32_u8_179) == 1, "incorrect alignment");
typedef uint8_t enum__key_value_Parser__enum_193_193; /* key_value.Parser__enum_193 */
struct key_value_Parser_191 { /* key_value.Parser */
 uintptr_t pos;
 enum__key_value_Parser__enum_193_193 state;
};
zig_static_assert(sizeof (struct key_value_Parser_191) == 16, "incorrect size");
zig_static_assert(_Alignof (struct key_value_Parser_191) == 8, "incorrect alignment");
struct slice_u8_188 { /* []u8 */
 uint8_t *ptr zig_nonstring;
 size_t len;
};
struct slice_u8_50 { /* []const u8 */
 uint8_t const *ptr zig_nonstring;
 size_t len;
};
struct arr_5_usize_633 { uintptr_t array[5]; }; /* [5]usize */
zig_static_assert(sizeof (struct arr_5_usize_633) == 40, "incorrect size");
zig_static_assert(_Alignof (struct arr_5_usize_633) == 8, "incorrect alignment");
struct Target_Cpu_Feature_Set_620 { /* Target.Cpu.Feature.Set */
 struct arr_5_usize_633 ints;
};
zig_static_assert(sizeof (struct Target_Cpu_Feature_Set_620) == 40, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_Feature_Set_620) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Cpu_Arch_613; /* Target.Cpu.Arch */
struct Target_Cpu_Model_615;
struct Target_Cpu_603 { /* Target.Cpu */
 struct Target_Cpu_Model_615 const *model;
 struct Target_Cpu_Feature_Set_620 features;
 enum__Target_Cpu_Arch_613 arch;
};
zig_static_assert(sizeof (struct Target_Cpu_603) == 56, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_603) == 8, "incorrect alignment");
struct Target_Cpu_Model_615 { /* Target.Cpu.Model */
 struct slice_u8_50 name;
 struct slice_u8_51 llvm_name;
 struct Target_Cpu_Feature_Set_620 features;
};
zig_static_assert(sizeof (struct Target_Cpu_Model_615) == 72, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_Model_615) == 8, "incorrect alignment");
struct SemanticVersion_640 { /* SemanticVersion */
 uintptr_t major;
 uintptr_t minor;
 uintptr_t patch;
 struct slice_u8_50 pre;
 struct slice_u8_50 build;
};
zig_static_assert(sizeof (struct SemanticVersion_640) == 56, "incorrect size");
zig_static_assert(_Alignof (struct SemanticVersion_640) == 8, "incorrect alignment");
struct SemanticVersion_Range_642 { /* SemanticVersion.Range */
 struct SemanticVersion_640 zig_e_min;
 struct SemanticVersion_640 zig_e_max;
};
zig_static_assert(sizeof (struct SemanticVersion_Range_642) == 112, "incorrect size");
zig_static_assert(_Alignof (struct SemanticVersion_Range_642) == 8, "incorrect alignment");
struct Target_Os_HurdVersionRange_644 { /* Target.Os.HurdVersionRange */
 struct SemanticVersion_Range_642 range;
 struct SemanticVersion_640 glibc;
};
zig_static_assert(sizeof (struct Target_Os_HurdVersionRange_644) == 168, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_HurdVersionRange_644) == 8, "incorrect alignment");
struct Target_Os_LinuxVersionRange_646 { /* Target.Os.LinuxVersionRange */
 struct SemanticVersion_Range_642 range;
 struct SemanticVersion_640 glibc;
 uint32_t android;
};
zig_static_assert(sizeof (struct Target_Os_LinuxVersionRange_646) == 176, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_LinuxVersionRange_646) == 8, "incorrect alignment");
typedef uint32_t enum__Target_Os_WindowsVersion_648; /* Target.Os.WindowsVersion */
struct Target_Os_WindowsVersion_Range_650 { /* Target.Os.WindowsVersion.Range */
 enum__Target_Os_WindowsVersion_648 zig_e_min;
 enum__Target_Os_WindowsVersion_648 zig_e_max;
};
zig_static_assert(sizeof (struct Target_Os_WindowsVersion_Range_650) == 8, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_WindowsVersion_Range_650) == 4, "incorrect alignment");
typedef uint8_t enum___40typeInfo_28Target_Os_VersionRange_29__40_22union_22_tag_type__3f_638; /* @typeInfo(Target.Os.VersionRange).@"union".tag_type.? */
struct Target_Os_VersionRange_636 { /* Target.Os.VersionRange */
 union {
  struct SemanticVersion_Range_642 semver;
  struct Target_Os_HurdVersionRange_644 hurd;
  struct Target_Os_LinuxVersionRange_646 linux;
  struct Target_Os_WindowsVersion_Range_650 windows;
 } payload;
 enum___40typeInfo_28Target_Os_VersionRange_29__40_22union_22_tag_type__3f_638 tag;
};
zig_static_assert(sizeof (struct Target_Os_VersionRange_636) == 184, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_VersionRange_636) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Os_Tag_634; /* Target.Os.Tag */
struct Target_Os_605 { /* Target.Os */
 struct Target_Os_VersionRange_636 version_range;
 enum__Target_Os_Tag_634 tag;
};
zig_static_assert(sizeof (struct Target_Os_605) == 192, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_605) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Abi_607; /* Target.Abi */
typedef uint8_t enum__Target_ObjectFormat_609; /* Target.ObjectFormat */
struct arr_255_u8_707 { uint8_t array[255] zig_nonstring; }; /* [255]u8 */
zig_static_assert(sizeof (struct arr_255_u8_707) == 255, "incorrect size");
zig_static_assert(_Alignof (struct arr_255_u8_707) == 1, "incorrect alignment");
struct Target_DynamicLinker_611 { /* Target.DynamicLinker */
 struct arr_255_u8_707 buffer;
 uint8_t len;
};
zig_static_assert(sizeof (struct Target_DynamicLinker_611) == 256, "incorrect size");
zig_static_assert(_Alignof (struct Target_DynamicLinker_611) == 1, "incorrect alignment");
struct Target_601 { /* Target */
 struct Target_Cpu_603 cpu;
 struct Target_Os_605 os;
 enum__Target_Abi_607 abi;
 enum__Target_ObjectFormat_609 ofmt;
 struct Target_DynamicLinker_611 dynamic_linker;
};
zig_static_assert(sizeof (struct Target_601) == 512, "incorrect size");
zig_static_assert(_Alignof (struct Target_601) == 8, "incorrect alignment");
struct opt_u64_449 { /* ?u64 */
 uint64_t payload;
 bool is_null;
};
zig_static_assert(sizeof (struct opt_u64_449) == 16, "incorrect size");
zig_static_assert(_Alignof (struct opt_u64_449) == 8, "incorrect alignment");
struct builtin_CallingConvention_CommonOptions_433 { /* builtin.CallingConvention.CommonOptions */
 struct opt_u64_449 incoming_stack_alignment;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_CommonOptions_433) == 16, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_CommonOptions_433) == 8, "incorrect alignment");
struct builtin_CallingConvention_X86RegparmOptions_435 { /* builtin.CallingConvention.X86RegparmOptions */
 struct opt_u64_449 incoming_stack_alignment;
 uint8_t register_params;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_X86RegparmOptions_435) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_X86RegparmOptions_435) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ArmInterruptOptions_InterruptType_450; /* builtin.CallingConvention.ArmInterruptOptions.InterruptType */
struct builtin_CallingConvention_ArmInterruptOptions_437 { /* builtin.CallingConvention.ArmInterruptOptions */
 struct opt_u64_449 incoming_stack_alignment;
 enum__builtin_CallingConvention_ArmInterruptOptions_InterruptType_450 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ArmInterruptOptions_437) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ArmInterruptOptions_437) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_MipsInterruptOptions_InterruptMode_459; /* builtin.CallingConvention.MipsInterruptOptions.InterruptMode */
struct builtin_CallingConvention_MipsInterruptOptions_439 { /* builtin.CallingConvention.MipsInterruptOptions */
 struct opt_u64_449 incoming_stack_alignment;
 enum__builtin_CallingConvention_MipsInterruptOptions_InterruptMode_459 mode;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_MipsInterruptOptions_439) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_MipsInterruptOptions_439) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_RiscvInterruptOptions_PrivilegeMode_471; /* builtin.CallingConvention.RiscvInterruptOptions.PrivilegeMode */
struct builtin_CallingConvention_RiscvInterruptOptions_441 { /* builtin.CallingConvention.RiscvInterruptOptions */
 struct opt_u64_449 incoming_stack_alignment;
 enum__builtin_CallingConvention_RiscvInterruptOptions_PrivilegeMode_471 mode;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_RiscvInterruptOptions_441) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_RiscvInterruptOptions_441) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ArcInterruptOptions_InterruptType_473; /* builtin.CallingConvention.ArcInterruptOptions.InterruptType */
struct builtin_CallingConvention_ArcInterruptOptions_443 { /* builtin.CallingConvention.ArcInterruptOptions */
 struct opt_u64_449 incoming_stack_alignment;
 enum__builtin_CallingConvention_ArcInterruptOptions_InterruptType_473 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ArcInterruptOptions_443) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ArcInterruptOptions_443) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_MicroblazeInterruptOptions_InterruptType_476; /* builtin.CallingConvention.MicroblazeInterruptOptions.InterruptType */
struct builtin_CallingConvention_MicroblazeInterruptOptions_445 { /* builtin.CallingConvention.MicroblazeInterruptOptions */
 struct opt_u64_449 incoming_stack_alignment;
 enum__builtin_CallingConvention_MicroblazeInterruptOptions_InterruptType_476 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_MicroblazeInterruptOptions_445) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_MicroblazeInterruptOptions_445) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ShInterruptOptions_SaveBehavior_478; /* builtin.CallingConvention.ShInterruptOptions.SaveBehavior */
struct builtin_CallingConvention_ShInterruptOptions_447 { /* builtin.CallingConvention.ShInterruptOptions */
 struct opt_u64_449 incoming_stack_alignment;
 enum__builtin_CallingConvention_ShInterruptOptions_SaveBehavior_478 save;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ShInterruptOptions_447) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ShInterruptOptions_447) == 8, "incorrect alignment");
typedef uint8_t enum___40typeInfo_28builtin_CallingConvention_29__40_22union_22_tag_type__3f_336; /* @typeInfo(builtin.CallingConvention).@"union".tag_type.? */
struct builtin_CallingConvention_334 { /* builtin.CallingConvention */
 union {
  struct builtin_CallingConvention_CommonOptions_433 x86_64_sysv;
  struct builtin_CallingConvention_CommonOptions_433 x86_64_x32;
  struct builtin_CallingConvention_CommonOptions_433 x86_64_win;
  struct builtin_CallingConvention_CommonOptions_433 x86_64_regcall_v3_sysv;
  struct builtin_CallingConvention_CommonOptions_433 x86_64_regcall_v4_win;
  struct builtin_CallingConvention_CommonOptions_433 x86_64_vectorcall;
  struct builtin_CallingConvention_CommonOptions_433 x86_64_interrupt;
  struct builtin_CallingConvention_X86RegparmOptions_435 x86_sysv;
  struct builtin_CallingConvention_X86RegparmOptions_435 x86_win;
  struct builtin_CallingConvention_X86RegparmOptions_435 x86_stdcall;
  struct builtin_CallingConvention_CommonOptions_433 x86_fastcall;
  struct builtin_CallingConvention_CommonOptions_433 x86_thiscall;
  struct builtin_CallingConvention_CommonOptions_433 x86_thiscall_mingw;
  struct builtin_CallingConvention_CommonOptions_433 x86_regcall_v3;
  struct builtin_CallingConvention_CommonOptions_433 x86_regcall_v4_win;
  struct builtin_CallingConvention_CommonOptions_433 x86_vectorcall;
  struct builtin_CallingConvention_CommonOptions_433 x86_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 x86_16_cdecl;
  struct builtin_CallingConvention_CommonOptions_433 x86_16_stdcall;
  struct builtin_CallingConvention_CommonOptions_433 x86_16_regparmcall;
  struct builtin_CallingConvention_CommonOptions_433 x86_16_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 aarch64_aapcs;
  struct builtin_CallingConvention_CommonOptions_433 aarch64_aapcs_darwin;
  struct builtin_CallingConvention_CommonOptions_433 aarch64_aapcs_win;
  struct builtin_CallingConvention_CommonOptions_433 aarch64_vfabi;
  struct builtin_CallingConvention_CommonOptions_433 aarch64_vfabi_sve;
  struct builtin_CallingConvention_CommonOptions_433 alpha_osf;
  struct builtin_CallingConvention_CommonOptions_433 arm_aapcs;
  struct builtin_CallingConvention_CommonOptions_433 arm_aapcs_vfp;
  struct builtin_CallingConvention_ArmInterruptOptions_437 arm_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 mips64_n64;
  struct builtin_CallingConvention_CommonOptions_433 mips64_n32;
  struct builtin_CallingConvention_MipsInterruptOptions_439 mips64_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 mips_o32;
  struct builtin_CallingConvention_MipsInterruptOptions_439 mips_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 riscv64_lp64;
  struct builtin_CallingConvention_CommonOptions_433 riscv64_lp64_v;
  struct builtin_CallingConvention_RiscvInterruptOptions_441 riscv64_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 riscv32_ilp32;
  struct builtin_CallingConvention_CommonOptions_433 riscv32_ilp32_v;
  struct builtin_CallingConvention_RiscvInterruptOptions_441 riscv32_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 sparc64_sysv;
  struct builtin_CallingConvention_CommonOptions_433 sparc_sysv;
  struct builtin_CallingConvention_CommonOptions_433 powerpc64_elf;
  struct builtin_CallingConvention_CommonOptions_433 powerpc64_elf_altivec;
  struct builtin_CallingConvention_CommonOptions_433 powerpc64_elf_v2;
  struct builtin_CallingConvention_CommonOptions_433 powerpc_sysv;
  struct builtin_CallingConvention_CommonOptions_433 powerpc_sysv_altivec;
  struct builtin_CallingConvention_CommonOptions_433 powerpc_aix;
  struct builtin_CallingConvention_CommonOptions_433 powerpc_aix_altivec;
  struct builtin_CallingConvention_CommonOptions_433 wasm_mvp;
  struct builtin_CallingConvention_CommonOptions_433 arc_sysv;
  struct builtin_CallingConvention_ArcInterruptOptions_443 arc_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 bpf_std;
  struct builtin_CallingConvention_CommonOptions_433 csky_sysv;
  struct builtin_CallingConvention_CommonOptions_433 csky_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 hexagon_sysv;
  struct builtin_CallingConvention_CommonOptions_433 hexagon_sysv_hvx;
  struct builtin_CallingConvention_CommonOptions_433 hppa_elf;
  struct builtin_CallingConvention_CommonOptions_433 hppa64_elf;
  struct builtin_CallingConvention_CommonOptions_433 kvx_lp64;
  struct builtin_CallingConvention_CommonOptions_433 kvx_ilp32;
  struct builtin_CallingConvention_CommonOptions_433 lanai_sysv;
  struct builtin_CallingConvention_CommonOptions_433 loongarch64_lp64;
  struct builtin_CallingConvention_CommonOptions_433 loongarch32_ilp32;
  struct builtin_CallingConvention_CommonOptions_433 m68k_sysv;
  struct builtin_CallingConvention_CommonOptions_433 m68k_gnu;
  struct builtin_CallingConvention_CommonOptions_433 m68k_rtd;
  struct builtin_CallingConvention_CommonOptions_433 m68k_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 microblaze_std;
  struct builtin_CallingConvention_MicroblazeInterruptOptions_445 microblaze_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 msp430_eabi;
  struct builtin_CallingConvention_CommonOptions_433 msp430_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 or1k_sysv;
  struct builtin_CallingConvention_CommonOptions_433 propeller_sysv;
  struct builtin_CallingConvention_CommonOptions_433 s390x_sysv;
  struct builtin_CallingConvention_CommonOptions_433 s390x_sysv_vx;
  struct builtin_CallingConvention_CommonOptions_433 sh_gnu;
  struct builtin_CallingConvention_CommonOptions_433 sh_renesas;
  struct builtin_CallingConvention_ShInterruptOptions_447 sh_interrupt;
  struct builtin_CallingConvention_CommonOptions_433 ve_sysv;
  struct builtin_CallingConvention_CommonOptions_433 xcore_xs1;
  struct builtin_CallingConvention_CommonOptions_433 xcore_xs2;
  struct builtin_CallingConvention_CommonOptions_433 xtensa_call0;
  struct builtin_CallingConvention_CommonOptions_433 xtensa_windowed;
  struct builtin_CallingConvention_CommonOptions_433 amdgcn_device;
  struct builtin_CallingConvention_CommonOptions_433 amdgcn_cs;
 } payload;
 enum___40typeInfo_28builtin_CallingConvention_29__40_22union_22_tag_type__3f_336 tag;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_334) == 32, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_334) == 8, "incorrect alignment");
typedef uint32_t enum__failure_Kind_1529; /* failure.Kind */
struct tuple_2_usize_u1_402653184 { /* struct { usize, u1 } */
 uintptr_t f0;
 uint8_t f1;
};
zig_static_assert(sizeof (struct tuple_2_usize_u1_402653184) == 16, "incorrect size");
zig_static_assert(_Alignof (struct tuple_2_usize_u1_402653184) == 8, "incorrect alignment");
struct arr_6s116_u8_1629 { uint8_t array[7]; }; /* [6:0]u8 */
zig_static_assert(sizeof (struct arr_6s116_u8_1629) == 7, "incorrect size");
zig_static_assert(_Alignof (struct arr_6s116_u8_1629) == 1, "incorrect alignment");
#define key_value_value_has_no_terminator__215 value_has_no_terminator
zig_extern void value_has_no_terminator(void);
static struct arr_6s116_u8_1629 const __anon_1630;
static enum__builtin_OutputMode_147 const builtin_output_mode__220;
static struct slice_u8_188 verifier_prefix__anon_190__294(struct slice_u8_188 a0);
static struct Target_Cpu_Feature_Set_620 const Target_Cpu_Feature_Set_empty__545;
static struct Target_Cpu_603 const builtin_cpu__226;
static struct Target_Os_605 const builtin_os__227;
static enum__Target_Abi_607 const builtin_abi__225;
static enum__Target_ObjectFormat_609 const builtin_object_format__229;
static struct Target_601 const builtin_target__228;
static struct builtin_CallingConvention_334 const builtin_CallingConvention_c__328;
zig_extern void verifier_check(bool a0);
static void verifier_assert__291(bool a0);
static zig_noreturn void panic_outOfBounds__304(uintptr_t a0, uintptr_t a1);
zig_extern void verifier_assume(bool a0);
static void verifier_assume__290(bool a0);
zig_extern zig_noreturn void verifier_fail(uint32_t a0, uintptr_t a1, uintptr_t a2);
static zig_cold zig_noreturn void panic_fail__300(enum__failure_Kind_1529 a0, uintptr_t a1, uintptr_t a2);
zig_extern void verifier_any(void *a0, uintptr_t a1);
static uintptr_t verifier_any__anon_217__297(void);
static zig_noreturn void panic_noreturnReturned__326(void);
static uint8_t verifier_any__anon_215__296(void);
static struct slice_u8_50 key_value_Parser_next__295(struct key_value_Parser_191 *a0, struct slice_u8_50 a1);
static uintptr_t key_value_indexOfOrEnd__213(struct slice_u8_50 a0, uintptr_t a1, uint8_t a2);
static zig_noreturn void panic_corruptSwitch__320(void);
static zig_noreturn void panic_startGreaterThanEnd__305(uintptr_t a0, uintptr_t a1);
static zig_noreturn void panic_integerOverflow__314(void);
static struct Target_DynamicLinker_611 const Target_DynamicLinker_none__492;
static struct Target_Cpu_Model_615 const Target_x86_cpu_znver4__700;
static struct slice_u8_51 const zig_errorName[0] = {};
static struct arr_6s116_u8_1629 const __anon_1630 = {"znver4"};
static enum__builtin_OutputMode_147 const builtin_output_mode__220 = UINT8_C(2);
void key_value_value_has_no_terminator__215(void) {
 struct slice_u8_188 t1;
 struct slice_u8_50 t3;
 struct slice_u8_50 t4;
 struct slice_u8_50 t5;
 uintptr_t t8;
 uintptr_t t9;
 uintptr_t t7;
 uint64_t t10;
 uint64_t t11;
 struct key_value_Parser_191 t2;
 bool t6;
 uint8_t t12;
 struct arr_32_u8_179 t0;
 /* file:2:5 */
 memset(&t0, 0xaa, sizeof(struct arr_32_u8_179));
 /* dbg_var_ptr:buffer */
 /* file:3:34 */
 t1.ptr = (uint8_t *)&t0;
 t1.len = (uintptr_t)32ul;
 /* file:3:34 */
 t1 = verifier_prefix__anon_190__294(t1);
 /* dbg_var_val:input */
 /* file:4:5 */
 t2 = (struct key_value_Parser_191){(uintptr_t)0ul,UINT8_C(0)};
 /* dbg_var_ptr:parser */
 /* file:5:5 */
 /* file:5:30 */
 memcpy(&t4, &t1, 16);
 /* file:5:30 */
 t5 = key_value_Parser_next__295(&t2, t4);
 t6 = t5.ptr != NULL;
 if (t6) {
  t4 = t5;
  t3 = t4;
  goto zig_block_0;
 }
 /* file:5:45 */
 return;

zig_block_0:;
 /* dbg_var_val:value */
 t7 = (uintptr_t)0ul;
 /* file:6:10 */
 t8 = t3.len;
 zig_loop_32:
 t9 = t7;
 t10 = t9;
 t11 = t8;
 t6 = t10 < t11;
 if (t6) {
  t12 = t3.ptr[t9];
  /* dbg_var_val:byte */
  /* file:6:39 */
  t6 = t12 != UINT8_C(59);
  /* file:6:39 */
  verifier_assert__291(t6);
  /* file:6:51 */
  (void)0;
  goto zig_block_2;
 }
 goto zig_block_1;

zig_block_2:;
 t9 = t9 + (uintptr_t)1ul;
 t7 = t9;
 goto zig_loop_32;

zig_block_1:;
 return;
}
static struct slice_u8_188 verifier_prefix__anon_190__294(struct slice_u8_188 const a0) {
 struct slice_u8_188 const *t1;
 uintptr_t t3;
 uintptr_t t4;
 uintptr_t t13;
 uintptr_t t2;
 uint64_t t5;
 uint64_t t6;
 uint8_t *t8 zig_nonstring;
 uintptr_t const *t10;
 struct slice_u8_188 t11;
 struct slice_u8_188 t0;
 uint8_t *t12 zig_nonstring;
 bool t7;
 uint8_t t9;
 t0 = a0;
 t1 = (struct slice_u8_188 const *)&t0;
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
  t9 = verifier_any__anon_215__296();
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
 t3 = verifier_any__anon_217__297();
 /* dbg_var_val:len */
 /* file:4:25 */
 t10 = &t1->len;
 t4 = (*t10);
 t6 = t3;
 t5 = t4;
 t7 = t6 <= t5;
 /* file:4:11 */
 verifier_assume__290(t7);
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
 panic_outOfBounds__304(t3, t13);
 zig_unreachable();

zig_block_2:;
 t11.ptr = t12;
 t11.len = t4;
 /* file:5:5 */
 return t11;
}
static struct Target_Cpu_Feature_Set_620 const Target_Cpu_Feature_Set_empty__545 = {{{0ul,0ul,0ul,0ul,0ul}}};
static struct Target_Cpu_603 const builtin_cpu__226 = {(((struct Target_Cpu_Model_615 const *)&Target_x86_cpu_znver4__700)),{{{14373335171114205424ul,10664787974256315648ul,8073817237535973888ul,244ul,0ul}}},UINT8_C(54)};
static struct Target_Os_605 const builtin_os__227 = {{ .tag = UINT8_C(3), .payload = { .linux = {{{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}}},{2ul,43ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},UINT32_C(29)} } },UINT8_C(9)};
static enum__Target_Abi_607 const builtin_abi__225 = UINT8_C(1);
static enum__Target_ObjectFormat_609 const builtin_object_format__229 = UINT8_C(0);
static struct Target_601 const builtin_target__228 = {{(((struct Target_Cpu_Model_615 const *)&Target_x86_cpu_znver4__700)),{{{14373335171114205424ul,10664787974256315648ul,8073817237535973888ul,244ul,0ul}}},UINT8_C(54)},{{ .tag = UINT8_C(3), .payload = { .linux = {{{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}}},{2ul,43ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},UINT32_C(29)} } },UINT8_C(9)},UINT8_C(1),UINT8_C(0),{{"/lib64/ld-linux-x86-64.so.2\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},UINT8_C(27)}};
static struct builtin_CallingConvention_334 const builtin_CallingConvention_c__328 = { .tag = UINT8_C(4), .payload = { .x86_64_sysv = {{ .is_null = true, .payload = UINT64_C(0xaaaaaaaaaaaaaaaa) }} } };
static void verifier_assert__291(bool const a0) {
 /* file:2:19 */
 verifier_check(a0);
 return;
}
static zig_noreturn void panic_outOfBounds__304(uintptr_t const a0, uintptr_t const a1) {
 /* file:2:9 */
 panic_fail__300(UINT32_C(4), a0, a1);
 zig_unreachable();
}
static void verifier_assume__290(bool const a0) {
 /* file:2:20 */
 verifier_assume(a0);
 return;
}
static zig_cold zig_noreturn void panic_fail__300(enum__failure_Kind_1529 const a0, uintptr_t const a1, uintptr_t const a2) {
 uint32_t t0;
 /* file:3:18 */
 t0 = a0;
 /* file:3:18 */
 verifier_fail(t0, a1, a2);
 panic_noreturnReturned__326();
 zig_unreachable();
}
static uintptr_t verifier_any__anon_217__297(void) {
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
static zig_noreturn void panic_noreturnReturned__326(void) {
 /* file:2:9 */
 panic_fail__300(UINT32_C(26), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static uint8_t verifier_any__anon_215__296(void) {
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
static struct slice_u8_50 key_value_Parser_next__295(struct key_value_Parser_191 *const a0, struct slice_u8_50 const a1) {
 struct key_value_Parser_191 *const *t1;
 struct slice_u8_50 const *t3;
 struct key_value_Parser_191 *t4;
 struct key_value_Parser_191 *t0;
 enum__key_value_Parser__enum_193_193 *t5;
 uintptr_t *t7;
 uintptr_t *t8;
 uintptr_t t9;
 uintptr_t t11;
 uintptr_t t20;
 uintptr_t const *t10;
 uint64_t t12;
 uint64_t t13;
 struct tuple_2_usize_u1_402653184 t15;
 struct slice_u8_50 t17;
 struct slice_u8_50 t18;
 struct slice_u8_50 t2;
 uint8_t const *t19 zig_nonstring;
 enum__key_value_Parser__enum_193_193 t6;
 bool t14;
 uint8_t t16;
 t0 = a0;
 t1 = (struct key_value_Parser_191 *const *)&t0;
 t2 = a1;
 t3 = (struct slice_u8_50 const *)&t2;
 /* file:2:21 */
 t4 = (*t1);
 t5 = (enum__key_value_Parser__enum_193_193 *)&t4->state;
 t6 = (*t5);
 /* file:2:17 */
 switch (t6) {
  case UINT8_C(0): {
   /* file:4:21 */
   t4 = (*t1);
   t7 = (uintptr_t *)&t4->pos;
   /* file:4:52 */
   t4 = (*t1);
   t8 = (uintptr_t *)&t4->pos;
   t9 = (*t8);
   /* file:4:40 */
   t9 = key_value_indexOfOrEnd__213(a1, t9, UINT8_C(61));
   (*t7) = t9;
   /* file:5:21 */
   /* file:5:25 */
   t4 = (*t1);
   t7 = (uintptr_t *)&t4->pos;
   t9 = (*t7);
   /* file:5:38 */
   t10 = &t3->len;
   t11 = (*t10);
   t12 = t9;
   t13 = t11;
   t14 = t12 == t13;
   if (t14) {
    /* file:5:44 */
    return (struct slice_u8_50){NULL,(uintptr_t)0xaaaaaaaaaaaaaaaaul};
   }
   goto zig_block_0;

zig_block_0:;
   /* file:6:21 */
   t4 = (*t1);
   t7 = (uintptr_t *)&t4->pos;
   t11 = (*t7);
   /* file:6:26 */
   t15.f1 = zig_addo_u64(&t15.f0, t11, (uintptr_t)1ul, UINT8_C(64));
   t16 = t15.f1;
   t14 = t16 == UINT8_C(1);
   if (t14) {
    panic_integerOverflow__314();
    zig_unreachable();
   }
   t11 = t15.f0;
   t9 = t11;
   goto zig_block_1;

zig_block_1:;
   (*t7) = t9;
   /* file:7:21 */
   t4 = (*t1);
   t5 = (enum__key_value_Parser__enum_193_193 *)&t4->state;
   (*t5) = UINT8_C(1);
   /* file:8:33 */
   t4 = (*t1);
   /* file:8:33 */
   t17 = key_value_Parser_next__295(t4, a1);
   /* file:8:17 */
   return t17;
  }
  case UINT8_C(1): {
   /* file:11:35 */
   t4 = (*t1);
   t8 = (uintptr_t *)&t4->pos;
   t11 = (*t8);
   /* dbg_var_val:start */
   /* file:12:21 */
   t4 = (*t1);
   t8 = (uintptr_t *)&t4->pos;
   /* file:12:40 */
   t9 = key_value_indexOfOrEnd__213(a1, t11, UINT8_C(59));
   (*t8) = t9;
   /* file:13:21 */
   t4 = (*t1);
   t5 = (enum__key_value_Parser__enum_193_193 *)&t4->state;
   (*t5) = UINT8_C(2);
   /* file:14:41 */
   t4 = (*t1);
   t8 = (uintptr_t *)&t4->pos;
   t9 = (*t8);
   /* file:14:29 */
   t18 = (*t3);
   t19 = t18.ptr;
   t19 = (uint8_t const *)(((uintptr_t)t19) + (t11*sizeof(uint8_t)));
   t14 = t11 <= t9;
   if (t14) {
    goto zig_block_2;
   }
   panic_startGreaterThanEnd__305(t11, t9);
   zig_unreachable();

zig_block_2:;
   t11 = t9 - t11;
   t20 = t18.len;
   t14 = t9 <= t20;
   if (t14) {
    goto zig_block_3;
   }
   panic_outOfBounds__304(t9, t20);
   zig_unreachable();

zig_block_3:;
   t18.ptr = t19;
   t18.len = t11;
   /* file:14:17 */
   t17 = t18;
   return t17;
  }
  case UINT8_C(2): {
   /* file:16:22 */
   return (struct slice_u8_50){NULL,(uintptr_t)0xaaaaaaaaaaaaaaaaul};
  }
  default: {
   /* file:2:17 */
   panic_corruptSwitch__320();
   zig_unreachable();
  }
 }
}
static uintptr_t key_value_indexOfOrEnd__213(struct slice_u8_50 const a0, uintptr_t const a1, uint8_t const a2) {
 struct slice_u8_50 const *t1;
 uintptr_t t3;
 uintptr_t t5;
 uintptr_t t2;
 uintptr_t const *t4;
 uint64_t t6;
 uint64_t t7;
 struct slice_u8_50 t10;
 struct slice_u8_50 t0;
 uint8_t const *t11 zig_nonstring;
 struct tuple_2_usize_u1_402653184 t13;
 bool t8;
 bool t9;
 uint8_t t12;
 uint8_t t14;
 t0 = a0;
 t1 = (struct slice_u8_50 const *)&t0;
 /* file:2:5 */
 t2 = a1;
 /* dbg_var_ptr:at */
 zig_loop_12:
 /* file:3:12 */
 t3 = t2;
 /* file:3:22 */
 t4 = &t1->len;
 t5 = (*t4);
 t6 = t3;
 t7 = t5;
 t8 = t6 < t7;
 if (t8) {
  t5 = t2;
  /* file:3:36 */
  t10 = (*t1);
  t3 = t10.len;
  t8 = t5 < t3;
  if (t8) {
   goto zig_block_3;
  }
  panic_outOfBounds__304(t5, t3);
  zig_unreachable();

zig_block_3:;
  t11 = &t10.ptr[t5];
  t12 = (*t11);
  t8 = t12 != a2;
  t9 = t8;
  goto zig_block_2;
 }
 t9 = false;
 goto zig_block_2;

zig_block_2:;
 if (t9) {
  /* file:3:52 */
  t5 = t2;
  /* file:3:55 */
  t13.f1 = zig_addo_u64(&t13.f0, t5, (uintptr_t)1ul, UINT8_C(64));
  t14 = t13.f1;
  t9 = t14 == UINT8_C(1);
  if (t9) {
   panic_integerOverflow__314();
   zig_unreachable();
  }
  t5 = t13.f0;
  t3 = t5;
  goto zig_block_4;

zig_block_4:;
  t2 = t3;
  /* file:3:58 */
  (void)0;
  goto zig_block_1;
 }
 goto zig_block_0;

zig_block_1:;
 goto zig_loop_12;

zig_block_0:;
 /* file:4:5 */
 t5 = t2;
 /* file:4:5 */
 return t5;
}
static zig_noreturn void panic_corruptSwitch__320(void) {
 /* file:2:9 */
 panic_fail__300(UINT32_C(20), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static zig_noreturn void panic_startGreaterThanEnd__305(uintptr_t const a0, uintptr_t const a1) {
 /* file:2:9 */
 panic_fail__300(UINT32_C(5), a0, a1);
 zig_unreachable();
}
static zig_noreturn void panic_integerOverflow__314(void) {
 /* file:2:9 */
 panic_fail__300(UINT32_C(14), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static struct Target_DynamicLinker_611 const Target_DynamicLinker_none__492 = {{"\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},UINT8_C(0)};
static struct Target_Cpu_Model_615 const Target_x86_cpu_znver4__700 = {{((uint8_t const *)((struct arr_6s116_u8_1629 const *)&__anon_1630)),6ul},{((uint8_t const *)((struct arr_6s116_u8_1629 const *)&__anon_1630)),6ul},{{{177989145354830000ul,14125804287856987392ul,8071020079954911744ul,229ul,0ul}}}};
