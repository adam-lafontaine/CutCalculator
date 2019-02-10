# TESTED
class Piece:
    def __init__(self, name, length):
        self.name = name
        self.length = length

    def to_dictionary(self):
        return { 'name': self.name, 'length': self.length } # json.dumps()

    def __str__(self):
        return f"name: {self.name}, length: {self.length}"

#------------------------------------------------

# TESTED
class PieceGroup:
    def __init__(self, name, length, quantity):
        self.name = name
        self.length = length
        self.quantity = quantity

    def to_dictionary(self):
        return { 'name': self.name, 'length': self.length, 'quantity': self.quantity }

    def __str__(self):
        return f"name: {self.name}, length: {self.length}, quantity: {self.quantity}"

#------------------------------------------------


class ResultSet:
    def __init__(self, name, stock, pieces, leftover):
        self.name = name
        self.stock = stock
        self.piece_groups = group_pieces(pieces)
        self.leftover = leftover

    def to_dictionary(self):
        return {
            'name': self.name,
            'stock': self.stock.to_dictionary(),
            'pieces': [item.to_dictionary() for item in self.piece_groups],
            'leftover': self.leftover
        }


    def __str__(self):
        return f"name: {self.name}\nstock: {str(self.stock)}\npieces: {[str(item) for item in self.piece_groups]}\nleftover: {self.leftover}"

#--------------------------------------------------

# TESTED
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

# TESTED
# params: a PieceGroup object
# returns a list of identical Piece objects
def ungroup(group):
    result = []
    for i in range(group.quantity):
        result.append(Piece(group.name, group.length))

    return result

#-------------------------------------------------

# TESTED
# params: a list of PieceGroup objects
# returns a list of Piece objects
def ungroup_list(group_list):
    result = []
    for grp in group_list:
        result.extend(ungroup(grp))

    return result

#-------------------------------------------------

# TESTED
# returns true if binary has at least one true value
def has_bit(binary):
    return '1' in binary

#-------------------------------------------------

# TESTED
def flip_bit(bit):
    return '1' if bit == '0' else '0'

#-------------------------------------------------

#TESTED
# increments binary number by 1
def next_binary(binary):
    rev_list = list(binary[::-1])
    
    for i, e in enumerate(rev_list):
        rev_list[i] = flip_bit(e)
        if rev_list[i] == '1':
            break

    return ''.join(rev_list[::-1])

#------------------------------------------------

#TESTED
def has_common_bit(bin_1, bin_2):
    rev_1 = bin_1[::-1]
    rev_2 = bin_2[::-1]

    for i in range(0, min(len(bin_1), len(bin_2))):
        if rev_1[i] == '1' and rev_2[i] == '1':
            return True

    return False

#-------------------------------------------------

# TESTED
def to_binary(value, num_bits):
    result = []

    bin_values = ['0', '1']
    val = value

    while(val > 0):
        idx = int(val % 2)
        result.append(bin_values[idx])
        val -= idx
        val /= 2

    binary = ''.join(result[::-1])
    if len(binary) < num_bits:
        binary = binary.rjust(num_bits, '0')

    return binary

#---------------------------------------------------

# TESTED
def to_integer(binary):
    result = 0
    rev = binary[::-1]

    for i, bit in enumerate(rev):
        if bit == '1':
            result += 2 ** i

    return result

#--------------------------------------------------

# TESTED
# binary: '01101...'
# all_pieces: list of pieces
# returns list of pieces in the binary combination
# assert: 
def get_combo_pieces(binary, all_pieces):
    result = []    

    rev_binary = binary[::-1] # makes a copy
    all_pieces.reverse()

    for i, bit in enumerate(rev_binary):
        if bit == '1':
            result.insert(0, all_pieces[i])

    all_pieces.reverse() # by reference
    
    return result

#-------------------------------------------------
