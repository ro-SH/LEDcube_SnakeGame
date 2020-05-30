/*******************************************************************************
 * @File: 1986VE9x.h
 * @Author: Milandr, L.
 * @Project: Generic
 * @Microcontroller: 1986VE9x
 * @Device: Evaluation Board For MCU 1986VE9x
 * @Date: 08.05.2018
 * @Purpose: Объявление адресов, битовых полей и таблицы прерываний
             для микроконтроллеров серии 1986VE9x
 ******************************************************************************/

/* --------------------------- Условная компиляция -------------------------- */

#ifndef __MDR32FX_H
#define __MDR32FX_H

#ifdef __cplusplus
  extern "C" {
#endif

#if defined __CC_ARM
  #pragma anon_unions
#endif

/* ----------------------- Таблица векторов прерываний ---------------------- */

typedef enum IRQn
{
  // Процессорные исключения
  NonMaskableInt_IRQn   = -14,  // Немаскируемое прерывание
  HardFault_IRQn        = -13,  // Сбой обработки прерываний
  MemoryManagement_IRQn = -12,  // Защита памяти
  BusFault_IRQn         = -11,  // Сбой шины данных
  UsageFault_IRQn       = -10,  // Сбой выполнения инструкций
  SVCall_IRQn           = -5,   // Функция Supervisor Call
  PendSV_IRQn           = -2,   // Запрос сервисов системного уровня
  SysTick_IRQn          = -1,   // Системный таймер

  // Прерывания периферийных блоков
  CAN1_IRQn             =  0,   // Контроллер интерфейса CAN1
  CAN2_IRQn             =  1,   // Контроллер интерфейса CAN2
  USB_IRQn              =  2,   // Контроллер интерфейса USB
  DMA_IRQn              =  5,   // Контроллер прямого доступа к памяти
  UART1_IRQn            =  6,   // Контроллер интерфейса UART1
  UART2_IRQn            =  7,   // Контроллер интерфейса UART2
  SSP1_IRQn             =  8,   // Контроллер интерфейса SSP1
  I2C_IRQn              =  10,  // Контроллер интерфейса I2C
  POWER_IRQn            =  11,  // Детектор напряжения питания
  WWDG_IRQn             =  12,  // Оконный сторожевой таймер
  Timer1_IRQn           =  14,  // Таймер 1 общего назначения
  Timer2_IRQn           =  15,  // Таймер 2 общего назначения
  Timer3_IRQn           =  16,  // Таймер 3 общего назначения
  ADC_IRQn              =  17,  // Аналого-цифровой преобразователь
  COMPARATOR_IRQn       =  19,  // Контроллер схемы компаратора
  SSP2_IRQn             =  20,  // Контроллер интерфейса SSP2
  BACKUP_IRQn           =  27,  // Батарейный домен
  EXT_INT1_IRQn         =  28,  // Внешнее прерывание 1
  EXT_INT2_IRQn         =  29,  // Внешнее прерывание 2
  EXT_INT3_IRQn         =  30,  // Внешнее прерывание 3
  EXT_INT4_IRQn         =  31   // Внешнее прерывание 4
} IRQn_Type;

/* --------------------- Конфигурация процессорного ядра -------------------- */

#define __CM3_REV              0x0102  // Ревизия ядра Cortex-M3
#define __MPU_PRESENT          1       // Наличие модуля защиты памяти (MPU)
#define __NVIC_PRIO_BITS       3       // Количество битов, определяющий приоритет прерываний
#define __Vendor_SysTickConfig 0       // Использование нестандартной конфигурации системного таймера

/* --------------------- Подключение заголовочных файлов -------------------- */

#include "core_cm3.h"
#include "system_MDR32F9Qx.h"

/* ------------------------- Перечисление состояний ------------------------- */

// Битовые состояний
typedef enum
{
  RESET = 0,
  SET   = !RESET
} FlagStatus, ITStatus, BitStatus;

#define IS_BIT_STATUS(STATUS) (((STATUS) == RESET) || ((STATE) == SET))

// Функциональные состояния
typedef enum {
  DISABLE = 0,
  ENABLE  = !DISABLE
} FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

// Ошибки
typedef enum
{
  ERROR   = 0,
  SUCCESS = !ERROR
} ErrorStatus;

/* ----------------------------- Контроллер CAN ----------------------------- */

// Структура буферов
typedef struct
{
  __IO uint32_t ID;
  __IO uint32_t DLC;
  __IO uint32_t DATAL;
  __IO uint32_t DATAH;
} MDR_CAN_BUF_TypeDef;

// Структура фильтров
typedef struct
{
  __IO uint32_t MASK;
  __IO uint32_t FILTER;
} MDR_CAN_BUF_FILTER_TypeDef;

// Структура контроллера CAN
typedef struct
{
  __IO uint32_t CONTROL;
  __IO uint32_t STATUS;
  __IO uint32_t BITTMNG;
       uint32_t RESERVED0;
  __IO uint32_t INT_EN;
       uint32_t RESERVED1[2];
  __IO uint32_t OVER;
  __IO uint32_t RXID;
  __IO uint32_t RXDLC;
  __IO uint32_t RXDATAL;
  __IO uint32_t RXDATAH;
  __IO uint32_t TXID;
  __IO uint32_t TXDLC;
  __IO uint32_t DATAL;
  __IO uint32_t DATAH;
  __IO uint32_t BUF_CON[32];
  __IO uint32_t INT_RX;
  __IO uint32_t RX;
  __IO uint32_t INT_TX;
  __IO uint32_t TX;
       uint32_t RESERVED2[76];
       MDR_CAN_BUF_TypeDef CAN_BUF[32];
       uint32_t RESERVED3[64];
       MDR_CAN_BUF_FILTER_TypeDef CAN_BUF_FILTER[32];
} MDR_CAN_TypeDef;

// Регистр CONTROL
// Позиции битовых полей
#define CAN_CONTROL_CAN_EN_Pos                            0
#define CAN_CONTROL_ROM_Pos                               1
#define CAN_CONTROL_STM_Pos                               2
#define CAN_CONTROL_SAP_Pos                               3
#define CAN_CONTROL_ROP_Pos                               4

// Маски битовых полей
#define CAN_CONTROL_CAN_EN                                ((uint32_t)0x00000001)
#define CAN_CONTROL_ROM                                   ((uint32_t)0x00000002)
#define CAN_CONTROL_STM                                   ((uint32_t)0x00000004)
#define CAN_CONTROL_SAP                                   ((uint32_t)0x00000008)
#define CAN_CONTROL_ROP                                   ((uint32_t)0x00000010) 

// Регистр STATUS
// Позиции битовых полей
#define CAN_STATUS_RX_READY_Pos                            0
#define CAN_STATUS_TX_READY_Pos                            1
#define CAN_STATUS_ERROR_OVER_Pos                          2
#define CAN_STATUS_BIT_ERR_Pos                             3
#define CAN_STATUS_BIT_STUFF_ERR_Pos                       4
#define CAN_STATUS_CRC_ERR_Pos                             5
#define CAN_STATUS_FRAME_ERR_Pos                           6
#define CAN_STATUS_ACK_ERR_Pos                             7
#define CAN_STATUS_IDLOWER_Pos                             8
#define CAN_STATUS_ERR_STATUS_Pos                          9
#define CAN_STATUS_RX_ERR_CNT8_Pos                        11
#define CAN_STATUS_TX_ERR_CNT8_Pos                        12
#define CAN_STATUS_RX_ERR_CNT_Pos                         16
#define CAN_STATUS_TX_ERR_CNT_Pos                         24

// Маски битовых полей
#define CAN_STATUS_RX_READY                               ((uint32_t)0x00000001)
#define CAN_STATUS_TX_READY                               ((uint32_t)0x00000002)
#define CAN_STATUS_ERROR_OVER                             ((uint32_t)0x00000004)
#define CAN_STATUS_BIT_ERR                                ((uint32_t)0x00000008)
#define CAN_STATUS_BIT_STUFF_ERR                          ((uint32_t)0x00000010)
#define CAN_STATUS_CRC_ERR                                ((uint32_t)0x00000020)
#define CAN_STATUS_FRAME_ERR                              ((uint32_t)0x00000040)
#define CAN_STATUS_ACK_ERR                                ((uint32_t)0x00000080)
#define CAN_STATUS_IDLOWER                                ((uint32_t)0x00000100)
#define CAN_STATUS_ERR_STATUS_Msk                         ((uint32_t)0x00000600)
#define CAN_STATUS_RX_ERR_CNT8                            ((uint32_t)0x00000800)
#define CAN_STATUS_TX_ERR_CNT8                            ((uint32_t)0x00001000)
#define CAN_STATUS_RX_ERR_CNT_Msk                         ((uint32_t)0x00FF0000)
#define CAN_STATUS_TX_ERR_CNT_Msk                         ((uint32_t)0xFF000000)

// Регистр CAN_BITTMNG
// Позиции битовых полей
#define CAN_BITTMNG_BRP_Pos                               0
#define CAN_BITTMNG_PSEG_Pos                              16
#define CAN_BITTMNG_SEG1_Pos                              19
#define CAN_BITTMNG_SEG2_Pos                              22
#define CAN_BITTMNG_SJW_Pos                               25
#define CAN_BITTMNG_SB_Pos                                27

// Маски битовых полей
#define CAN_BITTMNG_BRP_Msk                               ((uint32_t)0x0000FFFF)
#define CAN_BITTMNG_PSEG_Msk                              ((uint32_t)0x00070000)
#define CAN_BITTMNG_SEG1_Msk                              ((uint32_t)0x00380000)
#define CAN_BITTMNG_SEG2_Msk                              ((uint32_t)0x01C00000)
#define CAN_BITTMNG_SJW_Msk                               ((uint32_t)0x06000000)
#define CAN_BITTMNG_SB                                    ((uint32_t)0x08000000)

// Регистр INT_EN
// Позиции битовых полей
#define CAN_INT_EN_GLB_INT_EN_Pos                         0
#define CAN_INT_EN_RX_INT_EN_Pos                          1
#define CAN_INT_EN_TX_INT_EN_Pos                          2
#define CAN_INT_EN_ERR_INT_EN_Pos                         3
#define CAN_INT_EN_ERR_OVER_INT_EN_Pos                    4

// Маски битовых полей
#define CAN_INT_EN_GLB_INT_EN                             ((uint32_t)0x00000001)
#define CAN_INT_EN_RX_INT_EN                              ((uint32_t)0x00000002)
#define CAN_INT_EN_TX_INT_EN                              ((uint32_t)0x00000004)
#define CAN_INT_EN_ERR_INT_EN                             ((uint32_t)0x00000008)
#define CAN_INT_EN_ERR_OVER_INT_EN                        ((uint32_t)0x00000010)

// Регистры BUF[x].ID (RXID, TXID)
// Позиции битовых полей
#define CAN_ID_EID_Pos                                    0
#define CAN_ID_SID_Pos                                    18

// Маски битовых полей
#define CAN_ID_EID_Msk                                    ((uint32_t)0x0003FFFF)
#define CAN_ID_SID_Msk                                    ((uint32_t)0x1FFC0000) 

// Регистры BUF[x].DLC (RXDLC, TXDLC)
// Позиции битовых полей
#define CAN_DLC_Pos                                       0
#define CAN_DLC_RTR_Pos                                   8
#define CAN_DLC_R1_Pos                                    9
#define CAN_DLC_R0_Pos                                    10
#define CAN_DLC_SSR_Pos                                   11
#define CAN_DLC_IDE_Pos                                   12

// Маски битовых полей
#define CAN_DLC_Msk                                       ((uint32_t)0x0000000F)
#define CAN_DLC_RTR                                       ((uint32_t)0x00000100)
#define CAN_DLC_R1                                        ((uint32_t)0x00000200)
#define CAN_DLC_R0                                        ((uint32_t)0x00000400)
#define CAN_DLC_SSR                                       ((uint32_t)0x00000800)
#define CAN_DLC_IDE                                       ((uint32_t)0x00001000)

// Регистры BUF[x].DATAL (RXDATAL, TXDATAL)
// Позиции битовых полей
#define CAN_DATAL_DB0_Pos                                 0
#define CAN_DATAL_DB1_Pos                                 8
#define CAN_DATAL_DB2_Pos                                 16
#define CAN_DATAL_DB3_Pos                                 24

// Маски битовых полей
#define CAN_DATAL_DB0_Msk                                 ((uint32_t)0x000000FF)
#define CAN_DATAL_DB1_Msk                                 ((uint32_t)0x0000FF00)
#define CAN_DATAL_DB2_Msk                                 ((uint32_t)0x00FF0000)
#define CAN_DATAL_DB3_Msk                                 ((uint32_t)0xFF000000)

// Регистры BUF[x].DATAH (RXDATAH, TXDATAH)
// Позиции битовых полей
#define CAN_DATAH_DB4_Pos                                 0
#define CAN_DATAH_DB5_Pos                                 8
#define CAN_DATAH_DB6_Pos                                 16
#define CAN_DATAH_DB7_Pos                                 24

// Маски битовых полей
#define CAN_DATAH_DB4_Msk                                 ((uint32_t)0x000000FF)
#define CAN_DATAH_DB5_Msk                                 ((uint32_t)0x0000FF00)
#define CAN_DATAH_DB6_Msk                                 ((uint32_t)0x00FF0000)
#define CAN_DATAH_DB7_Msk                                 ((uint32_t)0xFF000000)

// Регистры BUF_CON[x]
// Позиции битовых полей
#define CAN_BUF_CON_EN_Pos                                0
#define CAN_BUF_CON_RX_TXN_Pos                            1
#define CAN_BUF_CON_OVER_EN_Pos                           2
#define CAN_BUF_CON_RTR_EN_Pos                            3
#define CAN_BUF_CON_PRIOR_0_Pos                           4
#define CAN_BUF_CON_TX_REQ_Pos                            5
#define CAN_BUF_CON_RX_FULL_Pos                           6
#define CAN_BUF_CON_OVER_WR_Pos                           7

// Маски битовых полей
#define CAN_BUF_CON_EN                                    ((uint32_t)0x00000001)
#define CAN_BUF_CON_RX_TXN                                ((uint32_t)0x00000002)
#define CAN_BUF_CON_OVER_EN                               ((uint32_t)0x00000004)
#define CAN_BUF_CON_RTR_EN                                ((uint32_t)0x00000008)
#define CAN_BUF_CON_PRIOR_0                               ((uint32_t)0x00000010)
#define CAN_BUF_CON_TX_REQ                                ((uint32_t)0x00000020)
#define CAN_BUF_CON_RX_FULL                               ((uint32_t)0x00000040)
#define CAN_BUF_CON_OVER_WR                               ((uint32_t)0x00000080)

/* ----------------------------- Контроллер USB ----------------------------- */

// Структура управления оконечной точкой
typedef struct
{
  __IO uint32_t CTRL;
  __IO uint32_t STS;
  __IO uint32_t TS;
  __IO uint32_t NTS;
} MDR_USB_SEP_TypeDef;

// Структура данных оконечной точки
typedef struct
{
  __IO uint32_t RXFD;
       uint32_t RESERVED0;
  __IO uint32_t RXFDC_L;
  __IO uint32_t RXFDC_H;
  __IO uint32_t RXFC;
       uint32_t RESERVED1[11];
  __IO uint32_t TXFD;
       uint32_t RESERVED2[3];
  __IO uint32_t TXFDC;
       uint32_t RESERVED3[11];
} MDR_USB_SEP_FIFO_TypeDef;

// Структура контроллера USB
typedef struct
{
  __IO uint32_t HTXC;
  __IO uint32_t HTXT;
  __IO uint32_t HTXLC;
  __IO uint32_t HTXSE;
  __IO uint32_t HTXA;
  __IO uint32_t HTXE;
  __IO uint32_t HFN_L;
  __IO uint32_t HFN_H;
  __IO uint32_t HIS;
  __IO uint32_t HIM;
  __IO uint32_t HRXS;
  __IO uint32_t HRXP;
  __IO uint32_t HRXA;
  __IO uint32_t HRXE;
  __IO uint32_t HRXCS;
  __IO uint32_t HSTM;
       uint32_t RESERVED0[16];
  __IO uint32_t HRXFD;
       uint32_t RESERVED1;
  __IO uint32_t HRXFDC_L;
  __IO uint32_t HRXFDC_H;
  __IO uint32_t HRXFC;
       uint32_t RESERVED2[11];
  __IO uint32_t HTXFD;
       uint32_t RESERVED3[3];
  __IO uint32_t HTXFC;
       uint32_t RESERVED4[11];
       MDR_USB_SEP_TypeDef USB_SEP[4];
  __IO uint32_t SC;
  __IO uint32_t SLS;
  __IO uint32_t SIS;
  __IO uint32_t SIM;
  __IO uint32_t SA;
  __IO uint32_t SFN_L;
  __IO uint32_t SFN_H;
       uint32_t RESERVED5[9];
       MDR_USB_SEP_FIFO_TypeDef USB_SEP_FIFO[4];
  __IO uint32_t HSCR;
  __IO uint32_t HSVR;
} MDR_USB_TypeDef;

// Регистр HTXC
// Позиции битовых полей
#define USB_HTXC_TREQ_Pos                                 0
#define USB_HTXC_SOFS_Pos                                 1
#define USB_HTXC_PREEN_Pos                                2
#define USB_HTXC_ISOEN_Pos                                3

// Маски битовых полей
#define USB_HTXC_TREQ                                     ((uint32_t)0x00000001)
#define USB_HTXC_SOFS                                     ((uint32_t)0x00000002)
#define USB_HTXC_PREEN                                    ((uint32_t)0x00000004)
#define USB_HTXC_ISOEN                                    ((uint32_t)0x00000008)

// Регистр HTXLC
// Позиции битовых полей
#define USB_HTXLC_Pos                                     0
#define USB_HTXLC_DC_Pos                                  2
#define USB_HTXLC_FSPL_Pos                                3
#define USB_HTXLC_FSLR_Pos                                4

// Маски битовых полей
#define USB_HTXLC_Msk                                     ((uint32_t)0x00000003)
#define USB_HTXLC_DC                                      ((uint32_t)0x00000004)
#define USB_HTXLC_FSPL                                    ((uint32_t)0x00000008)
#define USB_HTXLC_FSLR                                    ((uint32_t)0x00000010)

// Регистр HIS
// Позиции битовых полей
#define USB_HIS_TDONE_Pos                                 0
#define USB_HIS_RESUME_Pos                                1
#define USB_HIS_CONEV_Pos                                 2
#define USB_HIS_SOFS_Pos                                  3

// Маски битовых полей
#define USB_HIS_TDONE                                     ((uint32_t)0x00000001)
#define USB_HIS_RESUME                                    ((uint32_t)0x00000002)
#define USB_HIS_CONEV                                     ((uint32_t)0x00000004)
#define USB_HIS_SOFS                                      ((uint32_t)0x00000008)

// Регистр HIM
// Позиции битовых полей
#define USB_HIM_TDONEIE_Pos                               0
#define USB_HIM_RESUMEIE_Pos                              1
#define USB_HIM_CONEVIE_Pos                               2
#define USB_HIM_SOFIE_Pos                                 3

// Маски битовых полей
#define USB_HIM_TDONEIE                                   ((uint32_t)0x00000001)
#define USB_HIM_RESUMEIE                                  ((uint32_t)0x00000002)
#define USB_HIM_CONEVIE                                   ((uint32_t)0x00000004)
#define USB_HIM_SOFIE                                     ((uint32_t)0x00000008)

// Регистр HRXS
// Позиции битовых полей
#define USB_HRXS_CRCERR_Pos                               0
#define USB_HRXS_BSERR_Pos                                1
#define USB_HRXS_RXOF_Pos                                 2
#define USB_HRXS_RXTO_Pos                                 3
#define USB_HRXS_NAKRXED_Pos                              4
#define USB_HRXS_STALLRXED_Pos                            5
#define USB_HRXS_ACKRXED_Pos                              6
#define USB_HRXS_DATASEQ_Pos                              7

// Маски битовых полей
#define USB_HRXS_CRCERR                                   ((uint32_t)0x00000001)
#define USB_HRXS_BSERR                                    ((uint32_t)0x00000002)
#define USB_HRXS_RXOF                                     ((uint32_t)0x00000004)
#define USB_HRXS_RXTO                                     ((uint32_t)0x00000008)
#define USB_HRXS_NAKRXED                                  ((uint32_t)0x00000010)
#define USB_HRXS_STALLRXED                                ((uint32_t)0x00000020)
#define USB_HRXS_ACKRXED                                  ((uint32_t)0x00000040)
#define USB_HRXS_DATASEQ                                  ((uint32_t)0x00000080)

// Регистр SEP[x].CTRL
// Позиции битовых полей
#define USB_SEP_CTRL_EPEN_Pos                             0
#define USB_SEP_CTRL_EPRDY_Pos                            1
#define USB_SEP_CTRL_EPDATASEQ_Pos                        2
#define USB_SEP_CTRL_EPSSTALL_Pos                         3
#define USB_SEP_CTRL_EPISOEN_Pos                          4

// Маски битовых полей
#define USB_SEP_CTRL_EPEN                                 ((uint32_t)0x00000001)
#define USB_SEP_CTRL_EPRDY                                ((uint32_t)0x00000002)
#define USB_SEP_CTRL_EPDATASEQ                            ((uint32_t)0x00000004)
#define USB_SEP_CTRL_EPSSTALL                             ((uint32_t)0x00000008)
#define USB_SEP_CTRL_EPISOEN                              ((uint32_t)0x00000010)

// Регистр SEP[x].STS
// Позиции битовых полей
#define USB_SEP_STS_SCCRCERR_Pos                          0
#define USB_SEP_STS_SCBSERR_Pos                           1
#define USB_SEP_STS_SCRXOF_Pos                            2
#define USB_SEP_STS_SCRXTO_Pos                            3
#define USB_SEP_STS_SCNAKSENT_Pos                         4
#define USB_SEP_STS_SCSTALLSENT_Pos                       5
#define USB_SEP_STS_SCACKRXED_Pos                         6
#define USB_SEP_STS_SCDATASEQ_Pos                         7

// Маски битовых полей
#define USB_SEP_STS_SCCRCERR                              ((uint32_t)0x00000001)
#define USB_SEP_STS_SCBSERR                               ((uint32_t)0x00000002)
#define USB_SEP_STS_SCRXOF                                ((uint32_t)0x00000004)
#define USB_SEP_STS_SCRXTO                                ((uint32_t)0x00000008)
#define USB_SEP_STS_SCNAKSENT                             ((uint32_t)0x00000010)
#define USB_SEP_STS_SCSTALLSENT                           ((uint32_t)0x00000020)
#define USB_SEP_STS_SCACKRXED                             ((uint32_t)0x00000040)
#define USB_SEP_STS_SCDATASEQ                             ((uint32_t)0x00000080)

// Регистр SC
// Позиции битовых полей
#define USB_SCGEN_Pos                                     0
#define USB_SCTXLS_Pos                                    1
#define USB_SCDC_Pos                                      3
#define USB_SCFSP_Pos                                     4
#define USB_SCFSR_Pos                                     5

// Маски битовых полей
#define USB_SCGEN                                         ((uint32_t)0x00000001)
#define USB_SCTXLS_Msk                                    ((uint32_t)0x00000006)
#define USB_SCDC                                          ((uint32_t)0x00000008)
#define USB_SCFSP                                         ((uint32_t)0x00000010)
#define USB_SCFSR                                         ((uint32_t)0x00000020)

// Регистр SIS
// Позиции битовых полей
#define USB_SIS_SCTDONE_Pos                               0
#define USB_SIS_SCRESUME_Pos                              1
#define USB_SIS_SCRESETEV_Pos                             2
#define USB_SIS_SCSOFREC_Pos                              3
#define USB_SIS_SCNAKSENT_Pos                             4

// Маски битовых полей
#define USB_SIS_SCTDONE                                   ((uint32_t)0x00000001)
#define USB_SIS_SCRESUME                                  ((uint32_t)0x00000002)
#define USB_SIS_SCRESETEV                                 ((uint32_t)0x00000004)
#define USB_SIS_SCSOFREC                                  ((uint32_t)0x00000008)
#define USB_SIS_SCNAKSENT                                 ((uint32_t)0x00000010)

// Регистр SIM
// Позиции битовых полей
#define USB_SIM_SCTDONEIE_Pos                             0
#define USB_SIM_SCRESUMEIE_Pos                            1
#define USB_SIM_SCRESETEVIE_Pos                           2
#define USB_SIM_SCSOFRECIE_Pos                            3
#define USB_SIM_SCNAKSENTIE_Pos                           4

// Маски битовых полей
#define USB_SIM_SCTDONEIE                                 ((uint32_t)0x00000001)
#define USB_SIM_SCRESUMEIE                                ((uint32_t)0x00000002)
#define USB_SIM_SCRESETEVIE                               ((uint32_t)0x00000004)
#define USB_SIM_SCSOFRECIE                                ((uint32_t)0x00000008)
#define USB_SIM_SCNAKSENTIE                               ((uint32_t)0x00000010)

// Регистр HSCR
// Позиции битовых полей
#define USB_HSCR_HOST_MODE_Pos                            0
#define USB_HSCR_RESET_CORE_Pos                           1
#define USB_HSCR_EN_TX_Pos                                2
#define USB_HSCR_EN_RX_Pos                                3
#define USB_HSCR_DP_PULLUP_Pos                            4
#define USB_HSCR_DP_PULLDOWN_Pos                          5
#define USB_HSCR_DM_PULLUP_Pos                            6
#define USB_HSCR_DM_PULLDOWN_Pos                          7

// Маски битовых полей
#define USB_HSCR_HOST_MODE                                ((uint32_t)0x00000001)
#define USB_HSCR_RESET_CORE                               ((uint32_t)0x00000002)
#define USB_HSCR_EN_TX                                    ((uint32_t)0x00000004)
#define USB_HSCR_EN_RX                                    ((uint32_t)0x00000008)
#define USB_HSCR_DP_PULLUP                                ((uint32_t)0x00000010)
#define USB_HSCR_DP_PULLDOWN                              ((uint32_t)0x00000020)
#define USB_HSCR_DM_PULLUP                                ((uint32_t)0x00000040)
#define USB_HSCR_DM_PULLDOWN                              ((uint32_t)0x00000080)

// Регистр HSVR
// Позиции битовых полей
#define USB_HSVR_VERSION_Pos                              0
#define USB_HSVR_REVISION_Pos                             4

// Маски битовых полей
#define USB_HSVR_VERSION_Msk                              ((uint32_t)0x0000000F)
#define USB_HSVR_REVISION_Msk                             ((uint32_t)0x000000F0)

/* ---------------------------- Контроллер EEPROM --------------------------- */

// Структура контроллера EEPROM
typedef struct
{
  __IO uint32_t CMD;
  __IO uint32_t ADR;
  __IO uint32_t DI;
  __IO uint32_t DO;
  __IO uint32_t KEY;
} MDR_EEPROM_TypeDef;

// Регистр CMD
// Позиции битовых полей
#define EEPROM_CMD_CON_Pos                                0
#define EEPROM_CMD_WR_Pos                                 1
#define EEPROM_CMD_RD_Pos                                 2
#define EEPROM_CMD_DELAY_Pos                              3
#define EEPROM_CMD_XE_Pos                                 6
#define EEPROM_CMD_YE_Pos                                 7
#define EEPROM_CMD_SE_Pos                                 8
#define EEPROM_CMD_IFREN_Pos                              9
#define EEPROM_CMD_ERASE_Pos                              10
#define EEPROM_CMD_MAS1_Pos                               11
#define EEPROM_CMD_PROG_Pos                               12
#define EEPROM_CMD_NVSTR_Pos                              13

// Маски битовых полей
#define EEPROM_CMD_CON                                    ((uint32_t)0x00000001)
#define EEPROM_CMD_WR                                     ((uint32_t)0x00000002)
#define EEPROM_CMD_RD                                     ((uint32_t)0x00000004)
#define EEPROM_CMD_DELAY_Msk                              ((uint32_t)0x00000038)
#define EEPROM_CMD_XE                                     ((uint32_t)0x00000040)
#define EEPROM_CMD_YE                                     ((uint32_t)0x00000080)
#define EEPROM_CMD_SE                                     ((uint32_t)0x00000100)
#define EEPROM_CMD_IFREN                                  ((uint32_t)0x00000200)
#define EEPROM_CMD_ERASE                                  ((uint32_t)0x00000400)
#define EEPROM_CMD_MAS1                                   ((uint32_t)0x00000800)
#define EEPROM_CMD_PROG                                   ((uint32_t)0x00001000)
#define EEPROM_CMD_NVSTR                                  ((uint32_t)0x00002000)

/* ----------------------- Контроллер тактовой частоты ---------------------- */

// Структура контроллера тактовой частоты
typedef struct
{
  __IO uint32_t CLOCK_STATUS;
  __IO uint32_t PLL_CONTROL;
  __IO uint32_t HS_CONTROL;
  __IO uint32_t CPU_CLOCK;
  __IO uint32_t USB_CLOCK;
  __IO uint32_t ADC_MCO_CLOCK;
  __IO uint32_t RTC_CLOCK;
  __IO uint32_t PER_CLOCK;
  __IO uint32_t CAN_CLOCK;
  __IO uint32_t TIM_CLOCK;
  __IO uint32_t UART_CLOCK;
  __IO uint32_t SSP_CLOCK;
} MDR_RST_CLK_TypeDef;

// Регистр CLOCK_STATUS
// Позиции битовых полей
#define RST_CLK_CLOCK_STATUS_PLL_USB_RDY_Pos              0
#define RST_CLK_CLOCK_STATUS_PLL_CPU_RDY_Pos              1
#define RST_CLK_CLOCK_STATUS_HSE_RDY_Pos                  2

// Маски битовых полей
#define RST_CLK_CLOCK_STATUS_PLL_USB_RDY                  ((uint32_t)0x00000001)
#define RST_CLK_CLOCK_STATUS_PLL_CPU_RDY                  ((uint32_t)0x00000002)
#define RST_CLK_CLOCK_STATUS_HSE_RDY                      ((uint32_t)0x00000004)

// Регистр PLL_CONTROL
// Позиции битовых полей
#define RST_CLK_PLL_CONTROL_PLL_USB_ON_Pos                0
#define RST_CLK_PLL_CONTROL_PLL_USB_RLD_Pos               1
#define RST_CLK_PLL_CONTROL_PLL_CPU_ON_Pos                2
#define RST_CLK_PLL_CONTROL_PLL_CPU_PLD_Pos               3
#define RST_CLK_PLL_CONTROL_PLL_USB_MUL_Pos               4
#define RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Pos               8

// Маски битовых полей
#define RST_CLK_PLL_CONTROL_PLL_USB_ON                    ((uint32_t)0x00000001)
#define RST_CLK_PLL_CONTROL_PLL_USB_RLD                   ((uint32_t)0x00000002)
#define RST_CLK_PLL_CONTROL_PLL_CPU_ON                    ((uint32_t)0x00000004)
#define RST_CLK_PLL_CONTROL_PLL_CPU_PLD                   ((uint32_t)0x00000008)
#define RST_CLK_PLL_CONTROL_PLL_USB_MUL_Msk               ((uint32_t)0x000000F0)
#define RST_CLK_PLL_CONTROL_PLL_CPU_MUL_Msk               ((uint32_t)0x00000F00)

// Регистр HS_CONTROL
// Позиции битовых полей
#define RST_CLK_HS_CONTROL_HSE_ON_Pos                     0
#define RST_CLK_HS_CONTROL_HSE_BYP_Pos                    1

// Маски битовых полей
#define RST_CLK_HS_CONTROL_HSE_ON                         ((uint32_t)0x00000001)
#define RST_CLK_HS_CONTROL_HSE_BYP                        ((uint32_t)0x00000002)

// Регистр CPU_CLOCK
// Позиции битовых полей
#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_Pos                  0
#define RST_CLK_CPU_CLOCK_CPU_C2_SEL_Pos                  2
#define RST_CLK_CPU_CLOCK_CPU_C3_SEL_Pos                  4
#define RST_CLK_CPU_CLOCK_HCLK_SEL_Pos                    8

// Маски битовых полей
#define RST_CLK_CPU_CLOCK_CPU_C1_SEL_Msk                  ((uint32_t)0x00000003)
#define RST_CLK_CPU_CLOCK_CPU_C2_SEL_Msk                  ((uint32_t)0x00000004)
#define RST_CLK_CPU_CLOCK_CPU_C3_SEL_Msk                  ((uint32_t)0x000000F0)
#define RST_CLK_CPU_CLOCK_HCLK_SEL_Msk                    ((uint32_t)0x00000300)

// Регистр USB_CLOCK
// Позиции битовых полей
#define RST_CLK_USB_CLOCK_USB_C1_SEL_Pos                  0
#define RST_CLK_USB_CLOCK_USB_C2_SEL_Pos                  2
#define RST_CLK_USB_CLOCK_USB_C3_SEL_Pos                  4
#define RST_CLK_USB_CLOCK_USB_CLK_EN_Pos                  8

// Маски битовых полей
#define RST_CLK_USB_CLOCK_USB_C1_SEL_Msk                  ((uint32_t)0x00000003)
#define RST_CLK_USB_CLOCK_USB_C2_SEL_Msk                  ((uint32_t)0x00000004)
#define RST_CLK_USB_CLOCK_USB_C3_SEL_Msk                  ((uint32_t)0x00000010)
#define RST_CLK_USB_CLOCK_USB_CLK_EN                      ((uint32_t)0x00000100)

// Регистр ADC_MCO
// Позиции битовых полей
#define RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL_Pos              0
#define RST_CLK_ADC_MCO_CLOCK_ADC_C2_SEL_Pos              4
#define RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL_Pos              8
#define RST_CLK_ADC_MCO_CLOCK_ADC_CLK_EN_Pos              13

// Маски битовых полей
#define RST_CLK_ADC_MCO_CLOCK_ADC_C1_SEL_Msk              ((uint32_t)0x00000003)
#define RST_CLK_ADC_MCO_CLOCK_ADC_C2_SEL_Msk              ((uint32_t)0x00000030)
#define RST_CLK_ADC_MCO_CLOCK_ADC_C3_SEL_Msk              ((uint32_t)0x00000F00)
#define RST_CLK_ADC_MCO_CLOCK_ADC_CLK_EN                  ((uint32_t)0x00002000)

// Регистр RTC_CLOCK
// Позиции битовых полей
#define RST_CLK_RTC_CLOCK_HSE_SEL_Pos                     0
#define RST_CLK_RTC_CLOCK_HSI_SEL_Pos                     4
#define RST_CLK_RTC_CLOCK_HSE_RTC_EN_Pos                  8
#define RST_CLK_RTC_CLOCK_HSI_RTC_EN_Pos                  9

// Маски битовых полей
#define RST_CLK_RTC_CLOCK_HSE_SEL_Msk                     ((uint32_t)0x0000000F)
#define RST_CLK_RTC_CLOCK_HSI_SEL_Msk                     ((uint32_t)0x000000F0)
#define RST_CLK_RTC_CLOCK_HSE_RTC_EN                      ((uint32_t)0x00000100)
#define RST_CLK_RTC_CLOCK_HSI_RTC_EN                      ((uint32_t)0x00000200)

// Регистр PER_CLOCK
// Позиции битовых полей
#define RST_CLK_PCLK_CAN1_Pos                             0
#define RST_CLK_PCLK_CAN2_Pos                             1
#define RST_CLK_PCLK_USB_Pos                              2
#define RST_CLK_PCLK_EEPROM_CNTRL_Pos                     3
#define RST_CLK_PCLK_RST_CLK_Pos                          4
#define RST_CLK_PCLK_DMA_Pos                              5
#define RST_CLK_PCLK_UART1_Pos                            6
#define RST_CLK_PCLK_UART2_Pos                            7
#define RST_CLK_PCLK_SSP1_Pos                             8
#define RST_CLK_PCLK_09_Pos                               9
#define RST_CLK_PCLK_I2C_Pos                              10
#define RST_CLK_PCLK_POWER_Pos                            11
#define RST_CLK_PCLK_WWDT_Pos                             12
#define RST_CLK_PCLK_IWDT_Pos                             13
#define RST_CLK_PCLK_TIMER1_Pos                           14
#define RST_CLK_PCLK_TIMER2_Pos                           15
#define RST_CLK_PCLK_TIMER3_Pos                           16
#define RST_CLK_PCLK_ADC_Pos                              17
#define RST_CLK_PCLK_DAC_Pos                              18
#define RST_CLK_PCLK_COMP_Pos                             19
#define RST_CLK_PCLK_SSP2_Pos                             20
#define RST_CLK_PCLK_PORTA_Pos                            21
#define RST_CLK_PCLK_PORTB_Pos                            22
#define RST_CLK_PCLK_PORTC_Pos                            23
#define RST_CLK_PCLK_PORTD_Pos                            24
#define RST_CLK_PCLK_PORTE_Pos                            25
#define RST_CLK_PCLK_26_Pos                               26
#define RST_CLK_PCLK_BKP_Pos                              27
#define RST_CLK_PCLK_28_Pos                               28
#define RST_CLK_PCLK_PORTF_Pos                            29
#define RST_CLK_PCLK_EBC_Pos                              30
#define RST_CLK_PCLK_31_Pos                               31

// Маски битовых полей
#define RST_CLK_PCLK_CAN1_Msk                             ((uint32_t)0x00000001)
#define RST_CLK_PCLK_CAN2_Msk                             ((uint32_t)0x00000002)
#define RST_CLK_PCLK_USB_Msk                              ((uint32_t)0x00000004)
#define RST_CLK_PCLK_EEPROM_CNTRL_Msk                     ((uint32_t)0x00000008)
#define RST_CLK_PCLK_RST_CLK_Msk                          ((uint32_t)0x00000010)
#define RST_CLK_PCLK_DMA_Msk                              ((uint32_t)0x00000020)
#define RST_CLK_PCLK_UART1_Msk                            ((uint32_t)0x00000040)
#define RST_CLK_PCLK_UART2_Msk                            ((uint32_t)0x00000080)
#define RST_CLK_PCLK_SSP1_Msk                             ((uint32_t)0x00000100)
#define RST_CLK_PCLK_09_Msk                               ((uint32_t)0x00000200)
#define RST_CLK_PCLK_I2C1_Msk                             ((uint32_t)0x00000400)
#define RST_CLK_PCLK_POWER_Msk                            ((uint32_t)0x00000800)
#define RST_CLK_PCLK_WWDT_Msk                             ((uint32_t)0x00001000)
#define RST_CLK_PCLK_IWDT_Msk                             ((uint32_t)0x00002000)
#define RST_CLK_PCLK_TIMER1_Msk                           ((uint32_t)0x00004000)
#define RST_CLK_PCLK_TIMER2_Msk                           ((uint32_t)0x00008000)
#define RST_CLK_PCLK_TIMER3_Msk                           ((uint32_t)0x00010000)
#define RST_CLK_PCLK_ADC_Msk                              ((uint32_t)0x00020000)
#define RST_CLK_PCLK_DAC_Msk                              ((uint32_t)0x00040000)
#define RST_CLK_PCLK_COMP_Msk                             ((uint32_t)0x00080000)
#define RST_CLK_PCLK_SSP2_Msk                             ((uint32_t)0x00100000)
#define RST_CLK_PCLK_PORTA_Msk                            ((uint32_t)0x00200000)
#define RST_CLK_PCLK_PORTB_Msk                            ((uint32_t)0x00400000)
#define RST_CLK_PCLK_PORTC_Msk                            ((uint32_t)0x00800000)
#define RST_CLK_PCLK_PORTD_Msk                            ((uint32_t)0x01000000)
#define RST_CLK_PCLK_PORTE_Msk                            ((uint32_t)0x02000000)
#define RST_CLK_PCLK_26_Msk                               ((uint32_t)0x04000000)
#define RST_CLK_PCLK_BKP_Msk                              ((uint32_t)0x08000000)
#define RST_CLK_PCLK_28_Msk                               ((uint32_t)0x10000000)
#define RST_CLK_PCLK_PORTF_Msk                            ((uint32_t)0x20000000)
#define RST_CLK_PCLK_EBC_Msk                              ((uint32_t)0x40000000)
#define RST_CLK_PCLK_31_Msk                               ((uint32_t)0x80000000)

// Регистр CAN_CLOCK
// Позиции битовых полей
#define RST_CLK_CAN_CLOCK_CAN1_BRG_Pos                    0
#define RST_CLK_CAN_CLOCK_CAN2_BRG_Pos                    8
#define RST_CLK_CAN_CLOCK_CAN1_CLK_EN_Pos                 24
#define RST_CLK_CAN_CLOCK_CAN2_CLK_EN_Pos                 25

// Маски битовых полей
#define RST_CLK_CAN_CLOCK_CAN1_BRG_Msk                    ((uint32_t)0x000000FF)
#define RST_CLK_CAN_CLOCK_CAN2_BRG_Msk                    ((uint32_t)0x0000FF00)
#define RST_CLK_CAN_CLOCK_CAN1_CLK_EN                     ((uint32_t)0x01000000)
#define RST_CLK_CAN_CLOCK_CAN2_CLK_EN                     ((uint32_t)0x02000000)

// Регистр TIM_CLOCK
// Позиции битовых полей
#define RST_CLK_TIM_CLOCK_TIM1_BRG_Pos                    0
#define RST_CLK_TIM_CLOCK_TIM2_BRG_Pos                    8
#define RST_CLK_TIM_CLOCK_TIM3_BRG_Pos                    16
#define RST_CLK_TIM_CLOCK_TIM1_CLK_EN_Pos                 24
#define RST_CLK_TIM_CLOCK_TIM2_CLK_EN_Pos                 25
#define RST_CLK_TIM_CLOCK_TIM3_CLK_EN_Pos                 26

// Маски битовых полей
#define RST_CLK_TIM_CLOCK_TIM1_BRG_Msk                    ((uint32_t)0x000000FF)
#define RST_CLK_TIM_CLOCK_TIM2_BRG_Msk                    ((uint32_t)0x0000FF00)
#define RST_CLK_TIM_CLOCK_TIM3_BRG_Msk                    ((uint32_t)0x00FF0000)
#define RST_CLK_TIM_CLOCK_TIM1_CLK_EN                     ((uint32_t)0x01000000)
#define RST_CLK_TIM_CLOCK_TIM2_CLK_EN                     ((uint32_t)0x02000000)
#define RST_CLK_TIM_CLOCK_TIM3_CLK_EN                     ((uint32_t)0x04000000)

// Регистр UART_CLOCK
// Позиции битовых полей
#define RST_CLK_UART_CLOCK_UART1_BRG_Pos                  0
#define RST_CLK_UART_CLOCK_UART2_BRG_Pos                  8
#define RST_CLK_UART_CLOCK_UART1_CLK_EN_Pos               24
#define RST_CLK_UART_CLOCK_UART2_CLK_EN_Pos               25

// Маски битовых полей
#define RST_CLK_UART_CLOCK_UART1_BRG_Msk                  ((uint32_t)0x000000FF)
#define RST_CLK_UART_CLOCK_UART2_BRG_Msk                  ((uint32_t)0x0000FF00)
#define RST_CLK_UART_CLOCK_UART1_CLK_EN                   ((uint32_t)0x01000000)
#define RST_CLK_UART_CLOCK_UART2_CLK_EN                   ((uint32_t)0x02000000)

// Регистр SSP_CLOCK
// Позиции битовых полей
#define RST_CLK_SSP_CLOCK_SSP1_BRG_Pos                    0
#define RST_CLK_SSP_CLOCK_SSP2_BRG_Pos                    8
#define RST_CLK_SSP_CLOCK_SSP1_CLK_EN_Pos                 24
#define RST_CLK_SSP_CLOCK_SSP2_CLK_EN_Pos                 25

// Маски битовых полей
#define RST_CLK_SSP_CLOCK_SSP1_BRG_Msk                    ((uint32_t)0x000000FF)
#define RST_CLK_SSP_CLOCK_SSP2_BRG_Msk                    ((uint32_t)0x0000FF00)
#define RST_CLK_SSP_CLOCK_SSP1_CLK_EN                     ((uint32_t)0x01000000)
#define RST_CLK_SSP_CLOCK_SSP2_CLK_EN                     ((uint32_t)0x02000000)

/* ----------------------------- Контроллер DMA ----------------------------- */

// Структура контроллера DMA
typedef struct
{
  __IO uint32_t STATUS;
  __IO uint32_t CFG;
  __IO uint32_t CTRL_BASE_PTR;
  __IO uint32_t ALT_CTRL_BASE_PTR;
  __IO uint32_t WAITONREQ_STATUS;
  __IO uint32_t CHNL_SW_REQUEST;
  __IO uint32_t CHNL_USEBURST_SET;
  __IO uint32_t CHNL_USEBURST_CLR;
  __IO uint32_t CHNL_REQ_MASK_SET;
  __IO uint32_t CHNL_REQ_MASK_CLR;
  __IO uint32_t CHNL_ENABLE_SET;
  __IO uint32_t CHNL_ENABLE_CLR;
  __IO uint32_t CHNL_PRI_ALT_SET;
  __IO uint32_t CHNL_PRI_ALT_CLR;
  __IO uint32_t CHNL_PRIORITY_SET;
  __IO uint32_t CHNL_PRIORITY_CLR;
       uint32_t RESERVED0[3];
  __IO uint32_t ERR_CLR;
} MDR_DMA_TypeDef;

// Структура управляющих данных
typedef struct
{
  __IO uint32_t DMA_SourceEndPointer;       // Указатель на конец данных источника
  __IO uint32_t DMA_DestinationEndPointer;  // Указатель на конец данных приемника
  __IO uint32_t DMA_Control;                // Область управления
       uint32_t DMA_Unused;                 // Неиспользуемая область
} DMA_ControlDataTypeDef;

// Регистр STATUS
// Позиции битовых полей
#define DMA_STATUS_MASTER_ENABLE_Pos                      0
#define DMA_STATUS_STATE_Pos                              4
#define DMA_STATUS_CHNLS_MINUS1_Pos                       16
#define DMA_STATUS_TEST_STATUS_Pos                        28

// Маски битовых полей
#define DMA_STATUS_MASTER_ENABLE                          ((uint32_t)0x00000001)
#define DMA_STATUS_STATE_Msk                              ((uint32_t)0x000000F0)
#define DMA_STATUS_CHNLS_MINUS1_Msk                       ((uint32_t)0x001F0000)
#define DMA_STATUS_TEST_STATUS_Msk                        ((uint32_t)0xF0000000)

// Регистр CFG
// Позиции битовых полей
#define DMA_CFG_MASTER_ENABLE_Pos                         0
#define DMA_CFG_CHNL_PROT_CTRL_Pos                        5

// Маски битовых полей
#define DMA_CFG_MASTER_ENABLE                             ((uint32_t)0x00000001)
#define DMA_CFG_CHNL_PROT_CTRL_Msk                        ((uint32_t)0x000000E0)

// Регистр CHANNEL_CFG
// Позиции битовых полей
#define DMA_CHANNEL_CFG_CYCLE_CTRL_Pos                    0
#define DMA_CHANNEL_CFG_NEXT_USEBURST_Pos                 3
#define DMA_CHANNEL_CFG_N_MINUS_1_Pos                     4
#define DMA_CHANNEL_CFG_R_POWER_Pos                       14
#define DMA_CHANNEL_CFG_SRC_PROT_CTRL_Pos                 18
#define DMA_CHANNEL_CFG_DST_PROT_CTRL_Pos                 21
#define DMA_CHANNEL_CFG_SRC_SIZE_Pos                      24
#define DMA_CHANNEL_CFG_SRC_INC_Pos                       26
#define DMA_CHANNEL_CFG_DST_SIZE_Pos                      28
#define DMA_CHANNEL_CFG_DST_INC_Pos                       30

// Маски битовых полей
#define DMA_CHANNEL_CFG_CYCLE_CTRL_Msk                    ((uint32_t)0x00000007)
#define DMA_CHANNEL_CFG_NEXT_USEBURST_Msk                 ((uint32_t)0x00000008)
#define DMA_CHANNEL_CFG_N_MINUS_1_Msk                     ((uint32_t)0x00003FF0)
#define DMA_CHANNEL_CFG_R_POWER_Msk                       ((uint32_t)0x0003C000)
#define DMA_CHANNEL_CFG_SRC_PROT_CTRL_Msk                 ((uint32_t)0x001C0000)
#define DMA_CHANNEL_CFG_DST_PROT_CTRL_Msk                 ((uint32_t)0x00E00000)
#define DMA_CHANNEL_CFG_SRC_SIZE_Msk                      ((uint32_t)0x03000000)
#define DMA_CHANNEL_CFG_SRC_INC_Msk                       ((uint32_t)0x0C000000)
#define DMA_CHANNEL_CFG_DST_SIZE_Msk                      ((uint32_t)0x03000000)
#define DMA_CHANNEL_CFG_DST_INC_Msk                       ((uint32_t)0xC0000000)

/* ----------------------------- Контроллер UART ---------------------------- */

// Структура контроллера UART
typedef struct
{
  __IO uint32_t DR;
  __IO uint32_t RSR_ECR;
       uint32_t RESERVED0[4];
  __IO uint32_t FR;
       uint32_t RESERVED1;
  __IO uint32_t ILPR;
  __IO uint32_t IBRD;
  __IO uint32_t FBRD;
  __IO uint32_t LCR_H;
  __IO uint32_t CR;
  __IO uint32_t IFLS;
  __IO uint32_t IMSC;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t ICR;
  __IO uint32_t DMACR;
} MDR_UART_TypeDef;

// Регистр DR
// Позиции битовых полей
#define UART_DR_DATA_Pos                                  0
#define UART_DR_FE_Pos                                    8
#define UART_DR_PE_Pos                                    9
#define UART_DR_BE_Pos                                    10
#define UART_DR_OE_Pos                                    11

// Маски битовых полей
#define UART_DR_DATA_Msk                                  ((uint32_t)0x000000FF)
#define UART_DR_FE                                        ((uint32_t)0x00000100)
#define UART_DR_PE                                        ((uint32_t)0x00000200)
#define UART_DR_BE                                        ((uint32_t)0x00000400)
#define UART_DR_OE                                        ((uint32_t)0x00000800)

// Регистр RSR_ECR
// Позиции битовых полей
#define UART_RSR_ECR_FE_Pos                               0
#define UART_RSR_ECR_PE_Pos                               1
#define UART_RSR_ECR_BE_Pos                               2
#define UART_RSR_ECR_OE_Pos                               3

// Маски битовых полей
#define UART_RSR_ECR_FE                                   ((uint32_t)0x00000001)
#define UART_RSR_ECR_PE                                   ((uint32_t)0x00000002)
#define UART_RSR_ECR_BE                                   ((uint32_t)0x00000004)
#define UART_RSR_ECR_OE                                   ((uint32_t)0x00000008)

// Регистр FR
// Позиции битовых полей
#define UART_FR_CTS_Pos                                   0
#define UART_FR_DSR_Pos                                   1
#define UART_FR_DCD_Pos                                   2
#define UART_FR_BUSY_Pos                                  3
#define UART_FR_RXFE_Pos                                  4
#define UART_FR_TXFF_Pos                                  5
#define UART_FR_RXFF_Pos                                  6
#define UART_FR_TXFE_Pos                                  7
#define UART_FR_RI_Pos                                    8

// Маски битовых полей
#define UART_FR_CTS                                       ((uint32_t)0x00000001)
#define UART_FR_DSR                                       ((uint32_t)0x00000002)
#define UART_FR_DCD                                       ((uint32_t)0x00000004)
#define UART_FR_BUSY                                      ((uint32_t)0x00000008)
#define UART_FR_RXFE                                      ((uint32_t)0x00000010)
#define UART_FR_TXFF                                      ((uint32_t)0x00000020)
#define UART_FR_RXFF                                      ((uint32_t)0x00000040)
#define UART_FR_TXFE                                      ((uint32_t)0x00000080)
#define UART_FR_RI                                        ((uint32_t)0x00000100)

// Регистр LCR_H
// Позиции битовых полей
#define UART_LCR_H_BRK_Pos                                0
#define UART_LCR_H_PEN_Pos                                1
#define UART_LCR_H_EPS_Pos                                2
#define UART_LCR_H_STP2_Pos                               3
#define UART_LCR_H_FEN_Pos                                4
#define UART_LCR_H_WLEN_Pos                               5
#define UART_LCR_H_SPS_Pos                                7

// Маски битовых полей
#define UART_LCR_H_BRK                                    ((uint32_t)0x00000001)
#define UART_LCR_H_PEN                                    ((uint32_t)0x00000002)
#define UART_LCR_H_EPS                                    ((uint32_t)0x00000004)
#define UART_LCR_H_STP2                                   ((uint32_t)0x00000008)
#define UART_LCR_H_FEN                                    ((uint32_t)0x00000010)
#define UART_LCR_H_WLEN_Msk                               ((uint32_t)0x00000060)
#define UART_LCR_H_SPS                                    ((uint32_t)0x00000080)

// Регистр CR
// Позиции битовых полей
#define UART_CR_UARTEN_Pos                                0
#define UART_CR_SIREN_Pos                                 1
#define UART_CR_SIRLP_Pos                                 2
#define UART_CR_LBE_Pos                                   7
#define UART_CR_TXE_Pos                                   8
#define UART_CR_RXE_Pos                                   9
#define UART_CR_DTR_Pos                                   10
#define UART_CR_RTS_Pos                                   11
#define UART_CR_OUT1_Pos                                  12
#define UART_CR_OUT2_Pos                                  13
#define UART_CR_RTSEN_Pos                                 14
#define UART_CR_CTSEN_Pos                                 15

// Маски битовых полей
#define UART_CR_UARTEN                                    ((uint32_t)0x00000001)
#define UART_CR_SIREN                                     ((uint32_t)0x00000002)
#define UART_CR_SIRLP                                     ((uint32_t)0x00000004)
#define UART_CR_LBE                                       ((uint32_t)0x00000080)
#define UART_CR_TXE                                       ((uint32_t)0x00000100)
#define UART_CR_RXE                                       ((uint32_t)0x00000200)
#define UART_CR_DTR                                       ((uint32_t)0x00000400)
#define UART_CR_RTS                                       ((uint32_t)0x00000800)
#define UART_CR_OUT1                                      ((uint32_t)0x00001000)
#define UART_CR_OUT2                                      ((uint32_t)0x00002000)
#define UART_CR_RTSEN                                     ((uint32_t)0x00004000)
#define UART_CR_CTSEN                                     ((uint32_t)0x00008000)

// Регистр IFLS
// Позиции битовых полей
#define UART_IFLS_TXIFLSEL_Pos                            0
#define UART_IFLS_RXIFLSEL_Pos                            3

// Маски битовых полей
#define UART_IFLS_TXIFLSEL_Msk                            ((uint32_t)0x00000007)
#define UART_IFLS_RXIFLSEL_Msk                            ((uint32_t)0x00000038)

// Регистр IMSC
// Позиции битовых полей
#define UART_IMSC_RIMIM_Pos                               0
#define UART_IMSC_CTSMIM_Pos                              1
#define UART_IMSC_DCDMIM_Pos                              2
#define UART_IMSC_DSRMIM_Pos                              3
#define UART_IMSC_RXIM_Pos                                4
#define UART_IMSC_TXIM_Pos                                5
#define UART_IMSC_RTIM_Pos                                6
#define UART_IMSC_FEIM_Pos                                7
#define UART_IMSC_PEIM_Pos                                8
#define UART_IMSC_BEIM_Pos                                9
#define UART_IMSC_OEIM_Pos                                10

// Маски битовых полей
#define UART_IMSC_RIMIM                                   ((uint32_t)0x00000001)
#define UART_IMSC_CTSMIM                                  ((uint32_t)0x00000002)
#define UART_IMSC_DCDMIM                                  ((uint32_t)0x00000004)
#define UART_IMSC_DSRMIM                                  ((uint32_t)0x00000008)
#define UART_IMSC_RXIM                                    ((uint32_t)0x00000010)
#define UART_IMSC_TXIM                                    ((uint32_t)0x00000020)
#define UART_IMSC_RTIM                                    ((uint32_t)0x00000040)
#define UART_IMSC_FEIM                                    ((uint32_t)0x00000080)
#define UART_IMSC_PEIM                                    ((uint32_t)0x00000100)
#define UART_IMSC_BEIM                                    ((uint32_t)0x00000200)
#define UART_IMSC_OEIM                                    ((uint32_t)0x00000400)

// Регистр RIS
// Позиции битовых полей
#define UART_RIS_RIRMIS_Pos                               0
#define UART_RIS_CTSRMIS_Pos                              1
#define UART_RIS_DCDRMIS_Pos                              2
#define UART_RIS_DSRRMIS_Pos                              3
#define UART_RIS_RXRIS_Pos                                4
#define UART_RIS_TXRIS_Pos                                5
#define UART_RIS_RTRIS_Pos                                6
#define UART_RIS_FERIS_Pos                                7
#define UART_RIS_PERIS_Pos                                8
#define UART_RIS_BERIS_Pos                                9
#define UART_RIS_OERIS_Pos                                10

// Маски битовых полей
#define UART_RIS_RIRMIS                                   ((uint32_t)0x00000001)
#define UART_RIS_CTSRMIS                                  ((uint32_t)0x00000002)
#define UART_RIS_DCDRMIS                                  ((uint32_t)0x00000004)
#define UART_RIS_DSRRMIS                                  ((uint32_t)0x00000008)
#define UART_RIS_RXRIS                                    ((uint32_t)0x00000010)
#define UART_RIS_TXRIS                                    ((uint32_t)0x00000020)
#define UART_RIS_RTRIS                                    ((uint32_t)0x00000040)
#define UART_RIS_FERIS                                    ((uint32_t)0x00000080)
#define UART_RIS_PERIS                                    ((uint32_t)0x00000100)
#define UART_RIS_BERIS                                    ((uint32_t)0x00000200)
#define UART_RIS_OERIS                                    ((uint32_t)0x00000400)

// Регистр MIS
// Позиции битовых полей
#define UART_MIS_RIMMIS_Pos                               0
#define UART_MIS_CTSMMIS_Pos                              1
#define UART_MIS_DCDMMIS_Pos                              2
#define UART_MIS_DSRMMIS_Pos                              3
#define UART_MIS_RXMIS_Pos                                4
#define UART_MIS_TXMIS_Pos                                5
#define UART_MIS_RTMIS_Pos                                6
#define UART_MIS_FEMIS_Pos                                7
#define UART_MIS_PEMIS_Pos                                8
#define UART_MIS_BEMIS_Pos                                9
#define UART_MIS_OEMIS_Pos                                10

// Маски битовых полей
#define UART_MIS_RIMMIS                                   ((uint32_t)0x00000001)
#define UART_MIS_CTSMMIS                                  ((uint32_t)0x00000002)
#define UART_MIS_DCDMMIS                                  ((uint32_t)0x00000004)
#define UART_MIS_DSRMMIS                                  ((uint32_t)0x00000008)
#define UART_MIS_RXMIS                                    ((uint32_t)0x00000010)
#define UART_MIS_TXMIS                                    ((uint32_t)0x00000020)
#define UART_MIS_RTMIS                                    ((uint32_t)0x00000040)
#define UART_MIS_FEMIS                                    ((uint32_t)0x00000080)
#define UART_MIS_PEMIS                                    ((uint32_t)0x00000100)
#define UART_MIS_BEMIS                                    ((uint32_t)0x00000200)
#define UART_MIS_OEMIS                                    ((uint32_t)0x00000400)

// Регистр ICR
// Позиции битовых полей
#define UART_ICR_RIMIC_Pos                                0
#define UART_ICR_CTSMIC_Pos                               1
#define UART_ICR_DCDMIC_Pos                               2
#define UART_ICR_DSRMIC_Pos                               3
#define UART_ICR_RXIC_Pos                                 4
#define UART_ICR_TXIC_Pos                                 5
#define UART_ICR_RTIC_Pos                                 6
#define UART_ICR_FEIC_Pos                                 7
#define UART_ICR_PEIC_Pos                                 8
#define UART_ICR_BEIC_Pos                                 9
#define UART_ICR_OEIC_Pos                                 10

// Маски битовых полей
#define UART_ICR_RIMIC                                    ((uint32_t)0x00000001)
#define UART_ICR_CTSMIC                                   ((uint32_t)0x00000002)
#define UART_ICR_DCDMIC                                   ((uint32_t)0x00000004)
#define UART_ICR_DSRMIC                                   ((uint32_t)0x00000008)
#define UART_ICR_RXIC                                     ((uint32_t)0x00000010)
#define UART_ICR_TXIC                                     ((uint32_t)0x00000020)
#define UART_ICR_RTIC                                     ((uint32_t)0x00000040)
#define UART_ICR_FEIC                                     ((uint32_t)0x00000080)
#define UART_ICR_PEIC                                     ((uint32_t)0x00000100)
#define UART_ICR_BEIC                                     ((uint32_t)0x00000200)
#define UART_ICR_OEIC                                     ((uint32_t)0x00000400)

// Регистр DMACR
// Позиции битовых полей
#define UART_DMACR_RXDMAE_Pos                             0
#define UART_DMACR_TXDMAE_Pos                             1
#define UART_DMACR_DMAONERR_Pos                           2

// Маски битовых полей
#define UART_DMACR_RXDMAE                                 ((uint32_t)0x00000001)
#define UART_DMACR_TXDMAE                                 ((uint32_t)0x00000002)
#define UART_DMACR_DMAONERR                               ((uint32_t)0x00000004)

/* ----------------------------- Контроллер SSP ----------------------------- */

// Структура контроллера SSP
typedef struct
{
  __IO uint32_t CR0;
  __IO uint32_t CR1;
  __IO uint32_t DR;
  __IO uint32_t SR;
  __IO uint32_t CPSR;
  __IO uint32_t IMSC;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t ICR;
  __IO uint32_t DMACR;
} MDR_SSP_TypeDef;

// Регистр CR0
// Позиции битовых полей
#define SSP_CR0_DSS_Pos                                   0
#define SSP_CR0_FRF_Pos                                   4
#define SSP_CR0_SPO_Pos                                   6
#define SSP_CR0_SPH_Pos                                   7
#define SSP_CR0_SCR_Pos                                   8

// Маски битовых полей
#define SSP_CR0_DSS_Msk                                   ((uint32_t)0x0000000F)
#define SSP_CR0_FRF_Msk                                   ((uint32_t)0x00000030)
#define SSP_CR0_SPO                                       ((uint32_t)0x00000040)
#define SSP_CR0_SPH                                       ((uint32_t)0x00000080)
#define SSP_CR0_SCR_Msk                                   ((uint32_t)0x0000FF00)

// Регистр CR1
// Позиции битовых полей
#define SSP_CR1_LBM_Pos                                   0
#define SSP_CR1_SSE_Pos                                   1
#define SSP_CR1_MS_Pos                                    2
#define SSP_CR1_SOD_Pos                                   3

// Маски битовых полей
#define SSP_CR1_LBM                                       ((uint32_t)0x00000001)
#define SSP_CR1_SSE                                       ((uint32_t)0x00000002)
#define SSP_CR1_MS                                        ((uint32_t)0x00000004)
#define SSP_CR1_SOD                                       ((uint32_t)0x00000008)

// Регистр SR
// Позиции битовых полей
#define SSP_SR_TFE_Pos                                    0
#define SSP_SR_TNF_Pos                                    1
#define SSP_SR_RNE_Pos                                    2
#define SSP_SR_RFF_Pos                                    3
#define SSP_SR_BSY_Pos                                    4

// Маски битовых полей
#define SSP_SR_TFE                                        ((uint32_t)0x00000001)
#define SSP_SR_TNF                                        ((uint32_t)0x00000002)
#define SSP_SR_RNE                                        ((uint32_t)0x00000004)
#define SSP_SR_RFF                                        ((uint32_t)0x00000008)
#define SSP_SR_BSY                                        ((uint32_t)0x00000010)

// Регистр IMSC
// Позиции битовых полей
#define SSP_IMSC_RORIM_Pos                                0
#define SSP_IMSC_RTIM_Pos                                 1
#define SSP_IMSC_RXIM_Pos                                 2
#define SSP_IMSC_TXIM_Pos                                 3

// Маски битовых полей
#define SSP_IMSC_RORIM                                    ((uint32_t)0x00000001)
#define SSP_IMSC_RTIM                                     ((uint32_t)0x00000002)
#define SSP_IMSC_RXIM                                     ((uint32_t)0x00000004)
#define SSP_IMSC_TXIM                                     ((uint32_t)0x00000008)

// Регистр RIS
// Позиции битовых полей
#define SSP_RIS_RORRIS_Pos                                0
#define SSP_RIS_RTRIS_Pos                                 1
#define SSP_RIS_RXRIS_Pos                                 2
#define SSP_RIS_TXRIS_Pos                                 3

// Маски битовых полей
#define SSP_RIS_RORRIS                                    ((uint32_t)0x00000001)
#define SSP_RIS_RTRIS                                     ((uint32_t)0x00000002)
#define SSP_RIS_RXRIS                                     ((uint32_t)0x00000004)
#define SSP_RIS_TXRIS                                     ((uint32_t)0x00000008)

// Регистр MIS
// Позиции битовых полей
#define SSP_MIS_RORMIS_Pos                                0
#define SSP_MIS_RTMIS_Pos                                 1
#define SSP_MIS_RXMIS_Pos                                 2
#define SSP_MIS_TXMIS_Pos                                 3

// Маски битовых полей
#define SSP_MIS_RORMIS                                    ((uint32_t)0x00000001)
#define SSP_MIS_RTMIS                                     ((uint32_t)0x00000002)
#define SSP_MIS_RXMIS                                     ((uint32_t)0x00000004)
#define SSP_MIS_TXMIS                                     ((uint32_t)0x00000008)

// Регистр ICR
// Позиции битовых полей
#define SSP_ICR_RORIC_Pos                                 0
#define SSP_ICR_RTIC_Pos                                  1

// Маски битовых полей
#define SSP_ICR_RORIC                                     ((uint32_t)0x00000001)
#define SSP_ICR_RTIC                                      ((uint32_t)0x00000002)

// Регистр DMACR
// Позиции битовых полей
#define SSP_DMACR_RXDMAE_Pos                              0
#define SSP_DMACR_TXDMAE_Pos                              1

// Маски битовых полей
#define SSP_DMACR_RXDMAE                                  ((uint32_t)0x00000001)
#define SSP_DMACR_TXDMAE                                  ((uint32_t)0x00000002)

/* ----------------------------- Контроллер I2C ----------------------------- */

// Структура контроллера I2C
typedef struct
{
  __IO uint32_t PRL;
  __IO uint32_t PRH;
  __IO uint32_t CTR;
  __IO uint32_t RXD;
  __IO uint32_t STA;
  __IO uint32_t TXD;
  __IO uint32_t CMD;
} MDR_I2C_TypeDef;

// Регистр CTR
// Позиции битовых полей
#define I2C_CTR_S_I2C_Pos                                 5
#define I2C_CTR_EN_INT_Pos                                6
#define I2C_CTR_EN_I2C_Pos                                7

// Маски битовых полей
#define I2C_CTR_S_I2C                                     ((uint32_t)0x00000020)
#define I2C_CTR_EN_INT                                    ((uint32_t)0x00000040)
#define I2C_CTR_EN_I2C                                    ((uint32_t)0x00000080)

// Регистр STA
// Позиции битовых полей
#define I2C_STA_INT_Pos                                   0
#define I2C_STA_TR_PROG_Pos                               1
#define I2C_STA_LOST_ARB_Pos                              5
#define I2C_STA_BUSY_Pos                                  6
#define I2C_STA_RX_ACK_Pos                                7

// Маски битовых полей
#define I2C_STA_INT                                       ((uint32_t)0x00000001)
#define I2C_STA_TR_PROG                                   ((uint32_t)0x00000002)
#define I2C_STA_LOST_ARB                                  ((uint32_t)0x00000020)
#define I2C_STA_BUSY                                      ((uint32_t)0x00000040)
#define I2C_STA_RX_ACK                                    ((uint32_t)0x00000080)

// Регистр CMD
// Позиции битовых полей
#define I2C_CMD_CLRINT_Pos                                0
#define I2C_CMD_ACK_Pos                                   3
#define I2C_CMD_WR_Pos                                    4
#define I2C_CMD_RD_Pos                                    5
#define I2C_CMD_STOP_Pos                                  6
#define I2C_CMD_START_Pos                                 7

// Маски битовых полей
#define I2C_CMD_CLRINT                                    ((uint32_t)0x00000001)
#define I2C_CMD_ACK                                       ((uint32_t)0x00000008)
#define I2C_CMD_WR                                        ((uint32_t)0x00000010)
#define I2C_CMD_RD                                        ((uint32_t)0x00000020)
#define I2C_CMD_STOP                                      ((uint32_t)0x00000040)
#define I2C_CMD_START                                     ((uint32_t)0x00000080)

/* ----------------------- Детектор напряжения питания ---------------------- */

// Структура детектора напряжения питания
typedef struct
{
  __IO uint32_t PVDCS;
} MDR_POWER_TypeDef;

// Регистр PVDCS
// Позиции битовых полей
#define POWER_PVDCS_PVDEN_Pos                             0
#define POWER_PVDCS_PBLS_Pos                              1
#define POWER_PVDCS_PLS_Pos                               3
#define POWER_PVDCS_PVBD_Pos                              6
#define POWER_PVDCS_PVD_Pos                               7
#define POWER_PVDCS_IEPVBD_Pos                            8
#define POWER_PVDCS_IEPVD_Pos                             9
#define POWER_PVDCS_INVB_Pos                              10
#define POWER_PVDCS_INV_Pos                               11

// Маски битовых полей
#define POWER_PVDCS_PVDEN                                 ((uint32_t)0x00000001)
#define POWER_PVDCS_PBLS_Msk                              ((uint32_t)0x00000006)
#define POWER_PVDCS_PLS_Msk                               ((uint32_t)0x00000038)
#define POWER_PVDCS_PVBD                                  ((uint32_t)0x00000040)
#define POWER_PVDCS_PVD                                   ((uint32_t)0x00000080)
#define POWER_PVDCS_IEPVBD                                ((uint32_t)0x00000100)
#define POWER_PVDCS_IEPVD                                 ((uint32_t)0x00000200)
#define POWER_PVDCS_INVB                                  ((uint32_t)0x00000400)
#define POWER_PVDCS_INV                                   ((uint32_t)0x00000800)

/* ------------------------ Оконный сторожевой таймер ----------------------- */

// Структура оконного сторожевого таймера
typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CFR;
  __IO uint32_t SR;
} MDR_WWDG_TypeDef;

