#ifndef __CC_SORT_DTO_H__
#define __CC_SORT_DTO_H__

#include <stdbool.h>

#include "../cc_types.h"

typedef struct CCSortDTO {

	result_list* result_data;
	bool success;
	char message[64];

} cc_sort_dto;


cc_sort_dto* cc_sort_dto_create(result_list* results, bool success, const char* message);

void cc_sort_dto_destroy(cc_sort_dto* dto);



#endif // !__CC_SORT_DTO_H__

