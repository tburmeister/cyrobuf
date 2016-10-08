#include <stdio.h>
#include <stdlib.h>

#include "test_message_proto.h"

int main(int argc, char **argv)
{
	struct Test *test = Test_init();
    cyrobuf_int64_list_append(&test->list_fieldx, 5);
    cyrobuf_int64_list_append(&test->list_fieldx, 6);
    test->substruct = TestSs1_init();
    test->test_ref = TestRef_init();
    TestRef_list_append(&test->list_ref, TestRef_init());

    Test_print(test, 0);
    printf("\n");

	Test_destroy(test);

    uint8_t buffer[256];
    size_t offset = 0;

    set_varint64(123456789, buffer, &offset);
    printf("used %zd bytes setting varint\n", offset);

    offset = 0;
    int64_t value = get_varint64(buffer, &offset);
    printf("got value %lld; consumed %zd bytes\n", value, offset);

	return 0;
}
