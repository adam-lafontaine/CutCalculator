/*
calc.js - computational functions
*/

//-------------------------------------------------

// sorts lengths to be cut from stock LengthsInStockList
// takes an array of LengthGroups to cut
// and an array of LengthGroups in stock to be cut from
// returns an array of ResultSet objects
function sortLengths(cutLengthGroupArray, stockLengthGroupArray)
{
	var results = []; // array of ResultSet objects

	// convert arrays of LengthGroups to arrays of Lengths
	var cutArray = convertToLengthArray(cutLengthGroupArray);
	var stockArray = convertToLengthArray(stockLengthGroupArray);

	// sort arrays
	var descending = function(lhs, rhs){return rhs.pieceLength - lhs.pieceLength};
	var ascending = function(lhs, rhs){return lhs.pieceLength - rhs.pieceLength};

	cutArray.sort(descending);
	stockArray.sort(ascending);

	// hash of bool array for combo and coresponding length
	var comboList = makeComboList(cutArray, stockArray[stockArray.length - 1].pieceLength);


	// loop until no combos remain
	while(Object.keys(comboList).length > 0)
	{
		// choose best stock/combo
		var bestStockAndCombo = findBestStockAndCombo(stockArray, comboList);

		// get stock from stockArray and remove
		var bestStock = stockArray.splice(bestStockAndCombo.stockIndex, 1)[0];

		// get array of Lengths from cutArray and remove
		var bestCombo = bestStockAndCombo.binary;
		var lengthArray = getLengthArrayFromCombo(bestCombo, cutArray);

		// remove redundant combos
		removeCombos(comboList, bestCombo, stockArray[stockArray.length - 1].pieceLength);

		// create ResultSet from stock and array of Lengths
		results.push(new ResultSet(bestStock, lengthArray, bestStockAndCombo.leftover));
	}

	return results;
}

//***************** UTILITY FUNCTIONS ********************************



// returns an array Lengths from cutArray based on the combination
function getLengthArrayFromCombo(binary, cutArray)
{
	var result = [];

	for(var i = cutArray.length - 1; i >= 0; i--)
	{
		var bit = binary[i];
		if(binary[i] === 1)
		{
			result.push(cutArray[i]);
		}
	}

	return result;
}

//---------------------------------------------------------

// converts an array of LengthGroup objects to and array of Length objects
function convertToLengthArray(lgArray)
{
	var result = [];
	for(var i = 0; i < lgArray.length; i++)
	{
		var array = ungroupLengths(lgArray[i]);
		for(var j = 0; j < array.length; j++)
		{
			result.push(array[j]);
		}
	}

	return result;
}

//----------------------------------------------

// calculates the total length of a combination of Lengths
// using a binary string to represent the Lengths in the combo
function calcComboLength(binary, cutArray)
{
	var result = 0;

	for(var i = 0; i < binary.length; i++)
	{
		var binaryIndex = binary.length - 1 - i;
		var arrayIndex = cutArray.length - 1 - i;

		if(binary[binaryIndex] === 1) {result += cutArray[arrayIndex].pieceLength;}
	}

	return result;
}

//----------------------------------------------

function findBestStockAndCombo(stockArray, comboList)
{
	var okLeftover = 0;

	var result = {};
	var max = stockArray[stockArray.length - 1].pieceLength; // longest Length in stock
	var bestDiff = max;
	var diff = max;

	var array = Object.keys(comboList);
	for(var b = array.length - 1; b >= 0; b--)
	{
		var bin = array[b];
		var len = comboList[bin];
		for(var i = 0; i < stockArray.length; i++)
		{
			diff = stockArray[i].pieceLength - len;
			if(0 <= diff && diff < bestDiff)
			{
				bestDiff = diff;
				result.binary = JSON.parse("[" + bin + "]");
				result.stockIndex = i;
				result.leftover = diff;
				if(diff <= okLeftover) {return result;}
			}
		}
	}

	return result;
}

//------------------------------------------------------

function makeComboList(cutArray, max)
{
	var comboList = {};
	var binary = convertToBinaryArray(1, cutArray.length);

	while(hasBit(binary))
	{
		var len = calcComboLength(binary, cutArray);
		if(len <= max)
		{
			comboList[binary] = len;
			binary = getNextBinary(binary);
		}
		else {
			binary = getSkippedBinary(binary);
		}
	}

	return comboList;
}

//--------------------------------------------------------

// returns true if binary has at least one true value
function hasBit(binary)
{
	for(var i = 0; i < binary.length; i++)
	{
		if(binary[i] === 1) {return true;}
	}
}

//--------------------------------------------------------

// gets next combination that isn't guaranteed to be longer than the max stock length
function getSkippedBinary(binary)
{
	var array = binary;

	array[array.length - 1] = 1;
	for(var i = array.length - 2; i >= 0; i--)
	{
		if(array[i] === 1) { break; }
		else {
			array[i] = 1;
		}
	}

	return getNextBinary(array);

}

//---------------------------------------------------------

// increments binary number by 1
function getNextBinary(binary)
{
	var flip = function(bit){ return bit === 1 ? 0 : 1; };
	var array = binary;

	array[array.length - 1] = flip(array[array.length - 1]);
	for(var i = array.length - 2; i >= 0; i--)
	{
		if(array[i + 1] === 1) { break; }
		else {
			array[i] = flip(array[i]);
		}

	}

	return array;
}

//-----------------------------------------------------------

/** Function Name: removeCombos
/**       Purpose: removes combos from comboList where length is greater then max and shares a bit with combo
/**    Parameters: comboList hash of combos and lengths, the combo to compare them to and the max length
/**       Returns: void, modifies comboList
*/function removeCombos(comboList, combo, max)
{
	var array = Object.keys(comboList);

	for(var i = array.length - 1; i >= 0; i--)
	{
		var len = comboList[array[i]];
		var thisCombo = JSON.parse("[" +array[i] + "]");
		if(comboList[array[i]] > max || hasCommonBit(thisCombo, combo))
		{
			delete comboList[array[i]];
		}
	}
}

//--------------------------------------------------------------

// returns true if both arrays have a true bit in the same position
function hasCommonBit(bin1, bin2)
{
	for(var i = 0; i < bin1.length && i < bin2.length; i++)
	{
		var idx1 = bin1.length - 1 - i;
		var idx2 = bin2.length - 1 - i;
		if(bin1[idx1] === 1 && bin2[idx2] === 1) {return true;}
	}
	return false;
}

//----------------------------------------------------------

/** Function Name: convertToBinaryArray
/**       Purpose: converts a positive integer to a binary value as a bool array
/**    Parameters: the integer to convert
/**       Returns: a bool array representation of the integer in binary
*/
function convertToBinaryArray(value, numBits)
{
	// array of false elements
	var result =[];
	for(var i = 0; i < numBits; i++) {result.push(0);}

	var binValues = [0, 1];

	var idx = result.length - 1;
	while(value > 0)
	{
		result[idx] = binValues[value % 2];
		idx--;

		value -= value % 2;
		value /= 2;
	}

	return result;
}

//----------------------------------------------

/** Function Name: convertFromBinaryArray
/**       Purpose: converts an array of bool to its integer value
/**    Parameters: an array of true and false representing a binary value
/**       Returns: the integer equivalent to the binary value
*/
function convertFromBinaryArray(value)
{
  var result = 0;
	var numBits = value.length;

	for (var i = 0; i < numBits; i++)
	{
		if (value[numBits - i - 1] === 1)
			result += Math.pow(2, i);
	}

	return result;
}

//-----------------------------------------------
