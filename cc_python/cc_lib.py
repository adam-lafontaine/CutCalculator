
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
def group_pieces(self, pieces):
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
def ungroup(self, group):
    result = []
    for i in group.quantity:
        result.append(Piece(group.name, group.length))

    return result

#-------------------------------------------------

def ungroup_list(self, group_list):
    result = []
    for grp in group_list:
        result.extend(grp)

    return result

# binary: [0, 1, 1, 0,...]
# all_pieces: list of pieces
# returns list of pieces in the binary combination
def get_combo_pieces(self, binary, all_pieces):
    result = []
    for i in binary:
        if i == 1:
            result.append(all_pieces[i])

    return result

#-------------------------------------------------

# returns true if binary has at least one true value
def has_bit(self, binary):
    return 1 in binary

#-------------------------------------------------

def flip_bit(self, bit):
    return bit = 1 if bit == 0 else 0

#-------------------------------------------------

# increments binary number by 1
def next_binary(self, binary):
    result = binary
    for i, e in reversed(list(enumerate(binary))):
        result[i] = flip_bit[e]
        if result[i] == 1:
            break

    return result


