
class Piece:
    def __init__(self, name, length):
        self.name = name
        self.length = length

class PieceGroup:
    def __init__(self, name, length, quantity):
        self.name = name
        self.length = length
        self.quantity = quantity


class ResultSet:
    def __init__(self, stock, pieces, leftover):
        self.stock = stock
        self.piece_groups = group_pieces(pieces)
        self.leftover = leftover


# params: a list of Piece objects
# returns a list of PieceGroup objects from the Piece objects grouped by name and length 
def group_pieces(self, pieces):
    result = {}

    for piece in pieces:
        key = f"[{piece.name}][{piece.length}]"
        if key not in result:
            result[key] = new PieceGroup(piece.name, piece.length, 0)

        result[key].quantity += 1

    return list(result.values())

# params: a PieceGroup object
# returns a list of identical Piece objects
def ungroup_pieces(self, group):
    result = []
    for i in group.quantity:
        result.append(new Piece(group.name, group.length))

    return result