// Регистр CR
// Позиции битовых полей
#define WWDG_CR_T_Pos                                     0
#define WWDG_CR_WDGA_Pos                                  7

// Маски битовых полей
#define WWDG_CR_T_Msk                                     ((uint32_t)0x0000007F)
#define WWDG_CR_WDGA                                      ((uint32_t)0x00000080)

// Регистр CFR
// Позиции битовых полей
#define WWDG_CFR_W_Pos                                    0
#define WWDG_CFR_WGTB_Pos                                 7
#define WWDG_CFR_EWI_Pos                                  9

// Маски битовых полей
#define WWDG_CFR_W_Msk                                    ((uint32_t)0x0000007F)
#define WWDG_CFR_WGTB_Msk                                 ((uint32_t)0x00000180)
#define WWDG_CFR_EWI                                      ((uint32_t)0x00000200)

/* ---------------------- Независимый сторожевой таймер --------------------- */

// Структура независимого сторожевого таймера
typedef struct
{
  __IO uint32_t KR;
  __IO uint32_t PR;
  __IO uint32_t RLR;
  __IO uint32_t SR;
} MDR_IWDG_TypeDef;

// Регистр SR
// Позиции битовых полей
#define IWDG_SR_PVU_Pos                                   0
#define IWDG_SR_RVU_Pos                                   1

