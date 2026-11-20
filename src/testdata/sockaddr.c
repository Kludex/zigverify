#define ZIG_TARGET_MAX_INT_ALIGNMENT 16
#include "zig.h"
struct slice_u8_51 { /* [:0]const u8 */
 uint8_t const *ptr;
 size_t len;
};
typedef uint8_t enum__builtin_OutputMode_147; /* builtin.OutputMode */
struct slice_u8_50 { /* []const u8 */
 uint8_t const *ptr zig_nonstring;
 size_t len;
};
struct SemanticVersion_211 { /* SemanticVersion */
 uintptr_t major;
 uintptr_t minor;
 uintptr_t patch;
 struct slice_u8_50 pre;
 struct slice_u8_50 build;
};
zig_static_assert(sizeof (struct SemanticVersion_211) == 56, "incorrect size");
zig_static_assert(_Alignof (struct SemanticVersion_211) == 8, "incorrect alignment");
struct SemanticVersion_Range_213 { /* SemanticVersion.Range */
 struct SemanticVersion_211 zig_e_min;
 struct SemanticVersion_211 zig_e_max;
};
zig_static_assert(sizeof (struct SemanticVersion_Range_213) == 112, "incorrect size");
zig_static_assert(_Alignof (struct SemanticVersion_Range_213) == 8, "incorrect alignment");
struct Target_Os_HurdVersionRange_215 { /* Target.Os.HurdVersionRange */
 struct SemanticVersion_Range_213 range;
 struct SemanticVersion_211 glibc;
};
zig_static_assert(sizeof (struct Target_Os_HurdVersionRange_215) == 168, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_HurdVersionRange_215) == 8, "incorrect alignment");
struct Target_Os_LinuxVersionRange_217 { /* Target.Os.LinuxVersionRange */
 struct SemanticVersion_Range_213 range;
 struct SemanticVersion_211 glibc;
 uint32_t android;
};
zig_static_assert(sizeof (struct Target_Os_LinuxVersionRange_217) == 176, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_LinuxVersionRange_217) == 8, "incorrect alignment");
typedef uint32_t enum__Target_Os_WindowsVersion_219; /* Target.Os.WindowsVersion */
struct Target_Os_WindowsVersion_Range_221 { /* Target.Os.WindowsVersion.Range */
 enum__Target_Os_WindowsVersion_219 zig_e_min;
 enum__Target_Os_WindowsVersion_219 zig_e_max;
};
zig_static_assert(sizeof (struct Target_Os_WindowsVersion_Range_221) == 8, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_WindowsVersion_Range_221) == 4, "incorrect alignment");
typedef uint8_t enum___40typeInfo_28Target_Os_VersionRange_29__40_22union_22_tag_type__3f_208; /* @typeInfo(Target.Os.VersionRange).@"union".tag_type.? */
struct Target_Os_VersionRange_205 { /* Target.Os.VersionRange */
 union {
  struct SemanticVersion_Range_213 semver;
  struct Target_Os_HurdVersionRange_215 hurd;
  struct Target_Os_LinuxVersionRange_217 linux;
  struct Target_Os_WindowsVersion_Range_221 windows;
 } payload;
 enum___40typeInfo_28Target_Os_VersionRange_29__40_22union_22_tag_type__3f_208 tag;
};
zig_static_assert(sizeof (struct Target_Os_VersionRange_205) == 184, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_VersionRange_205) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Os_Tag_203; /* Target.Os.Tag */
struct Target_Os_201 { /* Target.Os */
 struct Target_Os_VersionRange_205 version_range;
 enum__Target_Os_Tag_203 tag;
};
zig_static_assert(sizeof (struct Target_Os_201) == 192, "incorrect size");
zig_static_assert(_Alignof (struct Target_Os_201) == 8, "incorrect alignment");
struct arr_16_u8_180 { uint8_t array[16] zig_nonstring; }; /* [16]u8 */
zig_static_assert(sizeof (struct arr_16_u8_180) == 16, "incorrect size");
zig_static_assert(_Alignof (struct arr_16_u8_180) == 1, "incorrect alignment");
struct arr_14_u8_327 { uint8_t array[14] zig_nonstring; }; /* [14]u8 */
zig_static_assert(sizeof (struct arr_14_u8_327) == 14, "incorrect size");
zig_static_assert(_Alignof (struct arr_14_u8_327) == 1, "incorrect alignment");
struct os_linux_sockaddr_316 { /* os.linux.sockaddr */
 uint16_t family;
 struct arr_14_u8_327 data;
};
zig_static_assert(sizeof (struct os_linux_sockaddr_316) == 16, "incorrect size");
zig_static_assert(_Alignof (struct os_linux_sockaddr_316) == 2, "incorrect alignment");
struct arr_5_usize_671 { uintptr_t array[5]; }; /* [5]usize */
zig_static_assert(sizeof (struct arr_5_usize_671) == 40, "incorrect size");
zig_static_assert(_Alignof (struct arr_5_usize_671) == 8, "incorrect alignment");
struct Target_Cpu_Feature_Set_660 { /* Target.Cpu.Feature.Set */
 struct arr_5_usize_671 ints;
};
zig_static_assert(sizeof (struct Target_Cpu_Feature_Set_660) == 40, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_Feature_Set_660) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Cpu_Arch_653; /* Target.Cpu.Arch */
struct Target_Cpu_Model_655;
struct Target_Cpu_645 { /* Target.Cpu */
 struct Target_Cpu_Model_655 const *model;
 struct Target_Cpu_Feature_Set_660 features;
 enum__Target_Cpu_Arch_653 arch;
};
zig_static_assert(sizeof (struct Target_Cpu_645) == 56, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_645) == 8, "incorrect alignment");
struct Target_Cpu_Model_655 { /* Target.Cpu.Model */
 struct slice_u8_50 name;
 struct slice_u8_51 llvm_name;
 struct Target_Cpu_Feature_Set_660 features;
};
zig_static_assert(sizeof (struct Target_Cpu_Model_655) == 72, "incorrect size");
zig_static_assert(_Alignof (struct Target_Cpu_Model_655) == 8, "incorrect alignment");
typedef uint8_t enum__Target_Abi_647; /* Target.Abi */
typedef uint8_t enum__Target_ObjectFormat_649; /* Target.ObjectFormat */
struct arr_255_u8_674 { uint8_t array[255] zig_nonstring; }; /* [255]u8 */
zig_static_assert(sizeof (struct arr_255_u8_674) == 255, "incorrect size");
zig_static_assert(_Alignof (struct arr_255_u8_674) == 1, "incorrect alignment");
struct Target_DynamicLinker_651 { /* Target.DynamicLinker */
 struct arr_255_u8_674 buffer;
 uint8_t len;
};
zig_static_assert(sizeof (struct Target_DynamicLinker_651) == 256, "incorrect size");
zig_static_assert(_Alignof (struct Target_DynamicLinker_651) == 1, "incorrect alignment");
struct Target_199 { /* Target */
 struct Target_Cpu_645 cpu;
 struct Target_Os_201 os;
 enum__Target_Abi_647 abi;
 enum__Target_ObjectFormat_649 ofmt;
 struct Target_DynamicLinker_651 dynamic_linker;
};
zig_static_assert(sizeof (struct Target_199) == 512, "incorrect size");
zig_static_assert(_Alignof (struct Target_199) == 8, "incorrect alignment");
struct opt_u64_478 { /* ?u64 */
 uint64_t payload;
 bool is_null;
};
zig_static_assert(sizeof (struct opt_u64_478) == 16, "incorrect size");
zig_static_assert(_Alignof (struct opt_u64_478) == 8, "incorrect alignment");
struct builtin_CallingConvention_CommonOptions_462 { /* builtin.CallingConvention.CommonOptions */
 struct opt_u64_478 incoming_stack_alignment;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_CommonOptions_462) == 16, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_CommonOptions_462) == 8, "incorrect alignment");
