/*
 * stm_regs.h
 *
 *  Created on: 30.08.2022.
 *      Author: Sep
 */

#ifndef STM32_REGS_H_
#define STM32_REGS_H_

#include <stdint.h>
#include "stm32f1xx.h"

#define REG_Write(addr, u32Data)  *(volatile uint32_t *)(addr) = ((uint32_t)u32Data)
#define REG_Read(addr)            *(volatile uint32_t *)(addr)


// PWR
#define PWR__CR    (PWR_BASE + 0x00)
#define PWR__CSR   (PWR_BASE + 0x04)

typedef union {
    struct {
        uint32_t lp_ds: 1;
        uint32_t pd_ds: 1;
        uint32_t cwuf: 1;
        uint32_t csbf: 1;
        uint32_t pvde: 1;
        uint32_t pls: 3;
        uint32_t dbp: 1;
        uint32_t r__1: 23;

    } b;
    uint32_t all;
} pwr_cr_t;

typedef union {
    struct {
        uint32_t wuf: 1;
        uint32_t sbf: 1;
        uint32_t pvdo: 1;
        uint32_t r__1: 5;
        uint32_t ewup: 1;
        uint32_t r__2: 23;
    } b;
    uint32_t all;
} pwr_csr_t;

typedef union {
    pwr_cr_t cr;
    pwr_csr_t cs;
} pwr_reg_t;


// RCC
#define RCC__CR         (RCC_BASE + 0x00)
#define RCC__CFGR       (RCC_BASE + 0x04)
#define RCC__CIR        (RCC_BASE + 0x08)
#define RCC__APB2RSTR   (RCC_BASE + 0x0C)
#define RCC__APB1RSTR   (RCC_BASE + 0x10)
#define RCC__AHBENR     (RCC_BASE + 0x14)
#define RCC__APB2ENR    (RCC_BASE + 0x18)
#define RCC__APB1ENR    (RCC_BASE + 0x1C)
#define RCC__BDCR       (RCC_BASE + 0x20)
#define RCC__CSR        (RCC_BASE + 0x24)

typedef union {
    struct {
        uint32_t hsi_on: 1;
        uint32_t hsi_rdy: 1;
        uint32_t r__1: 1;
        uint32_t hsi_trim: 5;
        uint32_t hsi_cal: 8;
        uint32_t hse_on: 1;
        uint32_t hse_rdy: 1;
        uint32_t hse_byp: 1;
        uint32_t css_on: 1;
        uint32_t r__2: 4;
		uint32_t pll_on: 1;
		uint32_t pll_rdy: 1;
		uint32_t r__3: 6;
    } b;
    uint32_t all;
} rcc_cr_t;

typedef union {
    struct {
        uint32_t clk_sw: 2;
		uint32_t clk_sw_sts: 2;
		uint32_t ahb_pre: 4;
		uint32_t apb1_pre: 3;
		uint32_t apb2_pre: 3;
		uint32_t adc_pre: 2;
		uint32_t pll_src: 1;
		uint32_t pll_xtpre: 1;
		uint32_t pll_mul: 4;
		uint32_t usb_pre: 1;
		uint32_t r__1: 1;
		uint32_t mco: 3;
		uint32_t t__2: 5;
    } b;
    uint32_t all;
} rcc_cfgr_t;

typedef union {
    struct {
        uint32_t lsi_rdyf: 1;
		uint32_t lse_rdyf: 1;
		uint32_t hsi_rdyf: 1;
		uint32_t hse_rdyf: 1;
		uint32_t pll_rdyf: 1;
		uint32_t r__1: 2;
		uint32_t cssf: 1;
		uint32_t lsi_rdyie: 1;
		uint32_t lse_rdyie: 1;
		uint32_t hsi_rdyie: 1;
		uint32_t hse_rdyie: 1;
		uint32_t pll_rdyie: 1;
		uint32_t r__2: 3;
		uint32_t lsi_rdyc: 1;
		uint32_t lse_rdyc: 1;
		uint32_t hsi_rdyc: 1;
		uint32_t hse_rdyc: 1;
		uint32_t pll_rdyc: 1;
		uint32_t r__3: 2;
		uint32_t cssc: 1;
		uint32_t r__4: 8;
    } b;
    uint32_t all;
} rcc_cir_t;

typedef union {
    struct {
        uint32_t af_io_rst: 1;
		uint32_t r__1: 1;
		uint32_t io_pa_rst: 1;
		uint32_t io_pb_rst: 1;
		uint32_t io_pc_rst: 1;
		uint32_t io_pd_rst: 1;
		uint32_t io_pe_rst: 1;
		uint32_t io_pf_rst: 1;
		uint32_t io_pg_rst: 1;
		uint32_t adc1_rst: 1;
		uint32_t adc2_rst: 1;
		uint32_t tim1_rst: 1;
		uint32_t spi1_rst: 1;
		uint32_t tim8_rst: 1;
		uint32_t usart1_rst: 1;
		uint32_t adc3_rst: 1;
		uint32_t r__2: 3;
		uint32_t tim9_rst: 1;
		uint32_t tim10_rst: 1;
		uint32_t tim11_rst: 1;
		uint32_t r__3: 10;
    } b;
    uint32_t all;
} rcc_apb2_rstr_t;

typedef union {
    struct {
        uint32_t tim2_rst: 1;
		uint32_t tim3_rst: 1;
		uint32_t tim4_rst: 1;
		uint32_t tim5_rst: 1;
		uint32_t tim6_rst: 1;
		uint32_t tim7_rst: 1;
		uint32_t tim12_rst: 1;
		uint32_t tim13_rst: 1;
		uint32_t tim14_rst: 1;
		uint32_t r__1: 2;
		uint32_t wwdg_rst: 1;
		uint32_t r__2: 2;
		uint32_t spi2_rst: 1;
		uint32_t spi3_rst: 1;
		uint32_t r__3: 1;
		uint32_t usart2_rst: 1;
		uint32_t usart3_rst: 1;
		uint32_t uart4_rst: 1;
		uint32_t uart5_rst: 1;
		uint32_t i2c1_rst: 1;
		uint32_t i2c2_rst: 1;
		uint32_t usb_rst: 1;
		uint32_t r__4: 1;
		uint32_t can_rst: 1;
		uint32_t r__5: 1;
		uint32_t bkp_rst: 1;	
		uint32_t pwr_rst: 1;
		uint32_t dac_rst: 1;		
		uint32_t r__6: 2;
    } b;
    uint32_t all;
} rcc_apb1_rstr_t;

typedef union {
    struct {
        uint32_t dma1_en: 1;
		uint32_t dma2_en: 1;
		uint32_t sram_en: 1;
		uint32_t r__1: 1;
		uint32_t flitf_en: 1;
		uint32_t r__2: 1;
		uint32_t crc_en: 1;
		uint32_t r__3: 1;
		uint32_t fsmc_en: 1;
		uint32_t r__4: 1;
		uint32_t sdio_en: 1;
		uint32_t r__5: 21;
    } b;
    uint32_t all;
} rcc_ahb_enr_t;