// Маски битовых полей
#define IWDG_SR_PVU                                       ((uint32_t)0x00000001)
#define IWDG_SR_RVU                                       ((uint32_t)0x00000002)

/* ------------------------ Таймер общего назначения ------------------------ */

// Структура таймера общего назначения
typedef struct
{
  __IO uint32_t CNT;
  __IO uint32_t PSG;
  __IO uint32_t ARR;
  __IO uint32_t CNTRL;
  __IO uint32_t CCR1;
  __IO uint32_t CCR2;
  __IO uint32_t CCR3;
  __IO uint32_t CCR4;
  __IO uint32_t CH1_CNTRL;
  __IO uint32_t CH2_CNTRL;
  __IO uint32_t CH3_CNTRL;
  __IO uint32_t CH4_CNTRL;
  __IO uint32_t CH1_CNTRL1;
  __IO uint32_t CH2_CNTRL1;
  __IO uint32_t CH3_CNTRL1;
  __IO uint32_t CH4_CNTRL1;
  __IO uint32_t CH1_DTG;
  __IO uint32_t CH2_DTG;
  __IO uint32_t CH3_DTG;
  __IO uint32_t CH4_DTG;
  __IO uint32_t BRKETR_CNTRL;
  __IO uint32_t STATUS;
  __IO uint32_t IE;
  __IO uint32_t DMA_RE;
  __IO uint32_t CH1_CNTRL2;
  __IO uint32_t CH2_CNTRL2;
  __IO uint32_t CH3_CNTRL2;
  __IO uint32_t CH4_CNTRL2;
  __IO uint32_t CCR11;
  __IO uint32_t CCR21;
  __IO uint32_t CCR31;
  __IO uint32_t CCR41;
} MDR_TIMER_TypeDef;

