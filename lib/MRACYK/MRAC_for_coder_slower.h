/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MRAC_for_coder_slower.h
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

#ifndef RTW_HEADER_MRAC_for_coder_slower_h_
#define RTW_HEADER_MRAC_for_coder_slower_h_
#ifndef MRAC_for_coder_slower_COMMON_INCLUDES_
#define MRAC_for_coder_slower_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                              /* MRAC_for_coder_slower_COMMON_INCLUDES_ */

#include "MRAC_for_coder_slower_types.h"
#include <string.h>
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Continuous states (default storage) */
typedef struct {
  real_T k1_CSTATE[2];                 /* '<Root>/变量k1' */
  real_T _CSTATE[2];                   /* '<Root>/参考模型' */
  real_T k2_CSTATE;                    /* '<Root>/变量k2' */
  real_T _CSTATE_j;                    /* '<Root>/扰动观测器' */
} X_MRAC_for_coder_slower_T;

/* State derivatives (default storage) */
typedef struct {
  real_T k1_CSTATE[2];                 /* '<Root>/变量k1' */
  real_T _CSTATE[2];                   /* '<Root>/参考模型' */
  real_T k2_CSTATE;                    /* '<Root>/变量k2' */
  real_T _CSTATE_j;                    /* '<Root>/扰动观测器' */
} XDot_MRAC_for_coder_slower_T;

/* State disabled  */
typedef struct {
  boolean_T k1_CSTATE[2];              /* '<Root>/变量k1' */
  boolean_T _CSTATE[2];                /* '<Root>/参考模型' */
  boolean_T k2_CSTATE;                 /* '<Root>/变量k2' */
  boolean_T _CSTATE_j;                 /* '<Root>/扰动观测器' */
} XDis_MRAC_for_coder_slower_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Real-time Model Data Structure */
struct tag_RTM_MRAC_for_coder_slower_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_MRAC_for_coder_slower_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_MRAC_for_coder_slower_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[6];
  real_T odeF[3][6];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Continuous states (default storage) */
extern X_MRAC_for_coder_slower_T MRAC_for_coder_slower_X;

/* Model entry point functions */
extern void MRAC_for_coder_slower_initialize(void);
extern void MRAC_for_coder_slower_step(void);
extern void MRAC_for_coder_slower_terminate(void);

/* Exported data declaration */

/* Data with Exported storage */
extern real_T MRAC_for_co__InitialCondition_a;/* Referenced by: '<Root>/扰动观测器' */
extern real_T MRAC_for_co_k1_InitialCondition[2];/* Referenced by: '<Root>/变量k1' */
extern real_T MRAC_for_co_k2_InitialCondition;/* Referenced by: '<Root>/变量k2' */
extern real_T MRAC_for_code__InitialCondition[2];/* Referenced by: '<Root>/参考模型' */
extern real_T MRAC_for_code_controller_output;/* '<Root>/controller_output' */
extern real_T MRAC_for_coder__Constant2_Value[2];/* Referenced by: '<Root>/Constant2' */
extern real_T MRAC_for_coder__Constant3_Value[2];/* Referenced by: '<Root>/Constant3' */
extern real_T MRAC_for_coder_slowe_Gain1_Gain;/* Referenced by: '<Root>/Gain1' */
extern real_T MRAC_for_coder_slowe_Gain2_Gain;/* Referenced by: '<Root>/Gain2' */
extern real_T MRAC_for_coder_slower_Gain[2];/* '<Root>/Gain' */
extern real_T MRAC_for_coder_slower_Gain1;/* '<Root>/Gain1' */
extern real_T MRAC_for_coder_slower_Gain2;/* '<Root>/Gain2' */
extern real_T MRAC_for_coder_slower_Gain_Gain;/* Referenced by: '<Root>/Gain' */
extern real_T MRAC_for_coder_slower__A[4];/* Referenced by: '<Root>/参考模型' */
extern real_T MRAC_for_coder_slower__A_b;/* Referenced by: '<Root>/扰动观测器' */
extern real_T MRAC_for_coder_slower__B[2];/* Referenced by: '<Root>/参考模型' */
extern real_T MRAC_for_coder_slower__B_m;/* Referenced by: '<Root>/扰动观测器' */
extern real_T MRAC_for_coder_slower__C[4];/* Referenced by: '<Root>/参考模型' */
extern real_T MRAC_for_coder_slower__C_k;/* Referenced by: '<Root>/扰动观测器' */
extern real_T MRAC_for_coder_slower_k1_A[4];/* Referenced by: '<Root>/变量k1' */
extern real_T MRAC_for_coder_slower_k1_B[4];/* Referenced by: '<Root>/变量k1' */
extern real_T MRAC_for_coder_slower_k1_C[4];/* Referenced by: '<Root>/变量k1' */
extern real_T MRAC_for_coder_slower_k2_A;/* Referenced by: '<Root>/变量k2' */
extern real_T MRAC_for_coder_slower_k2_B;/* Referenced by: '<Root>/变量k2' */
extern real_T MRAC_for_coder_slower_k2_C;/* Referenced by: '<Root>/变量k2' */
extern real_T MRAC_for_coder_slower_omega;/* '<Root>/omega' */
extern real_T MRAC_for_coder_slower_ref;/* '<Root>/ref' */
extern real_T MRAC_for_coder_slower_theta;/* '<Root>/theta' */

/* Real-time Model object */
extern RT_MODEL_MRAC_for_coder_slowe_T *const MRAC_for_coder_slower_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MRAC_for_coder_slower'
 */
#endif                                 /* RTW_HEADER_MRAC_for_coder_slower_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
