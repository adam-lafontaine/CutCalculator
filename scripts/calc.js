/*
calc.js - computational functions
*/

//-------------------------------------------------

// sorts lengths to be cut from stock LengthsInStockList
// takes an array of LengthGroups to cut
// and an array of LengthGroups in stock to be cut from
// returns an array of ResultSet objects
function sortLengths(cutLengthGroupArray, stockLengthGroupArray, cutLoss)
{
	let results = []; // array of ResultSet objects

	// convert arrays of LengthGroups to arrays of Lengths
	let cutArray = convertToLengthArray(cutLengthGroupArray);
	let stockArray = convertToLengthArray(stockLengthGroupArray);

	// sort arrays
	let descending = function(lhs, rhs){ return rhs.pieceLength - lhs.pieceLength };
	let ascending = function(lhs, rhs){ return lhs.pieceLength - rhs.pieceLength };

	cutArray.sort(descending);
	stockArray.sort(ascending);

	// hash of bool array for combo and coresponding length
	let comboList = makeComboList(cutArray, stockArray[stockArray.length - 1].pieceLength, cutLoss);


	// loop until no combos remain
	while(Object.keys(comboList).length > 0)
	{
		// choose best stock/combo
		let bestStockAndCombo = findBestStockAndCombo(stockArray, comboList, cutLoss);

		// get stock from stockArray and remove
		let bestStock = stockArray.splice(bestStockAndCombo.stockIndex, 1)[0];

		// get array of Lengths from cutArray and remove
		let bestCombo = bestStockAndCombo.binary;
		let lengthArray = getLengthArrayFromCombo(bestCombo, cutArray);

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
	let result = [];

	for(let i = cutArray.length - 1; i >= 0; i--)
	{
		let bit = binary[i];
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
	let result = [];
	for(let i = 0; i < lgArray.length; i++)
	{
		let array = ungroupLengths(lgArray[i]);
		for(let j = 0; j < array.length; j++)
		{
			result.push(array[j]);
		}
	}

	return result;
}

//----------------------------------------------

// calculates the total length of material required for a combination of Lengths
// using a binary string to represent the Lengths in the combo
function calcComboLength(binary, cutArray, cutLoss)
{
	let result = 0;

	for(let i = 0; i < binary.length; i++)
	{
		let binaryIndex = binary.length - 1 - i;
		let arrayIndex = cutArray.length - 1 - i;

		result += binary[binaryIndex] * cutArray[arrayIndex].pieceLength;
	}

	// account for extra material required from cutting
	let numPieces = binary.reduce((total, val) => { return total + val; });

	if(cutLoss)
		result += cutLoss * numPieces;

	return result;
}

//----------------------------------------------

function findBestStockAndCombo(stockArray, comboList, cutLoss)
{
	let okLeftover = 0;

	let result = {};
	let max = stockArray[stockArray.length - 1].pieceLength; // longest Length in stock
	let bestDiff = max;
	let diff = max;

	let array = Object.keys(comboList);
	for(let b = array.length - 1; b >= 0; b--)
	{
		let bin = array[b];
		let len = comboList[bin];
		for(let i = 0; i < stockArray.length; i++)
		{
			diff = stockArray[i].pieceLength - len;

			if(diff < 0 && abs(diff) < cutLoss)
				diff = 0;

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

function makeComboList(cutArray, max, cutLoss)
{
	let comboList = {};
	let binary = convertToBinaryArray(1, cutArray.length);

	while(hasBit(binary))
	{
		let len = calcComboLength(binary, cutArray, cutLoss);
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
	return binary.indexOf(1) != -1;
}

//--------------------------------------------------------

// gets next combination that isn't guaranteed to be longer than the max stock length
function getSkippedBinary(binary)
{
	let array = binary;

	array[array.length - 1] = 1;
	for(let i = array.length - 2; i >= 0; i--)
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
	let flip = function(bit){ return bit === 1 ? 0 : 1; };
	let array = binary;

	array[array.length - 1] = flip(array[array.length - 1]);
	for(let i = array.length - 2; i >= 0; i--)
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
	let array = Object.keys(comboList);

	for(let i = array.length - 1; i >= 0; i--)
	{
		let len = comboList[array[i]];
		let thisCombo = JSON.parse("[" +array[i] + "]");
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
	for(let i = 0; i < bin1.length && i < bin2.length; i++)
	{
		let idx1 = bin1.length - 1 - i;
		let idx2 = bin2.length - 1 - i;
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
	let result =[];
	for(let i = 0; i < numBits; i++) {result.push(0);}

	let binValues = [0, 1];

	let idx = result.length - 1;
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
  let result = 0;
	let numBits = value.length;

	for (let i = 0; i < numBits; i++)
	{
		if (value[numBits - i - 1] === 1)
			result += Math.pow(2, i);
	}

	return result;
}

//-----------------------------------------------
