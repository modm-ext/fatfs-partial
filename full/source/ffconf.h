/*---------------------------------------------------------------------------/
/  Configurations of FatFs Module
/---------------------------------------------------------------------------*/

#define FFCONF_DEF	80386	/* Revision ID */

/*---------------------------------------------------------------------------/
/ Function Configurations
/---------------------------------------------------------------------------*/

#define FF_FS_READONLY	0
/* This option switches read-only configuration. (0:Read/Write or 1:Read-only)
/  Read-only configuration removes writing API functions, f_write(), f_sync(),
/  f_unlink(), f_mkdir(), f_chmod(), f_rename(), f_truncate(), f_getfree()
/  and optional writing functions as well. */


#define FF_FS_MINIMIZE	0
/* This option defines minimization level to remove some basic API functions.
/
/   0: Basic functions are fully enabled.
/   1: f_stat(), f_getfree(), f_unlink(), f_mkdir(), f_truncate() and f_rename()
/      are removed.
/   2: f_opendir(), f_readdir() and f_closedir() are removed in addition to 1.
/   3: f_lseek() function is removed in addition to 2. */


#define FF_USE_FIND		0
/* This option switches filtered directory read functions, f_findfirst() and
/  f_findnext(). (0:Disable, 1:Enable 2:Enable with matching altname[] too) */


#define FF_USE_MKFS		0
/* This option switches f_mkfs(). (0:Disable or 1:Enable) */


#define FF_USE_FASTSEEK	0
/* This option switches fast seek feature. (0:Disable or 1:Enable) */


#define FF_USE_EXPAND	0
/* This option switches f_expand(). (0:Disable or 1:Enable) */


#define FF_USE_CHMOD	0
/* This option switches attribute control API functions, f_chmod() and f_utime().
/  (0:Disable or 1:Enable) Also FF_FS_READONLY needs to be 0 to enable this option. */


#define FF_USE_LABEL	0
/* This option switches volume label API functions, f_getlabel() and f_setlabel().
/  (0:Disable or 1:Enable) */


#define FF_USE_FORWARD	0
/* This option switches f_forward(). (0:Disable or 1:Enable) */


#define FF_USE_STRFUNC	0
#define FF_PRINT_LLI	0
#define FF_PRINT_FLOAT	0
#define FF_STRF_ENCODE	0
/* FF_USE_STRFUNC switches string API functions, f_gets(), f_putc(), f_puts() and
/  f_printf().
/
/   0: Disable. FF_PRINT_LLI, FF_PRINT_FLOAT and FF_STRF_ENCODE have no effect.
/   1: Enable without LF-CRLF conversion.
/   2: Enable with LF-CRLF conversion.
/
/  FF_PRINT_LLI = 1 makes f_printf() support long long argument and FF_PRINT_FLOAT = 1/2
/  makes f_printf() support floating point argument. These features want C99 or later.
/  When FF_LFN_UNICODE >= 1 with LFN enabled, string API functions convert the character
/  encoding in it. FF_STRF_ENCODE selects assumption of character encoding ON THE FILE
/  to be read/written via those functions.
/
/   0: ANSI/OEM in current CP
/   1: Unicode in UTF-16LE
/   2: Unicode in UTF-16BE
/   3: Unicode in UTF-8
*/


/*---------------------------------------------------------------------------/
/ Locale and Namespace Configurations
/---------------------------------------------------------------------------*/

#define FF_CODE_PAGE	932
/* This option specifies the OEM code page to be used on the target system.
/  Incorrect code page setting can cause a file open failure.
/
/   437 - U.S.
/   720 - Arabic
/   737 - Greek
/   771 - KBL
/   775 - Baltic
/   850 - Latin 1
/   852 - Latin 2
/   855 - Cyrillic
/   857 - Turkish
/   860 - Portuguese
/   861 - Icelandic
/   862 - Hebrew
/   863 - Canadian French
/   864 - Arabic
/   865 - Nordic
/   866 - Russian
/   869 - Greek 2
/   932 - Japanese (DBCS)
/   936 - Simplified Chinese (DBCS)
/   949 - Korean (DBCS)
/   950 - Traditional Chinese (DBCS)
/     0 - Include all code pages above and configured by f_setcp()
*/


