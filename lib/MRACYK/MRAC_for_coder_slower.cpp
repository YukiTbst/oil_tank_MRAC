/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MRAC_for_coder_slower.c
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

#include "MRAC_for_coder_slower.h"
#include "rtwtypes.h"
#include "MRAC_for_coder_slower_private.h"

/* Exported data definition */

/* Data with Exported storage */
real_T MRAC_for_co__InitialCondition_a = 0.0;/* Referenced by: '<Root>/�Ŷ��۲���' */
real_T MRAC_for_co_k1_InitialCondition[2] = { 0.0, 0.0 } ;/* Referenced by: '<Root>/����k1' */

real_T MRAC_for_co_k2_InitialCondition = 0.0;/* Referenced by: '<Root>/����k2' */
real_T MRAC_for_code__InitialCondition[2] = { 0.0, 0.0 } ;/* Referenced by: '<Root>/�ο�ģ��' */

real_T MRAC_for_code_controller_output;/* '<Root>/controller_output' */
real_T MRAC_for_coder__Constant2_Value[2] = { 5.0, 2.75 } ;/* Referenced by: '<Root>/Constant2' */                                              //init:25, 65

real_T MRAC_for_coder__Constant3_Value[2] = { 1.0, 2.6 } ;/* Referenced by: '<Root>/Constant3' */

real_T MRAC_for_coder_slowe_Gain1_Gain = 10.0;/* Referenced by: '<Root>/Gain1' */
real_T MRAC_for_coder_slowe_Gain2_Gain = 10.0;/* Referenced by: '<Root>/Gain2' */
real_T MRAC_for_coder_slower_Gain[2];  /* '<Root>/Gain' */
real_T MRAC_for_coder_slower_Gain1;    /* '<Root>/Gain1' */
real_T MRAC_for_coder_slower_Gain2;    /* '<Root>/Gain2' */
real_T MRAC_for_coder_slower_Gain_Gain = 1.0;/* Referenced by: '<Root>/Gain' */
real_T MRAC_for_coder_slower__A[4] = { 0.0, -1.0, 1.0, -2.0 } ;/* Referenced by: '<Root>/�ο�ģ��' */

real_T MRAC_for_coder_slower__A_b = 0.0;/* Referenced by: '<Root>/�Ŷ��۲���' */
real_T MRAC_for_coder_slower__B[2] = { 0.0, 1.0 } ;/* Referenced by: '<Root>/�ο�ģ��' */

real_T MRAC_for_coder_slower__B_m = 1.0;/* Referenced by: '<Root>/�Ŷ��۲���' */
real_T MRAC_for_coder_slower__C[4] = { 1.0, 0.0, 0.0, 1.0 } ;/* Referenced by: '<Root>/�ο�ģ��' */

real_T MRAC_for_coder_slower__C_k = 1.0;/* Referenced by: '<Root>/�Ŷ��۲���' */
real_T MRAC_for_coder_slower_k1_A[4] = { 0.0, 0.0, 0.0, 0.0 } ;/* Referenced by: '<Root>/����k1' */

real_T MRAC_for_coder_slower_k1_B[4] = { 1.0, 0.0, 0.0, 1.0 } ;/* Referenced by: '<Root>/����k1' */

real_T MRAC_for_coder_slower_k1_C[4] = { 1.0, 0.0, 0.0, 1.0 } ;/* Referenced by: '<Root>/����k1' */

real_T MRAC_for_coder_slower_k2_A = 0.0;/* Referenced by: '<Root>/����k2' */
real_T MRAC_for_coder_slower_k2_B = 1.0;/* Referenced by: '<Root>/����k2' */
real_T MRAC_for_coder_slower_k2_C = 1.0;/* Referenced by: '<Root>/����k2' */
real_T MRAC_for_coder_slower_omega;    /* '<Root>/omega' */
real_T MRAC_for_coder_slower_ref;      /* '<Root>/ref' */
real_T MRAC_for_coder_slower_theta;    /* '<Root>/theta' */

/* Continuous states */
X_MRAC_for_coder_slower_T MRAC_for_coder_slower_X;

