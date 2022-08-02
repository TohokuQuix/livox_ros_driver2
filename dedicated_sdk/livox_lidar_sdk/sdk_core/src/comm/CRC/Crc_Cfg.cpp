

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "Crc.h"

/*
**********************************************************************************************************************
* Type definitions
**********************************************************************************************************************
*/

const uint8_t  CRC_8_Tbl[CRC_TABLESIZE] =
{
    /*  0:*/ 0x00u, 0x1du, 0x3au, 0x27u, 0x74u, 0x69u, 0x4eu, 0x53u,
    /*  8:*/ 0xe8u, 0xf5u, 0xd2u, 0xcfu, 0x9cu, 0x81u, 0xa6u, 0xbbu,
    /* 16:*/ 0xcdu, 0xd0u, 0xf7u, 0xeau, 0xb9u, 0xa4u, 0x83u, 0x9eu,
    /* 24:*/ 0x25u, 0x38u, 0x1fu, 0x02u, 0x51u, 0x4cu, 0x6bu, 0x76u,
    /* 32:*/ 0x87u, 0x9au, 0xbdu, 0xa0u, 0xf3u, 0xeeu, 0xc9u, 0xd4u,
    /* 40:*/ 0x6fu, 0x72u, 0x55u, 0x48u, 0x1bu, 0x06u, 0x21u, 0x3cu,
    /* 48:*/ 0x4au, 0x57u, 0x70u, 0x6du, 0x3eu, 0x23u, 0x04u, 0x19u,
    /* 56:*/ 0xa2u, 0xbfu, 0x98u, 0x85u, 0xd6u, 0xcbu, 0xecu, 0xf1u,
    /* 64:*/ 0x13u, 0x0eu, 0x29u, 0x34u, 0x67u, 0x7au, 0x5du, 0x40u,
    /* 72:*/ 0xfbu, 0xe6u, 0xc1u, 0xdcu, 0x8fu, 0x92u, 0xb5u, 0xa8u,
    /* 80:*/ 0xdeu, 0xc3u, 0xe4u, 0xf9u, 0xaau, 0xb7u, 0x90u, 0x8du,
    /* 88:*/ 0x36u, 0x2bu, 0x0cu, 0x11u, 0x42u, 0x5fu, 0x78u, 0x65u,
    /* 96:*/ 0x94u, 0x89u, 0xaeu, 0xb3u, 0xe0u, 0xfdu, 0xdau, 0xc7u,
    /*104:*/ 0x7cu, 0x61u, 0x46u, 0x5bu, 0x08u, 0x15u, 0x32u, 0x2fu,
    /*112:*/ 0x59u, 0x44u, 0x63u, 0x7eu, 0x2du, 0x30u, 0x17u, 0x0au,
    /*120:*/ 0xb1u, 0xacu, 0x8bu, 0x96u, 0xc5u, 0xd8u, 0xffu, 0xe2u,
    /*128:*/ 0x26u, 0x3bu, 0x1cu, 0x01u, 0x52u, 0x4fu, 0x68u, 0x75u,
    /*136:*/ 0xceu, 0xd3u, 0xf4u, 0xe9u, 0xbau, 0xa7u, 0x80u, 0x9du,
    /*144:*/ 0xebu, 0xf6u, 0xd1u, 0xccu, 0x9fu, 0x82u, 0xa5u, 0xb8u,
    /*152:*/ 0x03u, 0x1eu, 0x39u, 0x24u, 0x77u, 0x6au, 0x4du, 0x50u,
    /*160:*/ 0xa1u, 0xbcu, 0x9bu, 0x86u, 0xd5u, 0xc8u, 0xefu, 0xf2u,
    /*168:*/ 0x49u, 0x54u, 0x73u, 0x6eu, 0x3du, 0x20u, 0x07u, 0x1au,
    /*176:*/ 0x6cu, 0x71u, 0x56u, 0x4bu, 0x18u, 0x05u, 0x22u, 0x3fu,
    /*184:*/ 0x84u, 0x99u, 0xbeu, 0xa3u, 0xf0u, 0xedu, 0xcau, 0xd7u,
    /*192:*/ 0x35u, 0x28u, 0x0fu, 0x12u, 0x41u, 0x5cu, 0x7bu, 0x66u,
    /*200:*/ 0xddu, 0xc0u, 0xe7u, 0xfau, 0xa9u, 0xb4u, 0x93u, 0x8eu,
    /*208:*/ 0xf8u, 0xe5u, 0xc2u, 0xdfu, 0x8cu, 0x91u, 0xb6u, 0xabu,
    /*216:*/ 0x10u, 0x0du, 0x2au, 0x37u, 0x64u, 0x79u, 0x5eu, 0x43u,
    /*224:*/ 0xb2u, 0xafu, 0x88u, 0x95u, 0xc6u, 0xdbu, 0xfcu, 0xe1u,
    /*232:*/ 0x5au, 0x47u, 0x60u, 0x7du, 0x2eu, 0x33u, 0x14u, 0x09u,
    /*240:*/ 0x7fu, 0x62u, 0x45u, 0x58u, 0x0bu, 0x16u, 0x31u, 0x2cu,
    /*248:*/ 0x97u, 0x8au, 0xadu, 0xb0u, 0xe3u, 0xfeu, 0xd9u, 0xc4u
};

