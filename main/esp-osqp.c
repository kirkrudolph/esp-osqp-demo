#include "stdio.h"
#include <string.h>
#include "esp_timer.h"

#include "workspace.h"
#include "osqp.h"

void app_main(void)
{
    const unsigned MEASUREMENTS = 10;
    uint64_t start = esp_timer_get_time();

    for (int retries = 0; retries < MEASUREMENTS; retries++) {
      // Solve Problem
      osqp_solve(&workspace); // This is the thing you need to measure
    }

    uint64_t end = esp_timer_get_time();

    // Print status
    printf("Status:                %s\n", (&workspace)->info->status);
    printf("Number of iterations:  %d\n", (int)((&workspace)->info->iter));
    printf("Objective value:       %.4e\n", (&workspace)->info->obj_val);
    printf("Primal residual:       %.4e\n", (&workspace)->info->pri_res);
    printf("Dual residual:         %.4e\n", (&workspace)->info->dua_res);

    printf("%u iterations took %llu seconds (%llu ms per invocation)\n",
           MEASUREMENTS, (end - start)/1000/1000, (end - start)/1000/MEASUREMENTS);

}
