/*
Object (class) definitions
*/

function Length(length, label)
{
  this.pieceLength = length;
  this.pieceLabel = label;
}


//--------------------------------------------------

// represents a quantity of Length objects all having the same
// length and label
function LengthGroup(qty, length, label)
{
  this.quantity = qty;
  this.groupLength = length;
  this.groupLabel = label;
}

//---------------------------------------------------

function ResultSet(stockLength, lengthArray, leftover)
{
  this.stockLength = stockLength;
  this.lengthGroupArray = groupLengths(lengthArray);
  this.leftover = leftover;
}

//----------------------------------------------------------


//*****************************************************************

// compresses an array of Lengths into an array of LengthGroups
function groupLengths(lengthArray)
{
  let result = [];
  let isNewLength = true;
  let len = lengthArray[0].pieceLength;
  let lab = lengthArray[0].pieceLabel;
  result.push(new LengthGroup(1, len, lab));

  for(let i = 1; i < lengthArray.length; i++)
  {
    len = lengthArray[i].pieceLength;
    lab = lengthArray[i].pieceLabel;
    isNewLength = true;
    for(let j = 0; j < result.length; j++)
    {
      if(result[j].groupLength === len && result[j].groupLabel === lab)
      {
        isNewLength = false;
        result[j].quantity++;
        break;
      }
    }

    if(isNewLength)
    {
      result.push(new LengthGroup(1, len, lab));
    }
  }

  return result;
}

//-------------------------------------------------

// converts a LengthGroup object to an array of identical Lengths
function ungroupLengths(group)
{
  let result = [];
  for(let i = 0; i < group.quantity; i++)
  {
    result.push(new Length(group.groupLength, group.groupLabel));
  }

  return result;
}