typedef union {
    struct {
        uint32_t af_io_en: 1;
		uint32_t r__1: 1;
		uint32_t io_pa_en: 1;
		uint32_t io_pb_en: 1;
		uint32_t io_pc_en: 1;
		uint32_t io_pd_en: 1;
		uint32_t io_pe_en: 1;
		uint32_t io_pf_en: 1;
		uint32_t io_pg_en: 1;
		uint32_t adc1_en: 1;
		uint32_t adc2_en: 1;
		uint32_t tim1_en: 1;
		uint32_t spi1_en: 1;
		uint32_t tim8_en: 1;
		uint32_t usart1_en: 1;
		uint32_t adc3_en: 1;
		uint32_t r__2: 3;
		uint32_t tim9_en: 1;
		uint32_t tim10_en: 1;
		uint32_t tim11_en: 1;
		uint32_t r__3: 10;
    } b;
    uint32_t all;
} rcc_apb2_enr_t;

typedef union {
    struct {
        uint32_t tim2_en: 1;
		uint32_t tim3_en: 1;
		uint32_t tim4_en: 1;
		uint32_t tim5_en: 1;
		uint32_t tim6_en: 1;
		uint32_t tim7_en: 1;
		uint32_t tim12_en: 1;
		uint32_t tim13_en: 1;
		uint32_t tim14_en: 1;
		uint32_t r__1: 2;
		uint32_t wwdg_en: 1;
		uint32_t r__2: 2;
		uint32_t spi2_en: 1;
		uint32_t spi3_en: 1;
		uint32_t r__3: 1;
		uint32_t usart2_en: 1;
		uint32_t usart3_en: 1;
		uint32_t uart4_en: 1;
		uint32_t uart5_en: 1;
		uint32_t i2c1_en: 1;
		uint32_t i2c2_en: 1;
		uint32_t usb_en: 1;
		uint32_t r__4: 1;
		uint32_t can_en: 1;
		uint32_t r__5: 1;
		uint32_t bkp_en: 1;
		uint32_t pwr_en: 1;
		uint32_t dac_en: 1;
		uint32_t r__6: 2;
    } b;
    uint32_t all;
} rcc_apb1_enr_t;

typedef union {
    struct {
        uint32_t lse_on: 1;
		uint32_t lse_rdy: 1;
		uint32_t lse_byp: 1;
		uint32_t r__1: 5;
		uint32_t rtc_sel: 2;
		uint32_t r__2: 5;
		uint32_t rtc_en: 1;
		uint32_t bd_rst: 1;
		uint32_t r__3: 15;
    } b;
    uint32_t all;
} rcc_bd_cr_t;

typedef union {
    struct {
        uint32_t lsi_on: 1;
		uint32_t lsi_rdy: 1;
		uint32_t r__1: 22;
		uint32_t rmvf: 1;
		uint32_t r__2: 1;
		uint32_t pin_rstf: 1;
		uint32_t por_rstf: 1;
		uint32_t sft_rstf: 1;
		uint32_t iwdg_rstf: 1;
		uint32_t wwdg_rstf: 1;
		uint32_t lpwr_rstf: 1;
    } b;
    uint32_t all;
} rcc_csr_t;

typedef union {
    rcc_cr_t cr;
    rcc_cfgr_t cfg;
	rcc_cir_t cir;
	rcc_apb2_rstr_t apb2_rst;
	rcc_apb1_rstr_t apb1_rst;
	rcc_ahb_enr_t ahb_en;
	rcc_apb2_enr_t apb2_en;
	rcc_apb1_enr_t apb1_en;
	rcc_bd_cr_t bd_cr;
	rcc_csr_t cs;
} rcc_reg_t;

// GPIO
#define GPIOA__CRL    (GPIOA_BASE + 0x00)
#define GPIOA__CRH    (GPIOA_BASE + 0x04)
#define GPIOA__IDR    (GPIOA_BASE + 0x08)
#define GPIOA__ODR    (GPIOA_BASE + 0x0C)
#define GPIOA__BSRR   (GPIOA_BASE + 0x10)
#define GPIOA__BRR    (GPIOA_BASE + 0x14)

#define GPIOB__CRL    (GPIOB_BASE + 0x00)
#define GPIOB__CRH    (GPIOB_BASE + 0x04)
#define GPIOB__IDR    (GPIOB_BASE + 0x08)
#define GPIOB__ODR    (GPIOB_BASE + 0x0C)
#define GPIOB__BSRR   (GPIOB_BASE + 0x10)
#define GPIOB__BRR    (GPIOB_BASE + 0x14)

#define GPIOC__CRL    (GPIOC_BASE + 0x00)
#define GPIOC__CRH    (GPIOC_BASE + 0x04)
#define GPIOC__IDR    (GPIOC_BASE + 0x08)
#define GPIOC__ODR    (GPIOC_BASE + 0x0C)
#define GPIOC__BSRR   (GPIOC_BASE + 0x10)
#define GPIOC__BRR    (GPIOC_BASE + 0x14)

#define GPIOD__CRL    (GPIOD_BASE + 0x00)
#define GPIOD__CRH    (GPIOD_BASE + 0x04)
#define GPIOD__IDR    (GPIOD_BASE + 0x08)
#define GPIOD__ODR    (GPIOD_BASE + 0x0C)
#define GPIOD__BSRR   (GPIOD_BASE + 0x10)
#define GPIOD__BRR    (GPIOD_BASE + 0x14)

typedef union {
    struct {
        uint32_t mode_0 :2;
        uint32_t cnf_0 :2;
        uint32_t mode_1 :2;
        uint32_t cnf_1 :2;
        uint32_t mode_2 :2;
        uint32_t cnf_2 :2;
        uint32_t mode_3 :2;
        uint32_t cnf_3 :2;
        uint32_t mode_4 :2;
        uint32_t cnf_4 :2;
        uint32_t mode_5 :2;
        uint32_t cnf_5 :2;
        uint32_t mode_6 :2;
        uint32_t cnf_6 :2;
        uint32_t mode_7 :2;
        uint32_t cnf_7 :2;
    } b;
    uint32_t all;
} gpio_crl_t;

typedef union {
    struct {
        uint32_t mode_8 :2;
        uint32_t cnf_8 :2;
        uint32_t mode_9 :2;
        uint32_t cnf_9 :2;
        uint32_t mode_10 :2;
        uint32_t cnf_10 :2;
        uint32_t mode_11 :2;
        uint32_t cnf_11 :2;
        uint32_t mode_12 :2;
        uint32_t cnf_12 :2;
        uint32_t mode_13 :2;
        uint32_t cnf_13 :2;
        uint32_t mode_14 :2;
        uint32_t cnf_14 :2;
        uint32_t mode_15 :2;
        uint32_t cnf_15 :2;
    } b;
    uint32_t all;
} gpio_crh_t;