struct builtin_CallingConvention_X86RegparmOptions_464 { /* builtin.CallingConvention.X86RegparmOptions */
 struct opt_u64_478 incoming_stack_alignment;
 uint8_t register_params;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_X86RegparmOptions_464) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_X86RegparmOptions_464) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ArmInterruptOptions_InterruptType_479; /* builtin.CallingConvention.ArmInterruptOptions.InterruptType */
struct builtin_CallingConvention_ArmInterruptOptions_466 { /* builtin.CallingConvention.ArmInterruptOptions */
 struct opt_u64_478 incoming_stack_alignment;
 enum__builtin_CallingConvention_ArmInterruptOptions_InterruptType_479 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ArmInterruptOptions_466) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ArmInterruptOptions_466) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_MipsInterruptOptions_InterruptMode_486; /* builtin.CallingConvention.MipsInterruptOptions.InterruptMode */
struct builtin_CallingConvention_MipsInterruptOptions_468 { /* builtin.CallingConvention.MipsInterruptOptions */
 struct opt_u64_478 incoming_stack_alignment;
 enum__builtin_CallingConvention_MipsInterruptOptions_InterruptMode_486 mode;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_MipsInterruptOptions_468) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_MipsInterruptOptions_468) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_RiscvInterruptOptions_PrivilegeMode_498; /* builtin.CallingConvention.RiscvInterruptOptions.PrivilegeMode */
struct builtin_CallingConvention_RiscvInterruptOptions_470 { /* builtin.CallingConvention.RiscvInterruptOptions */
 struct opt_u64_478 incoming_stack_alignment;
 enum__builtin_CallingConvention_RiscvInterruptOptions_PrivilegeMode_498 mode;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_RiscvInterruptOptions_470) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_RiscvInterruptOptions_470) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ArcInterruptOptions_InterruptType_500; /* builtin.CallingConvention.ArcInterruptOptions.InterruptType */
struct builtin_CallingConvention_ArcInterruptOptions_472 { /* builtin.CallingConvention.ArcInterruptOptions */
 struct opt_u64_478 incoming_stack_alignment;
 enum__builtin_CallingConvention_ArcInterruptOptions_InterruptType_500 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ArcInterruptOptions_472) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ArcInterruptOptions_472) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_MicroblazeInterruptOptions_InterruptType_503; /* builtin.CallingConvention.MicroblazeInterruptOptions.InterruptType */
struct builtin_CallingConvention_MicroblazeInterruptOptions_474 { /* builtin.CallingConvention.MicroblazeInterruptOptions */
 struct opt_u64_478 incoming_stack_alignment;
 enum__builtin_CallingConvention_MicroblazeInterruptOptions_InterruptType_503 type;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_MicroblazeInterruptOptions_474) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_MicroblazeInterruptOptions_474) == 8, "incorrect alignment");
typedef uint8_t enum__builtin_CallingConvention_ShInterruptOptions_SaveBehavior_505; /* builtin.CallingConvention.ShInterruptOptions.SaveBehavior */
struct builtin_CallingConvention_ShInterruptOptions_476 { /* builtin.CallingConvention.ShInterruptOptions */
 struct opt_u64_478 incoming_stack_alignment;
 enum__builtin_CallingConvention_ShInterruptOptions_SaveBehavior_505 save;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_ShInterruptOptions_476) == 24, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_ShInterruptOptions_476) == 8, "incorrect alignment");