// Регистр CNTRL
// Позиции битовых полей
#define TIMER_CNTRL_CNT_EN_Pos                            0
#define TIMER_CNTRL_ARRB_EN_Pos                           1
#define TIMER_CNTRL_WR_CMPL_Pos                           2
#define TIMER_CNTRL_DIR_Pos                               3
#define TIMER_CNTRL_FDTS_Pos                              4
#define TIMER_CNTRL_CNT_MODE_Pos                          6
#define TIMER_CNTRL_EVENT_SEL_Pos                         8

// Маски битовых полей
#define TIMER_CNTRL_CNT_EN                                ((uint32_t)0x00000001)
#define TIMER_CNTRL_ARRB_EN                               ((uint32_t)0x00000002)
#define TIMER_CNTRL_WR_CMPL                               ((uint32_t)0x00000004)
#define TIMER_CNTRL_DIR                                   ((uint32_t)0x00000008)
#define TIMER_CNTRL_FDTS_Msk                              ((uint32_t)0x00000030)
#define TIMER_CNTRL_CNT_MODE_Msk                          ((uint32_t)0x000000C0)
#define TIMER_CNTRL_EVENT_SEL_Msk                         ((uint32_t)0x00000F00)

// Регистр CH_CNTRL
// Позиции битовых полей
#define TIMER_CH_CNTRL_CHFLTR_Pos                         0
#define TIMER_CH_CNTRL_CHSEL_Pos                          4
#define TIMER_CH_CNTRL_CHPSC_Pos                          6
#define TIMER_CH_CNTRL_OCCE_Pos                           8
#define TIMER_CH_CNTRL_OCCM_Pos                           9
#define TIMER_CH_CNTRL_BRKEN_Pos                          12
#define TIMER_CH_CNTRL_ETREN_Pos                          13
#define TIMER_CH_CNTRL_WR_CMPL_Pos                        14
#define TIMER_CH_CNTRL_CAP_NPWM_Pos                       15