typedef union {
    struct {
    	uint32_t idr_0 :1;
        uint32_t idr_1 :1;
        uint32_t idr_2 :1;
        uint32_t idr_3 :1;
        uint32_t idr_4 :1;
        uint32_t idr_5 :1;
        uint32_t idr_6 :1;
        uint32_t idr_7 :1;
        uint32_t idr_8 :1;
        uint32_t idr_9 :1;
        uint32_t idr_10 :1;
        uint32_t idr_11 :1;
        uint32_t idr_12 :1;
        uint32_t idr_13 :1;
        uint32_t idr_14 :1;
        uint32_t idr_15 :1;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} gpio_idr_t;

typedef union {
    struct {
    	uint32_t odr_0 :1;
        uint32_t odr_1 :1;
        uint32_t odr_2 :1;
        uint32_t odr_3 :1;
        uint32_t odr_4 :1;
        uint32_t odr_5 :1;
        uint32_t odr_6 :1;
        uint32_t odr_7 :1;
        uint32_t odr_8 :1;
        uint32_t odr_9 :1;
        uint32_t odr_10 :1;
        uint32_t odr_11 :1;
        uint32_t odr_12 :1;
        uint32_t odr_13 :1;
        uint32_t odr_14 :1;
        uint32_t odr_15 :1;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} gpio_odr_t;

typedef union {
    struct {
    	uint32_t bs_0 :1;
        uint32_t bs_1 :1;
        uint32_t bs_2 :1;
        uint32_t bs_3 :1;
        uint32_t bs_4 :1;
        uint32_t bs_5 :1;
        uint32_t bs_6 :1;
        uint32_t bs_7 :1;
        uint32_t bs_8 :1;
        uint32_t bs_9 :1;
        uint32_t bs_10 :1;
        uint32_t bs_11 :1;
        uint32_t bs_12 :1;
        uint32_t bs_13 :1;
        uint32_t bs_14 :1;
        uint32_t bs_15 :1;
        uint32_t br_0 :1;
		uint32_t br_1 :1;
		uint32_t br_2 :1;
		uint32_t br_3 :1;
		uint32_t br_4 :1;
		uint32_t br_5 :1;
		uint32_t br_6 :1;
		uint32_t br_7 :1;
		uint32_t br_8 :1;
		uint32_t br_9 :1;
		uint32_t br_10 :1;
		uint32_t br_11 :1;
		uint32_t br_12 :1;
		uint32_t br_13 :1;
		uint32_t br_14 :1;
		uint32_t br_15 :1;
    } b;
    uint32_t all;
} gpio_bsrr_t;

typedef union {
    struct {
    	uint32_t br_0 :1;
        uint32_t br_1 :1;
        uint32_t br_2 :1;
        uint32_t br_3 :1;
        uint32_t br_4 :1;
        uint32_t br_5 :1;
        uint32_t br_6 :1;
        uint32_t br_7 :1;
        uint32_t br_8 :1;
        uint32_t br_9 :1;
        uint32_t br_10 :1;
        uint32_t br_11 :1;
        uint32_t br_12 :1;
        uint32_t br_13 :1;
        uint32_t br_14 :1;
        uint32_t br_15 :1;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} gpio_brr_t;

typedef union {
    gpio_crl_t crl;
    gpio_crh_t crh;
    gpio_idr_t idr;
    gpio_odr_t odr;
    gpio_bsrr_t bsrr;
    gpio_brr_t brr;
} gpio_reg_t;

// AFIO
#define AFIO__EVCR       (AFIO_BASE + 0x00)
#define AFIO__MAPR       (AFIO_BASE + 0x04)
#define AFIO__EXTICR1    (AFIO_BASE + 0x08)
#define AFIO__EXTICR2    (AFIO_BASE + 0x0C)
#define AFIO__EXTICR3    (AFIO_BASE + 0x10)
#define AFIO__EXTICR4    (AFIO_BASE + 0x14)
#define AFIO__MAPR2      (AFIO_BASE + 0x1C)

typedef union {
    struct {
        uint32_t pin :4;
        uint32_t port :3;
        uint32_t ev_oe :1;
        uint32_t r__1 :24;
    } b;
    uint32_t all;
} afio_evcr_t;

typedef union {
    struct {
        uint32_t exti0 :4;
        uint32_t exti1 :4;
        uint32_t exti2 :4;
        uint32_t exti3 :4;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} afio_exticr1_t;

typedef union {
    struct {
        uint32_t exti4 :4;
        uint32_t exti5 :4;
        uint32_t exti6 :4;
        uint32_t exti7 :4;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} afio_exticr2_t;

typedef union {
    struct {
        uint32_t exti8 :4;
        uint32_t exti9 :4;
        uint32_t exti10 :4;
        uint32_t exti11 :4;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} afio_exticr3_t;

typedef union {
    struct {
        uint32_t exti12 :4;
        uint32_t exti13 :4;
        uint32_t exti14 :4;
        uint32_t exti15 :4;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} afio_exticr4_t;

typedef union {
    afio_evcr_t evcr;
    afio_exticr1_t exticr1;
    afio_exticr2_t exticr2;
    afio_exticr3_t exticr3;
    afio_exticr4_t exticr4;
} afio_reg_t;

// EXTI
#define EXTI__IMR       (EXTI_BASE + 0x00)
#define EXTI__EMR       (EXTI_BASE + 0x04)
#define EXTI__RTSR      (EXTI_BASE + 0x08)
#define EXTI__FTSR      (EXTI_BASE + 0x0C)
#define EXTI__SWIER     (EXTI_BASE + 0x10)
#define EXTI__PR        (EXTI_BASE + 0x14)

typedef union {
    struct {
    	uint32_t mr_0 :1;
        uint32_t mr_1 :1;
        uint32_t mr_2 :1;
        uint32_t mr_3 :1;
        uint32_t mr_4 :1;
        uint32_t mr_5 :1;
        uint32_t mr_6 :1;
        uint32_t mr_7 :1;
        uint32_t mr_8 :1;
        uint32_t mr_9 :1;
        uint32_t mr_10 :1;
        uint32_t mr_11 :1;
        uint32_t mr_12 :1;
        uint32_t mr_13 :1;
        uint32_t mr_14 :1;
        uint32_t mr_15 :1;
        uint32_t mr_16 :1;
        uint32_t mr_17 :1;
        uint32_t mr_18 :1;
        uint32_t mr_19 :1;
        uint32_t r__1 :12;
    } b;
    uint32_t all;
} exti_mr_t;

typedef union {
    struct {
    	uint32_t tr_0 :1;
        uint32_t tr_1 :1;
        uint32_t tr_2 :1;
        uint32_t tr_3 :1;
        uint32_t tr_4 :1;
        uint32_t tr_5 :1;
        uint32_t tr_6 :1;
        uint32_t tr_7 :1;
        uint32_t tr_8 :1;
        uint32_t tr_9 :1;
        uint32_t tr_10 :1;
        uint32_t tr_11 :1;
        uint32_t tr_12 :1;
        uint32_t tr_13 :1;
        uint32_t tr_14 :1;
        uint32_t tr_15 :1;
        uint32_t tr_16 :1;
        uint32_t tr_17 :1;
        uint32_t tr_18 :1;
        uint32_t tr_19 :1;
        uint32_t r__1 :12;
    } b;
    uint32_t all;
} exti_tr_t;

typedef union {
    struct {
    	uint32_t swier_0 :1;
        uint32_t swier_1 :1;
        uint32_t swier_2 :1;
        uint32_t swier_3 :1;
        uint32_t swier_4 :1;
        uint32_t swier_5 :1;
        uint32_t swier_6 :1;
        uint32_t swier_7 :1;
        uint32_t swier_8 :1;
        uint32_t swier_9 :1;
        uint32_t swier_10 :1;
        uint32_t swier_11 :1;
        uint32_t swier_12 :1;
        uint32_t swier_13 :1;
        uint32_t swier_14 :1;
        uint32_t swier_15 :1;
        uint32_t swier_16 :1;
        uint32_t swier_17 :1;
        uint32_t swier_18 :1;
        uint32_t swier_19 :1;
        uint32_t r__1 :12;
    } b;
    uint32_t all;
} exti_swier_t;

typedef union {
    struct {
    	uint32_t pr_0 :1;
        uint32_t pr_1 :1;
        uint32_t pr_2 :1;
        uint32_t pr_3 :1;
        uint32_t pr_4 :1;
        uint32_t pr_5 :1;
        uint32_t pr_6 :1;
        uint32_t pr_7 :1;
        uint32_t pr_8 :1;
        uint32_t pr_9 :1;
        uint32_t pr_10 :1;
        uint32_t pr_11 :1;
        uint32_t pr_12 :1;
        uint32_t pr_13 :1;
        uint32_t pr_14 :1;
        uint32_t pr_15 :1;
        uint32_t pr_16 :1;
        uint32_t pr_17 :1;
        uint32_t pr_18 :1;
        uint32_t pr_19 :1;
        uint32_t r__1 :12;
    } b;
    uint32_t all;
} exti_pr_t;

typedef union {
    exti_mr_t imr;
    exti_mr_t emr;
    exti_tr_t rtsr;
    exti_tr_t ftsr;
    exti_swier_t swier;
    exti_pr_t pr;
} exti_reg_t;


// DMA
#define DMA__ISR       (DMA1_BASE + 0x00)
#define DMA__IFCR      (DMA1_BASE + 0x04)

#define DMA__CCR1      (DMA1_BASE + 0x08)
#define DMA__CNDTR1    (DMA1_BASE + 0x0C)
#define DMA__CPAR1     (DMA1_BASE + 0x10)
#define DMA__CMAR1     (DMA1_BASE + 0x14)

#define DMA__CCR2      (DMA1_BASE + 0x1C)
#define DMA__CNDTR2    (DMA1_BASE + 0x20)
#define DMA__CPAR2     (DMA1_BASE + 0x24)
#define DMA__CMAR2     (DMA1_BASE + 0x28)

#define DMA__CCR3      (DMA1_BASE + 0x30)
#define DMA__CNDTR3    (DMA1_BASE + 0x34)
#define DMA__CPAR3     (DMA1_BASE + 0x38)
#define DMA__CMAR3     (DMA1_BASE + 0x3C)

#define DMA__CCR4      (DMA1_BASE + 0x44)
#define DMA__CNDTR4    (DMA1_BASE + 0x48)
#define DMA__CPAR4     (DMA1_BASE + 0x4C)
#define DMA__CMAR4     (DMA1_BASE + 0x50)

#define DMA__CCR5      (DMA1_BASE + 0x58)
#define DMA__CNDTR5    (DMA1_BASE + 0x5C)
#define DMA__CPAR5     (DMA1_BASE + 0x60)
#define DMA__CMAR5     (DMA1_BASE + 0x64)

#define DMA__CCR6      (DMA1_BASE + 0x6C)
#define DMA__CNDTR6    (DMA1_BASE + 0x70)
#define DMA__CPAR6     (DMA1_BASE + 0x74)
#define DMA__CMAR6     (DMA1_BASE + 0x78)

#define DMA__CCR7      (DMA1_BASE + 0x80)
#define DMA__CNDTR7    (DMA1_BASE + 0x84)
#define DMA__CPAR7     (DMA1_BASE + 0x88)
#define DMA__CMAR7     (DMA1_BASE + 0x8C)

typedef union {
    struct {
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__1 :28;
    } ch_1;
    struct {
        uint32_t r__1 :4;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :24;
    } ch_2;
    struct {
        uint32_t r__1 :8;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :20;
    } ch_3;
    struct {
        uint32_t r__1 :12;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :16;
    } ch_4;
    struct {
        uint32_t r__1 :16;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :12;
    } ch_5;
    struct {
        uint32_t r__1 :20;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :8;
    } ch_6;
    struct {
        uint32_t r__1 :24;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :4;
    } ch_7;
    uint32_t all;
} dma_isr_t;

typedef union {
    struct {
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__1 :28;
    } ch_1;
    struct {
        uint32_t r__1 :4;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :24;
    } ch_2;
    struct {
        uint32_t r__1 :8;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :20;
    } ch_3;
    struct {
        uint32_t r__1 :12;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :16;
    } ch_4;
    struct {
        uint32_t r__1 :16;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :12;
    } ch_5;
    struct {
        uint32_t r__1 :20;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :8;
    } ch_6;
    struct {
        uint32_t r__1 :24;
        uint32_t glob :1;
        uint32_t tc :1;
        uint32_t ht :1;
        uint32_t te :1;
        uint32_t r__2 :4;
    } ch_7;
    uint32_t all;
} dma_ifcr_t;

typedef union {
    struct {
        uint32_t en :1;
        uint32_t tcie :1;
        uint32_t htei :1;
        uint32_t teie :1;
        uint32_t dir :1;
        uint32_t circ :1;
        uint32_t pinc :1;
        uint32_t minc :1;
        uint32_t psize :2;
        uint32_t msize :2;
        uint32_t pl :2;
        uint32_t mem2mem :1;
        uint32_t r__1 :17;
    } b;
    uint32_t all;
} dma_ccr_t;

typedef union {
    struct {
        uint32_t ndt :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} dma_cndtr_t;

typedef union {
    struct {
        uint32_t pa :32;
    } b;
    uint32_t all;
} dma_cpar_t;

typedef union {
    struct {
        uint32_t ma :32;
    } b;
    uint32_t all;
} dma_cmar_t;

typedef union {
    dma_isr_t int_sts;
    dma_ifcr_t int_clr;
    dma_ccr_t ch_cfg;
    dma_cndtr_t data_len;
    dma_cpar_t per_addr;
    dma_cmar_t mem_addr;
} dma_reg_t;


// RTC
#define RTC__CRH    (RTC_BASE + 0x00)
#define RTC__CRL    (RTC_BASE + 0x04)
#define RTC__PRLH   (RTC_BASE + 0x08)
#define RTC__PRLL   (RTC_BASE + 0x0C)
#define RTC__DIVH   (RTC_BASE + 0x10)
#define RTC__DIVL   (RTC_BASE + 0x14)
#define RTC__CNTH   (RTC_BASE + 0x18)
#define RTC__CNTL   (RTC_BASE + 0x1C)
#define RTC__ALRH   (RTC_BASE + 0x20)
#define RTC__ALRL   (RTC_BASE + 0x24)

typedef union {
    struct {
        uint32_t sec_ie :1;
        uint32_t alr_ie :1;
        uint32_t ow_ie :1;
        uint32_t r__1 :29;
    } b;
    uint32_t all;
} rtc_crh_t;

typedef union {
    struct {
        uint32_t secf :1;
        uint32_t alrf :1;
        uint32_t owf :1;
        uint32_t rsf :1;
        uint32_t cnf :1;
        uint32_t rtoff :1;
        uint32_t r__1 :26;
    } b;
    uint32_t all;
} rtc_crl_t;

typedef union {
    struct {
        uint32_t prl :4;
        uint32_t r__1 :28;
    } b;
    uint32_t all;
} rtc_prlh_t;

typedef union {
    struct {
        uint32_t prl :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} rtc_prll_t;

typedef union {
    struct {
        uint32_t div :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} rtc_divh_t;

typedef union {
    struct {
        uint32_t div :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} rtc_divl_t;

typedef union {
    struct {
        uint32_t cnt :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} rtc_cnth_t;

typedef union {
    struct {
        uint32_t cnt :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} rtc_cntl_t;

typedef union {
    struct {
        uint32_t alr :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} rtc_alrh_t;

typedef union {
    struct {
        uint32_t alr :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} rtc_alrl_t;

typedef union {
    rtc_crh_t cr_h;
    rtc_crl_t cr_l;
    rtc_prlh_t prl_h;
    rtc_prll_t prl_l;
    rtc_divh_t div_h;
    rtc_divl_t div_l;
    rtc_cnth_t cnt_h;
    rtc_cntl_t cnt_l;
    rtc_alrh_t alr_h;
    rtc_alrl_t alr_l;
} rtc_reg_t;


// USART
#define USART1__SR    (USART1_BASE + 0x00)
#define USART1__DR    (USART1_BASE + 0x04)
#define USART1__BRR   (USART1_BASE + 0x08)
#define USART1__CR1   (USART1_BASE + 0x0C)
#define USART1__CR2   (USART1_BASE + 0x10)
#define USART1__CR3   (USART1_BASE + 0x14)
#define USART1__GTPR  (USART1_BASE + 0x18)

#define USART2__SR    (USART2_BASE + 0x00)
#define USART2__DR    (USART2_BASE + 0x04)
#define USART2__BRR   (USART2_BASE + 0x08)
#define USART2__CR1   (USART2_BASE + 0x0C)
#define USART2__CR2   (USART2_BASE + 0x10)
#define USART2__CR3   (USART2_BASE + 0x14)
#define USART2__GTPR  (USART2_BASE + 0x18)

typedef union {
    struct {
        uint32_t pe :1;
        uint32_t fe :1;
        uint32_t ne :1;
        uint32_t ore :1;
        uint32_t idle :1;
        uint32_t rxne :1;
        uint32_t tc :1;
        uint32_t txe :1;
        uint32_t lbd :1;
        uint32_t cts :1;
        uint32_t r__1 :22;
    } b;
    uint32_t all;
} usart_sr_t;

typedef union {
    struct {
        uint32_t dr :9;
        uint32_t r__1 :23;
    } b;
    uint32_t all;
} usart_dr_t;

typedef union {
    struct {
        uint32_t fraction :4;
        uint32_t mantissa :12;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} usart_brr_t;

typedef union {
    struct {
        uint32_t sbk :1;
        uint32_t rwu :1;
        uint32_t rx_en :1;
        uint32_t tx_en :1;
        uint32_t idle_ie :1;
        uint32_t rxne_ie :1;
        uint32_t tc_ie :1;
        uint32_t txe_ie :1;
        uint32_t pe_ie :1;
        uint32_t ps :1;
        uint32_t pce :1;
        uint32_t wake :1;
        uint32_t m :1;
        uint32_t en :1;
        uint32_t r__1 :18;
    } b;
    uint32_t all;
} usart_cr1_t;

typedef union {
    struct {
        uint32_t add :4;
        uint32_t r__1 :1;
        uint32_t lbdl :1;
        uint32_t lbd_ie :1;
        uint32_t r__2 :1;
        uint32_t lbcl :1;
        uint32_t cpha :1;
        uint32_t cpol :1;
        uint32_t clk_en :1;
        uint32_t stop :2;
        uint32_t lin_en :1;
        uint32_t r__3 :17;
    } b;
    uint32_t all;
} usart_cr2_t;

typedef union {
    struct {
        uint32_t err_ie :1;
        uint32_t ir_en :1;
        uint32_t ir_lp :1;
        uint32_t hd_sel :1;
        uint32_t nack :1;
        uint32_t sc_en :1;
        uint32_t dmar :1;
        uint32_t dmat :1;
        uint32_t rts_en :1;
        uint32_t cts_en :2;
        uint32_t cts_ie :1;
        uint32_t r__1 :17;
    } b;
    uint32_t all;
} usart_cr3_t;

typedef union {
    struct {
        uint32_t psc :8;
        uint32_t gt :8;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} usart_gtpr_t;

typedef union {
    usart_sr_t sr;
    usart_dr_t dr;
    usart_brr_t brr;
    usart_cr1_t cr1;
    usart_cr2_t cr2;
    usart_cr3_t cr3;
    usart_gtpr_t gtpr;
} usart_reg_t;

// I2C_1
#define I2C1__CR1    (I2C1_BASE + 0x00)
#define I2C1__CR2    (I2C1_BASE + 0x04)
#define I2C1__OAR1   (I2C1_BASE + 0x08)
#define I2C1__OAR2   (I2C1_BASE + 0x0C)
#define I2C1__DR     (I2C1_BASE + 0x10)
#define I2C1__SR1    (I2C1_BASE + 0x14)
#define I2C1__SR2    (I2C1_BASE + 0x18)
#define I2C1__CCR    (I2C1_BASE + 0x1C)
#define I2C1__TRISE  (I2C1_BASE + 0x20)

typedef union {
    struct {
        uint32_t pe :1;
        uint32_t smbus :1;
        uint32_t r__1 :1;
        uint32_t smb_type :1;
        uint32_t en_arp :1;
        uint32_t en_pec :1;
        uint32_t en_gc :1;
        uint32_t no_strech :1;
        uint32_t start :1;
        uint32_t stop :1;
        uint32_t ack :1;
        uint32_t pos :1;
        uint32_t pec :1;
        uint32_t alert :1;
        uint32_t r__2 :1;
        uint32_t sw_rst :1;
        uint32_t r__3 :16;
    } b;
    uint32_t all;
} i2c_cr1_t;

typedef union {
    struct {
        uint32_t freq :6;
        uint32_t r__1 :2;
        uint32_t err_en :1;
        uint32_t evt_en :1;
        uint32_t buff_en :1;
        uint32_t dma_en :1;
        uint32_t last :1;
        uint32_t r__2 :19;
    } b;
    uint32_t all;
} i2c_cr2_t;

typedef union {
    struct {
        uint32_t dr :8;
        uint32_t r__1 :24;
    } b;
    uint32_t all;
} i2c_dr_t;

typedef union {
    struct {
        uint32_t sb :1;
        uint32_t addr :1;
        uint32_t btf :1;
        uint32_t addr10 :1;
        uint32_t stopf :1;
        uint32_t r__1 :1;
        uint32_t rxne :1;
        uint32_t txe :1;
        uint32_t berr :1;
        uint32_t arlo :1;
        uint32_t af :1;
        uint32_t ovr :1;
        uint32_t pec_err :1;
        uint32_t r__2 :1;
        uint32_t tmo :1;
        uint32_t smb_alert :1;
        uint32_t r__3 :16;
    } b;
    uint32_t all;
} i2c_sr1_t;

typedef union {
    struct {
        uint32_t msl :1;
        uint32_t busy :1;
        uint32_t tra :1;
        uint32_t r__1 :1;
        uint32_t gen_call :1;
        uint32_t smbde_fault :1;
        uint32_t smg_host :1;
        uint32_t dualf :1;
        uint32_t pec :8;
        uint32_t r__2 :16;
    } b;
    uint32_t all;
} i2c_sr2_t;

typedef union {
    struct {
        uint32_t ccr :12;
        uint32_t r__1 :2;
        uint32_t duty :1;
        uint32_t f_s :1;
        uint32_t r__2 :16;
    } b;
    uint32_t all;
} i2c_ccr_t;

typedef union {
    struct {
        uint32_t trise :6;
        uint32_t r__1 :26;
    } b;
    uint32_t all;
} i2c_trise_t;

typedef union {
    i2c_cr1_t cr1;
    i2c_cr2_t cr2;
    i2c_dr_t dr;
    i2c_sr1_t sr1;
    i2c_sr2_t sr2;
    i2c_ccr_t ccr;
    i2c_trise_t trise;
} i2c_reg_t;

// I2C_1
#define TIM2__CR1    (TIM2_BASE + 0x00)
#define TIM2__CR2    (TIM2_BASE + 0x04)
#define TIM2__SMCR   (TIM2_BASE + 0x08)
#define TIM2__DIER   (TIM2_BASE + 0x0C)
#define TIM2__SR     (TIM2_BASE + 0x10)
#define TIM2__EGR    (TIM2_BASE + 0x14)
#define TIM2__CCMR1  (TIM2_BASE + 0x18)
#define TIM2__CCMR2  (TIM2_BASE + 0x1C)
#define TIM2__CCER   (TIM2_BASE + 0x20)
#define TIM2__CNT    (TIM2_BASE + 0x24)
#define TIM2__PSC    (TIM2_BASE + 0x28)
#define TIM2__ARR    (TIM2_BASE + 0x2C)

#define TIM2__CCR1   (TIM2_BASE + 0x34)
#define TIM2__CCR2   (TIM2_BASE + 0x38)
#define TIM2__CCR3   (TIM2_BASE + 0x3C)
#define TIM2__CCR4   (TIM2_BASE + 0x40)

#define TIM2__DCR    (TIM2_BASE + 0x48)
#define TIM2__DMAR   (TIM2_BASE + 0x4C)

typedef union {
    struct {
        uint32_t cen :1;
        uint32_t udis :1;
        uint32_t urs :1;
        uint32_t opm :1;
        uint32_t dir :1;
        uint32_t cms :2;
        uint32_t arpe :1;
        uint32_t cdk :2;
        uint32_t r__1 :22;
    } b;
    uint32_t all;
} tim_cr1_t;

typedef union {
    struct {
        uint32_t r__1 :3;
        uint32_t ccds :1;
        uint32_t mms :3;
        uint32_t ti1s :1;
        uint32_t r__2 :24;
    } b;
    uint32_t all;
} tim_cr2_t;

typedef union {
    struct {
        uint32_t sms :3;
        uint32_t r__1 :1;
        uint32_t ts :3;
        uint32_t msm :1;
        uint32_t etf :4;
        uint32_t etps :2;
        uint32_t ece :1;
        uint32_t etp :1;
        uint32_t r__2 :16;
    } b;
    uint32_t all;
} tim_smcr_t;

typedef union {
    struct {
        uint32_t uie :1;
        uint32_t cc1ie :1;
        uint32_t cc2ie :1;
        uint32_t cc3ie :1;
        uint32_t cc4ie :1;
        uint32_t r__1 :1;
        uint32_t tie :1;
        uint32_t r__2 :1;
        uint32_t ude :1;
        uint32_t cc1de :1;
        uint32_t cc2de :1;
        uint32_t cc3de :1;
        uint32_t cc4de :1;
        uint32_t r__3 :1;
        uint32_t tde :1;
        uint32_t r__4 :17;
    } b;
    uint32_t all;
} tim_dier_t;

typedef union {
    struct {
        uint32_t uif :1;
        uint32_t cc1if :1;
        uint32_t cc2if :1;
        uint32_t cc3if :1;
        uint32_t cc4if :1;
        uint32_t r__1 :1;
        uint32_t tif :1;
        uint32_t r__2 :2;
        uint32_t cc1of :1;
        uint32_t cc2of :1;
        uint32_t cc3of :1;
        uint32_t cc4of :1;
        uint32_t r__3 :19;
    } b;
    uint32_t all;
} tim_sr_t;

typedef union {
    struct {
        uint32_t ug :1;
        uint32_t cc1g :1;
        uint32_t cc2g :1;
        uint32_t cc3g :1;
        uint32_t cc4g :1;
        uint32_t r__1 :1;
        uint32_t tg :1;
        uint32_t r__2 :25;
    } b;
    uint32_t all;
} tim_egr_t;

typedef union {
    struct {
        uint32_t cc1s :2;
        uint32_t oc1fe :1;
        uint32_t oc1pe :1;
        uint32_t oc1m :3;
        uint32_t oc1ce :1;
        uint32_t cc2s :2;
        uint32_t oc2fe :1;
        uint32_t oc2pe :1;
        uint32_t oc2m :3;
        uint32_t oc2ce :1;
        uint32_t r__2 :16;
    } b;
    uint32_t all;
} tim_ccmr1_t;

typedef union {
    struct {
        uint32_t cc3s :2;
        uint32_t oc3fe :1;
        uint32_t oc3pe :1;
        uint32_t oc3m :3;
        uint32_t oc3ce :1;
        uint32_t cc4s :2;
        uint32_t oc4fe :1;
        uint32_t oc4pe :1;
        uint32_t oc4m :3;
        uint32_t oc4ce :1;
        uint32_t r__2 :16;
    } b;
    uint32_t all;
} tim_ccmr2_t;

typedef union {
    struct {
        uint32_t cc1e :1;
        uint32_t cc1p :1;
        uint32_t r__1 :2;
        uint32_t cc2e :1;
        uint32_t cc2p :1;
        uint32_t r__2 :2;
        uint32_t cc3e :1;
        uint32_t cc3p :1;
        uint32_t r__3 :2;
        uint32_t cc4e :1;
        uint32_t cc4p :1;
        uint32_t r__4 :18;
    } b;
    uint32_t all;
} tim_ccer_t;

typedef union {
    struct {
        uint32_t cnt :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} tim_cnt_t;

typedef union {
    struct {
        uint32_t psc :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} tim_psc_t;

typedef union {
    struct {
        uint32_t arr :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} tim_arr_t;

typedef union {
    struct {
        uint32_t ccr :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} tim_ccr_t;

typedef union {
    struct {
        uint32_t dba :5;
        uint32_t r__1 :3;
        uint32_t db4 :5;
        uint32_t r__2 :19;
    } b;
    uint32_t all;
} tim_dcr_t;

typedef union {
    struct {
        uint32_t dmab :16;
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} tim_dmar_t;

typedef union {
    tim_cr1_t cr1;
    tim_cr2_t cr2;
    tim_smcr_t smcr;
    tim_dier_t dier;
    tim_sr_t sr;
    tim_egr_t egr;
    tim_ccmr1_t ccmr1;
    tim_ccmr2_t ccmr2;
    tim_ccer_t ccer;
    tim_cnt_t cnt;
    tim_psc_t psc;
    tim_arr_t arr;
    tim_ccr_t ccr;
    tim_dcr_t dcr;
    tim_dmar_t dmar;
} tim_reg_t;

// SPI_1
#define SPI1__CR1    (SPI1_BASE + 0x00)
#define SPI1__CR2    (SPI1_BASE + 0x04)
#define SPI1__SR     (SPI1_BASE + 0x08)
#define SPI1__DR     (SPI1_BASE + 0x0C)

typedef union {
    struct {
        uint32_t clk_pha :1;    // clock phase
        uint32_t clk_pol :1;    // clock polarity
        uint32_t mstr :1;       // master selection
        uint32_t br :3;         // baud rate control
        uint32_t spi_en :1;     // SPI enable
        uint32_t lsb_first :1;  // frame format
        uint32_t ssi :1;        // internal slave select
        uint32_t ssm :1;        // software slave management
        uint32_t rx_only :1;    // Receive only
        uint32_t dff :1;        // data frame format
        uint32_t crc_next :1;   // CRC transfer next
        uint32_t crc_en :1;     // hardware CRC calculation enable
        uint32_t bidir_oe :1;   // output enable in bidirectional mode
        uint32_t bidir_mode :1; // bidirectional data mode enable
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} spi_cr1_t;

typedef union {
    struct {
        uint32_t rx_dma_en :1;  // rx buffer DMA enable
        uint32_t tx_dma_en :1;  // tx buffer DMA enable
        uint32_t ss_oe :1;      // SS output enable
        uint32_t r__1 :2;
        uint32_t err_ie :1;     // error interrupt enable
        uint32_t rxne_ie :1;    // rx buffer not empty interrupt enable
        uint32_t txe_ie :1;     // tx buffer empty interrupt enable
        uint32_t r__2 :24;
    } b;
    uint32_t all;
} spi_cr2_t;

typedef union {
    struct {
        uint32_t rxne :1;    // receive buffer not empty
        uint32_t txe :1;     // transmit buffer empty
        uint32_t chside :1;  // channel side
        uint32_t udr :1;     // underrun flag
        uint32_t crc_err :1; // CRC error flag
        uint32_t modf :1;    // mode fault
        uint32_t ovr :1;     // overrun flag
        uint32_t bsy :1;     // busy flag
        uint32_t r__1 :24;
    } b;
    uint32_t all;
} spi_sr_t;

typedef union {
    struct {
        uint32_t dr :1;    // data register
        uint32_t r__1 :16;
    } b;
    uint32_t all;
} spi_dr_t;

typedef union {
    spi_cr1_t cr1; // SPI control register 1
    spi_cr2_t cr2; // SPI control register 2
    spi_sr_t sr;   // SPI status register
    spi_dr_t dr;   // SPI data register
} spi_reg_t;

// ADC
#define ADC__SR      (ADC1_BASE + 0x00)
#define ADC__CR1     (ADC1_BASE + 0x04)
#define ADC__CR2     (ADC1_BASE + 0x08)
#define ADC__SMPR1   (ADC1_BASE + 0x0C)
#define ADC__SMPR2   (ADC1_BASE + 0x10)
#define ADC__JOFR1   (ADC1_BASE + 0x14)
#define ADC__JOFR2   (ADC1_BASE + 0x18)
#define ADC__JOFR3   (ADC1_BASE + 0x1C)
#define ADC__JOFR4   (ADC1_BASE + 0x20)
#define ADC__HTR     (ADC1_BASE + 0x24)
#define ADC__LTR     (ADC1_BASE + 0x28)
#define ADC__SQR1    (ADC1_BASE + 0x2C)
#define ADC__SQR2    (ADC1_BASE + 0x30)
#define ADC__SQR3    (ADC1_BASE + 0x34)
#define ADC__JSQR    (ADC1_BASE + 0x38)
#define ADC__JDR1    (ADC1_BASE + 0x3C)
#define ADC__JDR2    (ADC1_BASE + 0x40)
#define ADC__JDR3    (ADC1_BASE + 0x44)
#define ADC__JDR4    (ADC1_BASE + 0x48)
#define ADC__DR      (ADC1_BASE + 0x4C)

typedef union {
    struct {
        uint32_t awd :1;   // analog watchdog flag
        uint32_t eoc :1;   // end of conversion
        uint32_t jeoc :1;  // injected channel end of conversion
        uint32_t jstrt :1; // injected channel start flag
        uint32_t strt :1;  // regular channel start flag
        uint32_t r__2 :27;
    } b;
    uint32_t all;
} adc_sr_t;

typedef union {
    struct {
        uint32_t awd_ch :5;   // analog watchdog channel select bits
        uint32_t eoc_ie :1;   // interrupt enable for EOC
        uint32_t awd_ie :1;   // analog watchdog interrupt enable
        uint32_t jeoc_ie :1;  // interrupt enable for injected channels
        uint32_t scan :1;     // scan mode
        uint32_t awd_sgl :1;  // enable the watchdog on a single channel in scan mode
        uint32_t jauto :1;    // automatic injected group conversion
        uint32_t disc_en :1;  // discontinuous mode on regular channels
        uint32_t jdisc_en :1; // discontinuous mode on injected channels
        uint32_t disc_num :3; // discontinuous mode channel count
        uint32_t dual_mod :4; // dual mode selection
        uint32_t r__1 :2;
        uint32_t jawd_en :1;  // analog watchdog enable on injected channels
        uint32_t awd_en :1;   // analog watchdog enable on regular channels
        uint32_t r__2 :8;
    } b;
    uint32_t all;
} adc_cr1_t;

typedef union {
    struct {
        uint32_t ad_on :1;      // A/D converter ON / OFF
        uint32_t cont :1;       // continuous conversion
        uint32_t cal :1;        // A/D calibration
        uint32_t rst_cal :1;    // reset calibration
        uint32_t r__1 :4;
        uint32_t dma :1;        // direct memory access mode
        uint32_t r__2 :2;
        uint32_t align :1;      // data alignment
        uint32_t jext_sel :3;   // external event select for injected group
        uint32_t jext_trig :1;  // external trigger conversion mode for injected channels
        uint32_t r__3 :1;       // dual mode selection
        uint32_t ext_sel :3;    // external event select for regular group
        uint32_t ext_trig :1;   // external trigger conversion mode for regular channels
        uint32_t jsw_start :1;  // start conversion of injected channels
        uint32_t sw_start :1;   // start conversion of regular channels
        uint32_t ts_vref_en :1; // temperature sensor and VREFINT enable
        uint32_t r__4 :8;
    } b;
    uint32_t all;
} adc_cr2_t;

typedef union {
    struct {
        uint32_t smp10 :3; // channel 10 sample time selection
        uint32_t smp11 :3;
        uint32_t smp12 :3;
        uint32_t smp13 :3;
        uint32_t smp14 :3;
        uint32_t smp15 :3;
        uint32_t smp16 :3;
        uint32_t smp17 :3;
        uint32_t r__1 :8;
    } b;
    uint32_t all;
} adc_smpr1_t;

typedef union {
    struct {
        uint32_t smp0 :3; // channel 0 sample time selection
        uint32_t smp1 :3;
        uint32_t smp2 :3;
        uint32_t smp3 :3;
        uint32_t smp4 :3;
        uint32_t smp5 :3;
        uint32_t smp6 :3;
        uint32_t smp7 :3;
        uint32_t smp8 :3;
        uint32_t smp9 :3;
        uint32_t r__1 :8;
    } b;
    uint32_t all;
} adc_smpr2_t;

typedef union {
    struct {
        uint32_t joffset :12; // data offset for injected channel x
        uint32_t r__1 :20;
    } b;
    uint32_t all;
} adc_jofr_t;

typedef union {
    struct {
        uint32_t ht :12; // analog watchdog high threshold
        uint32_t r__1 :20;
    } b;
    uint32_t all;
} adc_htr_t;

typedef union {
    struct {
        uint32_t lt :12; // analog watchdog low threshold
        uint32_t r__1 :20;
    } b;
    uint32_t all;
} adc_ltr_t;

typedef union {
    struct {
        uint32_t sq13 :5; // 13th conversion in regular sequence
        uint32_t sq14 :5; // 14th conversion in regular sequence
        uint32_t sq15 :5; // 15th conversion in regular sequence
        uint32_t sq16 :5; // 16th conversion in regular sequence
        uint32_t len :4;  // regular channel sequence length
        uint32_t r__1 :8;
    } b;
    uint32_t all;
} adc_sqr1_t;

typedef union {
    struct {
        uint32_t sq7 :5;  // 7th conversion in regular sequence
        uint32_t sq8 :5;  // 8th conversion in regular sequence
        uint32_t sq9 :5;  // 8th conversion in regular sequence
        uint32_t sq10 :5; // 10th conversion in regular sequence
        uint32_t sq11 :5; // 11th conversion in regular sequence
        uint32_t sq12 :5; // 12th conversion in regular sequence
        uint32_t r__1 :2;
    } b;
    uint32_t all;
} adc_sqr2_t;

typedef union {
    struct {
        uint32_t sq1 :5; // first conversion in regular sequence
        uint32_t sq2 :5; // second conversion in regular sequence
        uint32_t sq3 :5; // third conversion in regular sequence
        uint32_t sq4 :5; // 4th conversion in regular sequence
        uint32_t sq5 :5; // 5th conversion in regular sequence
        uint32_t sq6 :5; // 6th conversion in regular sequence
        uint32_t r__1 :2;
    } b;
    uint32_t all;
} adc_sqr3_t;

typedef union {
    struct {
        uint32_t jsq1 :5; // first conversion in injected sequence (when JL[1:0] = 3)
        uint32_t jsq2 :5; // second conversion in injected sequence (when JL[1:0] = 3)
        uint32_t jsq3 :5; // third conversion in injected sequence (when JL[1:0] = 3)
        uint32_t jsq4 :5; // fourth conversion in injected sequence (when JL[1:0] = 3)
        uint32_t jlen :4;  // injected sequence length
        uint32_t r__1 :8;
    } b;
    uint32_t all;
} adc_jsqr_t;

typedef union {
    struct {
        uint32_t jdata :16; // injected data
        uint32_t r__1 :8;
    } b;
    uint32_t all;
} adc_jdr_t;

typedef union {
    struct {
        uint32_t data :16; // regular data
        uint32_t adc2_data :16; // ADC2 data
    } b;
    uint32_t all;
} adc_dr_t;

typedef union {
    adc_sr_t sr;       // status register
    adc_cr1_t cr1;     // control register 1
    adc_cr2_t cr2;     // control register 2
    adc_smpr1_t smpr1; // sample time register 1
    adc_smpr2_t smpr2; // sample time register 2
    adc_jofr_t jofr;   // injected channel data offset register
    adc_htr_t htr;     // watchdog high threshold register
    adc_htr_t ltr;     // watchdog low threshold register
    adc_sqr1_t sqr1;   // regular sequence register 1
    adc_sqr2_t sqr2;   // regular sequence register 2
    adc_sqr3_t sqr3;   // regular sequence register 3
    adc_jsqr_t jsqr;   // injected sequence register
    adc_jdr_t jdr;     // injected data register
    adc_jdr_t dr;      // regular data register
} adc_reg_t;

// SYSTICK
#define SYSTICK__CTRL      (SysTick_BASE + 0x00)
#define SYSTICK__LOAD      (SysTick_BASE + 0x04)
#define SYSTICK__VAL       (SysTick_BASE + 0x08)

typedef union {
    struct {
        uint32_t enable :1;   // counter enable
        uint32_t tick_int :1; // systick exception request enable
        uint32_t clk_src :1;  // clock source selection
        uint32_t r__1 :13;
        uint32_t cnt_flag :1; // returns 1 if timer counted to 0 since last time this was read.
        uint32_t r__2 :15;
    } b;
    uint32_t all;
} systick_ctrl_t;

typedef union {
    struct {
        uint32_t reload :24; // counter enable
        uint32_t r__1 :8;
    } b;
    uint32_t all;
} systick_load_t;

typedef union {
    struct {
        uint32_t current :24; // current counter value
        uint32_t r__1 :8;
    } b;
    uint32_t all;
} systick_val_t;

typedef union {
    systick_ctrl_t ctrl; // systick control and status register
    systick_load_t load; // systick reload value register
    systick_val_t val;   // systick current value register
} systick_reg_t;

#endif /* REGS32_DEF_H_ */
