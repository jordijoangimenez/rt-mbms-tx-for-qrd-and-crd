/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2020 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

/*!
 * \file utils_avx512.h
 * \brief Declarations of AVX512-related quantities and functions.
 * \author Jesus Gomez
 * \date 2020
 *
 * \copyright Software Radio Systems Limited
 *
 */

#ifndef SRSLTE_UTILS_AVX512_H
#define SRSLTE_UTILS_AVX512_H

#define SRSLTE_AVX512_B_SIZE 64    /*!< \brief Number of packed bytes in an AVX512 instruction. */
#define SRSLTE_AVX512_B_SIZE_LOG 6 /*!< \brief \f$\log_2\f$ of \ref SRSLTE_AVX512_B_SIZE. */

#endif // SRSLTE_UTILS_AVX512_H