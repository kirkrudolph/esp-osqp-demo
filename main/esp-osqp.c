#include "stdio.h"
#include <string.h>

#include "workspace.h"
#include "osqp.h"

void app_main(void)
{
    
    // Solve Problem
    osqp_solve(&workspace);

    // Print status
    printf("Status:                %s\n", (&workspace)->info->status);
    printf("Number of iterations:  %d\n", (int)((&workspace)->info->iter));
    printf("Objective value:       %.4e\n", (&workspace)->info->obj_val);
    printf("Primal residual:       %.4e\n", (&workspace)->info->pri_res);
    printf("Dual residual:         %.4e\n", (&workspace)->info->dua_res);


}
