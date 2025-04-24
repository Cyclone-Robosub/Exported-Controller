/*
 * ControllerForExport_data.cpp
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

/* Block parameters (default storage) */
P_ControllerForExport_T ControllerForExport::ControllerForExport_P{
  /* Variable: inverse_wrench
   * Referenced by: '<Root>/Constant'
   */
  { 0.090000000000000024, 0.089999999999999983, -0.089999999999999983,
    -0.089999999999999983, 0.35355339059327373, 0.35355339059327373,
    0.35355339059327373, 0.35355339059327373, -0.10227272727272732,
    0.10227272727272736, -0.10227272727272729, 0.10227272727272731,
    0.35355339059327395, -0.35355339059327395, -0.35355339059327395,
    0.35355339059327395, -0.24999999999999997, -0.24999999999999989,
    -0.24999999999999997, -0.25, 0.0, 0.0, 0.0, 0.0, 1.1363636363636362,
    -1.1363636363636365, 1.1363636363636362, -1.1363636363636365,
    -1.2385988437816789E-16, 6.1717010246948657E-17, 6.1717010246948657E-17,
    -1.2385988437816789E-16, 1.0, 1.0, -1.0, -1.0, 6.0061913394359678E-18,
    6.0061913394359678E-18, 6.0061913394359678E-18, 6.0061913394359678E-18,
    -3.63447328399022E-16, 2.7258549629926646E-16, 1.2114910946634065E-16,
    -1.34608267418164E-16, 1.3094570021973104, -1.30945700219731,
    1.3094570021973098, -1.3094570021973102 },

  /* Variable: kd_F
   * Referenced by: '<S32>/Derivative Gain'
   */
  4000.0,

  /* Variable: kd_T
   * Referenced by: '<S84>/Derivative Gain'
   */
  4000.0,

  /* Variable: ki_F
   * Referenced by: '<S36>/Integral Gain'
   */
  100.0,

  /* Variable: ki_T
   * Referenced by: '<S88>/Integral Gain'
   */
  100.0,

  /* Variable: kp_F
   * Referenced by: '<S44>/Proportional Gain'
   */
  2000.0,

  /* Variable: kp_T
   * Referenced by: '<S96>/Proportional Gain'
   */
  2000.0,

  /* Mask Parameter: ForcePID_InitialConditionForFil
   * Referenced by: '<S34>/Filter'
   */
  0.0,

  /* Mask Parameter: TorquePID_InitialConditionForFi
   * Referenced by: '<S86>/Filter'
   */
  0.0,

  /* Mask Parameter: ForcePID_InitialConditionForInt
   * Referenced by: '<S39>/Integrator'
   */
  0.0,

  /* Mask Parameter: TorquePID_InitialConditionForIn
   * Referenced by: '<S91>/Integrator'
   */
  0.0,

  /* Mask Parameter: ForcePID_LowerSaturationLimit
   * Referenced by:
   *   '<S46>/Saturation'
   *   '<S31>/DeadZone'
   */
  -85.0,

  /* Mask Parameter: TorquePID_LowerSaturationLimit
   * Referenced by:
   *   '<S98>/Saturation'
   *   '<S83>/DeadZone'
   */
  -30.0,

  /* Mask Parameter: ForcePID_N
   * Referenced by: '<S42>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: TorquePID_N
   * Referenced by: '<S94>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: ForcePID_UpperSaturationLimit
   * Referenced by:
   *   '<S46>/Saturation'
   *   '<S31>/DeadZone'
   */
  85.0,

  /* Mask Parameter: TorquePID_UpperSaturationLimit
   * Referenced by:
   *   '<S98>/Saturation'
   *   '<S83>/DeadZone'
   */
  30.0,

  /* Expression: 0
   * Referenced by: '<S29>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S81>/Constant1'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S29>/ZeroGain'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S81>/ZeroGain'
   */
  0.0,

  /* Computed Parameter: Memory_InitialCondition
   * Referenced by: '<S29>/Memory'
   */
  false,

  /* Computed Parameter: Memory_InitialCondition_l
   * Referenced by: '<S81>/Memory'
   */
  false
};