typedef uint8_t enum___40typeInfo_28builtin_CallingConvention_29__40_22union_22_tag_type__3f_363; /* @typeInfo(builtin.CallingConvention).@"union".tag_type.? */
struct builtin_CallingConvention_361 { /* builtin.CallingConvention */
 union {
  struct builtin_CallingConvention_CommonOptions_462 x86_64_sysv;
  struct builtin_CallingConvention_CommonOptions_462 x86_64_x32;
  struct builtin_CallingConvention_CommonOptions_462 x86_64_win;
  struct builtin_CallingConvention_CommonOptions_462 x86_64_regcall_v3_sysv;
  struct builtin_CallingConvention_CommonOptions_462 x86_64_regcall_v4_win;
  struct builtin_CallingConvention_CommonOptions_462 x86_64_vectorcall;
  struct builtin_CallingConvention_CommonOptions_462 x86_64_interrupt;
  struct builtin_CallingConvention_X86RegparmOptions_464 x86_sysv;
  struct builtin_CallingConvention_X86RegparmOptions_464 x86_win;
  struct builtin_CallingConvention_X86RegparmOptions_464 x86_stdcall;
  struct builtin_CallingConvention_CommonOptions_462 x86_fastcall;
  struct builtin_CallingConvention_CommonOptions_462 x86_thiscall;
  struct builtin_CallingConvention_CommonOptions_462 x86_thiscall_mingw;
  struct builtin_CallingConvention_CommonOptions_462 x86_regcall_v3;
  struct builtin_CallingConvention_CommonOptions_462 x86_regcall_v4_win;
  struct builtin_CallingConvention_CommonOptions_462 x86_vectorcall;
  struct builtin_CallingConvention_CommonOptions_462 x86_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 x86_16_cdecl;
  struct builtin_CallingConvention_CommonOptions_462 x86_16_stdcall;
  struct builtin_CallingConvention_CommonOptions_462 x86_16_regparmcall;
  struct builtin_CallingConvention_CommonOptions_462 x86_16_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 aarch64_aapcs;
  struct builtin_CallingConvention_CommonOptions_462 aarch64_aapcs_darwin;
  struct builtin_CallingConvention_CommonOptions_462 aarch64_aapcs_win;
  struct builtin_CallingConvention_CommonOptions_462 aarch64_vfabi;
  struct builtin_CallingConvention_CommonOptions_462 aarch64_vfabi_sve;
  struct builtin_CallingConvention_CommonOptions_462 alpha_osf;
  struct builtin_CallingConvention_CommonOptions_462 arm_aapcs;
  struct builtin_CallingConvention_CommonOptions_462 arm_aapcs_vfp;
  struct builtin_CallingConvention_ArmInterruptOptions_466 arm_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 mips64_n64;
  struct builtin_CallingConvention_CommonOptions_462 mips64_n32;
  struct builtin_CallingConvention_MipsInterruptOptions_468 mips64_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 mips_o32;
  struct builtin_CallingConvention_MipsInterruptOptions_468 mips_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 riscv64_lp64;
  struct builtin_CallingConvention_CommonOptions_462 riscv64_lp64_v;
  struct builtin_CallingConvention_RiscvInterruptOptions_470 riscv64_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 riscv32_ilp32;
  struct builtin_CallingConvention_CommonOptions_462 riscv32_ilp32_v;
  struct builtin_CallingConvention_RiscvInterruptOptions_470 riscv32_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 sparc64_sysv;
  struct builtin_CallingConvention_CommonOptions_462 sparc_sysv;
  struct builtin_CallingConvention_CommonOptions_462 powerpc64_elf;
  struct builtin_CallingConvention_CommonOptions_462 powerpc64_elf_altivec;
  struct builtin_CallingConvention_CommonOptions_462 powerpc64_elf_v2;
  struct builtin_CallingConvention_CommonOptions_462 powerpc_sysv;
  struct builtin_CallingConvention_CommonOptions_462 powerpc_sysv_altivec;
  struct builtin_CallingConvention_CommonOptions_462 powerpc_aix;
  struct builtin_CallingConvention_CommonOptions_462 powerpc_aix_altivec;
  struct builtin_CallingConvention_CommonOptions_462 wasm_mvp;
  struct builtin_CallingConvention_CommonOptions_462 arc_sysv;
  struct builtin_CallingConvention_ArcInterruptOptions_472 arc_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 bpf_std;
  struct builtin_CallingConvention_CommonOptions_462 csky_sysv;
  struct builtin_CallingConvention_CommonOptions_462 csky_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 hexagon_sysv;
  struct builtin_CallingConvention_CommonOptions_462 hexagon_sysv_hvx;
  struct builtin_CallingConvention_CommonOptions_462 hppa_elf;
  struct builtin_CallingConvention_CommonOptions_462 hppa64_elf;
  struct builtin_CallingConvention_CommonOptions_462 kvx_lp64;
  struct builtin_CallingConvention_CommonOptions_462 kvx_ilp32;
  struct builtin_CallingConvention_CommonOptions_462 lanai_sysv;
  struct builtin_CallingConvention_CommonOptions_462 loongarch64_lp64;
  struct builtin_CallingConvention_CommonOptions_462 loongarch32_ilp32;
  struct builtin_CallingConvention_CommonOptions_462 m68k_sysv;
  struct builtin_CallingConvention_CommonOptions_462 m68k_gnu;
  struct builtin_CallingConvention_CommonOptions_462 m68k_rtd;
  struct builtin_CallingConvention_CommonOptions_462 m68k_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 microblaze_std;
  struct builtin_CallingConvention_MicroblazeInterruptOptions_474 microblaze_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 msp430_eabi;
  struct builtin_CallingConvention_CommonOptions_462 msp430_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 or1k_sysv;
  struct builtin_CallingConvention_CommonOptions_462 propeller_sysv;
  struct builtin_CallingConvention_CommonOptions_462 s390x_sysv;
  struct builtin_CallingConvention_CommonOptions_462 s390x_sysv_vx;
  struct builtin_CallingConvention_CommonOptions_462 sh_gnu;
  struct builtin_CallingConvention_CommonOptions_462 sh_renesas;
  struct builtin_CallingConvention_ShInterruptOptions_476 sh_interrupt;
  struct builtin_CallingConvention_CommonOptions_462 ve_sysv;
  struct builtin_CallingConvention_CommonOptions_462 xcore_xs1;
  struct builtin_CallingConvention_CommonOptions_462 xcore_xs2;
  struct builtin_CallingConvention_CommonOptions_462 xtensa_call0;
  struct builtin_CallingConvention_CommonOptions_462 xtensa_windowed;
  struct builtin_CallingConvention_CommonOptions_462 amdgcn_device;
  struct builtin_CallingConvention_CommonOptions_462 amdgcn_cs;
 } payload;
 enum___40typeInfo_28builtin_CallingConvention_29__40_22union_22_tag_type__3f_363 tag;
};
zig_static_assert(sizeof (struct builtin_CallingConvention_361) == 32, "incorrect size");
zig_static_assert(_Alignof (struct builtin_CallingConvention_361) == 8, "incorrect alignment");
struct arr_8_u8_1500 { uint8_t array[8] zig_nonstring; }; /* [8]u8 */
zig_static_assert(sizeof (struct arr_8_u8_1500) == 8, "incorrect size");
zig_static_assert(_Alignof (struct arr_8_u8_1500) == 1, "incorrect alignment");
struct os_linux_sockaddr_in_1496 { /* os.linux.sockaddr.in */
 uint16_t family;
 uint16_t port;
 uint32_t addr;
 struct arr_8_u8_1500 zero;
};
zig_static_assert(sizeof (struct os_linux_sockaddr_in_1496) == 16, "incorrect size");
zig_static_assert(_Alignof (struct os_linux_sockaddr_in_1496) == 4, "incorrect alignment");
struct os_linux_sockaddr_in6_1588 { /* os.linux.sockaddr.in6 */
 uint16_t family;
 uint16_t port;
 uint32_t flowinfo;
 struct arr_16_u8_180 addr;
 uint32_t scope_id;
};
zig_static_assert(sizeof (struct os_linux_sockaddr_in6_1588) == 28, "incorrect size");
zig_static_assert(_Alignof (struct os_linux_sockaddr_in6_1588) == 4, "incorrect alignment");
struct tuple_2_usize_u1_671088641 { /* struct { usize, u1 } */
 uintptr_t f0;
 uint8_t f1;
};
zig_static_assert(sizeof (struct tuple_2_usize_u1_671088641) == 16, "incorrect size");
zig_static_assert(_Alignof (struct tuple_2_usize_u1_671088641) == 8, "incorrect alignment");
struct slice_u8_1623 { /* []align(2) const u8 */
 uint8_t const *ptr zig_nonstring;
 size_t len;
};
struct opt_usize_590 { /* ?usize */
 uintptr_t payload;
 bool is_null;
};
zig_static_assert(sizeof (struct opt_usize_590) == 16, "incorrect size");
zig_static_assert(_Alignof (struct opt_usize_590) == 8, "incorrect alignment");
struct arr_108_u8_1599 { uint8_t array[108] zig_nonstring; }; /* [108]u8 */
zig_static_assert(sizeof (struct arr_108_u8_1599) == 108, "incorrect size");
zig_static_assert(_Alignof (struct arr_108_u8_1599) == 1, "incorrect alignment");
struct os_linux_sockaddr_un_1594 { /* os.linux.sockaddr.un */
 uint16_t family;
 struct arr_108_u8_1599 path;
};
zig_static_assert(sizeof (struct os_linux_sockaddr_un_1594) == 110, "incorrect size");
zig_static_assert(_Alignof (struct os_linux_sockaddr_un_1594) == 2, "incorrect alignment");
struct arr_0_u8_1617;
typedef uint32_t enum__failure_Kind_1632; /* failure.Kind */
typedef uint64_t enum__builtin_CompilerBackend_1683; /* builtin.CompilerBackend */
struct arr_128_u8_1742 { uint8_t array[128] zig_nonstring; }; /* [128]u8 */
zig_static_assert(sizeof (struct arr_128_u8_1742) == 128, "incorrect size");
zig_static_assert(_Alignof (struct arr_128_u8_1742) == 1, "incorrect alignment");
struct sockaddr_Storage_1739 { /* sockaddr.Storage */
 zig_align(8) struct arr_128_u8_1742 bytes;
};
zig_static_assert(sizeof (struct sockaddr_Storage_1739) == 128, "incorrect size");
zig_static_assert(_Alignof (struct sockaddr_Storage_1739) == 8, "incorrect alignment");
struct arr_6s116_u8_1807 { uint8_t array[7]; }; /* [6:0]u8 */
zig_static_assert(sizeof (struct arr_6s116_u8_1807) == 7, "incorrect size");
zig_static_assert(_Alignof (struct arr_6s116_u8_1807) == 1, "incorrect alignment");
#define sockaddr_short_buffer_is_never_read_past__224 short_buffer_is_never_read_past
zig_extern void short_buffer_is_never_read_past(void);
#define sockaddr_same_is_reflexive_for_every_family__223 same_is_reflexive_for_every_family
zig_extern void same_is_reflexive_for_every_family(void);
#define sockaddr_unclamped_length_never_panics__222 unclamped_length_never_panics
zig_extern void unclamped_length_never_panics(void);
#define sockaddr_same_is_reflexive_and_symmetric__221 same_is_reflexive_and_symmetric
zig_extern void same_is_reflexive_and_symmetric(void);
#define sockaddr_same_never_panics__220 same_never_panics
zig_extern void same_never_panics(void);
static struct arr_6s116_u8_1807 const __anon_1808;
static enum__builtin_OutputMode_147 const builtin_output_mode__229;
static bool const builtin_link_libc__240;
static struct Target_Os_201 const builtin_os__236;
static enum__Target_Os_Tag_203 const posix_native_os__306;
static bool const posix_use_libc__314;
static struct Target_Cpu_Feature_Set_660 const Target_Cpu_Feature_Set_empty__1666;
static struct Target_Cpu_645 const builtin_cpu__235;
static enum__Target_Abi_647 const builtin_abi__234;
static enum__Target_ObjectFormat_649 const builtin_object_format__238;
static struct Target_199 const builtin_target__237;
static struct builtin_CallingConvention_361 const builtin_CallingConvention_c__1540;
zig_extern void verifier_any(void *a0, uintptr_t a1);
static struct arr_16_u8_180 verifier_any__anon_190__304(void);
static bool sockaddr_same__219(struct os_linux_sockaddr_316 const *a0, signed int a1, struct os_linux_sockaddr_316 const *a2, signed int a3);
static struct slice_u8_50 sockaddr_unixName__217(struct os_linux_sockaddr_316 const *a0, signed int a1);
static zig_noreturn void panic_incorrectAlignment__2457(void);
static struct opt_usize_590 mem_findScalar__anon_1629__2473(struct slice_u8_50 a0, uint8_t a1);
zig_extern zig_noreturn void verifier_fail(uint32_t a0, uintptr_t a1, uintptr_t a2);
static zig_cold zig_noreturn void panic_fail__2446(enum__failure_Kind_1632 a0, uintptr_t a1, uintptr_t a2);
static enum__builtin_CompilerBackend_1683 const builtin_zig_backend__228;
static bool const mem_use_vectors__2181;
static bool const builtin_fuzz__245;
static bool const mem_use_vectors_for_comparison__2182;
static struct opt_usize_590 mem_findScalarPos__anon_1674__2476(struct slice_u8_50 a0, uintptr_t a1, uint8_t a2);
static zig_noreturn void panic_noreturnReturned__2472(void);
static zig_noreturn void panic_startGreaterThanEnd__2451(uintptr_t a0, uintptr_t a1);
static zig_noreturn void panic_outOfBounds__2450(uintptr_t a0, uintptr_t a1);
static zig_noreturn void panic_integerOverflow__2460(void);
static zig_noreturn void panic_integerOutOfBounds__2459(void);
static bool mem_eql__anon_1492__2443(struct slice_u8_50 a0, struct slice_u8_50 a1);
static zig_noreturn void panic_forLenMismatch__2469(void);
static struct sockaddr_Storage_1739 verifier_any__anon_1744__2478(void);
zig_extern void verifier_check(bool a0);
static void verifier_assert__300(bool a0);
static struct arr_128_u8_1742 verifier_any__anon_1782__2480(void);
static signed int verifier_any__anon_1748__2479(void);
static struct Target_DynamicLinker_651 const Target_DynamicLinker_none__1613;
static struct Target_Cpu_Model_655 const Target_x86_cpu_znver4__1786;
static struct slice_u8_50 sockaddr_unixNameUnclamped__218(struct os_linux_sockaddr_316 const *a0, signed int a1);
zig_extern void verifier_assume(bool a0);
static void verifier_assume__299(bool a0);
static struct slice_u8_51 const zig_errorName[0] = {};
static struct arr_6s116_u8_1807 const __anon_1808 = {"znver4"};
static enum__builtin_OutputMode_147 const builtin_output_mode__229 = UINT8_C(2);
static bool const builtin_link_libc__240 = false;
static struct Target_Os_201 const builtin_os__236 = {{ .tag = UINT8_C(3), .payload = { .linux = {{{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}}},{2ul,43ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},UINT32_C(29)} } },UINT8_C(9)};
static enum__Target_Os_Tag_203 const posix_native_os__306 = UINT8_C(9);
static bool const posix_use_libc__314 = false;
void sockaddr_short_buffer_is_never_read_past__224(void) {
 struct arr_16_u8_180 const *t2;
 struct os_linux_sockaddr_316 const *t3;
 struct os_linux_sockaddr_316 const *t4;
 struct arr_16_u8_180 zig_align(8) t0;
 struct arr_16_u8_180 t1;
 /* file:2:5 */
 /* file:2:44 */
 t1 = verifier_any__anon_190__304();
 t0 = t1;
 t2 = (struct arr_16_u8_180 const *)&t0;
 /* dbg_var_ptr:a */
 /* file:3:14 */
 t3 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:3:35 */
 t4 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:3:13 */
 (void)sockaddr_same__219(t3, 16, t4, 16);
 return;
}
static struct Target_Cpu_Feature_Set_660 const Target_Cpu_Feature_Set_empty__1666 = {{{0ul,0ul,0ul,0ul,0ul}}};
static struct Target_Cpu_645 const builtin_cpu__235 = {(((struct Target_Cpu_Model_655 const *)&Target_x86_cpu_znver4__1786)),{{{14373335171114205424ul,10664787974256315648ul,8073817237535973888ul,244ul,0ul}}},UINT8_C(54)};
static enum__Target_Abi_647 const builtin_abi__234 = UINT8_C(1);
static enum__Target_ObjectFormat_649 const builtin_object_format__238 = UINT8_C(0);
static struct Target_199 const builtin_target__237 = {{(((struct Target_Cpu_Model_655 const *)&Target_x86_cpu_znver4__1786)),{{{14373335171114205424ul,10664787974256315648ul,8073817237535973888ul,244ul,0ul}}},UINT8_C(54)},{{ .tag = UINT8_C(3), .payload = { .linux = {{{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},{7ul,0ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}}},{2ul,43ul,0ul,{NULL,0xaaaaaaaaaaaaaaaaul},{NULL,0xaaaaaaaaaaaaaaaaul}},UINT32_C(29)} } },UINT8_C(9)},UINT8_C(1),UINT8_C(0),{{"/lib64/ld-linux-x86-64.so.2\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},UINT8_C(27)}};
static struct builtin_CallingConvention_361 const builtin_CallingConvention_c__1540 = { .tag = UINT8_C(4), .payload = { .x86_64_sysv = {{ .is_null = true, .payload = UINT64_C(0xaaaaaaaaaaaaaaaa) }} } };
static struct arr_16_u8_180 verifier_any__anon_190__304(void) {
 void *t1;
 struct arr_16_u8_180 t2;
 struct arr_16_u8_180 t0;
 /* file:2:13 */
 /* file:14:13 */
 memset(&t0, 0xaa, sizeof(struct arr_16_u8_180));
 /* dbg_var_ptr:value */
 /* file:15:17 */
 /* file:16:29 */
 t1 = (void *)&t0;
 /* file:16:29 */
 verifier_any(t1, (uintptr_t)16ul);
 /* file:20:13 */
 t2 = t0;
 /* file:20:13 */
 return t2;
}
static bool sockaddr_same__219(struct os_linux_sockaddr_316 const *const a0, signed int const a1, struct os_linux_sockaddr_316 const *const a2, signed int const a3) {
 struct os_linux_sockaddr_316 const *const *t1;
 struct os_linux_sockaddr_316 const *const *t3;
 struct os_linux_sockaddr_316 const *t4;
 struct os_linux_sockaddr_316 const *t0;
 struct os_linux_sockaddr_316 const *t2;
 uint16_t const *t5;
 struct slice_u8_50 t9;
 struct slice_u8_50 t10;
 uintptr_t t11;
 struct os_linux_sockaddr_in_1496 const *t12;
 struct os_linux_sockaddr_in_1496 const *t13;
 struct os_linux_sockaddr_in_1496 const *t15;
 struct os_linux_sockaddr_in_1496 const *const *t14;
 struct os_linux_sockaddr_in_1496 const *const *t16;
 uint32_t const *t18;
 struct os_linux_sockaddr_in6_1588 const *t21;
 struct os_linux_sockaddr_in6_1588 const *t22;
 struct os_linux_sockaddr_in6_1588 const *t24;
 struct os_linux_sockaddr_in6_1588 const *const *t23;
 struct os_linux_sockaddr_in6_1588 const *const *t25;
 struct arr_16_u8_180 const *t26;
 uint32_t t19;
 uint32_t t20;
 uint16_t t6;
 uint16_t t7;
 bool t8;
 bool t17;
 t0 = a0;
 t1 = (struct os_linux_sockaddr_316 const *const *)&t0;
 t2 = a2;
 t3 = (struct os_linux_sockaddr_316 const *const *)&t2;
 /* file:2:9 */
 /* file:2:10 */
 t4 = (*t1);
 t5 = (uint16_t const *)&t4->family;
 t6 = (*t5);
 /* file:2:22 */
 t4 = (*t3);
 t5 = (uint16_t const *)&t4->family;
 t7 = (*t5);
 t8 = t6 != t7;
 if (t8) {
  /* file:2:31 */
  return false;
 }
 goto zig_block_0;

zig_block_0:;
 /* file:3:9 */
 /* file:3:10 */
 t4 = (*t1);
 t5 = (uint16_t const *)&t4->family;
 t7 = (*t5);
 /* file:3:29 */
 t8 = t7 == UINT16_C(1);
 if (t8) {
  /* file:3:67 */
  t9 = sockaddr_unixName__217(a0, a1);
  /* file:3:87 */
  t10 = sockaddr_unixName__217(a2, a3);
  /* file:3:54 */
  t8 = mem_eql__anon_1492__2443(t9, t10);
  /* file:3:36 */
  return t8;
 }
 goto zig_block_1;

zig_block_1:;
 /* file:4:9 */
 /* file:4:10 */
 t4 = (*t1);
 t5 = (uint16_t const *)&t4->family;
 t7 = (*t5);
 /* file:4:29 */
 t8 = t7 == UINT16_C(2);
 if (t8) {
  /* file:5:45 */
  t11 = (uintptr_t)a0;
  t11 = t11 & (uintptr_t)3ul;
  t8 = t11 == (uintptr_t)0ul;
  if (t8) {
   goto zig_block_3;
  }
  panic_incorrectAlignment__2457();
  zig_unreachable();

zig_block_3:;
  t12 = (struct os_linux_sockaddr_in_1496 const *)a0;
  t13 = t12;
  t14 = (struct os_linux_sockaddr_in_1496 const *const *)&t13;
  /* dbg_var_val:x */
  /* file:6:45 */
  t11 = (uintptr_t)a2;
  t11 = t11 & (uintptr_t)3ul;
  t8 = t11 == (uintptr_t)0ul;
  if (t8) {
   goto zig_block_4;
  }
  panic_incorrectAlignment__2457();
  zig_unreachable();

zig_block_4:;
  t12 = (struct os_linux_sockaddr_in_1496 const *)a2;
  t15 = t12;
  t16 = (struct os_linux_sockaddr_in_1496 const *const *)&t15;
  /* dbg_var_val:y */
  /* file:7:17 */
  t12 = (*t14);
  t5 = (uint16_t const *)&t12->port;
  t7 = (*t5);
  /* file:7:27 */
  t12 = (*t16);
  t5 = (uint16_t const *)&t12->port;
  t6 = (*t5);
  t8 = t7 == t6;
  if (t8) {
   /* file:7:38 */
   t12 = (*t14);
   t18 = (uint32_t const *)&t12->addr;
   t19 = (*t18);
   /* file:7:48 */
   t12 = (*t16);
   t18 = (uint32_t const *)&t12->addr;
   t20 = (*t18);
   t8 = t19 == t20;
   t17 = t8;
   goto zig_block_5;
  }
  t17 = false;
  goto zig_block_5;

zig_block_5:;
  /* file:7:9 */
  return t17;
 }
 goto zig_block_2;

zig_block_2:;
 /* file:9:9 */
 /* file:9:10 */
 t4 = (*t1);
 t5 = (uint16_t const *)&t4->family;
 t7 = (*t5);
 /* file:9:29 */
 t17 = t7 == UINT16_C(10);
 if (t17) {
  /* file:10:46 */
  t11 = (uintptr_t)a0;
  t11 = t11 & (uintptr_t)3ul;
  t17 = t11 == (uintptr_t)0ul;
  if (t17) {
   goto zig_block_7;
  }
  panic_incorrectAlignment__2457();
  zig_unreachable();

zig_block_7:;
  t21 = (struct os_linux_sockaddr_in6_1588 const *)a0;
  t22 = t21;
  t23 = (struct os_linux_sockaddr_in6_1588 const *const *)&t22;
  /* dbg_var_val:x */
  /* file:11:46 */
  t11 = (uintptr_t)a2;
  t11 = t11 & (uintptr_t)3ul;
  t17 = t11 == (uintptr_t)0ul;
  if (t17) {
   goto zig_block_8;
  }
  panic_incorrectAlignment__2457();
  zig_unreachable();

zig_block_8:;
  t21 = (struct os_linux_sockaddr_in6_1588 const *)a2;
  t24 = t21;
  t25 = (struct os_linux_sockaddr_in6_1588 const *const *)&t24;
  /* dbg_var_val:y */
  /* file:12:13 */
  /* file:12:14 */
  t21 = (*t23);
  t5 = (uint16_t const *)&t21->port;
  t7 = (*t5);
  /* file:12:24 */
  t21 = (*t25);
  t5 = (uint16_t const *)&t21->port;
  t6 = (*t5);
  t17 = t7 != t6;
  if (t17) {
   t8 = true;
   goto zig_block_10;
  }
  /* file:12:52 */
  t21 = (*t23);
  t26 = (struct arr_16_u8_180 const *)&t21->addr;
  t10.ptr = (uint8_t const *)t26;
  t10.len = (uintptr_t)16ul;
  /* file:12:61 */
  t21 = (*t25);
  t26 = (struct arr_16_u8_180 const *)&t21->addr;
  t9.ptr = (uint8_t const *)t26;
  t9.len = (uintptr_t)16ul;
  /* file:12:45 */
  t17 = mem_eql__anon_1492__2443(t10, t9);
  t17 = !t17;
  t8 = t17;
  goto zig_block_10;

zig_block_10:;
  if (t8) {
   /* file:12:69 */
   return false;
  }
  goto zig_block_9;

zig_block_9:;
  /* file:13:17 */
  t21 = (*t23);
  t18 = (uint32_t const *)&t21->flowinfo;
  t20 = (*t18);
  /* file:13:31 */
  t21 = (*t25);
  t18 = (uint32_t const *)&t21->flowinfo;
  t19 = (*t18);
  t17 = t20 == t19;
  if (t17) {
   /* file:13:46 */
   t21 = (*t23);
   t18 = (uint32_t const *)&t21->scope_id;
   t19 = (*t18);
   /* file:13:60 */
   t21 = (*t25);
   t18 = (uint32_t const *)&t21->scope_id;
   t20 = (*t18);
   t17 = t19 == t20;
   t8 = t17;
   goto zig_block_11;
  }
  t8 = false;
  goto zig_block_11;

zig_block_11:;
  /* file:13:9 */
  return t8;
 }
 goto zig_block_6;

zig_block_6:;
 /* file:15:5 */
 return false;
}
static struct slice_u8_50 sockaddr_unixName__217(struct os_linux_sockaddr_316 const *const a0, signed int const a1) {
 struct os_linux_sockaddr_un_1594 const *t0;
 struct os_linux_sockaddr_un_1594 const *t1;
 struct os_linux_sockaddr_un_1594 const *const *t2;
 struct arr_108_u8_1599 const *t5;
 struct arr_108_u8_1599 const *t18;
 uint8_t const *t6 zig_nonstring;
 struct arr_0_u8_1617 const *t7;
 struct slice_u8_50 t8;
 uintptr_t t9;
 uintptr_t t10;
 uintptr_t t19;
 struct tuple_2_usize_u1_671088641 t11;
 uint64_t t13;
 uint8_t const *t15 zig_nonstring;
 struct slice_u8_1623 t17;
 struct opt_usize_590 t20;
 int32_t t3;
 bool t4;
 uint8_t t12;
 uint8_t t14;
 uint8_t t16;
 /* file:2:42 */
 t0 = (struct os_linux_sockaddr_un_1594 const *)a0;
 t1 = t0;
 t2 = (struct os_linux_sockaddr_un_1594 const *const *)&t1;
 /* dbg_var_val:un */
 /* file:3:9 */
 t3 = a1;
 t4 = t3 <= INT32_C(2);
 if (t4) {
  /* file:3:34 */
  t0 = (*t2);
  t5 = (struct arr_108_u8_1599 const *)&t0->path;
  /* file:3:39 */
  t6 = (uint8_t const *)t5;
  t6 = (uint8_t const *)(((uintptr_t)t6) + ((uintptr_t)0ul*sizeof(uint8_t)));
  t7 = (struct arr_0_u8_1617 const *)t6;
  /* file:3:25 */
  t8.ptr = (uint8_t const *)t7;
  t8.len = (uintptr_t)0ul;
  return t8;
 }
 goto zig_block_0;

zig_block_0:;
 /* file:4:31 */
 t4 = a1 < 0;
 if (t4) {
  panic_integerOutOfBounds__2459();
  zig_unreachable();
 }
 t10 = (uintptr_t)a1;
 t9 = t10;
 goto zig_block_1;

zig_block_1:;
 /* file:4:46 */
 t11.f1 = zig_subo_u64(&t11.f0, t9, (uintptr_t)2ul, UINT8_C(64));
 t12 = t11.f1;
 t4 = t12 == UINT8_C(1);
 if (t4) {
  panic_integerOverflow__2460();
  zig_unreachable();
 }
 t9 = t11.f0;
 t10 = t9;
 goto zig_block_2;

zig_block_2:;
 /* file:4:59 */
 /* file:4:64 */
 t13 = t10;
 t13 = (UINT64_C(108) < t13) ? UINT64_C(108) : t13;
 t14 = (uint8_t)t13;
 /* dbg_var_val:n */
 /* file:5:9 */
 /* file:5:11 */
 t0 = (*t2);
 t5 = (struct arr_108_u8_1599 const *)&t0->path;
 /* file:5:16 */
 t15 = &t5->array[(uintptr_t)0ul];
 t16 = (*t15);
 t4 = t16 == UINT8_C(0);
 if (t4) {
  /* file:5:35 */
  t0 = (*t2);
  t5 = (struct arr_108_u8_1599 const *)&t0->path;
  /* file:5:40 */
  t6 = (uint8_t const *)t5;
  t6 = (uint8_t const *)(((uintptr_t)t6) + ((uintptr_t)0ul*sizeof(uint8_t)));
  t10 = (uintptr_t)t14;
  t9 = t10 - (uintptr_t)0ul;
  t4 = t10 <= (uintptr_t)108ul;
  if (t4) {
   goto zig_block_4;
  }
  panic_outOfBounds__2450(t10, (uintptr_t)108ul);
  zig_unreachable();

zig_block_4:;
  t17.ptr = t6;
  t17.len = t9;
  /* file:5:26 */
  memcpy(&t8, &t17, 16);
  return t8;
 }
 goto zig_block_3;

zig_block_3:;
 /* file:6:14 */
 t0 = (*t2);
 t5 = (struct arr_108_u8_1599 const *)&t0->path;
 /* file:6:53 */
 t0 = (*t2);
 t18 = (struct arr_108_u8_1599 const *)&t0->path;
 /* file:6:58 */
 t6 = (uint8_t const *)t18;
 t6 = (uint8_t const *)(((uintptr_t)t6) + ((uintptr_t)0ul*sizeof(uint8_t)));
 t9 = (uintptr_t)t14;
 t19 = t9 - (uintptr_t)0ul;
 t4 = t9 <= (uintptr_t)108ul;
 if (t4) {
  goto zig_block_6;
 }
 panic_outOfBounds__2450(t9, (uintptr_t)108ul);
 zig_unreachable();

zig_block_6:;
 t17.ptr = t6;
 t17.len = t19;
 memcpy(&t8, &t17, 16);
 /* file:6:46 */
 t20 = mem_findScalar__anon_1629__2473(t8, UINT8_C(0));
 t4 = !t20.is_null;
 if (t4) {
  t19 = t20.payload;
  t10 = t19;
  goto zig_block_5;
 }
 t19 = (uintptr_t)t14;
 t10 = t19;
 goto zig_block_5;

zig_block_5:;
 /* file:6:19 */
 t6 = (uint8_t const *)t5;
 t6 = (uint8_t const *)(((uintptr_t)t6) + ((uintptr_t)0ul*sizeof(uint8_t)));
 t19 = t10 - (uintptr_t)0ul;
 t4 = t10 <= (uintptr_t)108ul;
 if (t4) {
  goto zig_block_7;
 }
 panic_outOfBounds__2450(t10, (uintptr_t)108ul);
 zig_unreachable();

zig_block_7:;
 t17.ptr = t6;
 t17.len = t19;
 /* file:6:5 */
 memcpy(&t8, &t17, 16);
 return t8;
}
static zig_noreturn void panic_incorrectAlignment__2457(void) {
 /* file:2:9 */
 panic_fail__2446(UINT32_C(11), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static struct opt_usize_590 mem_findScalar__anon_1629__2473(struct slice_u8_50 const a0, uint8_t const a1) {
 struct opt_usize_590 t0;
 /* file:2:25 */
 t0 = mem_findScalarPos__anon_1674__2476(a0, (uintptr_t)0ul, a1);
 /* file:2:5 */
 return t0;
}
static zig_cold zig_noreturn void panic_fail__2446(enum__failure_Kind_1632 const a0, uintptr_t const a1, uintptr_t const a2) {
 uint32_t t0;
 /* file:3:18 */
 t0 = a0;
 /* file:3:18 */
 verifier_fail(t0, a1, a2);
 panic_noreturnReturned__2472();
 zig_unreachable();
}
static enum__builtin_CompilerBackend_1683 const builtin_zig_backend__228 = UINT64_C(3);
static bool const mem_use_vectors__2181 = true;
static bool const builtin_fuzz__245 = true;
static bool const mem_use_vectors_for_comparison__2182 = false;
static struct opt_usize_590 mem_findScalarPos__anon_1674__2476(struct slice_u8_50 const a0, uintptr_t const a1, uint8_t const a2) {
 struct slice_u8_50 const *t1;
 uintptr_t const *t2;
 uintptr_t t3;
 uintptr_t t11;
 uintptr_t t12;
 uintptr_t t14;
 uintptr_t t17;
 uintptr_t t7;
 uintptr_t t8;
 uint64_t t4;
 uint64_t t5;
 struct slice_u8_50 t9;
 struct slice_u8_50 t0;
 uint8_t const *t10 zig_nonstring;
 struct tuple_2_usize_u1_671088641 t15;
 struct opt_usize_590 t18;
 bool t6;
 uint8_t t13;
 uint8_t t16;
 t0 = a0;
 t1 = (struct slice_u8_50 const *)&t0;
 /* file:2:9 */
 /* file:2:29 */
 t2 = &t1->len;
 t3 = (*t2);
 t4 = a1;
 t5 = t3;
 t6 = t4 >= t5;
 if (t6) {
  /* file:2:35 */
  return (struct opt_usize_590){ .is_null = true, .payload = (uintptr_t)0xaaaaaaaaaaaaaaaaul };
 }
 goto zig_block_0;

zig_block_0:;
 /* file:4:5 */
 t7 = a1;
 /* dbg_var_ptr:i */
 /* file:5:9 */
 t8 = (uintptr_t)0ul;
 /* file:57:10 */
 t3 = t7;
 /* file:57:15 */
 t9 = (*t1);
 t10 = t9.ptr;
 t10 = (uint8_t const *)(((uintptr_t)t10) + (t3*sizeof(uint8_t)));
 t11 = t9.len;
 t6 = t3 <= t11;
 if (t6) {
  goto zig_block_1;
 }
 panic_startGreaterThanEnd__2451(t3, t11);
 zig_unreachable();

zig_block_1:;
 t3 = t11 - t3;
 t12 = t9.len;
 t6 = t11 <= t12;
 if (t6) {
  goto zig_block_2;
 }
 panic_outOfBounds__2450(t11, t12);
 zig_unreachable();

zig_block_2:;
 t9.ptr = t10;
 t9.len = t3;
 /* file:57:22 */
 t3 = t7;
 t12 = t9.len;
 zig_loop_53:
 t11 = t8;
 t5 = t11;
 t4 = t12;
 t6 = t5 < t4;
 if (t6) {
  t13 = t9.ptr[t11];
  /* dbg_var_val:c */
  t15.f1 = zig_addo_u64(&t15.f0, t3, t11, UINT8_C(64));
  t16 = t15.f1;
  t6 = t16 == UINT8_C(1);
  if (t6) {
   panic_integerOverflow__2460();
   zig_unreachable();
  }
  t17 = t15.f0;
  t14 = t17;
  goto zig_block_5;

zig_block_5:;
  /* dbg_var_val:j */
  /* file:58:13 */
  t6 = t13 == a2;
  if (t6) {
   /* file:58:25 */
   t18.is_null = false;
   t18.payload = t14;
   return t18;
  }
  goto zig_block_6;

zig_block_6:;
  /* file:59:5 */
  (void)0;
  goto zig_block_4;
 }
 goto zig_block_3;

zig_block_4:;
 t11 = t11 + (uintptr_t)1ul;
 t8 = t11;
 goto zig_loop_53;

zig_block_3:;
 /* file:60:5 */
 return (struct opt_usize_590){ .is_null = true, .payload = (uintptr_t)0xaaaaaaaaaaaaaaaaul };
}
static zig_noreturn void panic_noreturnReturned__2472(void) {
 /* file:2:9 */
 panic_fail__2446(UINT32_C(26), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static zig_noreturn void panic_startGreaterThanEnd__2451(uintptr_t const a0, uintptr_t const a1) {
 /* file:2:9 */
 panic_fail__2446(UINT32_C(5), a0, a1);
 zig_unreachable();
}
static zig_noreturn void panic_outOfBounds__2450(uintptr_t const a0, uintptr_t const a1) {
 /* file:2:9 */
 panic_fail__2446(UINT32_C(4), a0, a1);
 zig_unreachable();
}
static zig_noreturn void panic_integerOverflow__2460(void) {
 /* file:2:9 */
 panic_fail__2446(UINT32_C(14), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static zig_noreturn void panic_integerOutOfBounds__2459(void) {
 /* file:2:9 */
 panic_fail__2446(UINT32_C(13), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
static bool mem_eql__anon_1492__2443(struct slice_u8_50 const a0, struct slice_u8_50 const a1) {
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
 panic_forLenMismatch__2469();
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
static zig_noreturn void panic_forLenMismatch__2469(void) {
 /* file:2:9 */
 panic_fail__2446(UINT32_C(23), (uintptr_t)0ul, (uintptr_t)0ul);
 zig_unreachable();
}
void sockaddr_same_is_reflexive_for_every_family__223(void) {
 struct sockaddr_Storage_1739 t0;
 struct sockaddr_Storage_1739 t1;
 struct sockaddr_Storage_1739 const *t2;
 struct os_linux_sockaddr_316 const *t4;
 struct os_linux_sockaddr_316 const *t5;
 signed int t3;
 bool t6;
 /* file:2:27 */
 t0 = verifier_any__anon_1744__2478();
 t1 = t0;
 t2 = (struct sockaddr_Storage_1739 const *)&t1;
 /* dbg_var_val:a */
 /* file:3:29 */
 t3 = verifier_any__anon_1748__2479();
 /* dbg_var_val:len */
 /* file:4:26 */
 t4 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:4:45 */
 t5 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:4:25 */
 t6 = sockaddr_same__219(t4, t3, t5, t3);
 /* file:4:20 */
 verifier_assert__300(t6);
 return;
}
static struct sockaddr_Storage_1739 verifier_any__anon_1744__2478(void) {
 struct arr_128_u8_1742 *t1;
 struct sockaddr_Storage_1739 t3;
 struct sockaddr_Storage_1739 t0;
 struct arr_128_u8_1742 t2;
 /* file:2:13 */
 /* file:33:17 */
 /* file:34:13 */
 memset(&t0, 0xaa, sizeof(struct sockaddr_Storage_1739));
 /* dbg_var_ptr:value */
 /* file:36:21 */
 /* file:36:41 */
 t1 = (struct arr_128_u8_1742 *)&t0.bytes;
 /* file:36:72 */
 t2 = verifier_any__anon_1782__2480();
 (*t1) = t2;
 /* file:37:13 */
 (void)0;
 /* file:38:13 */
 t3 = t0;
 /* file:38:13 */
 return t3;
}
static void verifier_assert__300(bool const a0) {
 /* file:2:19 */
 verifier_check(a0);
 return;
}
static struct arr_128_u8_1742 verifier_any__anon_1782__2480(void) {
 void *t1;
 struct arr_128_u8_1742 t2;
 struct arr_128_u8_1742 t0;
 /* file:2:13 */
 /* file:14:13 */
 memset(&t0, 0xaa, sizeof(struct arr_128_u8_1742));
 /* dbg_var_ptr:value */
 /* file:15:17 */
 /* file:16:29 */
 t1 = (void *)&t0;
 /* file:16:29 */
 verifier_any(t1, (uintptr_t)128ul);
 /* file:20:13 */
 t2 = t0;
 /* file:20:13 */
 return t2;
}
static signed int verifier_any__anon_1748__2479(void) {
 void *t1;
 uint32_t t2;
 uint32_t t0;
 signed int t3;
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
 memcpy(&t3, &t2, 4);
 t3 = zig_wrap_i32(t3, UINT8_C(32));
 /* file:10:13 */
 return t3;
}
static struct Target_DynamicLinker_651 const Target_DynamicLinker_none__1613 = {{"\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252\252"},UINT8_C(0)};
static struct Target_Cpu_Model_655 const Target_x86_cpu_znver4__1786 = {{((uint8_t const *)((struct arr_6s116_u8_1807 const *)&__anon_1808)),6ul},{((uint8_t const *)((struct arr_6s116_u8_1807 const *)&__anon_1808)),6ul},{{{177989145354830000ul,14125804287856987392ul,8071020079954911744ul,229ul,0ul}}}};
void sockaddr_unclamped_length_never_panics__222(void) {
 struct sockaddr_Storage_1739 t0;
 struct sockaddr_Storage_1739 t1;
 struct sockaddr_Storage_1739 const *t2;
 struct os_linux_sockaddr_316 const *t3;
 signed int t4;
 /* file:2:27 */
 t0 = verifier_any__anon_1744__2478();
 t1 = t0;
 t2 = (struct sockaddr_Storage_1739 const *)&t1;
 /* dbg_var_val:a */
 /* file:3:27 */
 t3 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:3:53 */
 t4 = verifier_any__anon_1748__2479();
 /* file:3:26 */
 (void)sockaddr_unixNameUnclamped__218(t3, t4);
 return;
}
static struct slice_u8_50 sockaddr_unixNameUnclamped__218(struct os_linux_sockaddr_316 const *const a0, signed int const a1) {
 struct os_linux_sockaddr_un_1594 const *t0;
 struct os_linux_sockaddr_un_1594 const *t1;
 struct os_linux_sockaddr_un_1594 const *const *t2;
 struct arr_108_u8_1599 const *t5;
 uint8_t const *t6 zig_nonstring;
 struct arr_0_u8_1617 const *t7;
 struct slice_u8_50 t8;
 uintptr_t t9;
 uintptr_t t10;
 struct tuple_2_usize_u1_671088641 t11;
 struct slice_u8_1623 t13;
 int32_t t3;
 bool t4;
 uint8_t t12;
 /* file:2:42 */
 t0 = (struct os_linux_sockaddr_un_1594 const *)a0;
 t1 = t0;
 t2 = (struct os_linux_sockaddr_un_1594 const *const *)&t1;
 /* dbg_var_val:un */
 /* file:3:9 */
 t3 = a1;
 t4 = t3 <= INT32_C(2);
 if (t4) {
  /* file:3:34 */
  t0 = (*t2);
  t5 = (struct arr_108_u8_1599 const *)&t0->path;
  /* file:3:39 */
  t6 = (uint8_t const *)t5;
  t6 = (uint8_t const *)(((uintptr_t)t6) + ((uintptr_t)0ul*sizeof(uint8_t)));
  t7 = (struct arr_0_u8_1617 const *)t6;
  /* file:3:25 */
  t8.ptr = (uint8_t const *)t7;
  t8.len = (uintptr_t)0ul;
  return t8;
 }
 goto zig_block_0;

zig_block_0:;
 /* file:4:14 */
 t0 = (*t2);
 t5 = (struct arr_108_u8_1599 const *)&t0->path;
 /* file:4:36 */
 t4 = a1 < 0;
 if (t4) {
  panic_integerOutOfBounds__2459();
  zig_unreachable();
 }
 t10 = (uintptr_t)a1;
 t9 = t10;
 goto zig_block_1;

zig_block_1:;
 /* file:4:51 */
 t11.f1 = zig_subo_u64(&t11.f0, t9, (uintptr_t)2ul, UINT8_C(64));
 t12 = t11.f1;
 t4 = t12 == UINT8_C(1);
 if (t4) {
  panic_integerOverflow__2460();
  zig_unreachable();
 }
 t9 = t11.f0;
 t10 = t9;
 goto zig_block_2;

zig_block_2:;
 /* file:4:19 */
 t6 = (uint8_t const *)t5;
 t6 = (uint8_t const *)(((uintptr_t)t6) + ((uintptr_t)0ul*sizeof(uint8_t)));
 t9 = t10 - (uintptr_t)0ul;
 t4 = t10 <= (uintptr_t)108ul;
 if (t4) {
  goto zig_block_3;
 }
 panic_outOfBounds__2450(t10, (uintptr_t)108ul);
 zig_unreachable();

zig_block_3:;
 t13.ptr = t6;
 t13.len = t9;
 /* file:4:5 */
 memcpy(&t8, &t13, 16);
 return t8;
}
void sockaddr_same_is_reflexive_and_symmetric__221(void) {
 struct sockaddr_Storage_1739 t0;
 struct sockaddr_Storage_1739 t1;
 struct sockaddr_Storage_1739 t3;
 struct sockaddr_Storage_1739 const *t2;
 struct sockaddr_Storage_1739 const *t4;
 struct os_linux_sockaddr_316 const *t7;
 struct os_linux_sockaddr_316 const *t14;
 struct os_linux_sockaddr_316 const *t8;
 struct os_linux_sockaddr_316 const *const *t9;
 uint16_t const *t10;
 signed int t5;
 signed int t6;
 uint16_t t11;
 bool t12;
 bool t13;
 /* file:2:27 */
 t0 = verifier_any__anon_1744__2478();
 t1 = t0;
 t2 = (struct sockaddr_Storage_1739 const *)&t1;
 /* dbg_var_val:a */
 /* file:3:27 */
 t0 = verifier_any__anon_1744__2478();
 t3 = t0;
 t4 = (struct sockaddr_Storage_1739 const *)&t3;
 /* dbg_var_val:b */
 /* file:4:31 */
 t5 = verifier_any__anon_1748__2479();
 /* dbg_var_val:a_len */
 /* file:5:31 */
 t6 = verifier_any__anon_1748__2479();
 /* dbg_var_val:b_len */
 /* file:6:47 */
 t7 = (struct os_linux_sockaddr_316 const *)t2;
 t8 = t7;
 t9 = (struct os_linux_sockaddr_316 const *const *)&t8;
 /* file:6:60 */
 t7 = (*t9);
 t10 = (uint16_t const *)&t7->family;
 t11 = (*t10);
 /* dbg_var_val:family */
 /* file:7:39 */
 t12 = t11 == UINT16_C(1);
 if (t12) {
  t13 = true;
  goto zig_block_0;
 }
 /* file:7:66 */
 t12 = t11 == UINT16_C(2);
 t13 = t12;
 goto zig_block_0;

zig_block_0:;
 if (t13) {
  t12 = true;
  goto zig_block_1;
 }
 /* file:7:93 */
 t13 = t11 == UINT16_C(10);
 t12 = t13;
 goto zig_block_1;

zig_block_1:;
 /* file:7:20 */
 verifier_assume__299(t12);
 /* file:8:26 */
 t7 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:8:47 */
 t14 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:8:25 */
 t12 = sockaddr_same__219(t7, t5, t14, t5);
 /* file:8:20 */
 verifier_assert__300(t12);
 /* file:9:26 */
 t14 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:9:47 */
 t7 = (struct os_linux_sockaddr_316 const *)t4;
 /* file:9:25 */
 t12 = sockaddr_same__219(t14, t5, t7, t6);
 /* file:9:76 */
 t7 = (struct os_linux_sockaddr_316 const *)t4;
 /* file:9:97 */
 t14 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:9:75 */
 t13 = sockaddr_same__219(t7, t6, t14, t5);
 t13 = t12 == t13;
 /* file:9:20 */
 verifier_assert__300(t13);
 return;
}
static void verifier_assume__299(bool const a0) {
 /* file:2:20 */
 verifier_assume(a0);
 return;
}
void sockaddr_same_never_panics__220(void) {
 struct sockaddr_Storage_1739 t0;
 struct sockaddr_Storage_1739 t1;
 struct sockaddr_Storage_1739 t3;
 struct sockaddr_Storage_1739 const *t2;
 struct sockaddr_Storage_1739 const *t4;
 struct os_linux_sockaddr_316 const *t5;
 struct os_linux_sockaddr_316 const *t7;
 signed int t6;
 signed int t8;
 /* file:2:27 */
 t0 = verifier_any__anon_1744__2478();
 t1 = t0;
 t2 = (struct sockaddr_Storage_1739 const *)&t1;
 /* dbg_var_val:a */
 /* file:3:27 */
 t0 = verifier_any__anon_1744__2478();
 t3 = t0;
 t4 = (struct sockaddr_Storage_1739 const *)&t3;
 /* dbg_var_val:b */
 /* file:4:14 */
 t5 = (struct os_linux_sockaddr_316 const *)t2;
 /* file:4:40 */
 t6 = verifier_any__anon_1748__2479();
 /* file:4:49 */
 t7 = (struct os_linux_sockaddr_316 const *)t4;
 /* file:4:75 */
 t8 = verifier_any__anon_1748__2479();
 /* file:4:13 */
 (void)sockaddr_same__219(t5, t6, t7, t8);
 return;
}
