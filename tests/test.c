#include <stdio.h>
#include <stdlib.h>

#include "test_message_proto.h"

int main(int argc, char **argv)
{
	struct Test *test = Test_init();

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