const uint8_t  CRC_8H2F_Tbl[CRC_TABLESIZE] =
{
        /*    0: */    0x0u,     0x2fu,    0x5eu,    0x71u,    0xbcu,    0x93u,    0xe2u,    0xcdu,
        /*    8: */    0x57u,    0x78u,    0x9u,     0x26u,    0xebu,    0xc4u,    0xb5u,    0x9au,
        /*   16: */    0xaeu,    0x81u,    0xf0u,    0xdfu,    0x12u,    0x3du,    0x4cu,    0x63u,
        /*   24: */    0xf9u,    0xd6u,    0xa7u,    0x88u,    0x45u,    0x6au,    0x1bu,    0x34u,
        /*   32: */    0x73u,    0x5cu,    0x2du,    0x2u,     0xcfu,    0xe0u,    0x91u,    0xbeu,
        /*   40: */    0x24u,    0xbu,     0x7au,    0x55u,    0x98u,    0xb7u,    0xc6u,    0xe9u,
        /*   48: */    0xddu,    0xf2u,    0x83u,    0xacu,    0x61u,    0x4eu,    0x3fu,    0x10u,
        /*   56: */    0x8au,    0xa5u,    0xd4u,    0xfbu,    0x36u,    0x19u,    0x68u,    0x47u,
        /*   64: */    0xe6u,    0xc9u,    0xb8u,    0x97u,    0x5au,    0x75u,    0x4u,     0x2bu,
        /*   72: */    0xb1u,    0x9eu,    0xefu,    0xc0u,    0xdu,     0x22u,    0x53u,    0x7cu,
        /*   80: */    0x48u,    0x67u,    0x16u,    0x39u,    0xf4u,    0xdbu,    0xaau,    0x85u,
        /*   88: */    0x1fu,    0x30u,    0x41u,    0x6eu,    0xa3u,    0x8cu,    0xfdu,    0xd2u,
        /*   96: */    0x95u,    0xbau,    0xcbu,    0xe4u,    0x29u,    0x6u,     0x77u,    0x58u,
        /*  104: */    0xc2u,    0xedu,    0x9cu,    0xb3u,    0x7eu,    0x51u,    0x20u,    0xfu,
        /*  112: */    0x3bu,    0x14u,    0x65u,    0x4au,    0x87u,    0xa8u,    0xd9u,    0xf6u,
        /*  120: */    0x6cu,    0x43u,    0x32u,    0x1du,    0xd0u,    0xffu,    0x8eu,    0xa1u,
        /*  128: */    0xe3u,    0xccu,    0xbdu,    0x92u,    0x5fu,    0x70u,    0x1u,     0x2eu,
        /*  136: */    0xb4u,    0x9bu,    0xeau,    0xc5u,    0x8u,     0x27u,    0x56u,    0x79u,
        /*  144: */    0x4du,    0x62u,    0x13u,    0x3cu,    0xf1u,    0xdeu,    0xafu,    0x80u,
        /*  152: */    0x1au,    0x35u,    0x44u,    0x6bu,    0xa6u,    0x89u,    0xf8u,    0xd7u,
        /*  160: */    0x90u,    0xbfu,    0xceu,    0xe1u,    0x2cu,    0x3u,     0x72u,    0x5du,
        /*  168: */    0xc7u,    0xe8u,    0x99u,    0xb6u,    0x7bu,    0x54u,    0x25u,    0xau,
        /*  176: */    0x3eu,    0x11u,    0x60u,    0x4fu,    0x82u,    0xadu,    0xdcu,    0xf3u,
        /*  184: */    0x69u,    0x46u,    0x37u,    0x18u,    0xd5u,    0xfau,    0x8bu,    0xa4u,
        /*  192: */    0x5u,     0x2au,    0x5bu,    0x74u,    0xb9u,    0x96u,    0xe7u,    0xc8u,
        /*  200: */    0x52u,    0x7du,    0xcu,     0x23u,    0xeeu,    0xc1u,    0xb0u,    0x9fu,
        /*  208: */    0xabu,    0x84u,    0xf5u,    0xdau,    0x17u,    0x38u,    0x49u,    0x66u,
        /*  216: */    0xfcu,    0xd3u,    0xa2u,    0x8du,    0x40u,    0x6fu,    0x1eu,    0x31u,
        /*  224: */    0x76u,    0x59u,    0x28u,    0x7u,     0xcau,    0xe5u,    0x94u,    0xbbu,
        /*  232: */    0x21u,    0xeu,     0x7fu,    0x50u,    0x9du,    0xb2u,    0xc3u,    0xecu,
        /*  240: */    0xd8u,    0xf7u,    0x86u,    0xa9u,    0x64u,    0x4bu,    0x3au,    0x15u,
        /*  248: */    0x8fu,    0xa0u,    0xd1u,    0xfeu,    0x33u,    0x1cu,    0x6du,    0x42u
};

