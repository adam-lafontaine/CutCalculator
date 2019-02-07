
class Piece:
    def __init__(self, name, length):
        self.name = name
        self.length = length

class PieceGroup:
    def __init__(self, name, length, quantity):
        self.name = name
        self.length = length
        self.quantity = quantity

#------------------------------------------------


class ResultSet:
    def __init__(self, stock, pieces, leftover):
        self.stock = stock
        self.piece_groups = self.group(pieces)
        self.leftover = leftover

    def group(self, pieces):
        result = {}
        for piece in pieces:
            key = f"[{piece.name}][{piece.length}]"
            if key not in result:
                result[key] = PieceGroup(piece.name, piece.length, 0)

            result[key].quantity += 1

        return list(result.values())

#--------------------------------------------------

# params: a list of Piece objects
# returns a list of PieceGroup objects from the Piece objects grouped by name and length
def group_pieces(pieces):
    result = {}

    for piece in pieces:
        key = f"[{piece.name}][{piece.length}]"
        if key not in result:
            result[key] = PieceGroup(piece.name, piece.length, 0)

        result[key].quantity += 1

    return list(result.values())

#-------------------------------------------------

# params: a PieceGroup object
# returns a list of identical Piece objects
def ungroup(group):
    result = []
    for i in group.quantity:
        result.append(Piece(group.name, group.length))

    return result

#-------------------------------------------------

def ungroup_list(group_list):
    result = []
    for grp in group_list:
        result.extend(grp)

    return result

# binary: '01101...'
# all_pieces: list of pieces
# returns list of pieces in the binary combination
def get_combo_pieces(binary, all_pieces):
    result = []
    for i in binary:
        if i == '1':
            result.append(all_pieces[i])

    return result

#-------------------------------------------------

# returns true if binary has at least one true value
def has_bit(binary):
    return '1' in binary

#-------------------------------------------------

def flip_bit(bit):
    return '1' if bit == '0' else '0'

#-------------------------------------------------

# increments binary number by 1
def next_binary(binary):
    result = binary
    for i, e in reversed(list(enumerate(binary))):
        result[i] = flip_bit(e)
        if result[i] == '1':
            break

    return result

#------------------------------------------------

def has_common_bit(bin_1, bin_2):
    rev_1 = bin_1[::-1]
    rev_2 = bin_2[::-1]

    for i in range(0, min(len(bin_1), len(bin_2))):
        if rev_1[i] == rev_2[i]:
            return True

    return False