/* Real-time model */
static RT_MODEL_MRAC_for_coder_slowe_T MRAC_for_coder_slower_M_;
RT_MODEL_MRAC_for_coder_slowe_T *const MRAC_for_coder_slower_M =
  &MRAC_for_coder_slower_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  MRAC_for_coder_slower_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  MRAC_for_coder_slower_step();
  MRAC_for_coder_slower_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  MRAC_for_coder_slower_step();
  MRAC_for_coder_slower_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void MRAC_for_coder_slower_step(void)
{
  real_T rtb_DotProduct3_0;
  real_T rtb_e_idx_0;
  real_T rtb_e_idx_1;
  if (rtmIsMajorTimeStep(MRAC_for_coder_slower_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&MRAC_for_coder_slower_M->solverInfo,
                          ((MRAC_for_coder_slower_M->Timing.clockTick0+1)*
      MRAC_for_coder_slower_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(MRAC_for_coder_slower_M)) {
    MRAC_for_coder_slower_M->Timing.t[0] = rtsiGetT
      (&MRAC_for_coder_slower_M->solverInfo);
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/omega'
   *  Inport: '<Root>/theta'
   *  StateSpace: '<Root>/�ο�ģ��'
   */
  rtb_e_idx_0 = (MRAC_for_coder_slower__C[0] * MRAC_for_coder_slower_X._CSTATE[0]
                 + MRAC_for_coder_slower_X._CSTATE[1] *
                 MRAC_for_coder_slower__C[2]) - MRAC_for_coder_slower_theta;
  rtb_e_idx_1 = (MRAC_for_coder_slower_X._CSTATE[0] * MRAC_for_coder_slower__C[1]
                 + MRAC_for_coder_slower_X._CSTATE[1] *
                 MRAC_for_coder_slower__C[3]) - MRAC_for_coder_slower_omega;

  /* DotProduct: '<Root>/Dot Product2' incorporates:
   *  Constant: '<Root>/Constant2'
   */
  rtb_DotProduct3_0 = MRAC_for_coder__Constant2_Value[0] * rtb_e_idx_0 +
    MRAC_for_coder__Constant2_Value[1] * rtb_e_idx_1;

  /* Gain: '<Root>/Gain1' incorporates:
   *  DotProduct: '<Root>/Dot Product2'
   *  Inport: '<Root>/ref'
   *  Product: '<Root>/Product1'
   */
  MRAC_for_coder_slower_Gain1 = rtb_DotProduct3_0 * MRAC_for_coder_slower_ref *
    MRAC_for_coder_slowe_Gain1_Gain;

  /* Gain: '<Root>/Gain' incorporates:
   *  DotProduct: '<Root>/Dot Product2'
   *  Inport: '<Root>/omega'
   *  Inport: '<Root>/theta'
   *  Product: '<Root>/Product'
   */
  MRAC_for_coder_slower_Gain[0] = rtb_DotProduct3_0 *
    MRAC_for_coder_slower_theta * MRAC_for_coder_slower_Gain_Gain;
  MRAC_for_coder_slower_Gain[1] = rtb_DotProduct3_0 *
    MRAC_for_coder_slower_omega * MRAC_for_coder_slower_Gain_Gain;

  /* Gain: '<Root>/Gain2' incorporates:
   *  Constant: '<Root>/Constant3'
   *  DotProduct: '<Root>/Dot Product4'
   */
  MRAC_for_coder_slower_Gain2 = (rtb_e_idx_0 * MRAC_for_coder__Constant3_Value[0]
    + rtb_e_idx_1 * MRAC_for_coder__Constant3_Value[1]) *
    MRAC_for_coder_slowe_Gain2_Gain;

  /* Outport: '<Root>/controller_output' incorporates:
   *  DotProduct: '<Root>/Dot Product3'
   *  Inport: '<Root>/omega'
   *  Inport: '<Root>/ref'
   *  Inport: '<Root>/theta'
   *  Product: '<Root>/Product2'
   *  StateSpace: '<Root>/����k1'
   *  StateSpace: '<Root>/����k2'
   *  StateSpace: '<Root>/�Ŷ��۲���'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<Root>/Sum2'
   */
  MRAC_for_code_controller_output = (((MRAC_for_coder_slower_k1_C[0] *
    MRAC_for_coder_slower_X.k1_CSTATE[0] + MRAC_for_coder_slower_X.k1_CSTATE[1] *
    MRAC_for_coder_slower_k1_C[2]) * MRAC_for_coder_slower_theta +
    (MRAC_for_coder_slower_X.k1_CSTATE[0] * MRAC_for_coder_slower_k1_C[1] +
     MRAC_for_coder_slower_X.k1_CSTATE[1] * MRAC_for_coder_slower_k1_C[3]) *
    MRAC_for_coder_slower_omega) + MRAC_for_coder_slower_k2_C *
    MRAC_for_coder_slower_X.k2_CSTATE * MRAC_for_coder_slower_ref) +
    MRAC_for_coder_slower__C_k * MRAC_for_coder_slower_X._CSTATE_j;
  if (rtmIsMajorTimeStep(MRAC_for_coder_slower_M)) {
    rt_ertODEUpdateContinuousStates(&MRAC_for_coder_slower_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++MRAC_for_coder_slower_M->Timing.clockTick0;
    MRAC_for_coder_slower_M->Timing.t[0] = rtsiGetSolverStopTime
      (&MRAC_for_coder_slower_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      MRAC_for_coder_slower_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void MRAC_for_coder_slower_derivatives(void)
{
  XDot_MRAC_for_coder_slower_T *_rtXdot;
  _rtXdot = ((XDot_MRAC_for_coder_slower_T *) MRAC_for_coder_slower_M->derivs);

  /* Derivatives for StateSpace: '<Root>/����k1' */
  _rtXdot->k1_CSTATE[0] = MRAC_for_coder_slower_k1_A[0] *
    MRAC_for_coder_slower_X.k1_CSTATE[0];
  _rtXdot->k1_CSTATE[0] += MRAC_for_coder_slower_X.k1_CSTATE[1] *
    MRAC_for_coder_slower_k1_A[2];
  _rtXdot->k1_CSTATE[0] += MRAC_for_coder_slower_k1_B[0] *
    MRAC_for_coder_slower_Gain[0];

  /* Derivatives for StateSpace: '<Root>/�ο�ģ��' */
  _rtXdot->_CSTATE[0] = MRAC_for_coder_slower__A[0] *
    MRAC_for_coder_slower_X._CSTATE[0];

  /* Derivatives for StateSpace: '<Root>/����k1' */
  _rtXdot->k1_CSTATE[0] += MRAC_for_coder_slower_Gain[1] *
    MRAC_for_coder_slower_k1_B[2];

  /* Derivatives for StateSpace: '<Root>/�ο�ģ��' incorporates:
   *  Inport: '<Root>/ref'
   */
  _rtXdot->_CSTATE[0] += MRAC_for_coder_slower_X._CSTATE[1] *
    MRAC_for_coder_slower__A[2];
  _rtXdot->_CSTATE[0] += MRAC_for_coder_slower__B[0] * MRAC_for_coder_slower_ref;

  /* Derivatives for StateSpace: '<Root>/����k1' */
  _rtXdot->k1_CSTATE[1] = MRAC_for_coder_slower_X.k1_CSTATE[0] *
    MRAC_for_coder_slower_k1_A[1];
  _rtXdot->k1_CSTATE[1] += MRAC_for_coder_slower_X.k1_CSTATE[1] *
    MRAC_for_coder_slower_k1_A[3];
  _rtXdot->k1_CSTATE[1] += MRAC_for_coder_slower_Gain[0] *
    MRAC_for_coder_slower_k1_B[1];

  /* Derivatives for StateSpace: '<Root>/�ο�ģ��' */
  _rtXdot->_CSTATE[1] = MRAC_for_coder_slower_X._CSTATE[0] *
    MRAC_for_coder_slower__A[1];

  /* Derivatives for StateSpace: '<Root>/����k1' */
  _rtXdot->k1_CSTATE[1] += MRAC_for_coder_slower_Gain[1] *
    MRAC_for_coder_slower_k1_B[3];

  /* Derivatives for StateSpace: '<Root>/�ο�ģ��' incorporates:
   *  Inport: '<Root>/ref'
   */
  _rtXdot->_CSTATE[1] += MRAC_for_coder_slower_X._CSTATE[1] *
    MRAC_for_coder_slower__A[3];
  _rtXdot->_CSTATE[1] += MRAC_for_coder_slower__B[1] * MRAC_for_coder_slower_ref;

  /* Derivatives for StateSpace: '<Root>/����k2' */
  _rtXdot->k2_CSTATE = MRAC_for_coder_slower_k2_A *
    MRAC_for_coder_slower_X.k2_CSTATE;
  _rtXdot->k2_CSTATE += MRAC_for_coder_slower_k2_B * MRAC_for_coder_slower_Gain1;

  /* Derivatives for StateSpace: '<Root>/�Ŷ��۲���' */
  _rtXdot->_CSTATE_j = MRAC_for_coder_slower__A_b *
    MRAC_for_coder_slower_X._CSTATE_j;
  _rtXdot->_CSTATE_j += MRAC_for_coder_slower__B_m * MRAC_for_coder_slower_Gain2;
}

/* Model initialize function */
void MRAC_for_coder_slower_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&MRAC_for_coder_slower_M->solverInfo,
                          &MRAC_for_coder_slower_M->Timing.simTimeStep);
    rtsiSetTPtr(&MRAC_for_coder_slower_M->solverInfo, &rtmGetTPtr
                (MRAC_for_coder_slower_M));
    rtsiSetStepSizePtr(&MRAC_for_coder_slower_M->solverInfo,
                       &MRAC_for_coder_slower_M->Timing.stepSize0);
    rtsiSetdXPtr(&MRAC_for_coder_slower_M->solverInfo,
                 &MRAC_for_coder_slower_M->derivs);
    rtsiSetContStatesPtr(&MRAC_for_coder_slower_M->solverInfo, (real_T **)
                         &MRAC_for_coder_slower_M->contStates);
    rtsiSetNumContStatesPtr(&MRAC_for_coder_slower_M->solverInfo,
      &MRAC_for_coder_slower_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&MRAC_for_coder_slower_M->solverInfo,
      &MRAC_for_coder_slower_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&MRAC_for_coder_slower_M->solverInfo,
      &MRAC_for_coder_slower_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&MRAC_for_coder_slower_M->solverInfo,
      &MRAC_for_coder_slower_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&MRAC_for_coder_slower_M->solverInfo,
                          (&rtmGetErrorStatus(MRAC_for_coder_slower_M)));
    rtsiSetRTModelPtr(&MRAC_for_coder_slower_M->solverInfo,
                      MRAC_for_coder_slower_M);
  }

  rtsiSetSimTimeStep(&MRAC_for_coder_slower_M->solverInfo, MAJOR_TIME_STEP);
  MRAC_for_coder_slower_M->intgData.y = MRAC_for_coder_slower_M->odeY;
  MRAC_for_coder_slower_M->intgData.f[0] = MRAC_for_coder_slower_M->odeF[0];
  MRAC_for_coder_slower_M->intgData.f[1] = MRAC_for_coder_slower_M->odeF[1];
  MRAC_for_coder_slower_M->intgData.f[2] = MRAC_for_coder_slower_M->odeF[2];
  MRAC_for_coder_slower_M->contStates = ((X_MRAC_for_coder_slower_T *)
    &MRAC_for_coder_slower_X);
  rtsiSetSolverData(&MRAC_for_coder_slower_M->solverInfo, (void *)
                    &MRAC_for_coder_slower_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&MRAC_for_coder_slower_M->solverInfo,
    false);
  rtsiSetSolverName(&MRAC_for_coder_slower_M->solverInfo,"ode3");
  rtmSetTPtr(MRAC_for_coder_slower_M, &MRAC_for_coder_slower_M->Timing.tArray[0]);
  MRAC_for_coder_slower_M->Timing.stepSize0 = 0.01;

  /* InitializeConditions for StateSpace: '<Root>/����k1' */
  MRAC_for_coder_slower_X.k1_CSTATE[0] = MRAC_for_co_k1_InitialCondition[0];

  /* InitializeConditions for StateSpace: '<Root>/�ο�ģ��' */
  MRAC_for_coder_slower_X._CSTATE[0] = MRAC_for_code__InitialCondition[0];

  /* InitializeConditions for StateSpace: '<Root>/����k1' */
  MRAC_for_coder_slower_X.k1_CSTATE[1] = MRAC_for_co_k1_InitialCondition[1];

  /* InitializeConditions for StateSpace: '<Root>/�ο�ģ��' */
  MRAC_for_coder_slower_X._CSTATE[1] = MRAC_for_code__InitialCondition[1];

  /* InitializeConditions for StateSpace: '<Root>/����k2' */
  MRAC_for_coder_slower_X.k2_CSTATE = MRAC_for_co_k2_InitialCondition;

  /* InitializeConditions for StateSpace: '<Root>/�Ŷ��۲���' */
  MRAC_for_coder_slower_X._CSTATE_j = MRAC_for_co__InitialCondition_a;
}

/* Model terminate function */
void MRAC_for_coder_slower_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