const uint16_t  CRC_16_Tbl[CRC_TABLESIZE] =
{
    /*  0:*/ 0x0000u, 0x1021u, 0x2042u, 0x3063u, 0x4084u, 0x50a5u, 0x60c6u, 0x70e7u,
    /*  8:*/ 0x8108u, 0x9129u, 0xa14au, 0xb16bu, 0xc18cu, 0xd1adu, 0xe1ceu, 0xf1efu,
    /* 16:*/ 0x1231u, 0x0210u, 0x3273u, 0x2252u, 0x52b5u, 0x4294u, 0x72f7u, 0x62d6u,
    /* 24:*/ 0x9339u, 0x8318u, 0xb37bu, 0xa35au, 0xd3bdu, 0xc39cu, 0xf3ffu, 0xe3deu,
    /* 32:*/ 0x2462u, 0x3443u, 0x0420u, 0x1401u, 0x64e6u, 0x74c7u, 0x44a4u, 0x5485u,
    /* 40:*/ 0xa56au, 0xb54bu, 0x8528u, 0x9509u, 0xe5eeu, 0xf5cfu, 0xc5acu, 0xd58du,
    /* 48:*/ 0x3653u, 0x2672u, 0x1611u, 0x0630u, 0x76d7u, 0x66f6u, 0x5695u, 0x46b4u,
    /* 56:*/ 0xb75bu, 0xa77au, 0x9719u, 0x8738u, 0xf7dfu, 0xe7feu, 0xd79du, 0xc7bcu,
    /* 64:*/ 0x48c4u, 0x58e5u, 0x6886u, 0x78a7u, 0x0840u, 0x1861u, 0x2802u, 0x3823u,
    /* 72:*/ 0xc9ccu, 0xd9edu, 0xe98eu, 0xf9afu, 0x8948u, 0x9969u, 0xa90au, 0xb92bu,
    /* 80:*/ 0x5af5u, 0x4ad4u, 0x7ab7u, 0x6a96u, 0x1a71u, 0x0a50u, 0x3a33u, 0x2a12u,
    /* 88:*/ 0xdbfdu, 0xcbdcu, 0xfbbfu, 0xeb9eu, 0x9b79u, 0x8b58u, 0xbb3bu, 0xab1au,
    /* 96:*/ 0x6ca6u, 0x7c87u, 0x4ce4u, 0x5cc5u, 0x2c22u, 0x3c03u, 0x0c60u, 0x1c41u,
    /*104:*/ 0xedaeu, 0xfd8fu, 0xcdecu, 0xddcdu, 0xad2au, 0xbd0bu, 0x8d68u, 0x9d49u,
    /*112:*/ 0x7e97u, 0x6eb6u, 0x5ed5u, 0x4ef4u, 0x3e13u, 0x2e32u, 0x1e51u, 0x0e70u,
    /*120:*/ 0xff9fu, 0xefbeu, 0xdfddu, 0xcffcu, 0xbf1bu, 0xaf3au, 0x9f59u, 0x8f78u,
    /*128:*/ 0x9188u, 0x81a9u, 0xb1cau, 0xa1ebu, 0xd10cu, 0xc12du, 0xf14eu, 0xe16fu,
    /*136:*/ 0x1080u, 0x00a1u, 0x30c2u, 0x20e3u, 0x5004u, 0x4025u, 0x7046u, 0x6067u,
    /*144:*/ 0x83b9u, 0x9398u, 0xa3fbu, 0xb3dau, 0xc33du, 0xd31cu, 0xe37fu, 0xf35eu,
    /*152:*/ 0x02b1u, 0x1290u, 0x22f3u, 0x32d2u, 0x4235u, 0x5214u, 0x6277u, 0x7256u,
    /*160:*/ 0xb5eau, 0xa5cbu, 0x95a8u, 0x8589u, 0xf56eu, 0xe54fu, 0xd52cu, 0xc50du,
    /*168:*/ 0x34e2u, 0x24c3u, 0x14a0u, 0x0481u, 0x7466u, 0x6447u, 0x5424u, 0x4405u,
    /*176:*/ 0xa7dbu, 0xb7fau, 0x8799u, 0x97b8u, 0xe75fu, 0xf77eu, 0xc71du, 0xd73cu,
    /*184:*/ 0x26d3u, 0x36f2u, 0x0691u, 0x16b0u, 0x6657u, 0x7676u, 0x4615u, 0x5634u,
    /*192:*/ 0xd94cu, 0xc96du, 0xf90eu, 0xe92fu, 0x99c8u, 0x89e9u, 0xb98au, 0xa9abu,
    /*200:*/ 0x5844u, 0x4865u, 0x7806u, 0x6827u, 0x18c0u, 0x08e1u, 0x3882u, 0x28a3u,
    /*208:*/ 0xcb7du, 0xdb5cu, 0xeb3fu, 0xfb1eu, 0x8bf9u, 0x9bd8u, 0xabbbu, 0xbb9au,
    /*216:*/ 0x4a75u, 0x5a54u, 0x6a37u, 0x7a16u, 0x0af1u, 0x1ad0u, 0x2ab3u, 0x3a92u,
    /*224:*/ 0xfd2eu, 0xed0fu, 0xdd6cu, 0xcd4du, 0xbdaau, 0xad8bu, 0x9de8u, 0x8dc9u,
    /*232:*/ 0x7c26u, 0x6c07u, 0x5c64u, 0x4c45u, 0x3ca2u, 0x2c83u, 0x1ce0u, 0x0cc1u,
    /*240:*/ 0xef1fu, 0xff3eu, 0xcf5du, 0xdf7cu, 0xaf9bu, 0xbfbau, 0x8fd9u, 0x9ff8u,
    /*248:*/ 0x6e17u, 0x7e36u, 0x4e55u, 0x5e74u, 0x2e93u, 0x3eb2u, 0x0ed1u, 0x1ef0u
};