// Маски битовых полей
#define TIMER_CH_CNTRL_CHFLTR_Msk                         ((uint32_t)0x0000000F)
#define TIMER_CH_CNTRL_CHSEL_Msk                          ((uint32_t)0x00000030)
#define TIMER_CH_CNTRL_CHPSC_Msk                          ((uint32_t)0x000000C0)
#define TIMER_CH_CNTRL_OCCE                               ((uint32_t)0x00000100)
#define TIMER_CH_CNTRL_OCCM_Msk                           ((uint32_t)0x00000E00)
#define TIMER_CH_CNTRL_BRKEN                              ((uint32_t)0x00001000)
#define TIMER_CH_CNTRL_ETREN                              ((uint32_t)0x00002000)
#define TIMER_CH_CNTRL_WR_CMPL                            ((uint32_t)0x00004000)
#define TIMER_CH_CNTRL_CAP_NPWM                           ((uint32_t)0x00008000)

// Регистр CH_CNTRL1
// Позиции битовых полей
#define TIMER_CH_CNTRL1_SELOE_Pos                         0
#define TIMER_CH_CNTRL1_SELO_Pos                          2
#define TIMER_CH_CNTRL1_INV_Pos                           4
#define TIMER_CH_CNTRL1_NSELOE_Pos                        8
#define TIMER_CH_CNTRL1_NSELO_Pos                         10
#define TIMER_CH_CNTRL1_NINV_Pos                          12

// Маски битовых полей
#define TIMER_CH_CNTRL1_SELOE_Msk                         ((uint32_t)0x00000003)
#define TIMER_CH_CNTRL1_SELO_Msk                          ((uint32_t)0x0000000C)
#define TIMER_CH_CNTRL1_INV                               ((uint32_t)0x00000010)
#define TIMER_CH_CNTRL1_NSELOE_Msk                        ((uint32_t)0x00000300)
#define TIMER_CH_CNTRL1_NSELO_Msk                         ((uint32_t)0x00000C00)
#define TIMER_CH_CNTRL1_NINV                              ((uint32_t)0x00001000)

// Регистр CH_DTG
// Позиции битовых полей
#define TIMER_CH_DTGX_Pos                                 0
#define TIMER_CH_DTG_EDTS_Pos                             4
#define TIMER_CH_DTG_Pos                                  8

// Маски битовых полей
#define TIMER_CH_DTGX_Msk                                 ((uint32_t)0x0000000F)
#define TIMER_CH_DTG_EDTS                                 ((uint32_t)0x00000010)
#define TIMER_CH_DTG_Msk                                  ((uint32_t)0x0000FF00)

// Регистр BRKETR_CNTRL
// Позиции битовых полей
#define TIMER_BRKETR_CNTRL_BRK_INV_Pos                    0
#define TIMER_BRKETR_CNTRL_ETR_INV_Pos                    1
#define TIMER_BRKETR_CNTRL_ETR_PSC_Pos                    2
#define TIMER_BRKETR_CNTRL_ETR_FILTER_Pos                 4

// Маски битовых полей
#define TIMER_BRKETR_CNTRL_BRK_INV                        ((uint32_t)0x00000001)
#define TIMER_BRKETR_CNTRL_ETR_INV                        ((uint32_t)0x00000002)
#define TIMER_BRKETR_CNTRL_ETR_PSC_Msk                    ((uint32_t)0x0000000C)
#define TIMER_BRKETR_CNTRL_ETR_FILTER_Msk                 ((uint32_t)0x000000F0)

// Регистр STATUS
// Позиции битовых полей
#define TIMER_STATUS_CNT_ZERO_EVENT_Pos                   0
#define TIMER_STATUS_CNT_ARR_EVENT_Pos                    1
#define TIMER_STATUS_ETR_RE_EVENT_Pos                     2
#define TIMER_STATUS_ETR_FE_EVENT_Pos                     3
#define TIMER_STATUS_BRK_EVENT_Pos                        4
#define TIMER_STATUS_CCR_CAP_EVENT_Pos                    5
#define TIMER_STATUS_CCR_REF_EVENT_Pos                    9
#define TIMER_STATUS_CCR1_CAP_EVENT_Pos                   13

// Маски битовых полей
#define TIMER_STATUS_CNT_ZERO_EVENT                       ((uint32_t)0x00000001)
#define TIMER_STATUS_CNT_ARR_EVENT                        ((uint32_t)0x00000002)
#define TIMER_STATUS_ETR_RE_EVENT                         ((uint32_t)0x00000004)
#define TIMER_STATUS_ETR_FE_EVENT                         ((uint32_t)0x00000008)
#define TIMER_STATUS_BRK_EVENT                            ((uint32_t)0x00000010)
#define TIMER_STATUS_CCR_CAP_EVENT_Msk                    ((uint32_t)0x000001E0)
#define TIMER_STATUS_CCR_REF_EVENT_Msk                    ((uint32_t)0x00001E00)
#define TIMER_STATUS_CCR1_CAP_EVENT_Msk                   ((uint32_t)0x0001E000)

// Регистр IE
// Позиции битовых полей
#define TIMER_IE_CNT_ZERO_EVENT_IE_Pos                    0
#define TIMER_IE_CNT_ARR_EVENT_IE_Pos                     1
#define TIMER_IE_ETR_RE_EVENT_IE_Pos                      2
#define TIMER_IE_ETR_FE_EVENT_IE_Pos                      3
#define TIMER_IE_BRK_EVENT_IE_Pos                         4
#define TIMER_IE_CCR_CAP_EVENT_IE_Pos                     5
#define TIMER_IE_CCR_REF_EVENT_IE_Pos                     9
#define TIMER_IE_CCR1_CAP_EVENT_IE_Pos                    13

// Маски битовых полей
#define TIMER_IE_CNT_ZERO_EVENT_IE                        ((uint32_t)0x00000001)
#define TIMER_IE_CNT_ARR_EVENT_IE                         ((uint32_t)0x00000002)
#define TIMER_IE_ETR_RE_EVENT_IE                          ((uint32_t)0x00000004)
#define TIMER_IE_ETR_FE_EVENT_IE                          ((uint32_t)0x00000008)
#define TIMER_IE_BRK_EVENT_IE                             ((uint32_t)0x00000010)
#define TIMER_IE_CCR_CAP_EVENT_IE_Msk                     ((uint32_t)0x000001E0)
#define TIMER_IE_CCR_REF_EVENT_IE_Msk                     ((uint32_t)0x00001E00)
#define TIMER_IE_CCR1_CAP_EVENT_IE_Msk                    ((uint32_t)0x0001E000)

// Регистр DMA_RE
// Позиции битовых полей
#define TIMER_DMA_RE_CNT_ZERO_EVENT_RE_Pos                0
#define TIMER_DMA_RE_CNT_ARR_EVENT_RE_Pos                 1
#define TIMER_DMA_RE_ETR_RE_EVENT_RE_Pos                  2
#define TIMER_DMA_RE_ETR_FE_EVENT_RE_Pos                  3
#define TIMER_DMA_RE_BRK_EVENT_RE_Pos                     4
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_Pos                 5
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_Pos                 9
#define TIMER_DMA_RE_CCR1_CAP_EVENT_RE_Pos                13