#define FF_USE_LFN		0
#define FF_MAX_LFN		255
/* The FF_USE_LFN switches the support for LFN (long file name).
/
/   0: Disable LFN. FF_MAX_LFN has no effect.
/   1: Enable LFN with static working buffer on the BSS. Always NOT thread-safe.
/   2: Enable LFN with dynamic working buffer on the STACK.
/   3: Enable LFN with dynamic working buffer on the HEAP.
/
/  To enable the LFN, ffunicode.c needs to be added to the project. The LFN feature
/  requiers certain internal working buffer occupies (FF_MAX_LFN + 1) * 2 bytes and
/  additional (FF_MAX_LFN + 44) / 15 * 32 bytes when exFAT is enabled.
/  The FF_MAX_LFN defines size of the working buffer in UTF-16 code unit and it can
/  be in range of 12 to 255. It is recommended to be set 255 to fully support the LFN
/  specification.
/  When use stack for the working buffer, take care on stack overflow. When use heap
/  memory for the working buffer, memory management functions, ff_memalloc() and
/  ff_memfree() exemplified in ffsystem.c, need to be added to the project. */


#define FF_LFN_UNICODE	0
/* This option switches the character encoding on the API when LFN is enabled.
/
/   0: ANSI/OEM in current CP (TCHAR = char)
/   1: Unicode in UTF-16 (TCHAR = WCHAR)
/   2: Unicode in UTF-8 (TCHAR = char)
/   3: Unicode in UTF-32 (TCHAR = DWORD)
/
/  Also behavior of string I/O functions will be affected by this option.
/  When LFN is not enabled, this option has no effect. */


#define FF_LFN_BUF		255
#define FF_SFN_BUF		12
/* This set of options defines size of file name members in the FILINFO structure
/  which is used to read out directory items. These values should be suffcient for
/  the file names to read. The maximum possible length of the read file name depends
/  on character encoding. When LFN is not enabled, these options have no effect. */


#define FF_FS_RPATH		0
/* This option configures support for relative path feature.
/
/   0: Disable relative path and remove related API functions.
/   1: Enable relative path and dot names. f_chdir() and f_chdrive() are available.
/   2: f_getcwd() is available in addition to 1.
*/


#define FF_PATH_DEPTH	10
/*  This option defines maximum depth of directory in the exFAT volume. It is NOT
/   relevant to FAT/FAT32 volume.
/   For example, FF_PATH_DEPTH = 3 will able to follow a path "/dir1/dir2/dir3/file"
/   but a sub-directory in the dir3 will not able to be followed and set current
/   directory.
/   The size of filesystem object (FATFS) increases FF_PATH_DEPTH * 24 bytes.
/   When FF_FS_EXFAT == 0 or FF_FS_RPATH == 0, this option has no effect.
*/



/*---------------------------------------------------------------------------/
/ Drive/Volume Configurations
/---------------------------------------------------------------------------*/

#define FF_VOLUMES		1
/* Number of volumes (logical drives) to be used. (1-10) */


#define FF_STR_VOLUME_ID	0
#define FF_VOLUME_STRS		"RAM","NAND","CF","SD","SD2","USB","USB2","USB3"
/* FF_STR_VOLUME_ID switches support for volume ID in arbitrary strings.
/  When FF_STR_VOLUME_ID is set to 1 or 2, arbitrary strings can be used as drive
/  number in the path name. FF_VOLUME_STRS defines the volume ID strings for each
/  logical drive. Number of items must not be less than FF_VOLUMES. Valid
/  characters for the volume ID strings are A-Z, a-z and 0-9, however, they are
/  compared in case-insensitive. If FF_STR_VOLUME_ID >= 1 and FF_VOLUME_STRS is
/  not defined, a user defined volume string table is needed as:
/
/  const char* VolumeStr[FF_VOLUMES] = {"ram","flash","sd","usb",...
*/


#define FF_MULTI_PARTITION	0
/* This option switches support for multiple volumes on the physical drive.
/  By default (0), each logical drive number is bound to the same physical drive
/  number and only an FAT volume found on the physical drive will be mounted.
/  When this feature is enabled (1), each logical drive number can be bound to
/  arbitrary physical drive and partition listed in the VolToPart[]. Also f_fdisk()
/  will be available. */


#define FF_MIN_SS		512
#define FF_MAX_SS		512
/* This set of options configures the range of sector size to be supported. (512,
/  1024, 2048 or 4096) Always set both 512 for most systems, generic memory card and
/  harddisk, but a larger value may be required for on-board flash memory and some
/  type of optical media. When FF_MAX_SS is larger than FF_MIN_SS, FatFs is
/  configured for variable sector size mode and disk_ioctl() needs to implement
/  GET_SECTOR_SIZE command. */


