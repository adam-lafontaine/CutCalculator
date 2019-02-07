import cc_lib

def result_msg(expected, result):
    return f"{'Success' if result == expected else 'Fail'}"

def test_has_bit():
    print("\nTest: has_bit(binary)")

    source = [{'in': '01001', 'out': True}, {'in': '1010', 'out': True}, {'in': '0000000', 'out': False}]
    success = "Pass"

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = cc_lib.has_bit(src_in)
        if result != src_out:
            success = "Fail"

        print(f"   input = {src_in}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

    return success

#---------------------------------------

def test_flip_bit():
    print("\nTest: flip_bit(binary)")

    source = [{'in': '0', 'out': '1'}, {'in': '1', 'out': '0'}]
    success = "Pass"

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = cc_lib.flip_bit(src_in)
        if result != src_out:
            success = "Fail"

        print(f"   input = {src_in}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

    return success

#-------------------------------------------

def test_next_binary():
    print("\nTest: next_binary(binary)")

    success = "Pass"
    source = [{'in': '1011', 'out': '1100'}, {'in': '100011', 'out': '100100'}, {'in': '0000000', 'out': '0000001'}]

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = cc_lib.next_binary(src_in)
        if result != src_out:
            success = "Fail"

        print(f"   input = {src_in}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

    return success

#--------------------------------------------

def test_has_common_bit():
    print("\nTest: has_common_bit(bin_1, bin_2)")

    success = "Pass"
    source = [
        {'p1': '0', 'p2': '0', 'out': False},
        {'p1': '0', 'p2': '1', 'out': False},
        {'p1': '100110', 'p2': '000100', 'out': True},
        {'p1': '0100110011', 'p2': '0010', 'out': True},
        {'p1': '1001001', 'p2': '0110110', 'out': False}
        ]

    for src in source:
        param_1 = src['p1']
        param_2 = src['p2']
        src_out = src['out']
        result = cc_lib.has_common_bit(param_1, param_2)
        if result != src_out:
            success = "Fail"

        print(f"   input = {param_1}, {param_2}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

    return success

#==============================================

def main():
    print("=== Cut Calculator Test ===")

    tests = {
        'has_bit()': test_has_bit(),
        'flip_bit()' : test_flip_bit(),
        'next_binary()' : test_next_binary(),
        'has_common_bit()': test_has_common_bit()
    }

    spaces = 0
    for key in tests:
        spaces = len(key) if len(key) > spaces else spaces

    print("\nSummary:")
    for key in tests:
        print(f"{key.rjust(spaces)}: {tests[key]}")

    print("\nDone.")

#==================================
if __name__ == '__main__':
    main()