// Маски битовых полей
#define TIMER_DMA_RE_CNT_ZERO_EVENT_RE                    ((uint32_t)0x00000001)
#define TIMER_DMA_RE_CNT_ARR_EVENT_RE                     ((uint32_t)0x00000002)
#define TIMER_DMA_RE_ETR_RE_EVENT_RE                      ((uint32_t)0x00000004)
#define TIMER_DMA_RE_ETR_FE_EVENT_RE                      ((uint32_t)0x00000008)
#define TIMER_DMA_RE_BRK_EVENT_RE                         ((uint32_t)0x00000010)
#define TIMER_DMA_RE_CCR_CAP_EVENT_RE_Msk                 ((uint32_t)0x000001E0)
#define TIMER_DMA_RE_CCR_REF_EVENT_RE_Msk                 ((uint32_t)0x00001E00)
#define TIMER_DMA_RE_CCR1_CAP_EVENT_RE_Msk                ((uint32_t)0x0001E000)

// Регистр CH_CNTRL2
// Позиции битовых полей
#define TIMER_CH_CNTRL2_CHSEL1_Pos                        0
#define TIMER_CH_CNTRL2_CCR1_EN_Pos                       2
#define TIMER_CH_CNTRL2_CCRRLD_Pos                        3

// Маски битовых полей
#define TIMER_CH_CNTRL2_CHSEL1_Msk                        ((uint32_t)0x00000003)
#define TIMER_CH_CNTRL2_CCR1_EN                           ((uint32_t)0x00000004)
#define TIMER_CH_CNTRL2_CCRRLD                            ((uint32_t)0x00000008)

/* -------------------- Аналого-цифровой преобразователь -------------------- */

// Структура аналого-цифрового преобразователя
typedef struct
{
  __IO uint32_t ADC1_CFG;
  __IO uint32_t ADC2_CFG;
  __IO uint32_t ADC1_H_LEVEL;
  __IO uint32_t ADC2_H_LEVEL;
  __IO uint32_t ADC1_L_LEVEL;
  __IO uint32_t ADC2_L_LEVEL;
  __IO uint32_t ADC1_RESULT;
  __IO uint32_t ADC2_RESULT;
  __IO uint32_t ADC1_STATUS;
  __IO uint32_t ADC2_STATUS;
  __IO uint32_t ADC1_CHSEL;
  __IO uint32_t ADC2_CHSEL;
} MDR_ADC_TypeDef;

// Регистр ADC1_CFG
// Позиции битовых полей
#define ADC1_CFG_REG_ADON_Pos                             0
#define ADC1_CFG_REG_GO_Pos                               1
#define ADC1_CFG_REG_CLKS_Pos                             2
#define ADC1_CFG_REG_SAMPLE_Pos                           3
#define ADC1_CFG_REG_CHS_Pos                              4
#define ADC1_CFG_REG_CHCH_Pos                             9
#define ADC1_CFG_REG_RNGC_Pos                             10
#define ADC1_CFG_M_REF_Pos                                11
#define ADC1_CFG_REG_DIVCLK_Pos                           12
#define ADC1_CFG_SYNC_CONVER_Pos                          16
#define ADC1_CFG_TS_EN_Pos                                17
#define ADC1_CFG_TS_BUF_EN_Pos                            18
#define ADC1_CFG_SEL_TS_Pos                               19
#define ADC1_CFG_SEL_VREF_Pos                             20
#define ADC1_CFG_TR_Pos                                   21
#define ADC1_CFG_DELAY_GO_Pos                             25
#define ADC1_CFG_DELAY_ADC_Pos                            28

// Маски битовых полей
#define ADC1_CFG_REG_ADON                                 ((uint32_t)0x00000001)
#define ADC1_CFG_REG_GO                                   ((uint32_t)0x00000002)
#define ADC1_CFG_REG_CLKS                                 ((uint32_t)0x00000004)
#define ADC1_CFG_REG_SAMPLE                               ((uint32_t)0x00000008)
#define ADC1_CFG_REG_CHS_Msk                              ((uint32_t)0x000001F0)
#define ADC1_CFG_REG_CHCH                                 ((uint32_t)0x00000200)
#define ADC1_CFG_REG_RNGC                                 ((uint32_t)0x00000400)
#define ADC1_CFG_M_REF                                    ((uint32_t)0x00000800)
#define ADC1_CFG_REG_DIVCLK_Msk                           ((uint32_t)0x0000F000)
#define ADC1_CFG_SYNC_CONVER                              ((uint32_t)0x00010000)
#define ADC1_CFG_TS_EN                                    ((uint32_t)0x00020000)
#define ADC1_CFG_TS_BUF_EN                                ((uint32_t)0x00040000)
#define ADC1_CFG_SEL_TS                                   ((uint32_t)0x00080000)
#define ADC1_CFG_SEL_VREF                                 ((uint32_t)0x00100000)
#define ADC1_CFG_TR_Msk                                   ((uint32_t)0x01E00000)
#define ADC1_CFG_DELAY_GO_Msk                             ((uint32_t)0x0E000000)
#define ADC1_CFG_DELAY_ADC_Msk                            ((uint32_t)0xF0000000)

// Регистр ADC2_CFG
// Позиции битовых полей
#define ADC2_CFG_REG_ADON_Pos                             0
#define ADC2_CFG_REG_GO_Pos                               1
#define ADC2_CFG_REG_CLKS_Pos                             2
#define ADC2_CFG_REG_SAMPLE_Pos                           3
#define ADC2_CFG_REG_CHS_Pos                              4
#define ADC2_CFG_REG_CHCH_Pos                             9
#define ADC2_CFG_REG_RNGC_Pos                             10
#define ADC2_CFG_M_REF_Pos                                11
#define ADC2_CFG_REG_DIVCLK_Pos                           12
#define ADC2_CFG_ADC1_OP_Pos                              17
#define ADC2_CFG_ADC2_OP_Pos                              18
#define ADC2_CFG_DELAY_GO_Pos                             25

// Маски битовых полей
#define ADC2_CFG_REG_ADON                                 ((uint32_t)0x00000001)
#define ADC2_CFG_REG_GO                                   ((uint32_t)0x00000002)
#define ADC2_CFG_REG_CLKS                                 ((uint32_t)0x00000004)
#define ADC2_CFG_REG_SAMPLE                               ((uint32_t)0x00000008)
#define ADC2_CFG_REG_CHS_Msk                              ((uint32_t)0x000001F0)
#define ADC2_CFG_REG_CHCH                                 ((uint32_t)0x00000200)
#define ADC2_CFG_REG_RNGC                                 ((uint32_t)0x00000400)
#define ADC2_CFG_M_REF                                    ((uint32_t)0x00000800)
#define ADC2_CFG_REG_DIVCLK_Msk                           ((uint32_t)0x0000F000)
#define ADC2_CFG_ADC1_OP                                  ((uint32_t)0x00020000)
#define ADC2_CFG_ADC2_OP                                  ((uint32_t)0x00040000)
#define ADC2_CFG_DELAY_GO_Msk                             ((uint32_t)0x0E000000)

// Регистры RESULT
// Позиции битовых полей
#define ADC_RESULT_Pos                                    0
#define ADC_RESULT_CHANNEL_Pos                            16

// Маски битовых полей
#define ADC_RESULT_Msk                                    ((uint32_t)0x00000FFF)
#define ADC_RESULT_CHANNEL_Msk                            ((uint32_t)0x001F0000)

// Регистры STATUS
// Позиции битовых полей
#define ADC_STATUS_FLG_REG_OVERWRITE_Pos                  0
#define ADC_STATUS_FLG_REG_AWOIFEN_Pos                    1
#define ADC_STATUS_FLG_REG_EOCIF_Pos                      2
#define ADC_STATUS_AWOIF_IE_Pos                           3
#define ADC_STATUS_ECOIF_IE_Pos                           4

// Маски битовых полей
#define ADC_STATUS_FLG_REG_OVERWRITE                      ((uint32_t)0x00000001)
#define ADC_STATUS_FLG_REG_AWOIFEN                        ((uint32_t)0x00000002)
#define ADC_STATUS_FLG_REG_EOCIF                          ((uint32_t)0x00000004)
#define ADC_STATUS_AWOIF_IE                               ((uint32_t)0x00000008)
#define ADC_STATUS_ECOIF_IE                               ((uint32_t)0x00000010)

/* -------------------- Цифро-аналоговый преобразователь -------------------- */

// Структура цифро-аналогового преобразователя
typedef struct
{
  __IO uint32_t CFG;
  __IO uint32_t DAC1_DATA;
  __IO uint32_t DAC2_DATA;
} MDR_DAC_TypeDef;

// Регистр CFG
// Позиции битовых полей
#define DAC_CFG_M_REF0_Pos                                0
#define DAC_CFG_M_REF1_Pos                                1
#define DAC_CFG_ON_DAC0_Pos                               2
#define DAC_CFG_ON_DAC1_Pos                               3
#define DAC_CFG_SYNC_A_Pos                                4

// Маски битовых полей
#define DAC_CFG_M_REF0                                    ((uint32_t)0x00000001)
#define DAC_CFG_M_REF1                                    ((uint32_t)0x00000002)
#define DAC_CFG_ON_DAC0                                   ((uint32_t)0x00000004)
#define DAC_CFG_ON_DAC1                                   ((uint32_t)0x00000008)
#define DAC_CFG_SYNC_A                                    ((uint32_t)0x00000010)

// Регистр DAC1_DATA
// Позиции битовых полей
#define DAC1_DATA_DAC0DATA_Pos                            0
#define DAC1_DATA_DAC1DATA_Pos                            16

// Маски битовых полей
#define DAC1_DATA_DAC0DATA_Msk                            ((uint32_t)0x00000FFF)
#define DAC1_DATA_DAC1DATA_Msk                            ((uint32_t)0x0FFF0000)

// Регистр DAC2_DATA
// Позиции битовых полей
#define DAC2_DATA_DAC1DATA_Pos                            0
#define DAC2_DATA_DAC0DATA_Pos                            16

// Маски битовых полей
#define DAC2_DATA_DAC1DATA_Msk                            ((uint32_t)0x00000FFF)
#define DAC2_DATA_DAC0DATA_Msk                            ((uint32_t)0x0FFF0000)

/* ---------------------- Контреллер схемы компаратора ---------------------- */

// Структура контроллера схемы компаратора
typedef struct
{
  __IO uint32_t CFG;
  __IO uint32_t RESULT;
  __IO uint32_t RESULT_LATCH;
} MDR_COMP_TypeDef;

// Регистр CFG
// Позиции битовых полей
#define COMP_CFG_ON_Pos                                   0
#define COMP_CFG_CVRR_Pos                                 1
#define COMP_CFG_CVRSS_Pos                                2
#define COMP_CFG_CVREN_Pos                                3
#define COMP_CFG_CVR_Pos                                  4
#define COMP_CFG_CREF_Pos                                 8
#define COMP_CFG_CCH_Pos                                  9
#define COMP_CFG_INV_Pos                                  11
#define COMP_CFG_READY_Pos                                12
#define COMP_CFG_CMPIE_Pos                                13

// Маски битовых полей
#define COMP_CFG_ON                                       ((uint32_t)0x00000001)
#define COMP_CFG_CVRR                                     ((uint32_t)0x00000002)
#define COMP_CFG_CVRSS                                    ((uint32_t)0x00000004)
#define COMP_CFG_CVREN                                    ((uint32_t)0x00000008)
#define COMP_CFG_CVR_Msk                                  ((uint32_t)0x000000F0)
#define COMP_CFG_CREF                                     ((uint32_t)0x00000100)
#define COMP_CFG_CCH_Msk                                  ((uint32_t)0x00000600)
#define COMP_CFG_INV                                      ((uint32_t)0x00000800)
#define COMP_CFG_READY                                    ((uint32_t)0x00001000)
#define COMP_CFG_CMPIE                                    ((uint32_t)0x00002000)

// Регистр RESULT
// Позиции битовых полей
#define COMP_RESULT_RSLT_SY_Pos                           0
#define COMP_RESULT_RSLT_AS_Pos                           1
#define COMP_RESULT_RST_LCH_Pos                           2

// Маски битовых полей
#define COMP_RESULT_RSLT_SY                               ((uint32_t)0x00000001)
#define COMP_RESULT_RSLT_AS                               ((uint32_t)0x00000002)
#define COMP_RESULT_RST_LCH                               ((uint32_t)0x00000004)

/* --------------------------- Порты ввода-вывода --------------------------- */

// Структура портов ввода-вывода
typedef struct
{
  __IO uint32_t RXTX;
  __IO uint32_t OE;
  __IO uint32_t FUNC;
  __IO uint32_t ANALOG;
  __IO uint32_t PULL;
  __IO uint32_t PD;
  __IO uint32_t PWR;
  __IO uint32_t GFEN;
} MDR_PORT_TypeDef;

// Регистр RXTX
// Позиции битовых полей
#define PORT_RXTX0_Pos                                    0
#define PORT_RXTX1_Pos                                    1
#define PORT_RXTX2_Pos                                    2
#define PORT_RXTX3_Pos                                    3
#define PORT_RXTX4_Pos                                    4
#define PORT_RXTX5_Pos                                    5
#define PORT_RXTX6_Pos                                    6
#define PORT_RXTX7_Pos                                    7
#define PORT_RXTX8_Pos                                    8
#define PORT_RXTX9_Pos                                    9
#define PORT_RXTX10_Pos                                   10
#define PORT_RXTX11_Pos                                   11
#define PORT_RXTX12_Pos                                   12
#define PORT_RXTX13_Pos                                   13
#define PORT_RXTX14_Pos                                   14
#define PORT_RXTX15_Pos                                   15

// Маски битовых полей
#define PORT_RXTX0_Msk                                    ((uint32_t)0x00000001)
#define PORT_RXTX1_Msk                                    ((uint32_t)0x00000002)
#define PORT_RXTX2_Msk                                    ((uint32_t)0x00000004)
#define PORT_RXTX3_Msk                                    ((uint32_t)0x00000008)
#define PORT_RXTX4_Msk                                    ((uint32_t)0x00000010)
#define PORT_RXTX5_Msk                                    ((uint32_t)0x00000020)
#define PORT_RXTX6_Msk                                    ((uint32_t)0x00000040)
#define PORT_RXTX7_Msk                                    ((uint32_t)0x00000080)
#define PORT_RXTX8_Msk                                    ((uint32_t)0x00000100)
#define PORT_RXTX9_Msk                                    ((uint32_t)0x00000200)
#define PORT_RXTX10_Msk                                   ((uint32_t)0x00000400)
#define PORT_RXTX11_Msk                                   ((uint32_t)0x00000800)
#define PORT_RXTX12_Msk                                   ((uint32_t)0x00001000)
#define PORT_RXTX13_Msk                                   ((uint32_t)0x00002000)
#define PORT_RXTX14_Msk                                   ((uint32_t)0x00004000)
#define PORT_RXTX15_Msk                                   ((uint32_t)0x00008000)

// Регистр OE
// Позиции битовых полей
#define PORT_OE0_Pos                                      0
#define PORT_OE1_Pos                                      1
#define PORT_OE2_Pos                                      2
#define PORT_OE3_Pos                                      3
#define PORT_OE4_Pos                                      4
#define PORT_OE5_Pos                                      5
#define PORT_OE6_Pos                                      6
#define PORT_OE7_Pos                                      7
#define PORT_OE8_Pos                                      8
#define PORT_OE9_Pos                                      9
#define PORT_OE10_Pos                                     10
#define PORT_OE11_Pos                                     11
#define PORT_OE12_Pos                                     12
#define PORT_OE13_Pos                                     13
#define PORT_OE14_Pos                                     14
#define PORT_OE15_Pos                                     15

// Маски битовых полей
#define PORT_OE0_Msk                                      ((uint32_t)0x00000001)
#define PORT_OE1_Msk                                      ((uint32_t)0x00000002)
#define PORT_OE2_Msk                                      ((uint32_t)0x00000004)
#define PORT_OE3_Msk                                      ((uint32_t)0x00000008)
#define PORT_OE4_Msk                                      ((uint32_t)0x00000010)
#define PORT_OE5_Msk                                      ((uint32_t)0x00000020)
#define PORT_OE6_Msk                                      ((uint32_t)0x00000040)
#define PORT_OE7_Msk                                      ((uint32_t)0x00000080)
#define PORT_OE8_Msk                                      ((uint32_t)0x00000100)
#define PORT_OE9_Msk                                      ((uint32_t)0x00000200)
#define PORT_OE10_Msk                                     ((uint32_t)0x00000400)
#define PORT_OE11_Msk                                     ((uint32_t)0x00000800)
#define PORT_OE12_Msk                                     ((uint32_t)0x00001000)
#define PORT_OE13_Msk                                     ((uint32_t)0x00002000)
#define PORT_OE14_Msk                                     ((uint32_t)0x00004000)
#define PORT_OE15_Msk                                     ((uint32_t)0x00008000)

