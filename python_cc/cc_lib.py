
class CC:
    _piece_combos = {} # { "001": { 'combo_size': 30, 'meta': {} }, '010': { 'combo_size': 25, 'meta': {} } }
    _pieces = []       # [ { 'size': 60, 'meta': {} }, {'size': 60, 'meta': {} } ]
    _containers = []   # [ { 'capacity': 200, 'meta': {} }, { 'capacity': 150, 'meta': {} } ]
    _results = []      # [ { 'binary': "001" 'combo': {}, 'pieces': [], 'container': {}, 'delta': 10 }, ]

    _loss_per_piece = 0
    _tolerance = 0

    # TESTED
    def set_inputs(self, pieces, containers, loss=0):
        """ 
        list of pieces { 'size': number }
        list of empty containers { 'capacity': number, 'pieces': [], 'cap_remaining': number }
        generates _piece_combos
         """
        self._pieces = sorted(pieces, key=lambda i: i['size'], reverse=True) # descending
        self._containers = sorted(containers, key=lambda i: i['capacity'])   # ascending
        self._loss_per_piece = loss
        self._piece_combos = {}
        self._results = []

        self.build_piece_combos()

    #------------------------------------------------------    

    # TESTED
    def to_binary(self, int_value, num_bits):
        result = []

        bin_values = ['0', '1']
        val = int_value

        while(val > 0):
            idx = int(val % 2)
            result.append(bin_values[idx])
            val -= idx
            val /= 2

        binary = ''.join(result[::-1])
        if len(binary) < num_bits:
            binary = binary.rjust(num_bits, '0')

        return binary

    #--------------------------------------------

    # TESTED
    def to_integer(self, binary):
        result = 0
        rev = binary[::-1]

        for i, bit in enumerate(rev):
            if bit == '1':
                result += 2 ** i

        return result

    #--------------------------------------------

    # TESTED
    def has_bit(self, binary):
        return '1' in binary

    #---------------------------------------------

    # TESTED
    def flip_bit(self, bit):
        return '1' if bit == '0' else '0'

    #---------------------------------------------

    # TESTED
    def has_common_bit(self, bin_1, bin_2):
        rev_1 = bin_1[::-1]
        rev_2 = bin_2[::-1]

        for i in range(0, min(len(bin_1), len(bin_2))):
            if rev_1[i] == '1' and rev_2[i] == '1':
                return True

        return False

    #-----------------------------------------

    # TESTED
    def next_binary(self, binary):
        rev_list = list(binary[::-1])

        for i, e in enumerate(rev_list):
            rev_list[i] = self.flip_bit(e)
            if rev_list[i] == '1':
                break

        return ''.join(rev_list[::-1])

    #-----------------------------------------

    # TESTED
    def skip_binary(self, binary):
        rev_list = list(binary[::-1])

        rev_list[0] = '1'

        for i in range(1, len(rev_list)):
            if rev_list[i] == '1':
                break
            else:
                rev_list[i] = '1'

        return self.next_binary(''.join(rev_list[::-1]))

    #---------------------------------------------

    # TESTED
    def combo_size(self, binary):
        result = 0
        for i, bit in enumerate(binary):
            result += int(bit) * (self._pieces[i]['size'] + self._loss_per_piece) # wrong   

        return result   

    #----------------------------------------

    # TESTED
    def build_piece_combos(self):
        int_val = 1
        binary = self.to_binary(int_val, len(self._pieces))
        max_capacity = self._containers[-1]['capacity'] + self._loss_per_piece  # last element
        
        while self.has_bit(binary):
            size = self.combo_size(binary)
            if size <= max_capacity:
                self._piece_combos[binary] = {'combo_size': size}
                binary = self.next_binary(binary)
            else:
                binary = self.skip_binary(binary)

    #-----------------------------------------------------

    # TESTED
    def filter_pieces(self, combo):
        '''
        returns subset of _pieces based on the combo passed
        '''
        result = []

        for i, bit in enumerate(combo):
            if bit == '1':
                result.append(self._pieces[i])

        return result

    #-----------------------------------------

    # TESTED
    def best_match(self):
        result = {}
        if len(self._containers) == 0:
            return result

        max_capacity = self._containers[-1]['capacity'] + self._loss_per_piece  # last element
        diff = max_capacity
        best_diff = max_capacity
        container_index = 0

        sorted_combos = sorted(self._piece_combos.keys(), reverse=True)

        for binary in sorted_combos:
            size = self._piece_combos[binary]['combo_size']

            for i, container in enumerate(self._containers):
                diff = container['capacity'] - size

                # not needed as _loss_per_piece is included in max_capacity
                #if diff < 0 and abs(diff) <= self._loss_per_piece:
                #    diff = 0

                if 0 <= diff and diff < best_diff:
                    best_diff = diff
                    result['binary'] = binary
                    container_index = i   
                    
                    if diff <= self._tolerance:
                        result['combo'] = self._piece_combos[binary]
                        result['pieces'] = self.filter_pieces(binary)
                        result['container'] = self._containers.pop(i)
                        result['delta'] = diff
                        return result

        result['combo'] = self._piece_combos[result['binary']]
        result['pieces'] = self.filter_pieces(result['binary'])
        result['container'] = self._containers.pop(container_index) # remove container
        result['delta'] = best_diff

        return result

    #------------------------------------------------

    # TESTED
    def remove_combos(self, binary):
        '''
        deletes all combos that share a bit with binary
        or have a size larger than the max container capacity
        '''

        has_max = len(self._containers) > 0
        max_capacity = 0
        if has_max:
            max_capacity = self._containers[-1]['capacity'] + self._loss_per_piece  # last element
        
        combos = [key for key in self._piece_combos.keys()]

        for combo in combos:
            if self.has_common_bit(binary, combo) or (has_max and self._piece_combos[combo]['combo_size'] > max_capacity):
                del self._piece_combos[combo]

    #---------------------------------------------

    def sort(self):

        result = {
            'data': [],
            'success': True,
            'message': ""
        }

        while len(self._containers) > 0 and len(self._piece_combos) > 0:
            match = self.best_match()
            self.remove_combos(match['binary'])
            self._results.append(match)

        result['data'] = self._results

        if len(self._piece_combos) > 0:
            result['message'] = "Not enough containers"
            result['success'] = False
        else:
            result['message'] = "Sort successful"
            result['success'] = True

        return result

#=================================================


# TESTED
class Piece:
    name = ""
    length = 0

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
    name = ""
    length = 0
    quantity = 0

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
    name = ""
    stock = {}
    pieces = []
    leftover = 0

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