const uint32_t  CRC_32_REV_Tbl[CRC_TABLESIZE] =
{
    /*  0:*/ 0x00000000uL, 0x77073096uL, 0xee0e612cuL, 0x990951bauL,
    /*  4:*/ 0x076dc419uL, 0x706af48fuL, 0xe963a535uL, 0x9e6495a3uL,
    /*  8:*/ 0x0edb8832uL, 0x79dcb8a4uL, 0xe0d5e91euL, 0x97d2d988uL,
    /*  8:*/ 0x09b64c2buL, 0x7eb17cbduL, 0xe7b82d07uL, 0x90bf1d91uL,
    /* 16:*/ 0x1db71064uL, 0x6ab020f2uL, 0xf3b97148uL, 0x84be41deuL,
    /* 20:*/ 0x1adad47duL, 0x6ddde4ebuL, 0xf4d4b551uL, 0x83d385c7uL,
    /* 24:*/ 0x136c9856uL, 0x646ba8c0uL, 0xfd62f97auL, 0x8a65c9ecuL,
    /* 28:*/ 0x14015c4fuL, 0x63066cd9uL, 0xfa0f3d63uL, 0x8d080df5uL,
    /* 32:*/ 0x3b6e20c8uL, 0x4c69105euL, 0xd56041e4uL, 0xa2677172uL,
    /* 36:*/ 0x3c03e4d1uL, 0x4b04d447uL, 0xd20d85fduL, 0xa50ab56buL,
    /* 40:*/ 0x35b5a8fauL, 0x42b2986cuL, 0xdbbbc9d6uL, 0xacbcf940uL,
    /* 44:*/ 0x32d86ce3uL, 0x45df5c75uL, 0xdcd60dcfuL, 0xabd13d59uL,
    /* 48:*/ 0x26d930acuL, 0x51de003auL, 0xc8d75180uL, 0xbfd06116uL,
    /* 52:*/ 0x21b4f4b5uL, 0x56b3c423uL, 0xcfba9599uL, 0xb8bda50fuL,
    /* 56:*/ 0x2802b89euL, 0x5f058808uL, 0xc60cd9b2uL, 0xb10be924uL,
    /* 60:*/ 0x2f6f7c87uL, 0x58684c11uL, 0xc1611dabuL, 0xb6662d3duL,
    /* 64:*/ 0x76dc4190uL, 0x01db7106uL, 0x98d220bcuL, 0xefd5102auL,
    /* 68:*/ 0x71b18589uL, 0x06b6b51fuL, 0x9fbfe4a5uL, 0xe8b8d433uL,
    /* 72:*/ 0x7807c9a2uL, 0x0f00f934uL, 0x9609a88euL, 0xe10e9818uL,
    /* 76:*/ 0x7f6a0dbbuL, 0x086d3d2duL, 0x91646c97uL, 0xe6635c01uL,
    /* 80:*/ 0x6b6b51f4uL, 0x1c6c6162uL, 0x856530d8uL, 0xf262004euL,
    /* 84:*/ 0x6c0695eduL, 0x1b01a57buL, 0x8208f4c1uL, 0xf50fc457uL,
    /* 88:*/ 0x65b0d9c6uL, 0x12b7e950uL, 0x8bbeb8eauL, 0xfcb9887cuL,
    /* 92:*/ 0x62dd1ddfuL, 0x15da2d49uL, 0x8cd37cf3uL, 0xfbd44c65uL,
    /* 96:*/ 0x4db26158uL, 0x3ab551ceuL, 0xa3bc0074uL, 0xd4bb30e2uL,
    /*100:*/ 0x4adfa541uL, 0x3dd895d7uL, 0xa4d1c46duL, 0xd3d6f4fbuL,
    /*104:*/ 0x4369e96auL, 0x346ed9fcuL, 0xad678846uL, 0xda60b8d0uL,
    /*108:*/ 0x44042d73uL, 0x33031de5uL, 0xaa0a4c5fuL, 0xdd0d7cc9uL,
    /*112:*/ 0x5005713cuL, 0x270241aauL, 0xbe0b1010uL, 0xc90c2086uL,
    /*116:*/ 0x5768b525uL, 0x206f85b3uL, 0xb966d409uL, 0xce61e49fuL,
    /*120:*/ 0x5edef90euL, 0x29d9c998uL, 0xb0d09822uL, 0xc7d7a8b4uL,
    /*124:*/ 0x59b33d17uL, 0x2eb40d81uL, 0xb7bd5c3buL, 0xc0ba6caduL,
    /*128:*/ 0xedb88320uL, 0x9abfb3b6uL, 0x03b6e20cuL, 0x74b1d29auL,
    /*132:*/ 0xead54739uL, 0x9dd277afuL, 0x04db2615uL, 0x73dc1683uL,
    /*136:*/ 0xe3630b12uL, 0x94643b84uL, 0x0d6d6a3euL, 0x7a6a5aa8uL,
    /*140:*/ 0xe40ecf0buL, 0x9309ff9duL, 0x0a00ae27uL, 0x7d079eb1uL,
    /*144:*/ 0xf00f9344uL, 0x8708a3d2uL, 0x1e01f268uL, 0x6906c2feuL,
    /*148:*/ 0xf762575duL, 0x806567cbuL, 0x196c3671uL, 0x6e6b06e7uL,
    /*152:*/ 0xfed41b76uL, 0x89d32be0uL, 0x10da7a5auL, 0x67dd4accuL,
    /*156:*/ 0xf9b9df6fuL, 0x8ebeeff9uL, 0x17b7be43uL, 0x60b08ed5uL,
    /*160:*/ 0xd6d6a3e8uL, 0xa1d1937euL, 0x38d8c2c4uL, 0x4fdff252uL,
    /*164:*/ 0xd1bb67f1uL, 0xa6bc5767uL, 0x3fb506dduL, 0x48b2364buL,
    /*168:*/ 0xd80d2bdauL, 0xaf0a1b4cuL, 0x36034af6uL, 0x41047a60uL,
    /*172:*/ 0xdf60efc3uL, 0xa867df55uL, 0x316e8eefuL, 0x4669be79uL,
    /*176:*/ 0xcb61b38cuL, 0xbc66831auL, 0x256fd2a0uL, 0x5268e236uL,
    /*180:*/ 0xcc0c7795uL, 0xbb0b4703uL, 0x220216b9uL, 0x5505262fuL,
    /*184:*/ 0xc5ba3bbeuL, 0xb2bd0b28uL, 0x2bb45a92uL, 0x5cb36a04uL,
    /*188:*/ 0xc2d7ffa7uL, 0xb5d0cf31uL, 0x2cd99e8buL, 0x5bdeae1duL,
    /*192:*/ 0x9b64c2b0uL, 0xec63f226uL, 0x756aa39cuL, 0x026d930auL,
    /*196:*/ 0x9c0906a9uL, 0xeb0e363fuL, 0x72076785uL, 0x05005713uL,
    /*200:*/ 0x95bf4a82uL, 0xe2b87a14uL, 0x7bb12baeuL, 0x0cb61b38uL,
    /*204:*/ 0x92d28e9buL, 0xe5d5be0duL, 0x7cdcefb7uL, 0x0bdbdf21uL,
    /*208:*/ 0x86d3d2d4uL, 0xf1d4e242uL, 0x68ddb3f8uL, 0x1fda836euL,
    /*212:*/ 0x81be16cduL, 0xf6b9265buL, 0x6fb077e1uL, 0x18b74777uL,
    /*216:*/ 0x88085ae6uL, 0xff0f6a70uL, 0x66063bcauL, 0x11010b5cuL,
    /*220:*/ 0x8f659effuL, 0xf862ae69uL, 0x616bffd3uL, 0x166ccf45uL,
    /*224:*/ 0xa00ae278uL, 0xd70dd2eeuL, 0x4e048354uL, 0x3903b3c2uL,
    /*228:*/ 0xa7672661uL, 0xd06016f7uL, 0x4969474duL, 0x3e6e77dbuL,
    /*232:*/ 0xaed16a4auL, 0xd9d65adcuL, 0x40df0b66uL, 0x37d83bf0uL,
    /*236:*/ 0xa9bcae53uL, 0xdebb9ec5uL, 0x47b2cf7fuL, 0x30b5ffe9uL,
    /*240:*/ 0xbdbdf21cuL, 0xcabac28auL, 0x53b39330uL, 0x24b4a3a6uL,
    /*244:*/ 0xbad03605uL, 0xcdd70693uL, 0x54de5729uL, 0x23d967bfuL,
    /*248:*/ 0xb3667a2euL, 0xc4614ab8uL, 0x5d681b02uL, 0x2a6f2b94uL,
    /*252:*/ 0xb40bbe37uL, 0xc30c8ea1uL, 0x5a05df1buL, 0x2d02ef8duL
};

