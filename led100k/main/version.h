#ifndef VERSION_H
#define VERSION_H

#define VERSION_HARDWARE_ID			0x2200  // hardware id sirius_r2
#define VERSION_HARDWARE_REVISION	0x0203

#define VERSION_MAJOR				1
#define VERSION_MINOR				19

#if (VERSION_MINOR < 10)
#define VERSION_MINOR_STR		"0" STR(VERSION_MINOR)
#else
#define VERSION_MINOR_STR		STR(VERSION_MINOR)
#endif
#define VERSION_MAJOR_STR		STR(VERSION_MAJOR)

#define VERSION_IS_DEBUG		(VERSION_MINOR % 2)

#ifdef VCS_REVISION
#define VCS_REVISION_STR        STR(VCS_REVISION)
#else
#define VCS_REVISION_STR        "n/a"
#endif

#ifdef VCS_PATH
#define VCS_PATH_STR            STR(VCS_PATH)
#else
#define VCS_PATH_STR            "n/a"
#endif

typedef enum
{
    HW_REV_0, HW_REV_2_3, HW_REV_2_4,
} HW_REV_T;

typedef struct device_info_s
{
    uint16_t hardware_id;
    uint16_t hardware_revision;
    uint8_t version_major;
    uint8_t version_minor;
    uint8_t reserved[9];
} DEVICE_INFO_T;

HW_REV_T VERSION_GetHWRev(void);
void VERSION_Init(void);

#endif
