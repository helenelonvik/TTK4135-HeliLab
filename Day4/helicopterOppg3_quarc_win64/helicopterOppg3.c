/*
 * helicopterOppg3.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterOppg3".
 *
 * Model version              : 11.7
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Mon Mar 22 10:15:08 2021
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopterOppg3.h"
#include "helicopterOppg3_private.h"
#include "helicopterOppg3_dt.h"

/* Block signals (default storage) */
B_helicopterOppg3_T helicopterOppg3_B;

/* Continuous states */
X_helicopterOppg3_T helicopterOppg3_X;

/* Block states (default storage) */
DW_helicopterOppg3_T helicopterOppg3_DW;

/* Real-time model */
static RT_MODEL_helicopterOppg3_T helicopterOppg3_M_;
RT_MODEL_helicopterOppg3_T *const helicopterOppg3_M = &helicopterOppg3_M_;

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
  helicopterOppg3_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopterOppg3_output(void)
{
  /* local block i/o variables */
  real_T rtb_FromWorkspace[2];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T lastTime;
  real_T rtb_Backgain;
  real_T rtb_Clock;
  real_T rtb_Derivative;
  real_T *lastU;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopterOppg3_M)) {
    /* set solver stop time */
    if (!(helicopterOppg3_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopterOppg3_M->solverInfo,
                            ((helicopterOppg3_M->Timing.clockTickH0 + 1) *
        helicopterOppg3_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopterOppg3_M->solverInfo,
                            ((helicopterOppg3_M->Timing.clockTick0 + 1) *
        helicopterOppg3_M->Timing.stepSize0 +
        helicopterOppg3_M->Timing.clockTickH0 *
        helicopterOppg3_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopterOppg3_M)) {
    helicopterOppg3_M->Timing.t[0] = rtsiGetT(&helicopterOppg3_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopterOppg3_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopterOppg3_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopterOppg3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (helicopterOppg3_DW.HILReadEncoderTimebase_Task, 1,
         &helicopterOppg3_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopterOppg3_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopterOppg3_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopterOppg3_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopterOppg3_B.TravelCounttorad = helicopterOppg3_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopterOppg3_P.TravelCounttorad_Gain;

    /* Gain: '<S12>/Gain' */
    helicopterOppg3_B.Gain = helicopterOppg3_P.Gain_Gain *
      helicopterOppg3_B.TravelCounttorad;

    /* ToFile: '<Root>/To File' */
    {
      if (!(++helicopterOppg3_DW.ToFile_IWORK.Decimation % 1) &&
          (helicopterOppg3_DW.ToFile_IWORK.Count * (1 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterOppg3_DW.ToFile_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[1 + 1];
          helicopterOppg3_DW.ToFile_IWORK.Decimation = 0;
          u[0] = helicopterOppg3_M->Timing.t[1];
          u[1] = helicopterOppg3_B.Gain;
          if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
            rtmSetErrorStatus(helicopterOppg3_M,
                              "Error writing to MAT-file travel_10_4_3.mat");
            return;
          }

          if (((++helicopterOppg3_DW.ToFile_IWORK.Count) * (1 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file travel_10_4_3.mat.\n");
          }
        }
      }
    }

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopterOppg3_B.PitchCounttorad = helicopterOppg3_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S9>/Gain' */
    helicopterOppg3_B.Gain_i = helicopterOppg3_P.Gain_Gain_a *
      helicopterOppg3_B.PitchCounttorad;

    /* ToFile: '<Root>/To File1' */
    {
      if (!(++helicopterOppg3_DW.ToFile1_IWORK.Decimation % 1) &&
          (helicopterOppg3_DW.ToFile1_IWORK.Count * (1 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterOppg3_DW.ToFile1_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[1 + 1];
          helicopterOppg3_DW.ToFile1_IWORK.Decimation = 0;
          u[0] = helicopterOppg3_M->Timing.t[1];
          u[1] = helicopterOppg3_B.Gain_i;
          if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
            rtmSetErrorStatus(helicopterOppg3_M,
                              "Error writing to MAT-file pitch_10_4_3.mat");
            return;
          }

          if (((++helicopterOppg3_DW.ToFile1_IWORK.Count) * (1 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file pitch_10_4_3.mat.\n");
          }
        }
      }
    }

    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopterOppg3_B.ElevationCounttorad = helicopterOppg3_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopterOppg3_P.ElevationCounttorad_Gain;

    /* Gain: '<S7>/Gain' */
    helicopterOppg3_B.Gain_e = helicopterOppg3_P.Gain_Gain_l *
      helicopterOppg3_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopterOppg3_B.Sum = helicopterOppg3_B.Gain_e +
      helicopterOppg3_P.elavation_offsetdeg_Value;

    /* ToFile: '<Root>/To File2' */
    {
      if (!(++helicopterOppg3_DW.ToFile2_IWORK.Decimation % 1) &&
          (helicopterOppg3_DW.ToFile2_IWORK.Count * (1 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterOppg3_DW.ToFile2_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[1 + 1];
          helicopterOppg3_DW.ToFile2_IWORK.Decimation = 0;
          u[0] = helicopterOppg3_M->Timing.t[1];
          u[1] = helicopterOppg3_B.Sum;
          if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
            rtmSetErrorStatus(helicopterOppg3_M,
                              "Error writing to MAT-file elevation_10_4_3.mat");
            return;
          }

          if (((++helicopterOppg3_DW.ToFile2_IWORK.Count) * (1 + 1))+1 >=
              100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file elevation_10_4_3.mat.\n");
          }
        }
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      helicopterOppg3_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopterOppg3_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopterOppg3_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopterOppg3_M->Timing.t[0];

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

    helicopterOppg3_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_FromWorkspace[0])[elIdx] = pDataValues[currTimeIndex + 1];
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
            (&rtb_FromWorkspace[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  /* Gain: '<S13>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopterOppg3_B.Gain_d = (helicopterOppg3_P.TravelTransferFcn_C *
    helicopterOppg3_X.TravelTransferFcn_CSTATE +
    helicopterOppg3_P.TravelTransferFcn_D * helicopterOppg3_B.TravelCounttorad) *
    helicopterOppg3_P.Gain_Gain_lu;

  /* Gain: '<S10>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopterOppg3_B.Gain_b = (helicopterOppg3_P.PitchTransferFcn_C *
    helicopterOppg3_X.PitchTransferFcn_CSTATE +
    helicopterOppg3_P.PitchTransferFcn_D * helicopterOppg3_B.PitchCounttorad) *
    helicopterOppg3_P.Gain_Gain_ae;

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopterOppg3_B.Gain_dg = (helicopterOppg3_P.ElevationTransferFcn_C *
    helicopterOppg3_X.ElevationTransferFcn_CSTATE +
    helicopterOppg3_P.ElevationTransferFcn_D *
    helicopterOppg3_B.ElevationCounttorad) * helicopterOppg3_P.Gain_Gain_n;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Clock = ((rtb_FromWorkspace[0] - helicopterOppg3_P.Gain1_Gain *
                helicopterOppg3_B.Gain_i) * helicopterOppg3_P.K_pp -
               helicopterOppg3_P.Gain1_Gain * helicopterOppg3_B.Gain_b *
               helicopterOppg3_P.K_pd) + helicopterOppg3_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopterOppg3_X.Integrator_CSTATE >=
      helicopterOppg3_P.Integrator_UpperSat) {
    helicopterOppg3_X.Integrator_CSTATE = helicopterOppg3_P.Integrator_UpperSat;
  } else {
    if (helicopterOppg3_X.Integrator_CSTATE <=
        helicopterOppg3_P.Integrator_LowerSat) {
      helicopterOppg3_X.Integrator_CSTATE =
        helicopterOppg3_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Gain: '<S2>/Gain1'
   */
  rtb_Derivative = rtb_FromWorkspace[1] - helicopterOppg3_P.Gain1_Gain *
    helicopterOppg3_B.Sum;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopterOppg3_P.K_ep * rtb_Derivative +
                   helicopterOppg3_X.Integrator_CSTATE) -
                  helicopterOppg3_P.Gain1_Gain * helicopterOppg3_B.Gain_dg *
                  helicopterOppg3_P.K_ed) + helicopterOppg3_P.Vs_ff;

  /* If: '<S3>/If' incorporates:
   *  Clock: '<S3>/Clock'
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S6>/In1'
   */
  if (rtmIsMajorTimeStep(helicopterOppg3_M)) {
    rtAction = (int8_T)!(helicopterOppg3_M->Timing.t[0] >= 2.0);
    helicopterOppg3_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopterOppg3_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    helicopterOppg3_B.In1 = helicopterOppg3_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopterOppg3_M)) {
      srUpdateBC(helicopterOppg3_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopterOppg3_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  rtb_Derivative = helicopterOppg3_M->Timing.t[0];
  if ((helicopterOppg3_DW.TimeStampA >= rtb_Derivative) &&
      (helicopterOppg3_DW.TimeStampB >= rtb_Derivative)) {
    rtb_Derivative = 0.0;
  } else {
    lastTime = helicopterOppg3_DW.TimeStampA;
    lastU = &helicopterOppg3_DW.LastUAtTimeA;
    if (helicopterOppg3_DW.TimeStampA < helicopterOppg3_DW.TimeStampB) {
      if (helicopterOppg3_DW.TimeStampB < rtb_Derivative) {
        lastTime = helicopterOppg3_DW.TimeStampB;
        lastU = &helicopterOppg3_DW.LastUAtTimeB;
      }
    } else {
      if (helicopterOppg3_DW.TimeStampA >= rtb_Derivative) {
        lastTime = helicopterOppg3_DW.TimeStampB;
        lastU = &helicopterOppg3_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopterOppg3_B.PitchCounttorad - *lastU) /
      (rtb_Derivative - lastTime);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S11>/Gain' */
  helicopterOppg3_B.Gain_l = helicopterOppg3_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopterOppg3_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Derivative = (rtb_Backgain - rtb_Clock) * helicopterOppg3_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Derivative > helicopterOppg3_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterOppg3_B.BackmotorSaturation =
      helicopterOppg3_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopterOppg3_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterOppg3_B.BackmotorSaturation =
      helicopterOppg3_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterOppg3_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterOppg3_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (rtb_Clock + rtb_Backgain) * helicopterOppg3_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > helicopterOppg3_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterOppg3_B.FrontmotorSaturation =
      helicopterOppg3_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopterOppg3_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterOppg3_B.FrontmotorSaturation =
      helicopterOppg3_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterOppg3_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterOppg3_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopterOppg3/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopterOppg3_DW.HILWriteAnalog_Buffer[0] =
        helicopterOppg3_B.FrontmotorSaturation;
      helicopterOppg3_DW.HILWriteAnalog_Buffer[1] =
        helicopterOppg3_B.BackmotorSaturation;
      result = hil_write_analog(helicopterOppg3_DW.HILInitialize_Card,
        helicopterOppg3_P.HILWriteAnalog_channels, 2,
        &helicopterOppg3_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopterOppg3_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopterOppg3_DW.TimeStampA == (rtInf)) {
    helicopterOppg3_DW.TimeStampA = helicopterOppg3_M->Timing.t[0];
    lastU = &helicopterOppg3_DW.LastUAtTimeA;
  } else if (helicopterOppg3_DW.TimeStampB == (rtInf)) {
    helicopterOppg3_DW.TimeStampB = helicopterOppg3_M->Timing.t[0];
    lastU = &helicopterOppg3_DW.LastUAtTimeB;
  } else if (helicopterOppg3_DW.TimeStampA < helicopterOppg3_DW.TimeStampB) {
    helicopterOppg3_DW.TimeStampA = helicopterOppg3_M->Timing.t[0];
    lastU = &helicopterOppg3_DW.LastUAtTimeA;
  } else {
    helicopterOppg3_DW.TimeStampB = helicopterOppg3_M->Timing.t[0];
    lastU = &helicopterOppg3_DW.LastUAtTimeB;
  }

  *lastU = helicopterOppg3_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
  if (rtmIsMajorTimeStep(helicopterOppg3_M)) {
    rt_ertODEUpdateContinuousStates(&helicopterOppg3_M->solverInfo);
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
  if (!(++helicopterOppg3_M->Timing.clockTick0)) {
    ++helicopterOppg3_M->Timing.clockTickH0;
  }

  helicopterOppg3_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopterOppg3_M->solverInfo);

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
    if (!(++helicopterOppg3_M->Timing.clockTick1)) {
      ++helicopterOppg3_M->Timing.clockTickH1;
    }

    helicopterOppg3_M->Timing.t[1] = helicopterOppg3_M->Timing.clockTick1 *
      helicopterOppg3_M->Timing.stepSize1 +
      helicopterOppg3_M->Timing.clockTickH1 *
      helicopterOppg3_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopterOppg3_derivatives(void)
{
  XDot_helicopterOppg3_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopterOppg3_T *) helicopterOppg3_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterOppg3_P.TravelTransferFcn_A *
    helicopterOppg3_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterOppg3_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterOppg3_P.PitchTransferFcn_A *
    helicopterOppg3_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterOppg3_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    helicopterOppg3_P.ElevationTransferFcn_A *
    helicopterOppg3_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterOppg3_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopterOppg3_X.Integrator_CSTATE <=
          helicopterOppg3_P.Integrator_LowerSat);
  usat = (helicopterOppg3_X.Integrator_CSTATE >=
          helicopterOppg3_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopterOppg3_B.In1 > 0.0)) || (usat &&
       (helicopterOppg3_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopterOppg3_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopterOppg3_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterOppg3/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopterOppg3_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopterOppg3_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopterOppg3_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
      return;
    }

    if ((helicopterOppg3_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopterOppg3_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopterOppg3_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopterOppg3_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopterOppg3_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopterOppg3_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopterOppg3_DW.HILInitialize_Card,
        helicopterOppg3_P.HILInitialize_AIChannels, 8U,
        &helicopterOppg3_DW.HILInitialize_AIMinimums[0],
        &helicopterOppg3_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg3_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopterOppg3_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopterOppg3_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopterOppg3_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopterOppg3_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopterOppg3_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (helicopterOppg3_DW.HILInitialize_Card,
         helicopterOppg3_P.HILInitialize_AOChannels, 8U,
         &helicopterOppg3_DW.HILInitialize_AOMinimums[0],
         &helicopterOppg3_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg3_P.HILInitialize_AOStart && !is_switching) ||
        (helicopterOppg3_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterOppg3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterOppg3_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopterOppg3_DW.HILInitialize_Card,
        helicopterOppg3_P.HILInitialize_AOChannels, 8U,
        &helicopterOppg3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }
    }

    if (helicopterOppg3_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterOppg3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterOppg3_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopterOppg3_DW.HILInitialize_Card,
         helicopterOppg3_P.HILInitialize_AOChannels, 8U,
         &helicopterOppg3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg3_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopterOppg3_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopterOppg3_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopterOppg3_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopterOppg3_DW.HILInitialize_Card,
         helicopterOppg3_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &helicopterOppg3_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg3_P.HILInitialize_EIStart && !is_switching) ||
        (helicopterOppg3_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopterOppg3_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopterOppg3_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopterOppg3_DW.HILInitialize_Card,
        helicopterOppg3_P.HILInitialize_EIChannels, 8U,
        &helicopterOppg3_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg3_P.HILInitialize_POPStart && !is_switching) ||
        (helicopterOppg3_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopterOppg3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterOppg3_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopterOppg3_DW.HILInitialize_Card,
        helicopterOppg3_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopterOppg3_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopterOppg3_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &helicopterOppg3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopterOppg3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopterOppg3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = helicopterOppg3_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopterOppg3_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            helicopterOppg3_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = helicopterOppg3_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopterOppg3_DW.HILInitialize_Card,
          &helicopterOppg3_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &helicopterOppg3_DW.HILInitialize_POSortedFreqs
          [0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopterOppg3_DW.HILInitialize_Card,
          &helicopterOppg3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopterOppg3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &helicopterOppg3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterOppg3_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopterOppg3_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopterOppg3_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopterOppg3_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopterOppg3_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopterOppg3_DW.HILInitialize_Card,
        helicopterOppg3_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopterOppg3_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopterOppg3_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopterOppg3_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &helicopterOppg3_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopterOppg3_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopterOppg3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterOppg3_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopterOppg3_DW.HILInitialize_Card,
        helicopterOppg3_P.HILInitialize_POChannels, 8U,
        &helicopterOppg3_DW.HILInitialize_POSortedFreqs[0],
        &helicopterOppg3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterOppg3_P.HILInitialize_POStart && !is_switching) ||
        (helicopterOppg3_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterOppg3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterOppg3_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopterOppg3_DW.HILInitialize_Card,
        helicopterOppg3_P.HILInitialize_POChannels, 8U,
        &helicopterOppg3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }
    }

    if (helicopterOppg3_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterOppg3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterOppg3_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopterOppg3_DW.HILInitialize_Card,
         helicopterOppg3_P.HILInitialize_POChannels, 8U,
         &helicopterOppg3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopterOppg3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (helicopterOppg3_DW.HILInitialize_Card,
       helicopterOppg3_P.HILReadEncoderTimebase_SamplesI,
       helicopterOppg3_P.HILReadEncoderTimebase_Channels, 3,
       &helicopterOppg3_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopterOppg3_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopterOppg3_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "travel_10_4_3.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterOppg3_M,
                        "Error creating .mat file travel_10_4_3.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterOppg3_M,
                        "Error writing mat file header to file travel_10_4_3.mat");
      return;
    }

    helicopterOppg3_DW.ToFile_IWORK.Count = 0;
    helicopterOppg3_DW.ToFile_IWORK.Decimation = -1;
    helicopterOppg3_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitch_10_4_3.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterOppg3_M,
                        "Error creating .mat file pitch_10_4_3.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterOppg3_M,
                        "Error writing mat file header to file pitch_10_4_3.mat");
      return;
    }

    helicopterOppg3_DW.ToFile1_IWORK.Count = 0;
    helicopterOppg3_DW.ToFile1_IWORK.Decimation = -1;
    helicopterOppg3_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "elevation_10_4_3.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterOppg3_M,
                        "Error creating .mat file elevation_10_4_3.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterOppg3_M,
                        "Error writing mat file header to file elevation_10_4_3.mat");
      return;
    }

    helicopterOppg3_DW.ToFile2_IWORK.Count = 0;
    helicopterOppg3_DW.ToFile2_IWORK.Decimation = -1;
    helicopterOppg3_DW.ToFile2_PWORK.FilePtr = fp;
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

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829882,
      0.50820398852585569, 0.51572350682389734, 0.5235987755982987,
      0.52359877559829882, 0.52359877559829882, 0.52359877559829848,
      -0.11657231154271745, -0.52359877559829882, -0.52359877559829882,
      -0.52359877559829882, -0.52359877559829882, -0.52359877559829882,
      -0.52359877559829882, -0.52037385529711466, -0.48344203980440026,
      -0.52359877559829882, -0.52359877559829882, -0.52359877559829882,
      -0.5235987755982987, -0.40507215977083877, -0.29349130935540063,
      -0.20242060513774371, -0.1315002077842139, -0.07918384490161777,
      -0.043088338286051485, -0.020254387972701064, -0.007492653093191067,
      -0.0016438655667654319, 0.00016779637272473983, 0.00022714593822868544,
      5.6013694348453483E-6, 3.1976614239503157E-6, 1.5699994415126116E-6,
      1.5699994415126116E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.11421479148377538, 0.13256982457286456, 0.15296659850460612,
      0.17527346985997716, 0.19916839054700017, 0.22406543272859797,
      0.24896592353779148, 0.27230169025758977, 0.29175120956785722,
      0.30390795972703777, 0.303906840376833, 0.28491259749742176,
      0.23742634826071221, 0.14839208363874609, 4.1284055535472378E-6,
      4.0760996175646335E-6, -2.7453925377237765E-7, 9.1684035780193355E-7,
      -1.669876264493352E-6, 1.05276696319121E-6, -3.1362462929207353E-6,
      -3.7646087112102652E-6, -1.2779509314268871E-6, -5.0300059421889255E-6,
      -2.834738955848069E-6, -4.4173364656716138E-6, -2.5769013896278815E-6,
      -4.58812634403939E-6, -5.040707694681571E-6, -3.7856115697074E-6,
      -3.0493515732268943E-6, -1.8128491508057223E-6, -1.2388626346991606E-6,
      -1.0758640363491683E-6, 4.1519449166662662E-7, -3.5781283047709684E-6,
      2.7568838448252456E-6, -4.0063473837207758E-7, 3.5748455399272514E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopterOppg3_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterOppg3_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopterOppg3_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopterOppg3_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopterOppg3_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopterOppg3_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopterOppg3_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopterOppg3_X.Integrator_CSTATE = helicopterOppg3_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopterOppg3_DW.TimeStampA = (rtInf);
  helicopterOppg3_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void helicopterOppg3_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterOppg3/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopterOppg3_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopterOppg3_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopterOppg3_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopterOppg3_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterOppg3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterOppg3_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopterOppg3_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopterOppg3_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterOppg3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterOppg3_P.HILInitialize_POFinal;
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
      result = hil_write(helicopterOppg3_DW.HILInitialize_Card
                         , helicopterOppg3_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopterOppg3_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopterOppg3_DW.HILInitialize_AOVoltages[0]
                         , &helicopterOppg3_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopterOppg3_DW.HILInitialize_Card,
            helicopterOppg3_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopterOppg3_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopterOppg3_DW.HILInitialize_Card,
            helicopterOppg3_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopterOppg3_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterOppg3_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopterOppg3_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopterOppg3_DW.HILInitialize_Card);
    hil_close(helicopterOppg3_DW.HILInitialize_Card);
    helicopterOppg3_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) helicopterOppg3_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "travel_10_4_3.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error closing MAT-file travel_10_4_3.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error reopening MAT-file travel_10_4_3.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           helicopterOppg3_DW.ToFile_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error writing header for ans to MAT-file travel_10_4_3.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error closing MAT-file travel_10_4_3.mat");
        return;
      }

      helicopterOppg3_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) helicopterOppg3_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitch_10_4_3.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error closing MAT-file pitch_10_4_3.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error reopening MAT-file pitch_10_4_3.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           helicopterOppg3_DW.ToFile1_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error writing header for ans to MAT-file pitch_10_4_3.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error closing MAT-file pitch_10_4_3.mat");
        return;
      }

      helicopterOppg3_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File2' */
  {
    FILE *fp = (FILE *) helicopterOppg3_DW.ToFile2_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "elevation_10_4_3.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error closing MAT-file elevation_10_4_3.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error reopening MAT-file elevation_10_4_3.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           helicopterOppg3_DW.ToFile2_IWORK.Count, "ans")) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error writing header for ans to MAT-file elevation_10_4_3.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterOppg3_M,
                          "Error closing MAT-file elevation_10_4_3.mat");
        return;
      }

      helicopterOppg3_DW.ToFile2_PWORK.FilePtr = (NULL);
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
  helicopterOppg3_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopterOppg3_update();
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
  helicopterOppg3_initialize();
}

void MdlTerminate(void)
{
  helicopterOppg3_terminate();
}

/* Registration function */
RT_MODEL_helicopterOppg3_T *helicopterOppg3(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopterOppg3_P.Integrator_UpperSat = rtInf;
  helicopterOppg3_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopterOppg3_M, 0,
                sizeof(RT_MODEL_helicopterOppg3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopterOppg3_M->solverInfo,
                          &helicopterOppg3_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopterOppg3_M->solverInfo, &rtmGetTPtr(helicopterOppg3_M));
    rtsiSetStepSizePtr(&helicopterOppg3_M->solverInfo,
                       &helicopterOppg3_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopterOppg3_M->solverInfo, &helicopterOppg3_M->derivs);
    rtsiSetContStatesPtr(&helicopterOppg3_M->solverInfo, (real_T **)
                         &helicopterOppg3_M->contStates);
    rtsiSetNumContStatesPtr(&helicopterOppg3_M->solverInfo,
      &helicopterOppg3_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopterOppg3_M->solverInfo,
      &helicopterOppg3_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopterOppg3_M->solverInfo,
      &helicopterOppg3_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopterOppg3_M->solverInfo,
      &helicopterOppg3_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopterOppg3_M->solverInfo, (&rtmGetErrorStatus
      (helicopterOppg3_M)));
    rtsiSetRTModelPtr(&helicopterOppg3_M->solverInfo, helicopterOppg3_M);
  }

  rtsiSetSimTimeStep(&helicopterOppg3_M->solverInfo, MAJOR_TIME_STEP);
  helicopterOppg3_M->intgData.f[0] = helicopterOppg3_M->odeF[0];
  helicopterOppg3_M->contStates = ((real_T *) &helicopterOppg3_X);
  rtsiSetSolverData(&helicopterOppg3_M->solverInfo, (void *)
                    &helicopterOppg3_M->intgData);
  rtsiSetSolverName(&helicopterOppg3_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopterOppg3_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopterOppg3_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopterOppg3_M->Timing.sampleTimes =
      (&helicopterOppg3_M->Timing.sampleTimesArray[0]);
    helicopterOppg3_M->Timing.offsetTimes =
      (&helicopterOppg3_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopterOppg3_M->Timing.sampleTimes[0] = (0.0);
    helicopterOppg3_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopterOppg3_M->Timing.offsetTimes[0] = (0.0);
    helicopterOppg3_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopterOppg3_M, &helicopterOppg3_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopterOppg3_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopterOppg3_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopterOppg3_M, -1);
  helicopterOppg3_M->Timing.stepSize0 = 0.002;
  helicopterOppg3_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopterOppg3_M->Sizes.checksums[0] = (2485339873U);
  helicopterOppg3_M->Sizes.checksums[1] = (1472501910U);
  helicopterOppg3_M->Sizes.checksums[2] = (1012866546U);
  helicopterOppg3_M->Sizes.checksums[3] = (1588810612U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopterOppg3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &helicopterOppg3_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopterOppg3_M->extModeInfo,
      &helicopterOppg3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopterOppg3_M->extModeInfo,
                        helicopterOppg3_M->Sizes.checksums);
    rteiSetTPtr(helicopterOppg3_M->extModeInfo, rtmGetTPtr(helicopterOppg3_M));
  }

  helicopterOppg3_M->solverInfoPtr = (&helicopterOppg3_M->solverInfo);
  helicopterOppg3_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopterOppg3_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopterOppg3_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopterOppg3_M->blockIO = ((void *) &helicopterOppg3_B);

  {
    helicopterOppg3_B.TravelCounttorad = 0.0;
    helicopterOppg3_B.Gain = 0.0;
    helicopterOppg3_B.PitchCounttorad = 0.0;
    helicopterOppg3_B.Gain_i = 0.0;
    helicopterOppg3_B.ElevationCounttorad = 0.0;
    helicopterOppg3_B.Gain_e = 0.0;
    helicopterOppg3_B.Sum = 0.0;
    helicopterOppg3_B.Gain_d = 0.0;
    helicopterOppg3_B.Gain_b = 0.0;
    helicopterOppg3_B.Gain_dg = 0.0;
    helicopterOppg3_B.Gain_l = 0.0;
    helicopterOppg3_B.BackmotorSaturation = 0.0;
    helicopterOppg3_B.FrontmotorSaturation = 0.0;
    helicopterOppg3_B.In1 = 0.0;
  }

  /* parameters */
  helicopterOppg3_M->defaultParam = ((real_T *)&helicopterOppg3_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopterOppg3_X;
    helicopterOppg3_M->contStates = (x);
    (void) memset((void *)&helicopterOppg3_X, 0,
                  sizeof(X_helicopterOppg3_T));
  }

  /* states (dwork) */
  helicopterOppg3_M->dwork = ((void *) &helicopterOppg3_DW);
  (void) memset((void *)&helicopterOppg3_DW, 0,
                sizeof(DW_helicopterOppg3_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg3_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg3_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg3_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg3_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg3_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg3_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg3_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterOppg3_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopterOppg3_DW.TimeStampA = 0.0;
  helicopterOppg3_DW.LastUAtTimeA = 0.0;
  helicopterOppg3_DW.TimeStampB = 0.0;
  helicopterOppg3_DW.LastUAtTimeB = 0.0;
  helicopterOppg3_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopterOppg3_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopterOppg3_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopterOppg3_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopterOppg3_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopterOppg3_M->Sizes.numY = (0); /* Number of model outputs */
  helicopterOppg3_M->Sizes.numU = (0); /* Number of model inputs */
  helicopterOppg3_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopterOppg3_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopterOppg3_M->Sizes.numBlocks = (59);/* Number of blocks */
  helicopterOppg3_M->Sizes.numBlockIO = (14);/* Number of block outputs */
  helicopterOppg3_M->Sizes.numBlockPrms = (143);/* Sum of parameter "widths" */
  return helicopterOppg3_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
