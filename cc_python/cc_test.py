import cc_lib

def result_msg(expected, result):
    return f"{'Success' if result == expected else 'Fail'}"

def test_has_bit():
    print("/nTest: has_bit(binary)")
    source = [{'in': '01001', 'out': True}, {'in': '1010', 'out': True}, {'in': '0000000', 'out': False}]
    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = cc_lib.has_bit(src_in)
        print(f"   input = {src_in}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

#---------------------------------------

def test_flip_bit():
    print("/nTest: has_bit(binary)")
    source = [{'in': '0', 'out': '1'}, {'in': '1', 'out': '0'}]
    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = cc_lib.has_bit(src_in)
        print(f"   input = {src_in}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

#-------------------------------------------


def main():
    print("=== Cut Calculator Test ===")

    test_has_bit()
    test_flip_bit()

#==================================
if __name__ == '__main__':
    main()
