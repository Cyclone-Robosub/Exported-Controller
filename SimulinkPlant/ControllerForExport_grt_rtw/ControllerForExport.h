/*
 * ControllerForExport.h
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

#ifndef ControllerForExport_h_
#define ControllerForExport_h_
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "ControllerForExport_types.h"

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

#include <cfloat>
#include <cstring>

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

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
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

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
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

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
struct B_ControllerForExport_T {
  real_T ProportionalGain[3];          /* '<S44>/Proportional Gain' */
  real_T Integrator[3];                /* '<S39>/Integrator' */
  real_T DerivativeGain[3];            /* '<S32>/Derivative Gain' */
  real_T Filter[3];                    /* '<S34>/Filter' */
  real_T SumD[3];                      /* '<S34>/SumD' */
  real_T FilterCoefficient[3];         /* '<S42>/Filter Coefficient' */
  real_T Sum[3];                       /* '<S48>/Sum' */
  real_T Saturation[3];                /* '<S46>/Saturation' */
  real_T ProportionalGain_l[3];        /* '<S96>/Proportional Gain' */
  real_T Integrator_a[3];              /* '<S91>/Integrator' */
  real_T DerivativeGain_l[3];          /* '<S84>/Derivative Gain' */
  real_T Filter_b[3];                  /* '<S86>/Filter' */
  real_T SumD_k[3];                    /* '<S86>/SumD' */
  real_T FilterCoefficient_h[3];       /* '<S94>/Filter Coefficient' */
  real_T Sum_h[3];                     /* '<S100>/Sum' */
  real_T Saturation_e[3];              /* '<S98>/Saturation' */
  real_T TmpSignalConversionAtMapsforces[6];
  real_T Mapsforcestopwms[8];          /* '<Root>/Maps forces to pwms' */
  real_T ZeroGain[3];                  /* '<S29>/ZeroGain' */
  real_T DeadZone[3];                  /* '<S31>/DeadZone' */
  real_T SignPreSat[3];                /* '<S29>/SignPreSat' */
  real_T IntegralGain[3];              /* '<S36>/Integral Gain' */
  real_T SignPreIntegrator[3];         /* '<S29>/SignPreIntegrator' */
  real_T Switch[3];                    /* '<S29>/Switch' */
  real_T ZeroGain_a[3];                /* '<S81>/ZeroGain' */
  real_T DeadZone_o[3];                /* '<S83>/DeadZone' */
  real_T SignPreSat_m[3];              /* '<S81>/SignPreSat' */
  real_T IntegralGain_g[3];            /* '<S88>/Integral Gain' */
  real_T SignPreIntegrator_a[3];       /* '<S81>/SignPreIntegrator' */
  real_T Switch_e[3];                  /* '<S81>/Switch' */
  real_T pwm_cmd[8];                   /* '<Root>/Thruster Forces to PWM' */
  int8_T DataTypeConv1[3];             /* '<S29>/DataTypeConv1' */
  int8_T DataTypeConv2[3];             /* '<S29>/DataTypeConv2' */
  int8_T DataTypeConv1_f[3];           /* '<S81>/DataTypeConv1' */
  int8_T DataTypeConv2_j[3];           /* '<S81>/DataTypeConv2' */
  boolean_T NotEqual[3];               /* '<S29>/NotEqual' */
  boolean_T Equal1[3];                 /* '<S29>/Equal1' */
  boolean_T AND3[3];                   /* '<S29>/AND3' */
  boolean_T Memory[3];                 /* '<S29>/Memory' */
  boolean_T NotEqual_o[3];             /* '<S81>/NotEqual' */
  boolean_T Equal1_n[3];               /* '<S81>/Equal1' */
  boolean_T AND3_a[3];                 /* '<S81>/AND3' */
  boolean_T Memory_k[3];               /* '<S81>/Memory' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_ControllerForExport_T {
  boolean_T Memory_PreviousInput[3];   /* '<S29>/Memory' */
  boolean_T Memory_PreviousInput_f[3]; /* '<S81>/Memory' */
};

/* Continuous states (default storage) */
struct X_ControllerForExport_T {
  real_T Integrator_CSTATE[3];         /* '<S39>/Integrator' */
  real_T Filter_CSTATE[3];             /* '<S34>/Filter' */
  real_T Integrator_CSTATE_a[3];       /* '<S91>/Integrator' */
  real_T Filter_CSTATE_k[3];           /* '<S86>/Filter' */
};

