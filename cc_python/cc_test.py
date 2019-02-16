import cc_lib as cc
import json

def result_msg(expected, result):
    return f"{'Success' if result == expected else 'Fail'}"

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

def test_Piece_to_dictionary():
    print("\nTest: Piece.to_dictionary()")

    success = "Pass"
    source = [
        cc.Piece("piece_0", 40), cc.Piece(
            "piece_1", 25), cc.Piece("piece_2", 99)
    ]

    expected = [
        {'name': "piece_0", 'length': 40}, {'name': "piece_1",
                                            'length': 25}, {'name': "piece_2", 'length': 99}
    ]

    for i, src in enumerate(source):
        result = src.to_dictionary()
        exp = expected[i]
        src_str = str(src)
        res_str = json.dumps(result)
        exp_str = json.dumps(exp)
        print(f"   input = {src_str}")
        print(f"expected = {exp_str}")
        print(f"  result = {res_str}")
        print(result_msg(exp_str, res_str))
        if res_str != exp_str:
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

#---------------------------------------------

def test_PieceGroup_to_dictionary():
    print("\nTest: PieceGroup.to_dictionary()")
    success = "Pass"

    source = [
        cc.PieceGroup("3x40", 40, 3),
        cc.PieceGroup("2x25", 25, 2),
        cc.PieceGroup("1x99", 99, 1)
    ]

    expected = [
        {'name': "3x40", 'length': 40, 'quantity': 3},
        {'name': "2x25", 'length': 25, 'quantity': 2},
        {'name': "1x99", 'length': 99, 'quantity': 1}
    ]

    for i, src in enumerate(source):
        result = src.to_dictionary()
        exp = expected[i]
        src_str = str(src)
        res_str = json.dumps(result)
        exp_str = json.dumps(exp)
        print(f"   input = {src_str}")
        print(f"expected = {exp_str}")
        print(f"  result = {res_str}")
        print(result_msg(exp_str, res_str))
        if res_str != exp_str:
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
        cc.Piece("piece_0", 40), cc.Piece(
            "piece_1", 40), cc.Piece("piece_2", 40),
        cc.Piece("piece_3", 25), cc.Piece("piece_4", 25),
        cc.Piece("piece_5", 99)
    ]

    combo_list = ["111111", "000000", "101010", "001011", "000111"]

    expected = [
        [item.name for item in source],
        [],
        [source[0].name, source[2].name, source[4].name],
        [source[2].name, source[4].name, source[5].name],
        [source[3].name, source[4].name, source[5].name]
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

#-------------------------------------------

def test_ResultSet_init():
    print("\nTest ResultSet.__init__()")

    success = "Pass"

    name = "result_set"
    stock = cc.Piece("stock", 240)
    pieces = [
        cc.Piece("50in", 50), cc.Piece("50in", 50), cc.Piece("50in", 50),
        cc.Piece("25in", 25), cc.Piece("25in", 25),
        cc.Piece("30in", 30)
    ]
    leftover = 10

    expected_str = {
        'name': name,
        'stock': str(stock),
        'pieces': [str(item) for item in cc.group_pieces(pieces)],
        'leftover': leftover
    }

    result = cc.ResultSet(name, stock, pieces, leftover)

    result_str = {
        'name': result.name,
        'stock': str(result.stock),
        'pieces': [str(item) for item in result.piece_groups],
        'leftover': result.leftover
    }

    print("input:")
    print(f"name = {name}")
    print(f"stock = {str(stock)}")
    print(f"pieces = {[str(item) for item in pieces]}")
    print(f"leftover = {leftover}")

    for key in expected_str:
        exp_str = expected_str[key]
        res_str = result_str[key]
        print(f"expected: {key} = {exp_str}")
        print(f"  result: {key} = {res_str}")
        print(result_msg(exp_str, res_str))
        if res_str != exp_str:
            success = "Fail"

    return success


#------------------------------------------------

def test_has_bit():
    print("\nTest: has_bit(binary)")

    source = [{'in': '01001', 'out': True}, {'in': '1010', 'out': True}, {'in': '0000000', 'out': False}]
    success = "Pass"

    c_c = cc.CC()

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = c_c.has_bit(src_in)
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

    c_c = cc.CC()

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = c_c.flip_bit(src_in)
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

    c_c = cc.CC()

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = c_c.next_binary(src_in)
        if result != src_out:
            success = "Fail"

        print(f"   input = {src_in}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

    return success

#--------------------------------------------

def test_skip_binary():
    print("\nTest: skip_binary(binary)")

    success = "Pass"
    source = [{'in': '1100100', 'out': '1101000'}, {'in': '0010001000', 'out': '0010010000'}, {'in': '11111', 'out': '00000'}]

    c_c = cc.CC()

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = c_c.skip_binary(src_in)
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

    c_c = cc.CC()

    for src in source:
        param_1 = src['p1']
        param_2 = src['p2']
        src_out = src['out']
        result = c_c.has_common_bit(param_1, param_2)
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

    c_c = cc.CC()

    for src in source:
        param_1 = src['p1']
        param_2 = src['p2']
        src_out = src['out']
        result = c_c.to_binary(param_1, param_2)
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

    c_c = cc.CC()

    for src in source:
        src_in = src['in']
        src_out = src['out']
        result = c_c.to_integer(src_in)
        if result != src_out:
            success = "Fail"

        print(f"   input = {src_in}")
        print(f"expected = {src_out}")
        print(f"  result = {result}")
        print(result_msg(src_out, result))

    return success

#------------------------------------------

def test_set_inputs():
    print("\nTest: set_inputs(pieces, containers, loss)")
    
    success = "Pass"

    source = {
        'pieces': [{'size': 30}, {'size': 60}, {'size': 20}, {'size': 40}],
        'containers': [{'capacity': 300}, {'capacity': 200}, {'capacity': 150}],
        'loss': 0.25
    }

    expected = {
        'pieces': [{'size': 60}, {'size': 40}, {'size': 30}, {'size': 20}],
        'containers': [{'capacity': 150}, {'capacity': 200}, {'capacity': 300}],
        'loss': 0.25
    }

    c_c = cc.CC()
    c_c.set_inputs(source['pieces'], source['containers'], source['loss'])

    result = {
        'pieces': c_c._pieces,
        'containers': c_c._containers,
        'loss': c_c._loss_per_piece
    }

    for key in source:
        src = json.dumps(source[key])
        exp = json.dumps(expected[key])
        res = json.dumps(result[key])
        print(f"   input {key} = {src}")
        print(f"expected {key} = {exp}")
        print(f"  output {key} = {res}")
        if exp != res:
            success = "Fail"

    return success

#------------------------------------------


def test_combo_size():
    print("\nTest: combo_size(binary)")

    success = "Pass"

    source = {
        'pieces': [{'size': 40}, {'size': 30}, {'size': 60}],
        'containers': [{'capacity': 300}, {'capacity': 200}, {'capacity': 150}],
        'loss': 0       
    }

    # sorted: [{'size': 60}, {'size': 30}, {'size': 20}]
    combos = ["001", "010", "100", "101", "011", "110", "111"] 
    expected = [30, 40, 60, 90, 70, 100, 130]   

    c_c = cc.CC()
    c_c.set_inputs(source['pieces'], source['containers'], source['loss'])

    print(f"pieces: {json.dumps(c_c._pieces)}")
    print(f"loss = {c_c._loss_per_piece}")

    for i, combo in enumerate(combos):
        exp = expected[i]
        res = c_c.combo_size(combo)
        print(f"   input = {combo}")
        print(f"expected = {exp}")
        print(f"  result = {res}")
        if exp != res:
            success = "Fail"

    c_c.set_inputs(source['pieces'], source['containers'], 0.25)
    expected = [30.25, 40.25, 60.25, 90.5, 70.5, 100.5, 130.75]

    print(f"pieces: {json.dumps(c_c._pieces)}")
    print(f"loss = {c_c._loss_per_piece}")

    for i, combo in enumerate(combos):
        exp = expected[i]
        res = c_c.combo_size(combo)
        print(f"   input = {combo}")
        print(f"expected = {exp}")
        print(f"  result = {res}")
        if exp != res:
            success = "Fail"

    return success



#---------------------------------------------

def test_build_piece_combos():
    print("\nTest: build_piece_combos()")

    success = "Pass"

    source = {
        'pieces': [{'size': 30}, {'size': 60}, {'size': 20}],
        'containers': [{'capacity': 300}, {'capacity': 200}, {'capacity': 150}],
        'loss': 0
    }

    # sorted: [{'size': 60}, {'size': 30}, {'size': 20}]

    expected = {
        '001': {'combo_size': 20}, 
        '010': {'combo_size': 30},
        '011': {'combo_size': 50},
        '100': {'combo_size': 60},
        '101': {'combo_size': 80},
        '110': {'combo_size': 90},
        '111': {'combo_size': 110}
    }

    c_c = cc.CC()
    c_c.set_inputs(source['pieces'], source['containers'], source['loss'])

    result = c_c._piece_combos

    exp = json.dumps(expected)
    res = json.dumps(result)

    for key in source:
        src = json.dumps(source[key])
        print(f"   input {key} = {src}")

    print(f"expected combos = {exp}")
    print(f"  output combos = {res}")
    if res != exp:
        success = "Fail"

    return success

#--------------------------------------------------

def test_filter_pieces():
    print("\nTest: filter_pieces(combo)")
    success = "Pass"

    source = {
        'pieces': [{'size': 30}, {'size': 20}, {'size': 60}],
        'containers': [{'capacity': 300}, {'capacity': 200}, {'capacity': 150}],
        'loss': 0
    }

    c_c = cc.CC()
    c_c.set_inputs(source['pieces'], source['containers'], source['loss'])

    # sorted: [{'size': 60}, {'size': 30}, {'size': 20}]
    combos = ["001", "010", "100", "101", "011", "110", "111"]
    expected = [
        [{'size': 20}],
        [{'size': 30}],
        [{'size': 60}],
        [{'size': 60}, {'size': 20}],
        [{'size': 30}, {'size': 20}],
        [{'size': 60}, {'size': 30}],
        [{'size': 60}, {'size': 30}, {'size': 20}]
    ]

    print(f"pieces: {json.dumps(c_c._pieces)}")

    for i, combo in enumerate(combos):
        exp = json.dumps(expected[i])
        res = json.dumps(c_c.filter_pieces(combo))
        print(f"   input = {combo}")
        print(f"expected = {exp}")
        print(f"  result = {res}")
        if exp != res:
            success = "Fail"

    return success

#----------------------------------------

def test_best_match():
    print("\nTest: best_match()")
    success = "Pass"

    source = {
        'pieces': [{'size': 30}, {'size': 60}, {'size': 20}, {'size': 40}, {'size': 50}],
        'containers': [{'capacity': 85}, {'capacity': 90}, {'capacity': 110}],
        'loss': 0.25
    }

    # sorted: [{'size': 60}, {'size': 50}, {'size': 40}, {'size': 30}, {'size': 20}]

    expected = {
        'binary': "10001",
        'combo': {'combo_size': 80.5,},
        'pieces': [{'size': 60}, {'size': 20}],
        'container': {'capacity': 85},
        'difference': 4.5
    }

    expected['remaining_containers'] = [{'capacity': 90}, {'capacity': 110}]

    c_c = cc.CC()
    c_c.set_inputs(source['pieces'], source['containers'], source['loss'])

    print(f"pieces: {json.dumps(c_c._pieces)}")
    print(f"containers: {json.dumps(c_c._containers)}")

    result = c_c.best_match()

    result['remaining_containers'] = c_c._containers

    for key in expected:
        exp = json.dumps(expected[key])
        res = json.dumps(result[key])
        print(f"expected {key} = {exp}")
        print(f"  output {key} = {res}")
        if exp != res:
            success = "Fail"    

    return success


#==============================================

def main():
    print("=== Cut Calculator Test ===")

    tests = {
        'has_bit()': test_has_bit(),
        'flip_bit()' : test_flip_bit(),
        'has_common_bit()': test_has_common_bit(),
        'next_binary()': test_next_binary(),
        'skip_binary()': test_skip_binary(),
        'to_binary()': test_to_binary(),        
        'to_integer()': test_to_integer(),
        'set_inputs()': test_set_inputs(),
        'combo_size()': test_combo_size(),
        'build_piece_combos()': test_build_piece_combos(),
        'filter_pieces()': test_filter_pieces(),
        'best_match()': test_best_match(),
        
        #'Piece.__init__()': test_Piece_init(),
        #'Piece.__str__()': test_Piece_str(),
        #'Piece.to_dictionary()': test_Piece_to_dictionary(),
        #'PieceGroup.__init__()': test_PieceGroup_init(),
        #'PieceGroup.__str__()': test_PieceGroup_str(),
        #'PieceGroup.to_dictionary()': test_PieceGroup_to_dictionary(),
        #'ungroup()': test_ungroup(),
        #'group_pieces()': test_group_pieces(),
        #'ungroup_pieces()': test_ungroup_pieces(),
        #'get_combo_pieces()': test_get_combo_pieces(),
        #'ResultSet.__init()__': test_ResultSet_init()
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
