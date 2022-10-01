#include "stdio.h"
#include <string.h>
#include "esp_timer.h"

#include "workspace.h"
#include "osqp.h"

void update_problem(void){

  // float l_new = ;
  // float u_new = ;

  //int osqp_update_bounds(&workspace,&l_new,&u_new);
}



void app_main(void)
{
    const unsigned MEASUREMENTS = 10;
    uint64_t start = esp_timer_get_time();

    // May steps
    for (int retries = 0; retries < MEASUREMENTS; retries++) {

      // Solve Problem
      int osqp_solve_exit_flag = osqp_solve(&workspace);

      // Error Handling
      if (osqp_solve_exit_flag){
        printf("OSQP Solve Error: %d\n",osqp_solve_exit_flag);
        return;
      }

    }
    
    uint64_t end = esp_timer_get_time();

    // Print status
    printf("Status:                %s\n", (&workspace)->info->status);
    printf("Number of iterations:  %d\n", (int)((&workspace)->info->iter));
    printf("Objective value:       %.4e\n", (&workspace)->info->obj_val);
    printf("Primal residual:       %.4e\n", (&workspace)->info->pri_res);
    printf("Dual residual:         %.4e\n", (&workspace)->info->dua_res);
    printf("Dual residual:         %.4e\n", (&workspace)->info->dua_res);
    printf("Variables:             %d\n", (&workspace)->data->n);
    printf("Variables:             %d\n", (&workspace)->data->n);
    printf("Constraints:           %d\n", (&workspace)->data->m);


    printf("%u iterations took %llu ms (%llu us per invocation)\n",
           MEASUREMENTS, (end - start)/1000, (end - start)/MEASUREMENTS);

}
