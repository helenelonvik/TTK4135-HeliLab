/*
 * helicopterOppg4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterOppg4".
 *
 * Model version              : 11.12
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Mon Mar 22 10:41:07 2021
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopterOppg4.h"
#include "helicopterOppg4_private.h"
#include "helicopterOppg4_dt.h"

/* Block signals (default storage) */
B_helicopterOppg4_T helicopterOppg4_B;

/* Continuous states */
X_helicopterOppg4_T helicopterOppg4_X;

/* Block states (default storage) */
DW_helicopterOppg4_T helicopterOppg4_DW;

/* Real-time model */
static RT_MODEL_helicopterOppg4_T helicopterOppg4_M_;
RT_MODEL_helicopterOppg4_T *const helicopterOppg4_M = &helicopterOppg4_M_;

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopterOppg4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopterOppg4_output(void)
{
  /* local block i/o variables */
  real_T rtb_Sum1_k[2];
  real_T rtb_Sum[6];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Gain1[6];
  real_T lastTime;
  real_T rtb_Backgain;
  real_T rtb_Clock;
  real_T rtb_Derivative;
  real_T *lastU;
  int32_T i;
  int32_T i_0;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopterOppg4_M)) {
    /* set solver stop time */
    if (!(helicopterOppg4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopterOppg4_M->solverInfo,
                            ((helicopterOppg4_M->Timing.clockTickH0 + 1) *
        helicopterOppg4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopterOppg4_M->solverInfo,
                            ((helicopterOppg4_M->Timing.clockTick0 + 1) *
        helicopterOppg4_M->Timing.stepSize0 +
        helicopterOppg4_M->Timing.clockTickH0 *
        helicopterOppg4_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopterOppg4_M)) {
    helicopterOppg4_M->Timing.t[0] = rtsiGetT(&helicopterOppg4_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopterOppg4_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopterOppg4_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopterOppg4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopterOppg4_DW.HILReadEncoderTimebase_Task, 1,
         &helicopterOppg4_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopterOppg4_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopterOppg4_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopterOppg4_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S5>/Travel: Count to rad' incorporates:
     *  Gain: '<S5>/Travel_gain'
     */
    helicopterOppg4_B.TravelCounttorad = helicopterOppg4_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopterOppg4_P.TravelCounttorad_Gain;

    /* Gain: '<S13>/Gain' */
    helicopterOppg4_B.Gain = helicopterOppg4_P.Gain_Gain *
      helicopterOppg4_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/travel_offset [deg]'
     */
    helicopterOppg4_B.Sum3 = helicopterOppg4_P.travel_offsetdeg_Value +
      helicopterOppg4_B.Gain;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopterOppg4_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopterOppg4_DW.ToFile_IWORK.Count * (1 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterOppg4_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[1 + 1];
          helicopterOppg4_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopterOppg4_M->Timing.t[1];
          u[1] = helicopterOppg4_B.Sum3;
          if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
            rtmSetErrorStatus(helicopterOppg4_M,
                              "Error writing to MAT-file travel_10_opt.mat");
            return;
          }

          if (((++helicopterOppg4_DW.ToFile_IWORK.Count) * (1 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file travel_10_opt.mat.\n");
          }
        }
      }
    }

    /* Gain: '<S5>/Pitch: Count to rad' */
    helicopterOppg4_B.PitchCounttorad = helicopterOppg4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopterOppg4_B.Gain_i = helicopterOppg4_P.Gain_Gain_a *
      helicopterOppg4_B.PitchCounttorad;

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++helicopterOppg4_DW.ToFile1_IWORK.Decimation % 1) &&
          (helicopterOppg4_DW.ToFile1_IWORK.Count * (1 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterOppg4_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[1 + 1];
          helicopterOppg4_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helicopterOppg4_M->Timing.t[1];
          u[1] = helicopterOppg4_B.Gain_i;
          if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
            rtmSetErrorStatus(helicopterOppg4_M,
                              "Error writing to MAT-file pitch_10_opt.mat");
            return;
          }

          if (((++helicopterOppg4_DW.ToFile1_IWORK.Count) * (1 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file pitch_10_opt.mat.\n");
          }
        }
      }
    }

    /* Gain: '<S5>/Elevation: Count to rad' incorporates:
     *  Gain: '<S5>/Elevation_gain'
     */
    helicopterOppg4_B.ElevationCounttorad = helicopterOppg4_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopterOppg4_P.ElevationCounttorad_Gain;

    /* Gain: '<S8>/Gain' */
    helicopterOppg4_B.Gain_e = helicopterOppg4_P.Gain_Gain_l *
      helicopterOppg4_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopterOppg4_B.Sum = helicopterOppg4_B.Gain_e +
      helicopterOppg4_P.elavation_offsetdeg_Value;

    /* ToFile: '<Root>/To File2' */
    {
      if (!(++helicopterOppg4_DW.ToFile2_IWORK.Decimation % 1) &&
          (helicopterOppg4_DW.ToFile2_IWORK.Count * (1 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterOppg4_DW.ToFile2_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[1 + 1];
          helicopterOppg4_DW.ToFile2_IWORK.Decimation = 0;
          u[0] = helicopterOppg4_M->Timing.t[1];
          u[1] = helicopterOppg4_B.Sum;
          if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
            rtmSetErrorStatus(helicopterOppg4_M,
                              "Error writing to MAT-file elevation_10_opt.mat");
            return;
          }

          if (((++helicopterOppg4_DW.ToFile2_IWORK.Count) * (1 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file elevation_10_opt.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopterOppg4_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopterOppg4_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopterOppg4_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopterOppg4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopterOppg4_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_Sum1_k[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_Sum1_k[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 81;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum1_k[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      helicopterOppg4_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopterOppg4_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopterOppg4_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopterOppg4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopterOppg4_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Sum[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Sum[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 81;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  /* Gain: '<S14>/Gain' incorporates:
   *  TransferFcn: '<S5>/Travel: Transfer Fcn'
   */
  helicopterOppg4_B.Gain_d = (helicopterOppg4_P.TravelTransferFcn_C *
    helicopterOppg4_X.TravelTransferFcn_CSTATE +
    helicopterOppg4_P.TravelTransferFcn_D * helicopterOppg4_B.TravelCounttorad) *
    helicopterOppg4_P.Gain_Gain_lu;

  /* Gain: '<S11>/Gain' incorporates:
   *  TransferFcn: '<S5>/Pitch: Transfer Fcn'
   */
  helicopterOppg4_B.Gain_b = (helicopterOppg4_P.PitchTransferFcn_C *
    helicopterOppg4_X.PitchTransferFcn_CSTATE +
    helicopterOppg4_P.PitchTransferFcn_D * helicopterOppg4_B.PitchCounttorad) *
    helicopterOppg4_P.Gain_Gain_ae;

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S5>/Elevation: Transfer Fcn'
   */
  helicopterOppg4_B.Gain_dg = (helicopterOppg4_P.ElevationTransferFcn_C *
    helicopterOppg4_X.ElevationTransferFcn_CSTATE +
    helicopterOppg4_P.ElevationTransferFcn_D *
    helicopterOppg4_B.ElevationCounttorad) * helicopterOppg4_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1[0] = helicopterOppg4_P.Gain1_Gain * helicopterOppg4_B.Sum3;
  rtb_Gain1[1] = helicopterOppg4_P.Gain1_Gain * helicopterOppg4_B.Gain_d;
  rtb_Gain1[2] = helicopterOppg4_P.Gain1_Gain * helicopterOppg4_B.Gain_i;
  rtb_Gain1[3] = helicopterOppg4_P.Gain1_Gain * helicopterOppg4_B.Gain_b;
  rtb_Gain1[4] = helicopterOppg4_P.Gain1_Gain * helicopterOppg4_B.Sum;
  rtb_Gain1[5] = helicopterOppg4_P.Gain1_Gain * helicopterOppg4_B.Gain_dg;
  for (i = 0; i < 6; i++) {
    /* Sum: '<S4>/Sum' */
    rtb_Sum[i] = rtb_Gain1[i] - rtb_Sum[i];
  }

  for (i = 0; i < 2; i++) {
    /* Sum: '<S4>/Sum1' incorporates:
     *  Gain: '<S4>/K_lqr*u'
     */
    rtb_Clock = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Clock += helicopterOppg4_P.K_lqr[(i_0 << 1) + i] * rtb_Sum[i_0];
    }

    rtb_Sum1_k[i] -= rtb_Clock;

    /* End of Sum: '<S4>/Sum1' */
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S6>/K_pd'
   *  Gain: '<S6>/K_pp'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   */
  rtb_Clock = ((rtb_Sum1_k[0] - rtb_Gain1[2]) * helicopterOppg4_P.K_pp -
               helicopterOppg4_P.K_pd * rtb_Gain1[3]) + helicopterOppg4_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopterOppg4_X.Integrator_CSTATE >=
      helicopterOppg4_P.Integrator_UpperSat) {
    helicopterOppg4_X.Integrator_CSTATE = helicopterOppg4_P.Integrator_UpperSat;
  } else {
    if (helicopterOppg4_X.Integrator_CSTATE <=
        helicopterOppg4_P.Integrator_LowerSat) {
      helicopterOppg4_X.Integrator_CSTATE =
        helicopterOppg4_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' */
  rtb_Derivative = rtb_Sum1_k[1] - rtb_Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopterOppg4_P.K_ep * rtb_Derivative +
                   helicopterOppg4_X.Integrator_CSTATE) - helicopterOppg4_P.K_ed
                  * rtb_Gain1[5]) + helicopterOppg4_P.Vs_ff;

  /* If: '<S3>/If' incorporates:
   *  Clock: '<S3>/Clock'
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S7>/In1'
   */
  if (rtmIsMajorTimeStep(helicopterOppg4_M)) {
    rtAction = (int8_T)!(helicopterOppg4_M->Timing.t[0] >= 2.0);
    helicopterOppg4_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopterOppg4_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    helicopterOppg4_B.In1 = helicopterOppg4_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopterOppg4_M)) {
      srUpdateBC(helicopterOppg4_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopterOppg4_M)) {
  }

  /* Derivative: '<S5>/Derivative' */
  rtb_Derivative = helicopterOppg4_M->Timing.t[0];
  if ((helicopterOppg4_DW.TimeStampA >= rtb_Derivative) &&
      (helicopterOppg4_DW.TimeStampB >= rtb_Derivative)) {
    rtb_Derivative = 0.0;
  } else {
    lastTime = helicopterOppg4_DW.TimeStampA;
    lastU = &helicopterOppg4_DW.LastUAtTimeA;
    if (helicopterOppg4_DW.TimeStampA < helicopterOppg4_DW.TimeStampB) {
      if (helicopterOppg4_DW.TimeStampB < rtb_Derivative) {
        lastTime = helicopterOppg4_DW.TimeStampB;
        lastU = &helicopterOppg4_DW.LastUAtTimeB;
      }
    } else {
      if (helicopterOppg4_DW.TimeStampA >= rtb_Derivative) {
        lastTime = helicopterOppg4_DW.TimeStampB;
        lastU = &helicopterOppg4_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopterOppg4_B.PitchCounttorad - *lastU) /
      (rtb_Derivative - lastTime);
  }

  /* End of Derivative: '<S5>/Derivative' */

  /* Gain: '<S12>/Gain' */
  helicopterOppg4_B.Gain_l = helicopterOppg4_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopterOppg4_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Derivative = (rtb_Backgain - rtb_Clock) * helicopterOppg4_P.Backgain_Gain;

  /* Saturate: '<S5>/Back motor: Saturation' */
  if (rtb_Derivative > helicopterOppg4_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S5>/Back motor: Saturation' */
    helicopterOppg4_B.BackmotorSaturation =
      helicopterOppg4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopterOppg4_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S5>/Back motor: Saturation' */
    helicopterOppg4_B.BackmotorSaturation =
      helicopterOppg4_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S5>/Back motor: Saturation' */
    helicopterOppg4_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S5>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterOppg4_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (rtb_Clock + rtb_Backgain) * helicopterOppg4_P.Frontgain_Gain;

  /* Saturate: '<S5>/Front motor: Saturation' */
  if (rtb_Derivative > helicopterOppg4_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S5>/Front motor: Saturation' */
    helicopterOppg4_B.FrontmotorSaturation =
      helicopterOppg4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopterOppg4_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S5>/Front motor: Saturation' */
    helicopterOppg4_B.FrontmotorSaturation =
      helicopterOppg4_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S5>/Front motor: Saturation' */
    helicopterOppg4_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S5>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterOppg4_M)) {
    /* S-Function (hil_write_analog_block): '<S5>/HIL Write Analog' */

    /* S-Function Block: helicopterOppg4/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopterOppg4_DW.HILWriteAnalog_Buffer[0] =
        helicopterOppg4_B.FrontmotorSaturation;
      helicopterOppg4_DW.HILWriteAnalog_Buffer[1] =
        helicopterOppg4_B.BackmotorSaturation;
      result = hil_write_analog(helicopterOppg4_DW.HILInitialize_Card,
        helicopterOppg4_P.HILWriteAnalog_channels, 2,
        &helicopterOppg4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopterOppg4_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S5>/Derivative' */
  if (helicopterOppg4_DW.TimeStampA == (rtInf)) {
    helicopterOppg4_DW.TimeStampA = helicopterOppg4_M->Timing.t[0];
    lastU = &helicopterOppg4_DW.LastUAtTimeA;
  } else if (helicopterOppg4_DW.TimeStampB == (rtInf)) {
    helicopterOppg4_DW.TimeStampB = helicopterOppg4_M->Timing.t[0];
    lastU = &helicopterOppg4_DW.LastUAtTimeB;
  } else if (helicopterOppg4_DW.TimeStampA < helicopterOppg4_DW.TimeStampB) {
    helicopterOppg4_DW.TimeStampA = helicopterOppg4_M->Timing.t[0];
    lastU = &helicopterOppg4_DW.LastUAtTimeA;
  } else {
    helicopterOppg4_DW.TimeStampB = helicopterOppg4_M->Timing.t[0];
    lastU = &helicopterOppg4_DW.LastUAtTimeB;
  }

  *lastU = helicopterOppg4_B.PitchCounttorad;

  /* End of Update for Derivative: '<S5>/Derivative' */
  if (rtmIsMajorTimeStep(helicopterOppg4_M)) {
    rt_ertODEUpdateContinuousStates(&helicopterOppg4_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helicopterOppg4_M->Timing.clockTick0)) {
    ++helicopterOppg4_M->Timing.clockTickH0;
  }

  helicopterOppg4_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopterOppg4_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopterOppg4_M->Timing.clockTick1)) {
      ++helicopterOppg4_M->Timing.clockTickH1;
    }

    helicopterOppg4_M->Timing.t[1] = helicopterOppg4_M->Timing.clockTick1 *
      helicopterOppg4_M->Timing.stepSize1 +
      helicopterOppg4_M->Timing.clockTickH1 *
      helicopterOppg4_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopterOppg4_derivatives(void)
{
  XDot_helicopterOppg4_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopterOppg4_T *) helicopterOppg4_M->derivs);

  /* Derivatives for TransferFcn: '<S5>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterOppg4_P.TravelTransferFcn_A *
    helicopterOppg4_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterOppg4_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterOppg4_P.PitchTransferFcn_A *
    helicopterOppg4_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterOppg4_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopterOppg4_P.ElevationTransferFcn_A *
    helicopterOppg4_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterOppg4_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopterOppg4_X.Integrator_CSTATE <=
          helicopterOppg4_P.Integrator_LowerSat);
  usat = (helicopterOppg4_X.Integrator_CSTATE >=
          helicopterOppg4_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopterOppg4_B.In1 > 0.0)) || (usat &&
       (helicopterOppg4_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopterOppg4_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopterOppg4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterOppg4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopterOppg4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopterOppg4_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopterOppg4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
      return;
    }

    if ((helicopterOppg4_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopterOppg4_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopterOppg4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopterOppg4_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopterOppg4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopterOppg4_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopterOppg4_DW.HILInitialize_Card,
        helicopterOppg4_P.HILInitialize_AIChannels, 8U,
        &helicopterOppg4_DW.HILInitialize_AIMinimums[0],
        &helicopterOppg4_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg4_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopterOppg4_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopterOppg4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopterOppg4_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopterOppg4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopterOppg4_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopterOppg4_DW.HILInitialize_Card,
         helicopterOppg4_P.HILInitialize_AOChannels, 8U,
         &helicopterOppg4_DW.HILInitialize_AOMinimums[0],
         &helicopterOppg4_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg4_P.HILInitialize_AOStart && !is_switching) ||
        (helicopterOppg4_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterOppg4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterOppg4_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopterOppg4_DW.HILInitialize_Card,
        helicopterOppg4_P.HILInitialize_AOChannels, 8U,
        &helicopterOppg4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }
    }

    if (helicopterOppg4_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterOppg4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterOppg4_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopterOppg4_DW.HILInitialize_Card,
         helicopterOppg4_P.HILInitialize_AOChannels, 8U,
         &helicopterOppg4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg4_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopterOppg4_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopterOppg4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopterOppg4_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopterOppg4_DW.HILInitialize_Card,
         helicopterOppg4_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopterOppg4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg4_P.HILInitialize_EIStart && !is_switching) ||
        (helicopterOppg4_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopterOppg4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopterOppg4_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopterOppg4_DW.HILInitialize_Card,
        helicopterOppg4_P.HILInitialize_EIChannels, 8U,
        &helicopterOppg4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg4_P.HILInitialize_POPStart && !is_switching) ||
        (helicopterOppg4_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopterOppg4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterOppg4_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopterOppg4_DW.HILInitialize_Card,
        helicopterOppg4_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopterOppg4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopterOppg4_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &helicopterOppg4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopterOppg4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopterOppg4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopterOppg4_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopterOppg4_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            helicopterOppg4_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = helicopterOppg4_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopterOppg4_DW.HILInitialize_Card,
          &helicopterOppg4_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopterOppg4_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopterOppg4_DW.HILInitialize_Card,
          &helicopterOppg4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopterOppg4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopterOppg4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterOppg4_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopterOppg4_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopterOppg4_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopterOppg4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopterOppg4_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopterOppg4_DW.HILInitialize_Card,
        helicopterOppg4_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopterOppg4_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopterOppg4_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopterOppg4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopterOppg4_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopterOppg4_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopterOppg4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterOppg4_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopterOppg4_DW.HILInitialize_Card,
        helicopterOppg4_P.HILInitialize_POChannels, 8U,
        &helicopterOppg4_DW.HILInitialize_POSortedFreqs[0],
        &helicopterOppg4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg4_P.HILInitialize_POStart && !is_switching) ||
        (helicopterOppg4_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterOppg4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterOppg4_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopterOppg4_DW.HILInitialize_Card,
        helicopterOppg4_P.HILInitialize_POChannels, 8U,
        &helicopterOppg4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }
    }

    if (helicopterOppg4_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterOppg4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterOppg4_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopterOppg4_DW.HILInitialize_Card,
         helicopterOppg4_P.HILInitialize_POChannels, 8U,
         &helicopterOppg4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S5>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopterOppg4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopterOppg4_DW.HILInitialize_Card,
       helicopterOppg4_P.HILReadEncoderTimebase_SamplesI,
       helicopterOppg4_P.HILReadEncoderTimebase_Channels, 3,
       &helicopterOppg4_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopterOppg4_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopterOppg4_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "travel_10_opt.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterOppg4_M,
                        "Error creating .mat file travel_10_opt.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterOppg4_M,
                        "Error writing mat file header to file travel_10_opt.mat");
      return;
    }

    helicopterOppg4_DW.ToFile_IWORK.Count = 0;
    helicopterOppg4_DW.ToFile_IWORK.Decimation = -1;
    helicopterOppg4_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitch_10_opt.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterOppg4_M,
                        "Error creating .mat file pitch_10_opt.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterOppg4_M,
                        "Error writing mat file header to file pitch_10_opt.mat");
      return;
    }

    helicopterOppg4_DW.ToFile1_IWORK.Count = 0;
    helicopterOppg4_DW.ToFile1_IWORK.Decimation = -1;
    helicopterOppg4_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "elevation_10_opt.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterOppg4_M,
                        "Error creating .mat file elevation_10_opt.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterOppg4_M,
                        "Error writing mat file header to file elevation_10_opt.mat");
      return;
    }

    helicopterOppg4_DW.ToFile2_IWORK.Count = 0;
    helicopterOppg4_DW.ToFile2_IWORK.Decimation = -1;
    helicopterOppg4_DW.ToFile2_PWORK.FilePtr = fp;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.4, 0.4, 0.4, 0.4,
      0.4, 0.4, 0.4, 0.38823924898995288, 0.39398373782260843,
      0.39999999999999991, 0.4, 0.31702964449498316, -0.37071929347853855,
      -0.32031659918726557, 0.13308786357963651, 0.0992662438540574,
      -1.6000217335207097E-15, 9.8620278210122019E-16, 2.6144394468138677E-16,
      9.4344770861116541E-16, -2.1403455681780482E-15, -0.23414443209209018,
      -0.4, -0.4, -0.4, -0.4, -0.4, -0.4, -0.39947132287497605,
      -0.33583325401002234, -0.25716578657815631, -0.18512631129019486,
      -0.12331321631313931, -0.07401212825913378, -0.0381578851398658,
      -0.015346433704270692, -0.0037162607794328549, 7.1385523304836726E-7,
      -1.7621928407047286E-6, 6.1090163289709592E-7, 6.1090163289709592E-7, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.097442362618052128,
      0.1124058281655748, 0.12876524867906239, 0.14627019122178694,
      0.16448817982185482, 0.1826729144201957, 0.19966211421091978,
      0.21373894806293095, 0.22237061801182853, 0.23573092003829124,
      0.25073092003829123, 0.26573092003829124, 0.28073092003829125,
      0.2848669971607059, 0.2372539162247124, 0.14802143352772207,
      -0.00065427894381653708, 0.010390783901399438, 0.026986244989086906,
      0.0512406818495099, 0.042229410094735395, 0.029729410094735387,
      0.017229410094735376, 0.0047294100947353687, 1.9751195294542582E-6,
      2.4678353953150896E-6, 3.7806082654108377E-6, -3.4667474926751375E-7,
      4.6124299676569664E-7, 2.5350347873151017E-6, 5.3224729874687925E-7,
      1.3742251487780056E-7, 3.4378258941969932E-6, 2.3843765130160134E-6,
      -5.6024939278513238E-8, -9.4676360140598414E-7, 2.7876989763802891E-6,
      -1.987913070022256E-6, -2.0232177964831558E-6, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0 } ;

    helicopterOppg4_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterOppg4_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopterOppg4_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1387274733013317, 3.1295875481811395,
      3.1112400796859472, 3.0815332916324976, 3.0390576937909479,
      2.9829805649397136, 2.9128641917403222, 2.8285987800793921,
      2.7301843299569239, 2.6176208413729172, 2.4909083143273718,
      2.350641061388087, 2.2024526262619739, 2.052452626261974,
      1.9024526262619743, 1.7524526262619744, 1.6024526262619745,
      1.4524526262619746, 1.3024526262619747, 1.1524526262619748,
      1.0024526262619748, 0.85412979129068289, 0.71066796299201551,
      0.57519762564846444, 0.45019439771095854, 0.33737555005522474,
      0.23781295478138836, 0.15210811086987611, 0.080552305419902312,
      0.022800245378445612, -0.022236789366603477, -0.05623486343680982,
      -0.081203935241075276, -0.099231141186258989, -0.11226808709763687,
      -0.12198138017010632, -0.12967158403471341, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.011460721153846158,
      -0.036559700480769237, -0.073389873980769238, -0.1188271522137981,
      -0.16990239136619859, -0.22430851540493749, -0.28046549279756572,
      -0.33706164664371957, -0.39365780048987342, -0.45025395433602727,
      -0.50685010818218112, -0.56106901175713875, -0.592753740504452, -0.6, -0.6,
      -0.6, -0.6, -0.6, -0.6, -0.6, -0.6, -0.59329133988516725,
      -0.57384731319467, -0.541881349374204, -0.50001291175002349,
      -0.45127539062293548, -0.39825038109534538, -0.34281937564604903,
      -0.28622322179989518, -0.23100824016582677, -0.18014813898019635,
      -0.13599229628082538, -0.099876287217061863, -0.072108823780734826,
      -0.052147783645511585, -0.038853172289877724, -0.0307608154584284,
      -0.026349066239329432, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.081000000000000016, 0.17739000000000002, 0.2603016,
      0.321133329, 0.36098028351, 0.3845217057444, 0.39689606855816095, 0.4, 0.4,
      0.4, 0.4, 0.38319850301023411, 0.22393556165277451, 0.051213794599863485,
      -3.5733602628824353E-17, 1.7189452445028976E-16, -1.0542424693203501E-16,
      6.7825212147156106E-18, 1.0239286912367286E-16, 3.1023349814631465E-16,
      -1.0443129229697789E-16, -0.047414247498648511, -0.1374229545233917,
      -0.22592322373961657, -0.2959101265997125, -0.34445818533585837,
      -0.37476051585928433, -0.39176517612822392, -0.4, -0.39023840230670165,
      -0.35945977052705164, -0.31207663205807551, -0.25525415852065275,
      -0.19624982652925674, -0.14107700809128212, -0.093961235541007271,
      -0.057193687425805578, -0.031180558531178595, -0.014656699181524081, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.32400000000000007,
      0.38556, 0.33164639999999995, 0.24332691599999995, 0.15938781803999993,
      0.094165688937599953, 0.049497451255043935, 0.012415725767356179,
      1.0057363517748203E-16, -2.8447046120577083E-17, -6.9503456358090956E-18,
      -0.067205987959063657, -0.63705176542983843, -0.690887068211644,
      -0.20485517839945408, 8.3051266837881133E-16, -1.109275809620604E-15,
      4.4882744025013074E-16, 3.8244061969280883E-16, 8.3136239516056221E-16,
      -1.6586592327470601E-15, -0.18965698999459363, -0.36003482809897275,
      -0.35400107686489957, -0.27994761144038366, -0.19419223494458346,
      -0.12120932209370376, -0.06801864107575846, -0.032939295487104413,
      0.039046390773193412, 0.12311452711860017, 0.18953255387590459,
      0.22728989414969086, 0.23601732796558408, 0.22069127375189843,
      0.18846309020109939, 0.1470701924608068, 0.10405251557850795,
      0.066095437398618048, 0.037814880346314729, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0038976945047220859, 0.010732544334178331,
      0.019828156398825691, 0.030707029513118451, 0.043020754318615267,
      0.056487624598196458, 0.070833401161637347, 0.085730920038291261,
      0.10073092003829126, 0.11573092003829126, 0.13073092003829126,
      0.14573092003829127, 0.16073092003829129, 0.17529636312318786,
      0.18709654882158266, 0.19308566305680092, 0.18916909848731589,
      0.17951136457940881, 0.16722941009473541, 0.1547294100947354,
      0.14222941009473539, 0.12972941009473538, 0.11722941009473536,
      0.10472941009473537, 0.092540312695727128, 0.081037776565948585,
      0.07043479360458299, 0.06083147889813572, 0.0522521167798039,
      0.044671341754270878, 0.038032813357650859, 0.032262848146408611,
      0.027279693998392991, 0.022999382958787794, 0.019340006334091383,
      0.016224367170377972, 0.013581494926745324, 0.011346717377227814,
      0.0094625101217356358, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.015590778018888344, 0.027339399317824978, 0.036382448258589439,
      0.04351549245717104, 0.049254899221987287, 0.053867481118324741,
      0.057383106253763569, 0.059590075506615665, 0.06, 0.06, 0.06, 0.06, 0.06,
      0.058261772339586342, 0.047200742793579185, 0.023956456940872981,
      -0.015666258277940086, -0.038630935631628296, -0.04912781793869362, -0.05,
      -0.05, -0.05, -0.05, -0.05, -0.048756389596032949, -0.046010144519114178,
      -0.042411931845462381, -0.038413258825789089, -0.034317448473327253,
      -0.030323100102132097, -0.026554113586480084, -0.023079860844969009,
      -0.019932616592062476, -0.017121244158420781, -0.014637506498785632,
      -0.012462556654853652, -0.010571488974530594, -0.0089391101980700362,
      -0.0075368290219687108, -0.0063375721935376769, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    } ;

    helicopterOppg4_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterOppg4_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopterOppg4_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopterOppg4_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S5>/Travel: Transfer Fcn' */
  helicopterOppg4_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Pitch: Transfer Fcn' */
  helicopterOppg4_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S5>/Elevation: Transfer Fcn' */
  helicopterOppg4_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopterOppg4_X.Integrator_CSTATE = helicopterOppg4_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S5>/Derivative' */
  helicopterOppg4_DW.TimeStampA = (rtInf);
  helicopterOppg4_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopterOppg4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterOppg4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopterOppg4_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopterOppg4_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopterOppg4_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopterOppg4_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterOppg4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterOppg4_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopterOppg4_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopterOppg4_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterOppg4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterOppg4_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopterOppg4_DW.HILInitialize_Card
                         , helicopterOppg4_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopterOppg4_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopterOppg4_DW.HILInitialize_AOVoltages[0]
                         , &helicopterOppg4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopterOppg4_DW.HILInitialize_Card,
            helicopterOppg4_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopterOppg4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopterOppg4_DW.HILInitialize_Card,
            helicopterOppg4_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopterOppg4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterOppg4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopterOppg4_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopterOppg4_DW.HILInitialize_Card);
    hil_close(helicopterOppg4_DW.HILInitialize_Card);
    helicopterOppg4_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopterOppg4_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "travel_10_opt.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error closing MAT-file travel_10_opt.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error reopening MAT-file travel_10_opt.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           helicopterOppg4_DW.ToFile_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error writing header for ans to MAT-file travel_10_opt.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error closing MAT-file travel_10_opt.mat");
        return;
      }

      helicopterOppg4_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) helicopterOppg4_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch_10_opt.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error closing MAT-file pitch_10_opt.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error reopening MAT-file pitch_10_opt.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           helicopterOppg4_DW.ToFile1_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error writing header for ans to MAT-file pitch_10_opt.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error closing MAT-file pitch_10_opt.mat");
        return;
      }

      helicopterOppg4_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (FILE *) helicopterOppg4_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elevation_10_opt.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error closing MAT-file elevation_10_opt.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error reopening MAT-file elevation_10_opt.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           helicopterOppg4_DW.ToFile2_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error writing header for ans to MAT-file elevation_10_opt.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg4_M,
                          "Error closing MAT-file elevation_10_opt.mat");
        return;
      }

      helicopterOppg4_DW.ToFile2_PWORK.FilePtr = (NULL);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopterOppg4_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopterOppg4_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopterOppg4_initialize();
}

void MdlTerminate(void)
{
  helicopterOppg4_terminate();
}

/* Registration function */
RT_MODEL_helicopterOppg4_T *helicopterOppg4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopterOppg4_P.Integrator_UpperSat = rtInf;
  helicopterOppg4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopterOppg4_M, 0,
                sizeof(RT_MODEL_helicopterOppg4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopterOppg4_M->solverInfo,
                          &helicopterOppg4_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopterOppg4_M->solverInfo, &rtmGetTPtr(helicopterOppg4_M));
    rtsiSetStepSizePtr(&helicopterOppg4_M->solverInfo,
                       &helicopterOppg4_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopterOppg4_M->solverInfo, &helicopterOppg4_M->derivs);
    rtsiSetContStatesPtr(&helicopterOppg4_M->solverInfo, (real_T **)
                         &helicopterOppg4_M->contStates);
    rtsiSetNumContStatesPtr(&helicopterOppg4_M->solverInfo,
      &helicopterOppg4_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopterOppg4_M->solverInfo,
      &helicopterOppg4_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopterOppg4_M->solverInfo,
      &helicopterOppg4_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopterOppg4_M->solverInfo,
      &helicopterOppg4_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopterOppg4_M->solverInfo, (&rtmGetErrorStatus
      (helicopterOppg4_M)));
    rtsiSetRTModelPtr(&helicopterOppg4_M->solverInfo, helicopterOppg4_M);
  }

  rtsiSetSimTimeStep(&helicopterOppg4_M->solverInfo, MAJOR_TIME_STEP);
  helicopterOppg4_M->intgData.f[0] = helicopterOppg4_M->odeF[0];
  helicopterOppg4_M->contStates = ((real_T *) &helicopterOppg4_X);
  rtsiSetSolverData(&helicopterOppg4_M->solverInfo, (void *)
                    &helicopterOppg4_M->intgData);
  rtsiSetSolverName(&helicopterOppg4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopterOppg4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopterOppg4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopterOppg4_M->Timing.sampleTimes =
      (&helicopterOppg4_M->Timing.sampleTimesArray[0]);
    helicopterOppg4_M->Timing.offsetTimes =
      (&helicopterOppg4_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopterOppg4_M->Timing.sampleTimes[0] = (0.0);
    helicopterOppg4_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopterOppg4_M->Timing.offsetTimes[0] = (0.0);
    helicopterOppg4_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopterOppg4_M, &helicopterOppg4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopterOppg4_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopterOppg4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopterOppg4_M, -1);
  helicopterOppg4_M->Timing.stepSize0 = 0.002;
  helicopterOppg4_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopterOppg4_M->Sizes.checksums[0] = (1743506850U);
  helicopterOppg4_M->Sizes.checksums[1] = (951465521U);
  helicopterOppg4_M->Sizes.checksums[2] = (4101425626U);
  helicopterOppg4_M->Sizes.checksums[3] = (3326815249U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopterOppg4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &helicopterOppg4_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopterOppg4_M->extModeInfo,
      &helicopterOppg4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopterOppg4_M->extModeInfo,
                        helicopterOppg4_M->Sizes.checksums);
    rteiSetTPtr(helicopterOppg4_M->extModeInfo, rtmGetTPtr(helicopterOppg4_M));
  }

  helicopterOppg4_M->solverInfoPtr = (&helicopterOppg4_M->solverInfo);
  helicopterOppg4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopterOppg4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopterOppg4_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopterOppg4_M->blockIO = ((void *) &helicopterOppg4_B);

  {
    helicopterOppg4_B.TravelCounttorad = 0.0;
    helicopterOppg4_B.Gain = 0.0;
    helicopterOppg4_B.Sum3 = 0.0;
    helicopterOppg4_B.PitchCounttorad = 0.0;
    helicopterOppg4_B.Gain_i = 0.0;
    helicopterOppg4_B.ElevationCounttorad = 0.0;
    helicopterOppg4_B.Gain_e = 0.0;
    helicopterOppg4_B.Sum = 0.0;
    helicopterOppg4_B.Gain_d = 0.0;
    helicopterOppg4_B.Gain_b = 0.0;
    helicopterOppg4_B.Gain_dg = 0.0;
    helicopterOppg4_B.Gain_l = 0.0;
    helicopterOppg4_B.BackmotorSaturation = 0.0;
    helicopterOppg4_B.FrontmotorSaturation = 0.0;
    helicopterOppg4_B.In1 = 0.0;
  }

  /* parameters */
  helicopterOppg4_M->defaultParam = ((real_T *)&helicopterOppg4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopterOppg4_X;
    helicopterOppg4_M->contStates = (x);
    (void) memset((void *)&helicopterOppg4_X, 0,
                  sizeof(X_helicopterOppg4_T));
  }

  /* states (dwork) */
  helicopterOppg4_M->dwork = ((void *) &helicopterOppg4_DW);
  (void) memset((void *)&helicopterOppg4_DW, 0,
                sizeof(DW_helicopterOppg4_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopterOppg4_DW.TimeStampA = 0.0;
  helicopterOppg4_DW.LastUAtTimeA = 0.0;
  helicopterOppg4_DW.TimeStampB = 0.0;
  helicopterOppg4_DW.LastUAtTimeB = 0.0;
  helicopterOppg4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopterOppg4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopterOppg4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopterOppg4_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopterOppg4_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopterOppg4_M->Sizes.numY = (0); /* Number of model outputs */
  helicopterOppg4_M->Sizes.numU = (0); /* Number of model inputs */
  helicopterOppg4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopterOppg4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopterOppg4_M->Sizes.numBlocks = (65);/* Number of blocks */
  helicopterOppg4_M->Sizes.numBlockIO = (15);/* Number of block outputs */
  helicopterOppg4_M->Sizes.numBlockPrms = (156);/* Sum of parameter "widths" */
  return helicopterOppg4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
