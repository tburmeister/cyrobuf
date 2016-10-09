#include <stdio.h>
#include <stdlib.h>

#include "test_message_proto.h"

static char *test_buffer =
    "\x08\x80\x89\x9a\x81\x02\x10\xc1S\x1a\tgo goats! \x00 d \xc8\x01 "
    "\xac\x02 \x90\x03*A\x08\xb9`\x12\x05hello\x1a\x12\tH\xe1z\x14\xae.\x96@\x12\x07goodbye!\xd7"
    "\xa3p=\n/v@*\r\tn\x86\x1b\xf0\xf9!\t@\x12\x02pi2\tsomething2\x17\x08\x80\x89\x9a\x81\x02\x10"
    "\xd7\x08\x19\x8d\x97n\x12\x83\xc0\xf3?\"\x03"
    "fooB\x17\x08\x80\x89\x9a\x81\x02\x10\xd7\x08\x19"
    "\x8d\x97n\x12\x83\xc0\xf3?\"\x03"
    "fooJ7\n\nwhat\'s up?\x12\x0cnothing much\x18\x18 W*\x17\x08"
    "\x80\x89\x9a\x81\x02\x10\xd7\x08\x19\x8d\x97n\x12\x83\xc0\xf3?\"\x03"
    "fooP\xee\x87\xfb\xff\xff"
    "\xff\xff\xff\xff\x01X\xff\xff\xff\xff\xff\xff\xff\xff\xff\x01";

static size_t buffer_size = 229;

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

    offset = 0;
    memcpy(buffer, test_buffer, buffer_size);

    test = Test_init();
    Test_parse_from_string(test, buffer, buffer_size, &offset);
    Test_print(test, 0);
    printf("\n");

	Test_destroy(test);

	return 0;
}
