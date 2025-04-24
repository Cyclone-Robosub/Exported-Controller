/*
 * ControllerForExport.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ControllerForExport".
 *
 * Model version              : 1.1
 * Simulink Coder version : 24.1 (R2024a) 19-Nov-2023
 * C++ source code generated on : Tue Apr 22 13:59:47 2025
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "ControllerForExport.h"
#include "ControllerForExport_private.h"
#include <cmath>
#include "rtwtypes.h"
#include "cmath"

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void ControllerForExport::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3]{
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3]{
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE3_IntgData *id { static_cast<ODE3_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T hB[3];
  int_T i;
  int_T nXc { 12 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  ControllerForExport_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  ControllerForExport_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  ControllerForExport_derivatives();

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

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (std::isinf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

/* Model step function */
void ControllerForExport::step()
{
  real_T tmp[6];
  const real_T *tmp_0;
  real_T DerivativeGain;
  real_T ErrorSIgnal;
  real_T Filter_b;
  real_T Integrator;
  real_T y;
  int32_T i;
  int32_T i_0;
  int8_T DataTypeConv1;
  int8_T DataTypeConv2;
  boolean_T Equal1;
  boolean_T NotEqual;
  if (rtmIsMajorTimeStep((&ControllerForExport_M))) {
    /* set solver stop time */
    if (!((&ControllerForExport_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&ControllerForExport_M)->solverInfo,
                            (((&ControllerForExport_M)->Timing.clockTickH0 + 1) *
        (&ControllerForExport_M)->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&ControllerForExport_M)->solverInfo,
                            (((&ControllerForExport_M)->Timing.clockTick0 + 1) *
        (&ControllerForExport_M)->Timing.stepSize0 + (&ControllerForExport_M)
        ->Timing.clockTickH0 * (&ControllerForExport_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&ControllerForExport_M))) {
    (&ControllerForExport_M)->Timing.t[0] = rtsiGetT(&(&ControllerForExport_M)
      ->solverInfo);
  }

  /* Gain: '<S44>/Proportional Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ErrorSIgnal = ControllerForExport_U.ErrorSIgnal[0];

  /* Gain: '<S44>/Proportional Gain' */
  y = ControllerForExport_P.kp_F * ErrorSIgnal;
  ControllerForExport_B.ProportionalGain[0] = y;

  /* Integrator: '<S39>/Integrator' */
  Integrator = ControllerForExport_X.Integrator_CSTATE[0];
  ControllerForExport_B.Integrator[0] = Integrator;

  /* Gain: '<S32>/Derivative Gain' */
  DerivativeGain = ControllerForExport_P.kd_F * ErrorSIgnal;
  ControllerForExport_B.DerivativeGain[0] = DerivativeGain;

  /* Integrator: '<S34>/Filter' */
  ErrorSIgnal = ControllerForExport_X.Filter_CSTATE[0];
  ControllerForExport_B.Filter[0] = ErrorSIgnal;

  /* Sum: '<S34>/SumD' incorporates:
   *  Gain: '<S32>/Derivative Gain'
   *  Integrator: '<S34>/Filter'
   */
  DerivativeGain -= ErrorSIgnal;
  ControllerForExport_B.SumD[0] = DerivativeGain;

  /* Gain: '<S42>/Filter Coefficient' incorporates:
   *  Sum: '<S34>/SumD'
   */
  DerivativeGain *= ControllerForExport_P.ForcePID_N;
  ControllerForExport_B.FilterCoefficient[0] = DerivativeGain;

  /* Sum: '<S48>/Sum' incorporates:
   *  Gain: '<S42>/Filter Coefficient'
   *  Gain: '<S44>/Proportional Gain'
   *  Integrator: '<S39>/Integrator'
   */
  ControllerForExport_B.Sum[0] = (y + Integrator) + DerivativeGain;

  /* Saturate: '<S46>/Saturation' incorporates:
   *  Sum: '<S48>/Sum'
   */
  y = ControllerForExport_B.Sum[0];
  if (y > ControllerForExport_P.ForcePID_UpperSaturationLimit) {
    /* Saturate: '<S46>/Saturation' */
    y = ControllerForExport_P.ForcePID_UpperSaturationLimit;
  } else if (y < ControllerForExport_P.ForcePID_LowerSaturationLimit) {
    /* Saturate: '<S46>/Saturation' */
    y = ControllerForExport_P.ForcePID_LowerSaturationLimit;
  }

  /* Saturate: '<S46>/Saturation' */
  ControllerForExport_B.Saturation[0] = y;

  /* Gain: '<S96>/Proportional Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ErrorSIgnal = ControllerForExport_U.ErrorSIgnal[3];

  /* Gain: '<S96>/Proportional Gain' */
  Integrator = ControllerForExport_P.kp_T * ErrorSIgnal;
  ControllerForExport_B.ProportionalGain_l[0] = Integrator;

  /* Integrator: '<S91>/Integrator' */
  DerivativeGain = ControllerForExport_X.Integrator_CSTATE_a[0];
  ControllerForExport_B.Integrator_a[0] = DerivativeGain;

  /* Gain: '<S84>/Derivative Gain' */
  ErrorSIgnal *= ControllerForExport_P.kd_T;
  ControllerForExport_B.DerivativeGain_l[0] = ErrorSIgnal;

  /* Integrator: '<S86>/Filter' */
  Filter_b = ControllerForExport_X.Filter_CSTATE_k[0];
  ControllerForExport_B.Filter_b[0] = Filter_b;

  /* Sum: '<S86>/SumD' incorporates:
   *  Gain: '<S84>/Derivative Gain'
   *  Integrator: '<S86>/Filter'
   */
  ErrorSIgnal -= Filter_b;
  ControllerForExport_B.SumD_k[0] = ErrorSIgnal;

  /* Gain: '<S94>/Filter Coefficient' incorporates:
   *  Sum: '<S86>/SumD'
   */
  ErrorSIgnal *= ControllerForExport_P.TorquePID_N;
  ControllerForExport_B.FilterCoefficient_h[0] = ErrorSIgnal;

  /* Sum: '<S100>/Sum' incorporates:
   *  Gain: '<S94>/Filter Coefficient'
   *  Gain: '<S96>/Proportional Gain'
   *  Integrator: '<S91>/Integrator'
   */
  ControllerForExport_B.Sum_h[0] = (Integrator + DerivativeGain) + ErrorSIgnal;

  /* Saturate: '<S98>/Saturation' incorporates:
   *  Sum: '<S100>/Sum'
   */
  Integrator = ControllerForExport_B.Sum_h[0];
  if (Integrator > ControllerForExport_P.TorquePID_UpperSaturationLimit) {
    /* Saturate: '<S98>/Saturation' */
    Integrator = ControllerForExport_P.TorquePID_UpperSaturationLimit;
  } else if (Integrator < ControllerForExport_P.TorquePID_LowerSaturationLimit)
  {
    /* Saturate: '<S98>/Saturation' */
    Integrator = ControllerForExport_P.TorquePID_LowerSaturationLimit;
  }

  /* Saturate: '<S98>/Saturation' */
  ControllerForExport_B.Saturation_e[0] = Integrator;

  /* SignalConversion generated from: '<Root>/Maps forces to pwms' */
  ControllerForExport_B.TmpSignalConversionAtMapsforces[0] = y;
  ControllerForExport_B.TmpSignalConversionAtMapsforces[3] = Integrator;

  /* Gain: '<S44>/Proportional Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ErrorSIgnal = ControllerForExport_U.ErrorSIgnal[1];

  /* Gain: '<S44>/Proportional Gain' */
  y = ControllerForExport_P.kp_F * ErrorSIgnal;
  ControllerForExport_B.ProportionalGain[1] = y;

  /* Integrator: '<S39>/Integrator' */
  Integrator = ControllerForExport_X.Integrator_CSTATE[1];
  ControllerForExport_B.Integrator[1] = Integrator;

  /* Gain: '<S32>/Derivative Gain' */
  DerivativeGain = ControllerForExport_P.kd_F * ErrorSIgnal;
  ControllerForExport_B.DerivativeGain[1] = DerivativeGain;

  /* Integrator: '<S34>/Filter' */
  ErrorSIgnal = ControllerForExport_X.Filter_CSTATE[1];
  ControllerForExport_B.Filter[1] = ErrorSIgnal;

  /* Sum: '<S34>/SumD' incorporates:
   *  Gain: '<S32>/Derivative Gain'
   *  Integrator: '<S34>/Filter'
   */
  DerivativeGain -= ErrorSIgnal;
  ControllerForExport_B.SumD[1] = DerivativeGain;

  /* Gain: '<S42>/Filter Coefficient' incorporates:
   *  Sum: '<S34>/SumD'
   */
  DerivativeGain *= ControllerForExport_P.ForcePID_N;
  ControllerForExport_B.FilterCoefficient[1] = DerivativeGain;

  /* Sum: '<S48>/Sum' incorporates:
   *  Gain: '<S42>/Filter Coefficient'
   *  Gain: '<S44>/Proportional Gain'
   *  Integrator: '<S39>/Integrator'
   */
  ControllerForExport_B.Sum[1] = (y + Integrator) + DerivativeGain;

  /* Saturate: '<S46>/Saturation' incorporates:
   *  Sum: '<S48>/Sum'
   */
  y = ControllerForExport_B.Sum[1];
  if (y > ControllerForExport_P.ForcePID_UpperSaturationLimit) {
    /* Saturate: '<S46>/Saturation' */
    y = ControllerForExport_P.ForcePID_UpperSaturationLimit;
  } else if (y < ControllerForExport_P.ForcePID_LowerSaturationLimit) {
    /* Saturate: '<S46>/Saturation' */
    y = ControllerForExport_P.ForcePID_LowerSaturationLimit;
  }

  /* Saturate: '<S46>/Saturation' */
  ControllerForExport_B.Saturation[1] = y;

  /* Gain: '<S96>/Proportional Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ErrorSIgnal = ControllerForExport_U.ErrorSIgnal[4];

  /* Gain: '<S96>/Proportional Gain' */
  Integrator = ControllerForExport_P.kp_T * ErrorSIgnal;
  ControllerForExport_B.ProportionalGain_l[1] = Integrator;

  /* Integrator: '<S91>/Integrator' */
  DerivativeGain = ControllerForExport_X.Integrator_CSTATE_a[1];
  ControllerForExport_B.Integrator_a[1] = DerivativeGain;

  /* Gain: '<S84>/Derivative Gain' */
  ErrorSIgnal *= ControllerForExport_P.kd_T;
  ControllerForExport_B.DerivativeGain_l[1] = ErrorSIgnal;

  /* Integrator: '<S86>/Filter' */
  Filter_b = ControllerForExport_X.Filter_CSTATE_k[1];
  ControllerForExport_B.Filter_b[1] = Filter_b;

  /* Sum: '<S86>/SumD' incorporates:
   *  Gain: '<S84>/Derivative Gain'
   *  Integrator: '<S86>/Filter'
   */
  ErrorSIgnal -= Filter_b;
  ControllerForExport_B.SumD_k[1] = ErrorSIgnal;

  /* Gain: '<S94>/Filter Coefficient' incorporates:
   *  Sum: '<S86>/SumD'
   */
  ErrorSIgnal *= ControllerForExport_P.TorquePID_N;
  ControllerForExport_B.FilterCoefficient_h[1] = ErrorSIgnal;

  /* Sum: '<S100>/Sum' incorporates:
   *  Gain: '<S94>/Filter Coefficient'
   *  Gain: '<S96>/Proportional Gain'
   *  Integrator: '<S91>/Integrator'
   */
  ControllerForExport_B.Sum_h[1] = (Integrator + DerivativeGain) + ErrorSIgnal;

  /* Saturate: '<S98>/Saturation' incorporates:
   *  Sum: '<S100>/Sum'
   */
  Integrator = ControllerForExport_B.Sum_h[1];
  if (Integrator > ControllerForExport_P.TorquePID_UpperSaturationLimit) {
    /* Saturate: '<S98>/Saturation' */
    Integrator = ControllerForExport_P.TorquePID_UpperSaturationLimit;
  } else if (Integrator < ControllerForExport_P.TorquePID_LowerSaturationLimit)
  {
    /* Saturate: '<S98>/Saturation' */
    Integrator = ControllerForExport_P.TorquePID_LowerSaturationLimit;
  }

  /* Saturate: '<S98>/Saturation' */
  ControllerForExport_B.Saturation_e[1] = Integrator;

  /* SignalConversion generated from: '<Root>/Maps forces to pwms' */
  ControllerForExport_B.TmpSignalConversionAtMapsforces[1] = y;
  ControllerForExport_B.TmpSignalConversionAtMapsforces[4] = Integrator;

  /* Gain: '<S44>/Proportional Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ErrorSIgnal = ControllerForExport_U.ErrorSIgnal[2];

  /* Gain: '<S44>/Proportional Gain' */
  y = ControllerForExport_P.kp_F * ErrorSIgnal;
  ControllerForExport_B.ProportionalGain[2] = y;

  /* Integrator: '<S39>/Integrator' */
  Integrator = ControllerForExport_X.Integrator_CSTATE[2];
  ControllerForExport_B.Integrator[2] = Integrator;

  /* Gain: '<S32>/Derivative Gain' */
  DerivativeGain = ControllerForExport_P.kd_F * ErrorSIgnal;
  ControllerForExport_B.DerivativeGain[2] = DerivativeGain;

  /* Integrator: '<S34>/Filter' */
  ErrorSIgnal = ControllerForExport_X.Filter_CSTATE[2];
  ControllerForExport_B.Filter[2] = ErrorSIgnal;

  /* Sum: '<S34>/SumD' incorporates:
   *  Gain: '<S32>/Derivative Gain'
   *  Integrator: '<S34>/Filter'
   */
  DerivativeGain -= ErrorSIgnal;
  ControllerForExport_B.SumD[2] = DerivativeGain;

  /* Gain: '<S42>/Filter Coefficient' incorporates:
   *  Sum: '<S34>/SumD'
   */
  DerivativeGain *= ControllerForExport_P.ForcePID_N;
  ControllerForExport_B.FilterCoefficient[2] = DerivativeGain;

  /* Sum: '<S48>/Sum' incorporates:
   *  Gain: '<S42>/Filter Coefficient'
   *  Gain: '<S44>/Proportional Gain'
   *  Integrator: '<S39>/Integrator'
   */
  ControllerForExport_B.Sum[2] = (y + Integrator) + DerivativeGain;

  /* Saturate: '<S46>/Saturation' incorporates:
   *  Sum: '<S48>/Sum'
   */
  y = ControllerForExport_B.Sum[2];
  if (y > ControllerForExport_P.ForcePID_UpperSaturationLimit) {
    /* Saturate: '<S46>/Saturation' */
    y = ControllerForExport_P.ForcePID_UpperSaturationLimit;
  } else if (y < ControllerForExport_P.ForcePID_LowerSaturationLimit) {
    /* Saturate: '<S46>/Saturation' */
    y = ControllerForExport_P.ForcePID_LowerSaturationLimit;
  }

  /* Saturate: '<S46>/Saturation' */
  ControllerForExport_B.Saturation[2] = y;

  /* Gain: '<S96>/Proportional Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ErrorSIgnal = ControllerForExport_U.ErrorSIgnal[5];

  /* Gain: '<S96>/Proportional Gain' */
  Integrator = ControllerForExport_P.kp_T * ErrorSIgnal;
  ControllerForExport_B.ProportionalGain_l[2] = Integrator;

  /* Integrator: '<S91>/Integrator' */
  DerivativeGain = ControllerForExport_X.Integrator_CSTATE_a[2];
  ControllerForExport_B.Integrator_a[2] = DerivativeGain;

  /* Gain: '<S84>/Derivative Gain' */
  ErrorSIgnal *= ControllerForExport_P.kd_T;
  ControllerForExport_B.DerivativeGain_l[2] = ErrorSIgnal;

  /* Integrator: '<S86>/Filter' */
  Filter_b = ControllerForExport_X.Filter_CSTATE_k[2];
  ControllerForExport_B.Filter_b[2] = Filter_b;

  /* Sum: '<S86>/SumD' incorporates:
   *  Gain: '<S84>/Derivative Gain'
   *  Integrator: '<S86>/Filter'
   */
  ErrorSIgnal -= Filter_b;
  ControllerForExport_B.SumD_k[2] = ErrorSIgnal;

  /* Gain: '<S94>/Filter Coefficient' incorporates:
   *  Sum: '<S86>/SumD'
   */
  ErrorSIgnal *= ControllerForExport_P.TorquePID_N;
  ControllerForExport_B.FilterCoefficient_h[2] = ErrorSIgnal;

  /* Sum: '<S100>/Sum' incorporates:
   *  Gain: '<S94>/Filter Coefficient'
   *  Gain: '<S96>/Proportional Gain'
   *  Integrator: '<S91>/Integrator'
   */
  ControllerForExport_B.Sum_h[2] = (Integrator + DerivativeGain) + ErrorSIgnal;

  /* Saturate: '<S98>/Saturation' incorporates:
   *  Sum: '<S100>/Sum'
   */
  Integrator = ControllerForExport_B.Sum_h[2];
  if (Integrator > ControllerForExport_P.TorquePID_UpperSaturationLimit) {
    /* Saturate: '<S98>/Saturation' */
    Integrator = ControllerForExport_P.TorquePID_UpperSaturationLimit;
  } else if (Integrator < ControllerForExport_P.TorquePID_LowerSaturationLimit)
  {
    /* Saturate: '<S98>/Saturation' */
    Integrator = ControllerForExport_P.TorquePID_LowerSaturationLimit;
  }

  /* Saturate: '<S98>/Saturation' */
  ControllerForExport_B.Saturation_e[2] = Integrator;

  /* SignalConversion generated from: '<Root>/Maps forces to pwms' */
  ControllerForExport_B.TmpSignalConversionAtMapsforces[2] = y;
  ControllerForExport_B.TmpSignalConversionAtMapsforces[5] = Integrator;

  /* Product: '<Root>/Maps forces to pwms' incorporates:
   *  Constant: '<Root>/Constant'
   *  SignalConversion generated from: '<Root>/Maps forces to pwms'
   */
  tmp_0 = &ControllerForExport_P.inverse_wrench[0];
  for (i = 0; i < 6; i++) {
    tmp[i] = ControllerForExport_B.TmpSignalConversionAtMapsforces[i];
  }

  /* :  pwm_cmd = zeros(8,1); */
  /* :  for i=1:length(pwm_cmd) */
  for (i_0 = 0; i_0 < 8; i_0++) {
    /* Product: '<Root>/Maps forces to pwms' */
    y = 0.0;
    for (i = 0; i < 6; i++) {
      /* Product: '<Root>/Maps forces to pwms' */
      y += tmp_0[(i << 3) + i_0] * tmp[i];
    }

    /* Product: '<Root>/Maps forces to pwms' */
    ControllerForExport_B.Mapsforcestopwms[i_0] = y;

    /* MATLAB Function: '<Root>/Thruster Forces to PWM' incorporates:
     *  Product: '<Root>/Maps forces to pwms'
     */
    /* :  x = thruster_force_cmd(i); */
    /* :  y = 0; */
    /* :  if(x>0) */
    if (y > 0.0) {
      /* :  y = -3e-5*x^4 + 0.0048*x^3 - 0.2987*x^2 + 14.385*x + 1535; */
      y = (((-3.0E-5 * rt_powd_snf(ControllerForExport_B.Mapsforcestopwms[i_0],
              4.0) + 0.0048 * rt_powd_snf
             (ControllerForExport_B.Mapsforcestopwms[i_0], 3.0)) -
            ControllerForExport_B.Mapsforcestopwms[i_0] *
            ControllerForExport_B.Mapsforcestopwms[i_0] * 0.2987) + 14.385 *
           ControllerForExport_B.Mapsforcestopwms[i_0]) + 1535.0;
    } else if (y < 0.0) {
      /* :  elseif(x<0) */
      /* :  y = 6e-5*x^4 + 0.0086*x^3 + 0.4394*x^2 + 17.718*x + 1464.4; */
      y = (((6.0E-5 * rt_powd_snf(ControllerForExport_B.Mapsforcestopwms[i_0],
              4.0) + 0.0086 * rt_powd_snf
             (ControllerForExport_B.Mapsforcestopwms[i_0], 3.0)) +
            ControllerForExport_B.Mapsforcestopwms[i_0] *
            ControllerForExport_B.Mapsforcestopwms[i_0] * 0.4394) + 17.718 *
           ControllerForExport_B.Mapsforcestopwms[i_0]) + 1464.4;
    } else {
      /* :  else */
      /* :  y = 1500; */
      y = 1500.0;
    }

    /* :  if(y > 1900) */
    if (y > 1900.0) {
      /* :  y = 1900; */
      y = 1900.0;
    }

    /* :  if (y < 1100) */
    if (y < 1100.0) {
      /* :  y = 1100; */
      y = 1100.0;
    }

    /* :  pwm_cmd(i) = y; */
    ControllerForExport_B.pwm_cmd[i_0] = y;

    /* End of MATLAB Function: '<Root>/Thruster Forces to PWM' */

    /* Outport: '<Root>/PWM' */
    ControllerForExport_Y.PWM[i_0] = y;
  }

  /* Gain: '<S29>/ZeroGain' incorporates:
   *  Sum: '<S48>/Sum'
   */
  Integrator = ControllerForExport_B.Sum[0];

  /* Gain: '<S29>/ZeroGain' incorporates:
   *  Sum: '<S48>/Sum'
   */
  y = ControllerForExport_P.ZeroGain_Gain * Integrator;
  ControllerForExport_B.ZeroGain[0] = y;

  /* DeadZone: '<S31>/DeadZone' incorporates:
   *  Sum: '<S48>/Sum'
   */
  if (Integrator > ControllerForExport_P.ForcePID_UpperSaturationLimit) {
    Integrator -= ControllerForExport_P.ForcePID_UpperSaturationLimit;
  } else if (Integrator >= ControllerForExport_P.ForcePID_LowerSaturationLimit)
  {
    Integrator = 0.0;
  } else {
    Integrator -= ControllerForExport_P.ForcePID_LowerSaturationLimit;
  }

  /* DeadZone: '<S31>/DeadZone' */
  ControllerForExport_B.DeadZone[0] = Integrator;

  /* RelationalOperator: '<S29>/NotEqual' incorporates:
   *  DeadZone: '<S31>/DeadZone'
   *  Gain: '<S29>/ZeroGain'
   */
  NotEqual = (y != Integrator);
  ControllerForExport_B.NotEqual[0] = NotEqual;

  /* Signum: '<S29>/SignPreSat' incorporates:
   *  DeadZone: '<S31>/DeadZone'
   */
  y = ControllerForExport_B.DeadZone[0];
  if (std::isnan(y)) {
    /* Signum: '<S29>/SignPreSat' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S29>/SignPreSat' */
    y = -1.0;
  } else {
    /* Signum: '<S29>/SignPreSat' */
    y = (y > 0.0);
  }

  /* Signum: '<S29>/SignPreSat' */
  ControllerForExport_B.SignPreSat[0] = y;

  /* DataTypeConversion: '<S29>/DataTypeConv1' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S29>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S29>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S29>/DataTypeConv1' */
  ControllerForExport_B.DataTypeConv1[0] = DataTypeConv1;

  /* Gain: '<S36>/Integral Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ControllerForExport_B.IntegralGain[0] = ControllerForExport_P.ki_F *
    ControllerForExport_U.ErrorSIgnal[0];

  /* Signum: '<S29>/SignPreIntegrator' incorporates:
   *  Gain: '<S36>/Integral Gain'
   */
  y = ControllerForExport_B.IntegralGain[0];
  if (std::isnan(y)) {
    /* Signum: '<S29>/SignPreIntegrator' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S29>/SignPreIntegrator' */
    y = -1.0;
  } else {
    /* Signum: '<S29>/SignPreIntegrator' */
    y = (y > 0.0);
  }

  /* Signum: '<S29>/SignPreIntegrator' */
  ControllerForExport_B.SignPreIntegrator[0] = y;

  /* DataTypeConversion: '<S29>/DataTypeConv2' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S29>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S29>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S29>/DataTypeConv2' */
  ControllerForExport_B.DataTypeConv2[0] = DataTypeConv2;

  /* RelationalOperator: '<S29>/Equal1' incorporates:
   *  DataTypeConversion: '<S29>/DataTypeConv1'
   *  DataTypeConversion: '<S29>/DataTypeConv2'
   */
  Equal1 = (DataTypeConv1 == DataTypeConv2);
  ControllerForExport_B.Equal1[0] = Equal1;

  /* Logic: '<S29>/AND3' incorporates:
   *  RelationalOperator: '<S29>/Equal1'
   *  RelationalOperator: '<S29>/NotEqual'
   */
  ControllerForExport_B.AND3[0] = (NotEqual && Equal1);

  /* Gain: '<S29>/ZeroGain' incorporates:
   *  Sum: '<S48>/Sum'
   */
  Integrator = ControllerForExport_B.Sum[1];

  /* Gain: '<S29>/ZeroGain' incorporates:
   *  Sum: '<S48>/Sum'
   */
  y = ControllerForExport_P.ZeroGain_Gain * Integrator;
  ControllerForExport_B.ZeroGain[1] = y;

  /* DeadZone: '<S31>/DeadZone' incorporates:
   *  Sum: '<S48>/Sum'
   */
  if (Integrator > ControllerForExport_P.ForcePID_UpperSaturationLimit) {
    Integrator -= ControllerForExport_P.ForcePID_UpperSaturationLimit;
  } else if (Integrator >= ControllerForExport_P.ForcePID_LowerSaturationLimit)
  {
    Integrator = 0.0;
  } else {
    Integrator -= ControllerForExport_P.ForcePID_LowerSaturationLimit;
  }

  /* DeadZone: '<S31>/DeadZone' */
  ControllerForExport_B.DeadZone[1] = Integrator;

  /* RelationalOperator: '<S29>/NotEqual' incorporates:
   *  DeadZone: '<S31>/DeadZone'
   *  Gain: '<S29>/ZeroGain'
   */
  NotEqual = (y != Integrator);
  ControllerForExport_B.NotEqual[1] = NotEqual;

  /* Signum: '<S29>/SignPreSat' incorporates:
   *  DeadZone: '<S31>/DeadZone'
   */
  y = ControllerForExport_B.DeadZone[1];
  if (std::isnan(y)) {
    /* Signum: '<S29>/SignPreSat' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S29>/SignPreSat' */
    y = -1.0;
  } else {
    /* Signum: '<S29>/SignPreSat' */
    y = (y > 0.0);
  }

  /* Signum: '<S29>/SignPreSat' */
  ControllerForExport_B.SignPreSat[1] = y;

  /* DataTypeConversion: '<S29>/DataTypeConv1' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S29>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S29>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S29>/DataTypeConv1' */
  ControllerForExport_B.DataTypeConv1[1] = DataTypeConv1;

  /* Gain: '<S36>/Integral Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ControllerForExport_B.IntegralGain[1] = ControllerForExport_P.ki_F *
    ControllerForExport_U.ErrorSIgnal[1];

  /* Signum: '<S29>/SignPreIntegrator' incorporates:
   *  Gain: '<S36>/Integral Gain'
   */
  y = ControllerForExport_B.IntegralGain[1];
  if (std::isnan(y)) {
    /* Signum: '<S29>/SignPreIntegrator' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S29>/SignPreIntegrator' */
    y = -1.0;
  } else {
    /* Signum: '<S29>/SignPreIntegrator' */
    y = (y > 0.0);
  }

  /* Signum: '<S29>/SignPreIntegrator' */
  ControllerForExport_B.SignPreIntegrator[1] = y;

  /* DataTypeConversion: '<S29>/DataTypeConv2' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S29>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S29>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S29>/DataTypeConv2' */
  ControllerForExport_B.DataTypeConv2[1] = DataTypeConv2;

  /* RelationalOperator: '<S29>/Equal1' incorporates:
   *  DataTypeConversion: '<S29>/DataTypeConv1'
   *  DataTypeConversion: '<S29>/DataTypeConv2'
   */
  Equal1 = (DataTypeConv1 == DataTypeConv2);
  ControllerForExport_B.Equal1[1] = Equal1;

  /* Logic: '<S29>/AND3' incorporates:
   *  RelationalOperator: '<S29>/Equal1'
   *  RelationalOperator: '<S29>/NotEqual'
   */
  ControllerForExport_B.AND3[1] = (NotEqual && Equal1);

  /* Gain: '<S29>/ZeroGain' incorporates:
   *  Sum: '<S48>/Sum'
   */
  Integrator = ControllerForExport_B.Sum[2];

  /* Gain: '<S29>/ZeroGain' incorporates:
   *  Sum: '<S48>/Sum'
   */
  y = ControllerForExport_P.ZeroGain_Gain * Integrator;
  ControllerForExport_B.ZeroGain[2] = y;

  /* DeadZone: '<S31>/DeadZone' incorporates:
   *  Sum: '<S48>/Sum'
   */
  if (Integrator > ControllerForExport_P.ForcePID_UpperSaturationLimit) {
    Integrator -= ControllerForExport_P.ForcePID_UpperSaturationLimit;
  } else if (Integrator >= ControllerForExport_P.ForcePID_LowerSaturationLimit)
  {
    Integrator = 0.0;
  } else {
    Integrator -= ControllerForExport_P.ForcePID_LowerSaturationLimit;
  }

  /* DeadZone: '<S31>/DeadZone' */
  ControllerForExport_B.DeadZone[2] = Integrator;

  /* RelationalOperator: '<S29>/NotEqual' incorporates:
   *  DeadZone: '<S31>/DeadZone'
   *  Gain: '<S29>/ZeroGain'
   */
  NotEqual = (y != Integrator);
  ControllerForExport_B.NotEqual[2] = NotEqual;

  /* Signum: '<S29>/SignPreSat' incorporates:
   *  DeadZone: '<S31>/DeadZone'
   */
  y = ControllerForExport_B.DeadZone[2];
  if (std::isnan(y)) {
    /* Signum: '<S29>/SignPreSat' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S29>/SignPreSat' */
    y = -1.0;
  } else {
    /* Signum: '<S29>/SignPreSat' */
    y = (y > 0.0);
  }

  /* Signum: '<S29>/SignPreSat' */
  ControllerForExport_B.SignPreSat[2] = y;

  /* DataTypeConversion: '<S29>/DataTypeConv1' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S29>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S29>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S29>/DataTypeConv1' */
  ControllerForExport_B.DataTypeConv1[2] = DataTypeConv1;

  /* Gain: '<S36>/Integral Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ControllerForExport_B.IntegralGain[2] = ControllerForExport_P.ki_F *
    ControllerForExport_U.ErrorSIgnal[2];

  /* Signum: '<S29>/SignPreIntegrator' incorporates:
   *  Gain: '<S36>/Integral Gain'
   */
  y = ControllerForExport_B.IntegralGain[2];
  if (std::isnan(y)) {
    /* Signum: '<S29>/SignPreIntegrator' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S29>/SignPreIntegrator' */
    y = -1.0;
  } else {
    /* Signum: '<S29>/SignPreIntegrator' */
    y = (y > 0.0);
  }

  /* Signum: '<S29>/SignPreIntegrator' */
  ControllerForExport_B.SignPreIntegrator[2] = y;

  /* DataTypeConversion: '<S29>/DataTypeConv2' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S29>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S29>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S29>/DataTypeConv2' */
  ControllerForExport_B.DataTypeConv2[2] = DataTypeConv2;

  /* RelationalOperator: '<S29>/Equal1' incorporates:
   *  DataTypeConversion: '<S29>/DataTypeConv1'
   *  DataTypeConversion: '<S29>/DataTypeConv2'
   */
  Equal1 = (DataTypeConv1 == DataTypeConv2);
  ControllerForExport_B.Equal1[2] = Equal1;

  /* Logic: '<S29>/AND3' incorporates:
   *  RelationalOperator: '<S29>/Equal1'
   *  RelationalOperator: '<S29>/NotEqual'
   */
  ControllerForExport_B.AND3[2] = (NotEqual && Equal1);
  if (rtmIsMajorTimeStep((&ControllerForExport_M))) {
    /* Memory: '<S29>/Memory' */
    ControllerForExport_B.Memory[0] =
      ControllerForExport_DW.Memory_PreviousInput[0];
    ControllerForExport_B.Memory[1] =
      ControllerForExport_DW.Memory_PreviousInput[1];
    ControllerForExport_B.Memory[2] =
      ControllerForExport_DW.Memory_PreviousInput[2];
  }

  /* Switch: '<S29>/Switch' incorporates:
   *  Constant: '<S29>/Constant1'
   *  Gain: '<S36>/Integral Gain'
   *  Memory: '<S29>/Memory'
   */
  if (ControllerForExport_B.Memory[0]) {
    ControllerForExport_B.Switch[0] = ControllerForExport_P.Constant1_Value;
  } else {
    ControllerForExport_B.Switch[0] = ControllerForExport_B.IntegralGain[0];
  }

  /* Gain: '<S81>/ZeroGain' incorporates:
   *  Sum: '<S100>/Sum'
   */
  Integrator = ControllerForExport_B.Sum_h[0];

  /* Gain: '<S81>/ZeroGain' incorporates:
   *  Sum: '<S100>/Sum'
   */
  y = ControllerForExport_P.ZeroGain_Gain_m * Integrator;
  ControllerForExport_B.ZeroGain_a[0] = y;

  /* DeadZone: '<S83>/DeadZone' incorporates:
   *  Sum: '<S100>/Sum'
   */
  if (Integrator > ControllerForExport_P.TorquePID_UpperSaturationLimit) {
    Integrator -= ControllerForExport_P.TorquePID_UpperSaturationLimit;
  } else if (Integrator >= ControllerForExport_P.TorquePID_LowerSaturationLimit)
  {
    Integrator = 0.0;
  } else {
    Integrator -= ControllerForExport_P.TorquePID_LowerSaturationLimit;
  }

  /* DeadZone: '<S83>/DeadZone' */
  ControllerForExport_B.DeadZone_o[0] = Integrator;

  /* RelationalOperator: '<S81>/NotEqual' incorporates:
   *  DeadZone: '<S83>/DeadZone'
   *  Gain: '<S81>/ZeroGain'
   */
  NotEqual = (y != Integrator);
  ControllerForExport_B.NotEqual_o[0] = NotEqual;

  /* Signum: '<S81>/SignPreSat' incorporates:
   *  DeadZone: '<S83>/DeadZone'
   */
  y = ControllerForExport_B.DeadZone_o[0];
  if (std::isnan(y)) {
    /* Signum: '<S81>/SignPreSat' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S81>/SignPreSat' */
    y = -1.0;
  } else {
    /* Signum: '<S81>/SignPreSat' */
    y = (y > 0.0);
  }

  /* Signum: '<S81>/SignPreSat' */
  ControllerForExport_B.SignPreSat_m[0] = y;

  /* DataTypeConversion: '<S81>/DataTypeConv1' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S81>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S81>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S81>/DataTypeConv1' */
  ControllerForExport_B.DataTypeConv1_f[0] = DataTypeConv1;

  /* Gain: '<S88>/Integral Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ControllerForExport_B.IntegralGain_g[0] = ControllerForExport_P.ki_T
    * ControllerForExport_U.ErrorSIgnal[3];

  /* Signum: '<S81>/SignPreIntegrator' incorporates:
   *  Gain: '<S88>/Integral Gain'
   */
  y = ControllerForExport_B.IntegralGain_g[0];
  if (std::isnan(y)) {
    /* Signum: '<S81>/SignPreIntegrator' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S81>/SignPreIntegrator' */
    y = -1.0;
  } else {
    /* Signum: '<S81>/SignPreIntegrator' */
    y = (y > 0.0);
  }

  /* Signum: '<S81>/SignPreIntegrator' */
  ControllerForExport_B.SignPreIntegrator_a[0] = y;

  /* DataTypeConversion: '<S81>/DataTypeConv2' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S81>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S81>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S81>/DataTypeConv2' */
  ControllerForExport_B.DataTypeConv2_j[0] = DataTypeConv2;

  /* RelationalOperator: '<S81>/Equal1' incorporates:
   *  DataTypeConversion: '<S81>/DataTypeConv1'
   *  DataTypeConversion: '<S81>/DataTypeConv2'
   */
  Equal1 = (DataTypeConv1 == DataTypeConv2);
  ControllerForExport_B.Equal1_n[0] = Equal1;

  /* Logic: '<S81>/AND3' incorporates:
   *  RelationalOperator: '<S81>/Equal1'
   *  RelationalOperator: '<S81>/NotEqual'
   */
  ControllerForExport_B.AND3_a[0] = (NotEqual && Equal1);

  /* Switch: '<S29>/Switch' incorporates:
   *  Constant: '<S29>/Constant1'
   *  Gain: '<S36>/Integral Gain'
   *  Memory: '<S29>/Memory'
   */
  if (ControllerForExport_B.Memory[1]) {
    ControllerForExport_B.Switch[1] = ControllerForExport_P.Constant1_Value;
  } else {
    ControllerForExport_B.Switch[1] = ControllerForExport_B.IntegralGain[1];
  }

  /* Gain: '<S81>/ZeroGain' incorporates:
   *  Sum: '<S100>/Sum'
   */
  Integrator = ControllerForExport_B.Sum_h[1];

  /* Gain: '<S81>/ZeroGain' incorporates:
   *  Sum: '<S100>/Sum'
   */
  y = ControllerForExport_P.ZeroGain_Gain_m * Integrator;
  ControllerForExport_B.ZeroGain_a[1] = y;

  /* DeadZone: '<S83>/DeadZone' incorporates:
   *  Sum: '<S100>/Sum'
   */
  if (Integrator > ControllerForExport_P.TorquePID_UpperSaturationLimit) {
    Integrator -= ControllerForExport_P.TorquePID_UpperSaturationLimit;
  } else if (Integrator >= ControllerForExport_P.TorquePID_LowerSaturationLimit)
  {
    Integrator = 0.0;
  } else {
    Integrator -= ControllerForExport_P.TorquePID_LowerSaturationLimit;
  }

  /* DeadZone: '<S83>/DeadZone' */
  ControllerForExport_B.DeadZone_o[1] = Integrator;

  /* RelationalOperator: '<S81>/NotEqual' incorporates:
   *  DeadZone: '<S83>/DeadZone'
   *  Gain: '<S81>/ZeroGain'
   */
  NotEqual = (y != Integrator);
  ControllerForExport_B.NotEqual_o[1] = NotEqual;

  /* Signum: '<S81>/SignPreSat' incorporates:
   *  DeadZone: '<S83>/DeadZone'
   */
  y = ControllerForExport_B.DeadZone_o[1];
  if (std::isnan(y)) {
    /* Signum: '<S81>/SignPreSat' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S81>/SignPreSat' */
    y = -1.0;
  } else {
    /* Signum: '<S81>/SignPreSat' */
    y = (y > 0.0);
  }

  /* Signum: '<S81>/SignPreSat' */
  ControllerForExport_B.SignPreSat_m[1] = y;

  /* DataTypeConversion: '<S81>/DataTypeConv1' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S81>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S81>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S81>/DataTypeConv1' */
  ControllerForExport_B.DataTypeConv1_f[1] = DataTypeConv1;

  /* Gain: '<S88>/Integral Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ControllerForExport_B.IntegralGain_g[1] = ControllerForExport_P.ki_T
    * ControllerForExport_U.ErrorSIgnal[4];

  /* Signum: '<S81>/SignPreIntegrator' incorporates:
   *  Gain: '<S88>/Integral Gain'
   */
  y = ControllerForExport_B.IntegralGain_g[1];
  if (std::isnan(y)) {
    /* Signum: '<S81>/SignPreIntegrator' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S81>/SignPreIntegrator' */
    y = -1.0;
  } else {
    /* Signum: '<S81>/SignPreIntegrator' */
    y = (y > 0.0);
  }

  /* Signum: '<S81>/SignPreIntegrator' */
  ControllerForExport_B.SignPreIntegrator_a[1] = y;

  /* DataTypeConversion: '<S81>/DataTypeConv2' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S81>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S81>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S81>/DataTypeConv2' */
  ControllerForExport_B.DataTypeConv2_j[1] = DataTypeConv2;

  /* RelationalOperator: '<S81>/Equal1' incorporates:
   *  DataTypeConversion: '<S81>/DataTypeConv1'
   *  DataTypeConversion: '<S81>/DataTypeConv2'
   */
  Equal1 = (DataTypeConv1 == DataTypeConv2);
  ControllerForExport_B.Equal1_n[1] = Equal1;

  /* Logic: '<S81>/AND3' incorporates:
   *  RelationalOperator: '<S81>/Equal1'
   *  RelationalOperator: '<S81>/NotEqual'
   */
  ControllerForExport_B.AND3_a[1] = (NotEqual && Equal1);

  /* Switch: '<S29>/Switch' incorporates:
   *  Constant: '<S29>/Constant1'
   *  Gain: '<S36>/Integral Gain'
   *  Memory: '<S29>/Memory'
   */
  if (ControllerForExport_B.Memory[2]) {
    ControllerForExport_B.Switch[2] = ControllerForExport_P.Constant1_Value;
  } else {
    ControllerForExport_B.Switch[2] = ControllerForExport_B.IntegralGain[2];
  }

  /* Gain: '<S81>/ZeroGain' incorporates:
   *  Sum: '<S100>/Sum'
   */
  Integrator = ControllerForExport_B.Sum_h[2];

  /* Gain: '<S81>/ZeroGain' incorporates:
   *  Sum: '<S100>/Sum'
   */
  y = ControllerForExport_P.ZeroGain_Gain_m * Integrator;
  ControllerForExport_B.ZeroGain_a[2] = y;

  /* DeadZone: '<S83>/DeadZone' incorporates:
   *  Sum: '<S100>/Sum'
   */
  if (Integrator > ControllerForExport_P.TorquePID_UpperSaturationLimit) {
    Integrator -= ControllerForExport_P.TorquePID_UpperSaturationLimit;
  } else if (Integrator >= ControllerForExport_P.TorquePID_LowerSaturationLimit)
  {
    Integrator = 0.0;
  } else {
    Integrator -= ControllerForExport_P.TorquePID_LowerSaturationLimit;
  }

  /* DeadZone: '<S83>/DeadZone' */
  ControllerForExport_B.DeadZone_o[2] = Integrator;

  /* RelationalOperator: '<S81>/NotEqual' incorporates:
   *  DeadZone: '<S83>/DeadZone'
   *  Gain: '<S81>/ZeroGain'
   */
  NotEqual = (y != Integrator);
  ControllerForExport_B.NotEqual_o[2] = NotEqual;

  /* Signum: '<S81>/SignPreSat' incorporates:
   *  DeadZone: '<S83>/DeadZone'
   */
  y = ControllerForExport_B.DeadZone_o[2];
  if (std::isnan(y)) {
    /* Signum: '<S81>/SignPreSat' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S81>/SignPreSat' */
    y = -1.0;
  } else {
    /* Signum: '<S81>/SignPreSat' */
    y = (y > 0.0);
  }

  /* Signum: '<S81>/SignPreSat' */
  ControllerForExport_B.SignPreSat_m[2] = y;

  /* DataTypeConversion: '<S81>/DataTypeConv1' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S81>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S81>/DataTypeConv1' */
    DataTypeConv1 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S81>/DataTypeConv1' */
  ControllerForExport_B.DataTypeConv1_f[2] = DataTypeConv1;

  /* Gain: '<S88>/Integral Gain' incorporates:
   *  Inport: '<Root>/Error SIgnal'
   */
  ControllerForExport_B.IntegralGain_g[2] = ControllerForExport_P.ki_T
    * ControllerForExport_U.ErrorSIgnal[5];

  /* Signum: '<S81>/SignPreIntegrator' incorporates:
   *  Gain: '<S88>/Integral Gain'
   */
  y = ControllerForExport_B.IntegralGain_g[2];
  if (std::isnan(y)) {
    /* Signum: '<S81>/SignPreIntegrator' */
    y = (rtNaN);
  } else if (y < 0.0) {
    /* Signum: '<S81>/SignPreIntegrator' */
    y = -1.0;
  } else {
    /* Signum: '<S81>/SignPreIntegrator' */
    y = (y > 0.0);
  }

  /* Signum: '<S81>/SignPreIntegrator' */
  ControllerForExport_B.SignPreIntegrator_a[2] = y;

  /* DataTypeConversion: '<S81>/DataTypeConv2' */
  if (std::isnan(y)) {
    i = 0;
  } else {
    i = static_cast<int32_T>(std::fmod(y, 256.0));
  }

  if (i < 0) {
    /* DataTypeConversion: '<S81>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>
      (-static_cast<real_T>(i))));
  } else {
    /* DataTypeConversion: '<S81>/DataTypeConv2' */
    DataTypeConv2 = static_cast<int8_T>(i);
  }

  /* DataTypeConversion: '<S81>/DataTypeConv2' */
  ControllerForExport_B.DataTypeConv2_j[2] = DataTypeConv2;

  /* RelationalOperator: '<S81>/Equal1' incorporates:
   *  DataTypeConversion: '<S81>/DataTypeConv1'
   *  DataTypeConversion: '<S81>/DataTypeConv2'
   */
  Equal1 = (DataTypeConv1 == DataTypeConv2);
  ControllerForExport_B.Equal1_n[2] = Equal1;

  /* Logic: '<S81>/AND3' incorporates:
   *  RelationalOperator: '<S81>/Equal1'
   *  RelationalOperator: '<S81>/NotEqual'
   */
  ControllerForExport_B.AND3_a[2] = (NotEqual && Equal1);
  if (rtmIsMajorTimeStep((&ControllerForExport_M))) {
    /* Memory: '<S81>/Memory' */
    ControllerForExport_B.Memory_k[0] =
      ControllerForExport_DW.Memory_PreviousInput_f[0];
    ControllerForExport_B.Memory_k[1] =
      ControllerForExport_DW.Memory_PreviousInput_f[1];
    ControllerForExport_B.Memory_k[2] =
      ControllerForExport_DW.Memory_PreviousInput_f[2];
  }

  /* Switch: '<S81>/Switch' incorporates:
   *  Constant: '<S81>/Constant1'
   *  Gain: '<S88>/Integral Gain'
   *  Memory: '<S81>/Memory'
   */
  if (ControllerForExport_B.Memory_k[0]) {
    ControllerForExport_B.Switch_e[0] = ControllerForExport_P.Constant1_Value_m;
  } else {
    ControllerForExport_B.Switch_e[0] = ControllerForExport_B.IntegralGain_g[0];
  }

  if (ControllerForExport_B.Memory_k[1]) {
    ControllerForExport_B.Switch_e[1] = ControllerForExport_P.Constant1_Value_m;
  } else {
    ControllerForExport_B.Switch_e[1] = ControllerForExport_B.IntegralGain_g[1];
  }

  if (ControllerForExport_B.Memory_k[2]) {
    ControllerForExport_B.Switch_e[2] = ControllerForExport_P.Constant1_Value_m;
  } else {
    ControllerForExport_B.Switch_e[2] = ControllerForExport_B.IntegralGain_g[2];
  }

  /* End of Switch: '<S81>/Switch' */
  if (rtmIsMajorTimeStep((&ControllerForExport_M))) {
    /* Matfile logging */
    rt_UpdateTXYLogVars((&ControllerForExport_M)->rtwLogInfo,
                        ((&ControllerForExport_M)->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&ControllerForExport_M))) {
    if (rtmIsMajorTimeStep((&ControllerForExport_M))) {
      /* Update for Memory: '<S29>/Memory' incorporates:
       *  Logic: '<S29>/AND3'
       */
      ControllerForExport_DW.Memory_PreviousInput[0] =
        ControllerForExport_B.AND3[0];

      /* Update for Memory: '<S81>/Memory' incorporates:
       *  Logic: '<S81>/AND3'
       */
      ControllerForExport_DW.Memory_PreviousInput_f[0] =
        ControllerForExport_B.AND3_a[0];

      /* Update for Memory: '<S29>/Memory' incorporates:
       *  Logic: '<S29>/AND3'
       */
      ControllerForExport_DW.Memory_PreviousInput[1] =
        ControllerForExport_B.AND3[1];

      /* Update for Memory: '<S81>/Memory' incorporates:
       *  Logic: '<S81>/AND3'
       */
      ControllerForExport_DW.Memory_PreviousInput_f[1] =
        ControllerForExport_B.AND3_a[1];

      /* Update for Memory: '<S29>/Memory' incorporates:
       *  Logic: '<S29>/AND3'
       */
      ControllerForExport_DW.Memory_PreviousInput[2] =
        ControllerForExport_B.AND3[2];

      /* Update for Memory: '<S81>/Memory' incorporates:
       *  Logic: '<S81>/AND3'
       */
      ControllerForExport_DW.Memory_PreviousInput_f[2] =
        ControllerForExport_B.AND3_a[2];
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&ControllerForExport_M))) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal((&ControllerForExport_M))!=-1) &&
          !((rtmGetTFinal((&ControllerForExport_M))-((((&ControllerForExport_M
               )->Timing.clockTick1+(&ControllerForExport_M)->Timing.clockTickH1*
               4294967296.0)) * 0.2)) > ((((&ControllerForExport_M)
              ->Timing.clockTick1+(&ControllerForExport_M)->Timing.clockTickH1*
              4294967296.0)) * 0.2) * (DBL_EPSILON))) {
        rtmSetErrorStatus((&ControllerForExport_M), "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&(&ControllerForExport_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&ControllerForExport_M)->Timing.clockTick0)) {
      ++(&ControllerForExport_M)->Timing.clockTickH0;
    }

    (&ControllerForExport_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&ControllerForExport_M)->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&ControllerForExport_M)->Timing.clockTick1++;
      if (!(&ControllerForExport_M)->Timing.clockTick1) {
        (&ControllerForExport_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void ControllerForExport::ControllerForExport_derivatives()
{
  XDot_ControllerForExport_T *_rtXdot;
  _rtXdot = ((XDot_ControllerForExport_T *) (&ControllerForExport_M)->derivs);

  /* Derivatives for Integrator: '<S39>/Integrator' incorporates:
   *  Switch: '<S29>/Switch'
   */
  _rtXdot->Integrator_CSTATE[0] = ControllerForExport_B.Switch[0];

  /* Derivatives for Integrator: '<S34>/Filter' incorporates:
   *  Gain: '<S42>/Filter Coefficient'
   */
  _rtXdot->Filter_CSTATE[0] = ControllerForExport_B.FilterCoefficient[0];

  /* Derivatives for Integrator: '<S91>/Integrator' incorporates:
   *  Switch: '<S81>/Switch'
   */
  _rtXdot->Integrator_CSTATE_a[0] = ControllerForExport_B.Switch_e[0];

  /* Derivatives for Integrator: '<S86>/Filter' incorporates:
   *  Gain: '<S94>/Filter Coefficient'
   */
  _rtXdot->Filter_CSTATE_k[0] = ControllerForExport_B.FilterCoefficient_h[0];

  /* Derivatives for Integrator: '<S39>/Integrator' incorporates:
   *  Switch: '<S29>/Switch'
   */
  _rtXdot->Integrator_CSTATE[1] = ControllerForExport_B.Switch[1];

  /* Derivatives for Integrator: '<S34>/Filter' incorporates:
   *  Gain: '<S42>/Filter Coefficient'
   */
  _rtXdot->Filter_CSTATE[1] = ControllerForExport_B.FilterCoefficient[1];

  /* Derivatives for Integrator: '<S91>/Integrator' incorporates:
   *  Switch: '<S81>/Switch'
   */
  _rtXdot->Integrator_CSTATE_a[1] = ControllerForExport_B.Switch_e[1];

  /* Derivatives for Integrator: '<S86>/Filter' incorporates:
   *  Gain: '<S94>/Filter Coefficient'
   */
  _rtXdot->Filter_CSTATE_k[1] = ControllerForExport_B.FilterCoefficient_h[1];

  /* Derivatives for Integrator: '<S39>/Integrator' incorporates:
   *  Switch: '<S29>/Switch'
   */
  _rtXdot->Integrator_CSTATE[2] = ControllerForExport_B.Switch[2];

  /* Derivatives for Integrator: '<S34>/Filter' incorporates:
   *  Gain: '<S42>/Filter Coefficient'
   */
  _rtXdot->Filter_CSTATE[2] = ControllerForExport_B.FilterCoefficient[2];

  /* Derivatives for Integrator: '<S91>/Integrator' incorporates:
   *  Switch: '<S81>/Switch'
   */
  _rtXdot->Integrator_CSTATE_a[2] = ControllerForExport_B.Switch_e[2];

  /* Derivatives for Integrator: '<S86>/Filter' incorporates:
   *  Gain: '<S94>/Filter Coefficient'
   */
  _rtXdot->Filter_CSTATE_k[2] = ControllerForExport_B.FilterCoefficient_h[2];
}

/* Model initialize function */
void ControllerForExport::initialize()
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&ControllerForExport_M)->solverInfo,
                          &(&ControllerForExport_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&ControllerForExport_M)->solverInfo, &rtmGetTPtr
                ((&ControllerForExport_M)));
    rtsiSetStepSizePtr(&(&ControllerForExport_M)->solverInfo,
                       &(&ControllerForExport_M)->Timing.stepSize0);
    rtsiSetdXPtr(&(&ControllerForExport_M)->solverInfo, &(&ControllerForExport_M)
                 ->derivs);
    rtsiSetContStatesPtr(&(&ControllerForExport_M)->solverInfo, (real_T **)
                         &(&ControllerForExport_M)->contStates);
    rtsiSetNumContStatesPtr(&(&ControllerForExport_M)->solverInfo,
      &(&ControllerForExport_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&ControllerForExport_M)->solverInfo,
      &(&ControllerForExport_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&ControllerForExport_M)->solverInfo, &(
      &ControllerForExport_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&ControllerForExport_M)->solverInfo,
      &(&ControllerForExport_M)->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&(&ControllerForExport_M)->solverInfo,
      (boolean_T**) &(&ControllerForExport_M)->contStateDisabled);
    rtsiSetErrorStatusPtr(&(&ControllerForExport_M)->solverInfo,
                          (&rtmGetErrorStatus((&ControllerForExport_M))));
    rtsiSetRTModelPtr(&(&ControllerForExport_M)->solverInfo,
                      (&ControllerForExport_M));
  }

  rtsiSetSimTimeStep(&(&ControllerForExport_M)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&ControllerForExport_M)->solverInfo,
    false);
  rtsiSetIsContModeFrozen(&(&ControllerForExport_M)->solverInfo, false);
  (&ControllerForExport_M)->intgData.y = (&ControllerForExport_M)->odeY;
  (&ControllerForExport_M)->intgData.f[0] = (&ControllerForExport_M)->odeF[0];
  (&ControllerForExport_M)->intgData.f[1] = (&ControllerForExport_M)->odeF[1];
  (&ControllerForExport_M)->intgData.f[2] = (&ControllerForExport_M)->odeF[2];
  (&ControllerForExport_M)->contStates = ((X_ControllerForExport_T *)
    &ControllerForExport_X);
  (&ControllerForExport_M)->contStateDisabled = ((XDis_ControllerForExport_T *)
    &ControllerForExport_XDis);
  (&ControllerForExport_M)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&ControllerForExport_M)->solverInfo, static_cast<void *>
                    (&(&ControllerForExport_M)->intgData));
  rtsiSetSolverName(&(&ControllerForExport_M)->solverInfo,"ode3");
  rtmSetTPtr((&ControllerForExport_M), &(&ControllerForExport_M)->Timing.tArray
             [0]);
  rtmSetTFinal((&ControllerForExport_M), 10.0);
  (&ControllerForExport_M)->Timing.stepSize0 = 0.2;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (nullptr);
    (&ControllerForExport_M)->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo((&ControllerForExport_M)->rtwLogInfo, (nullptr));
    rtliSetLogXSignalPtrs((&ControllerForExport_M)->rtwLogInfo, (nullptr));
    rtliSetLogT((&ControllerForExport_M)->rtwLogInfo, "tout");
    rtliSetLogX((&ControllerForExport_M)->rtwLogInfo, "");
    rtliSetLogXFinal((&ControllerForExport_M)->rtwLogInfo, "");
    rtliSetLogVarNameModifier((&ControllerForExport_M)->rtwLogInfo, "rt_");
    rtliSetLogFormat((&ControllerForExport_M)->rtwLogInfo, 4);
    rtliSetLogMaxRows((&ControllerForExport_M)->rtwLogInfo, 0);
    rtliSetLogDecimation((&ControllerForExport_M)->rtwLogInfo, 1);
    rtliSetLogY((&ControllerForExport_M)->rtwLogInfo, "");
    rtliSetLogYSignalInfo((&ControllerForExport_M)->rtwLogInfo, (nullptr));
    rtliSetLogYSignalPtrs((&ControllerForExport_M)->rtwLogInfo, (nullptr));
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime((&ControllerForExport_M)->rtwLogInfo, 0.0,
    rtmGetTFinal((&ControllerForExport_M)), (&ControllerForExport_M)
    ->Timing.stepSize0, (&rtmGetErrorStatus((&ControllerForExport_M))));

  /* InitializeConditions for Integrator: '<S39>/Integrator' */
  ControllerForExport_X.Integrator_CSTATE[0] =
    ControllerForExport_P.ForcePID_InitialConditionForInt;

  /* InitializeConditions for Integrator: '<S34>/Filter' */
  ControllerForExport_X.Filter_CSTATE[0] =
    ControllerForExport_P.ForcePID_InitialConditionForFil;

  /* InitializeConditions for Integrator: '<S91>/Integrator' */
  ControllerForExport_X.Integrator_CSTATE_a[0] =
    ControllerForExport_P.TorquePID_InitialConditionForIn;

  /* InitializeConditions for Integrator: '<S86>/Filter' */
  ControllerForExport_X.Filter_CSTATE_k[0] =
    ControllerForExport_P.TorquePID_InitialConditionForFi;

  /* InitializeConditions for Memory: '<S29>/Memory' */
  ControllerForExport_DW.Memory_PreviousInput[0] =
    ControllerForExport_P.Memory_InitialCondition;

  /* InitializeConditions for Memory: '<S81>/Memory' */
  ControllerForExport_DW.Memory_PreviousInput_f[0] =
    ControllerForExport_P.Memory_InitialCondition_l;

  /* InitializeConditions for Integrator: '<S39>/Integrator' */
  ControllerForExport_X.Integrator_CSTATE[1] =
    ControllerForExport_P.ForcePID_InitialConditionForInt;

  /* InitializeConditions for Integrator: '<S34>/Filter' */
  ControllerForExport_X.Filter_CSTATE[1] =
    ControllerForExport_P.ForcePID_InitialConditionForFil;

  /* InitializeConditions for Integrator: '<S91>/Integrator' */
  ControllerForExport_X.Integrator_CSTATE_a[1] =
    ControllerForExport_P.TorquePID_InitialConditionForIn;

  /* InitializeConditions for Integrator: '<S86>/Filter' */
  ControllerForExport_X.Filter_CSTATE_k[1] =
    ControllerForExport_P.TorquePID_InitialConditionForFi;

  /* InitializeConditions for Memory: '<S29>/Memory' */
  ControllerForExport_DW.Memory_PreviousInput[1] =
    ControllerForExport_P.Memory_InitialCondition;

  /* InitializeConditions for Memory: '<S81>/Memory' */
  ControllerForExport_DW.Memory_PreviousInput_f[1] =
    ControllerForExport_P.Memory_InitialCondition_l;

  /* InitializeConditions for Integrator: '<S39>/Integrator' */
  ControllerForExport_X.Integrator_CSTATE[2] =
    ControllerForExport_P.ForcePID_InitialConditionForInt;

  /* InitializeConditions for Integrator: '<S34>/Filter' */
  ControllerForExport_X.Filter_CSTATE[2] =
    ControllerForExport_P.ForcePID_InitialConditionForFil;

  /* InitializeConditions for Integrator: '<S91>/Integrator' */
  ControllerForExport_X.Integrator_CSTATE_a[2] =
    ControllerForExport_P.TorquePID_InitialConditionForIn;

  /* InitializeConditions for Integrator: '<S86>/Filter' */
  ControllerForExport_X.Filter_CSTATE_k[2] =
    ControllerForExport_P.TorquePID_InitialConditionForFi;

  /* InitializeConditions for Memory: '<S29>/Memory' */
  ControllerForExport_DW.Memory_PreviousInput[2] =
    ControllerForExport_P.Memory_InitialCondition;

  /* InitializeConditions for Memory: '<S81>/Memory' */
  ControllerForExport_DW.Memory_PreviousInput_f[2] =
    ControllerForExport_P.Memory_InitialCondition_l;
}

/* Model terminate function */
void ControllerForExport::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
ControllerForExport::ControllerForExport() :
  ControllerForExport_U(),
  ControllerForExport_Y(),
  ControllerForExport_B(),
  ControllerForExport_DW(),
  ControllerForExport_X(),
  ControllerForExport_XDis(),
  ControllerForExport_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
ControllerForExport::~ControllerForExport() = default;

/* Real-Time Model get method */
RT_MODEL_ControllerForExport_T * ControllerForExport::getRTM()
{
  return (&ControllerForExport_M);
}
