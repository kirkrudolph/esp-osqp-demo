#include <stdio.h>
#include "osqp.h"
#include "cs.h"

int test(void) {
  // Load problem data
  c_float P_x[3] = { 4.0, 1.0, 2.0, };
  c_int   P_nnz  = 3;
  c_int   P_i[3] = { 0, 0, 1, };
  c_int   P_p[3] = { 0, 1, 3, };
  c_float q[2]   = { 1.0, 1.0, };
  c_float A_x[4] = { 1.0, 1.0, 1.0, 1.0, };
  c_int   A_nnz  = 4;
  c_int   A_i[4] = { 0, 1, 0, 2, };
  c_int   A_p[3] = { 0, 2, 4, };
  c_float l[3]   = { 1.0, 0.0, 0.0, };
  c_float u[3]   = { 1.0, 0.7, 0.7, };
  c_int n = 2;
  c_int m = 3;

  // Exitflag
  c_int exitflag = 0;

  // Workspace structures
  OSQPWorkspace *work     = (OSQPWorkspace *)malloc(sizeof(OSQPWorkspace));
  OSQPSettings  *settings = (OSQPSettings *)malloc(sizeof(OSQPSettings));
  OSQPData      *data     = (OSQPData *)malloc(sizeof(OSQPData));

  // Populate data
  if (data) {
    data->n = n;
    data->m = m;
//    data->P = csc_matrix(data->n, data->n, P_nnz, P_x, P_i, P_p);
    data->q = q;
//    data->A = csc_matrix(data->m, data->n, A_nnz, A_x, A_i, A_p);
    data->l = l;
    data->u = u;
  }

  // Define solver settings as default
  if (settings) osqp_set_default_settings(settings);

  // Setup workspace (only non-embedded)
  //exitflag = osqp_setup(&work, data, settings);

  // Solve Problem
  osqp_solve(work);

  // Clean workspace (only non-embedded)
  //osqp_cleanup(work);
  if (data) {
    if (data->A) free(data->A);
    if (data->P) free(data->P);
    free(data);
  }
  if (settings)  free(settings);

  return exitflag;
}

void app_main(void)
{
    printf("esp-osqp demo\n");
    int exitflag = test();
    printf("Exit Flag: %d", exitflag);
}