const uint32_t  CRC_32P4_REV_Tbl[CRC_TABLESIZE] =
{
    /*  0:*/ 0x00000000uL, 0x30850FF5uL, 0x610A1FEAuL, 0x518F101FuL,
    /*  4:*/ 0xC2143FD4uL, 0xF2913021uL, 0xA31E203EuL, 0x939B2FCBuL,
    /*  8:*/ 0x159615F7uL, 0x25131A02uL, 0x749C0A1DuL, 0x441905E8uL,
    /*  8:*/ 0xD7822A23uL, 0xE70725D6uL, 0xB68835C9uL, 0x860D3A3CuL,
    /* 16:*/ 0x2B2C2BEEuL, 0x1BA9241BuL, 0x4A263404uL, 0x7AA33BF1uL,
    /* 20:*/ 0xE938143AuL, 0xD9BD1BCFuL, 0x88320BD0uL, 0xB8B70425uL,
    /* 24:*/ 0x3EBA3E19uL, 0x0E3F31ECuL, 0x5FB021F3uL, 0x6F352E06uL,
    /* 28:*/ 0xFCAE01CDuL, 0xCC2B0E38uL, 0x9DA41E27uL, 0xAD2111D2uL,
    /* 32:*/ 0x565857DCuL, 0x66DD5829uL, 0x37524836uL, 0x07D747C3uL,
    /* 36:*/ 0x944C6808uL, 0xA4C967FDuL, 0xF54677E2uL, 0xC5C37817uL,
    /* 40:*/ 0x43CE422BuL, 0x734B4DDEuL, 0x22C45DC1uL, 0x12415234uL,
    /* 44:*/ 0x81DA7DFFuL, 0xB15F720AuL, 0xE0D06215uL, 0xD0556DE0uL,
    /* 48:*/ 0x7D747C32uL, 0x4DF173C7uL, 0x1C7E63D8uL, 0x2CFB6C2DuL,
    /* 52:*/ 0xBF6043E6uL, 0x8FE54C13uL, 0xDE6A5C0CuL, 0xEEEF53F9uL,
    /* 56:*/ 0x68E269C5uL, 0x58676630uL, 0x09E8762FuL, 0x396D79DAuL,
    /* 60:*/ 0xAAF65611uL, 0x9A7359E4uL, 0xCBFC49FBuL, 0xFB79460EuL,
    /* 64:*/ 0xACB0AFB8uL, 0x9C35A04DuL, 0xCDBAB052uL, 0xFD3FBFA7uL,
    /* 68:*/ 0x6EA4906CuL, 0x5E219F99uL, 0x0FAE8F86uL, 0x3F2B8073uL,
    /* 72:*/ 0xB926BA4FuL, 0x89A3B5BAuL, 0xD82CA5A5uL, 0xE8A9AA50uL,
    /* 76:*/ 0x7B32859BuL, 0x4BB78A6EuL, 0x1A389A71uL, 0x2ABD9584uL,
    /* 80:*/ 0x879C8456uL, 0xB7198BA3uL, 0xE6969BBCuL, 0xD6139449uL,
    /* 84:*/ 0x4588BB82uL, 0x750DB477uL, 0x2482A468uL, 0x1407AB9DuL,
    /* 88:*/ 0x920A91A1uL, 0xA28F9E54uL, 0xF3008E4BuL, 0xC38581BEuL,
    /* 92:*/ 0x501EAE75uL, 0x609BA180uL, 0x3114B19FuL, 0x0191BE6AuL,
    /* 96:*/ 0xFAE8F864uL, 0xCA6DF791uL, 0x9BE2E78EuL, 0xAB67E87BuL,
    /*100:*/ 0x38FCC7B0uL, 0x0879C845uL, 0x59F6D85AuL, 0x6973D7AFuL,
    /*104:*/ 0xEF7EED93uL, 0xDFFBE266uL, 0x8E74F279uL, 0xBEF1FD8CuL,
    /*108:*/ 0x2D6AD247uL, 0x1DEFDDB2uL, 0x4C60CDADuL, 0x7CE5C258uL,
    /*112:*/ 0xD1C4D38AuL, 0xE141DC7FuL, 0xB0CECC60uL, 0x804BC395uL,
    /*116:*/ 0x13D0EC5EuL, 0x2355E3ABuL, 0x72DAF3B4uL, 0x425FFC41uL,
    /*120:*/ 0xC452C67DuL, 0xF4D7C988uL, 0xA558D997uL, 0x95DDD662uL,
    /*124:*/ 0x0646F9A9uL, 0x36C3F65CuL, 0x674CE643uL, 0x57C9E9B6uL,
    /*128:*/ 0xC8DF352FuL, 0xF85A3ADAuL, 0xA9D52AC5uL, 0x99502530uL,
    /*132:*/ 0x0ACB0AFBuL, 0x3A4E050EuL, 0x6BC11511uL, 0x5B441AE4uL,
    /*136:*/ 0xDD4920D8uL, 0xEDCC2F2DuL, 0xBC433F32uL, 0x8CC630C7uL,
    /*140:*/ 0x1F5D1F0CuL, 0x2FD810F9uL, 0x7E5700E6uL, 0x4ED20F13uL,
    /*144:*/ 0xE3F31EC1uL, 0xD3761134uL, 0x82F9012BuL, 0xB27C0EDEuL,
    /*148:*/ 0x21E72115uL, 0x11622EE0uL, 0x40ED3EFFuL, 0x7068310AuL,
    /*152:*/ 0xF6650B36uL, 0xC6E004C3uL, 0x976F14DCuL, 0xA7EA1B29uL,
    /*156:*/ 0x347134E2uL, 0x04F43B17uL, 0x557B2B08uL, 0x65FE24FDuL,
    /*160:*/ 0x9E8762F3uL, 0xAE026D06uL, 0xFF8D7D19uL, 0xCF0872ECuL,
    /*164:*/ 0x5C935D27uL, 0x6C1652D2uL, 0x3D9942CDuL, 0x0D1C4D38uL,
    /*168:*/ 0x8B117704uL, 0xBB9478F1uL, 0xEA1B68EEuL, 0xDA9E671BuL,
    /*172:*/ 0x490548D0uL, 0x79804725uL, 0x280F573AuL, 0x188A58CFuL,
    /*176:*/ 0xB5AB491DuL, 0x852E46E8uL, 0xD4A156F7uL, 0xE4245902uL,
    /*180:*/ 0x77BF76C9uL, 0x473A793CuL, 0x16B56923uL, 0x263066D6uL,
    /*184:*/ 0xA03D5CEAuL, 0x90B8531FuL, 0xC1374300uL, 0xF1B24CF5uL,
    /*188:*/ 0x6229633EuL, 0x52AC6CCBuL, 0x03237CD4uL, 0x33A67321uL,
    /*192:*/ 0x646F9A97uL, 0x54EA9562uL, 0x0565857DuL, 0x35E08A88uL,
    /*196:*/ 0xA67BA543uL, 0x96FEAAB6uL, 0xC771BAA9uL, 0xF7F4B55CuL,
    /*200:*/ 0x71F98F60uL, 0x417C8095uL, 0x10F3908AuL, 0x20769F7FuL,
    /*204:*/ 0xB3EDB0B4uL, 0x8368BF41uL, 0xD2E7AF5EuL, 0xE262A0ABuL,
    /*208:*/ 0x4F43B179uL, 0x7FC6BE8CuL, 0x2E49AE93uL, 0x1ECCA166uL,
    /*212:*/ 0x8D578EADuL, 0xBDD28158uL, 0xEC5D9147uL, 0xDCD89EB2uL,
    /*216:*/ 0x5AD5A48EuL, 0x6A50AB7BuL, 0x3BDFBB64uL, 0x0B5AB491uL,
    /*220:*/ 0x98C19B5AuL, 0xA84494AFuL, 0xF9CB84B0uL, 0xC94E8B45uL,
    /*224:*/ 0x3237CD4BuL, 0x02B2C2BEuL, 0x533DD2A1uL, 0x63B8DD54uL,
    /*228:*/ 0xF023F29FuL, 0xC0A6FD6AuL, 0x9129ED75uL, 0xA1ACE280uL,
    /*232:*/ 0x27A1D8BCuL, 0x1724D749uL, 0x46ABC756uL, 0x762EC8A3uL,
    /*236:*/ 0xE5B5E768uL, 0xD530E89DuL, 0x84BFF882uL, 0xB43AF777uL,
    /*240:*/ 0x191BE6A5uL, 0x299EE950uL, 0x7811F94FuL, 0x4894F6BAuL,
    /*244:*/ 0xDB0FD971uL, 0xEB8AD684uL, 0xBA05C69BuL, 0x8A80C96EuL,
    /*248:*/ 0x0C8DF352uL, 0x3C08FCA7uL, 0x6D87ECB8uL, 0x5D02E34DuL,
    /*252:*/ 0xCE99CC86uL, 0xFE1CC373uL, 0xAF93D36CuL, 0x9F16DC99uL
};