// Регистр FUNC
// Позиции битовых полей
#define PORT_FUNC0_Pos                                    0
#define PORT_FUNC1_Pos                                    2
#define PORT_FUNC2_Pos                                    4
#define PORT_FUNC3_Pos                                    6
#define PORT_FUNC4_Pos                                    8
#define PORT_FUNC5_Pos                                    10
#define PORT_FUNC6_Pos                                    12
#define PORT_FUNC7_Pos                                    14
#define PORT_FUNC8_Pos                                    16
#define PORT_FUNC9_Pos                                    18
#define PORT_FUNC10_Pos                                   20
#define PORT_FUNC11_Pos                                   22
#define PORT_FUNC12_Pos                                   24
#define PORT_FUNC13_Pos                                   26
#define PORT_FUNC14_Pos                                   28
#define PORT_FUNC15_Pos                                   30

// Маски битовых полей
#define PORT_FUNC0_Msk                                    ((uint32_t)0x00000003)
#define PORT_FUNC1_Msk                                    ((uint32_t)0x0000000C)
#define PORT_FUNC2_Msk                                    ((uint32_t)0x00000030)
#define PORT_FUNC3_Msk                                    ((uint32_t)0x000000C0)
#define PORT_FUNC4_Msk                                    ((uint32_t)0x00000300)
#define PORT_FUNC5_Msk                                    ((uint32_t)0x00000C00)
#define PORT_FUNC6_Msk                                    ((uint32_t)0x00003000)
#define PORT_FUNC7_Msk                                    ((uint32_t)0x0000C000)
#define PORT_FUNC8_Msk                                    ((uint32_t)0x00030000)
#define PORT_FUNC9_Msk                                    ((uint32_t)0x000C0000)
#define PORT_FUNC10_Msk                                   ((uint32_t)0x00300000)
#define PORT_FUNC11_Msk                                   ((uint32_t)0x00C00000)
#define PORT_FUNC12_Msk                                   ((uint32_t)0x03000000)
#define PORT_FUNC13_Msk                                   ((uint32_t)0x0C000000)
#define PORT_FUNC14_Msk                                   ((uint32_t)0x30000000)
#define PORT_FUNC15_Msk                                   ((uint32_t)0xC0000000)

// Регистр ANALOG
// Позиции битовых полей
#define PORT_ANALOG0_Pos                                  0
#define PORT_ANALOG1_Pos                                  1
#define PORT_ANALOG2_Pos                                  2
#define PORT_ANALOG3_Pos                                  3
#define PORT_ANALOG4_Pos                                  4
#define PORT_ANALOG5_Pos                                  5
#define PORT_ANALOG6_Pos                                  6
#define PORT_ANALOG7_Pos                                  7
#define PORT_ANALOG8_Pos                                  8
#define PORT_ANALOG9_Pos                                  9
#define PORT_ANALOG10_Pos                                 10
#define PORT_ANALOG11_Pos                                 11
#define PORT_ANALOG12_Pos                                 12
#define PORT_ANALOG13_Pos                                 13
#define PORT_ANALOG14_Pos                                 14
#define PORT_ANALOG15_Pos                                 15

// Маски битовых полей
#define PORT_ANALOG0_Msk                                  ((uint32_t)0x00000001)
#define PORT_ANALOG1_Msk                                  ((uint32_t)0x00000002)
#define PORT_ANALOG2_Msk                                  ((uint32_t)0x00000004)
#define PORT_ANALOG3_Msk                                  ((uint32_t)0x00000008)
#define PORT_ANALOG4_Msk                                  ((uint32_t)0x00000010)
#define PORT_ANALOG5_Msk                                  ((uint32_t)0x00000020)
#define PORT_ANALOG6_Msk                                  ((uint32_t)0x00000040)
#define PORT_ANALOG7_Msk                                  ((uint32_t)0x00000080)
#define PORT_ANALOG8_Msk                                  ((uint32_t)0x00000100)
#define PORT_ANALOG9_Msk                                  ((uint32_t)0x00000200)
#define PORT_ANALOG10_Msk                                 ((uint32_t)0x00000400)
#define PORT_ANALOG11_Msk                                 ((uint32_t)0x00000800)
#define PORT_ANALOG12_Msk                                 ((uint32_t)0x00001000)
#define PORT_ANALOG13_Msk                                 ((uint32_t)0x00002000)
#define PORT_ANALOG14_Msk                                 ((uint32_t)0x00004000)
#define PORT_ANALOG15_Msk                                 ((uint32_t)0x00008000)

// Регистр PULL
// Позиции битовых полей
#define PORT_PULL_DOWN0_Pos                               0
#define PORT_PULL_DOWN1_Pos                               1
#define PORT_PULL_DOWN2_Pos                               2
#define PORT_PULL_DOWN3_Pos                               3
#define PORT_PULL_DOWN4_Pos                               4
#define PORT_PULL_DOWN5_Pos                               5
#define PORT_PULL_DOWN6_Pos                               6
#define PORT_PULL_DOWN7_Pos                               7
#define PORT_PULL_DOWN8_Pos                               8
#define PORT_PULL_DOWN9_Pos                               9
#define PORT_PULL_DOWN10_Pos                              10
#define PORT_PULL_DOWN11_Pos                              11
#define PORT_PULL_DOWN12_Pos                              12
#define PORT_PULL_DOWN13_Pos                              13
#define PORT_PULL_DOWN14_Pos                              14
#define PORT_PULL_DOWN15_Pos                              15

#define PORT_PULL_UP0_Pos                                 16
#define PORT_PULL_UP1_Pos                                 17
#define PORT_PULL_UP2_Pos                                 18
#define PORT_PULL_UP3_Pos                                 19
#define PORT_PULL_UP4_Pos                                 20
#define PORT_PULL_UP5_Pos                                 21
#define PORT_PULL_UP6_Pos                                 22
#define PORT_PULL_UP7_Pos                                 23
#define PORT_PULL_UP8_Pos                                 24
#define PORT_PULL_UP9_Pos                                 25
#define PORT_PULL_UP10_Pos                                26
#define PORT_PULL_UP11_Pos                                27
#define PORT_PULL_UP12_Pos                                28
#define PORT_PULL_UP13_Pos                                29
#define PORT_PULL_UP14_Pos                                30
#define PORT_PULL_UP15_Pos                                31

// Маски битовых полей
#define PORT_PULL_DOWN_Msk                                ((uint32_t)0x0000FFFF)
#define PORT_PULL_DOWN0_Msk                               ((uint32_t)0x00000001)
#define PORT_PULL_DOWN1_Msk                               ((uint32_t)0x00000002)
#define PORT_PULL_DOWN2_Msk                               ((uint32_t)0x00000004)
#define PORT_PULL_DOWN3_Msk                               ((uint32_t)0x00000008)
#define PORT_PULL_DOWN4_Msk                               ((uint32_t)0x00000010)
#define PORT_PULL_DOWN5_Msk                               ((uint32_t)0x00000020)
#define PORT_PULL_DOWN6_Msk                               ((uint32_t)0x00000040)
#define PORT_PULL_DOWN7_Msk                               ((uint32_t)0x00000080)
#define PORT_PULL_DOWN8_Msk                               ((uint32_t)0x00000100)
#define PORT_PULL_DOWN9_Msk                               ((uint32_t)0x00000200)
#define PORT_PULL_DOWN10_Msk                              ((uint32_t)0x00000400)
#define PORT_PULL_DOWN11_Msk                              ((uint32_t)0x00000800)
#define PORT_PULL_DOWN12_Msk                              ((uint32_t)0x00001000)
#define PORT_PULL_DOWN13_Msk                              ((uint32_t)0x00002000)
#define PORT_PULL_DOWN14_Msk                              ((uint32_t)0x00004000)
#define PORT_PULL_DOWN15_Msk                              ((uint32_t)0x00008000)

#define PORT_PULL_UP_Msk                                  ((uint32_t)0xFFFF0000)
#define PORT_PULL_UP0_Msk                                 ((uint32_t)0x00010000)
#define PORT_PULL_UP1_Msk                                 ((uint32_t)0x00020000)
#define PORT_PULL_UP2_Msk                                 ((uint32_t)0x00040000)
#define PORT_PULL_UP3_Msk                                 ((uint32_t)0x00080000)
#define PORT_PULL_UP4_Msk                                 ((uint32_t)0x00100000)
#define PORT_PULL_UP5_Msk                                 ((uint32_t)0x00200000)
#define PORT_PULL_UP6_Msk                                 ((uint32_t)0x00400000)
#define PORT_PULL_UP7_Msk                                 ((uint32_t)0x00800000)
#define PORT_PULL_UP8_Msk                                 ((uint32_t)0x01000000)
#define PORT_PULL_UP9_Msk                                 ((uint32_t)0x02000000)
#define PORT_PULL_UP10_Msk                                ((uint32_t)0x04000000)
#define PORT_PULL_UP11_Msk                                ((uint32_t)0x08000000)
#define PORT_PULL_UP12_Msk                                ((uint32_t)0x10000000)
#define PORT_PULL_UP13_Msk                                ((uint32_t)0x20000000)
#define PORT_PULL_UP14_Msk                                ((uint32_t)0x40000000)
#define PORT_PULL_UP15_Msk                                ((uint32_t)0x80000000)

// Регистр PD
// Позиции битовых полей
#define PORT_PD0_Pos                                      0
#define PORT_PD1_Pos                                      1
#define PORT_PD2_Pos                                      2
#define PORT_PD3_Pos                                      3
#define PORT_PD4_Pos                                      4
#define PORT_PD5_Pos                                      5
#define PORT_PD6_Pos                                      6
#define PORT_PD7_Pos                                      7
#define PORT_PD8_Pos                                      8
#define PORT_PD9_Pos                                      9
#define PORT_PD10_Pos                                     10
#define PORT_PD11_Pos                                     11
#define PORT_PD12_Pos                                     12
#define PORT_PD13_Pos                                     13
#define PORT_PD14_Pos                                     14
#define PORT_PD15_Pos                                     15

#define PORT_SHM0_Pos                                     16
#define PORT_SHM1_Pos                                     17
#define PORT_SHM2_Pos                                     18
#define PORT_SHM3_Pos                                     19
#define PORT_SHM4_Pos                                     20
#define PORT_SHM5_Pos                                     21
#define PORT_SHM6_Pos                                     22
#define PORT_SHM7_Pos                                     23
#define PORT_SHM8_Pos                                     24
#define PORT_SHM9_Pos                                     25
#define PORT_SHM10_Pos                                    26
#define PORT_SHM11_Pos                                    27
#define PORT_SHM12_Pos                                    28
#define PORT_SHM13_Pos                                    29
#define PORT_SHM14_Pos                                    30
#define PORT_SHM15_Pos                                    31

// Маски битовых полей
#define PORT_PD_Msk                                       ((uint32_t)0x0000FFFF)
#define PORT_PD0_Msk                                      ((uint32_t)0x00000001)
#define PORT_PD1_Msk                                      ((uint32_t)0x00000002)
#define PORT_PD2_Msk                                      ((uint32_t)0x00000004)
#define PORT_PD3_Msk                                      ((uint32_t)0x00000008)
#define PORT_PD4_Msk                                      ((uint32_t)0x00000010)
#define PORT_PD5_Msk                                      ((uint32_t)0x00000020)
#define PORT_PD6_Msk                                      ((uint32_t)0x00000040)
#define PORT_PD7_Msk                                      ((uint32_t)0x00000080)
#define PORT_PD8_Msk                                      ((uint32_t)0x00000100)
#define PORT_PD9_Msk                                      ((uint32_t)0x00000200)
#define PORT_PD10_Msk                                     ((uint32_t)0x00000400)
#define PORT_PD11_Msk                                     ((uint32_t)0x00000800)
#define PORT_PD12_Msk                                     ((uint32_t)0x00001000)
#define PORT_PD13_Msk                                     ((uint32_t)0x00002000)
#define PORT_PD14_Msk                                     ((uint32_t)0x00004000)
#define PORT_PD15_Msk                                     ((uint32_t)0x00008000)

#define PORT_SHM_Msk                                      ((uint32_t)0xFFFF0000)
#define PORT_SHM0_Msk                                     ((uint32_t)0x00010000)
#define PORT_SHM1_Msk                                     ((uint32_t)0x00020000)
#define PORT_SHM2_Msk                                     ((uint32_t)0x00040000)
#define PORT_SHM3_Msk                                     ((uint32_t)0x00080000)
#define PORT_SHM4_Msk                                     ((uint32_t)0x00100000)
#define PORT_SHM5_Msk                                     ((uint32_t)0x00200000)
#define PORT_SHM6_Msk                                     ((uint32_t)0x00400000)
#define PORT_SHM7_Msk                                     ((uint32_t)0x00800000)
#define PORT_SHM8_Msk                                     ((uint32_t)0x01000000)
#define PORT_SHM9_Msk                                     ((uint32_t)0x02000000)
#define PORT_SHM10_Msk                                    ((uint32_t)0x04000000)
#define PORT_SHM11_Msk                                    ((uint32_t)0x08000000)
#define PORT_SHM12_Msk                                    ((uint32_t)0x10000000)
#define PORT_SHM13_Msk                                    ((uint32_t)0x20000000)
#define PORT_SHM14_Msk                                    ((uint32_t)0x40000000)
#define PORT_SHM15_Msk                                    ((uint32_t)0x80000000)

// Регистр PWR
// Позиции битовых полей
#define PORT_PWR0_Pos                                     0
#define PORT_PWR1_Pos                                     2
#define PORT_PWR2_Pos                                     4
#define PORT_PWR3_Pos                                     6
#define PORT_PWR4_Pos                                     8
#define PORT_PWR5_Pos                                     10
#define PORT_PWR6_Pos                                     12
#define PORT_PWR7_Pos                                     14
#define PORT_PWR8_Pos                                     16
#define PORT_PWR9_Pos                                     18
#define PORT_PWR10_Pos                                    20
#define PORT_PWR11_Pos                                    22
#define PORT_PWR12_Pos                                    24
#define PORT_PWR13_Pos                                    26
#define PORT_PWR14_Pos                                    28
#define PORT_PWR15_Pos                                    30

// Маски битовых полей
#define PORT_PWR0_Msk                                     ((uint32_t)0x00000003)
#define PORT_PWR1_Msk                                     ((uint32_t)0x0000000C)
#define PORT_PWR2_Msk                                     ((uint32_t)0x00000030)
#define PORT_PWR3_Msk                                     ((uint32_t)0x000000C0)
#define PORT_PWR4_Msk                                     ((uint32_t)0x00000300)
#define PORT_PWR5_Msk                                     ((uint32_t)0x00000C00)
#define PORT_PWR6_Msk                                     ((uint32_t)0x00003000)
#define PORT_PWR7_Msk                                     ((uint32_t)0x0000C000)
#define PORT_PWR8_Msk                                     ((uint32_t)0x00030000)
#define PORT_PWR9_Msk                                     ((uint32_t)0x000C0000)
#define PORT_PWR10_Msk                                    ((uint32_t)0x00300000)
#define PORT_PWR11_Msk                                    ((uint32_t)0x00C00000)
#define PORT_PWR12_Msk                                    ((uint32_t)0x03000000)
#define PORT_PWR13_Msk                                    ((uint32_t)0x0C000000)
#define PORT_PWR14_Msk                                    ((uint32_t)0x30000000)
#define PORT_PWR15_Msk                                    ((uint32_t)0xC0000000)

// Регистр GFEN
// Позиции битовых полей
#define PORT_GFEN0_Pos                                    0
#define PORT_GFEN1_Pos                                    1
#define PORT_GFEN2_Pos                                    2
#define PORT_GFEN3_Pos                                    3
#define PORT_GFEN4_Pos                                    4
#define PORT_GFEN5_Pos                                    5
#define PORT_GFEN6_Pos                                    6
#define PORT_GFEN7_Pos                                    7
#define PORT_GFEN8_Pos                                    8
#define PORT_GFEN9_Pos                                    9
#define PORT_GFEN10_Pos                                   10
#define PORT_GFEN11_Pos                                   11
#define PORT_GFEN12_Pos                                   12
#define PORT_GFEN13_Pos                                   13
#define PORT_GFEN14_Pos                                   14
#define PORT_GFEN15_Pos                                   15

