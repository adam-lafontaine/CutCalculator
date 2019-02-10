import cc_lib as cc

def result_msg(expected, result):
    return f"{'Success' if result == expected else 'Fail'}"

def test_has_bit():
    print("\nTest: has_bit(binary)")

    source = [{'in': '01001', 'out': True}, {'in': '1010', 'out': True}, {'in': '0000000', 'out': False}]
    success = "Pass"

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = cc.has_bit(src_in)
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
        result = cc.flip_bit(src_in)
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
        result = cc.next_binary(src_in)
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
        result = cc.has_common_bit(param_1, param_2)
        if result != src_out:
            success = "Fail"

        print(f"   input = {param_1}, {param_2}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

    return success

#-----------------------------------------------

def test_to_binary():
    print("\nTest: to_binary(value, num_bits)")

    success = "Pass"
    source = [
        {'p1': 3205, 'p2': 12, 'out': '110010000101'},
        {'p1': 55, 'p2': 6, 'out': '110111'},
        {'p1': 55, 'p2': 12, 'out': '000000110111'},
        {'p1': 3205, 'p2': 5, 'out': '110010000101'},
        {'p1': 1, 'p2': 12, 'out': '000000000001'},
    ]

    for src in source:
        param_1 = src['p1']
        param_2 = src['p2']
        src_out = src['out']
        result = cc.to_binary(param_1, param_2)
        if result != src_out:
            success = "Fail"

        print(f"   input = {param_1}, {param_2}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

    return success

#------------------------------------------------

def test_to_integer():
    print("\nTest: to_integer(binary)")

    success = "Pass"
    source = [
        {'in': '1011', 'out': 11}, 
        {'in': '100011', 'out': 35}, 
        {'in': '0000000', 'out': 0},
        {'in': '1001001110001', 'out': 4721},
        {'in': '00001011', 'out': 11},
        {'in': '0000100011', 'out': 35},
        {'in': '00001001001110001', 'out': 4721}
        ]

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = cc.to_integer(src_in)
        if result != src_out:
            success = "Fail"

        print(f"   input = {src_in}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

    return success

#-------------------------------------------

def test_Piece_init():
    print("\nTest: Piece.__init__()")
    
    success = "Pass"
    source = [
        {'name': 'piece1', 'length': 45},
        {'name': 'piece2', 'length': 66},
        {'name': 'piece3', 'length': 2}
        ]

    for src in source:
        name = src['name']
        length = src['length']
        piece = cc.Piece(name, length)
        exp = f"name: {name}, length: {length}"
        result = f"name: {piece.name}, length: {piece.length}"
        print(f"   input = {src}")
        print(f"expected = {exp}")
        print(f"  result = {result}")
        print(result_msg(exp, result))
        if result != exp:
            success = "Fail"

    return success

#-----------------------------------------------

def test_Piece_str():
    print("\nTest: Piece.__str()__")

    success = "Pass"
    source = [
        {'name': 'piece1', 'length': 45},
        {'name': 'piece2', 'length': 66},
        {'name': 'piece3', 'length': 2}
    ]

    expected = [
        "name: piece1, length: 45",
        "name: piece2, length: 66",
        "name: piece3, length: 2"
    ]

    for i in range(0, 3):
        src = source[i]
        exp = expected[i]
        piece = cc.Piece(src['name'], src['length'])        
        result = str(piece)
        print(f"   input = {src}")
        print(f"expected = {exp}")
        print(f"  result = {result}")
        print(result_msg(exp, result))
        if result != exp:
            success = "Fail"

    return success

#-----------------------------------------------

def test_PieceGroup_init():
    print("\nTest: PieceGroup.__init__()")
    
    success = "Pass"
    source = [
        {'name': 'piece1', 'length': 45, 'qty': 10},
        {'name': 'piece2', 'length': 66, 'qty': 8},
        {'name': 'piece3', 'length': 2, 'qty': 99}
    ]

    for src in source:
        name = src['name']
        length = src['length']
        qty = src['qty']
        piece_group = cc.PieceGroup(name, length, qty)
        exp = f"name: {name}, length: {length}, qty: {qty}"
        result = f"name: {piece_group.name}, length: {piece_group.length}, qty: {piece_group.quantity}"
        print(f"   input = {src}")
        print(f"expected = {exp}")
        print(f"  result = {result}")
        print(result_msg(exp, result))
        if result != exp:
            success = "Fail"

    return success

#-----------------------------------------------

def test_PieceGroup_str():
    print("\nTest: PieceGroup.__str__()")

    success = "Pass"
    source = [
        {'name': 'piece1', 'length': 45, 'qty': 10},
        {'name': 'piece2', 'length': 66, 'qty': 8},
        {'name': 'piece3', 'length': 2, 'qty': 99}
    ]

    expected = [
        "name: piece1, length: 45, quantity: 10",
        "name: piece2, length: 66, quantity: 8",
        "name: piece3, length: 2, quantity: 99"
    ]

    for i in range(0, 3):
        src = source[i]
        exp = expected[i]
        piece_group = cc.PieceGroup(src['name'], src['length'], src['qty'])
        result = str(piece_group)
        print(f"   input = {src}")
        print(f"expected = {exp}")
        print(f"  result = {result}")
        print(result_msg(exp, result))
        if result != exp:
            success = "Fail"

    return success

#----------------------------------------------

def test_ungroup():
    print("\nTest ungroup()")

    success = "Pass"
    source = [
        cc.PieceGroup("3x40", 40, 3),
        cc.PieceGroup("2x25", 25, 2),
        cc.PieceGroup("1x99", 99, 1)
    ]

    expected = [
        [cc.Piece("3x40", 40), cc.Piece("3x40", 40), cc.Piece("3x40", 40)],
        [cc.Piece("2x25", 25), cc.Piece("2x25", 25)],
        [cc.Piece("1x99", 99)]
    ]

    for i in range(0, 3):
        src = source[i]
        exp = expected[i]
        result = cc.ungroup(src)

        exp_str = [str(item) for item in exp]
        res_str = [str(item) for item in result]

        print(f"   input = {src}")
        print(f"expected = {exp_str}")
        print(f"  result = {res_str}")
        print(result_msg(exp_str, res_str))
        if res_str != exp_str:
            success = "Fail"

    return success

#------------------------------------------------

def test_group_pieces():
    print("\nTest group_pieces(pieces)")
    
    success = "Pass"

    source = [
        cc.Piece("3x40", 40), cc.Piece("3x40", 40), cc.Piece("3x40", 40),
        cc.Piece("2x25", 25), cc.Piece("2x25", 25),
        cc.Piece("1x99", 99)       
    ]

    expected = [
        cc.PieceGroup("3x40", 40, 3),
        cc.PieceGroup("2x25", 25, 2),
        cc.PieceGroup("1x99", 99, 1)
    ]

    result = cc.group_pieces(source)

    src_str = [str(item) for item in source]
    exp_str = [str(item) for item in expected]
    res_str = [str(item) for item in result]

    print(f"   input = {src_str}")
    print(f"expected = {exp_str}")
    print(f"  result = {res_str}")
    print(result_msg(exp_str, res_str))
    if res_str != exp_str:
        success = "Fail"        

    return success

#-------------------------------------------------

def test_ungroup_pieces():
    print("Test: ungroup_pieces(group_list)")

    success = "Pass"

    source = [
        cc.PieceGroup("3x40", 40, 3),
        cc.PieceGroup("2x25", 25, 2),
        cc.PieceGroup("1x99", 99, 1)
    ]

    expected = [
        cc.Piece("3x40", 40), cc.Piece("3x40", 40), cc.Piece("3x40", 40),
        cc.Piece("2x25", 25), cc.Piece("2x25", 25),
        cc.Piece("1x99", 99)
    ]

    result = cc.ungroup_list(source)

    src_str = [str(item) for item in source]
    exp_str = [str(item) for item in expected]
    res_str = [str(item) for item in result]

    print(f"   input = {src_str}")
    print(f"expected = {exp_str}")
    print(f"  result = {res_str}")
    print(result_msg(exp_str, res_str))
    if res_str != exp_str:
        success = "Fail"        

    return success

#-------------------------------------------------

def test_get_combo_pieces():
    print("\nTest: get_combo_pieces(binary, all_pieces")

    success = "Pass"
    source = [
        cc.Piece("piece_0", 40), cc.Piece("piece_1", 40), cc.Piece("piece_2", 40),
        cc.Piece("piece_3", 25), cc.Piece("piece_4", 25),
        cc.Piece("piece_5", 99)
    ]

    combo_list = ["111111", "000000", "101010", "001011", "000111"]

    expected = [
        [item.name for item in source],
        [],
        [ source[0].name, source[2].name, source[4].name ],
        [ source[2].name, source[4].name, source[5].name ],
        [ source[3].name, source[4].name, source[5].name ]
    ]

    source_names = [item.name for item in source]

    for i, combo in enumerate(combo_list):
        src_str = f"{combo} | {source_names}"
        exp_str = expected[i]
        result = cc.get_combo_pieces(combo, source)
        res_str = [item.name for item in result]
        print(f"   input = {src_str}")
        print(f"expected = {exp_str}")
        print(f"  result = {res_str}")
        print(result_msg(exp_str, res_str))
        if res_str != exp_str:
            success = "Fail"

    return success

#==============================================

def main():
    print("=== Cut Calculator Test ===")

    tests = {
        'has_bit()': test_has_bit(),
        'flip_bit()' : test_flip_bit(),
        'next_binary()' : test_next_binary(),
        'has_common_bit()': test_has_common_bit(),
        'to_binary()': test_to_binary(),
        'to_integer()': test_to_integer(),
        'Piece.__init__()': test_Piece_init(),
        'Piece.__str__()': test_Piece_str(),
        'PieceGroup.__init__()': test_PieceGroup_init(),
        'ungroup()': test_ungroup(),
        'group_pieces()': test_group_pieces(),
        'ungroup_pieces()': test_ungroup_pieces(),
        'get_combo_pieces()': test_get_combo_pieces()
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
