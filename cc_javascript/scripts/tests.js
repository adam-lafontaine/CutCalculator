/*
file used for test input
*/
$(function()
{
  cutGroupArray = [];
  cutGroupArray.push(new LengthGroup(3, 10, 'short'));
  cutGroupArray.push(new LengthGroup(3, 48, 'long'));
  cutGroupArray.push(new LengthGroup(3, 30, 'medium'));

  stockGroupArray = [];
  stockGroupArray.push(new LengthGroup(10, 100, '10ft'));

  enterTestData(cutGroupArray, stockGroupArray);

});

//************ FOR TESTING *****************************************

function enterTestData(cutGroupArray, stockGroupArray)
{
  removeAllInputRows();

  for(var i = 0; i < cutGroupArray.length; i++)
  {
    addCutRow();
    $('#TextBoxQtyCut' + (i+1)).val(cutGroupArray[i].quantity);
    $('#TextBoxLengthCut' + (i+1)).val(cutGroupArray[i].groupLength);
    $('#TextBoxLabelCut' + (i+1)).val(cutGroupArray[i].groupLabel);
  }

  for(var i = 0; i < stockGroupArray.length; i++)
  {
    addStockRow();
    $('#TextBoxQtyStock' + (i+1)).val(stockGroupArray[i].quantity);
    $('#TextBoxLengthStock' + (i+1)).val(stockGroupArray[i].groupLength);
    $('#TextBoxLabelStock' + (i+1)).val(stockGroupArray[i].groupLabel);
  }

}
