#include <stdlib.h>
#include <string.h>
#include "cc_sort_dto.h"

void result_list_destroy(result_list* list);

cc_sort_dto* cc_sort_dto_create(result_list* results, bool success, const char* message) {
	cc_sort_dto* dto = (cc_sort_dto*)malloc(sizeof(cc_sort_dto));
	if (dto == NULL)
		return NULL;

	dto->result_data = results;
	dto->success = success;
	strcpy_s(dto->message, strlen(message) + 1, message);

	return dto;
}

void cc_sort_dto_destroy(cc_sort_dto* dto) {
	if (dto == NULL)
		return;

	result_list_destroy(dto->result_data);

	free(dto);
}