const uint64_t CRC_64_REV_Tbl[CRC_TABLESIZE] =
{
    /*  0:*/ 0x0000000000000000ULL, 0xb32e4cbe03a75f6fULL, 0xf4843657a840a05bULL, 0x47aa7ae9abe7ff34ULL,
    /*  4:*/ 0x7bd0c384ff8f5e33ULL, 0xc8fe8f3afc28015cULL, 0x8f54f5d357cffe68ULL, 0x3c7ab96d5468a107ULL,
    /*  8:*/ 0xf7a18709ff1ebc66ULL, 0x448fcbb7fcb9e309ULL, 0x0325b15e575e1c3dULL, 0xb00bfde054f94352ULL,
    /* 12:*/ 0x8c71448d0091e255ULL, 0x3f5f08330336bd3aULL, 0x78f572daa8d1420eULL, 0xcbdb3e64ab761d61ULL,
    /* 16:*/ 0x7d9ba13851336649ULL, 0xceb5ed8652943926ULL, 0x891f976ff973c612ULL, 0x3a31dbd1fad4997dULL,
    /* 20:*/ 0x064b62bcaebc387aULL, 0xb5652e02ad1b6715ULL, 0xf2cf54eb06fc9821ULL, 0x41e11855055bc74eULL,
    /* 24:*/ 0x8a3a2631ae2dda2fULL, 0x39146a8fad8a8540ULL, 0x7ebe1066066d7a74ULL, 0xcd905cd805ca251bULL,
    /* 28:*/ 0xf1eae5b551a2841cULL, 0x42c4a90b5205db73ULL, 0x056ed3e2f9e22447ULL, 0xb6409f5cfa457b28ULL,
    /* 32:*/ 0xfb374270a266cc92ULL, 0x48190ecea1c193fdULL, 0x0fb374270a266cc9ULL, 0xbc9d3899098133a6ULL,
    /* 36:*/ 0x80e781f45de992a1ULL, 0x33c9cd4a5e4ecdceULL, 0x7463b7a3f5a932faULL, 0xc74dfb1df60e6d95ULL,
    /* 40:*/ 0x0c96c5795d7870f4ULL, 0xbfb889c75edf2f9bULL, 0xf812f32ef538d0afULL, 0x4b3cbf90f69f8fc0ULL,
    /* 44:*/ 0x774606fda2f72ec7ULL, 0xc4684a43a15071a8ULL, 0x83c230aa0ab78e9cULL, 0x30ec7c140910d1f3ULL,
    /* 48:*/ 0x86ace348f355aadbULL, 0x3582aff6f0f2f5b4ULL, 0x7228d51f5b150a80ULL, 0xc10699a158b255efULL,
    /* 52:*/ 0xfd7c20cc0cdaf4e8ULL, 0x4e526c720f7dab87ULL, 0x09f8169ba49a54b3ULL, 0xbad65a25a73d0bdcULL,
    /* 56:*/ 0x710d64410c4b16bdULL, 0xc22328ff0fec49d2ULL, 0x85895216a40bb6e6ULL, 0x36a71ea8a7ace989ULL,
    /* 60:*/ 0x0adda7c5f3c4488eULL, 0xb9f3eb7bf06317e1ULL, 0xfe5991925b84e8d5ULL, 0x4d77dd2c5823b7baULL,
    /* 64:*/ 0x64b62bcaebc387a1ULL, 0xd7986774e864d8ceULL, 0x90321d9d438327faULL, 0x231c512340247895ULL,
    /* 68:*/ 0x1f66e84e144cd992ULL, 0xac48a4f017eb86fdULL, 0xebe2de19bc0c79c9ULL, 0x58cc92a7bfab26a6ULL,
    /* 72:*/ 0x9317acc314dd3bc7ULL, 0x2039e07d177a64a8ULL, 0x67939a94bc9d9b9cULL, 0xd4bdd62abf3ac4f3ULL,
    /* 76:*/ 0xe8c76f47eb5265f4ULL, 0x5be923f9e8f53a9bULL, 0x1c4359104312c5afULL, 0xaf6d15ae40b59ac0ULL,
    /* 80:*/ 0x192d8af2baf0e1e8ULL, 0xaa03c64cb957be87ULL, 0xeda9bca512b041b3ULL, 0x5e87f01b11171edcULL,
    /* 84:*/ 0x62fd4976457fbfdbULL, 0xd1d305c846d8e0b4ULL, 0x96797f21ed3f1f80ULL, 0x2557339fee9840efULL,
    /* 88:*/ 0xee8c0dfb45ee5d8eULL, 0x5da24145464902e1ULL, 0x1a083bacedaefdd5ULL, 0xa9267712ee09a2baULL,
    /* 92:*/ 0x955cce7fba6103bdULL, 0x267282c1b9c65cd2ULL, 0x61d8f8281221a3e6ULL, 0xd2f6b4961186fc89ULL,
    /* 96:*/ 0x9f8169ba49a54b33ULL, 0x2caf25044a02145cULL, 0x6b055fede1e5eb68ULL, 0xd82b1353e242b407ULL,
    /*100:*/ 0xe451aa3eb62a1500ULL, 0x577fe680b58d4a6fULL, 0x10d59c691e6ab55bULL, 0xa3fbd0d71dcdea34ULL,
    /*104:*/ 0x6820eeb3b6bbf755ULL, 0xdb0ea20db51ca83aULL, 0x9ca4d8e41efb570eULL, 0x2f8a945a1d5c0861ULL,
    /*108:*/ 0x13f02d374934a966ULL, 0xa0de61894a93f609ULL, 0xe7741b60e174093dULL, 0x545a57dee2d35652ULL,
    /*112:*/ 0xe21ac88218962d7aULL, 0x5134843c1b317215ULL, 0x169efed5b0d68d21ULL, 0xa5b0b26bb371d24eULL,
    /*116:*/ 0x99ca0b06e7197349ULL, 0x2ae447b8e4be2c26ULL, 0x6d4e3d514f59d312ULL, 0xde6071ef4cfe8c7dULL,
    /*120:*/ 0x15bb4f8be788911cULL, 0xa6950335e42fce73ULL, 0xe13f79dc4fc83147ULL, 0x521135624c6f6e28ULL,
    /*124:*/ 0x6e6b8c0f1807cf2fULL, 0xdd45c0b11ba09040ULL, 0x9aefba58b0476f74ULL, 0x29c1f6e6b3e0301bULL,
    /*128:*/ 0xc96c5795d7870f42ULL, 0x7a421b2bd420502dULL, 0x3de861c27fc7af19ULL, 0x8ec62d7c7c60f076ULL,
    /*132:*/ 0xb2bc941128085171ULL, 0x0192d8af2baf0e1eULL, 0x4638a2468048f12aULL, 0xf516eef883efae45ULL,
    /*136:*/ 0x3ecdd09c2899b324ULL, 0x8de39c222b3eec4bULL, 0xca49e6cb80d9137fULL, 0x7967aa75837e4c10ULL,
    /*140:*/ 0x451d1318d716ed17ULL, 0xf6335fa6d4b1b278ULL, 0xb199254f7f564d4cULL, 0x02b769f17cf11223ULL,
    /*144:*/ 0xb4f7f6ad86b4690bULL, 0x07d9ba1385133664ULL, 0x4073c0fa2ef4c950ULL, 0xf35d8c442d53963fULL,
    /*148:*/ 0xcf273529793b3738ULL, 0x7c0979977a9c6857ULL, 0x3ba3037ed17b9763ULL, 0x888d4fc0d2dcc80cULL,
    /*152:*/ 0x435671a479aad56dULL, 0xf0783d1a7a0d8a02ULL, 0xb7d247f3d1ea7536ULL, 0x04fc0b4dd24d2a59ULL,
    /*156:*/ 0x3886b22086258b5eULL, 0x8ba8fe9e8582d431ULL, 0xcc0284772e652b05ULL, 0x7f2cc8c92dc2746aULL,
    /*160:*/ 0x325b15e575e1c3d0ULL, 0x8175595b76469cbfULL, 0xc6df23b2dda1638bULL, 0x75f16f0cde063ce4ULL,
    /*164:*/ 0x498bd6618a6e9de3ULL, 0xfaa59adf89c9c28cULL, 0xbd0fe036222e3db8ULL, 0x0e21ac88218962d7ULL,
    /*168:*/ 0xc5fa92ec8aff7fb6ULL, 0x76d4de52895820d9ULL, 0x317ea4bb22bfdfedULL, 0x8250e80521188082ULL,
    /*172:*/ 0xbe2a516875702185ULL, 0x0d041dd676d77eeaULL, 0x4aae673fdd3081deULL, 0xf9802b81de97deb1ULL,
    /*176:*/ 0x4fc0b4dd24d2a599ULL, 0xfceef8632775faf6ULL, 0xbb44828a8c9205c2ULL, 0x086ace348f355aadULL,
    /*180:*/ 0x34107759db5dfbaaULL, 0x873e3be7d8faa4c5ULL, 0xc094410e731d5bf1ULL, 0x73ba0db070ba049eULL,
    /*184:*/ 0xb86133d4dbcc19ffULL, 0x0b4f7f6ad86b4690ULL, 0x4ce50583738cb9a4ULL, 0xffcb493d702be6cbULL,
    /*188:*/ 0xc3b1f050244347ccULL, 0x709fbcee27e418a3ULL, 0x3735c6078c03e797ULL, 0x841b8ab98fa4b8f8ULL,
    /*192:*/ 0xadda7c5f3c4488e3ULL, 0x1ef430e13fe3d78cULL, 0x595e4a08940428b8ULL, 0xea7006b697a377d7ULL,
    /*196:*/ 0xd60abfdbc3cbd6d0ULL, 0x6524f365c06c89bfULL, 0x228e898c6b8b768bULL, 0x91a0c532682c29e4ULL,
    /*200:*/ 0x5a7bfb56c35a3485ULL, 0xe955b7e8c0fd6beaULL, 0xaeffcd016b1a94deULL, 0x1dd181bf68bdcbb1ULL,
    /*204:*/ 0x21ab38d23cd56ab6ULL, 0x9285746c3f7235d9ULL, 0xd52f0e859495caedULL, 0x6601423b97329582ULL,
    /*208:*/ 0xd041dd676d77eeaaULL, 0x636f91d96ed0b1c5ULL, 0x24c5eb30c5374ef1ULL, 0x97eba78ec690119eULL,
    /*212:*/ 0xab911ee392f8b099ULL, 0x18bf525d915feff6ULL, 0x5f1528b43ab810c2ULL, 0xec3b640a391f4fadULL,
    /*216:*/ 0x27e05a6e926952ccULL, 0x94ce16d091ce0da3ULL, 0xd3646c393a29f297ULL, 0x604a2087398eadf8ULL,
    /*220:*/ 0x5c3099ea6de60cffULL, 0xef1ed5546e415390ULL, 0xa8b4afbdc5a6aca4ULL, 0x1b9ae303c601f3cbULL,
    /*224:*/ 0x56ed3e2f9e224471ULL, 0xe5c372919d851b1eULL, 0xa26908783662e42aULL, 0x114744c635c5bb45ULL,
    /*228:*/ 0x2d3dfdab61ad1a42ULL, 0x9e13b115620a452dULL, 0xd9b9cbfcc9edba19ULL, 0x6a978742ca4ae576ULL,
    /*232:*/ 0xa14cb926613cf817ULL, 0x1262f598629ba778ULL, 0x55c88f71c97c584cULL, 0xe6e6c3cfcadb0723ULL,
    /*236:*/ 0xda9c7aa29eb3a624ULL, 0x69b2361c9d14f94bULL, 0x2e184cf536f3067fULL, 0x9d36004b35545910ULL,
    /*240:*/ 0x2b769f17cf112238ULL, 0x9858d3a9ccb67d57ULL, 0xdff2a94067518263ULL, 0x6cdce5fe64f6dd0cULL,
    /*244:*/ 0x50a65c93309e7c0bULL, 0xe388102d33392364ULL, 0xa4226ac498dedc50ULL, 0x170c267a9b79833fULL,
    /*248:*/ 0xdcd7181e300f9e5eULL, 0x6ff954a033a8c131ULL, 0x28532e49984f3e05ULL, 0x9b7d62f79be8616aULL,
    /*252:*/ 0xa707db9acf80c06dULL, 0x14299724cc279f02ULL, 0x5383edcd67c06036ULL, 0xe0ada17364673f59ULL
};