#define FF_LBA64		0
/* This option switches support for 64-bit LBA. (0:Disable or 1:Enable)
/  To enable the 64-bit LBA, also exFAT needs to be enabled. (FF_FS_EXFAT == 1) */


#define FF_MIN_GPT		0x10000000
/* Minimum number of sectors to switch GPT as partitioning format in f_mkfs() and
/  f_fdisk(). 2^32 sectors maximum. This option has no effect when FF_LBA64 == 0. */


#define FF_USE_TRIM		0
/* This option switches support for ATA-TRIM. (0:Disable or 1:Enable)
/  To enable this feature, also CTRL_TRIM command should be implemented to
/  the disk_ioctl(). */



/*---------------------------------------------------------------------------/
/ System Configurations
/---------------------------------------------------------------------------*/

#define FF_FS_TINY		0
/* This option switches tiny buffer configuration. (0:Normal or 1:Tiny)
/  At the tiny configuration, size of file object (FIL) is reduced FF_MAX_SS bytes.
/  Instead of private sector buffer eliminated from the file object, common sector
/  buffer in the filesystem object (FATFS) is used for the file data transfer. */


#define FF_FS_EXFAT		0
/* This option switches support for exFAT filesystem. (0:Disable or 1:Enable)
/  To enable exFAT, also LFN needs to be enabled. (FF_USE_LFN >= 1)
/  Note that enabling exFAT discards ANSI C (C89) compatibility. */


#define FF_FS_NORTC		0
#define FF_NORTC_MON	1
#define FF_NORTC_MDAY	1
#define FF_NORTC_YEAR	2025
/* The option FF_FS_NORTC switches timestamp feature. If the system does not have
/  an RTC or valid timestamp is not needed, set FF_FS_NORTC = 1 to disable the
/  timestamp feature. Every object modified by FatFs will have a fixed timestamp
/  defined by FF_NORTC_MON, FF_NORTC_MDAY and FF_NORTC_YEAR in local time.
/  To enable timestamp function (FF_FS_NORTC = 0), get_fattime() need to be added
/  to the project to read current time form real-time clock. FF_NORTC_MON,
/  FF_NORTC_MDAY and FF_NORTC_YEAR have no effect.
/  These options have no effect in read-only configuration (FF_FS_READONLY = 1). */


#define FF_FS_CRTIME	0
/* This option enables(1)/disables(0) the timestamp of the file created. When
/  set 1, the file created time is available in FILINFO structure. */


#define FF_FS_NOFSINFO	0
/* If you need to know the correct free space on the FAT32 volume, set bit 0 of
/  this option, and f_getfree() on the first time after volume mount will force
/  a full FAT scan. Bit 1 controls the use of last allocated cluster number.
/
/  bit0=0: Use free cluster count in the FSINFO if available.
/  bit0=1: Do not trust free cluster count in the FSINFO.
/  bit1=0: Use last allocated cluster number in the FSINFO if available.
/  bit1=1: Do not trust last allocated cluster number in the FSINFO.
*/


#define FF_FS_LOCK		0
/* The option FF_FS_LOCK switches file lock function to control duplicated file open
/  and illegal operation to open objects. This option must be 0 when FF_FS_READONLY
/  is 1.
/
/  0:  Disable file lock function. To avoid volume corruption, application program
/      should avoid illegal open, remove and rename to the open objects.
/  >0: Enable file lock function. The value defines how many files/sub-directories
/      can be opened simultaneously under file lock control. Note that the file
/      lock control is independent of re-entrancy. */


#define FF_FS_REENTRANT	0
#define FF_FS_TIMEOUT	1000
/* The option FF_FS_REENTRANT switches the re-entrancy (thread safe) of the FatFs
/  module itself. Note that regardless of this option, file access to different
/  volume is always re-entrant and volume control functions, f_mount(), f_mkfs()
/  and f_fdisk(), are always not re-entrant. Only file/directory access to
/  the same volume is under control of this featuer.
/
/   0: Disable re-entrancy. FF_FS_TIMEOUT have no effect.
/   1: Enable re-entrancy. Also user provided synchronization handlers,
/      ff_mutex_create(), ff_mutex_delete(), ff_mutex_take() and ff_mutex_give(),
/      must be added to the project. Samples are available in ffsystem.c.
/
/  The FF_FS_TIMEOUT defines timeout period in unit of O/S time tick.
*/



/*--- End of configuration options ---*/
