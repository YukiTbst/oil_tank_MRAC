/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MRAC_for_coder_slower_private.h
 *
 * Code generated for Simulink model 'MRAC_for_coder_slower'.
 *
 * Model version                  : 9.1
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Wed Nov 23 19:46:40 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MRAC_for_coder_slower_private_h_
#define RTW_HEADER_MRAC_for_coder_slower_private_h_
#include "rtwtypes.h"
#include "MRAC_for_coder_slower_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

/* private model entry point functions */
extern void MRAC_for_coder_slower_derivatives(void);

#endif                         /* RTW_HEADER_MRAC_for_coder_slower_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