// Маски битовых полей
#define PORT_GFEN0_Msk                                    ((uint32_t)0x00000001)
#define PORT_GFEN1_Msk                                    ((uint32_t)0x00000002)
#define PORT_GFEN2_Msk                                    ((uint32_t)0x00000004)
#define PORT_GFEN3_Msk                                    ((uint32_t)0x00000008)
#define PORT_GFEN4_Msk                                    ((uint32_t)0x00000010)
#define PORT_GFEN5_Msk                                    ((uint32_t)0x00000020)
#define PORT_GFEN6_Msk                                    ((uint32_t)0x00000040)
#define PORT_GFEN7_Msk                                    ((uint32_t)0x00000080)
#define PORT_GFEN8_Msk                                    ((uint32_t)0x00000100)
#define PORT_GFEN9_Msk                                    ((uint32_t)0x00000200)
#define PORT_GFEN10_Msk                                   ((uint32_t)0x00000400)
#define PORT_GFEN11_Msk                                   ((uint32_t)0x00000800)
#define PORT_GFEN12_Msk                                   ((uint32_t)0x00001000)
#define PORT_GFEN13_Msk                                   ((uint32_t)0x00002000)
#define PORT_GFEN14_Msk                                   ((uint32_t)0x00004000)
#define PORT_GFEN15_Msk                                   ((uint32_t)0x00008000)

/* ---------------------------- Батарейный домен ---------------------------- */

// Структура батарейного домена
typedef struct
{
  __IO uint32_t REG_00;
  __IO uint32_t REG_01;
  __IO uint32_t REG_02;
  __IO uint32_t REG_03;
  __IO uint32_t REG_04;
  __IO uint32_t REG_05;
  __IO uint32_t REG_06;
  __IO uint32_t REG_07;
  __IO uint32_t REG_08;
  __IO uint32_t REG_09;
  __IO uint32_t REG_0A;
  __IO uint32_t REG_0B;
  __IO uint32_t REG_0C;
  __IO uint32_t REG_0D;
  __IO uint32_t REG_0E;
  __IO uint32_t REG_0F;
  __IO uint32_t RTC_CNT;
  __IO uint32_t RTC_DIV;
  __IO uint32_t RTC_PRL;
  __IO uint32_t RTC_ALRM;
  __IO uint32_t RTC_CS;
} MDR_BKP_TypeDef;

// Регистр REG_0E
// Позиции битовых полей
#define BKP_REG_0E_LOW_Pos                                0
#define BKP_REG_0E_SELECTRI_Pos                           3
#define BKP_REG_0E_JTAGA_Pos                              6
#define BKP_REG_0E_JTAGB_Pos                              7
#define BKP_REG_0E_TRIM_Pos                               8
#define BKP_REG_0E_FPOR_Pos                               11
#define BKP_REG_0E_BKP_REG_Pos                            12

// Маски битовых полей
#define BKP_REG_0E_LOW_Msk                                ((uint32_t)0x00000007)
#define BKP_REG_0E_SELECTRI_Msk                           ((uint32_t)0x00000038)
#define BKP_REG_0E_JTAGA                                  ((uint32_t)0x00000040)
#define BKP_REG_0E_JTAGB                                  ((uint32_t)0x00000080)
#define BKP_REG_0E_TRIM_Msk                               ((uint32_t)0x00000700)
#define BKP_REG_0E_FPOR                                   ((uint32_t)0x00000800)
#define BKP_REG_0E_BKP_REG_Msk                            ((uint32_t)0xFFFFF000)

// Регистр REG_0F
// Позиции битовых полей
#define BKP_REG_0F_LSE_ON_Pos                             0
#define BKP_REG_0F_LSE_BYP_Pos                            1
#define BKP_REG_0F_RTC_SEL_Pos                            2
#define BKP_REG_0F_RTC_EN_Pos                             4
#define BKP_REG_0F_CAL_Pos                                5
#define BKP_REG_0F_LSE_RDY_Pos                            13
#define BKP_REG_0F_BKP_REG_Pos                            14
#define BKP_REG_0F_LSI_ON_Pos                             15
#define BKP_REG_0F_LSI_TRIM_Pos                           16
#define BKP_REG_0F_LSI_RDY_Pos                            21
#define BKP_REG_0F_HSI_ON_Pos                             22
#define BKP_REG_0F_HSI_RDY_Pos                            23
#define BKP_REG_0F_HSI_TRIM_Pos                           24
#define BKP_REG_0F_STANDBY_Pos                            30
#define BKP_REG_0F_RTC_RESET_Pos                          31

// Маски битовых полей
#define BKP_REG_0F_LSE_ON                                 ((uint32_t)0x00000001)
#define BKP_REG_0F_LSE_BYP                                ((uint32_t)0x00000002)
#define BKP_REG_0F_RTC_SEL_Msk                            ((uint32_t)0x0000000C)
#define BKP_REG_0F_RTC_EN                                 ((uint32_t)0x00000010)
#define BKP_REG_0F_CAL_Msk                                ((uint32_t)0x00001FE0)
#define BKP_REG_0F_LSE_RDY                                ((uint32_t)0x00002000)
#define BKP_REG_0F_BKP_REG                                ((uint32_t)0x00004000)
#define BKP_REG_0F_LSI_ON                                 ((uint32_t)0x00008000)
#define BKP_REG_0F_LSI_TRIM_Msk                           ((uint32_t)0x001F0000)
#define BKP_REG_0F_LSI_RDY                                ((uint32_t)0x00200000)
#define BKP_REG_0F_HSI_ON                                 ((uint32_t)0x00400000)
#define BKP_REG_0F_HSI_RDY                                ((uint32_t)0x00800000)
#define BKP_REG_0F_HSI_TRIM_Msk                           ((uint32_t)0x3F000000)
#define BKP_REG_0F_STANDBY                                ((uint32_t)0x40000000)
#define BKP_REG_0F_RTC_RESET                              ((uint32_t)0x80000000)

// Регистр RTC_CS
// Позиции битовых полей
#define BKP_RTC_CS_OWF_Pos                                0
#define BKP_RTC_CS_SECF_Pos                               1
#define BKP_RTC_CS_ALRF_Pos                               2
#define BKP_RTC_CS_OWF_IE_Pos                             3
#define BKP_RTC_CS_SECF_IE_Pos                            4
#define BKP_RTC_CS_ALRF_IE_Pos                            5
#define BKP_RTC_CS_WEC_Pos                                6

// Маски битовых полей
#define BKP_RTC_CS_OWF                                    ((uint32_t)0x00000001)
#define BKP_RTC_CS_SECF                                   ((uint32_t)0x00000002)
#define BKP_RTC_CS_ALRF                                   ((uint32_t)0x00000004)
#define BKP_RTC_CS_OWF_IE                                 ((uint32_t)0x00000008)
#define BKP_RTC_CS_SECF_IE                                ((uint32_t)0x00000010)
#define BKP_RTC_CS_ALRF_IE                                ((uint32_t)0x00000020)
#define BKP_RTC_CS_WEC                                    ((uint32_t)0x00000040)

/* ------------------------- Внешняя системная шина ------------------------- */

// Структура внешней системной шины
typedef struct
{
       uint32_t RESERVED0[20];
  __IO uint32_t NAND_CYCLES;
  __IO uint32_t CONTROL;
#if defined (USE_MDR1986VE94)
  __IO uint32_t MEM_REGION[4];
#endif
} MDR_EBC_TypeDef;

// Регистр NAND_CYCLES
// Позиции битовых полей
#define EBC_NAND_CYCLES_TRC_Pos                           0
#define EBC_NAND_CYCLES_TWC_Pos                           4
#define EBC_NAND_CYCLES_TREA_Pos                          8
#define EBC_NAND_CYCLES_TWP_Pos                           12
#define EBC_NAND_CYCLES_TWHR_Pos                          16
#define EBC_NAND_CYCLES_TALEA_Pos                         20
#define EBC_NAND_CYCLES_TRR_Pos                           24

// Маски битовых полей
#define EBC_NAND_CYCLES_TRC_Msk                           ((uint32_t)0x0000000F)
#define EBC_NAND_CYCLES_TWC_Msk                           ((uint32_t)0x000000F0)
#define EBC_NAND_CYCLES_TREA_Msk                          ((uint32_t)0x00000F00)
#define EBC_NAND_CYCLES_TWP_Msk                           ((uint32_t)0x0000F000)
#define EBC_NAND_CYCLES_TWHR_Msk                          ((uint32_t)0x000F0000)
#define EBC_NAND_CYCLES_TALEA_Msk                         ((uint32_t)0x00F00000)
#define EBC_NAND_CYCLES_TRR_Msk                           ((uint32_t)0x0F000000)

// Регистр CONTROL
// Позиции битовых полей
#define EBC_CONTROL_ROM_Pos                               0
#define EBC_CONTROL_RAM_Pos                               1
#define EBC_CONTROL_NAND_Pos                              2
#define EBC_CONTROL_CPOL_Pos                              3
#define EBC_CONTROL_BUSY_Pos                              7
#define EBC_CONTROL_WAIT_STATE_Pos                        12
#if defined (USE_MDR1986VE94)
  #define EBC_CONTROL_FS_RDY_Pos                          16
  #define EBC_CONTROL_FF_RDY_Pos                          17
#endif

// Маски битовых полей
#define EBC_CONTROL_ROM                                   ((uint32_t)0x00000001)
#define EBC_CONTROL_RAM                                   ((uint32_t)0x00000002)
#define EBC_CONTROL_NAND                                  ((uint32_t)0x00000004)
#define EBC_CONTROL_CPOL                                  ((uint32_t)0x00000008)
#define EBC_CONTROL_BUSY                                  ((uint32_t)0x00000080)
#define EBC_CONTROL_WAIT_STATE_Msk                        ((uint32_t)0x0000F000)
#if defined (USE_MDR1986VE94)
  #define EBC_CONTROL_FS_RDY                              ((uint32_t)0x00010000)
  #define EBC_CONTROL_FF_RDY                              ((uint32_t)0x00020000)
#endif

// Регистр RAM_CYCLES (только для 1986ВЕ94Т)
#if defined (USE_MDR1986VE94)

// Позиции битовых полей
#define EBC_RAM_CYCLES_ENABLE_TUNE_Pos                     0
#define EBC_RAM_CYCLES_WS_ACTIVE_Pos                       1
#define EBC_RAM_CYCLES_WS_SETUP_Pos                        8
#define EBC_RAM_CYCLES_WS_HOLD_Pos                        11
#define EBC_RAM_CYCLES_USE_READY_Pos                      14

// Маски битовых полей
#define EBC_RAM_CYCLES_ENABLE_TUNE                        ((uint32_t)0x00000001)
#define EBC_RAM_CYCLES_WS_ACTIVE_Msk                      ((uint32_t)0x000000FE)
#define EBC_RAM_CYCLES_WS_SETUP_Msk                       ((uint32_t)0x00000700)
#define EBC_RAM_CYCLES_WS_HOLD_Msk                        ((uint32_t)0x00003200)
#define EBC_RAM_CYCLES_USE_READY                          ((uint32_t)0x00004000)

#endif

/* ------------------- Базовые адреса периферийных блоков ------------------- */

#define MDR_CAN1_BASE                                     ((uint32_t)0x40000000)
#define MDR_CAN2_BASE                                     ((uint32_t)0x40008000)
#define MDR_USB_BASE                                      ((uint32_t)0x40010000)
#define MDR_EEPROM_BASE                                   ((uint32_t)0x40018000)
#define MDR_RST_CLK_BASE                                  ((uint32_t)0x40020000)
#define MDR_DMA_BASE                                      ((uint32_t)0x40028000)
#define MDR_UART1_BASE                                    ((uint32_t)0x40030000)
#define MDR_UART2_BASE                                    ((uint32_t)0x40038000)
#define MDR_SSP1_BASE                                     ((uint32_t)0x40040000)
#define MDR_I2C_BASE                                      ((uint32_t)0x40050000)
#define MDR_POWER_BASE                                    ((uint32_t)0x40058000)
#define MDR_WWDG_BASE                                     ((uint32_t)0x40060000)
#define MDR_IWDG_BASE                                     ((uint32_t)0x40068000)
#define MDR_TIMER1_BASE                                   ((uint32_t)0x40070000)
#define MDR_TIMER2_BASE                                   ((uint32_t)0x40078000)
#define MDR_TIMER3_BASE                                   ((uint32_t)0x40080000)
#define MDR_ADC_BASE                                      ((uint32_t)0x40088000)
#define MDR_DAC_BASE                                      ((uint32_t)0x40090000)
#define MDR_COMP_BASE                                     ((uint32_t)0x40098000)
#define MDR_SSP2_BASE                                     ((uint32_t)0x400A0000)
#define MDR_PORTA_BASE                                    ((uint32_t)0x400A8000)
#define MDR_PORTB_BASE                                    ((uint32_t)0x400B0000)
#define MDR_PORTC_BASE                                    ((uint32_t)0x400B8000)
#define MDR_PORTD_BASE                                    ((uint32_t)0x400C0000)
#define MDR_PORTE_BASE                                    ((uint32_t)0x400C8000)
#define MDR_BKP_BASE                                      ((uint32_t)0x400D8000)
#define MDR_PORTF_BASE                                    ((uint32_t)0x400E8000)
#define MDR_EBC_BASE                                      ((uint32_t)0x400F0000)

/* --------------------- Объявление периферийных блоков --------------------- */

#define MDR_CAN1                      ((MDR_CAN_TypeDef     *) MDR_CAN1_BASE)
#define MDR_CAN2                      ((MDR_CAN_TypeDef     *) MDR_CAN2_BASE)
#define MDR_USB                       ((MDR_USB_TypeDef     *) MDR_USB_BASE)
#define MDR_EEPROM                    ((MDR_EEPROM_TypeDef  *) MDR_EEPROM_BASE)
#define MDR_RST_CLK                   ((MDR_RST_CLK_TypeDef *) MDR_RST_CLK_BASE)
#define MDR_DMA                       ((MDR_DMA_TypeDef     *) MDR_DMA_BASE)
#define MDR_UART1                     ((MDR_UART_TypeDef    *) MDR_UART1_BASE)
#define MDR_UART2                     ((MDR_UART_TypeDef    *) MDR_UART2_BASE)
#define MDR_SSP1                      ((MDR_SSP_TypeDef     *) MDR_SSP1_BASE)
#define MDR_I2C                       ((MDR_I2C_TypeDef     *) MDR_I2C_BASE)
#define MDR_POWER                     ((MDR_POWER_TypeDef   *) MDR_POWER_BASE)
#define MDR_WWDG                      ((MDR_WWDG_TypeDef    *) MDR_WWDG_BASE)
#define MDR_IWDG                      ((MDR_IWDG_TypeDef    *) MDR_IWDG_BASE)
#define MDR_TIMER1                    ((MDR_TIMER_TypeDef   *) MDR_TIMER1_BASE)
#define MDR_TIMER2                    ((MDR_TIMER_TypeDef   *) MDR_TIMER2_BASE)
#define MDR_TIMER3                    ((MDR_TIMER_TypeDef   *) MDR_TIMER3_BASE)
#define MDR_ADC                       ((MDR_ADC_TypeDef     *) MDR_ADC_BASE)
#define MDR_DAC                       ((MDR_DAC_TypeDef     *) MDR_DAC_BASE)
#define MDR_COMP                      ((MDR_COMP_TypeDef    *) MDR_COMP_BASE)
#define MDR_SSP2                      ((MDR_SSP_TypeDef     *) MDR_SSP2_BASE)
#define MDR_PORTA                     ((MDR_PORT_TypeDef    *) MDR_PORTA_BASE)
#define MDR_PORTB                     ((MDR_PORT_TypeDef    *) MDR_PORTB_BASE)
#define MDR_PORTC                     ((MDR_PORT_TypeDef    *) MDR_PORTC_BASE)
#define MDR_PORTD                     ((MDR_PORT_TypeDef    *) MDR_PORTD_BASE)
#define MDR_PORTE                     ((MDR_PORT_TypeDef    *) MDR_PORTE_BASE)
#define MDR_BKP                       ((MDR_BKP_TypeDef     *) MDR_BKP_BASE)
#define MDR_PORTF                     ((MDR_PORT_TypeDef    *) MDR_PORTF_BASE)
#define MDR_EBC                       ((MDR_EBC_TypeDef     *) MDR_EBC_BASE)

#ifdef __cplusplus
}

#endif

#endif