/* State derivatives (default storage) */
struct XDot_ControllerForExport_T {
  real_T Integrator_CSTATE[3];         /* '<S39>/Integrator' */
  real_T Filter_CSTATE[3];             /* '<S34>/Filter' */
  real_T Integrator_CSTATE_a[3];       /* '<S91>/Integrator' */
  real_T Filter_CSTATE_k[3];           /* '<S86>/Filter' */
};

/* State disabled  */
struct XDis_ControllerForExport_T {
  boolean_T Integrator_CSTATE[3];      /* '<S39>/Integrator' */
  boolean_T Filter_CSTATE[3];          /* '<S34>/Filter' */
  boolean_T Integrator_CSTATE_a[3];    /* '<S91>/Integrator' */
  boolean_T Filter_CSTATE_k[3];        /* '<S86>/Filter' */
};

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
struct ODE3_IntgData {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
};

#endif

/* External inputs (root inport signals with default storage) */
struct ExtU_ControllerForExport_T {
  real_T ErrorSIgnal[6];               /* '<Root>/Error SIgnal' */
};

/* External outputs (root outports fed by signals with default storage) */
struct ExtY_ControllerForExport_T {
  real_T PWM[8];                       /* '<Root>/PWM' */
};

/* Parameters (default storage) */
struct P_ControllerForExport_T_ {
  real_T inverse_wrench[48];           /* Variable: inverse_wrench
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T kd_F;                         /* Variable: kd_F
                                        * Referenced by: '<S32>/Derivative Gain'
                                        */
  real_T kd_T;                         /* Variable: kd_T
                                        * Referenced by: '<S84>/Derivative Gain'
                                        */
  real_T ki_F;                         /* Variable: ki_F
                                        * Referenced by: '<S36>/Integral Gain'
                                        */
  real_T ki_T;                         /* Variable: ki_T
                                        * Referenced by: '<S88>/Integral Gain'
                                        */
  real_T kp_F;                         /* Variable: kp_F
                                        * Referenced by: '<S44>/Proportional Gain'
                                        */
  real_T kp_T;                         /* Variable: kp_T
                                        * Referenced by: '<S96>/Proportional Gain'
                                        */
  real_T ForcePID_InitialConditionForFil;
                              /* Mask Parameter: ForcePID_InitialConditionForFil
                               * Referenced by: '<S34>/Filter'
                               */
  real_T TorquePID_InitialConditionForFi;
                              /* Mask Parameter: TorquePID_InitialConditionForFi
                               * Referenced by: '<S86>/Filter'
                               */
  real_T ForcePID_InitialConditionForInt;
                              /* Mask Parameter: ForcePID_InitialConditionForInt
                               * Referenced by: '<S39>/Integrator'
                               */
  real_T TorquePID_InitialConditionForIn;
                              /* Mask Parameter: TorquePID_InitialConditionForIn
                               * Referenced by: '<S91>/Integrator'
                               */
  real_T ForcePID_LowerSaturationLimit;
                                /* Mask Parameter: ForcePID_LowerSaturationLimit
                                 * Referenced by:
                                 *   '<S46>/Saturation'
                                 *   '<S31>/DeadZone'
                                 */
  real_T TorquePID_LowerSaturationLimit;
                               /* Mask Parameter: TorquePID_LowerSaturationLimit
                                * Referenced by:
                                *   '<S98>/Saturation'
                                *   '<S83>/DeadZone'
                                */
  real_T ForcePID_N;                   /* Mask Parameter: ForcePID_N
                                        * Referenced by: '<S42>/Filter Coefficient'
                                        */
  real_T TorquePID_N;                  /* Mask Parameter: TorquePID_N
                                        * Referenced by: '<S94>/Filter Coefficient'
                                        */
  real_T ForcePID_UpperSaturationLimit;
                                /* Mask Parameter: ForcePID_UpperSaturationLimit
                                 * Referenced by:
                                 *   '<S46>/Saturation'
                                 *   '<S31>/DeadZone'
                                 */
  real_T TorquePID_UpperSaturationLimit;
                               /* Mask Parameter: TorquePID_UpperSaturationLimit
                                * Referenced by:
                                *   '<S98>/Saturation'
                                *   '<S83>/DeadZone'
                                */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S29>/Constant1'
                                        */
  real_T Constant1_Value_m;            /* Expression: 0
                                        * Referenced by: '<S81>/Constant1'
                                        */
  real_T ZeroGain_Gain;                /* Expression: 0
                                        * Referenced by: '<S29>/ZeroGain'
                                        */
  real_T ZeroGain_Gain_m;              /* Expression: 0
                                        * Referenced by: '<S81>/ZeroGain'
                                        */
  boolean_T Memory_InitialCondition;
                                  /* Computed Parameter: Memory_InitialCondition
                                   * Referenced by: '<S29>/Memory'
                                   */
  boolean_T Memory_InitialCondition_l;
                                /* Computed Parameter: Memory_InitialCondition_l
                                 * Referenced by: '<S81>/Memory'
                                 */
};

/* Real-time Model Data Structure */
struct tag_RTM_ControllerForExport_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_ControllerForExport_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_ControllerForExport_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[12];
  real_T odeF[3][12];
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
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tStart;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model ControllerForExport */
class ControllerForExport final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  ControllerForExport(ControllerForExport const&) = delete;

  /* Assignment Operator */
  ControllerForExport& operator= (ControllerForExport const&) & = delete;

  /* Move Constructor */
  ControllerForExport(ControllerForExport &&) = delete;

  /* Move Assignment Operator */
  ControllerForExport& operator= (ControllerForExport &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_ControllerForExport_T * getRTM();

  /* External inputs */
  ExtU_ControllerForExport_T ControllerForExport_U;

  /* External outputs */
  ExtY_ControllerForExport_T ControllerForExport_Y;

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  ControllerForExport();

  /* Destructor */
  ~ControllerForExport();

  /* private data and function members */
 private:
  /* Block signals */
  B_ControllerForExport_T ControllerForExport_B;

  /* Block states */
  DW_ControllerForExport_T ControllerForExport_DW;

  /* Tunable parameters */
  static P_ControllerForExport_T ControllerForExport_P;

  /* Block continuous states */
  X_ControllerForExport_T ControllerForExport_X;

  /* Block Continuous state disabled vector */
  XDis_ControllerForExport_T ControllerForExport_XDis;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void ControllerForExport_derivatives();

  /* Real-Time Model */
  RT_MODEL_ControllerForExport_T ControllerForExport_M;
};

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
 * '<Root>' : 'ControllerForExport'
 * '<S1>'   : 'ControllerForExport/Force PID'
 * '<S2>'   : 'ControllerForExport/Thruster Forces to PWM'
 * '<S3>'   : 'ControllerForExport/Torque PID'
 * '<S4>'   : 'ControllerForExport/Force PID/Anti-windup'
 * '<S5>'   : 'ControllerForExport/Force PID/D Gain'
 * '<S6>'   : 'ControllerForExport/Force PID/External Derivative'
 * '<S7>'   : 'ControllerForExport/Force PID/Filter'
 * '<S8>'   : 'ControllerForExport/Force PID/Filter ICs'
 * '<S9>'   : 'ControllerForExport/Force PID/I Gain'
 * '<S10>'  : 'ControllerForExport/Force PID/Ideal P Gain'
 * '<S11>'  : 'ControllerForExport/Force PID/Ideal P Gain Fdbk'
 * '<S12>'  : 'ControllerForExport/Force PID/Integrator'
 * '<S13>'  : 'ControllerForExport/Force PID/Integrator ICs'
 * '<S14>'  : 'ControllerForExport/Force PID/N Copy'
 * '<S15>'  : 'ControllerForExport/Force PID/N Gain'
 * '<S16>'  : 'ControllerForExport/Force PID/P Copy'
 * '<S17>'  : 'ControllerForExport/Force PID/Parallel P Gain'
 * '<S18>'  : 'ControllerForExport/Force PID/Reset Signal'
 * '<S19>'  : 'ControllerForExport/Force PID/Saturation'
 * '<S20>'  : 'ControllerForExport/Force PID/Saturation Fdbk'
 * '<S21>'  : 'ControllerForExport/Force PID/Sum'
 * '<S22>'  : 'ControllerForExport/Force PID/Sum Fdbk'
 * '<S23>'  : 'ControllerForExport/Force PID/Tracking Mode'
 * '<S24>'  : 'ControllerForExport/Force PID/Tracking Mode Sum'
 * '<S25>'  : 'ControllerForExport/Force PID/Tsamp - Integral'
 * '<S26>'  : 'ControllerForExport/Force PID/Tsamp - Ngain'
 * '<S27>'  : 'ControllerForExport/Force PID/postSat Signal'
 * '<S28>'  : 'ControllerForExport/Force PID/preSat Signal'
 * '<S29>'  : 'ControllerForExport/Force PID/Anti-windup/Cont. Clamping Parallel'
 * '<S30>'  : 'ControllerForExport/Force PID/Anti-windup/Cont. Clamping Parallel/Dead Zone'
 * '<S31>'  : 'ControllerForExport/Force PID/Anti-windup/Cont. Clamping Parallel/Dead Zone/Enabled'
 * '<S32>'  : 'ControllerForExport/Force PID/D Gain/Internal Parameters'
 * '<S33>'  : 'ControllerForExport/Force PID/External Derivative/Error'
 * '<S34>'  : 'ControllerForExport/Force PID/Filter/Cont. Filter'
 * '<S35>'  : 'ControllerForExport/Force PID/Filter ICs/Internal IC - Filter'
 * '<S36>'  : 'ControllerForExport/Force PID/I Gain/Internal Parameters'
 * '<S37>'  : 'ControllerForExport/Force PID/Ideal P Gain/Passthrough'
 * '<S38>'  : 'ControllerForExport/Force PID/Ideal P Gain Fdbk/Disabled'
 * '<S39>'  : 'ControllerForExport/Force PID/Integrator/Continuous'
 * '<S40>'  : 'ControllerForExport/Force PID/Integrator ICs/Internal IC'
 * '<S41>'  : 'ControllerForExport/Force PID/N Copy/Disabled'
 * '<S42>'  : 'ControllerForExport/Force PID/N Gain/Internal Parameters'
 * '<S43>'  : 'ControllerForExport/Force PID/P Copy/Disabled'
 * '<S44>'  : 'ControllerForExport/Force PID/Parallel P Gain/Internal Parameters'
 * '<S45>'  : 'ControllerForExport/Force PID/Reset Signal/Disabled'
 * '<S46>'  : 'ControllerForExport/Force PID/Saturation/Enabled'
 * '<S47>'  : 'ControllerForExport/Force PID/Saturation Fdbk/Disabled'
 * '<S48>'  : 'ControllerForExport/Force PID/Sum/Sum_PID'
 * '<S49>'  : 'ControllerForExport/Force PID/Sum Fdbk/Disabled'
 * '<S50>'  : 'ControllerForExport/Force PID/Tracking Mode/Disabled'
 * '<S51>'  : 'ControllerForExport/Force PID/Tracking Mode Sum/Passthrough'
 * '<S52>'  : 'ControllerForExport/Force PID/Tsamp - Integral/TsSignalSpecification'
 * '<S53>'  : 'ControllerForExport/Force PID/Tsamp - Ngain/Passthrough'
 * '<S54>'  : 'ControllerForExport/Force PID/postSat Signal/Forward_Path'
 * '<S55>'  : 'ControllerForExport/Force PID/preSat Signal/Forward_Path'
 * '<S56>'  : 'ControllerForExport/Torque PID/Anti-windup'
 * '<S57>'  : 'ControllerForExport/Torque PID/D Gain'
 * '<S58>'  : 'ControllerForExport/Torque PID/External Derivative'
 * '<S59>'  : 'ControllerForExport/Torque PID/Filter'
 * '<S60>'  : 'ControllerForExport/Torque PID/Filter ICs'
 * '<S61>'  : 'ControllerForExport/Torque PID/I Gain'
 * '<S62>'  : 'ControllerForExport/Torque PID/Ideal P Gain'
 * '<S63>'  : 'ControllerForExport/Torque PID/Ideal P Gain Fdbk'
 * '<S64>'  : 'ControllerForExport/Torque PID/Integrator'
 * '<S65>'  : 'ControllerForExport/Torque PID/Integrator ICs'
 * '<S66>'  : 'ControllerForExport/Torque PID/N Copy'
 * '<S67>'  : 'ControllerForExport/Torque PID/N Gain'
 * '<S68>'  : 'ControllerForExport/Torque PID/P Copy'
 * '<S69>'  : 'ControllerForExport/Torque PID/Parallel P Gain'
 * '<S70>'  : 'ControllerForExport/Torque PID/Reset Signal'
 * '<S71>'  : 'ControllerForExport/Torque PID/Saturation'
 * '<S72>'  : 'ControllerForExport/Torque PID/Saturation Fdbk'
 * '<S73>'  : 'ControllerForExport/Torque PID/Sum'
 * '<S74>'  : 'ControllerForExport/Torque PID/Sum Fdbk'
 * '<S75>'  : 'ControllerForExport/Torque PID/Tracking Mode'
 * '<S76>'  : 'ControllerForExport/Torque PID/Tracking Mode Sum'
 * '<S77>'  : 'ControllerForExport/Torque PID/Tsamp - Integral'
 * '<S78>'  : 'ControllerForExport/Torque PID/Tsamp - Ngain'
 * '<S79>'  : 'ControllerForExport/Torque PID/postSat Signal'
 * '<S80>'  : 'ControllerForExport/Torque PID/preSat Signal'
 * '<S81>'  : 'ControllerForExport/Torque PID/Anti-windup/Cont. Clamping Parallel'
 * '<S82>'  : 'ControllerForExport/Torque PID/Anti-windup/Cont. Clamping Parallel/Dead Zone'
 * '<S83>'  : 'ControllerForExport/Torque PID/Anti-windup/Cont. Clamping Parallel/Dead Zone/Enabled'
 * '<S84>'  : 'ControllerForExport/Torque PID/D Gain/Internal Parameters'
 * '<S85>'  : 'ControllerForExport/Torque PID/External Derivative/Error'
 * '<S86>'  : 'ControllerForExport/Torque PID/Filter/Cont. Filter'
 * '<S87>'  : 'ControllerForExport/Torque PID/Filter ICs/Internal IC - Filter'
 * '<S88>'  : 'ControllerForExport/Torque PID/I Gain/Internal Parameters'
 * '<S89>'  : 'ControllerForExport/Torque PID/Ideal P Gain/Passthrough'
 * '<S90>'  : 'ControllerForExport/Torque PID/Ideal P Gain Fdbk/Disabled'
 * '<S91>'  : 'ControllerForExport/Torque PID/Integrator/Continuous'
 * '<S92>'  : 'ControllerForExport/Torque PID/Integrator ICs/Internal IC'
 * '<S93>'  : 'ControllerForExport/Torque PID/N Copy/Disabled'
 * '<S94>'  : 'ControllerForExport/Torque PID/N Gain/Internal Parameters'
 * '<S95>'  : 'ControllerForExport/Torque PID/P Copy/Disabled'
 * '<S96>'  : 'ControllerForExport/Torque PID/Parallel P Gain/Internal Parameters'
 * '<S97>'  : 'ControllerForExport/Torque PID/Reset Signal/Disabled'
 * '<S98>'  : 'ControllerForExport/Torque PID/Saturation/Enabled'
 * '<S99>'  : 'ControllerForExport/Torque PID/Saturation Fdbk/Disabled'
 * '<S100>' : 'ControllerForExport/Torque PID/Sum/Sum_PID'
 * '<S101>' : 'ControllerForExport/Torque PID/Sum Fdbk/Disabled'
 * '<S102>' : 'ControllerForExport/Torque PID/Tracking Mode/Disabled'
 * '<S103>' : 'ControllerForExport/Torque PID/Tracking Mode Sum/Passthrough'
 * '<S104>' : 'ControllerForExport/Torque PID/Tsamp - Integral/TsSignalSpecification'
 * '<S105>' : 'ControllerForExport/Torque PID/Tsamp - Ngain/Passthrough'
 * '<S106>' : 'ControllerForExport/Torque PID/postSat Signal/Forward_Path'
 * '<S107>' : 'ControllerForExport/Torque PID/preSat Signal/Forward_Path'
 */
#endif                                 /* ControllerForExport_h_ */
